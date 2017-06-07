//
// GameEngineGeneration.cpp for generation in /home/deneub_s/cpp_indie_studio/sources
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 13:51:26 2017 Stanislas Deneubourg
// Last update Wed Jun  7 16:37:58 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

void	GameNamespace::GameEngine::mapGen()
{
  int   x1, y1, y2, x2;

  for (int i = 0; i < this->sizeY; i++)
    for (int j = 0; j < this->sizeX; j++)
      this->gameMap.emplace_back(j, i);
  for (int i = 0; i < this->sizeY; i++)
    for (int j = 0; j < this->sizeX; j++)
      this->gameMap2.emplace_back(j, i);
  for (int i = 0; i < this->sizeY * this->sizeX; i++)
    {
      if ((i % this->sizeY) == 0 || (i % this->sizeX) == this->sizeX - 1)
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
      if ((std::rand() % 100) < this->fillProbe)
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
      else
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
    }
  for (int i = 0; i < this->sizeY * this->sizeX; i++)
    this->gameMap2.at(i).terrain = GameNamespace::TerrainType::GROUND;
  for (int i = 0; i < this->generations; i++)
    {
      for (y1 = 1; y1 < this->sizeY - 1; y1++)
        {
          for (x1 = 1; x1 < this->sizeX - 1; x1++)
            {
              int       adjcountR1 = 0;
              int       adjcountR2 = 0;

              for (y2 = -1; y2 < 1; y2++)
                for (x2 = -1; x2 < 1; x2++)
                  if ((this->gameMap.at((x1-x2) + this->sizeY * (y1-y2)).terrain) != GameNamespace::TerrainType::AIR)
                    adjcountR1++;
              for (y2 = y1 - 2; y2 <= y1 + 2; y2++)
                {
                  for (x2 = x1 - 2; x2 <= x1 + 2; x2++)
                    {
                      if ((std::abs((y2-y1))) == 2 && (std::abs((x2-x1))) == 2)
                        continue;
                      if (y2 < 0 || x2 < 0 || y2 >= this->sizeY || x2 >= this->sizeX)
                        continue;
                      if ((this->gameMap.at(x2 + this->sizeY * y2).terrain) != GameNamespace::TerrainType::AIR)
                        adjcountR2++;
                    }
                }
              if (adjcountR1 >= this->r1Cutoff || adjcountR2 <= this->r2Cutoff)
                this->gameMap2.at(x1 + this->sizeY * y1).terrain = GameNamespace::TerrainType::GROUND;
              else
                this->gameMap2.at(x1 + this->sizeY * y1).terrain = GameNamespace::TerrainType::AIR;
            }
        }
      for (y1 = 1; y1 < this->sizeY - 1; y1++)
        for (x1 = 1; x1 < this->sizeX - 1; x1++)
          this->gameMap.at(x1 + this->sizeY * y1) = this->gameMap2.at(x1 + this->sizeY * y1);
    }
  if (this->drawWalls)
    {
      for (int i = 0; i < this->sizeX * this->sizeY; i++)
        {
          if ((i < this->sizeX) || ((i % this->sizeX) == 0) || ((i % this->sizeX) == this->sizeX - 1))
            this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
          if (i >= (this->sizeX * (this->sizeY - 1)))
            this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
        }

    }
  else
    {
      for (int i = 0; i < this->sizeX * this->sizeY; i++)
        if ((i < this->sizeX) || ((i % this->sizeX) == 0) || ((i % this->sizeX) == this->sizeX - 1) || (i >= (this->sizeX * (this->sizeY - 1))))
          this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
    }

  for (int i = 0; i < this->sizeX * this->sizeY; i++)
    if (this->gameMap.at(i).terrain == GameNamespace::TerrainType::GROUND)
      this->setBlockProperties(this->gameMap.at(i).x, this->gameMap.at(i).y);
}

