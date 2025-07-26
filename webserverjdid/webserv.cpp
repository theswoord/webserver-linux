#include "webserv.hpp"
#include <sys/wait.h>
#include <unistd.h>
void server::init()
{
    htmlcodes.err404 = "HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>Not Found</h1>\r\n  <p>The requested URL was not hhh found on this server.</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err403 = "HTTP/1.1 403 Forbidden\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>forbidden</h1>\r\n  <p>you don't have the provileges to access here.</p>\r\n </body>\r\n</html>\r\n";
}

std::vector<std::string> server::handle_request(std::string &request)
{
    std::vector<std::string> req; // hna fin kayna request
    this->req_len = request.size();
    split(request, "\r\n", req);
    printvector(req);
    return req; // khasni nthela fih 9bl manreturnih
}

void server::start_server(std::map<std::string, std::string> config)
{
    struct addrinfo hints; // generic
    struct addrinfo *result;
    struct sockaddr_in addr_it;
    socklen_t addrlen;             // what are you
    char *buffer = new char[1024]; // wach darori ?
    std::string buff;
    std::string buffprint;

    int fd, soc_fd, res;
    memset(&hints, 0, sizeof(hints)); // generic
    hints.ai_family = AF_INET;        // generic
    hints.ai_socktype = SOCK_STREAM;  // generic
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(get_details(config, "default_server").c_str(), get_details(config, "port").c_str(), &hints, &result); // iterator hhhhhh
    // addr_it.sin_family = AF_INET;                                                                                     // hado aytiro
    // addr_it.sin_port = htons(8080);                                                                                   // hado aytiro
    std::memcpy(&addr_it, result->ai_addr, sizeof(addr_it));
    addrlen = sizeof(&addr_it);
    soc_fd = socket(AF_INET, SOCK_STREAM, 0); // 3mr protocol o hadok mn struct li 9bl
    res = 1;
    setsockopt(soc_fd, SOL_SOCKET, SO_REUSEADDR, &res, sizeof(int));
    if (bind(soc_fd, (sockaddr *)&addr_it, sizeof(addr_it)) < 0)
        perror("bind"); // atir
    if (listen(soc_fd, 20) < 0)
        perror("listen");
    while (1)
    {
        fd = accept(soc_fd, (sockaddr *)&addr_it, &addrlen);
        read(fd, buffer, BUFFER_SIZE);
        buff = buffer;
        buffprint = buffer;
        this->requests = handle_request(buff);
        ft_bzero(buffer, 1024); // wach momkin ?

        // std::cout  << "------------------------ \n"<< buffprint << std::endl;
        // srand(time(NULL)); // best server everrrr
        // if(rand()%2 == 0)
        response(fd, this->requests, config);
        // else
        // send_err(fd,this->htmlcodes.err403);
    }
    delete[] buffer;
}

server::server(std::vector<t_server> conf) : _conf(conf)
{
    this->init(); // hada kaydir errors html f string
    this->number = this->_conf.capacity();
    dist(); // hada li kaybda serveurat
}

