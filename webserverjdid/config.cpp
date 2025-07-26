#include "webserv.hpp"

t_server::t_server(std::string name, std::map<std::string, std::string> data)
{
    this->section_name = name;
    this->section_data = data;
}

void config::get_file(std::ifstream &file) // hna anbda n9ra config file
{
    std::string parser;
    std::string tempsecname;
    std::string key, value;
    std::map<std::string, std::string> tempserver;
    std::string savename;
    std::string parsersave;
    while (std::getline(file, parser)) // matnsach default value ila makanoch f file dialk
    {
        if (parser.size() == 0)
            continue;

        parsersave = parser;
        key = parsersave.substr(0, parser.find(" = "));
        parsersave.erase(0, parser.find(" = ") + 3);
        value = parsersave;
        if (config_section(parser).size() == 0)
        {
            this->general_server.insert(std::pair<std::string, std::string>(key, value));
        }
        else
        {
            if (savename != config_section(parser))
            {
                if (savename.size()!= 0)
                {
                this->servers_conf.push_back(transfer(savename, tempserver));
                }
                savename = config_section(parser);
                tempserver.clear();
                continue;
            }
            tempserver.insert(std::pair<std::string, std::string>(key, value));

            if (file.eof()) // newline flkher makayt9rach
            {
                tempserver.insert(std::pair<std::string, std::string>(key, value));
                
                this->servers_conf.push_back(transfer(savename, tempserver));

                break;
            }
        }
    }
    this->servers_conf.push_back(transfer("general", this->general_server));
    // print_map(this->general_server);
    // for (size_t i = 0; i < 3; i++)
    // {
    //     std::cout << servers_conf[i].section_name <<std::endl;
    //     print_map(this->servers_conf[i].section_data);
    //     std::cout <<  std::endl;
    // }
}

// bool config::complete_configs( std::map<std::string , std::string >&server)
// {
//     std::map<std::string , std::string >::iterator it;
//     bool found;
//     // std::string keycompare = "port ";
//     it = server.begin();
//     while(it != server.end())
//     {
//     // found = (std::find(this->requirements.begin(), this->requirements.end(), it->first) != this->requirements.end()); // myvar = *it
//     // std::cout << it->first  << found << std::endl;
//         // *it->first
//         ++it;
//     }
//     return true;
// }

void config::requirements_init(void)
{
    // this->requirements.push_back("port"); // critical
    // this->requirements.push_back("server_name"); //critical // la somme dial criticals if missing get critical
    // this->requirements.push_back("index"); //non critical
    // this->requirements.push_back("root"); //non critical
    // this->requirements.push_back("limit_client_bs"); //non critical
    this->requirements.insert(std::pair<std::string , std::string>("port","0123456789") ); // hna
    this->requirements.insert(std::pair<std::string , std::string>("default_server","0123456789.") ); // hna
    this->requirements.insert(std::pair<std::string , std::string>("default_err","abcdefghijklmnopqrstuvwxyz. /0123456789") ); // hna
    this->requirements.insert(std::pair<std::string , std::string>("index","abcdefghijklmnopqrstuvwxyz. ") ); // hna
    this->requirements.insert(std::pair<std::string , std::string>("root","abcdefghijklmnopqrstuvwxyz./") ); // hna
    this->requirements.insert(std::pair<std::string , std::string>("listing","01") ); // hna
    this->requirements.insert(std::pair<std::string , std::string>("Limit_client_BS","0123456789KMG") ); // hna




}
void config::search_and_standarize(std::map<std::string ,std::string>&server,std::map<std::string ,std::string>&standart)
{
    // std::map<std::string , std::string>::iterator it = server.begin(); 
    std::map<std::string , std::string>::iterator it2 = standart.begin() ; 

    while (server.find(it2->first)!=server.end())
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
    
    // complete_configs(this->servers_conf[0].section_data);
    // search_and_standarize(this->general_server, this->requirements.);

    std::cout << "kaynin " << this->server_count  << " servers"<< std::endl;
    std::vector<t_server>::iterator it = this->servers_conf.begin();
    for (int i = 0; i < this->server_count; i++)
    {

    // std::cout << this->servers_conf[i].section_name << std::endl; 

    if(!clean_config(this->servers_conf[i].section_data))
    {
        std::cerr << this->servers_conf[i].section_name << " Problem in config Cannot be started" << std::endl;
        // this->servers_conf[i];
        this->servers_conf.erase(it+i);
        this->server_count--;
        i = 0;
        // continue;
    }
        /* code */
    }
    // std::cout << "where\n" ;
    

}


std::vector<t_server> config::get_configs(void)
{
    return this->servers_conf;
}

int config::clean_config(std::map<std::string , std::string> conf)
{
    // try
    // {
        std::map<std::string , std::string>::iterator it = conf.begin();
        std::map<std::string , std::string>::iterator reqiterator = this->requirements.begin();
        // it = std::find()
        while (reqiterator != this->requirements.end())
        {
            /* code */
        it = conf.find(reqiterator->first);
        
        if (it == conf.end() || !is_all_zwin(it->second,reqiterator->second))
        {
            std::cerr << reqiterator->first << " not found" << std::endl;
            return 0;
            /* code */
        }
        
        // if(!is_all_digit(it->second)) // khasni kola w7da bo7dha
        // {
        //     return 0;
        //     // throw(MisConfiguration());
        // }
            reqiterator++;
        }
        
    // }
    // catch(std::exception &e)
    // {
    //     std::cerr << e.what() << std::endl;
    // }
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

