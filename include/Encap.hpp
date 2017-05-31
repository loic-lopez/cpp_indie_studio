//
// Encap.hpp for Encap.hpp in /home/dupil_l/Module_C++/cpp_indie_studio
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 14:02:28 2017 Loïc Dupil
// Last update Wed May  3 14:14:15 2017 Loïc Dupil
//

#ifndef ENCAP_HPP
# define ENCAP_HPP

#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <unistd.h>
#include "Dependencies/dirent.h"

class Encap
{

public:
  static DIR		*c_opendir(const char *);
  static int		c_closedir(DIR *);
  static struct dirent	*c_readdir(DIR *);
  static int		c_stat(const char *, struct stat *);
};

#endif	// ENCAP_HPP
