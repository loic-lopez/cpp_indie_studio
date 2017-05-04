//
// GameEngine.cpp for GameEngine.cpp in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 18:20:40 2017 Stanislas Deneubourg
// Last update Thu May  4 14:42:53 2017 Stanislas Deneubourg
//

#include "GameEngine.hpp"

GameEngine::GameEngine(irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver,
		       const size_t &nb_textures, const size_t &nb_shapes)
{
  int	i = 0;

  srand(time(NULL));
  std::string file_texture = "./ressources/textures/ground" + std::to_string(rand() % nb_textures) + ".bmp";
  float	old_pos = 0;
  while (i < 20)
    {
      std::string file_shape = "./ressources/shapes/Rock_" + std::to_string(rand() % nb_shapes) + ".dae";
      irr::scene::IAnimatedMeshSceneNode *groundObject = smgr->addAnimatedMeshSceneNode(smgr->getMesh(file_shape.c_str()));
      
      if (groundObject)
	{
	  groundObject->setMaterialTexture(0,
				    driver->getTexture(file_texture.c_str())); // set diffuse texture
	  groundObject->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting
	  smgr->getMeshManipulator()->makePlanarTextureMapping(groundObject->getMesh(), 1.0f);
	  groundObject->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
	  //	  irr::core::vector3d<float> vector[8];
	  //	  groundObject->getTransformedBoundingBox().getEdges(vector);
	  irr::f32 minRadius = groundObject->getMesh()->getBoundingBox().getExtent().getLength() * 0.5f;
	  groundObject->setPosition(irr::core::vector3df(old_pos + minRadius,0,0));
	  old_pos += minRadius;
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
