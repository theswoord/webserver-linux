#pragma once

#include "webserv.hpp"

struct t_server;
struct codes;

class singleServer
{
    private:
    std::string section;
    std::map<std::string , std::string>config;
    std::vector<std::string>req;
    // codes htmlcodes;
    pollfd serverpollfd;
    int serverfd;
    public:
    singleServer(t_server &conf);
    void init();
std::string get_details(std::map<std::string , std::string > config, std::string details);
std::map<std::string ,std::string> get_config(std::string conf);
int start_server();
int get_fd();
pollfd get_poll() const ;
std::map<std::string , std::string> get_configuration() const ;
~singleServer();
};