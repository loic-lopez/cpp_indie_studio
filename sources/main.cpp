//
// main.cpp for main in /home/deneub_s/cpp_indie_studio
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Tue May  2 11:40:00 2017 Stanislas Deneubourg
// Last update Tue May  2 11:44:11 2017 Stanislas Deneubourg
//

#include <irrlicht.h>

using namespace irr;

int main()
{
  // start up the engine
  IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
					core::dimension2d<u32>(640,480));
  
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* scenemgr = device->getSceneManager();
  
  device->setWindowCaption(L"Hello World!");
  
  // load and show quake2 .md2 model
  scene::ISceneNode* node = scenemgr->addAnimatedMeshSceneNode(
        scenemgr->getMesh("quake2model.md2"));
  
  // if everything worked, add a texture and disable lighting
  if (node)
    {
        node->setMaterialTexture(0, driver->getTexture("texture.bmp"));
        node->setMaterialFlag(video::EMF_LIGHTING, false);
    }
  
  // add a first person shooter style user controlled camera
  scenemgr->addCameraSceneNodeFPS();
  
  // draw everything
  while(device->run() && driver)
    {
      driver->beginScene(true, true, video::SColor(255,0,0,255));
      scenemgr->drawAll();
      driver->endScene();
    }
  
  // delete device
  device->drop();
  return 0;
 }
