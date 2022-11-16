/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:21:15 by aer-razk          #+#    #+#             */
/*   Updated: 2022/11/14 16:37:38 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/server.hpp"

server::server()
{
	
}

server::~server()
{}

void    server::split_locations()
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
    lst["\tindex "] = 2;
    std::vector<std::string> splits;
    for(int i = 0; i < cont_server.size(); i++)
    {
        if (cont_server[i].find(var) < cont_server[i].length())
        {
            splits = ft_split(cont_server[i], ' ');
            if (splits.size() > lst[var] + 1 && splits[splits.size() - 1] != ";")
            {
				char echo[30000];
				std::sprintf(echo ,"do3afa2:%d:too many arguments.", i + 1);
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
    this->server_name = server_n[0];
}

void server::set_root()
{
    std::vector<std::string> root_p = this->checknsearch("root");
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
        throw errors("do3afa2:bad argument autoindex!");
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
    this->client_body_limit = atoi(client_body_limit_v[0].c_str());
}

void server::set_index()
{
    std::vector<std::string>    index_v = this->checknsearch("\tindex ");

    for (int i = 0;i <index_v.size(); i++)
    {
        if (index_v[i].length() > index_v[i].find(".html"))
            this->index.push_back(index_v[i]);
        else
            throw errors("do3afa2: bad file extension in index");
    }
}

void server::set_error_page()
{
    std::vector<std::string>    error_page_v = this->checknsearch("error_page");

    for (int i = 0;i < error_page_v[0].size();i++)
    {
        if (!isnumber(error_page_v[0][i]))
            throw errors("do3afa2:error page number is wrong");
    }
    this->error_page.insert(std::pair<int,std::string>(std::stoi(error_page_v[0]),error_page_v[1]));
}