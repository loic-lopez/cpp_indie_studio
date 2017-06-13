//
// main.cpp for main.cpp in /home/dupil_l/Module_C++/cpp_indie_studio/sources
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 16:39:31 2017 Loïc Dupil
// Last update Wed May 31 14:33:38 2017 Stanislas Deneubourg
//

#include <ctime>
#include "Core.hpp"

int	main()
{
  std::unique_ptr<ICore>	core(new Core);

  std::srand(std::time(nullptr));

  core->fillSaves();
  core->launch();
  return (0);
}
