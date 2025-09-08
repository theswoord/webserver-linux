#include "../headers/webserv.hpp"

int main(int ac , char ** av)
{
        signal(SIGPIPE, SIG_IGN);
    try
    {
        if (ac != 2)
            throw ConfigMissing();
        
        config configuration;
        configuration.init();
        std::ifstream Conf(av[1]);
        configuration.get_file(Conf);
        configuration.do_tests();
        server serv(configuration.get_configs());
        // std::cout << "www\n" ;
        
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

}