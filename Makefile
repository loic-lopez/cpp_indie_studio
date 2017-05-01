##
## Makefile for Makefile in /home/jabbar_y/rendu/cpp_indie_studio
## 
## Made by Jabbari Yassir
## Login   <jabbar_y@epitech.net>
## 
## Started on  Mon May  1 12:13:34 2017 Jabbari Yassir
## Last update Mon May  1 12:19:02 2017 Jabbari Yassir
##

NAME            =       indie_studio

SRC             =       sources/main.cpp		\
			sources/MinimalOgre.cpp

OBJ             =       $(SRC:.cpp=.o)

CXXFLAGS        +=      -Iinclude
CXXFLAGS        +=      -W -Wall -Wextra -Werror

LDFLAGS         +=      -lpthread

CXX             =       g++
RM              =       rm -f


all             :       $(NAME)

$(NAME)         :       $(OBJ)
			$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean           :
			$(RM) $(OBJ)

fclean          :       clean
			$(RM) $(NAME)

re              :       fclean all
