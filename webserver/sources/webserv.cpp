#include "../headers/webserv.hpp"

void server::init()
{
    htmlcodes.err404 = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html>\r\n<head>\r\n<title>404 Not Found</title>\r\n<style>body {font-family: Arial, sans-serif; background-color: #f8f9fa; color: #343a40; text-align: center; padding: 50px;} h1 {font-size: 2.5em;} p {font-size: 1.2em;} a {color: #007bff; text-decoration: none;} a:hover {text-decoration: underline;}</style>\r\n</head>\r\n<body>\r\n<h1>404 Not Found</h1>\r\n<p>We're sorry, but the requested URL <code></code> was not found on this server.</p>\r\n<p><a href=\"/\">Return to Home</a></p>\r\n</body>\r\n</html>\r\n";
    htmlcodes.err403 = "HTTP/1.1 403 Forbidden\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>forbidden</h1>\r\n  <p>you don't have the provileges to access here.</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err400 = "HTTP/1.1 400 Bad Request\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>Bad Request</h1>\r\n  <p>Request body could not be read properly.</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err414 = "HTTP/1.1 414 URI Too Long\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>URI Too Long</h1>\r\n  <p>The URI provided was too long for the server to process.</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err413 = "HTTP/1.1 413 Content Too Large\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>Content Too Large</h1>\r\n  <p>Upload failed</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err405 = "HTTP/1.1 405 Method Not Allowed\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>Method Not Allowed</h1>\r\n  <p></p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err409 = "HTTP/1.1 409 Conflict\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>Conflict</h1>\r\n  <p></p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err429 = "HTTP/1.1 429 Too Many Requests\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>Too Many Requests</h1>\r\n  <p>You're doing that too often! Try again later.</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err406 = "HTTP/1.1 406 UnsupportedType\r\nContent-type: text/html\r\n\r\n<html>\r\n <body>\r\n  <h1>UnsupportedType</h1>\r\n  <p>Only 'text/html' or 'application/json' content types supported.</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.err500 = "HTTP/1.1 500 Internal Server Error\r\nContent-type: text/html\r\n\r\n<html>\r\n <head>\r\n  <title>500 Internal Server Error</title>\r\n  <style>body {font-family: Arial, sans-serif; background-color: #f8d7da; color: #721c24; text-align: center; padding: 50px;} h1 {font-size: 50px;} p {font-size: 20px;}</style>\r\n </head>\r\n <body>\r\n  <h1>500 Internal Server Error</h1>\r\n  <p>Oops! Something went wrong on our end. Please try again later.</p>\r\n </body>\r\n</html>\r\n";
    htmlcodes.created = "HTTP/1.1 201 Created\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<!DOCTYPE html>\r\n<html lang=\"en\">\r\n<head>\r\n    <meta charset=\"UTF-8\">\r\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\r\n    <title>created</title>\r\n    <style>\r\n        body {\r\n            font-family: Arial, sans-serif;\r\n            background: linear-gradient(135deg, #6a11cb, #2575fc);\r\n            display: flex;\r\n            justify-content: center;\r\n            align-items: center;\r\n            height: 100vh;\r\n            margin: 0;\r\n            color: white;\r\n        }\r\n        .container {\r\n            text-align: center;\r\n            background: rgba(255, 255, 255, 0.2);\r\n            padding: 30px;\r\n            border-radius: 10px;\r\n            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.3);\r\n        }\r\n        h1 {\r\n            font-size: 5rem;\r\n            margin: 0;\r\n        }\r\n        p {\r\n            font-size: 1.5rem;\r\n            margin: 10px 0 0;\r\n        }\r\n        @media (max-width: 600px) {\r\n            h1 {\r\n                font-size: 3rem;\r\n            }\r\n            p {\r\n                font-size: 1rem;\r\n            }\r\n        }\r\n    </style>\r\n</head>\r\n<body>\r\n    <div class=\"container\">\r\n        <h1>201</h1>\r\n        <p>Created</p>\r\n    </div>\r\n</body>\r\n</html>\r\n";
    this->clientnumber = 0;
}

std::vector<std::string> server::handle_request(std::string &request)
{
    std::vector<std::string> req;
    split(request, "\r\n", req);
    request.clear();
    return req;
}

server::server(std::vector<t_server> conf) : _conf(conf)
{
    this->init();
    this->number = this->_conf.size();
    dist();
}

void server::dist()
{
    size_t i = 0;
    for (size_t i = 0; i < this->_conf.size(); i++)
    {
        this->objs.push_back(singleServer(this->_conf[i]));
        this->onlyservers_fd.push_back(this->objs[i].get_fd());
        servers.push_back(this->objs[i].get_poll());
        std::cout << "Serving HTTP on " << get_details(this->_conf[i].section_data, "default_server") << " port " + get_details(this->_conf[i].section_data, "port") + " <" + get_details(this->_conf[i].section_data, "server_name") + "> (http://" << get_details(this->_conf[i].section_data, "default_server") << ":" << get_details(this->_conf[i].section_data, "port") << "/)" << std::endl;
    }
    std::string the_request;

    while (true)
    {
        if (poll(this->servers.data(), this->servers.size(), -1) < 0)
            std::perror("poll");

        while (i < this->objs.size() + this->clients.size())
        {
            if (servers[i].revents & POLLIN && this->objs[i].get_fd() == this->onlyservers_fd[i])
            {
                int new_socket = accept(servers[i].fd, NULL, NULL);

                if (new_socket > 0)
                {
                    if (fcntl(new_socket, F_SETFL | O_NONBLOCK) < 0)
                        std::cerr << "Error: fcntl failed for socket " << new_socket
                                  << " - " << strerror(errno) << std::endl;

                    ajouter_client(new_socket, this->servers, this->objs[i].get_configuration());
                }
            }
            if (i >= this->objs.size() && servers[i].revents & (POLLOUT | POLLHUP))
            {
                int client_index = i - this->objs.size();
                std::cout << "number of clients " << this->clients.size() << "|" << this->clients[client_index]->fd << "|" << "| " << this->clients[client_index]->filefd << " |" << std::endl;
                response(*this->clients[client_index]);
                usleep(300);
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

std::string server::get_details(std::map<std::string, std::string> config, std::string details)
{
    std::map<std::string, std::string>::iterator it = config.find(details);
    // for (std::map<std::string, std::string>::iterator it = config.begin(); it != config.end(); ++it)
    // {
    //     /* code */
    // }
    
    if (it == config.end())
    {
        return ""; 
    }

    if (details == "Limit_client_BS")
    {
        std::string saveenergy = config.find(details)->second;
        if (saveenergy[saveenergy.size() - 1] == 'M')
        {
            return (saveenergy.substr(0, saveenergy.size() - 1) + "000000");
        }
        if (saveenergy[saveenergy.size() - 1]  == 'K')
        {
            return (saveenergy.substr(0, saveenergy.size() - 1) + "000");
        }
        if (saveenergy[saveenergy.size() - 1]  == 'G')
        {
            return (saveenergy.substr(0, saveenergy.size() - 1) + "000000000");
        }
    }
    
    return (config.find(details)->second);
}

bool server::statfolder(clients_tools &clients)
{
    struct stat hhh;
    std::string path = get_details(clients.config, "root") + parse_request(clients.request, "path");
    if (stat(path.c_str(), &hhh) >= 0)
    {
        if (hhh.st_mode & S_IFDIR)
        {
            return (true);
        }
    }

    return false;
}

server::~server()
{
}

void server::response(clients_tools &clients)
{

    if (clients.readd == 0)
        read_request(clients);
    if (clients.readd == -1)
    {
        write(clients.filefd, clients.to_be_written.c_str(), clients.to_be_written.size());
        close(clients.filefd);
        close(clients.fd);
        delete_client(clients);

        return;
    }
    if (clients.readd == -2)
    {
        close(clients.fd);
        close(clients.filefd);
        delete_client(clients);

        return;
    }
    if (parse_request(clients.request,"method") == "PATCH")
    {
        handle_patch(clients);
        close(clients.fd);
        delete_client(clients);
        return;
    }

    if (parse_request(clients.request, "method") == "DELETE")
    {
        response_delete(clients);
        close(clients.fd);
        delete_client(clients);

        return;
    }

    if ((parse_request(clients.request, "method") == "GET" || parse_request(clients.request, "method") == "POST") && statfolder(clients) && is_directory(clients.request))
    {
        set_headers_http(clients.response_string, "location", parse_request(clients.request, "path") + "/");
        headers(clients.response_string, clients.fd, "301");

        close(clients.fd);
        delete_client(clients);
        return;
    }
    if (parse_request(clients.request, "method") == "GET" && statfolder(clients) && is_index_av(clients.config, clients.request) == "" && get_details(clients.config, "listing") == "1")
    {
        file_listing(clients.fd, clients.config, clients.request);
        close(clients.fd);
        delete_client(clients);

        return;
    }
    else if (parse_request(clients.request, "method") == "GET" && statfolder(clients) && is_index_av(clients.config, clients.request) == "" && get_details(clients.config, "listing") == "0")
    {

        send_premade_html(clients, 403);
        close(clients.fd);
        delete_client(clients);

        return;
    }
    else if (parse_request(clients.request, "method") == "GET" && !is_a_file(clients.request) && is_index_av(clients.config, clients.request) != "")
    {

        set_headers_http(clients.response_string, "location", parse_request(clients.request, "path") + is_index_av(clients.config, clients.request));
        headers(clients.response_string, clients.fd, "301");
        close(clients.fd);
        delete_client(clients);

        return;
    }
    if (parse_request(clients.request, "method") == "GET" && is_cgi_av(clients) && get_extension(clients.request) == ".py")
    {
        exec_py(clients);
        close(clients.fd);
        delete_client(clients);

        return;
    }
    if (parse_request(clients.request, "method") == "GET" && is_keep_alive(clients.request))
    {

        send_weird_message(clients);
        return;
    }
    else if (parse_request(clients.request, "method") == "GET" && !is_keep_alive(clients.request))
    {
        sendfile(clients);
        return;
    }
}

void server::send_weird_message(clients_tools &clients)
{
    struct stat filestat;
    std::string path;
    path = get_details(clients.config, "root") + parse_request(clients.request, "path");
    if (stat(path.c_str(), &filestat) == -1)
    {
        send_premade_html(clients, 404);
        close(clients.fd);
        delete_client(clients);

        return;
    }
    if (clients.filefd == -1)
    {
        clients.cont_len = filestat.st_size;
        clients.filefd = open(path.c_str(), O_RDONLY);
        if (clients.filefd == -1)
        {
            headers(clients.response_string, clients.fd, "403");
            close(clients.fd);
            delete_client(clients);
            return;
        }
        set_headers_http(clients.response_string, "Content-Type", set_headers_mime(get_extension(clients.request)));

        headers(clients.response_string, clients.fd, "200");
    }
    int chunk = std::min(clients.cont_len - clients.offset, static_cast<size_t>(2048));
    char *p = new char[chunk]();
    int bytesRead = read(clients.filefd, p, chunk);
    if (bytesRead <= 0)
    {
        clients.readd = -2;
        return;
    }
    if (bytesRead == -1)
    {

        delete[] p;
        close(clients.filefd);
        close(clients.fd);
        delete_client(clients);
        return;
    }
    clients.offset += chunk;
    int sent = send(clients.fd, p, chunk, 0);
    if (sent == 0)
    {
        clients.readd = -2;
        return;
    }
    delete[] p;
    if (clients.offset >= clients.cont_len || sent == -1)
    {
        close(clients.filefd);
        close(clients.fd);
        delete_client(clients);
    }
}

void server::sendfile(clients_tools &clients)
{
    std::string path;
    unsigned long contlen = 0;
    path = get_details(clients.config, "root") + parse_request(clients.request, "path");
    std::ifstream file(path.c_str(), std::ifstream::binary);
    if (file)
    {
        file.seekg(0, std::ifstream::end);
        contlen = file.tellg();
    }
    contlen += 0;
    set_headers_http(this->response_string, "Content-Type", set_headers_mime(get_extension(clients.request)));

    headers(this->response_string, clients.fd, "200");
    file.seekg(0, std::ifstream::beg);
    while (file.tellg() != -1)
    {
        char *p = new char[1024];

        ft_bzero(p, 1024);
        file.read(p, 1024);

        int size = send(clients.fd, p, 1024, 0);
        if (size <= 0)
        {
            close(clients.fd);
            file.close();
            delete_client(clients);
            delete[] p;

            return;
        }

        delete[] p;
    }
    close(clients.fd);
    file.close();
    delete_client(clients);
}

void server::file_listing(int fd, std::map<std::string, std::string> cfg, std::vector<std::string> achbgha)
{
    DIR *mydir;
    struct dirent *toread;
    std::vector<std::string> save;
    mydir = opendir(extract_dir(cfg, achbgha).c_str());

    if (!mydir)
    {
        std::cerr << fd << "folder makaynch a ostad" << std::endl;
        send_erreur(fd, this->htmlcodes.err404);
        return;
    }
    for (toread = readdir(mydir); toread != NULL; toread = readdir(mydir))
    {
        save.push_back(toread->d_name);
    }
    closedir(mydir);
    list_dir(cfg, achbgha, save, fd);
}

// Helper function to check if a path corresponds to a directory
bool isDirectory(const std::string& path)
{
    struct stat statbuf;
    if (stat(path.c_str(), &statbuf) != 0)
    {
        return false;
    }
    return S_ISDIR(statbuf.st_mode);
}

void server::list_dir(std::map<std::string, std::string> cfg, std::vector<std::string> achbgha, std::vector<std::string> &saved, int fd)
{
    // --- SVG Icons ---
    const std::string FOLDER_ICON = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"20\" height=\"20\" viewBox=\"0 0 24 24\" fill=\"none\" stroke=\"currentColor\" stroke-width=\"2\" stroke-linecap=\"round\" stroke-linejoin=\"round\"><path d=\"M22 19a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h5l2 3h9a2 2 0 0 1 2 2z\"></path></svg>";
    const std::string FILE_ICON = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"20\" height=\"20\" viewBox=\"0 0 24 24\" fill=\"none\" stroke=\"currentColor\" stroke-width=\"2\" stroke-linecap=\"round\" stroke-linejoin=\"round\"><path d=\"M13 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V9z\"></path><polyline points=\"13 2 13 9 20 9\"></polyline></svg>";

    // --- Start of HTML Document ---
    std::string path_prefix = extract_dir(cfg, achbgha);
    std::string request_path = parse_request(achbgha, "path");

    std::string list =
        "<!DOCTYPE html>\r\n"
        "<html lang=\"en\">\r\n"
        "<head>\r\n"
        "    <meta charset=\"UTF-8\">\r\n"
        "    <title>Index of " + request_path + "</title>\r\n"
        "    <style>\r\n"
        "        body { font-family: sans-serif; margin: 0; background-color: #f4f5f7; color: #172b4d; }\r\n"
        "        .container { max-width: 800px; margin: 2em auto; background-color: #ffffff; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); overflow: hidden; }\r\n"
        "        header { padding: 1.5em 2em; background-color: #0052cc; color: #ffffff; }\r\n"
        "        header h1 { margin: 0; font-size: 1.5em; }\r\n"
        "        table { width: 100%; border-collapse: collapse; }\r\n"
        "        th, td { padding: 0.8em 2em; text-align: left; border-bottom: 1px solid #dfe1e6; }\r\n"
        "        th { background-color: #f4f5f7; font-weight: 600; }\r\n"
        "        a { color: #0052cc; text-decoration: none; font-weight: 500; }\r\n"
        "        a:hover { text-decoration: underline; }\r\n"
        "        .icon { vertical-align: middle; margin-right: 1em; }\r\n"
        "    </style>\r\n"
        "</head>\r\n"
        "<body>\r\n"
        "    <div class=\"container\">\r\n"
        "        <header><h1>Index of " + request_path + "</h1></header>\r\n"
        "        <table>\r\n"
        "            <thead><tr><th>Name</th></tr></thead>\r\n"
        "            <tbody>\r\n";

    // --- Generate Table Rows (C++98 compatible loop) ---
    for (std::vector<std::string>::const_iterator it = saved.begin(); it != saved.end(); ++it)
    {
        const std::string& entry = *it; // Dereference the iterator to get the string

        if (entry == ".") continue;

        std::string full_path = path_prefix + entry;
        std::string href = request_path;
        if (!href.empty() && href[href.size() - 1] != '/') href += '/';
        href += entry;

        std::string icon;
        if (isDirectory(full_path))
        {
            icon = FOLDER_ICON;
            href += "/";
        }
        else
        {
            icon = FILE_ICON;
        }

        list += "<tr><td><span class=\"icon\">" + icon + "</span><a href=\"" + href + "\">" + entry + "</a></td></tr>\r\n";
    }

    // --- End of HTML Document ---
    list +=
        "            </tbody>\r\n"
        "        </table>\r\n"
        "    </div>\r\n"
        "</body>\r\n"
        "</html>\r\n";

    // --- Send HTTP Response (C++98 compatible string conversion) ---
    std::stringstream ss;
    ss << list.size();
    std::string content_length = ss.str();

    std::string http_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + content_length + "\r\n\r\n";
    send(fd, http_header.c_str(), http_header.size(), 0);
    send(fd, list.c_str(), list.size(), 0);
    close(fd);
}

// void server::list_dir(std::map<std::string, std::string> cfg, std::vector<std::string> achbgha, std::vector<std::string> &saved, int fd)
// {
//     std::vector<std::string>::iterator it = saved.begin();
//     std::string list;
//     list = "<!DOCTYPE html>\r\n"
//            "<html>\r\n"
//            "<body>\r\n"
//            "\r\n"
//            "<h2>" +
//            extract_dir(cfg, achbgha) + "</h2>\r\n"
//                                        "\r\n"
//                                        "<pre><img src=\"/favicon.ico\" alt=\"Icon \">  Name <hr>\r\n"
//                                        "\r\n";
//     while (it != saved.end())
//     {
//         // while (*it == "." || *it == "..")
//         //     ++it;
//         list += "<a href=\"" + parse_request(achbgha, "path") + *it + "\">" + *it + "</a>"
//                                                                                     "\t\t\t" +
//                 "\r\n"

//             ;

//         ++it;
//     }
//     list +=
//         "\r\n"
//         "<hr></pre>\r\n"
//         "\r\n"
//         "</body>\r\n"
//         "</html>\r\n";
//     int ktbt = send(fd, "HTTP/1.1 200 OK\r\n\r\n", 19, 0);
//     int sent = send(fd, list.c_str(), list.size(), 0);
//     close(fd);
// }

void server::ajouter_client(int fd, std::vector<pollfd> &les_fd, std::map<std::string, std::string> cfg)
{
    struct pollfd poll_fd;
    poll_fd.fd = fd;
    poll_fd.events = POLLOUT | POLLHUP;

    les_fd.push_back(poll_fd);
    this->clients.push_back(new clients_tools(fd, cfg));
    this->clientnumber++;
}

int server::peek_for_size(clients_tools &clients)
{
    char *buffero = new char[BUFFER_SIZE]();
    int secondrequest = recv(clients.fd, buffero, BUFFER_SIZE, MSG_PEEK);
    if (secondrequest <= 0)
    {
        clients.readd = -2;
        return -1;
    }
    std::string seconddelim(buffero, secondrequest);
    clients.multipart_lenght -= (seconddelim.find("\r\n\r\n") + 4);
    delete[] buffero;
    return seconddelim.find("\r\n\r\n") + 4;
}

std::string server::peek_on_request(clients_tools &clients)
{
    // if()
    char *buffer = new char[4096]();
    int size = recv(clients.fd, buffer, 4096, MSG_PEEK);
    if (size <= 0)
    {
        clients.readd = -2;
        return "";
    }
    std::string buff(buffer, size);
    clients.reqsize = buff.find("\r\n\r\n") + 4;
    buff = buff.substr(0, clients.reqsize);
    delete[] buffer;
    if (config_checks(clients, buff, "transfer") == false)
    {
        send_premade_html(clients, 500);
        clients.readd = -2;
        return "err";
    }
    if (config_checks(clients, buff, "characters") == false)
    {
        send_premade_html(clients, 400);
        clients.readd = -2;
        return "err";
    }
    if (config_checks(clients, buff, "lenght") == false)
    {
        send_premade_html(clients, 414);
        clients.readd = -2;
        return "err";
    }
    if (config_checks(clients, buff, "method") == false)
    {
        send_premade_html(clients, 405);
        clients.readd = -2;
        return "err";
    }
    else if (buff.find("POST") != std::string::npos && config_checks(clients, buff, "body_size") == false)
    {
        send_premade_html(clients, 413);
        clients.readd = -2;
        return "err";
    }
    else if (buff.find("POST") != std::string::npos && config_checks(clients, buff, "postencodinglenght") == false)
    {
        send_premade_html(clients, 400);
        clients.readd = -2;
        return "err";
    }

    return extract_method(buff);
}

int server::fill_post(clients_tools &clients)
{
    int chunk = std::min(clients.post_lenght, static_cast<ssize_t>(1024));
    char *buffer = new char[chunk]();

    int test = recv(clients.fd, buffer, chunk, 0);
    if (test <= 0)
    {
        clients.readd = -2;
        return -1;
    }

    clients.to_be_written.append(buffer, chunk);

    ft_bzero(buffer, chunk);
    delete[] buffer;
    clients.post_lenght -= chunk;
    if (clients.post_lenght <= 0)
    {
        clients.readd = -1;
        return 1;
    }
    return 0;
}
std::string server::filename_fetcher(clients_tools &clients, int read)
{
    std::string tkhrbi9;
    char *buff = new char[read]();
    int readd = recv(clients.fd, buff, read, 0);
    if (readd <= 0)
    {
        clients.readd = -2;
        return "";
    }
    std::string str(buff, readd);
    delete[] buff;
    std::vector<std::string> vec;
    split(str, "\r\n", vec);
    std::vector<std::string>::iterator it = vec.begin();
    while (it != vec.end())
    {
        if (it->substr(0, it->find(": ")).find("Content-Disposition") != it->npos)
        {
            tkhrbi9 = it->substr(it->rfind("=\""), it->npos);
            strtrim(tkhrbi9, "\"=");
            return tkhrbi9;
        }
        ++it;
    }

    return "";
}
void server::fill_multipart(clients_tools &clients)
{

    int chunk = std::min(clients.multipart_lenght, static_cast<ssize_t>(1024));
    char *buffer = new char[chunk]();
    std::string writee;

    int readd = recv(clients.fd, buffer, chunk, 0);
    if (readd <= 0)
    {
        exit(1);
    }

    writee.append(buffer, readd);
    if (writee.rfind("--\r\n") == writee.npos)
    {
        clients.to_be_written.append(writee);
        clients.multipart_lenght -= chunk;
        writee.clear();
    }
    else
    {
        writee.erase(writee.rfind("\r\n--"));
        clients.to_be_written.append(writee);
        clients.multipart_lenght -= chunk;
    }
    if (clients.multipart_lenght <= 0)
    {
        delete[] buffer;
        clients.readd = -1;
        return;
    }

    delete[] buffer;
}

void server::fill_chunked(clients_tools &clients)
{
    char *buffer = NULL;
    buffer = new char[100]();
    if (clients.blackmagic.find("\r\n") == std::string::npos)
    {

        int readd = recv(clients.fd, buffer, 1, 0);
        if (readd <= 0)
        {
            clients.readd = -2;
            return;
        }
        clients.blackmagic.append(buffer, readd);
        delete[] buffer;
    }
    else
    {
        delete[] buffer;
        strtrim(clients.blackmagic, "\r\n");
        int dec = to_dec(clients.blackmagic) + 2;
        if (dec == 2)
        {
            clients.readd = -1;
            return;
        }
        buffer = new char[dec]();
        int readd = recv(clients.fd, buffer, dec, 0);
        if (readd <= 0)
        {
            clients.readd = -2;
            return;
        }
        clients.blackmagic.clear();
        clients.to_be_written.append(buffer, readd);
        strtrim(clients.to_be_written, "\r\n");
        delete[] buffer;
    }
}

void server::read_request(clients_tools &clients)
{

    if (clients.wach_post == 0)
    {

        if (peek_on_request(clients) == "POST")
            clients.wach_post = 1;
    }
    if (clients.wach_post == 0)
    {
        char *buffer = new char[1024];
        ft_bzero(buffer, BUFFER_SIZE);
        int size = recv(clients.fd, buffer, BUFFER_SIZE, 0);
        if (clients.readd == -2)
        {
            delete[] buffer;

            return;
        }
        if (size <= 0)
        {
            delete[] buffer;

            clients.readd = -2;
            return;
        }
        if (size > 0)
        {
            std::string buff(buffer, size);
            clients.request = handle_request(buff);
            ft_bzero(buffer, BUFFER_SIZE);
            clients.readd = 1;
        }
        delete[] buffer;
        return;
    }
    else if (clients.wach_post == 1 && clients.post_lenght == 0)
    {
        std::string buffpost;
        int size = 0;
        char *buffer = new char[clients.reqsize]();
        size = recv(clients.fd, buffer, clients.reqsize, 0);
        if (size <= 0)
        {
            clients.readd = -2;
            return;
        }
        buffpost.append(buffer, size);
        delete[] buffer;

        clients.request = handle_request(buffpost);
        clients.post_lenght = std::atoll(parse_request(clients.request, "Content-Length").c_str());
        if (is_cgi_av(clients))
        {
            clients.post_lenght = FORM;
            return;
        }
        if (parse_request(clients.request, "Content-Type") == "true")
        {
            clients.multipart_lenght = std::atoll(parse_request(clients.request, "Content-Length").c_str());

            clients.filename = filename_fetcher(clients, peek_for_size(clients));
            std::string multipartfile = get_details(clients.config, "uploadfolder") + clients.filename;
            if (access(get_details(clients.config, "uploadfolder").c_str(), W_OK) == -1)
            {
                exit(1);
            }
            clients.filefd = open(multipartfile.c_str(), O_TRUNC | O_CREAT | O_RDWR, 0666);
            clients.post_lenght = MULTIPART;
            headers(clients.response_string, clients.fd, "201");
            return;
        }
        if (!is_a_file(clients.request))
        {
            return;
        }
        std::string path;
        path = get_details(clients.config, "root") + parse_request(clients.request, "path");

        clients.filefd = open(path.c_str(), O_TRUNC | O_CREAT | O_RDWR, 0666);
        headers(clients.response_string, clients.fd, "201");
        if (clients.filefd == -1)
        {
            close(clients.fd);
            clients.readd = -1;
            return;
        }
        if (parse_request(clients.request, "Transfer-Encoding") == "chunked")
        {
            clients.post_lenght = CHUNK;
            buffpost.clear();
            return;
        }

        clients.post_lenght = std::atoll(parse_request(clients.request, "Content-Length").c_str());
        buffpost.clear();
    }
    else if (clients.wach_post == 1 && clients.post_lenght == CHUNK)
        fill_chunked(clients);
    else if (clients.wach_post == 1 && clients.post_lenght >= 0)
        fill_post(clients);
    else if (clients.wach_post == 1 && clients.post_lenght == MULTIPART)
        fill_multipart(clients);
    else if (clients.wach_post == 1 && clients.post_lenght == FORM)
        fill_form(clients);
}

bool server::is_keep_alive(std::vector<std::string> &achbgha)
{
    if (parse_request(achbgha, "Connection") == "keep-alive")
        return 1;
    else if (parse_request(achbgha, "Connection") == "close")
        return 0;

    return -1;
}

int server::fd_finder_servers(std::vector<pollfd> servs, int fd)
{
    std::vector<pollfd>::iterator it = servs.begin();
    while (it != servs.end())
    {
        if (it->fd == fd)
            return std::distance(servs.begin(), it);
        ++it;
    }
    return -1;
}

int server::fd_finder_client(std::vector<clients_tools *> client, int fd)
{
    std::vector<clients_tools *>::iterator it = client.begin();
    while (it != client.end())
    {
        if ((*it)->fd == fd)
            return std::distance(client.begin(), it);
        ++it;
    }
    return -1;
}
// void server::delete_client(clients_tools &client)
// {
//     // int clienttodel = this->clients.at((fd_finder_client(this->clients, client.fd)));
//     int clienttodel = fd_finder_client(this->clients, client.fd);
//     int servtodel = fd_finder_servers(this->servers, client.fd);
//     delete this->clients.at((clienttodel));
//     // this->clients.at((clienttodel)) = nullptr;

//     // printf(" to del %d\n" , clienttodel);
//     this->clients.erase(this->clients.begin() + (clienttodel));
//     this->servers.erase(this->servers.begin() + (servtodel));

// }

void server::delete_client(clients_tools &client)
{
    delete this->clients.at((fd_finder_client(this->clients, client.fd)));
    this->clients.erase(this->clients.begin() + (fd_finder_client(this->clients, client.fd)));
    this->servers.erase(this->servers.begin() + (fd_finder_servers(this->servers, client.fd)));
}

void open_and_delete(std::string path)
{
    DIR *dir;
    struct dirent *toread;
    dir = opendir(path.c_str());
    if (!dir)
    {
        return;
    }
    while ((toread = readdir(dir)) != NULL)
    {
        std::string file_path = path + "/" + toread->d_name;
        if (strcmp(toread->d_name, ".") == 0 || strcmp(toread->d_name, "..") == 0)
            continue;
        if (toread->d_type == DT_DIR)
        {
            open_and_delete(file_path);
            remove(file_path.c_str());
        }
        else
        {
            std::remove(file_path.c_str());
        }
    }
    closedir(dir);
}

void server::response_delete(clients_tools &clients)
{
    std::string path;
    std::string resp;

    path = get_details(clients.config, "root") + parse_request(clients.request, "path");

    open_and_delete(path);
    if (path != "/")
    {
        std::remove(path.c_str());
    }
    headers(clients.response_string, clients.fd, "204");
}

void server::send_premade_html(clients_tools &clients, int code)
{
    if (code == 403)
    {
        int size = send(clients.fd, this->htmlcodes.err403.c_str(), this->htmlcodes.err403.size(), 0);
        if (size <= 0)
        {
            clients.readd = -2;
            return;
        }
        return;
    }
    if (code == 413)
    {
        int size = send(clients.fd, this->htmlcodes.err413.c_str(), this->htmlcodes.err413.size(), 0);
        if (size <= 0)
        {
            clients.readd = -2;
            return;
        }
        return;
    }
    if (code == 500)
    {
        int size = send(clients.fd, this->htmlcodes.err500.c_str(), this->htmlcodes.err500.size(), 0);
        if (size <= 0)
        {
            clients.readd = -2;
            return;
        }
        return;
    }
    if (code == 400)
    {
        int size = send(clients.fd, this->htmlcodes.err400.c_str(), this->htmlcodes.err400.size(), 0);
        if (size <= 0)
        {
            clients.readd = -2;
            return;
        }
        return;
    }
    if (code == 405)
    {
        int size = send(clients.fd, this->htmlcodes.err405.c_str(), this->htmlcodes.err405.size(), 0);
        if (size <= 0)
        {
            clients.readd = -2;
            return;
        }
        return;
    }
    if (code == 414)
    {
        int size = send(clients.fd, this->htmlcodes.err414.c_str(), this->htmlcodes.err414.size(), 0);
        if (size <= 0)
        {
            clients.readd = -2;
            return;
        }
        return;
    }
    if (code == 404)
    {
        int size = send(clients.fd, this->htmlcodes.err404.c_str(), this->htmlcodes.err404.size(), 0);
        if (size <= 0)
        {
            clients.readd = -2;
            return;
        }
        return;
    }
}

void server::send_erreur(int fd, std::string hhh)
{
    std::string miw;
    headers(miw, fd, "404");
    send(fd, hhh.c_str(), hhh.size(), 0);
}

void server::handle_patch(clients_tools &client)
{
    std::ifstream patchfile(get_details(client.config,"patchfile").c_str());
    Json::Value value;
    patchfile >> value;
    patchfile.close();
    long actual = value["clicks"].asInt() ;
    actual++;
    value["clicks"] = actual;

    std::ofstream out(get_details(client.config,"patchfile").c_str());
    out << value;
    out.close();
    headers(client.response_string, client.fd, "200");

}