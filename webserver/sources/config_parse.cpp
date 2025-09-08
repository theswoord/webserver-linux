#include "../headers/webserv.hpp"

std::string config::config_section(std::string &parser)
{
  static std::string saveold;
    if(parser[0] == '[' && parser[parser.size()-1]==']')
    {
        saveold = parser.substr(1,parser.size()-2);
        return(parser.substr(1,parser.size()-2));
    }
    else 
    return saveold;
}