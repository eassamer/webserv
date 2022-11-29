/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:13:02 by bboulhan          #+#    #+#             */
/*   Updated: 2022/11/29 14:20:49 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

#include <iostream>
#include <map>
#include "../headers/server.hpp"
#include "../headers/location.hpp"

class Cgi{
	private:
		std::map<std::string , std::string> env;
		std::string exten;
		std::string path;
		char **c_env;
		server serv;
		location loc;
	public:
		Cgi();
		Cgi(const server &serv, const location &loc);
		Cgi(const Cgi &copy);
		Cgi &operator=(const Cgi &op);
		~Cgi();
		
		char **get_c_env()const;
		

		void execute_cgi();
		void env_init();
		void convert_env();	
		
};




#endif