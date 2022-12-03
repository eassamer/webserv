#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main(int ac, char **av, char **env)
{
	// char s[500];
	// getcwd(s, 100);
	(void)ac;
	(void)av;
	int saveIN;
	int saveOUT;


	FILE *fdIN = tmpfile();
	FILE *fdOUT = fopen("file", "w+");
	int fdin = fileno(fdIN);
	int fdout = fileno(fdOUT);
	// std::cout << fdin << "\t" << fdout << "\n";
	saveIN = dup(STDIN_FILENO);
	saveOUT = dup(STDOUT_FILENO);
	// std::string s = "python3 /Users/bboulhan/Desktop/webserver/website/test.py";
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	pid_t pid;
	pid = fork();
	if (pid ==  -1)
	{
		std::cout << "error\n";
	}
	else if (pid == 0)
	{
		// std::string a1 = "/usr/local/bin/python3";
		// std::string a2 = "./website/test.py";
		char **arg = new char *[3];
		arg[0] = strdup("/usr/bin/php");
		arg[1] = strdup("./website/test.php");
		// arg[0] = new char[a1.size() + 1];
		// arg[1] = new char [a2.size() + 1];
		arg[2] = NULL;
		// strcpy(arg[0], a1.c_str());
		// strcpy(arg[1], a2.c_str());
		execve(arg[0], arg , NULL);
		// system("python3 ./website/test.py");
		// execve("./cc", NULL, env);
		// system("./cc");
		std::cout << "error\n";
	}
	else
	{
		std::cout << "pp\n";
		waitpid(pid, NULL, 0);
	}
	dup2(saveIN, STDIN_FILENO);
	dup2(saveOUT, STDOUT_FILENO);
	int fd = open("file", O_RDWR);
	std::string p;
	char ss[2];
	ss[1] = 0;
	int j = 1;
	//std::cout << fdout << "\n";
	while (j)
	{	
		j = read(fd, ss, 1);
		p += ss[0];

	}
	std::cout << "ibra\n";
	std::cout << p << "\n";
}