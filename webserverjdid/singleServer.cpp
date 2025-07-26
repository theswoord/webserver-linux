#include "webserv.hpp"



// void singleServer::dist()
// {
//     // std::map<std::string,std::string> hh;
//     // if there is more start more , daba start ghir genral o zid mn b3d
//     // makhasoch istarti server ila makan fih walo
//     start_server(get_config("main server")); // hado kaynin f config file // an9lb 3la matalan root o dakchi li makaynch l9a lih chi 7el
//     for (size_t i = 0; i < this->_conf.capacity(); i++)
//     {
//             start_server(get_config(this->_conf[i].section_name)); // hado kaynin f config file // an9lb 3la matalan root o dakchi li makaynch l9a lih chi 7el

//     }
    
//     // start_server(get_config("main server")); // hado kaynin f config file // an9lb 3la matalan root o dakchi li makaynch l9a lih chi 7el
// }

// std::map<std::string, std::string> singleServer::get_config(std::string conf)
// {
//     std::vector<t_server>::iterator it = this->_conf.begin();
//     while (it != this->_conf.end())
//     {
//         if (it->section_name == conf)
//             return (it->section_data);

//         ++it;
//     }
//     return it->section_data;
// }

// std::string singleServer::get_details(std::map<std::string, std::string> config, std::string details) // hada howa li kay3ti evey detail of the config
// {
//     // std::map<std::string , std::string>::iterator it = config.begin();
//     // return()
//     return (config.find(details)->second);
// }

singleServer::~singleServer()
{
}

void singleServer::send_err(int fd, std::string errhtml)
{
    send(fd, errhtml.c_str(), errhtml.size(), 0); // kanendih
    close(fd);
}

void singleServer::init()
{
    htmlcodes.err404 = "HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>Not Found</h1>\r\n  <p>The requested URL was not hhh found on this server.</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err403 = "HTTP/1.1 403 Forbidden\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>forbidden</h1>\r\n  <p>you don't have the provileges to access here.</p>\r\n </body>\r\n</html>\r\n";
}

int singleServer::start_server()
{
    struct addrinfo hints; // generic
    struct addrinfo *result;
    struct sockaddr_in addr_it;
    socklen_t addrlen;             // what are you
    char *buffer = new char[1024]; // wach darori ?
    std::string buff;
    std::string buffprint;
    int soc_fd, res;
    // int fd, soc_fd, res;
    memset(&hints, 0, sizeof(hints)); // generic
    hints.ai_family = AF_INET;        // generic
    hints.ai_socktype = SOCK_STREAM;  // generic
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(get_details(this->config, "default_server").c_str(), get_details(this->config, "port").c_str(), &hints, &result); // iterator hhhhhh
    addr_it.sin_family = AF_INET;                                                                                     // hado aytiro
    // addr_it.sin_port = htons(8080);                                                                                   // hado aytiro
    std::memcpy(&addr_it, result->ai_addr, sizeof(addr_it));
    addrlen = sizeof(&addr_it);
    soc_fd = socket(AF_INET, SOCK_STREAM, 0); // 3mr protocol o hadok mn struct li 9bl
    res = 1;
    setsockopt(soc_fd, SOL_SOCKET, SO_REUSEADDR, &res, sizeof(int));
    // setsockopt(soc_fd, SOL_SOCKET, SO_NOSIGPIPE, &res, sizeof(int)); // hack

    if (bind(soc_fd, (sockaddr *)&addr_it, sizeof(addr_it)) < 0)
        perror("bind"); // atir
        // int flags = fcntl(soc_fd,F_GETFL);
    if (listen(soc_fd, INT_MAX) < 0)
        perror("listen");
    fcntl(soc_fd,F_SETFL, O_NONBLOCK);
    // while (1)
    // {
    //     fd = accept(soc_fd, (sockaddr *)&addr_it, &addrlen);
    //     read(fd, buffer, BUFFER_SIZE);
    //     buff = buffer;
    //     buffprint = buffer;
    //     this->requests = handle_request(buff);
    //     ft_bzero(buffer, 1024); // wach momkin ?

    //     // std::cout  << "------------------------ \n"<< buffprint << std::endl;
    //     // srand(time(NULL)); // best server everrrr
    //     // if(rand()%2 == 0)
    //     response(fd, this->requests, config);
    //     // else
    //     // send_err(fd,this->htmlcodes.err403);
    // }
    delete[] buffer;
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
    serverpollfd.fd = this->serverfd; // andwzha nichan
    serverpollfd.events = POLLIN | POLLERR | POLLHUP ;
};

std::string singleServer::get_details(std::map<std::string, std::string> config, std::string details) // hada howa li kay3ti evey detail of the config
{
    // std::map<std::string , std::string>::iterator it = config.begin();
    // return()
    return (config.find(details)->second);
}
