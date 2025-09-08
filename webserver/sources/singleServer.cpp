#include "../headers/webserv.hpp"




singleServer::~singleServer()
{
}

void singleServer::init()
{
    
}


int singleServer::start_server()
{
    struct addrinfo hints;
    struct addrinfo *result;
    struct sockaddr_in addr_it;
    socklen_t addrlen;
    int max_conn;
    max_conn = SOMAXCONN;
    std::string buff = get_details(this->config, "default_server");
    if (buff == "localhost")
        buff = "127.0.0.1";
    int soc_fd, res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(buff.c_str(), get_details(this->config, "port").c_str(), &hints, &result);
    addr_it.sin_family = AF_INET;
    std::memcpy(&addr_it, result->ai_addr, sizeof(addr_it));
    addrlen = sizeof(&addr_it);
    soc_fd = socket(AF_INET, SOCK_STREAM, 0);
    res = 1;
    setsockopt(soc_fd, SOL_SOCKET, SO_REUSEADDR, &res, sizeof(int));
    // setsockopt(soc_fd, SOL_SOCKET, SO_NOSIGPIPE, &res, sizeof(int));

    if (bind(soc_fd, (sockaddr *)&addr_it, sizeof(addr_it)) < 0)
        std::perror("bind");
    if (listen(soc_fd, max_conn) < 0)
        std::perror("listen");
    fcntl(soc_fd,F_SETFL, O_NONBLOCK);
    freeaddrinfo(result);
    return soc_fd;
}


int singleServer::get_fd()
{
    return(this->serverfd);
}

pollfd singleServer::get_poll() const
{
    return this->serverpollfd;
}

std::map<std::string , std::string> singleServer::get_configuration() const 
{
    return this->config;
}

singleServer::singleServer(t_server &conf) : section(conf.section_name), config(conf.section_data)
{
    this->init();
    this->serverfd = start_server();
    serverpollfd.fd = this->serverfd;
    serverpollfd.events = POLLIN | POLLERR | POLLHUP ;
};

std::string singleServer::get_details(std::map<std::string, std::string> config, std::string details)
{
    return (config.find(details)->second);
}
