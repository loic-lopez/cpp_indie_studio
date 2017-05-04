//
// main.cpp for main in /home/deneub_s/cpp_indie_studio/sources
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May  3 16:44:06 2017 Stanislas Deneubourg
// Last update Thu May  4 13:41:09 2017 Stanislas Deneubourg
//

#include "indie.hpp"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

int main()
{
  irr::IrrlichtDevice* device = irr::createDevice(irr::video::EDT_OPENGL,
                                                  irr::core::dimension2d<irr::u32>(1920,1080), 32);
  if (device == 0)
    return 1; // could not create selected driver.

  irr::video::IVideoDriver* driver = device->getVideoDriver();
  irr::scene::ISceneManager* smgr = device->getSceneManager();
  //  irr::gui::IGUIEnvironment* env = device->getGUIEnvironment();
  // load and display animated fairy mesh

  std::vector<irr::scene::IAnimatedMeshSceneNode *> fairys;
  size_t i = 0;

  while (i < 20)
    {
      irr::scene::IAnimatedMeshSceneNode *fairy = smgr->addAnimatedMeshSceneNode(smgr->getMesh("./ressources/shapes/Rock_1.dae"));
      
      
      if (fairy)
	{
	  std::string file = "./ressources/textures/ground" + std::to_string(rand() % 2) + ".bmp";
	  fairy->setMaterialTexture(0,
				    driver->getTexture(file.c_str())); // set diffuse texture
	  fairy->setMaterialFlag(irr::video::EMF_LIGHTING, true); // enable dynamic lighting
	  smgr->getMeshManipulator()->makePlanarTextureMapping(fairy->getMesh(), 1.0f);
	  fairy->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
	  irr::core::vector3d<float> vector[8];
	  fairy->getBoundingBox().getEdges(vector);
	  fairy->setPosition(irr::core::vector3df(static_cast<float>(i) * (vector[0].X * vector[4].X),0,0));
	  fairy->setMD2Animation (irr::scene::EMAT_STAND);
	  fairys.emplace_back(fairy);
	}
      i++;
    }

  // set ambient light

  // CAMERA PROPERTIES

  irr::SKeyMap keyMap[4];                    // re-assigne les commandes                            

  keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer                                             

  keyMap[0].KeyCode = irr::KEY_KEY_Z;        // w                                                   

  keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer                                             

  keyMap[1].KeyCode = irr::KEY_KEY_S;        // s                                                   

  keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche                                            

  keyMap[2].KeyCode = irr::KEY_KEY_Q;        // a                                                   

  keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite                                            

  keyMap[3].KeyCode = irr::KEY_KEY_D;        // d       
  
  // set window caption
  device->setWindowCaption(L"Irrlicht Engine - Render to Texture and Specular Highlights example");
  // add fps camera
  irr::scene::ICameraSceneNode* fpsCamera = smgr->addCameraSceneNodeFPS(0, 0.0f /* vitesse de rotation */, 0.03f /* vitesse de déplacement */, -1 /* pas d'ID */, keyMap /* assigner la keymap */, 5 /* taille de 5 */); fpsCamera->setPosition(irr::core::vector3df(0,0,-75));

  // disable mouse cursor
  device->getCursorControl()->setVisible(false);

  int lastFPS = -1;

  while(device->run())
    if (device->isWindowActive())
      {
        driver->beginScene(true, true, 0);

   
        // draw scene normally
	smgr->drawAll();
	
	//        env->drawAll();

        driver->endScene();

        // display frames per second in window title
        int fps = driver->getFPS();
        if (lastFPS != fps)
	  {
	    irr::core::stringw str = "Irrlicht Engine - Render to Texture and Specular Highlights example";
            str += " FPS:";
            str += fps;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
	  }
      }

  device->drop(); // drop device
  return 0;
}
