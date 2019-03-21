#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>

#include <signal.h>
#include "./term.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace msk;

unsigned const c_lineWidth = 160;

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

int main(int argc, char** argv) {

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

    return 0;
}