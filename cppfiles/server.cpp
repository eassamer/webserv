/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:21:15 by aer-razk          #+#    #+#             */
/*   Updated: 2022/12/05 14:44:39 by aer-razk         ###   ########.fr       */
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
		if (cont_server[i].find(var) == 1)
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
	for (int i = 0;i < index_v.size(); i++)
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
	if (listen(s_fd, 500) < 0)
		throw errors("do3afa2:listen:couldn't make the queue on the socket");
	//SETTING FD_SET
	FD_ZERO(&server_fds);
	FD_SET(s_fd, &server_fds);
	//std::cout << "\033[1;32m" << server_name << " : listening on port : 127.0.0.1:" << port << "\033[0m\n" ;
	std::cout << "\033[1;32m" << server_name << " : listening on port : " << IPADDRESS << ":" << port << "\033[0m\n" ; //gonna be deleted
}

int	server::check_request(std::string buff)
{
	int j = 0;
	std::vector<std::string> arr = ft_split(buff,'\n');
	int size = arr.size() - 1;
	std::vector<std::string> tmp;
	if (arr[0].length() > 1 && buff.find("GET") > buff.length() && buff.find("DELETE") > buff.length() && buff.find("POST") > buff.length())
		return (400);
	for (int i = 0; i < arr.size();i++)
	{
		tmp = ft_split(arr[i],' ');
		if (i == 0 && i != size)
			if ((tmp.size() != 3) || (tmp[2] != "HTTP/1.1\r" && tmp[2] != "HTTP/1.0\r"))
				return (400);
		if (i == size)
		{
			if (size == 0)
			{
				std::cout << buff << std::endl;
				return (0);
			}
			if (arr[size].length() == 1 && arr[size][0] == '\r')
				break;
		}
	}
	if (buff.find("POST") < buff.length() && buff.find("Content-Length:") > buff.length())
		return (411);
	return (1);
}

std::string server::read_request(int fd, int *j)
{
	char buffer[30000];
	int i;
	memset(buffer, 0, 30000);
	std::string buffer1, sbuffer;
	while ((i = read(fd, buffer, 29999)) > 0)
	{
		buffer1 = buffer;
		sbuffer.append(buffer, i);
		if (buffer1.find("Content-Type") > buffer1.length() && buffer[i - 1] == '\n')
			break ;
		(*j)++;
		if (*j > 1 && buffer[i - 1] == '\n' && buffer[i - 2] == '\r')
			break ;
	}
	return (sbuffer);
}

void	server::uploadfiles(std::string sbuffer)
{
	std::vector<std::string>    request_v;
	std::string boundray = "--" + sbuffer.substr(sbuffer.find("boundary=") + 9, sbuffer.substr(sbuffer.find("boundary=") + 9).find("\r\n") - 1);
	std::string files = sbuffer.substr(sbuffer.find(boundray));
	int k = 0;
	std::string counter;
	counter = files;
	while (k < counter.length())
	{
		k = counter.find(boundray) + boundray.length() + 1;
		if (k > counter.length())
			break ;
		request_v.push_back(counter.substr(k, counter.substr(k).find(boundray)));
		counter = counter.substr(k);
		std::cout << "hey\n";
	}
	k = -1;
	while (++k < request_v.size())
	{
		if (request_v[k].find("filename=") > request_v[k].length())
			request_v.erase(request_v.begin() + k);
		else
		{
			std::string filename = request_v[k].substr(request_v[k].find("filename=") + 10, request_v[k].substr(request_v[k].find("filename=") + 10).find("\r\n") - 1);
			std::ofstream fnr( "./uploads/" + filename);
			std::string content = request_v[k].substr(request_v[k].find("Content-Type:"));
			std::string content2 = content.substr(content.find("\r\n\r\n") + 4);
			fnr << content2;
			fnr.close();
		}
	}
}

