//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Thu May  4 17:55:57 2017 Stanislas Deneubourg
//

#include "GameEngine.hpp"

GameNamespace::GameEngine::GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
				      const size_t &nb_textures, const size_t &nb_shapes) : smgr(smgr), driver(driver), nb_shapes(nb_shapes)
{
  
  srand(time(NULL));
  this->file_texture = "./ressources/textures/ground/ground" + std::to_string(rand() % nb_textures) + ".bmp";
  this->old_pos = 0;
  for (size_t i = 0; i < 30; i++)
    {
      for (size_t j = 0; j < 30; j++)
	{
	  GameMap tmp;

	  tmp.x = j;
	  tmp.y = i;
	  tmp.terrain = GameNamespace::TerrainType::AIR;
	  this->gameMap.push_back(tmp);
	}
    }

  for (size_t i = 0; i < 2; i = i)
    {
      int start_x = rand() % 30;
      int start_y = rand() % 30;

      if ((this->gameMap.at(start_x + 30 * start_y).terrain) != GameNamespace::TerrainType::GROUND)
	{
	  this->gameMap.at(start_x + 30 * start_y).terrain = GameNamespace::TerrainType::GROUND;
	  i++;
	}
    }
  for (size_t i = 0; i < 30 * 30; i++)
    {
      if ((this->gameMap.at(i).terrain) == GameNamespace::TerrainType::GROUND)
	{
	  size_t	pos = i % 30;
	  for (size_t j = i; j - pos > 0; j--)
	    this->gameMap.at(j).terrain = GameNamespace::TerrainType::GROUND;
	}
    }
  for (size_t i = 0; i < 30 * 30; i++)
    {
      if ((this->gameMap.at(i).terrain) == GameNamespace::TerrainType::GROUND)
	{
	  if (this->old_pos == 0)
	    this->old_pos = this->gameMap.at(i).x;
	  this->setModelProperties(this->gameMap.at(i).x, this->gameMap.at(i).y);
	}
    }
  this->cameraActions[0].Action = irr::EKA_MOVE_FORWARD;
  this->cameraActions[0].KeyCode = irr::KEY_KEY_Z;
  this->cameraActions[1].Action = irr::EKA_MOVE_BACKWARD;
  this->cameraActions[1].KeyCode = irr::KEY_KEY_S;
  this->cameraActions[2].Action = irr::EKA_STRAFE_LEFT;
  this->cameraActions[2].KeyCode = irr::KEY_KEY_Q;
  this->cameraActions[3].Action = irr::EKA_STRAFE_RIGHT;
  this->cameraActions[3].KeyCode = irr::KEY_KEY_D;
  this->cameraActions[4].Action = irr::EKA_JUMP_UP;
  this->cameraActions[4].KeyCode = irr::KEY_KEY_A;
  this->cameraActions[5].Action = irr::EKA_CROUCH;
  this->cameraActions[5].KeyCode = irr::KEY_KEY_E;
  
  this->gameCamera = smgr->addCameraSceneNodeFPS(0, 0.0f /* vitesse de rotation */, 0.03f /* vitesse de déplacement */,
						 -1 /* pas d'ID */, this->cameraActions /* assigner la keymap */, 5 /* taille de 5 */);
  this->gameCamera->setPosition(irr::core::vector3df(0,0,-75));

}

void	GameNamespace::GameEngine::setModelProperties(int x, int y)
{
  
  this->file_shape = "./ressources/shapes/Rock_" + std::to_string(rand() % this->nb_shapes) + ".dae";
  irr::scene::IAnimatedMeshSceneNode *groundObject = this->smgr->addAnimatedMeshSceneNode(smgr->getMesh(file_shape.c_str()));
  
  if (groundObject)
    {
      groundObject->setMaterialTexture(0,
				       this->driver->getTexture(file_texture.c_str())); // set diffuse texture
      groundObject->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting
      smgr->getMeshManipulator()->makePlanarTextureMapping(groundObject->getMesh(), 1.0f);
      groundObject->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
      irr::f32 minRadius = groundObject->getMesh()->getBoundingBox().getExtent().getLength() * 0.70f;
      //      groundObject->setPosition(irr::core::vector3df(old_pos + minRadius,0,0));
      groundObject->setPosition(irr::core::vector3df(this->old_pos + minRadius, y + minRadius, 0));
      groundObject->setRotation(irr::core::vector3df(rand() % 360, rand() % 360, 0));
      if (x == 0)
	this->old_pos = 0;
      this->old_pos += minRadius;
      this->groundObjects.push_back(groundObject);
    }
}
