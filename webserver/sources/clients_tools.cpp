#include "../headers/clients_tools.hpp"

clients_tools::~clients_tools()
{

}

clients_tools::clients_tools(int _fd, std::map<std::string, std::string> &cfg)
{

    this->fd = _fd;
    this->cont_len = 0;
    this->config = cfg;
    this->opened = -1;
    this->readd = 0;
    this->filefd = -1;
    this->offset = 0;
    this->reqsize = 0;
    this->post_lenght = 0;
    this->wach_post = 0;
    this->chunkedread = 0;
}