/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <aer-razk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:21:21 by aer-razk          #+#    #+#             */
/*   Updated: 2022/11/18 17:18:14 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTES_HPP
#define ROUTES_HPP
#include "includes.hpp"

class location
{
    private:
        std::string    root;
        std::vector<std::string> allow_methods;
        std::string location_path;
    public:
        std::vector<std::string> cont_location;
        //orthodox canonical class methods
        location();
        ~location();
        //getters
        std::string    get_root(void);
		std::vector<std::string>	checknsearch(std::string var);
        std::string    get_index(void);
        int            get_response_code();
        std::string    get_method();
        bool        get_autoindex();
        std::string    get_cgi_path();
        std::string    get_cgi_extension();
        //setters
        void    set_location_path();
        void    set_allow_methods();
        void    set_root();
        void    set_();
};

#endif