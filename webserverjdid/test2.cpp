
#include "except.hpp"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <sys/select.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <map>
#include <istream>
#include <fstream>
#include <algorithm>
#include <list>
#include <strings.h>
#include <stdio.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <sstream>


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
    const char* to_cstr(int value)
    {
        std::stringstream ret;
        std::string miaw;
        ret << value;
        miaw = ret.str();
        std::cout <<"value " << value << "return" <<miaw << std::endl;
        return ret.str().c_str();
    }

int main()
{
    std::cout << to_cstr(51230) << std::endl;
}
// std::vector<std::string> split(std::string str , std::string delimiter)
// {

//    std::vector<std::string> res;
//    std::string strsave = str ;
//    std::string knife ;
//    int delisize = delimiter.size();
//    while (strsave.size()>=0)
//    {
//     /* code */
//     // knife.clear();
//     knife = strsave.substr(0,strsave.find(delimiter));
//     res.push_back(knife);
//     strsave.erase(2);
//     std::cout << strsave.size() << "|" << strsave << " |" << knife << "|" << std::endl;
//     if (strsave.size() <= delisize)
//     {
//         printf("salit\n");
//         // res.push_back(knife);

//         return res;
//         /* code */
//     }

//    }

//    return res;
// }

// int main()
// {
//    std::vector<std::string> res =

//     split("akala tilmido tofa7ata hh "," ");

//     // std::cout << res[it]
//     std::vector<std::string>::iterator it = res.begin();
//     while (it != res.end())
//     {
//        std::cout << *it << std::endl;
//        ++it;
//     }

// }