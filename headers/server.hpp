/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:10:58 by aer-razk          #+#    #+#             */
/*   Updated: 2022/11/19 10:45:37 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP
#include "includes.hpp"
#include "location.hpp"
#include "parser.hpp"

class location;

class server {
	private:
		int							port;
		std::vector<std::string>	index;
		std::string					server_name;
		std::map<int,std::string>	error_page;
		std::string					root;
		bool						autoindex;
		int							client_body_limit;
		std::string					path;
		std::vector<std::string>	allow_methods;
		int							s_fd;
		int							c_fd;
		fd_set						server_fds;
		fd_set						ready_fds;
		struct sockaddr_in 			s_address;
		int 						sl_address;
	public:
		std::vector<location>		locations;
		std::vector<std::string>	cont_server;
		//orthodox canonical class methods
		server();
		~server();
		//getters
		int						get_port();
		std::string				get_server_name();
		std::string				get_error_page(int status);
		std::string				get_root();
		bool					get_autoindex();
		int						get_client_body_limit();
		std::string				get_path();
		std::string				get_index();
		std::vector<location>	get_locations();
		//setters
		void	set_port();
		void	set_server_name();
		void	set_root();
		void	set_autoindex();
		void	set_client_body_limit();
		void	set_allow_methods();
		void	set_index();
		void	set_error_page();
		//methods
		std::vector<std::string>	checknsearch(std::string var);
		bool						check_brackets(std::string config);
		std::string					port_accessed(int fd);
		std::string					search_file(std::string path);
		void						get_page(int c_fd ,std::string path);
		std::string					read_text(std::string path);
		//parsers
		void	split_locations(); // split locations and store it inside locations
		//setup server
		void	manageports(int c_fd, std::string path_accessed);
		void	socketnmemset();
		void	bindnlisten();
		void	selectnaccept();
};

#endif
