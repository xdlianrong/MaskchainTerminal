#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <signal.h>
#include "./term.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>

using namespace msk;
using namespace boost::asio;
using namespace std;

io_service io;
ip::udp::endpoint send_ep;
ip::udp::socket sock(io, ip::udp::endpoint(ip::udp::v4(), 6699));
ip::udp::endpoint recv_ep1;
ip::udp::endpoint send_ep2;

unsigned const c_lineWidth = 160;

FILE *fp1 = NULL;
FILE *fp2 = NULL;
FILE *fp3 = NULL;

class communication{
    public:
        void startWorking();
        void doWork();
        void workLoop();

    private:
       std::string m_name;

        mutable std::mutex x_work;
        std::unique_ptr<std::thread> m_work;
        mutable std::condition_variable m_state_notifier;
};

void communication::startWorking(){
    std::unique_lock<std::mutex> l(x_work);
    m_state_notifier.notify_all();
    m_work.reset(new thread([&](){
        workLoop();
    }));
}

void communication::workLoop(){
    while(1){
        this_thread::sleep_for(std::chrono::milliseconds(100));
        doWork();
    }
}

void  communication::doWork(){
    char recv_buff[1024]={0};
    sock.receive_from(buffer(recv_buff,1024),send_ep);
    fp1 = fopen("file1.txt","a+");
    cout<<"open file1.txt"<<recv_buff<<endl;
    fputs(recv_buff,fp1);
    memset(recv_buff,'\0',1024);
    fclose(fp1);
}

class remoteEndpoint{
    public:
        remoteEndpoint(vector<char> in){
            string rep=bufferToStr(in);
            int idx=rep.find(":");
            this->rmIp=rep.substr(0, idx);
            string tmp=rep.substr(idx+1, rep.length()-1);
            this->rmPort=boost::lexical_cast<int>(tmp);
        }

        remoteEndpoint(string rep){
            int idx=rep.find(":");
            this->rmIp=rep.substr(0, idx);
            string tmp=rep.substr(idx+1, rep.length()-1);
            this->rmPort=boost::lexical_cast<int>(tmp);
        }

        ~remoteEndpoint(){}

        int traverser(){
            return 0;
        }

        string bufferToStr(vector<char> in) {
            string str;
            for(int i=0; i<in.size(); i++) {
                if(in[i]!=0) str+=in[i];
            }
            return str;
        }

        string rmEndpoint;
        string rmIp;
        int rmPort;
};

std::string exec(const char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
		result += buffer;
	}
	pclose(pipe);
	return result;
}

class commandHandler {
public:
    commandHandler():
        rpcEndpoint("localhost:8545"), 
        commandCounter(1) 
    {}
    commandHandler(std::string _rpcEndpoint):
        rpcEndpoint(_rpcEndpoint), 
        commandCounter(1) 
    {}

    void sendCommand(std::string _command) {
        std::cout<<exec(this->commandMaker(_command).data())<<std::endl<<std::endl;
        this->commandCounter++;
    }

    std::string commandMaker(std::string _command) {
        std::string ret;
        std::pair<std::string, std::string> cmdPair = this->commandParser(_command);
        ret = "curl -X POST -s " + this->rpcEndpoint + \
             " --data '{\"jsonrpc\":\"2.0\",\"method\":\"" + \
            cmdPair.first +  "\",\"params\":[" + \
            cmdPair.second + "],\"id\":" + \
            boost::lexical_cast<std::string>(this->commandCounter)+"}'";
            
            if(cmdPair.first == "eth_sendTransaction"){
                sock.send_to(buffer(cmdPair.second),send_ep);
            }
        return ret;
    }

    std::pair<std::string, std::string> commandParser (std::string cmdStr) {
        std::pair<std::string, std::string> ret;
        ret.first=cmdStr.substr(0,cmdStr.find("("));
        ret.second=cmdStr.substr(cmdStr.find("(")+1, cmdStr.find(")")-cmdStr.find("(")-1);
        return ret;
    }

private:
    int commandCounter;
    std::string rpcEndpoint;
};

void netWork(const char *ip_address){
    communication m_listener;

    string interchargeServer = boost::lexical_cast<string>(ip_address);
   // std::cout<<"Make sure your intercharge server is running forwarding program and destination port is open!\nInput your intercharge server: example: 1.2.3.4:1234 \n>>>";
   // std::cin>>interchargeServer;
    remoteEndpoint iServerEp = remoteEndpoint(interchargeServer);
    send_ep = ip::udp::endpoint(ip::address::from_string(iServerEp.rmIp),iServerEp.rmPort);
    iServerEp.~remoteEndpoint();
    m_listener.startWorking();
    while(1){continue;};
} 

int main(int argc, char** argv) {

    string ip_address;
    cout<<"Please input another endpoint's ip address such as 127.0.0.1:6699"<<endl;
    cout<<">";
    cin>>ip_address;

    const char *ip_address_ = ip_address.data(); 

    std::thread net_(netWork,ip_address_);

    boost::program_options::variables_map vm;

    boost::program_options::options_description terminalMode("终端命令表", c_lineWidth);
    auto addTerminalOption = terminalMode.add_options();
    addTerminalOption("safe-mode", "以安全模式启动终端");
    addTerminalOption("help", "显示帮助");

    try{
        //parse_command_line()对输入的选项做解析
        //store()将解析后的结果存入选项存储器
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, terminalMode), vm);
    }catch(...){
        std::cout << "输入的参数中存在未定义的选项！\n";
        return 0;
    }

    if(vm.count("help") ) {
        std::cout << terminalMode << std::endl;    //打印所有的选项信息
    }

    std::string rep;
    commandHandler ch;
    
    std::cout << GrayBold "\n===== Maskash Terminal  v0.0.1 alpha =====" StyleReset << "\n";
    std::cout << GrayBold "======== 西安西电链融科技有限公司 ========" StyleReset << "\n\n";

    std::cout << "请输入 Maskash RPC 端点" << "\n" << "> ";
    std::cin >> rep;

    std::cout << GrayBold "Maskash 底层平台连接中....."<<StyleReset;
    
    try{
        ch = commandHandler(rep);
    }catch(...){
        std::cout << MaroonBold "连接失败！" StyleReset << " 请检查RPC端点是否已启动 或 端点是否输入正确！\n";
        return -1;
    }
    std::cout << GreenBold<<"成功" StyleReset << "\n";

    std::cout << "控制台启动完成" << "\n\n";
    std::string command = "\n";

    for(; ; ) {
        std::cout << "> ";
        std::cin >> command;
        if(command!="q") {
            std::cout << "Maskash返回值：\n ";
            ch.sendCommand(command);
        } else {
            std::cout << "\n退出控制台\n";
            break;
        }
    }
    net_.join();

    return 0;
}