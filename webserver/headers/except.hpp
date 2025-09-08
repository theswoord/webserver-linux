#include <iostream>

class ConfigMissing : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Config File Missing";
    }
};