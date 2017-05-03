//
// main.cpp for main in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 14:03:38 2017 Stanislas Deneubourg
// Last update Wed May  3 17:14:34 2017 Stanislas Deneubourg
//

#include "indie.hpp"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

int	main()
{
  //  IEngine	*engine = new Engine;

  irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL,
						  irr::core::dimension2d<irr::u32>(1920,1080), 32);

  
  irr::video::IVideoDriver* driver = device->getVideoDriver();
  
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();

  device->getCursorControl()->setVisible(false);

  irr::scene::IAnimatedMeshSceneNode* fairy = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("./Rock_1.dae"));

   if (fairy)
    {
      fairy->setMaterialTexture(0,
                                driver->getTexture("./ground.bmp"  /*"./irrlicht/media/faerie2.bmp" */)); // set diffuse texture                                                                                    
      fairy->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting                                                                                                                                 
      fairy->getMaterial(0).Shininess = 20.0f; // set size of specular highlights                                                                                                                                   
      fairy->setPosition(irr::core::vector3df(-10,0,-100));
      fairy->setMD2Animation ( irr::scene::EMAT_STAND );
    }



  /* CAMERA */

  irr::SKeyMap keyMap[4];                    // re-assigne les commandes

  keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer

  keyMap[0].KeyCode = irr::KEY_KEY_W;        // w

  keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer

  keyMap[1].KeyCode = irr::KEY_KEY_S;        // s

  keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche

  keyMap[2].KeyCode = irr::KEY_KEY_A;        // a

  keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite

  keyMap[3].KeyCode = irr::KEY_KEY_D;        // d


  sceneManager->addCameraSceneNodeFPS(0, 0.0f /* vitesse de rotation */, 0.03f /* vitesse de déplacement */, -1 /* pas d'ID */,
				      keyMap /* assigner la keymap */, 5 /* taille de 5 */);


  irr::video::SColor color(                  // contient la couleur blanc

			   255,                                   // composante A alpha (transparence)

			   255,                                   // composante R rouge

			   255,                                   // composante G verte

			   255);                                  // composante B bleue

    

  while (device->run())
    {
      driver->beginScene(true, true, color);
      sceneManager->drawAll();
      driver->endScene();
  }

 

  device->drop ();                           // libere la memoire

  return 0;

}
