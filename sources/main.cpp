//
// main.cpp for main.cpp in /home/dupil_l/Module_C++/cpp_indie_studio/sources
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 16:39:31 2017 Loïc Dupil
// Last update Wed May  3 17:16:16 2017 Loïc Dupil
//

#include "Core.hpp"
#include "indie.hpp"

int	main()
{
  ICore	*bite = new Core;
  std::vector<std::string> saves;

  bite->fillSaves();
  bite->fillSoundLib();
  saves = bite->getSaves();
  for (size_t i = 0; i < saves.size() ; i++)
      std::cout << "sauvegarde nommée : \"" << saves[i] << "\" à été trouvée." << std::endl;
  saves = bite->getSoundLib();
  for (size_t i = 0; i < saves.size() ; i++)
      std::cout << "Fichier son nommé : \"" << saves[i] << "\" à été trouvé." << std::endl;
  return (0);
  
}
