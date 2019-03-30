#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/un.h>
#include <string>
#include <iostream>
#include <boost/lexical_cast.hpp>
//#include<netinet/in.h>
#define UNIXSOCKETNAME "test_socket"
#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

    std::string commandParser (std::string cmdStr) {
        static int commandCounter = 0;
        std::pair<std::string, std::string> ret;
        ret.first=cmdStr.substr(0,cmdStr.find("("));
        ret.second=cmdStr.substr(cmdStr.find("(")+1, cmdStr.find(")")-cmdStr.find("(")-1);
        std::string command = "{\"jsonrpc\":\"2.0\",\"method\":\"" + \
            ret.first +  "\",\"params\":[" + \
            ret.second + "],\"id\":" + \
            boost::lexical_cast<std::string>(commandCounter)+"}";
        commandCounter++;    
        return command;
    }

void echo_cli(int sock)
{
    char buf1[1024] = {0};
    char buf2[1024] = {0};
    int ret = 0;
    while(fgets(buf1, sizeof(buf1), stdin) != NULL)
    {
        std::string tmp_ = buf1;
        std::string input = commandParser(tmp_);
        std::cout<<input<<std::endl;
        memset(buf1,0,sizeof(buf1));
        strcpy(buf1,input.c_str());
        write(sock, buf1, strlen(buf1));
        ret = read(sock, buf2, sizeof(buf2));
        if(ret == 0)
        {
            printf("server %d close\n", sock);
            break;
        }
        std::string tmp = buf2;
        std::string output  = tmp.substr(tmp.rfind("result")+8,tmp.find_last_not_of("\"")-tmp.rfind("result")-9);
        std::cout<<output<<std::endl;
        memset(buf1, 0, sizeof(buf1));
        memset(buf2, 0, sizeof(buf2));
    }
    close(sock);
}
int main(int argc ,char **argv)
{
    int sock = socket(PF_UNIX, SOCK_STREAM, 0);
    if(sock < 0)
        ERR_EXIT("socket");
    struct sockaddr_un servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, argv[1]);
    if(connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("connect");
    echo_cli(sock);
    return 0;
}