void server::dist()
{
    size_t i = 0;
    char *buffer = new char[1024]; // wach darori ?
    // char *peek = new char[1024];
    // ft_bzero(peek, 1024);
    // std::map<std::string,std::string> hh;
    // if there is more start more , daba start ghir genral o zid mn b3d
    // makhasoch istarti server ila makan fih walo
    // start_server(get_config("main server")); // hado kaynin f config file // an9lb 3la matalan root o dakchi li makaynch l9a lih chi 7el
    for (size_t i = 0; i < this->_conf.capacity(); i++)
    {
        // start_server(get_config(this->_conf[i].section_name)); // hado kaynin f config file // an9lb 3la matalan root o dakchi li makaynch l9a lih chi 7el
        this->objs.push_back(singleServer(this->_conf[i]));
        this->onlyservers_fd.push_back(this->objs[i].get_fd());
        servers.push_back(this->objs[i].get_poll());
        // int flags = fcntl(this->objs[i].get_fd(),F_GETFL);
        // if (flags)
        // fcntl(this->objs[i].get_fd(),F_SETFL, flags | O_NONBLOCK);
    }
    // for (size_t i = 0; i < this->objs.capacity(); i++)
    // {
    // }

    while (1)
    {
        poll(this->servers.data(), this->servers.size(), -1); // 3 > clients // zdt timeout

        // std::cout << "hh" << std::endl;
        while (i < this->objs.capacity())
        {
            if (servers[i].revents & POLLIN && this->objs[i].get_fd() == this->onlyservers_fd[i])
            {
                std::cout << "lkwaa " << std::endl;
                int new_socket = accept(servers[i].fd, NULL, NULL);
                // this->servers.push_back()
                // int flags =fcntl(new_socket,F_GETFL);
                fcntl(new_socket,F_SETFL |O_NONBLOCK);
                ajouter_client(new_socket,this->servers);
                std::cout << new_socket << " waaa" << std::endl;
                if (new_socket >= 0)
                {
                    int size = recv(new_socket, buffer, BUFFER_SIZE, 0); 
                    if (size == -1)
                    {
                        std::cerr << "waaaaaaaa3" << std::endl;
                        exit(1);
                    }

                    std::string buff(buffer, size);
                    this->requests = handle_request(buff);
                    ft_bzero(buffer, BUFFER_SIZE); // wach momkin ?
                    response(new_socket, this->requests, this->objs[i].get_configuration());
                }
            }

            i++;
        }
        i = 0;
    }
}

std::map<std::string, std::string> server::get_config(std::string conf)
{
    std::vector<t_server>::iterator it = this->_conf.begin();
    while (it != this->_conf.end())
    {
        if (it->section_name == conf)
            return (it->section_data);

        ++it;
    }
    return it->section_data;
}

std::string server::get_details(std::map<std::string, std::string> config, std::string details) // hada howa li kay3ti evey detail of the config
{
    // std::map<std::string , std::string>::iterator it;
    // return()
    if (details == "Limit_client_BS")
    {
        /* code */
        std::string saveenergy = config.find(details)->second;
        if (saveenergy.back() == 'M')
        {
            return (saveenergy.substr(0, saveenergy.size() - 1) + "000000");
        }
        if (saveenergy.back() == 'K')
        {
            return (saveenergy.substr(0, saveenergy.size() - 1) + "000");
        }
        if (saveenergy.back() == 'G')
        {
            return (saveenergy.substr(0, saveenergy.size() - 1) + "000000000");
        }
        // std::cout << "ri7t tyayz " << config.find(details)->second.back() << std::endl;
        // it = config.find(details);
        // std
        // std::cout << "tyayz " << it->second.back() << std::endl;
    }

    return (config.find(details)->second);
}

server::~server()
{
}

void server::send_err(int fd, std::string errhtml)
{
    send(fd, errhtml.c_str(), errhtml.size(), 0); // kanendih
    close(fd);
}

