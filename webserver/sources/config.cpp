#include "../headers/webserv.hpp"

t_server::t_server(std::string name, std::map<std::string, std::string> data)
{
    this->section_name = name;
    this->section_data = data;
    this->mzyan = 1;
}

void config::get_file(std::ifstream &file)
{
    std::string parser;
    std::string key, value;
    std::map<std::string, std::string> tempserver;
    std::string savename;
    std::string parsersave;

    while (std::getline(file, parser))
    {
        if (parser.empty())
        {
            continue;
        }

        parsersave = parser;
        key = parsersave.substr(0, parser.find(" = "));
        parsersave.erase(0, parser.find(" = ") + 3);
        value = parsersave;

        if (config_section(parser).empty())
        {
            this->general_server.insert(std::pair<std::string, std::string>(key, value));
        }
        else
        {
            if (!savename.empty() && savename != config_section(parser))
            {
                this->servers_conf.push_back(transfer(savename, tempserver));
                tempserver.clear();
            }

            savename = config_section(parser);
            tempserver.insert(std::pair<std::string, std::string>(key, value));
        }
    }

    if (!tempserver.empty() && !savename.empty())
    {
        this->servers_conf.push_back(transfer(savename, tempserver));
    }

    this->servers_conf.push_back(transfer("general", this->general_server));
    file.close();
}


void config::requirements_init(void)
{
    this->requirements.insert(std::pair<std::string, std::string>("port", "0123456789"));
    this->requirements.insert(std::pair<std::string, std::string>("default_server", "0123456789localhost."));
    this->requirements.insert(std::pair<std::string, std::string>("index", "ABCDEFGHIKJLMNOPQRSTUVWZXYabcdefghijklmnopqrstuvwxyz. "));
    this->requirements.insert(std::pair<std::string, std::string>("root", "ABCDEFGHIKJLMNOPQRSTUVWZXYabcdefghijklmnopqrstuvwxyz-./"));
    this->requirements.insert(std::pair<std::string, std::string>("listing", "01"));
    this->requirements.insert(std::pair<std::string, std::string>("Limit_client_BS", "0123456789KMG"));  
    this->requirements.insert(std::pair<std::string, std::string>("methods", "GET DELETE POST PATCH"));
    this->requirements.insert(std::pair<std::string, std::string>("uploadfolder", "ABCDEFGHIKJLMNOPQRSTUVWZXYabcdefghijklmnopqrstuvwxyz-./"));

}
void config::search_and_standarize(std::map<std::string, std::string> &server, std::map<std::string, std::string> &standart)
{
    std::map<std::string, std::string>::iterator it2 = standart.begin();

    while (server.find(it2->first) != server.end())
    {
        it2++;
        /* code */
    }
}
void config::init()
{
    requirements_init();
}

void config::do_tests()
{

    duplicates_found();
    std::vector<t_server>::iterator it = this->servers_conf.begin();
    for (int i = 0; i < this->server_count; i++)
    {

        if (!clean_config(this->servers_conf[i].section_data))
        {
            std::cerr << "The server: [" << this->servers_conf[i].section_name << "] Cannot be started" << std::endl;
            this->servers_conf.erase(it + i);
            this->server_count--;
            i = 0;
        }
        if(  this->servers_conf[i].mzyan == 0)
        {
            this->servers_conf.erase(it + i);
            this->server_count--;
            i = 0;
        }
    }
}

std::vector<t_server> config::get_configs(void)
{
    return this->servers_conf;
}

bool config::is_port_av(std::string str)
{
    int port = 0;
    port = std::atoi(str.c_str());
    if (port >= 1024 && port <= 49151)
        return 1;
    return 0;
}

bool config::is_folder_av(std::string folder)
{
    return (access(folder.c_str(), F_OK | W_OK | R_OK) == -1);
}

int config::clean_config(std::map<std::string, std::string> conf)
{
    std::map<std::string, std::string>::iterator it = conf.begin();
    std::map<std::string, std::string>::iterator reqiterator = this->requirements.begin();
    while (reqiterator != this->requirements.end())
    {
        it = conf.find(reqiterator->first);

        if (it->first == "root" || it->first == "uploadfolder")
        {
            if (is_folder_av(it->second))
            {
                std::cerr << "3ndk mochkil f " << it->first << " either makaynch or cannot access it" << std::endl;
                return 0;
            }
        }
        if (it == conf.end() || !is_all_zwin(it->second, reqiterator->second))
        {
            std::cerr << reqiterator->first << " not found" << std::endl;
            return 0;
        }
        if (it->first == "port")
        {
            if (!is_port_av(it->second))
            {
                std::cerr << "3ndk mochkil f " << it->first << "you cannot use it" << std::endl;
                return 0;
            }
        }

        reqiterator++;
    }
    return 1;
}

std::map<std::string, std::string> config::get_config(std::string conf)
{

    std::vector<t_server>::iterator it = this->servers_conf.begin();
    while (it != this->servers_conf.end())
    {
        if (it->section_name == conf)
            return (it->section_data);

        ++it;
    }
    return it->section_data;
}

config::config()
{
    this->server_count = 0;
}
config::~config()
{
}

std::string config::key_value_getter(std::map<std::string , std::string> map , std::string key)
{
        std::string ret = map.find(key)->second;
        return (ret);
}

void config::duplicates_found()
{   
    std::string holder, holder2;
    for (std::vector<t_server>::iterator serverIT = this->servers_conf.begin(); serverIT !=this->servers_conf.end(); ++serverIT)
    {
        holder = serverIT->section_data["port"];
        holder2 = serverIT->section_data["default_server"];
        if (holder2 == "localhost")
            holder2 = "127.0.0.1";

        for (std::vector<t_server>::iterator helpIT = serverIT + 1; helpIT != this->servers_conf.end(); ++helpIT)
        {
            if (helpIT->section_data["port"] == holder && helpIT->section_data["default_server"] == holder2)
            {
                serverIT->mzyan = 0;
                helpIT->mzyan = 0;
            }
        }
    }
}
