#include "../headers/webserv.hpp"


std::string split(std::string &str, std::string delimiter, std::vector<std::string> &res)
{
    std::string hh;
    size_t fin = str.find(delimiter);
    size_t strsize = str.size();
    if (strsize > 0 && fin != str.npos)
    {
        hh = str.substr(0, fin);
        if (hh.size() > 0)
            res.push_back(hh);

        str = split(str.erase(0, fin + delimiter.size()), delimiter, res);
    }
    else
    {
        if (strsize > 0)
            res.push_back(str);
    }
    return str;
}

t_server config::transfer(std::string section ,  std::map<std::string , std::string> section_data)
{
    this->server_count ++ ;   
    return (t_server(section,section_data));
}

void print_map(std::map<std::string, std::string> &map)
{
    std::map<std::string, std::string>::iterator it;
    it = map.begin();
    while(it != map.end())
    {
        std::cout << "first : |" << (*it).first << "| second : |" << (*it).second << "|" << std::endl;

        ++it;
    }
}


void printvector(std::vector<std::string>&res)
{
        std::vector<std::string>::iterator it = res.begin();
    while (it != res.end())
    {
        std::cout << "|" << *it << "|" << std::endl;
        ++it;
    }
}

void ft_bzero(char *str, int len)
{
    int i = 0;
    while (i < len)
    {
        str[i] = 0;
        i++;
    }
    
}