void server::
response(int fd, std::vector<std::string> achbgha, std::map<std::string, std::string> cfg) // anzid headers oula ndir chi container fih all datas
{

    // std::cout << (parse_request(achbgha,"method") == "GET" && is_directory(achbgha) && is_index_av(cfg,achbgha) == "") <<std::endl;
    // std::cout <<"file hh "<<  is_a_file(achbgha) <<" directory "<< is_directory(achbgha)<< std::endl;
    // exit(0);
    if (parse_request(achbgha, "method") == "GET" && !is_a_file(achbgha) && is_directory(achbgha) ) // ila t799 l3ks then indexfiles
    {
        set_headers_http(this->response_string, "location", parse_request(achbgha, "path") +"/");
        headers(this->response_string, fd, "301");
        // parse_request(achbgha,"method");
        // achbgha[0] = parse_request(achbgha,"method") +" "+ parse_request(achbgha,"path") + "/" + " HTTP/1.1";
        // achbgha[0].replace(parse_request(achbgha,"method").size()+1, (parse_request(achbgha,"path") + is_index_av(cfg)).size(), parse_request(achbgha,"path") + is_index_av(cfg)) ;
    }

    if (parse_request(achbgha, "method") == "GET" && !is_a_file(achbgha) && is_index_av(cfg, achbgha) == "") // ila t799 l3ks then indexfiles
    {
        std::cout << "HAHAHAHAHAAHAHAHAHAH" << std::endl;
        // achbgha[0] = parse_request(achbgha,"method") +" "+ parse_request(achbgha,"path") + is_index_av(cfg,achbgha) + " HTTP/1.1";
        file_listing(fd, cfg, achbgha);
        // parse_request(achbgha,"method");
        // achbgha[0] = parse_request(achbgha,"method") +" "+ parse_request(achbgha,"path") + "/" + " HTTP/1.1";
        // achbgha[0].replace(parse_request(achbgha,"method").size()+1, (parse_request(achbgha,"path") + is_index_av(cfg)).size(), parse_request(achbgha,"path") + is_index_av(cfg)) ;
    }
    else if (parse_request(achbgha, "method") == "GET" && !is_a_file(achbgha) && is_index_av(cfg, achbgha) != "")
    {
        std::cout << "HOHOHOHOHOOHOHOHOHOH" << std::endl;

        set_headers_http(this->response_string, "location", parse_request(achbgha, "path") + is_index_av(cfg, achbgha));
        headers(this->response_string, fd, "301");
        // achbgha[0] = parse_request(achbgha,"method") +" "+ parse_request(achbgha,"path") + is_index_av(cfg,achbgha) + " HTTP/1.1";
    }
    std::cout << "waaaaaaaaaaaaaa" << std::endl;

    if (parse_request(achbgha, "method") == "GET")
    {
        std::cout << "GET\n";
        // if (achbgha[0].find("/favicon.ico") != achbgha[0].npos)
        // {
        //     std::cout << "FAVICON" << std::endl;
        //     sendimg(fd);
        // }
        // std::cout << "hahowaaa " << achbgha[0].substr(4, achbgha[0].size() - 12) << std::endl;

        response_get(fd, achbgha, cfg);
    }
    else if (parse_request(achbgha, "method") == "POST")
    {
        std::cout << "POST\n";
        // send(fd, "HTTP/1.1 200 OK\r\n\r\nara", 22, 0);
        response_post(fd, achbgha, cfg);
        // close(fd);
    }
    else if (parse_request(achbgha, "method") == "DELETE")
    {
        std::cout << "DELETE\n";
        response_delete(fd, achbgha, cfg);

        // send(fd, "HTTP/1.1 200 OK\r\n\r\nms7to", 24, 0);
        // close(fd);
    }
    else
    {
        send_err(fd, this->htmlcodes.err404);
    }
}

void server::response_get(int fd, std::vector<std::string> &achbgha, std::map<std::string, std::string> cfg)
{
    std::string resp;
    resp += get_details(cfg, "root");
    // std::vector<std::string>::iterator it = std::find(achbgha.begin(),achbgha.end(),"Sec-Fetch-Dest: document") ;
    // std::vector<std::string>::iterator it = std::find(achbgha.begin(),achbgha.end(),"GET /index.html HTTP/1.1") ;
    // if (it != achbgha.end())
    // {
    //     // std::cout << *it << std::endl;
    //     if(senddocument(fd,achbgha) == 1)  // hna
    //         send_err(fd, this->htmlcodes.err404);

    //     /* code */
    // }
    // else
    // {
    //     sendfile(fd , achbgha);
    // }
    /////////////////////
    //    exec_cgi(cfg);
    sendtotoption(fd, achbgha, cfg);
}

void server::sendimg(int fd)
{
    std::ifstream file("./favicon.ico", std::ifstream::binary);
    if (file)
    {
        file.seekg(0, std::ifstream::end);
        std::cout << "content lenght " << file.tellg();
    }
    send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);
    // send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0); // hna andir content lenght

    file.seekg(0, std::ifstream::beg);
    std::cout << file.is_open() << std::endl;
    while (file.tellg() != -1)
    {
        char *p = new char[1024];

        bzero(p, 1024);
        file.read(p, 1024);

        // printf("%ld\n", file.gcount());

        send(fd, p, 1024, 0);

        delete[] p;
    }
    // close(fd);
    file.close();
}

