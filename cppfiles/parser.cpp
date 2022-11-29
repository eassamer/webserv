/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:15 by aer-razk          #+#    #+#             */
/*   Updated: 2022/11/29 14:31:31 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.hpp"
#include "../headers/includes.hpp"

void	parser::fillncheck()
{
	std::ifstream	fn(this->conf_path);
	if (!fn)//if the file in the arg dosen't exist!
		throw errors("do3afa2:Config file dosen't exist.");
	std::string line;
	while (getline(fn, line))
	{		
		if (line.find('#') > line.size())
			conf_content.push_back(line);
		else
			conf_content.push_back(line.substr(0, line.find('#')));
	}
	int i = -1;
	int j = 0;
	while (++i < conf_content.size())
	{
		if (count(conf_content[i].begin(), conf_content[i].end(), '{') == 1 
				&& count(conf_content[i].begin(), conf_content[i].end(), '}') == 0)//if there's only a '{' increament!
		{
			if (conf_content[i].length() == 1)//if in this line there's only a '{'
			{
				char echo[30000];
				std::sprintf(echo ,"do3afa2:%d:No tag before '}'.", i + 1);
				throw errors(echo);	
			}
			j++;
		}
		else if(count(conf_content[i].begin(), conf_content[i].end(), '}') == 1 
				&& count(conf_content[i].begin(), conf_content[i].end(), '{') == 0)//if there's only a '}' decreament!
			j--;
	}
	if (j != 0)//if there's an '{' without an '}' or the opposite!
		throw errors("do3afa2:Parse error near '{'.");
}

void	parser::set_conf_path(char *conf_path)
{
	if (conf_path == NULL)//if there's no argument in path!
		throw errors("do3afa2 : no config file.");
	std::string conf = conf_path;
	if (conf.length() < 6 || conf.substr(conf.length() - 5, conf.length()) != ".conf")//if the extension is different from '.conf'!
		throw errors("do3afa2:File extension '.conf' incorrect.");
	this->conf_path = conf_path;
}

void	parser::checkspaces()
{
	int i = -1;
	int j;
	while (++i < conf_content.size())
	{
		j = -1;
		while (conf_content[i][++j])
		{
			if (conf_content[i][j] == ' ' && conf_content[i][j + 1] == ' ')//if there's two or more consecutive space!
			{
				char echo[30000];
				std::sprintf(echo ,"do3afa2:%d:%d:Two or more consecutive spaces.", i + 1 , j);
				throw errors(echo);
			}
		}
		if (conf_content[i][0] == ' ')//if there's one or more spaces at the beginning!
		{
			char echo[30000];
			std::sprintf(echo ,"do3afa2:%d:%d:Extra space at the beginning.", i + 1 , 0);
			throw errors(echo);	
		}
		if (conf_content[i][conf_content[i].length() - 1] == ' ')//if there's one or more spaces at the end!
		{
			char echo[30000];
			std::sprintf(echo ,"do3afa2:%d:%lu:Extra space at the end.", i + 1 , conf_content[i].length() - 1);
			throw errors(echo);
		}
	}
}

void	parser::checktabs()
{
	int i = -1;
	int k = 0;
	
	while (++i < conf_content.size())
	{
		if (k == 0 && conf_content[i][conf_content[i].find("server")] && conf_content[i].length() > 8)//if there's no tab before a tab other than 'server'!
		{
			char echo[30000];
			std::sprintf(echo ,"do3afa2:%d:%d:Level 1 tag can only be 'server'.", i + 1 , 0);
			throw errors(echo);	
		}
		if (count(conf_content[i].begin(), conf_content[i].end(), '}') == 1)//if there's a closed bracket decreament 'k'!
			k--;
		int j = k - 1;
		while (++j < conf_content[i].length())
		{
			if (conf_content[i][j] == '\t')//if there's an extra tab in the middle/end of a tag!
			{
				char echo[30000];
				std::sprintf(echo ,"do3afa2:%d:%d:Extra tabs for indent level.", i + 1 , j);
				throw errors(echo);	
			}
		}
		j = k;
		while (--j >= 0)
		{
			if (j + 1 == k && conf_content[i][k - 1] == '\t'  && (conf_content[i][k] == '\t' || !conf_content[i][k]))//if there's an extra tab before tag!
			{
				char echo[30000];
				std::sprintf(echo ,"do3afa2:%d:%d:Extra tabs for indent level.", i + 1 , k);
				throw errors(echo);	
			}
			else if (j + 1 == k && conf_content[i][k] == ' ')//if there's a space before a tag!
			{
				char echo[30000];
				std::sprintf(echo ,"do3afa2:%d:%d:Extra space at the beginning.", i + 1 , k);
				throw errors(echo);		
			}
			if (conf_content[i][j] != '\t' && !conf_content[i].empty())//if there's a missing tab before tag!
			{
				char echo[30000];
				std::sprintf(echo ,"do3afa2:%d:%d:Missing tabs for indent level.", i + 1 , j);
				throw errors(echo);
			}
		}
		if (count(conf_content[i].begin(), conf_content[i].end(), '{') == 1)//if there's an open bracket increament 'k'!
			k++;
	}
}

parser::parser()
{
	
}

parser::~parser(){}


void parser::split_servers()
{
    int x = 0;
    int y = 0;
    int a = 0;
    for(int i = 0; i < conf_content.size(); i++)
    {
        if (conf_content[i] == "server {") // search server  inside config file
        {
            a++;
            x = i;
        }
        else if (conf_content[i] == "}") // search } inside config file
        {
            a++;
            y = i;
        }
        if (a == 2)
        {
            a = 0;
            server tmp;
            for (int j = x; j <= y;j++)
                tmp.cont_server.push_back(conf_content[j]);
            servers.push_back(tmp);
            tmp.cont_server.clear();
        }
    }
	for (int i = 0;i < servers.size();i++)
	{
		servers[i].split_locations();
	}
}

std::vector<std::string>	ft_split(std::string arg, char arc)
{
	std::vector<std::string> res;
	int i = arg.length() - 1;
	while (arg[i] == arc || arg[i] == '\t')
		i--;
	arg = arg.substr(0, i + 1);
	i = 0;
	while (arg[i] == arc || arg[i] == '\t')
		i++;
	arg = arg.substr(i, arg.length() - i);
	i = arg.find(arc);
	while (i < arg.length())
	{	
		res.push_back(arg.substr(0, i));
		while (arg[i] == arc)
			i++;
		arg = arg.substr(i, arg.length() - i);
		i = arg.find(arc);
	}
	res.push_back(arg);
	return (res);
}

void	parser::FD_JOIN(fd_set fds)
{
	for (int i = 0; i < FD_SETSIZE; i++)
		if (!FD_ISSET(i, &server_fds) && FD_ISSET(i, &fds))
			FD_SET(i, &server_fds);
}

void	parser::selectnaccept()
{
	FD_ZERO(&server_fds);
	while (1)
	{
		//SAVING THE FD SET THAT WILL BE SENT TO SELECT CUZ SELECT IS DISTRUCTIVE
		int i = -1;
		while (++i < servers.size())
		{
			FD_JOIN(servers[i].server_fds);//JOINING THE FD SETS OF ALL SERVERS
			servers[i].ready_fds = servers[i].server_fds;
		}
		ready_fds = server_fds;
		if (select(FD_SETSIZE, &ready_fds, NULL, NULL, NULL) < 0)
			throw errors("do3afa2:select:couldn't select from the fdset");
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			int j = -1;
			while (++j < servers.size())
			{
				if (FD_ISSET(i, &servers[j].ready_fds) && FD_ISSET(i, &ready_fds))
				{
					if (i == servers[j].s_fd)
					{
						std::cout << "\033[1;32mserver : connection request :" << servers[j].us_path << "|port:" << servers[j].get_port() << "\033[0m\n" ;
						servers[j].c_fd = accept(servers[j].s_fd, (struct sockaddr *)&servers[j].s_address, (socklen_t*)&servers[j].sl_address);
						if (servers[j].c_fd < 0)
							throw errors("do3afa2:accept: couldn't accept request on port");
						FD_SET(servers[j].c_fd, &servers[j].server_fds);
					}
					else
					{
						if (check_header(servers[j].c_fd));
						servers[j].port_accessed(servers[j].c_fd);
						servers[j].manageports(servers[j].c_fd, servers[j].us_path, servers[j].us_method);
						FD_CLR(i, &servers[j].server_fds);
						FD_CLR(i, &server_fds);
						std::cout << "\033[1;32mserver : connection closed\033[0m\n" ;
					}
					break ;
				}
			}
			if (j < servers.size())
				break ;
		}
	}
}

bool check_header(int fd)
{
	
}