//
// Core.cpp for Core.cpp in /home/dupil_l/Module_C++/cpp_indie_studio
// 
// Made by Loïc Dupil
// Login   <dupil_l@epitech.net>
// 
// Started on  Wed May  3 13:51:01 2017 Loïc Dupil
// Last update Wed Jun  7 16:16:13 2017 Stanislas Deneubourg
//

#include "Core.hpp"
#include "Encap.hpp"

static int checkExtensionFile(std::string const &filename, std::string const &extension)
{
  const auto &tmp = filename;
  std::size_t pos = tmp.find_last_of('.');

  if (pos == std::string::npos || tmp.substr(pos, tmp.size()) != extension)
    {
      std::cout << "Error: Bad file extension." << std::endl;
      return (-1);
    }
  return (0);
}

Core::Core()
{
  this->driverType = irr::video::EDT_OPENGL;
  this->device = irr::createDevice(this->driverType,
				   irr::core::dimension2d<irr::u32>(1920, 1080), 32, false, false, false, nullptr);
  this->driver = device->getVideoDriver();
  this->smgr = device->getSceneManager();
  this->smgr->addLightSceneNode(nullptr, irr::core::vector3df(-15,5,-105),
				irr::video::SColorf(0.5f, 0.5f, 0.5f));
  this->guienv = this->device->getGUIEnvironment();

  this->smgr->setAmbientLight(irr::video::SColor(0.3, 255, 255, 255));
  this->device->getCursorControl()->setVisible(false);
  this->eventStatus = EventStatus::STAND_BY;
  this->soundEngine = nullptr;
  this->drawWalls = true;
  this->playSound = true;
  this->NbrBotTeams = 1;
  this->NbrHumanTeams = 1;
  this->NbrTeams = 2;
  this->WormsPerTeam = 2;
  this->playMainSound = true;
}

Core::Core(Core const &obj)
{

}

Core				&Core::operator=(Core const &obj)
{
  return (*this);
}

Core::~Core()
{
  if (this->soundEngine != nullptr)
    {
      this->soundEngine->stopAllSounds();
      this->soundEngine->drop();
    }
  this->device->drop();
}

std::vector<std::string>	Core::getSaves() const
{
  return (this->saves);
}

void				Core::setSave(const std::string &saveName)
{
  this->saves.push_back(saveName);
}

void				Core::fillSaves()
{
  DIR				*dir;
  struct dirent			*direntp;
  std::string			file;

  if ((dir = Encap::c_opendir("saves/")) == nullptr)
    {
      std::cerr << "No saves directory" << std::endl;
      return ;
    }
  while ((direntp = Encap::c_readdir(dir)) != nullptr)
    {
      file = direntp->d_name;
      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (checkExtensionFile(file, ".xml") == 0))
	    this->saves.emplace_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);
}

std::vector<irr::video::IImage *>		Core::getTextures() const
{
  return (this->textures);
}

void						Core::fillTextures()
{
  return ;
}

std::vector<std::string>			Core::getSoundLib() const
{
  return (this->soundlib);
}

void						Core::fillSoundLib()
{
  DIR				*dir;
  struct dirent			*direntp;
  std::string			file;

  if ((dir = Encap::c_opendir("ressources/sounds/")) == nullptr)
    {
      std::cerr << "No saves directory" << std::endl;
      return ;
    }
  while ((direntp = Encap::c_readdir(dir)) != nullptr)
    {
      file = direntp->d_name;
      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (checkExtensionFile(file, ".ogg") == 0))
	    this->soundlib.emplace_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);
}

std::vector<std::string>			Core::loadDir(const std::string &path, const std::string &file_extension)
{
  DIR				*dir;
  struct dirent			*direntp;
  std::vector<std::string>	content;

  if ((dir = Encap::c_opendir(path.c_str())) == nullptr)
    {
      std::cerr << path << ": No such file or directory directory" << std::endl;
      return (content);
    }
  while ((direntp = Encap::c_readdir(dir)) != nullptr)
    {

      if (direntp->d_name[0] != '.')
	{
	  if (direntp->d_type != 4 && (checkExtensionFile(direntp->d_name, file_extension) == 0))
	    content.emplace_back(direntp->d_name);
	}
    }
  Encap::c_closedir(dir);
  free(direntp);
  return (content);
}

void						Core::launchSplashScreen()
{
  this->soundEngine = irrklang::createIrrKlangDevice();
  this->mainSound = this->soundEngine->play2D("ressources/sounds/CarlOrff.ogg", true,
					      false, false, irrklang::E_STREAM_MODE::ESM_AUTO_DETECT, true);
  std::unique_ptr<IModel> splashScreen(new SplashScreen(this->smgr, this->driver, this->device));

  splashScreen->setModelProperties();
  splashScreen->launchModel();
}

void						Core::launchMenu()
{
  this->device->getCursorControl()->setVisible(true);
  std::unique_ptr<IModel> Menu(new MenuModel(this->device, this->driver,
					     this->smgr, this->guienv, this->saves,
					     this->playSound, this->drawWalls,
					     &this->NbrHumanTeams, &this->NbrBotTeams,
					     &this->NbrTeams, &this->WormsPerTeam,
					     this->mainSound, &this->playMainSound));
  if (Menu != nullptr)
    {
      Menu->setModelProperties();
      this->eventStatus = Menu->launchModel();
    }
}

void						Core::launchGame()
{
  std::unique_ptr<IModel> GameEngine(new GameNamespace::GameEngine(this->smgr, this->driver,
								   this->loadDir("./ressources/textures/ground/", ".bmp").size(),
								   this->loadDir("./ressources/shapes/", ".dae").size(),
								   this->device, this->playSound,
								   this->drawWalls, this->NbrBotTeams, this->NbrHumanTeams,
								   this->NbrTeams, this->WormsPerTeam,
								   this->mainSound, &this->playMainSound));
  if (GameEngine != nullptr)
    {
      this->device->getCursorControl()->setVisible(false);
      GameEngine->setModelProperties();
      this->eventStatus = GameEngine->launchModel();
    }
}

void						Core::launch()
{
   // this->launchSplashScreen();
  while(device->run())
    {
      if (this->eventStatus == EventStatus::QUIT)
	break;
      if (this->eventStatus == EventStatus::STAND_BY || this->eventStatus == EventStatus::BACK_TO_MENU)
	this->launchMenu();
      else if (this->eventStatus == EventStatus::ENTER_IN_GAME)
	this->launchGame();
    }
}
