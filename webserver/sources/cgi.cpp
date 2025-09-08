#include "../headers/webserv.hpp"


void server::fill_form(clients_tools &clients)
{
        clients.formpostlenght = std::atoll(parse_request(clients.request, "Content-Length").c_str());
    std::string content_type = parse_request(clients.request, "Content-Type");

    int form = std::min(clients.formpostlenght, static_cast<ssize_t>(1024));
    char *buffer = new char[form]();
  
    clients.writeform.clear();
    ssize_t readd = recv(clients.fd, buffer, form, 0);
    if (readd <= 0) {
        std::cerr << "Failed to read POST data" << std::endl;
        delete[] buffer;
        return;
    }
    clients.writeform.append(buffer, readd);
    delete[] buffer; 
    std::string script_path = "/home/nabil/webserver-linux/beforepush/cgi/script.py";
    std::string interp = "/usr/bin/python3";
 

 char **envp = set_env( clients);
    char *const argv[] = {(char *)interp.c_str(), (char *)script_path.c_str(), NULL};
    clients.response_string = execute_cgiii(argv, envp);
    for (int i = 0; envp[i]; i++)
    {
       delete envp[i];
    }
    
    delete[] envp;

     headers(clients.response_string, clients.fd, "200");
send(clients.fd, clients.response_string.c_str(), clients.response_string.length(),0);

    clients.readd = -1;
}


std::string server::execute_cgiii(char *const *argv, char *const *envp)
 {
    int pipefd[2]; 
    std::string output;

    if (pipe(pipefd) == -1) {
        perror("pipe creation failed");
        return "Error: Pipe creation failed";
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        return "Error: Fork failed";
    }

    if (pid == 0) {

        close(pipefd[0]);

        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 failed (stdout)");
            exit(1);
        }

        if (dup2(pipefd[1], STDERR_FILENO) == -1) {
            perror("dup2 failed (stderr)");
            exit(1);
        }

        close(pipefd[1]); 

        if (execve(argv[0], argv, envp) == -1) {
            perror("execve failed");
            exit(1);
        }
    } else {
        close(pipefd[1]);
        char buffer[1024];
        ssize_t count;
        while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            output.append(buffer, count);
        }

        if (count == -1) {
            perror("read from pipe failed");
        }

        close(pipefd[0]); 
        waitpid(pid, NULL, 0);
    }
    return output;
}


char **server::set_env(clients_tools &clients)
{
    std::string interp = "/usr/bin/python3";
    // printf("hnaya\n");
    // std::cout <<  get_details(clients.config, "cgi-folder") + get_details(clients.config, "hhhhh") << std::endl;
    // exit(13);
    std::string script_path = get_details(clients.config, "cgi-folder");
    std::string env_query_string = "QUERY_STRING=" + clients.writeform;
    std::string env_content_length = "CONTENT_LENGTH=" + to_cstr(clients.formpostlenght);
    std::string port = "SERVER_PORT=" + get_details(clients.config, "port");
    std::string method = "REQUEST_METH0D=" + parse_request(clients.request, "method");
    std::string env_name_server = "SERVER_NAME=webserve";
    std::string env_content_type = "CONTENT_TYPE=" + parse_request(clients.request, "Content-Type");
    std::string script_name = "SCRIPT_NAME=" + get_details(clients.config, "cgi-folder") + parse_request(clients.request, "path");
    std::string protocol = "SERVER_PROTOCOL=HTTP/1.1";
    std::string gateway_interface = "GATEWAY_INTERFACE=CGI/1.1";
    std::string script_filename = "SCRIPT_FILENAME=" + get_details(clients.config, "root") + parse_request(clients.request, "path");
    std::string pythopath = "PYTHONPATH=" + interp;
    std::vector<std::string> env_vars;
    env_vars.push_back(method);
    env_vars.push_back("CONTENT_TYPE=application/x-www-form-urlencoded");
    env_query_string = env_query_string + "&l7ma9=howahada";
    env_vars.push_back(env_query_string);
    env_vars.push_back(env_content_length);
    env_vars.push_back(port);
    env_vars.push_back(env_name_server);
    env_vars.push_back(protocol);
    env_vars.push_back(gateway_interface);
    env_vars.push_back(script_filename);
    env_vars.push_back(pythopath);
    for (std::vector<std::string>::iterator it = env_vars.begin() ; it != env_vars.end(); ++it)
    {
        std::cout << "\" " << *it << "\" "<< std::endl;
    }
    
    // env_vars.push_back("DISPLAY=:0");

    char **envp = new char*[env_vars.size() + 1];
    
    for (size_t i = 0; i < env_vars.size(); ++i) {
        envp[i] = new char[env_vars[i].size() + 1];
        std::strcpy(envp[i], env_vars[i].c_str());
    }

    envp[env_vars.size()] = NULL;
    return envp;
}

