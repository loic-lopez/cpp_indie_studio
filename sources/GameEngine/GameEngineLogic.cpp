//
// GameEngineLogic.cpp for game engine logic in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Sat Jun  3 12:52:35 2017 Stanislas Deneubourg
// Last update Sat Jun  3 14:35:45 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

void	GameNamespace::GameEngine::execGame()
{
  for (unsigned int i = 0; i < this->number_of_teams; i++)
    {
      std::cout << "Team " << i << " : ";
      this->teams.at(i).play_team(this->worms, this->device, this->worm_number_atm);
      std::cout << std::endl;
    }
  if (this->worm_number_atm < this->worms_per_team - 1)
    this->worm_number_atm++;
  else
    this->worm_number_atm = 0;
}