void server::response_post(int fd, std::vector<std::string> achbgha, std::map<std::string, std::string> cfg)
{
    std::string resp;
    // achbgha.at(0);
    int size = 1;
    char  buffer[10000];
    resp = "HTTP/1.1 200 OK\r\n\r\n";
    // // resp += "<html>\r\n<body>\r\n<h1>";
    // resp += get_details(cfg, "root");
    // resp += "\r\n";
    // // resp += achbgha[0];

    while (size>0)
    {
        size = recv(fd,buffer,1000,0);
        /* code */
    }
    std::cout << buffer << std::endl;
    // // resp += "</h1>\r\n</body>\r\n</html>";
    // // get_config("root")
    // set_headers_http()
    achbgha.at(0);
    get_details(cfg,"hh");
    // // get_details(cfg,"root");
    send(fd, resp.c_str(), resp.size(), 0); // kansendih
    // headers(resp,fd,"200");
    // exec_cgi(cfg);
    // close(fd);
}

void server::response_delete(int fd, std::vector<std::string> achbgha, std::map<std::string, std::string> cfg)
{
    std::string resp;
    achbgha.at(0);
    resp = "HTTP/1.1 200 OK\r\n\r\n";
    // resp += "<html>\r\n<body>\r\n<h1>";
    resp += get_details(cfg, "root");
    // resp += "\r\n";
    // resp += achbgha[0];
    // resp += "</h1>\r\n</body>\r\n</html>";
    // get_config("root")
    // get_details(cfg,"root");
    send(fd, resp.c_str(), resp.size(), 0); // kansendih
    close(fd);
}

void server::sendfile(int fd, std::vector<std::string> &achbgha)
{
    // std::cout << "dkhelthnqyqqqqqqqqqqqqqqqqqqq\n" ;
    std::string path;
    path = achbgha[0].substr(4, achbgha[0].size() - 13); // khasni expandi dakchi
    std::cout << "file diali " << path.c_str() << std::endl;
    std::ifstream file(path.c_str(), std::ifstream::binary);
    if (file)
    {
        file.seekg(0, std::ifstream::end);
        std::cout << "content lenght " << file.tellg();
    }
    send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);
    // send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0); // hna andir content lenght

    file.seekg(0, std::ifstream::beg);
    std::cout << file.is_open() << std::endl;
    while (file.tellg() != -1)
    {
        char *p = new char[1024];

        ft_bzero(p, 1024);
        file.read(p, 1024);

        // printf("%ld\n", file.gcount());

        send(fd, p, 1024, 0);

        delete[] p;
    }
    close(fd);
    file.close();
}

int server::senddocument(int fd, std::vector<std::string> &achbgha) // khassni seekg teelg ta d documents
{
    // hna andir teelgo aymchi leak
    //  std::string answer;
    //  char *buffer = new char[1024];
    //  ft_bzero(buffer,1024);

    // ft_bzero(buffer, 1024);

    std::string path;
    path = "." + achbgha[0].substr(4, achbgha[0].size() - 13); // changed
    std::ifstream file(path.c_str(), std::ifstream::binary);
    if (file)
    {
        file.seekg(0, std::ifstream::end);
        std::cout << "content lenght " << file.tellg();
    }
    send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);
    // send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0); // hna andir content lenght

    file.seekg(0, std::ifstream::beg);
    std::cout << file.is_open() << std::endl;
    while (file.tellg() != -1)
    {
        char *p = new char[1024];

        ft_bzero(p, 1024);
        file.read(p, 1024);

        // printf("%ld\n", file.gcount());

        send(fd, p, 1024, 0);

        delete[] p;
    }
    close(fd);
    file.close();
    return 0;
}


void server::sendtotoption(int fd, std::vector<std::string> &achbgha, std::map<std::string, std::string> cfg)
{
    // std::string response ;
    std::string path;
    unsigned long contlen = 0;
    path = get_details(cfg, "root") + parse_request(achbgha, "path"); // khasni ngadha
    std::cout << "file diali " << path << std::endl;
    std::ifstream file(path, std::ifstream::binary);
    if (file)
    {
        file.seekg(0, std::ifstream::end);
        // std::cout << "content lenght " << file.tellg();
        contlen = file.tellg();
    }
    // send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);
    // code_message("200");

    set_headers_http(this->response_string, "Content-Type", set_headers_mime(get_extension(achbgha)));
    // set_headers_http(this->response_string, "Content-Length", to_cstr(contlen));

    headers(this->response_string, fd, "200");

    // send(fd, "Content-Length:\r\n", 17, 0); // hna andir content lenght
    // // send(fd, std::to_string(file.tellg()).c_str(), 17, 0); // hna andir content lenght
    // send(fd, to_cstr(file.tellg()), std::strlen(to_cstr(file.tellg())), 0); // hna andir content lenght
    // send(fd, "\r\n", 2, 0); // hna andir content lenght

    file.seekg(0, std::ifstream::beg);
    // std::cout << file.is_open() << std::endl;
    while (file.tellg() != -1)
    {
        char *p = new char[1024];

        ft_bzero(p, 1024);
        file.read(p, 1024);

        // printf("%ld\n", file.gcount());

        send(fd, p, 1024, 0);

        delete[] p;
        //         char p[1024];

        // file.read(p, 1024);

        // // printf("%ld\n", file.gcount());

        // send(fd, p, 1024, 0);
    }
    close(fd);
    file.close();
}

