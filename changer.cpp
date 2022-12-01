#include	<sys/types.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/socket.h>
#include	<string.h>
#include	<iostream>
#include	<unistd.h>
#include	<stdio.h>
#include	<string>
#include	<stdlib.h>
#include	<cstdlib>
#include	<iostream>
#include	<string>
#include	<fstream>
#include	<vector>
#include	<map>
#include	<cstring>

int main()
{
	std::ifstream file("do3afa2.conf");
	std::string line;
	std::string buffer;

	while (std::getline(file, line))
		buffer += line + "\n";
	file.close();
	std::string s = "listen 0.0.0.0:";
	int i = buffer.find("listen 0.0.0.0:") + s.length();
	srand(time(0));
	int port = rand() % 10000 + 1000;
	if (std::to_string(port).length() > 4)
		port = port % 10000;
	if (std::to_string(port).length() < 4)
		port = port + 1000;
	std::string port_str = std::to_string(port) + ";";
	buffer.replace(i, port_str.length(), port_str);
	system("rm -rf do3afa2.conf");
	std::ofstream file2("do3afa2.conf");
	file2 << buffer;
	file2.close();

}