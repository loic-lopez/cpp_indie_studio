/*
** Dependencies.hpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Dependencies.hpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  mer. mai 31 15:19:42 2017 Loïc Lopez
** Last update mer. mai 31 15:19:42 2017 Loïc Lopez
*/

#ifndef CPP_INDIE_STUDIO_DEPENDENCIES_HPP
#define CPP_INDIE_STUDIO_DEPENDENCIES_HPP

#ifdef _MSC_VER
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
	#pragma comment(lib, "irrKlang.lib")
	#include <windows.h>
#endif

#include <irrKlang.h>
#include <irrlicht.h>
#include <btBulletDynamicsCommon.h>

#endif //CPP_INDIE_STUDIO_DEPENDENCIES_HPP