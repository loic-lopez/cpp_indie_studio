//
// WormBot.cpp for WormBot.cpp in /home/giangi_j/rendu/TEK2/c++II/cpp_indie_studio
// 
// Made by Jade Giangiacomi
// Login   <giangi_j@epitech.net>
// 
// Started on  Fri Jun 16 10:08:37 2017 Jade Giangiacomi
// Last update Fri Jun 16 13:09:27 2017 Jade Giangiacomi
//

#include "Worms/Worm.hpp"

void	Worm::playWormBot(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
			      std::vector<irr::core::vector3df> allWormsPos)
{
  for (unsigned int i = 0; i < allWormsPos.size(); i++)
    std::cout << allWormsPos.at(i).X << " | " << allWormsPos.at(i).Y << std::endl;
  this->wormLeftCollision(groundObjects);
}
