/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:10:58 by aer-razk          #+#    #+#             */
/*   Updated: 2022/12/12 12:05:34 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		SERVER_HPP
#define		SERVER_HPP
#include	"includes.hpp"
#include	"location.hpp"
#include	"parser.hpp"
#include	"client.hpp"
#include 	"cgi.hpp"
#include "Autoindex.hpp"

class Autoindex;
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
		//user request
	public:
		std::string					IPADDRESS;//gonna be deleted
		std::vector<location>		locations;
		std::vector<std::string>	cont_server;
		int							s_fd;
		std::vector<int>			c_fd;
		fd_set						server_fds;
		fd_set						ready_fds;
		struct sockaddr_in 			s_address;
		int 						sl_address;
		client 						clients[FD_SETSIZE];
		//orthodox canonical class methods
		server();
		~server();
		//getters
		int							get_port();
		std::string					get_server_name();
		std::string					get_error_page(int status);
		std::string					get_root();
		bool						get_autoindex();
		int							get_client_body_limit();
		std::string					get_path();
		std::string					getus_path();
		std::string					getus_method();
		std::string					get_index();
		std::vector<location>		get_locations();
		//setters
		void						set_port();
		void						set_server_name();
		void						setus_path(std::string path);
		void						setus_method(std::string method);
		void						set_root();
		void						set_autoindex();
		void						set_client_body_limit();
		void						set_allow_methods();
		void						set_index();
		void						set_error_page();
		//methods
		std::vector<std::string>	checknsearch(std::string var);
		bool						check_brackets(std::string config);
		int							port_accessed(int fd);
		void						check_paths();
		std::string					search_file(std::string path);
		void						get_page(int c_fd, std::string path, int status);
		void 						get_page_cgi(int c_fd ,std::string path, location &local, client &client);
		std::string					read_text(std::string path);
		//parse	
		void						split_locations(); // split locations and store it inside locations
		//setup server
		void						manageports(int c_fd, std::string path_accessed, std::string method);
		void						socketnmemset();
		void						bindnlisten();
		bool 						check_header(int fd);
		std::string					read_request(int fd, int *j);
		int							check_request(std::string &buff);
		void 						uploadfiles(std::string sbuffer);
		void						get_page_autoindex(int c_fd, std::string path);
};
#endif
