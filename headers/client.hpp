/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:08:05 by aer-razk          #+#    #+#             */
/*   Updated: 2022/12/08 18:21:26 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CLIENT_HPP
#define		CLIENT_HPP
#include	"includes.hpp"

class client
{
	private:
		std::string Content_Length;
		std::string host_name;
		std::string query_string;
		std::string Content_Type;
	public:
		std::string method;
		std::string path;
		std::string sbuffer;
		client();
		
		void		clear();
		void		fill();
		std::string convert_encodedForm(std::string str);
		std::string search_inData(std::string type);
};
#endif