/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:10:15 by aer-razk          #+#    #+#             */
/*   Updated: 2022/11/12 14:36:09 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.hpp"

void parser::fillncheck()
{
	std::ifstream	fn(this->conf_path);
	if (!fn)
		throw errors("do3afa2 : config file dosen't exist.");
	std::string line;
	while (getline(fn, line))
		conf_content.push_back(line);
	int i = -1;
	int j = 0;
	while (++i < conf_content.size())
	{
		if (count(conf_content[i].begin(),conf_content[i].end(),'{') == 1)
			j++;
		else if(count(conf_content[i].begin(),conf_content[i].end(),'}') == 1)
			j--;
	}
	if (j != 0)
		throw errors("do3afa2: parse error near '{'.");
}

void parser::set_conf_path(char *conf_path)
{
	if (conf_path == NULL)
		throw errors("do3afa2 : no config file.");
	std::string conf = conf_path;
	if (conf.length() < 6 || conf.substr(conf.length() - 5, conf.length()) != ".conf")
		throw errors("do3afa2 : file extension '.conf' incorrect.");
	this->conf_path = conf_path;
}

parser::parser()
{
	
}

parser::~parser(){}