##
## Makefile for Makefile in /home/jabbar_y/rendu/cpp_indie_studio
## 
## Made by Jabbari Yassir
## Login   <jabbar_y@epitech.net>
## 
## Started on  Mon May  1 12:13:34 2017 Jabbari Yassir
## Last update Fri May  5 18:15:47 2017 Stanislas Deneubourg
##

NAME            =       indie_studio

SRC             =       sources/main.cpp		\
			sources/Core.cpp		\
			sources/Encap.cpp		\
			sources/GameEngine.cpp  	\
			sources/EventReceiver.cpp 	\
			sources/SplashScreen.cpp  	\
			sources/MenuModel.cpp		\
			sources/MenuEventModel.cpp	\


OBJ             =       $(SRC:.cpp=.o)

CXXFLAGS	+=	 -I./bullet/include/bullet -I./irrlicht/include -I./include/ -L./irrlicht/lib/Linux -L./bullet/lib -Wall -Werror

CXXFLAGS	+=	-lIrrlicht -lGL -lGLU -lXrandr -lXxf86vm -lXext -lX11 -lXcursor -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath

CXXFLAGS	+=

CXX             =       g++ -g

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
