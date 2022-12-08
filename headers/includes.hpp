/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:02:13 by aer-razk          #+#    #+#             */
/*   Updated: 2022/12/08 12:18:52 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		INCLUDES_HPP
#define		INCLUDES_HPP
#include	<sys/types.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<string.h>
#include	<iostream>
#include	<unistd.h>
#include	<stdio.h>
#include	<string>
#include	<stdlib.h>
#include	<cstdlib>
#include	<iostream>
#include	<string>
#include	<fstream>
#include	<vector>
#include	<map>
#include	<sys/ioctl.h>
#include	<cstring>

class errors:public std::exception
{
	private:
		const char *	message;
	public:
		errors(const char * message):message(message){}
		virtual const char * what() const throw()
		{
			return (this->message);
		}
};

std::vector<std::string>	ft_split(std::string arg, char arc);

#endif