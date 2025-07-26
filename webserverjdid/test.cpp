
#include "except.hpp"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <sys/select.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <map>
#include <istream>
#include <fstream>
#include <algorithm>
#include <list>
#include <strings.h>
#include <stdio.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <cstring>

void sendimg(int fd)
{
    int n;
        std::ifstream file("./hello.png", std::ifstream::binary);
        if(file)
        {
            file.seekg(0,std::ifstream::end);
            std::cout << "content lenght " << file.tellg(); 
        }
    // std::streampos filesize = file.tellg();
    file.seekg(0, std::ifstream::beg);
    std::cout << file.is_open() << std::endl;
        send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);

    // std::cout << "content lenght" << file.tellg()-file.seekg(0) << std::endl;
while(file.tellg() != -1)
{
    char *p = new char[1024];

    bzero(p, 1024);
    file.read(p, 1024);

    // printf("%ld\n", file.gcount());

    send(fd, p, 1024, 0);

    delete[] p;
}
file.close();

}

int main()
{


    // int len = strlen(not_found_response_template);
    std::string buff;
    char *buffer;
    buffer = (char *)calloc(1024, 1);
    struct addrinfo hints; // generic
    memset(&hints, 0, sizeof(hints));   // generic
    hints.ai_family = AF_INET;// generic
    hints.ai_socktype = SOCK_STREAM;// generic
    hints.ai_flags = AI_PASSIVE;
    struct addrinfo *result;
    int not_found_fd = open("./hell.html",O_RDONLY); // anstorih f variable
    getaddrinfo("127.0.0.1", "8081", &hints, &result);
    // struct sockaddr_in *addr_in;
    // struct sockaddr *addr;
    struct sockaddr_in addr_it;

    // addr_it.sin_addr.s_addr =  inet_addr("10.11.5.9");
    // addr_in->
    addr_it.sin_family = AF_INET;
    addr_it.sin_port = htons(8080);
    // addr_it.sin_addr.s_addr = INADDR_ANY; //getaddrinfo()
    std::memcpy(&addr_it,result->ai_addr,sizeof(addr_it));
    // addr_it.sin_addr.s_addr = inet_addr("192.168.150.100");
    struct sockaddr_in new_address;// zaida
    // getaddrinfo("192.168.100.105","8080",(addrinfo *)&new_address,NULL ); // zaida
    socklen_t addrlen = sizeof(&addr_it); // what are you
    int soc_fd;
    int fd;
    // while(1){
    soc_fd = socket(AF_INET, SOCK_STREAM, 0);
    int res = 1;
    setsockopt(soc_fd, SOL_SOCKET, SO_REUSEADDR, &res, sizeof(int));
    if (bind(soc_fd, (sockaddr *)&addr_it, sizeof(addr_it)) < 0)
        perror("hh");   // what do you do
        // if (bind(soc_fd, (sockaddr *)&new_address, sizeof(addr_it)) < 0) // zaida
        // perror("nn");
    listen(soc_fd, 20); // 20 hya max connexions
    std::string answer;
    std::string image;
    int answer_fd;
    int n ; 
    // file.
while(1){
    fd = accept(soc_fd, (sockaddr *)&addr_it, &addrlen);
    std::cout << fd << std::endl;
    // fd = accept(soc_fd, (sockaddr *)&new_address, &addrlen); //zaida

    read(fd, buffer, 1024 - 1); // kan9ra request 
    buff = buffer;
    bzero(buffer, 1024);
    // std::cout << buff << std::endl;
    std::cout << buff << std::endl;
    answer = "."+buff.substr(4,buff.find("html"));
    // image = buff.substr(4,buff.find("png"));
    // std::cout << image << std::endl;
    answer_fd = open(answer.c_str(),O_RDONLY); // kanopni file dialo

    // std::cout << "-\n";
    // std::cout << answer << std::endl;
    read(answer_fd, buffer, 1024 - 1);
    answer.clear();
    answer = buffer;
    bzero(buffer, 1024);
    if(answer.size()>0)
    send(fd, answer.c_str(), answer.size(), 0); // kanendih
    else
    sendimg(fd);

    close(fd);
    }
    close(soc_fd);
}