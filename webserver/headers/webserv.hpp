#pragma once

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
#include <sstream>
#include <json/json.h>


#include <poll.h>
#include <algorithm>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <sstream>
#include <deque>
#include <cstring>
#include <sys/wait.h>
#include "clients_tools.hpp"
#include "config.hpp"
#include "singleServer.hpp"
#include <signal.h>
// #include <cstring.h>
    // ...


#define BUFFER_SIZE 4096
#define MULTIPART -2
#define CHUNK -1
#define FORM -3

class singleServer;
struct clients_tools;
class config;

template <typename T>
std::string to_cstr(T value)
{
    std::stringstream ret;
    std::string miw;
    ret << value;
    miw = ret.str();
    return miw;
}

template <typename F>
std::string to_hex(F value)
{
    std::stringstream ret;
    std::string miw;
    ret << std::hex << value;
    miw = ret.str();
    return miw;
}

template <typename F>
long to_dec(F value)
{
    std::stringstream ret;
    ret << std::hex << value;
    long dec;
    ret >> dec;
    return dec;
}

struct t_server
{
    t_server(std::string name, std::map<std::string, std::string> data);
    std::string section_name;
    std::map<std::string, std::string> section_data;
    int mzyan;
};

struct codes
{
    std::string err404;
    std::string err403;
    std::string err400;
    std::string err414;
    std::string err413;
    std::string err405;
    std::string err409;
    std::string err429;
    std::string err406;
    std::string err500;
    std::string created;
};

class server
{
private:
    std::vector<int> onlyservers_fd;
    codes htmlcodes;
    int number;
    std::string response_string;
    std::vector<std::string> peek;
    std::vector<clients_tools *> clients;
    int clientnumber;
    int req_len;
    std::vector<std::string> requests;
    std::vector<t_server> _conf;
    std::vector<singleServer> objs;
    std::vector<pollfd> servers;

public:
    std::string peek_on_request(clients_tools &clients);
    void init();
    int fill_post(clients_tools &clients);
    void read_request(clients_tools &clients);
    std::string get_details(std::map<std::string, std::string> config, std::string details);
    std::map<std::string, std::string> get_config(std::string conf);
    server(std::vector<t_server> conf);
    ~server();
    std::string exec_cgi_maerftch(clients_tools &clients);
    void dist();
    void send_erreur(int fd, std::string hhh);
    std::string script_fetch(clients_tools clients);
    bool is_cgi_av(clients_tools &clients);
    void send_weird_message(clients_tools &clients);
    std::vector<std::string> handle_request(std::string &request);
    void response(clients_tools &clients);
    bool is_multipart(std::string pos);
    void response_delete(clients_tools &clients);
    void send_premade_html(clients_tools &clients, int code);
    std::string extract_folder(clients_tools &clients);
    void sendfile(clients_tools &clients);
    bool is_keep_alive(std::vector<std::string> &achbgha);
    std::string parse_request(std::vector<std::string> achbgha, std::string detail);
    std::string extract_method(std::string pos);
    std::string extract_path(std::string pos);
    std::string extract_value(std::string pos);
    void exec_cgi(std::map<std::string, std::string> cfg);
    std::vector<std::string> index_finder(std::map<std::string, std::string> cfg);
    bool is_directory(std::vector<std::string> achbgha);
    std::string is_index_av(std::map<std::string, std::string> cfg, std::vector<std::string> achbgha);
    std::vector<std::string> key_divide(std::string key);
    std::string extract_dir(std::map<std::string, std::string> cfg, std::vector<std::string> achbgha);
    void fill_chunked(clients_tools &clients);
    void file_listing(int fd, std::map<std::string, std::string> cfg, std::vector<std::string> achbgha);
    void fill_multipart(clients_tools &clients);
    void list_dir(std::map<std::string, std::string> cfg, std::vector<std::string> achbgha, std::vector<std::string> &saved, int fd);
    bool request_cleanser(std::vector<std::string> &req, int code);
    std::string set_headers_mime(std::string key);
    std::string code_message(std::string code);
    std::string headers(std::string &res, int fd, std::string code);
    std::string set_headers_http(std::string &response, std::string key, std::string value);
    void ajouter_client(int fd, std::vector<pollfd> &les_fd, std::map<std::string, std::string> cfg);
    bool is_a_file(std::vector<std::string> achbgha);
    std::string get_extension(std::vector<std::string> achbgha);
    void cgi_with_fetch(clients_tools &clients);
    void exec_py(clients_tools &clients);
    std::string execute_cgii(std::string &script_path, std::string interpreter);
    int fd_finder_servers(std::vector<pollfd> servs, int fd);
    int fd_finder_client(std::vector<clients_tools *> client, int fd);
    void delete_client(clients_tools &client);
    void cgi_execute(clients_tools &clients);
    bool config_checks(clients_tools &clients, std::string headers, std::string what);
    int peek_for_size(clients_tools &clients);
    std::string filename_fetcher(clients_tools &clients, int read);
    std::string execute_cgiii(char *const *argv, char *const *envp);
    void fill_form(clients_tools &clients);
    char **set_env(clients_tools &clients);
    void fill_form2(clients_tools &clients);
    std::string execute_cgtizk(char *const *argv, char *const *envp);
    bool statfolder(clients_tools &clients);
    void handle_patch(clients_tools &client);
};

void print_map(std::map<std::string, std::string> &map);
std::string split(std::string &str, std::string delimiter, std::vector<std::string> &res);
void printvector(std::vector<std::string> &res);

void ft_bzero(char *str, int len);

bool is_all_digit(std::string str);
bool is_all_zwin(std::string str, std::string exclude);
void strtrim(std::string &s1, std::string set);
