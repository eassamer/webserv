/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:21:08 by aer-razk          #+#    #+#             */
/*   Updated: 2022/12/09 12:39:10 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/client.hpp"

client::client(){
}

void	client::clear()
{
	sbuffer.clear();
	path.clear();
	method.clear();
}

void	client::fill()
{
	path = sbuffer.substr(sbuffer.find("/"), sbuffer.substr(sbuffer.find("/"), sbuffer.length()).find(" "));
	method = sbuffer.substr(0, sbuffer.find(" "));
	path = this->convert_encodedForm(path);
	this->Content_Type = search_inData("Content-Type:");
	this->Content_Length = search_inData("Content-Length:");
	
}

std::string client::convert_encodedForm(std::string str)
{
	int i = 0;
	std::string tmp;
	std::string form;
	
	while (i < str.length())
	{
		if (str[i] == '%')
		{
			tmp = str[++i];
			tmp += str[++i];
			form += std::stoi(tmp, NULL, 16);		
			tmp.clear();
		}
		else
			form += str[i];
		i++;
	}
	return form;
}

std::string client::search_inData(std::string type)
{
	int  i = 0;
	unsigned int j = this->sbuffer.find(type, 0);
	if (j >= sbuffer.size())
		return "";
	std::string data;
	unsigned int x = sbuffer.find("\n", j); 
	data = sbuffer.substr(j, x - j);
	return data;
}

std::string client::get_Content_Length()
{
	return this->Content_Length;
}

std::string client::get_host_name()
{
	return this->host_name;
}

std::string client::get_query_string()
{
	return this->query_string;
}

std::string client::get_Content_Type()
{
	return this->Content_Type;
}

std::string client::get_remote_addr()
{
	return this->remote_addr;
}
