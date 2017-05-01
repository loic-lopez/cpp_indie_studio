##
## Makefile for Makefile in /home/jabbar_y/rendu/cpp_indie_studio
## 
## Made by Jabbari Yassir
## Login   <jabbar_y@epitech.net>
## 
## Started on  Mon May  1 12:13:34 2017 Jabbari Yassir
## Last update Mon May  1 14:53:09 2017 Jabbari Yassir
##

NAME            =       indie_studio

SRC             =       sources/main.cpp
OBJ             =       $(SRC:.cpp=.o)

CXXFLAGS	+=	-L./Ogre3Dlibrary/lib -L./OISlibrary/lib64 -L./SDL/lib64 -lOgreOverlay -lOgrePaging -lOIS -lOgreMain -lpthread -lboost_system
CXXFLAGS        +=      -Iinclude -IOgre3Dlibrary/Dependencies/zzip/include -Iinclude -IOgre3Dlibrary/Dependencies/Freetype/include
CXXFLAGS	+=	-IOgre3Dlibrary/include/OGRE/Bites -IOgre3Dlibrary/include/OGRE -IOgre3Dlibrary/include/OGRE/Overlay -IOISlibrary/include/OIS -ISDL/include/SDL2
CXXFLAGS	+=	-IOgre3Dlibrary/include/OGRE/HLMS -IOgre3Dlibrary/include/OGRE/MeshLodGenerator -IOgre3Dlibrary/include/OGRE/Paging
CXXFLAGS	+=	-IOgre3Dlibrary/include/OGRE/Plugins/BSPSceneManager -IOgre3Dlibrary/include/OGRE/Plugins/OctreeSceneManager -IOgre3Dlibrary/include/OGRE/Plugins/OctreeZone
CXXFLAGS	+=	-IOgre3Dlibrary/include/OGRE/Plugins/ParticleFX -IOgre3Dlibrary/include/OGRE/Plugins/PCZSceneManager -IOgre3Dlibrary/include/OGRE/Property
CXXFLAGS	+=	-IOgre3Dlibrary/include/OGRE/RTShaderSystem -IOgre3Dlibrary/include/OGRE/Terrain -IOgre3Dlibrary/include/OGRE/Threading
CXXFLAGS	+=	-IOgre3Dlibrary/include/OGRE/Volume

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
			@echo -e "\n" >> $$HOME/.bashrc
			@echo "# Paths to libraries for cpp_indie_studio" >> $$HOME/.bashrc
			@echo "export LD_LIBRARY_PATH="$$LD_LIBRARY_PATH:$$PWD/Ogre3Dlibrary/lib:$$PWD/OISlibrary/lib64:$$PWD/Ogre3Dlibrary/Dependencies/Freetype/lib64:$$PWD/Ogre3Dlibrary/Dependencies/zzip/lib"" >> $$HOME/.bashrc
			@echo "Don't forget to restart your terminal or source $$HOME/.bashrc"