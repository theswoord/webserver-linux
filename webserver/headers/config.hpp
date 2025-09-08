#pragma once

#include "webserv.hpp"

struct t_server;

class config
{
private:
std::map<std::string ,std::string>general_server;
std::map<std::string ,std::string>standart_config;
std::map<std::string,std::string>requirements;
std::vector<t_server>servers_conf;
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
bool is_folder_av(std::string folder);
void get_file(std::ifstream &file);
void duplicates_found();
bool is_port_av(std::string str);
t_server transfer(std::string section ,  std::map<std::string , std::string> section_data);
std::string config_section(std::string &parser);
void do_tests(void);
std::vector<t_server> get_configs(void);
std::map<std::string, std::string> get_config(std::string conf);
void search_and_standarize(std::map<std::string ,std::string>&server,std::map<std::string ,std::string>&standart);
std::string key_value_getter(std::map<std::string , std::string> map , std::string key);
};