void	GameNamespace::GameEngine::backgroundGen()
{
  this->gameCamera = smgr->addCameraSceneNode(nullptr,
                                              irr::core::vector3df(this->theFarthestMapPoint / 2,
                                                                   -this->sizeY / 2, -100),
                                              irr::core::vector3df(this->theFarthestMapPoint / 2,
                                                                   -this->sizeY / 2, 0),
                                              -1, true);
  this->waterMesh = this->smgr->addHillPlaneMesh("water",
						  irr::core::dimension2d<irr::f32>(20,10),
						  irr::core::dimension2d<irr::u32>(80,80), nullptr, 0,
                                                  irr::core::dimension2d<irr::f32>(0,0),
                                                  irr::core::dimension2d<irr::f32>(10,10));
  this->sea = this->smgr->addWaterSurfaceSceneNode(this->waterMesh->getMesh(0),
                                                   0.5f, 300.0f, 0.5f);
  this->sea->setMaterialTexture(0, this->driver->getTexture("./ressources/textures/terrain/detail_terrain.jpg"));
  this->sea->setMaterialTexture(1, this->driver->getTexture("./ressources/textures/water/water.jpg"));
  this->sea->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  this->sea->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);
  this->sea->setPosition(irr::core::vector3df(0, this->maxY *
					      ((this->groundObjects.at(this->groundObjects.size() - 1)->getMesh()
						->getBoundingBox().getExtent().getLength() * 0.70f) / 3)
                                              , 200.0f));
  this->driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
  this->skybox = this->smgr->addSkyBoxSceneNode(this->driver->getTexture("./ressources/skydome/irrlicht2_up.jpg"),
                                                this->driver->getTexture("./ressources/skydome/irrlicht2_dn.jpg"),
                                                this->driver->getTexture("./ressources/skydome/irrlicht2_lf.jpg"),
                                                this->driver->getTexture("./ressources/skydome/irrlicht2_rt.jpg"),
                                                this->driver->getTexture("./ressources/skydome/irrlicht2_ft.jpg"),
                                                this->driver->getTexture("./ressources/skydome/irrlicht2_bk.jpg"));
  this->backgroundTerrain = this->smgr->addTerrainSceneNode("./ressources/skydome/terrain-heightmap.bmp",
                                                            0, -1,
                                                            irr::core::vector3df(-1200.0f, -200.0f, 50.0f),
                                                            irr::core::vector3df(0.0f, 0.0f, 0.0f),
                                                            irr::core::vector3df(40.0f, 4.4f, 40.0f),
                                                            irr::video::SColor(255, 255, 255, 255),
                                                            5, irr::scene::ETPS_17, 4);
  this->backgroundTerrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->backgroundTerrain->setMaterialTexture(0, this->driver->getTexture("./ressources/textures/terrain/terrain_bruit.jpg"));
  this->backgroundTerrain->setMaterialTexture(1, this->driver->getTexture("./ressources/textures/terrain/detail_terrain.jpg"));
  this->backgroundTerrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
  this->backgroundTerrain->scaleTexture(1.0f, 20.0f);
}

void	GameNamespace::GameEngine::teamsGen()
{
  int	botTeamsLeftToEmplace = this->numberOfBotTeams;
  int	humanTeamsLeftToEmplace = this->numberOfHumanTeams;
  int	totalTeamsLeftToEmplace = this->numberOfTeams;
  int	whichTeamType;
  
  for (unsigned int i = 0; i < this->numberOfTeams; i++)
    {
      for (unsigned int j = 0; j < this->wormsPerTeam; j++)
	this->wormsRelativePos.push_back(this->wormsPosGen());
      whichTeamType = (std::rand() % (totalTeamsLeftToEmplace));
      if (whichTeamType < botTeamsLeftToEmplace)
	{
	  this->teams.emplace_back(this->wormsPerTeam, i, this->wormsRelativePos, this->device, this->worm, true);
	  std::cout << "BOT TEAM PLACED" << std::endl;
	  botTeamsLeftToEmplace--;
	  totalTeamsLeftToEmplace--;
	}
      else
	{
	  this->teams.emplace_back(this->wormsPerTeam, i, this->wormsRelativePos, this->device, this->worm, false);
	  std::cout << "HUMAN TEAM PLACED" << std::endl;
	  humanTeamsLeftToEmplace--;
	  totalTeamsLeftToEmplace--;
	}
      this->wormsRelativePos.clear();
    }
}

irr::core::vector3df	GameNamespace::GameEngine::wormsPosGen()
{
  int	x;
  int	y;
  int	z = 0;
  
  for (int placed = 0; placed == 0;)
    {
      x = std::rand() % this->sizeX;
      y = std::rand() % this->sizeY;
      if (((y + 1) < this->sizeY - 1) && ((y - 1) > 0) &&
	  (this->gameMap.at(x + this->sizeY * y).terrain) == GameNamespace::TerrainType::AIR
	  && (this->gameMap.at(x + this->sizeY * (y - 1)).terrain) == GameNamespace::TerrainType::AIR
	  && (this->gameMap.at(x + this->sizeY * (y + 1)).terrain) == GameNamespace::TerrainType::GROUND)
	placed = 1;
    }
  this->gameMap.at(x + this->sizeY * y).terrain = GameNamespace::TerrainType::WORM;
  return (irr::core::vector3df(static_cast<float>(x * this->blockSize),
			       static_cast<float>((-y * (this->blockSize / 3)) - 2.30),
			       static_cast<float>(z)));
}
