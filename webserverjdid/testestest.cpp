#include "except.hpp"
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

template<typename T>
    std::string to_cstr(T value)
    {
        std::stringstream ret;
        std::string miw;
        ret << value;
        miw = ret.str();
        std::cout <<"value " << value << "return" <<miw << std::endl;
        return miw;
    }


std::string set_headers_mime(std::string &responce,std::string key , std::string value)
{
    std::string star;
    std::string t_key , t_value;
    std::ifstream file("./mime.types");
    std::map<std::string, std::string>headers;
      while (std::getline(file, star)) 
      { 
        size_t pipe = star.find('|');
        if(pipe != std::string::npos)
        {
            t_key = star.substr(0,pipe);
            t_value = star.substr(pipe + 1);

            t_key.erase(0, t_key.find_first_not_of(" \t"));
            t_key.erase(t_key.find_last_not_of(" \t") + 1); 
            t_value.erase(0, t_value.find_first_not_of(" \t"));
            t_value.erase(t_value.find_last_not_of(" \t") + 1);
            headers.insert(std::make_pair(t_key,t_value));

        }
    }
    std::map<std::string , std::string>::iterator it = headers.find(key);

    if(it != headers.end())
        value = it->second;
    std::cout << value << std::endl;
    return value;
}


    std::string code_message(std::string code) // khasha tzade fl header
    {
        std::map<std::string, std::string> status;
        
        status.insert(std::make_pair("501", "Not Implemented"));
        status.insert(std::make_pair("400", "Bad Request"));
        status.insert(std::make_pair("414", "Request-URI Too long"));
        status.insert(std::make_pair("413", "Request Entity too long"));
        status.insert(std::make_pair("404", "Not Found"));
        status.insert(std::make_pair("301", "Moved Permanetly"));
        status.insert(std::make_pair("405", "Method Not Allowed"));
        status.insert(std::make_pair("403", "Forbidden"));
        status.insert(std::make_pair("200", "OK"));
        status.insert(std::make_pair("201", "Created"));
        status.insert(std::make_pair("409", "Conflict"));
        status.insert(std::make_pair("401", "Unauthorized")); 


        std::map<std::string, std::string>::iterator it = status.find(code);
        if (it != status.end()) 
        {
            return it->second;
        } else {
            return "makaynch hade l code";
        }
        return 0;
    }
    std::string headers(int fd ,  std::string code)
    {
        std::string lmessage = code_message(code);
        std::string reponse = "http/1.1" + code + " " + lmessage + "\r\n";
        // reponse +=  "Content-Type: text/html\r\n";
        // reponse +=  "Connection: close\r\n";
        //reponse +=  "\r\n";
        send(fd,reponse.c_str(), reponse.size(), 0);
        return reponse;
    }


    std::string set_headers_http(std::string &response , std::string key , std::string value)
    {
        std::string t_key , t_value;
        std::string result;


        std::streamsize contentLength;

        response += key + value + "\r\n";
        // if( key == "Content-Type")
        // {
        //     value = set_headers_mime(response,".css",t_value);
        //     response += "Content-Type : " + value + "\r\n";
        // }
        // else if (key == "Content-Length")
        // {
        //     response = "Content-Length:   7ta tji";
        // }
        // else
        //     std::cout << "makaynach " << std::endl;

        std::cout << response << std::endl;
        return response;
    }


    // std::string set_headers_mime(std::string &response,std::string key , std::string value)
    // {
    //     handle_mime();
    //     std::map<std::string, std::string>headers
    //     {key, value};


    // }
    // set_headers("Content-Type", "text/html");
    // set_headers("Content-LENGHT", "500");


    int main()
    {
        std::string responce;
        std::string value;
        std::string key;


        //set_headers_http(responce , "Content-Type" , value);
        std::cout << "dakhale l code" << std::endl;
        std::cin >> key;
        std::string code = code_message( key);
        std::cout << "ljawab :" << code << std::endl;
        //std::string code = set_headers_mime(responce , key ,value);
        //std::string code = set_headers_http(responce , key , value);
        return 0;
    }