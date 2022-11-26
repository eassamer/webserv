	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   server.cpp                                         :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2022/11/08 12:21:15 by aer-razk          #+#    #+#             */
	/*   Updated: 2022/11/18 15:50:10 by aer-razk         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "../headers/server.hpp"

server::server()
{
}

server::~server()
{}

void	server::split_locations()
{
	int x = 0;
	int y = 0;
	int a = 0;
	for (int i = 0; i < cont_server.size(); i++) 
	{
		if (cont_server[i].length() > cont_server[i].find("location")) // search location inside server content
		{
			a++;
			x = i;
		}
		else if (cont_server[i].length() > cont_server[i].find("}")) // search } inside server content
		{
			a++;
			y = i;
		}
		if (a == 2) // when he find the location and } hes gonna create a new location a store data
		{
			a = 0;
			location tmp;
			for (int j = x; j <= y; j++)
				tmp.cont_location.push_back(cont_server[j]);
			locations.push_back(tmp);
			tmp.cont_location.clear();
		}
	}
}

std::vector<std::string>    server::checknsearch(std::string var)
{
	std::map<std::string, int> lst;
	lst["server_name"] = 1;
	lst["listen"] = 1;
	lst["root"] = 1;
	lst["allow_methods"] = 3;
	lst["autoindex"] = 1;
	lst["client_body_limit"] = 1;
	lst["error_page"] = 2;
	lst["index"] = 1;
	std::vector<std::string> splits;
	for(int i = 0; i < cont_server.size(); i++)
	{
		if (cont_server[i].find(var) < cont_server[i].length() && cont_server[i].find(var) == 1)
		{
			splits = ft_split(cont_server[i], ' ');
			if ((splits.size() > lst[var] + 1 && splits[splits.size() - 1] != ";") || (splits.size() == 1))
			{
				char echo[30000];
				std::sprintf(echo ,"do3afa2:%d:arguments error.", i + 1);
				throw errors(echo);
			}
			break ;
		}
	}
	if (splits.size() == 0)
	{
		char echo[30000];
		std::sprintf(echo ,"do3afa2:%s:lack of tag.", var.c_str());
		throw errors(echo);
	}
	if (splits[splits.size() - 1][splits[splits.size() - 1].length() - 1] != ';')
		throw errors("do3afa2a:tag is not closed 'missing ;'");     
	splits[splits.size() - 1] = splits[splits.size() - 1].substr(0, splits[splits.size() - 1].length() - 1);
	splits.erase(splits.begin());
	return splits;
}

void    server::set_port()
{
	std::vector<std::string> cport = this->checknsearch("listen");
	std::vector<std::string> splited = ft_split(cport[0], ':');
	if (splited.size() != 2)
		throw errors("do3afa2:port error in config file.");
	int i = -1;
	while (++i < splited[1].length())
		if (!isnumber(splited[1][i]))
			throw errors("do3afa2:port not number in config file.");
	this->port = std::stoi(splited[1]);
}

void server::set_server_name()
{
	std::vector<std::string> server_n = this->checknsearch("server_name");
	if (server_n[0].empty() || server_n.size() > 1)
		throw errors("do3afa2:error in server name.");
	this->server_name = server_n[0];
}

void server::set_root()
{
	std::vector<std::string> root_p = this->checknsearch("root");
	if (root_p[0].empty() || root_p.size() > 1)
		throw errors("do3afa2:error in server name.");
	this->root = root_p[0];
}

void server::set_autoindex()
{
	std::vector<std::string> autoindex_v = this->checknsearch("autoindex");
	if (autoindex_v[0] == "on")
		this->autoindex = true;
	else if (autoindex_v[0] == "off")
		this->autoindex = false;
	else
		throw errors("do3afa2:bad argument autoindex must be 'on/off'");
}

void server::set_allow_methods()
{
	std::vector<std::string>    allow_methods_v = this->checknsearch("allow_methods");

	for (int i = 0; i < allow_methods_v.size();i++)
	{
		if (allow_methods_v[i] == "GET")
			this->allow_methods.push_back("GET");
		else if (allow_methods_v[i] == "POST")
			this->allow_methods.push_back("POST");
		else if (allow_methods_v[i] == "DELETE")
			this->allow_methods.push_back("DELETE");
		else
			throw errors("do3afa2:allow_methods bad arguments!");
	}
}

void server::set_client_body_limit()
{
	std::vector<std::string>    client_body_limit_v = this->checknsearch("client_body_limit");
	for (int i = 0;i < client_body_limit_v[0].size();i++)
	{
		if (!isnumber(client_body_limit_v[0][i]))
			throw errors("do3afa2:client_body_limit number is wrong");
	}
	if (atoi(client_body_limit_v[0].c_str()) == 0)
		throw (errors("do3afa2:error in client body limit."));
	this->client_body_limit = atoi(client_body_limit_v[0].c_str());
}

void server::set_index()
{
	std::vector<std::string>    index_v = this->checknsearch("index");
	for (int i = 0;i <index_v.size(); i++)
	{
		if (index_v[i].length() > 5 &&  index_v[i].find(".html") == index_v[i].length() - 5)
			this->index.push_back(index_v[i]);
		else
			throw errors("do3afa2: bad file extension in index");
	}
}

void server::set_error_page()
{
	std::vector<std::string>    error_page_v = this->checknsearch("error_page");

	this->error_page.insert(std::pair<int,std::string>(405, "./default/405.html"));
	if (error_page_v[0].size() == 0)
		throw errors("do3afa2:error page number is wrong");
	for (int i = 0;i < error_page_v[0].size();i++)
	{
		if (!isnumber(error_page_v[0][i]))
			throw errors("do3afa2:error page number is wrong");
	}
	if (std::stoi(error_page_v[0]) > 600 || std::stoi(error_page_v[0]) < 100)
		throw errors("do3afa2:error status code invalid");
	this->error_page.insert(std::pair<int,std::string>(std::stoi(error_page_v[0]),error_page_v[1]));
	if (error_page[std::stoi(error_page_v[0])].length() < 6 ||  error_page[std::stoi(error_page_v[0])].find(".html") != error_page[std::stoi(error_page_v[0])].length() - 5)
		throw errors("do3afa2:error page file extension is invalid");
	std::ifstream	fn(error_page[std::stoi(error_page_v[0])]);
	if (!fn)//if the file in the arg dosen't exist!
		throw errors("do3afa2:error page path invalid.");
}

void	server::socketnmemset()
{
	sl_address = sizeof(s_address);
	//INITILATION A INTERNET SOCKET WITH 'AF_INET' DOMAINE THAT WILL USE TCP PROTOCOL 'SOCK_STREAM'
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (s_fd < 0)
		throw errors("do3afa2:socket:socket couldn't be set");
	//SETTING PORT AND IPADDRESS IN SOCKADDR_IN STRUCT
	memset((char *)&s_address, 0, sizeof(s_address)); 
	s_address.sin_family = AF_INET;
	s_address.sin_addr.s_addr = htonl(INADDR_ANY);
	s_address.sin_port = htons(port);
}

void	server::bindnlisten()
{
	if (bind(s_fd, (struct sockaddr *)&s_address, sizeof(s_address)) < 0)
		throw errors("do3afa2:port is already taken.");
	//MARKING SOCKET AS PASSIVE 'ABLE TO ACCEPTE INCOMING CONNECTIONS' AND MAKING A QUEUE OF CONNECTION REQUESTS TO BE EXTRACTED USING ACCEPT
	if (listen(s_fd, 100) < 0)
		throw errors("do3afa2:listen:couldn't make the queue on the socket");
	//SETTING FD_SET
	FD_ZERO(&server_fds);
	FD_SET(s_fd, &server_fds);
	std::cout << "\033[1;32m" << server_name << " listening on port : " << port << "\033[0m\n" ;
}



void	server::port_accessed(int fd)
{
	char buffer[30000];
	std::cout << read(fd, buffer, 30000) << std::endl;
	std::string sbuffer = buffer;
	std::cout << buffer << std::endl;
	us_path = sbuffer.substr(sbuffer.find("/"), sbuffer.substr(sbuffer.find("/"), sbuffer.length()).find(" "));
	us_method = sbuffer.substr(0, sbuffer.find(" "));
}

int		server::get_port()
{
	return port;
}

std::string	server::get_server_name()
{
	return server_name;
}

std::string	server::get_error_page(int status)
{
	std::cout << "\033[1;33mserver : response [status : " << status << " KO]\033[0m\n" ;
	return error_page[status];
}

std::string server::get_index()
{
	return index[0];
}

std::string	server::get_root()
{
	return root;
}

bool	server::get_autoindex()
{
	return autoindex;
}

int		server::get_client_body_limit()
{
	return client_body_limit;
}

std::string server::get_path()
{
	return path;
}

void	server::get_page(int c_fd ,std::string path)
{
	std::string http = "HTTP/1.1 200 OK\n";
	std::string t_content = "Content-Type: text/html\n";
	std::string l_content = "Content-Length:";
	std::string text = read_text(path);

	l_content += std::to_string(text.length()) + "\n\n";
	std::string everything = http + t_content + l_content + text;
	write(c_fd , everything.c_str() , everything.length());
}

std::string server::read_text(std::string path)
{
	std::string text;
	std::string buffer;
	std::ifstream	fn(path);
	if (!fn)
		throw errors("do3afa2:invalid path from config file.");
	while(getline(fn, buffer))
		text += buffer;
	return (text);
}

void	server::manageports(int c_fd, std::string path_accessed, std::string method)
{
	int i = -1;
	while (++i < allow_methods.size())
		if (allow_methods[i] == method)
			break ;
	if (i < allow_methods.size())
	{
		if (path_accessed == "/")
		{
			get_page(c_fd, get_root() + "/" + get_index());
			std::cout << "\033[1;33mserver : response [status : 200 OK]\033[0m\n" ;
		}
		else
		{
			int i = -1;
			while (++i < locations.size())
				if (locations[i].get_location_path() == path_accessed)
					break ;
			if (i < locations.size())
				get_page(c_fd, root + locations[i].get_location_path() + "/" + locations[i].get_root());
			else
				get_page(c_fd, get_error_page(404));
		}
	}
	else
		get_page(c_fd, get_error_page(405));
}