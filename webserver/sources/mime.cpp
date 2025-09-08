#include "../headers/webserv.hpp"



    std::string server::set_headers_http(std::string &response , std::string key , std::string value)
    {
        std::string t_key , t_value;
        std::string result;
        response += key + ": " + value + "\r\n";
        return response;
    }

    std::string server::headers(std::string &res, int fd ,  std::string code)
    {
        std::string reponse;
        if(code == "201")
        {
            int size = send(fd,this->htmlcodes.created.c_str(), this->htmlcodes.created.size(),0);
            if(size <= 0)
            {
                return "err";
            }
            return reponse;
        }else{
        std::string lmessage = code_message(code);
        reponse = "HTTP/1.1 " + code + " " + lmessage + "\r\n";
        reponse += res;
        reponse +=  "\r\n";
        int size = send(fd,reponse.c_str(), reponse.size(), 0);
                    if(size <= 0)
            {
                return "err";
            }
        res.clear();
        }
        return reponse;
    }

    std::string server::code_message(std::string code) // khasha tzade fl header
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
        status.insert(std::make_pair("206", "Partial Content")); 


        std::map<std::string, std::string>::iterator it = status.find(code);
        if (it != status.end()) 
        {
            return it->second;
        } else {
            return "makaynch hade l code";
        }
        return 0;
    }

std::string server::set_headers_mime(std::string key) 
{
    std::string star;
    std::string value;
    std::string t_key , t_value;
    std::ifstream file("./mime.types");
    std::map<std::string, std::string> headers;

    while (std::getline(file, star)) 
    {
        size_t pipe = star.find('|');

        if (pipe != std::string::npos) 
        {
            t_key= star.substr(0, pipe);  
            t_value = star.substr(pipe + 1);   

            t_value.erase(0, t_value.find_first_not_of(" \t"));
            t_value.erase(t_value.find_last_not_of(" \t") + 1);


            std::istringstream splitt(t_key);
            std::string split;
            while (std::getline(splitt, split, ',')) 
            {
                
                split.erase(0, split.find_first_not_of(" \t"));
                split.erase(split.find_last_not_of(" \t") + 1);
                headers[split] = t_value ;
            }
        }
    }

    std::map<std::string, std::string>::iterator it = headers.find(key);
    if (it != headers.end()) 
    {
        value = it->second;
    }
    return value;
}



    std::string set_headers_http2(std::string &response , std::string key , std::string value)
    {
        std::string t_key , t_value;
        std::string result;
        response += key + ": " + value + "\r\n";
        return response;
    }


    std::string code_message2(std::string code)
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
        status.insert(std::make_pair("206", "Partial Content")); 


        std::map<std::string, std::string>::iterator it = status.find(code);
        if (it != status.end()) 
        {
            return it->second;
        } else {
            return "makaynch hade l code";
        }
        return 0;
    }