##
## Makefile for Makefile in /home/jabbar_y/rendu/cpp_indie_studio
## 
## Made by Jabbari Yassir
## Login   <jabbar_y@epitech.net>
## 
## Started on  Mon May  1 12:13:34 2017 Jabbari Yassir
## Last update Tue May  2 11:43:40 2017 Stanislas Deneubourg
##

NAME            =       indie_studio

SRC             =       sources/main.cpp

OBJ             =       $(SRC:.cpp=.o)

CXXFLAGS	+=	-I./irrlicht/include -L./irrlicht/lib/Linux -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor

CXXFLAGS	+=	-lpthread -lboost_system

CXX             =       g++

RM              =       rm -f


all             :       $(NAME)

$(NAME)         :       $(OBJ)
			$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean           :
			$(RM) $(OBJ)

fclean          :       clean
			$(RM) $(NAME)

re              :       fclean all

install		:
			make -C ./irrlicht/source/Irrlicht/
