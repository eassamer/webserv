#include <iostream>
#include "./headers/client.hpp"
#include <fcntl.h>



int main(int ac, char **av)
{

	(void)ac;
	client ab;
	std::string data;
	char s[2];
	s[1] = 0;
	int fd = open("ibra.txt", O_RDWR);
	while (read(fd, s, 1))
		data += s[0];
	
	ab.sbuffer = data;
	std::cout << ab.search_inData("Content-Length:") << "\n";
	
}