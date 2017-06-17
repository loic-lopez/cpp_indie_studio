//
// WormBot.cpp for WormBot.cpp in /home/giangi_j/rendu/TEK2/c++II/cpp_indie_studio
// 
// Made by Jade Giangiacomi
// Login   <giangi_j@epitech.net>
// 
// Started on  Fri Jun 16 10:08:37 2017 Jade Giangiacomi
// Last update Sat Jun 17 11:26:35 2017 Stanislas Deneubourg
//

#include "Worms/Worm.hpp"

void Worm::playWormBot(std::vector<irr::scene::IMeshSceneNode *> groundObjects,
		       std::vector<irr::core::vector3df> allWormsPos)
{
  if (!this->collideLeft)
    {
      this->wormLeftCollision(groundObjects);
    }
  else if (!this->collideRight)
    {
      this->wormRightCollision(groundObjects);
    }
}
