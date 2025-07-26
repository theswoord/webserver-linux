#include "webserv.hpp"

int main(int ac , char ** av)
{

    // struct sigaction sigs;

    struct sigaction minisignols;

    sigemptyset(&minisignols.sa_mask);
    sigaddset(&minisignols.sa_mask, SIGPIPE);
    minisignols.sa_flags = 0;
    minisignols.sa_handler = SIG_IGN;       

    if (sigaction(SIGPIPE, &minisignols, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    try
    {
        if (ac != 2)
            throw ConfigMissing();
        
        config configuration;
        configuration.init(); //check *.cfg
        std::ifstream Conf(av[1]); // hna dir protection b7al dial open
        configuration.get_file(Conf);
        configuration.do_tests(); // hna andir chi loop li atsartihom kamlin o npassi liha server f parametre
        std::cout << configuration.get_configs().capacity() << std::endl;
        server serv(configuration.get_configs());
        
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

}