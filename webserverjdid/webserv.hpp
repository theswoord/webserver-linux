#pragma once

#include "except.hpp"
#include <climits>
#include <signal.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <sys/select.h>
#include <string>
#include <vector>
#include <map>
#include <istream>
#include <fstream>
#include <poll.h>
#include <algorithm>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
// #include 
#include <list>
#include <strings.h>
#include <stdio.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <cstring> // linux
#include <sstream>
#define BUFFER_SIZE 1024

template<typename T>
    std::string to_cstr(T value)
    {
        std::stringstream ret;
        std::string miw;
        ret << value;
        miw = ret.str();
        // std::cout <<"value " << value << "return" <<miw << std::endl;
        return miw;
    }

// template<typename T>
// std::string to_string(const T & value) {
//     std::ostringstream oss;
//     oss << value;
//     return oss.str();
// }


struct t_server
{
    t_server(std::string name, std::map<std::string , std::string> data);
    std::string section_name;
    std::map<std::string ,std::string>section_data;
};

struct codes
{
    std::string err404;
    std::string err403;
};

class config
{
private:
std::map<std::string ,std::string>general_server;
std::map<std::string ,std::string>standart_config;
std::map<std::string,std::string>requirements;
// std::vector<std::string> config; // not used 
std::vector<t_server>servers_conf; // hada vector jam3 key value dial bzaf dial servers
// std::map<std::string , std::string> configmap;
int server_count;
public:
class MisConfiguration : public std::exception
{
    virtual const char*what() const throw()
    {
        return ("configuration error \n");
    }
};
config();
~config();
int clean_config(std::map<std::string , std::string> conf);
void init();
void requirements_init();
void get_file(std::ifstream &file);
t_server transfer(std::string section ,  std::map<std::string , std::string> section_data);
std::string config_section(std::string &parser);
bool complete_configs( std::map<std::string , std::string >&server);
void do_tests(void);
std::vector<t_server> get_configs(void);
std::map<std::string, std::string> get_config(std::string conf);
void search_and_standarize(std::map<std::string ,std::string>&server,std::map<std::string ,std::string>&standart);
};

class singleServer
{
    private:
    std::string section;
    std::map<std::string , std::string>config;
    std::vector<std::string>req;
    codes htmlcodes;
    pollfd serverpollfd;
    int serverfd;
    public:
    singleServer(t_server &conf);
    void init();
std::string get_details(std::map<std::string , std::string > config, std::string details);
std::map<std::string ,std::string> get_config(std::string conf);
int start_server();
void sendimg(int fd);
void dist();
std::vector<std::string>   handle_request(std::string &request);
void send_err(int fd, std::string errhtml);
int get_fd();
pollfd get_poll() const ;
std::map<std::string , std::string> get_configuration() const ;
~singleServer();
};
class server 
{
private:
std::vector <int> onlyservers_fd;
codes htmlcodes;
int number;
std::string response_string;
std::vector<std::string> peek;

int req_len;
// int res;
std::vector<std::string> requests;
std::vector<t_server> _conf;
std::vector<singleServer>objs;
std::vector<pollfd> servers;
// singleServer *servers;
public:
void init();
std::string get_details(std::map<std::string , std::string > config, std::string details);
std::map<std::string ,std::string> get_config(std::string conf);
void start_server(std::map<std::string ,std::string> config);
server(std::vector<t_server> conf);
~server();
void sendimg(int fd);
void dist();
std::vector<std::string>   handle_request(std::string &request);
void send_err(int fd, std::string errhtml);
void response(int fd, std::vector<std::string> achbgha,std::map<std::string, std::string> cfg); // aymkn itbdl;
void response_get(int fd, std::vector<std::string> &achbgha,std::map<std::string, std::string> cfg); // aymkn itbdl;
void response_post(int fd, std::vector<std::string> achbgha,std::map<std::string, std::string> cfg);
void response_delete(int fd, std::vector<std::string> achbgha,std::map<std::string, std::string> cfg);
void sendfile(int fd, std::vector<std::string> &achbgha);
int senddocument(int fd, std::vector<std::string> &achbgha);
void sendtotoption(int fd, std::vector<std::string> &achbgha, std::map<std::string, std::string> cfg);
std::string parse_request(std::vector<std::string> &achbgha, std::string detail);
std::string extract_method(std::string pos);
std::string extract_path(std::string pos);
std::string extract_value(std::string pos);
void exec_cgi(std::map<std::string , std::string> cfg);
std::vector<std::string> index_finder(std::map<std::string , std::string> cfg);
bool is_directory(std::vector<std::string> achbgha);
std::string is_index_av(std::map<std::string , std::string> cfg, std::vector<std::string>achbgha );
std::vector<std::string>key_divide(std::string key);
std::string extract_dir(std::map<std::string , std::string> cfg, std::vector<std::string>achbgha);

void file_listing(int fd, std::map<std::string , std::string> cfg , std::vector<std::string> achbgha);
void list_dir(std::map<std::string , std::string> cfg,std::vector<std::string> achbgha,std::vector<std::string>&saved,int fd);

std::string set_headers_mime(std::string key);
std::string code_message(std::string code);
std::string headers(std::string &res,int fd ,  std::string code);
std::string set_headers_http(std::string &response , std::string key , std::string value);
void ajouter_client(int fd, std::vector<pollfd>&les_fd);
bool is_a_file(std::vector<std::string> achbgha);
std::string get_extension(std::vector<std::string> achbgha);
// std::string extract_content_lenght(std::string pos);
// void 
};

void print_map(std::map<std::string, std::string> &map);
std::string split(std::string &str, std::string delimiter, std::vector<std::string> &res);
void printvector(std::vector<std::string>&res);

void ft_bzero(char *str , int len );

bool is_all_digit(std::string str);
bool is_all_zwin(std::string str,std::string exclude);



