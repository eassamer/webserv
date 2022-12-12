/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:21:08 by aer-razk          #+#    #+#             */
/*   Updated: 2022/12/12 17:32:25 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/client.hpp"

client::client(){
}

client::~client(){
	// if (this->cookie != NULL)
	// 	delete cookie;
}

void	client::clear()
{
	sbuffer.clear();
	path.clear();
	method.clear();
	Content_Length.clear();
	host_name.clear();
	query_string.clear();
	Content_Type.clear();
	remote_addr.clear();
	Authorization.clear();
	cookies.clear();
}

void	client::fill()
{
	path = sbuffer.substr(sbuffer.find("/"), sbuffer.substr(sbuffer.find("/"), sbuffer.length()).find(" "));
	method = sbuffer.substr(0, sbuffer.find(" "));
	path = this->convert_encodedForm(path);
	this->Content_Type = search_inData("Content-Type:");
	this->Content_Length = search_inData("Content-Length:");
	this->host_name = search_inData("Host:");
	this->query_string = search_inData("Query-String:");
	this->Authorization = search_inData("Authorization:");
	// this->cookies = search_inData("Cookie:");
	// if (this->cookies != "")
	// 	this->cookie = new client::Cookies(this->cookies);
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
	unsigned int x = sbuffer.find("\n", j); 
	return (sbuffer.substr(j + type.length() + 1, x - (j + type.length() + 1)));
}

std::string client::RandomString()
{
    char alpha[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    std::string result = "";
    for (int i = 0; i<26; i++)
        result = result + alpha[rand() % 26];
    return result;
}

std::string client::get_Content_Length(){
	return this->Content_Length;
}

std::string client::get_host_name(){
	return this->host_name;
}

std::string client::get_query_string(){
	return this->query_string;
}

std::string client::get_Content_Type(){
	return this->Content_Type;
}

std::string client::get_remote_addr(){
	return this->remote_addr;
}

std::string client::get_Authorization(){
	return this->Authorization;
}

//--------------------------------- Cookies -----------------------------------------//


// client::Cookies::Cookies(std::string cookie){
// 	readCookies(cookie);
// }

// client::Cookies::~Cookies(){
// }


// std::string client::Cookies::get_value(std::string key ,int i){
// 	unsigned int j;
// 	unsigned int k;
// 	j = key.find("=", i);
// 	if (j >= key.size())
// 		return "";
// 	k = key.find(";", j);
// 	if (k >= key.size())
// 		return (key.substr(j + 1, key.size() - 1));
// 	return (key.substr(j + 1, k - j - 1));
// }


// void client::Cookies::readCookies(std::string cookie){

// 	unsigned int j;
	
// 	j = cookie.find("=", 0);
// 	if (j >= cookie.size())
// 		return ;
// 	this->name = cookie.substr(0, j);
// 	this->value = get_value(cookie, 0);
// 	j += value.size();
// 	this->expire = get_value(cookie, j);
// 	j += expire.size();
// 	this->path = get_value(cookie, j);
// 	j += path.size();
// 	this->domain = get_value(cookie, j);
// }