int	server::port_accessed(int fd)
{
	int j = 0;
	int stat;
	static std::string sbuffer[FD_SETSIZE];
	sbuffer[fd] += read_request(fd, &j);
	//std::cout << sbuffer[fd] << std::endl;
	if ((stat = check_request(sbuffer[fd])) != 1)
	{
		if (stat != 0)
			sbuffer[fd].clear();
		return (stat);
	}
	if (j > 1)
		uploadfiles(sbuffer[fd]);
	us_path = sbuffer[fd].substr(sbuffer[fd].find("/"), sbuffer[fd].substr(sbuffer[fd].find("/"), sbuffer[fd].length()).find(" "));
	us_method = sbuffer[fd].substr(0, sbuffer[fd].find(" "));
	//std::cout << sbuffer[fd] << std::endl;
	sbuffer[fd].clear();
	return (1);
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

void	server::get_page(int c_fd ,std::string path, int status)
{
	std::map<int, std::string> status_map;
	status_map[200] = "200 OK";
	status_map[201] = "201 Created";
	status_map[202] = "202 Accepted";
	status_map[204] = "204 No Content";
	status_map[301] = "301 Moved Permanently";
	status_map[302] = "302 Found";
	status_map[304] = "304 Not Modified";
	status_map[400] = "400 Bad Request";
	status_map[401] = "401 Unauthorized";
	status_map[403] = "403 Forbidden";
	status_map[404] = "404 Not Found";
	status_map[405] = "405 Method Not Allowed";
	status_map[406] = "406 Not Acceptable";
	status_map[408] = "408 Request Timeout";
	status_map[409] = "409 Conflict";
	status_map[410] = "410 Gone";
	status_map[411] = "411 Length Required";
	status_map[413] = "413 Payload Too Large";
	status_map[414] = "414 URI Too Long";
	status_map[415] = "415 Unsupported Media Type";
	status_map[416] = "416 Range Not Satisfiable";
	status_map[417] = "417 Expectation Failed";
	status_map[418] = "418 I'm a teapot";
	status_map[421] = "421 Misdirected Request";
	status_map[422] = "422 Unprocessable Entity";
	status_map[423] = "423 Locked";
	status_map[424] = "424 Failed Dependency";
	status_map[426] = "426 Upgrade Required";
	status_map[428] = "428 Precondition Required";
	status_map[429] = "429 Too Many Requests";
	status_map[431] = "431 Request Header Fields Too Large";
	status_map[451] = "451 Unavailable For Legal Reasons";
	status_map[500] = "500 Internal Server Error";
	status_map[501] = "501 Not Implemented";
	status_map[502] = "502 Bad Gateway";
	status_map[503] = "503 Service Unavailable";
	status_map[504] = "504 Gateway Timeout";
	status_map[505] = "505 HTTP Version Not Supported";
	status_map[506] = "506 Variant Also Negotiates";
	status_map[507] = "507 Insufficient Storage";
	status_map[508] = "508 Loop Detected";
	status_map[510] = "510 Not Extended";
	status_map[511] = "511 Network Authentication Required";

	std::string http = "HTTP/1.1 " + status_map[status] + "\n";
	std::string t_content = "Content-Type: text/html\n";
	std::string l_content = "Content-Length:";
	std::string text = read_text(path);

	l_content += std::to_string(text.length()) + "\n\n";
	std::string everything = http + t_content + l_content + text;
	write(c_fd , everything.c_str() , everything.length());
	std::cout << "\033[1;33m" << server_name << " : response [status : " + status_map[status] + "]\033[0m\n" ;
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
		if (path_accessed == "/" || path_accessed == "")
			get_page(c_fd, get_root() + "/" + get_index(), 200);
		else
		{
			int i = -1;
			while (++i < locations.size())
				if (locations[i].get_location_path() == path_accessed)
					break ;
			if (i < locations.size())
				get_page(c_fd, locations[i].get_root() + "/" + locations[i].get_index(), 200);
			else
				get_page(c_fd, get_error_page(404), 404);
		}
	}
	else
		get_page(c_fd, get_error_page(405), 405);
}
