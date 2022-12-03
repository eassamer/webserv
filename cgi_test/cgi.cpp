/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:13:04 by bboulhan          #+#    #+#             */
/*   Updated: 2022/12/03 16:49:24 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"

Cgi::Cgi(){
	c_env = NULL;
}

Cgi::Cgi(server *serv, location *loc){
	this->loc = loc;
	this->serv = serv;
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


void Cgi::env_init()
{
	this->env["SERVER_PROTOCOL"] = "HTTP 1.1";
	this->env["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->env["SERVER_SOFTWARE"] = "webserv/1.0";
	this->env["SERVER_NAME"] = this->serv->get_server_name();
	this->env["SERVER_PORT"] = this->serv->get_port();
	this->env["REQUEST_METHOD"] = this->serv->us_method;
	this->env["PATH_INFO"] = this->loc->get_cgi_path();
	this->env["REQUEST_URI"] = this->loc->get_cgi_path();
	this->env["PATH_TRANSLATED"] = this->loc->get_cgi_path();
	this->env["SCRIPT_NAME"] = this->loc->get_cgi_path();
	this->env["CONTENT_LENGTH"] = "in header";
	this->env["REMOTE_ADDR"] = "ip adress of the user";
	this->env["CONTENT_TYPE"] = "in header of the request";
	// this->env["SERVER_ADDR"] = "";
	this->env["QUERY_STRING"] = "";
	this->env["AUTH_TYPE"] = "";
	//this->env["REMOTE_HOST"] = "";
	this->env["REMOTE_USER"] = "";
	this->env["REMOTE_IDENT"] = "";
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

void print_table(char **env)
{
	int  i = -1;
	while (env[++i])
	{
		printf("%s\n", env[i]);
	}
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
	// print_table(this->c_env);
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	
	fdIn = tmpfile();
	fdOut = tmpfile();
	fdCgi_in = fileno(fdIn);
	fdCgi_out = fileno(fdOut);
	pid = fork();
	if (pid == -1){
		std::cout << "Error in fork\n";
	}	
	else if (pid == 0)
	{
		dup2(fdCgi_in, STDIN_FILENO);
		dup2(fdCgi_out, STDOUT_FILENO);
		char **arg = new char *[3];
		arg[0] = strdup("/usr/local/bin/python3");
		arg[1] = strdup("./website/test.py");
		// arg[0] = strdup("/usr/bin/php");
		// arg[1] = strdup("./website/test.php");
		arg[2] = NULL;
		execve(arg[0], arg, this->c_env);
		std::cout << "Error\n";
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		waitpid(pid, NULL, 0);
		lseek(fdCgi_out, 0, SEEK_SET);
	}
	
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	// fclose(fdIn);
	// fclose(fdOut);
	close(fd_in);
	close(fd_out);
	// close(fdCgi_in);
	// close(fdCgi_out);
}

Cgi::~Cgi()
{
	// int i = -1;
	// while(this->c_env[++i])
	// 	delete this->c_env[i];
	// delete [] this->c_env;
}