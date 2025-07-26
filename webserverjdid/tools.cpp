#include "webserv.hpp"


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
        /* code */
        str[i] = 0;
        i++;
    }
    
}

bool is_all_digit(std::string str)
{

    return (str.find_first_not_of("0123456789") == std::string::npos);

}
bool is_all_zwin(std::string str,std::string exclude)
{

    return (str.find_first_not_of(exclude) == std::string::npos);

}

// parse requeste

std::string server::parse_request(std::vector<std::string> &achbgha , std::string detail)
{
    std::vector<std::string>::iterator it = achbgha.begin();
    std::string test ;
    
    if (detail == "method")
    {
        return(extract_method(*it));
        /* code */
    }
    if (detail == "path")
    {
         return(extract_path(*it));
        /* code */
    }
    // it = std::find(achbgha.begin(),achbgha.end(),"")
    while (it != achbgha.end())
    {
    //     if (detail == "Host" )
    // {
    //     if((it)->find((it)->substr(0,(it)->find(": "))) )
    //     test = extract_path(*it);
    //     std::cout << "l9itha o hyaaaaa " << *it << std::endl;
    //     /* code */
    // }
    // test = it->substr(0,it->find(": "));
    // std::cout << "hhhhh " << test << std::endl;
    if (it->substr(0,it->find(": ")).find(detail) != it->npos )
    {
        // std::cout << "l9itha o hyaaaaa " << *it << std::endl;
        return(extract_value(*it));
        // return test;
    }
    //     if (it->substr(0,it->find(": ")).find(detail) != it->npos )
    // {
    //     std::cout << "l9itha o hyaaaaa " << *it << std::endl;
    //     return(extract_value(*it));
    //     // return test;
    // }
    
    ++it;
    }
    // std::cout << test << std::endl;
    return "";
}

std::string server::extract_method(std::string pos)
{

    std::string ret;
    ret = pos.substr(0,pos.find(" "));
    return (ret);

}
std::string server::extract_path(std::string pos)
{

    std::string ret;
    ret = pos.substr(pos.find(" ")+1,pos.size()-(10+extract_method(pos).size()));
    // std::cout << "hahowa path |" << ret << "|" << std::endl;
    return (ret);

}
std::string server::extract_value(std::string pos)
{
    std::string ret;
    ret = pos.substr(pos.find(": ")+2,pos.size());
    // std::cout << "hahowa hh |" << ret << "|" << std::endl;
    return (ret);
}
// std::string server::extract_content_lenght(std::string pos)
// {
//     std::string ret;
//     ret = pos.substr(pos.find(": ")+2,pos.size());
//     // std::cout << "hahowa hh |" << ret << "|" << std::endl;
//     return (ret);
// }


//response code 200 OK 201 created 400 Bad request ghlet f file 401 Unauthorized mamconectich 405 Method not allowed 

bool server::is_directory(std::vector<std::string> achbgha)
{
    return (parse_request(achbgha,"path").back() != '/');
}
bool server::is_a_file(std::vector<std::string> achbgha)
{
    return (parse_request(achbgha,"path").rfind('.') != std::string::npos);
}

std::string server::is_index_av(std::map<std::string , std::string> cfg, std::vector<std::string>achbgha )
{       
    std::vector<std::string>temp = key_divide(get_details(cfg,"index"));
    std::string path;
        std::vector<std::string>::iterator it = temp.begin();
        while (it != temp.end())
        {

        path = (get_details(cfg,"root")+parse_request(achbgha,"path")+*it).c_str();
            // std::cout << " path = " << path << " 7afozli9 " << *it << std::endl;
        std::ifstream file(path);
        if (file.is_open())
        {
            file.close();
            return *it;
            /* code */
        }
        
            // if()

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


// get_details(cfg,"root")+parse_request(achbgha,"path")+"/"


std::string server::extract_dir(std::map<std::string , std::string> cfg, std::vector<std::string>achbgha)
{
    // std::cout << "extractdir " << get_details(cfg,"root")+parse_request(achbgha,"path") << std::endl;
    return (get_details(cfg,"root")+parse_request(achbgha,"path")) ; // zid liha "/"
}

std::string server::get_extension(std::vector<std::string> achbgha)
{
    std::string achbir = parse_request(achbgha,"path");
    if (is_a_file(achbgha))
    {
    return(achbir.substr(achbir.rfind('.'),achbir.size()));

        /* code */
    }
    
    return("");
}
