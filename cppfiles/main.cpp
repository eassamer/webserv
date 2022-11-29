/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:10:56 by aer-razk          #+#    #+#             */
/*   Updated: 2022/11/29 14:16:52 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.hpp"
#include "../cgi_test/cgi.hpp"

int main(int arc, char **arv)
{
	try
	{
		parser mehdi;
		mehdi.set_conf_path(arv[1]);
		mehdi.fillncheck();
		mehdi.checkspaces();
		mehdi.checktabs();
		mehdi.split_servers();
		int i = -1;
		while (++i < mehdi.servers.size())
		{
			mehdi.servers[i].set_port();
			mehdi.servers[i].set_server_name();
			mehdi.servers[i].set_root();
			mehdi.servers[i].set_allow_methods();
			mehdi.servers[i].set_client_body_limit();
			mehdi.servers[i].set_autoindex();
			mehdi.servers[i].set_index();
			mehdi.servers[i].set_error_page();
			int j = -1;
			while (++j < mehdi.servers[i].locations.size())
			{
				mehdi.servers[i].locations[j].set_root();
				mehdi.servers[i].locations[j].set_allow_methods();
				mehdi.servers[i].locations[j].set_index();
				mehdi.servers[i].locations[j].set_location_path();
				Cgi ibra(mehdi.servers[i], mehdi.servers[i].locations[i]);
				ibra.execute_cgi();
			}
			mehdi.servers[i].socketnmemset();
			mehdi.servers[i].bindnlisten();
		}
		mehdi.selectnaccept();
	}
	catch(std::exception &e)
	{
		std::cout << e.what();
	}
}
