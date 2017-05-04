//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Thu May  4 13:48:42 2017 Stanislas Deneubourg
//

#include "GameEngine.hpp"

GameEngine::GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
{
  int	i = 0;

  
  while (i < 20)
    {
      irr::scene::IAnimatedMeshSceneNode *groundObject = smgr->addAnimatedMeshSceneNode(smgr->getMesh("./ressources/shapes/Rock_1.dae"));
      
      
      if (groundObject)
	{
	  std::string file = "./ressources/textures/ground" + std::to_string(rand() % 2) + ".bmp";
	  groundObject->setMaterialTexture(0,
				    driver->getTexture(file.c_str())); // set diffuse texture
	  groundObject->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting
	  smgr->getMeshManipulator()->makePlanarTextureMapping(groundObject->getMesh(), 1.0f);
	  groundObject->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
	  irr::core::vector3d<float> vector[8];
	  groundObject->getBoundingBox().getEdges(vector);
	  groundObject->setPosition(irr::core::vector3df(static_cast<float>(i)
							 * (vector[0].X * vector[4].X),0,0));
	  this->groundObjects.push_back(groundObject);
	}
      i++;
    }
  this->cameraActions[0].Action = irr::EKA_MOVE_FORWARD;
  this->cameraActions[0].KeyCode = irr::KEY_KEY_Z;
  this->cameraActions[1].Action = irr::EKA_MOVE_BACKWARD;
  this->cameraActions[1].KeyCode = irr::KEY_KEY_S;
  this->cameraActions[2].Action = irr::EKA_STRAFE_LEFT;
  this->cameraActions[2].KeyCode = irr::KEY_KEY_Q;
  this->cameraActions[3].Action = irr::EKA_STRAFE_RIGHT;
  this->cameraActions[3].KeyCode = irr::KEY_KEY_D;
  
  this->gameCamera = smgr->addCameraSceneNodeFPS(0, 0.0f /* vitesse de rotation */, 0.03f /* vitesse de déplacement */,
						 -1 /* pas d'ID */, this->cameraActions /* assigner la keymap */, 5 /* taille de 5 */);
  this->gameCamera->setPosition(irr::core::vector3df(0,0,-75));

}

void	GameEngine::setModelProperties()
{

}
