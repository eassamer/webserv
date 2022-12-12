/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:13:04 by bboulhan          #+#    #+#             */
/*   Updated: 2022/12/12 16:07:12 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cgi.hpp"

Cgi::Cgi(){
	c_env = NULL;
}

Cgi::Cgi(server *serv, location *loc, client *cli){
	this->loc = loc;
	this->serv = serv;
	this->cli = cli;
	c_env = NULL;
}

Cgi::Cgi(const Cgi &copy)
{
	this->env = copy.env;
	this->exten = copy.exten;
	this->path = copy.path;
	int i = 0, j = -1;
	while (copy.c_env[i])
		i++;
	this->c_env = new char*[i];
	while (++j < i)
	{
		this->c_env[j] = new char[strlen(copy.c_env[j]) + 1];
		strcpy(this->c_env[j], copy.c_env[j]);
	}
	this->c_env[j] = NULL;
}

Cgi &Cgi::operator=(const Cgi &op)
{
	this->env = op.env;
	this->exten = op.exten;
	this->path = op.path;
	if (!op.c_env)
		return *this;
	delete [] c_env;
	int i = 0, j = -1;
	while (op.c_env[i])
		i++;
	this->c_env = new char*[i];
	while (++j < i)
	{
		this->c_env[j] = new char[strlen(op.c_env[j]) + 1];
		strcpy(this->c_env[j], op.c_env[j]);
	}
	this->c_env[j] = NULL;
	return *this;
}

//-------------------------------- Script Class -----------------------------------------// 

Cgi::Script::Script(){
	this->arg = NULL;
	this->name = "";
}

Cgi::Script::Script(std::string name) : name(name){
	this->arg = NULL;
}

void Cgi::Script::set_arg(std::string path, std::string args){
	this->arg = new char*[3];
	arg[0] = strdup(path.c_str());
	arg[1] = strdup(args.c_str());
	arg[2] = NULL;
}

char **Cgi::Script::get_arg() const{
	return this->arg;
}

std::string Cgi::Script::get_name() const{
	return this->name;
}

Cgi::Script::~Script(){
	if (this->arg != NULL)
	{
		int i = -1;
		while (this->arg[++i])
			delete this->arg[i];
		delete [] this->arg;
		this->arg = NULL;
	}
}

//-----------------------------------------------------------------------------------------//


void Cgi::set_script()
{
	Cgi::Script *py = new Cgi::Script("py");
	py->set_arg("/usr/local/bin/python3", "./website/test.py");	
	Cgi::Script *php = new Cgi::Script("php");
	php->set_arg("/usr/bin/php", "./website/test.php");
	Cgi::Script *bin = new Cgi::Script("bin");
	bin->set_arg(this->loc->get_cgi_path(), this->loc->get_cgi_path());
	this->tools.push_back(py);
	this->tools.push_back(php);
	this->tools.push_back(bin);
}


void Cgi::env_init()
{
	this->env["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->env["SERVER_SOFTWARE"] = "webserv/1.0";
	this->env["REDIRECT_STATUS"] = "200";
	this->env["SERVER_NAME"] = this->serv->get_server_name();
	this->env["SERVER_PORT"] = this->serv->get_port();
	this->env["REQUEST_METHOD"] = this->cli->method;
	this->env["PATH_INFO"] = this->loc->get_cgi_path();
	this->env["REQUEST_URI"] = this->loc->get_cgi_path();
	this->env["PATH_TRANSLATED"] = this->loc->get_cgi_path();
	this->env["SCRIPT_NAME"] = this->loc->get_cgi_path();
	this->env["REMOTE_HOST"] = this->cli->get_host_name();
	this->env["REMOTE_ADDR"] = this->cli->get_remote_addr();
	this->env["QUERY_STRING"] = this->cli->get_query_string();
	if (this->cli->method == "POST"){
		this->env["CONTENT_LENGTH"] = this->cli->get_Content_Length();
		this->env["CONTENT_TYPE"] = this->cli->get_Content_Type();
	}
	else{
		this->env["CONTENT_LENGTH"] = "";
		this->env["CONTENT_TYPE"] = "";
	}
	this->env["AUTH_TYPE"] = this->cli->get_Authorization();
	if (this->cli->get_Authorization() == ""){
	this->env["REMOTE_USER"] = this->cli->convert_encodedForm("REMOTE_USER");
	this->env["REMOTE_IDENT"] = this->cli->convert_encodedForm("REMOTE_IDENT");
	}
	else{
		this->env["REMOTE_USER"] = "";
		this->env["REMOTE_IDENT"] = "";
	}
}

void Cgi::convert_env()
{
	this->c_env = new char *[this->env.size() + 1];
	std::map<std::string , std::string>::iterator it = this->env.begin();
	std::map<std::string , std::string>::iterator ite = this->env.end();
	std::string tmp;
	int i = 0;
	while (it != ite)
	{
		tmp = it->first + "=" + it->second;
		this->c_env[i] = new char[tmp.size() + 1];
		strcpy(this->c_env[i++], (const char*)tmp.c_str());
		it++;
	}
	this->c_env[i] = NULL;
}

void Cgi::execute_cgi()
{
	int fd_in;
	int fd_out;
	int fdCgi_in;
	int fdCgi_out;
	pid_t pid;

	env_init();
	convert_env();
	set_script();
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	
	fdIn = tmpfile();
	fdOut = tmpfile();
	fdCgi_in = fileno(fdIn);
	fdCgi_out = fileno(fdOut);
	dup2(fdCgi_in, STDIN_FILENO);
	dup2(fdCgi_out, STDOUT_FILENO);
	pid = fork();
	if (pid == -1){
		std::cout << "Error in fork\n";
	}	
	else if (pid == 0)
	{
		std::vector<Cgi::Script*>::iterator it = tools.begin();
		std::vector<Cgi::Script*>::iterator ite = tools.end();
		while (it != ite){
			if (loc->get_cgi_extension() == (*it)->get_name())
				break;
			it++;
		}
		execve((*it)->get_arg()[0], (*it)->get_arg(), this->c_env);
		std::cout << "Error\n";
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		waitpid(-1, NULL, 0);
		lseek(fdCgi_out, 0, SEEK_SET);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

Cgi::~Cgi()
{
	int i = -1;
	while(this->c_env[++i])
		delete this->c_env[i];
	delete [] this->c_env;
	std::vector<Cgi::Script*>::iterator it = tools.begin();
	std::vector<Cgi::Script*>::iterator ite = tools.end();
	while (it != ite){
		delete *it;
		it++;
	}
}