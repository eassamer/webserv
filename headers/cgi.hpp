/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:13:02 by bboulhan          #+#    #+#             */
/*   Updated: 2022/12/05 16:58:07 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

#include <iostream>
#include <map>
#include "server.hpp"
#include "location.hpp"

class server;

class Cgi{
	private:
		std::map<std::string , std::string> env;
		std::string exten;
		std::string path;
		char **c_env;
		location *loc;
		server *serv;
		
	public:
		class Script{
			private:
				std::string name;
				char **arg;
			public:
				Script();
				~Script();
				Script(std::string name);
				
				char **get_arg() const;
				void set_arg(std::string path, std::string args);
				std::string get_name() const;
		};
		
		Cgi();
		Cgi(server *serv, location *loc);
		Cgi(const Cgi &copy);
		Cgi &operator=(const Cgi &op);
		~Cgi();
		
		
		std::vector<Cgi::Script* > tools;
		FILE *fdIn;
		FILE *fdOut;

		char **get_c_env()const;
		void set_script();
		void execute_cgi();
		void env_init();
		void convert_env();	
		
};




#endif