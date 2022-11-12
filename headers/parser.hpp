/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:01:22 by aer-razk          #+#    #+#             */
/*   Updated: 2022/11/12 14:29:58 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP
#include "includes.hpp"
#include "server.hpp"
class server;

class parser
{
	private:
		std::vector<server>			servers;
		std::string					conf_path;
		std::vector<std::string>	conf_content;
	public:
		//orthodox canonical class methods
		parser();
		~parser();
		parser(std::string conf_path);
		parser(parser const & src);
		parser & operator=(parser const & src);
		//getters
		std::vector<server>	get_servers();
		std::string			get_conf_path();
		std::string			get_conf_content();
		//setters
		void	set_servers(std::vector<server> servers);
		void	set_conf_content(std::string conf_content);
		//other methods
		void	set_conf_path(char *conf_path);
		void	fillncheck();
};

#endif
