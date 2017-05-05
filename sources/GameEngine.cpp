//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Fri May  5 17:19:31 2017 Stanislas Deneubourg
//

#include "GameEngine.hpp"
#include <iostream>

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

      int start_x;
      int start_y;
      int end_x;
      int end_y;
  
  for (size_t i = 0; i < 2; i = i)
    {
      start_x = rand() % 30;
      start_y = rand() % 30;
      end_x = rand() % 30;
      end_y = rand() % 30;
      
      if ((this->gameMap.at(start_x + 30 * start_y).terrain) != GameNamespace::TerrainType::GROUND)
	{
	  this->gameMap.at(start_x + 30 * start_y).terrain = GameNamespace::TerrainType::GROUND;
	  i++;
	}
      if ((this->gameMap.at(end_x + 30 * end_y).terrain) != GameNamespace::TerrainType::GROUND)
        {
          this->gameMap.at(end_x + 30 * end_y).terrain = GameNamespace::TerrainType::GROUND;
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
	  //if (this->old_pos == 0)
	    //	    this->old_pos = this->gameMap.at(i).x;
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
  
  /*  this->gameCamera = smgr->addCameraSceneNodeFPS(0, 0.0f, 0.03f, -1, this->cameraActions, 5, false, 0.0f, false, true); */

  for (size_t i = 0; i < this->max_pos_x_tab.size(); i++)
    this->final_pos_x_avg += this->max_pos_x_tab[i];
  this->final_pos_x_avg = final_pos_x_avg / this->max_pos_x_tab.size();
  std::cout << "Average final position : " << this->final_pos_x_avg << std::endl;
  //  this->gameCamera->setPosition(irr::core::vector3df(this->final_pos_x_avg, 0, -100));
  this->gameCamera = smgr->addCameraSceneNode(0,
					      irr::core::vector3df(this->final_pos_x_avg / 2,
								   0, -100),
					      irr::core::vector3df(this->final_pos_x_avg / 2,
                                                                   0, 0),
					      -1, true);
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
	{
	  std::cout << this->old_pos << std::endl;
	  this->max_pos_x_tab.push_back(old_pos);
	  this->old_pos = 0;
	}
      this->old_pos += minRadius;
      this->groundObjects.push_back(groundObject);
    }
}

void	GameNamespace::GameEngine::launchModel(irr::IrrlichtDevice *device)
{
  while(device->run())
    if (device->isWindowActive())
      {
	this->driver->beginScene(true, true, 0);


	// draw scene normally
	this->smgr->drawAll();

	//        env->drawAll();

	this->driver->endScene();

	// display frames per second in window title
      }
}
