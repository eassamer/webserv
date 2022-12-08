/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:08:05 by aer-razk          #+#    #+#             */
/*   Updated: 2022/12/08 12:26:00 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CLIENT_HPP
#define		CLIENT_HPP
#include	"includes.hpp"

class client
{
	//private:
	public:
		std::string method;
		std::string path;
		std::string sbuffer;
		void		clear();
		void		fill();
};
#endif