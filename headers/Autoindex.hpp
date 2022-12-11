#ifndef AUTOINDEX_HPP
# define AUTOINDEX_HPP





# include "includes.hpp"


class Autoindex
{
 	private:

        std::string     path_d;
        std::string     index;
        bool            checker;

    public:

        Autoindex(const std::string& path);
        ~Autoindex();

        std::string     getIndexPage() const;
        std::string     getDirectoryPath() const;
        bool            get_checker();

    private:

        void            generateIndexPage();
        std::string	    create_header();
        std::string	    footer();
		std::string		create_file_link(const unsigned char fileType, const std::string& fileName);
		std::string		getFileLink(const unsigned char fileType, std::string fileName);
		void			set_data(std::string* data);
};

#endif
