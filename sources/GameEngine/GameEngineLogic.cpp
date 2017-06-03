//
// GameEngineLogic.cpp for game engine logic in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Sat Jun  3 12:52:35 2017 Stanislas Deneubourg
// Last update Sat Jun  3 14:02:11 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

void	GameNamespace::GameEngine::execGame()
{
  unsigned int	worm_number = 0;
  
  while (42)
    {
      for (unsigned int i = 0; i < this->number_of_teams; i++)
	{
	  std::cout << "Team " << i << " : ";
	  this->teams.at(i).play_team(this->worms, this->device, worm_number);
	  std::cout << std::endl;
	}
      if (worm_number < this->worms_per_team - 1)
	worm_number++;
      else
	worm_number = 0;
    }
}