void server::exec_cgi(std::map<std::string, std::string> cfg)
{

    std::string script_path = get_details(cfg, "cgi-folder") + "script.py";

    pid_t pid = fork();

    if (pid < 0)
    {

        std::cerr << "Fork failed!" << std::endl;
        return;
    }
    else if (pid == 0)
    {

        std::vector<char> python_path("/usr/bin/python3", "/usr/bin/python3" + strlen("/usr/bin/python3"));
        std::vector<char> script(script_path.begin(), script_path.end());
        python_path.push_back('\0');
        script.push_back('\0');
        char *args[] = {python_path.data(), script.data(), NULL};

        char *env[] = {NULL};

        if (execve(args[0], args, env) == -1)
        {
            std::cerr << "Failed to execute CGI script." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // parent proces
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            std::cout << "CGI script exited with status: " << WEXITSTATUS(status) << std::endl;
        }
    }
}

std::vector<std::string> server::index_finder(std::map<std::string, std::string> cfg)
{
    std::vector<std::string> found;
    std::string indexref = get_details(cfg, "index");
    split(indexref, " ", found);
    return found;
}

// bool server::is_directory(std::string request )
// {

// }

void server::file_listing(int fd, std::map<std::string, std::string> cfg, std::vector<std::string> achbgha)
{
    DIR *mydir;
    struct dirent *toread;
    std::vector<std::string> save;
    // struct stat wahh;

    std::cout << extract_dir(cfg, achbgha).c_str() << " hhhh " << std::endl;
    mydir = opendir(extract_dir(cfg, achbgha).c_str());

    if (!mydir)
    {
        std::cerr << fd << "folder makaynch a ostad" << std::endl;
        return;
    }
    for (toread = readdir(mydir); toread != NULL; toread = readdir(mydir))
    {
        save.push_back(toread->d_name);
    }
    closedir(mydir);
    list_dir(cfg, achbgha, save, fd);
}

void server::list_dir(std::map<std::string, std::string> cfg, std::vector<std::string> achbgha, std::vector<std::string> &saved, int fd)
{
    std::vector<std::string>::iterator it = saved.begin();
    struct stat stats;
    // andir function dial send pliiiiiiz // an7ied . o ..
    std::string list;
    list = "<!DOCTYPE html>\r\n"
           "<html>\r\n"
           "<body>\r\n"
           "\r\n"
           "<h2>" +
           extract_dir(cfg, achbgha) + "</h2>\r\n"
                                       "\r\n"
                                       "<pre><img src=\"/favicon.ico\" alt=\"Icon \">  Name              Size <hr>\r\n"
                                       "\r\n";
    while (it != saved.end())
    {
        // while (*it== "." || *it == "..")
        //     ++it;
        stat(it->c_str(), &stats);
        list += "<a href=\"" + parse_request(achbgha, "path") + *it + "\">" + *it + "</a>"
                                                                                          "\t\t\t" + "\r\n"

            ; // + root

        // std::cout << fd << *it  << " " << stats.st_size << std::endl;
        ++it;
        /* code */
    }
    list +=
        "\r\n"
        "<hr></pre>\r\n"
        "\r\n"
        "</body>\r\n"
        "</html>\r\n";
    send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);

    send(fd, list.c_str(), list.size(), 0);
    close(fd);
}

// response(code)
// set_headers("content-lenght", "")

void server::ajouter_client(int fd, std::vector<pollfd>&les_fd)
{
    struct pollfd poll_fd;
    poll_fd.fd = fd;
    les_fd.push_back(poll_fd);
}