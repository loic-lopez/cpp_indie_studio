##
## Makefile for Makefile in /home/jabbar_y/rendu/cpp_indie_studio
## 
## Made by Jabbari Yassir
## Login   <jabbar_y@epitech.net>
## 
## Started on  Mon May  1 12:13:34 2017 Jabbari Yassir
## Last update Thu Jun 15 13:21:20 2017 Jabbari Yassir
##

NAME            =       indie_studio

SRC             =	sources/main.cpp								\
			sources/Core.cpp								\
			sources/Encap.cpp								\
			sources/GameEngine/GameEngine.cpp  						\
			sources/GameEngine/GameEngineGeneration.cpp					\
			sources/GameEngine/GameEngineLogic.cpp						\
			sources/Events/EventReceiver.cpp 						\
			sources/Model/SplashScreen.cpp  						\
			sources/Model/MenuModel.cpp							\
			sources/Events/MenuEvent.cpp							\
			sources/Events/MenuEventSubMenu.cpp						\
			sources/Model/MenuInGameModel.cpp						\
			sources/Model/SetMenuModelMainOptions.cpp					\
			sources/Worms/Team.cpp								\
			sources/Worms/Worm.cpp								\
			sources/Worms/WormWithWeapon.cpp						\
			sources/Worms/WormWithoutWeapon.cpp						\
			sources/Worms/Uzi.cpp								\
			sources/Worms/Inventory.cpp							\
			sources/Worms/Shotgun.cpp							\
			sources/Worms/Surrender.cpp							\
			sources/Worms/HolyHandGrenade.cpp						\
			sources/Model/InventoryModel.cpp

ECHO		=	/bin/echo -e

DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[5;31m"

OBJ             =       $(SRC:.cpp=.o)

CXXFLAGS	+=	-I./irrKlang/include

CXXFLAGS	+=	-I./irrlicht/include -I./include/

CXXFLAGS	+=	-L./irrKlang/lib/linux64 -L./irrlicht/lib/Linux -Wall -Werror

CXXFLAGS	+=	-lIrrKlang -lIrrlicht -lGL -lGLU -lXrandr -lXxf86vm -lXext -lX11 -lXcursor -fexpensive-optimizations -faggressive-loop-optimizations

CXXFLAGS	+=	-lpthread

CXX             =       g++ -g3

RM              =       rm -f


all             :       $(NAME)

$(NAME)         :       $(OBJ)
			@$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) && \
			$(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(NAME) $(DEFAULT)  || \
			$(ECHO) $(RED) "[ERROR]" $(TEAL) $(NAME) $(DEFAULT)

clean           :
			@$(RM) $(OBJ) && \
			$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(OBJ) $(DEFAULT) || \
			$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(OBJ) $(DEFAULT)

fclean          :       clean
			@$(RM) $(NAME) && \
			$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(NAME) $(DEFAULT) || \
			$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(NAME) $(DEFAULT)

re              :       fclean all

install		:
			make clean -C  ./irrlicht/source/Irrlicht/
			make NDEBUG=1 -C ./irrlicht/source/Irrlicht/
			make clean -C  ./irrlicht/source/Irrlicht/

.cpp.o:
			@$(CC) $(CXXFLAGS) -c -o $@ $< && \
			$(ECHO) $(GREEN) "[OK]" $(TEAL) $< "--->" $@ $(DEFAULT) || \
			$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $^ $(DEFAULT)
