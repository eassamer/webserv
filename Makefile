NAME = webserv

CFLAGS =  -std=c++98

CC = c++

GREEN=\033[0;32m

NC=\033[0m

FILES = cppfiles/main.cpp  cppfiles/server.cpp  cppfiles/location.cpp cppfiles/parser.cpp \
		cgi_test/cgi.cpp \

HEADERS = headers/*.hpp

OBJS = $(FILES:.cpp=.o)

dir:
	@mkdir fobjs uploads

all: $(NAME)
	@echo "$(GREEN)✔$(NC) Compiled."
	@mv cppfiles/*.o fobjs

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean : 
	@rm -f $(NAME)

fclean : clean
	@rm -f fobjs/*.o
	@rm -f cppfiles/*.o
	@rm -rf ./uploads/*
	@echo "$(GREEN)✔$(NC) Cleaned."

run :
	@rm -rf ./uploads/*
	@./default/replacer
	@make re && ./$(NAME) $(arg)

re : fclean all
