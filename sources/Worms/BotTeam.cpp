//
// BotTeam.cpp for bot team in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 11:42:14 2017 Stanislas Deneubourg
// Last update Thu Jun  1 13:47:06 2017 Stanislas Deneubourg
//

#include "Worms/BotTeam.hpp"

BotTeam::BotTeam(unsigned int players_, unsigned int team_nb,
		 std::vector<irr::core::vector3df> vector_pos,
		 irr::scene::IAnimatedMeshSceneNode *worm_mesh,
		 irr::IrrlichtDevice *device,
		 std::string worm_file)
{
  this->players = players_;
  this->team_name = "Bots ";
  this->team_name += team_nb;
  for (unsigned int i = 0; i < this->players; i++)
    {
      Worm	worm(i, vector_pos.at(i), worm_mesh, device, worm_file);
      this->team_players.push_back(worm);
      std::cout << "BOT " << i << " PLACED" << std::endl;
    }
}

BotTeam::~BotTeam()
{
  for (int i = this->team_players.size() != 0; i > 0; i = this->team_players.size())
    this->team_players.pop_back();
}
