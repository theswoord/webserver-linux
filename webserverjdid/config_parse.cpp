#include "webserv.hpp"

std::string config::config_section(std::string &parser)
{
  //anstori l9dim o nreturnih
  static std::string saveold;
  // if (parser != saveold)
  // {

  //   /* code */
  // }
  
    if(parser[0] == '[' && parser[parser.size()-1]==']')
    {
        // return 
        saveold = parser.substr(1,parser.size()-2);
        return(parser.substr(1,parser.size()-2));
    }
    else 
    return saveold;
}