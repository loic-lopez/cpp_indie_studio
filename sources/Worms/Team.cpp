//
// HumanTeam.cpp for human team in /home/deneub_s/cpp_indie_studio/sources/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 19:51:11 2017 Stanislas Deneubourg
// Last update Tue Jun  6 11:20:59 2017 Stanislas Deneubourg
//

#include "Worms/Team.hpp"

Team::Team(unsigned int players_, unsigned int team_nb,
	   std::vector<irr::core::vector3df> vector_pos,
	   irr::scene::IAnimatedMeshSceneNode *worm_mesh,
	   irr::IrrlichtDevice *device,
	   std::string worm_file, bool is_bot)
{
  this->players = players_;
  this->team_name = "Humans ";
  this->team_name += team_nb;
  for (unsigned int i = 0; i < this->players; i++)
    this->team_players.push_back(Worm(i, vector_pos.at(i), worm_mesh, device, worm_file, is_bot));
}

Team::~Team()
{
  for (int i = this->team_players.size() != 0; i > 0; i = this->team_players.size())
    this->team_players.pop_back();
}

double	Team::play_team(irr::scene::IAnimatedMeshSceneNode *worms,
				irr::IrrlichtDevice *device,
				unsigned int i, std::time_t turn_start)
{
  std::cout << "Player " << i << " : ";
  return (this->team_players.at(i).play_worm(worms, device, turn_start));
}
