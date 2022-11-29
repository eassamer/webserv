#include <unistd.h>
#include <iostream>


int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int  pid = fork();
	if (pid == -1)
	{
		std::cout << "error" << "\n";
		exit(0);
	}
	else
		execve("./cgi_tester", NULL, env);
}

// void		CgiHandler::_initEnv(Request &request, RequestConfig &config) {
// 	std::map<std::string, std::string>	headers = request.getHeaders();
// 	if (headers.find("Auth-Scheme") != headers.end() && headers["Auth-Scheme"] != "")
// 		this->_env["AUTH_TYPE"] = headers["Authorization"];

// 	this->_env["REDIRECT_STATUS"] = "200"; //Security needed to execute php-cgi
// 	this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
// 	this->_env["SCRIPT_NAME"] = config.getPath();
// 	this->_env["SCRIPT_FILENAME"] = config.getPath();
// 	this->_env["REQUEST_METHOD"] = request.getMethod();
// 	this->_env["CONTENT_LENGTH"] = to_string(this->_body.length());
// 	this->_env["CONTENT_TYPE"] = headers["Content-Type"];
// 	this->_env["PATH_INFO"] = request.getPath(); //might need some change, using config path/contentLocation
// 	this->_env["PATH_TRANSLATED"] = request.getPath(); //might need some change, using config path/contentLocation
// 	this->_env["QUERY_STRING"] = request.getQuery();
// 	this->_env["REMOTEaddr"] = to_string(config.getHostPort().host);
// 	this->_env["REMOTE_IDENT"] = headers["Authorization"];
// 	this->_env["REMOTE_USER"] = headers["Authorization"];
// 	this->_env["REQUEST_URI"] = request.getPath() + request.getQuery();
// 	if (headers.find("Hostname") != headers.end())
// 		this->_env["SERVER_NAME"] = headers["Hostname"];
// 	else
// 		this->_env["SERVER_NAME"] = this->_env["REMOTEaddr"];
// 	this->_env["SERVER_PORT"] = to_string(config.getHostPort().port);
// 	this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
// 	this->_env["SERVER_SOFTWARE"] = "Weebserv/1.0";

// 	this->_env.insert(config.getCgiParam().begin(), config.getCgiParam().end());
// }

// saveStdin = dup(STDIN_FILENO);
// 	saveStdout = dup(STDOUT_FILENO);

// 	FILE	*fIn = tmpfile();
// 	FILE	*fOut = tmpfile();
// 	long	fdIn = fileno(fIn);
// 	long	fdOut = fileno(fOut);
// 	int		ret = 1;

// 	write(fdIn, _body.c_str(), _body.size());
// 	lseek(fdIn, 0, SEEK_SET);

// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		std::cerr << RED << "Fork crashed." << RESET << std::endl;
// 		return ("Status: 500\r\n\r\n");
// 	}
// 	else if (!pid)
// 	{
// 		char * const * nll = NULL;

// 		dup2(fdIn, STDIN_FILENO);
// 		dup2(fdOut, STDOUT_FILENO);
// 		execve(scriptName.c_str(), nll, env);
// 		std::cerr << RED << "Execve crashed." << RESET << std::endl;
// 		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
// 	}
// 	else
// 	{
// 		char	buffer[CGI_BUFSIZE] = {0};

// 		waitpid(-1, NULL, 0);
// 		lseek(fdOut, 0, SEEK_SET);

// 		ret = 1;
// 		while (ret > 0)
// 		{
// 			memset(buffer, 0, CGI_BUFSIZE);
// 			ret = read(fdOut, buffer, CGI_BUFSIZE - 1);
// 			newBody += buffer;
// 		}
// 	}

// 	dup2(saveStdin, STDIN_FILENO);
// 	dup2(saveStdout, STDOUT_FILENO);
// 	fclose(fIn);
// 	fclose(fOut);
// 	close(fdIn);
// 	close(fdOut);
// 	close(saveStdin);
// 	close(saveStdout);

// 	for (size_t i = 0; env[i]; i++)
// 		delete[] env[i];
// 	delete[] env;

// 	if (!pid)
// 		exit(0);

// 	return (newBody);