void server::cgi_with_fetch(clients_tools &clients)
{
    std::string path;
    std::string cgi_response;
    path = script_fetch(clients);

    std::string interp_py = "/usr/bin/python3";
    std::string interp_js = "/usr/bin/node";
    if (get_extension(clients.request) == ".js")
    {
        cgi_response = execute_cgii(path, interp_js);
    }
    else
    {
        cgi_response = execute_cgii(path, interp_py);
    }

    set_headers_http(clients.response_string, "Content-Type", "text/html");
    headers(clients.response_string, clients.fd, "200");
    if (!cgi_response.empty())
    {
        int size = send(clients.fd, cgi_response.c_str(), cgi_response.size(), 0);
        if (size <= 0)
        {
            exit(1);
        }
        cgi_response.clear();
    }
    return;
}

std::string server::exec_cgi_maerftch(clients_tools &clients)
{

    std::string path = script_fetch(clients);
    int pipefd[2];
    std::string output;
    std::string interpreter = "/usr/bin/python3";

    if (pipe(pipefd) == -1)
    {
        std::perror("pipe");
        return "";
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        std::perror("fork");
        return "";
    }

    if (pid == 0)
    {
        char *const argv[] = {(char *)interpreter.c_str(), (char *)path.c_str(), NULL};
        char *const envp[] = {NULL};

        close(pipefd[0]);               
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]);               

        if (execve(interpreter.c_str(), argv, envp) == -1)
        {

            std::perror("execve");
            exit(1);
        }
    }
    else
    {
        close(pipefd[1]);
        char buffer[1024];
        ssize_t count;
        while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0)
        {
            output.append(buffer, count);
        }
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
    }
    return output;
}


void server::exec_py(clients_tools &clients)
{
    std::string path;
    std::string cgi_response;
    path = get_details(clients.config, "root") + parse_request(clients.request, "path");

    std::string interp_py = "/usr/bin/python3";
    std::string interp_js = "/usr/bin/node";
    if (get_extension(clients.request) == ".js")
    {
        cgi_response = execute_cgii(path, interp_js);
    }
    else
    {
        cgi_response = execute_cgii(path, interp_py);
    }
    set_headers_http(clients.response_string, "Content-Type", "text/html");
    headers(clients.response_string, clients.fd, "200");
    if (!cgi_response.empty())
    {
        int size = send(clients.fd, cgi_response.c_str(), cgi_response.size(), 0);
        if (size <= 0)
        {
            exit(1);
        }
        cgi_response.clear();
    }
}

std::string server::execute_cgii(std::string &script_path, std::string interpreter)
{
    int pipefd[2];
    std::string output;

    if (pipe(pipefd) == -1)
    {
        std::perror("pipe");
        return "";
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        std::perror("fork");
        return "";
    }

    if (pid == 0)
    {
        char *const argv[] = {(char *)interpreter.c_str(), (char *)script_path.c_str(), NULL};
        char *const envp[] = {NULL};

        close(pipefd[0]);              
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);              

        if (execve(interpreter.c_str(), argv, envp) == -1)
        {

            std::perror("execve");
            exit(1);
        }
    }
    else
    {
        close(pipefd[1]);
        char buffer[1024];
        ssize_t count;
        while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0)
        {
            output.append(buffer, count);
        }
        close(pipefd[0]);     
        waitpid(pid, NULL, 0);
    }
    return output;
}