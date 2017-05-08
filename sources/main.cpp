//
// main.cpp for main.cpp in /home/dupil_l/Module_C++/cpp_indie_studio/sources
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 16:39:31 2017 Loïc Dupil
// Last update Wed May  3 18:52:10 2017 Stanislas Deneubourg
//

#include "indie.hpp"

int	main()
{
  std::unique_ptr<ICore>	core(new Core);

  std::srand(std::time(nullptr));

  core->fillSaves();
  core->fillSoundLib();
  core->launch();
  /*for (size_t i = 0; i < saves.size() ; i++)
      std::cout << "sauvegarde nommée : \"" << saves[i] << "\" à été trouvée." << std::endl;
  saves = bite->getSoundLib();
  for (size_t i = 0; i < saves.size() ; i++)
      std::cout << "Fichier son nommé : \"" << saves[i] << "\" à été trouvé." << std::endl;
  */
  return (0);
  
}