bool is_valid_uri(std::string str) {
    return (str.find_first_of(" ") == std::string::npos &&
            str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefhijklmnopqrstuvwxyz0123456789-_~!*'();:@&=+$,/?#[]") == std::string::npos);
}

bool is_all_digit(std::string str)
{

    return (str.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_~!*'();:@&=+$,/?#[]") == std::string::npos);

}
// bool is_root_good()

bool is_all_zwin(std::string str,std::string exclude)
{

    return (str.find_first_not_of(exclude) == std::string::npos);

}

bool server::is_multipart(std::string pos)
{
       std::string ret(pos);
       std::vector<std::string>rett;
        split(ret, " ",rett);
        strtrim(rett[1],";");
        return(rett[1] == "multipart/form-data");

}

// parse requeste
std::string server::parse_request(std::vector<std::string> achbgha , std::string detail) // pain
{
    
    std::vector<std::string>::iterator it = achbgha.begin();
    std::string test ;
    
    if (detail == "method")
    {
        return(extract_method(*it));
    }
    if (detail == "path")
    {
         return(extract_path(*it));
    }
        if (detail == "folder")
    {
         return(extract_path(*it));
    }

    while (it != achbgha.end())
    {
    if (it->substr(0,it->find(": ")).find(detail) != it->npos )
    {
        if (detail == "Content-Type" && is_multipart(*it) == true)
        {

        return ("true");
        }
        return(extract_value(*it));
    }
    
    ++it;
    }
    return "";
}
std::string server::extract_method(std::string pos)
{

    std::string ret;
    ret = pos.substr(0,pos.find(" "));
    return (ret);

}
std::string extract_value(std::string pos)
{
    std::string ret;
    ret = pos.substr(pos.find(": ")+2,pos.size());
    return (ret);
}
std::string server::extract_path(std::string pos)
{

    std::string ret;
    ret = pos.substr(pos.find(" ")+1,pos.size()-(10+extract_method(pos).size()));
    return (ret);

}

std::string server::extract_folder(clients_tools &clients)
{

    std::string ret = parse_request(clients.request,"path");
    ret =  ret.substr(0,ret.rfind('/'));

    return (ret+"/");

}
std::string server::extract_value(std::string pos)
{
    std::string ret;
    ret = pos.substr(pos.find(": ")+2,pos.size());
    return (ret);
}

bool server::is_directory(std::vector<std::string> achbgha)
{
    return (parse_request(achbgha,"path")[parse_request(achbgha,"path").size()-1] != '/');
}
bool server::is_a_file(std::vector<std::string> achbgha)
{

    return (parse_request(achbgha,"path").rfind('.') != std::string::npos);
}


bool server::is_cgi_av(clients_tools &clients)
{
    std::vector<std::string>temp = key_divide(get_details(clients.config,"cgi-folder"));
    std::vector<std::string>::iterator it = temp.begin();
    std::string path = get_details(clients.config,"root")+extract_folder(clients);

    while(it != temp.end())
    {
        if(*it == path)
        return true;
        ++it;

    }
    return false;
}


std::string server::script_fetch(clients_tools clients )
{
    std::string path = get_details(clients.config,"root")+parse_request(clients.request,"path")+ get_details(clients.config,"cgiscript");
    std::ifstream file(path.c_str());
        if (file.is_open())
        {
            file.close();
            return path;
        }
    return "";
}

std::string server::is_index_av(std::map<std::string , std::string> cfg, std::vector<std::string>achbgha )
{       
    std::vector<std::string>temp = key_divide(get_details(cfg,"index"));
    std::string path;
        std::vector<std::string>::iterator it = temp.begin();
        while (it != temp.end())
        {

        path = (get_details(cfg,"root")+parse_request(achbgha,"path")+*it).c_str();
        std::ifstream file(path.c_str());
        if (file.is_open())
        {
            file.close();
            return *it;
        }
        

            ++it;
        }
        
        return "";
}

std::vector<std::string>server::key_divide(std::string key)
{
    std::vector<std::string>res ;
    split(key," ",res);
    return res;
}



std::string server::extract_dir(std::map<std::string , std::string> cfg, std::vector<std::string>achbgha)
{
    return (get_details(cfg,"root")+parse_request(achbgha,"path")) ;
}

std::string server::get_extension(std::vector<std::string> achbgha)
{
    std::string achbir = parse_request(achbgha,"path");
    if (is_a_file(achbgha))
    {
    return(achbir.substr(achbir.rfind('.'),achbir.size()));

    }
    
    return("");
}



void strtrim(std::string& s1, std::string set) {

    size_t start = s1.find_first_not_of(set);
    if (start != std::string::npos) 
        s1.erase(0, start);
    else {
        s1.clear();
        return;
    }
    size_t end = s1.find_last_not_of(set);
    if (end != std::string::npos) {
        s1.erase(end + 1);
    }
}




bool server::config_checks(clients_tools &clients, std::string headers,  std::string what)
{
    std::vector<std::string> temp;
    std::vector<std::string> configs;
    std::vector<std::string>::iterator it;

    std::string tempstring(headers);
    
    

    std::string test;
    std::string conftest;
    split(tempstring,"\r\n",temp);
    if (what == "transfer")
    {

        std::string path = parse_request(temp,"Transfer-Encoding");
        if (path != "" && path != "chunked"  )
        {
            tempstring.clear();
            temp.clear();
            configs.clear();
            test.clear();
            conftest.clear();
            return false;
        }
        
       
    }
        if (what == "postencodinglenght")
    {
        std::string transfer = parse_request(temp,"Transfer-Encoding");
        std::string lenghtt = parse_request(temp,"Content-Length");

        if( transfer == "" && lenghtt == "")
        {
            tempstring.clear();
            temp.clear();
            configs.clear();
            test.clear();
            conftest.clear();
            return false;

        }
        
    }
    if (what == "characters")
    {
        std::string path = parse_request(temp,"path");
        std::string transfer = parse_request(temp,"Transfer-Encoding");
        std::string lenghtt = parse_request(temp,"Content-Length");
        if(!is_all_zwin(path, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.-_~!*'();:@&=+$,/?#[]") )
        {
            tempstring.clear();
            temp.clear();
            configs.clear();
            test.clear();
            conftest.clear();
            return false;

        }
        
    }
        if (what == "lenght")
    {
        std::string path = parse_request(temp,"path");
        if(path.size() > 2048)
        {
            tempstring.clear();
            temp.clear();
            configs.clear();
            test.clear();
            conftest.clear();
            return false;

        }
        
    }
    if(what == "method")
    {
        conftest = get_details(clients.config,"methods");
        split (conftest," ",configs );
       test =  parse_request(temp,"method");

    it = configs.begin();
        if (std::find(it,configs.end(),test) == configs.end())
        {
            tempstring.clear();
            temp.clear();
            configs.clear();
            test.clear();
            conftest.clear();
            return false;
        }

    }
    if (what == "body_size")
    {
        size_t post_lenght = 0;
        size_t bodysize = 0;
        post_lenght = std::atoll(parse_request(temp, "Content-Length").c_str());
        bodysize = std::atoll(get_details(clients.config,"Limit_client_BS").c_str());
        if (post_lenght > bodysize)
        {
            tempstring.clear();
            temp.clear();
            configs.clear();
            test.clear();
            conftest.clear();
            return false;
        }
    }
    


    return true;
}