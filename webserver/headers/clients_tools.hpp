#pragma once

#include "webserv.hpp"

struct clients_tools
{
    public:
    int chunkedread;
    int wach_post;
    clients_tools(int _fd,std::map<std::string,std::string> &cfg);
    std::deque <std::vector<std::string> > request_queue;
    int index;
    size_t reqsize;
    std::vector<std::string> request;
    int fd;
    std::string blackmagic;
    std::string tjmi3adial;
    std::string multipart;
    std::string filename;
    std::string writeform;
    std::string to_be_written;
    ssize_t formpostlenght;
    std::size_t cont_len;
    std::vector <std::string>cgi_env;
    std::string response_string;
    std::map<std::string,std::string> config;
    int opened;
    ssize_t multipart_lenght;
    size_t offset;
    int readd;
    int filefd;
    ssize_t post_lenght;
    std::ifstream *file_ptr;
    std::vector<std::string>get_request();
    ~clients_tools();
};

