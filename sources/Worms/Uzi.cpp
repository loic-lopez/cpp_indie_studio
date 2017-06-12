/*
** Uzi.cpp for cpp_indie_studio in /home/lopez_i/cpp_indie_studio/Uzi.cpp
**
** Made by Loïc Lopez
** Login   <loic.lopez@epitech.eu>
**
** Started on  ven. juin 09 14:45:54 2017 Loïc Lopez
// Last update Mon Jun 12 18:21:05 2017 Stanislas Deneubourg
*/

// TODO: ENLEVER LES PRINTS
#include <iostream>
#include "Worms/Uzi.hpp"

Uzi::Uzi(irr::IrrlichtDevice *device)
{
  this->bulletsNumber = 30;
  this->damagePerBullet = 5;
  this->weight = 0;
  this->device = device;
}

Uzi::~Uzi()
{

}

bool	Uzi::fire()
{
  if (this->bulletsNumber > 0)
    {
      std::cout << "FIRE WITH UZI" << std::endl;
      this->bulletsNumber--;
      return (true);
    }
  std::cout << "NO MORE BULLETS IN UZI" << std::endl;
  return (false);
}

void	Uzi::showWeapon()
{
  this->uziSceneNode = this->device->getSceneManager()->addMeshSceneNode
    (this->device->getSceneManager()->getMesh("ressources/weapons/Uzi/Uzi.obj"));
  this->uziSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->uziSceneNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
}

void	Uzi::deleteWeapon()
{
  this->uziSceneNode->getParent()->removeChild(this->uziSceneNode);
}

void 	Uzi::setWeaponPosition(const irr::core::vector3df &position)
{
  this->uziSceneNode->setPosition(position);
}

void 	Uzi::setWeaponRotation(const irr::core::vector3df &rotation)
{
  this->uziSceneNode->setRotation(rotation);
}


