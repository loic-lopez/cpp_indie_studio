//
// GameEngineGeneration.cpp for generation in /home/deneub_s/cpp_indie_studio/sources
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Wed May 31 13:51:26 2017 Stanislas Deneubourg
// Last update Fri Jun  2 18:30:25 2017 Stanislas Deneubourg
//

#include "GameEngine/GameEngine.hpp"

void	GameNamespace::GameEngine::mapGen()
{
  int   x1, y1, y2, x2;

  for (int i = 0; i < this->size_y; i++)
    for (int j = 0; j < this->size_x; j++)
      this->gameMap.emplace_back(j, i);
  for (int i = 0; i < this->size_y; i++)
    for (int j = 0; j < this->size_x; j++)
      this->gameMap2.emplace_back(j, i);
  for (int i = 0; i < this->size_y * this->size_x; i++)
    {
      if ((i % this->size_y) == 0 || (i % this->size_x) == this->size_x - 1)
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
      if ((std::rand() % 100) < this->fillProbe)
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
      else
        this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
    }
  for (int i = 0; i < this->size_y * this->size_x; i++)
    this->gameMap2.at(i).terrain = GameNamespace::TerrainType::GROUND;
  for (int i = 0; i < this->generations; i++)
    {
      for (y1 = 1; y1 < this->size_y - 1; y1++)
        {
          for (x1 = 1; x1 < this->size_x - 1; x1++)
            {
              int       adjcount_r1 = 0;
              int       adjcount_r2 = 0;

              for (y2 = -1; y2 < 1; y2++)
                for (x2 = -1; x2 < 1; x2++)
                  if ((this->gameMap.at((x1-x2) + this->size_y * (y1-y2)).terrain) != GameNamespace::TerrainType::AIR)
                    adjcount_r1++;
              for (y2 = y1 - 2; y2 <= y1 + 2; y2++)
                {
                  for (x2 = x1 - 2; x2 <= x1 + 2; x2++)
                    {
                      if ((std::abs((y2-y1))) == 2 && (std::abs((x2-x1))) == 2)
                        continue;
                      if (y2 < 0 || x2 < 0 || y2 >= this->size_y || x2 >= this->size_x)
                        continue;
                      if ((this->gameMap.at(x2 + this->size_y * y2).terrain) != GameNamespace::TerrainType::AIR)
                        adjcount_r2++;
                    }
                }
              if (adjcount_r1 >= this->r1_cutoff || adjcount_r2 <= this->r2_cutoff)
                this->gameMap2.at(x1 + this->size_y * y1).terrain = GameNamespace::TerrainType::GROUND;
              else
                this->gameMap2.at(x1 + this->size_y * y1).terrain = GameNamespace::TerrainType::AIR;
            }
        }
      for (y1 = 1; y1 < this->size_y - 1; y1++)
        for (x1 = 1; x1 < this->size_x - 1; x1++)
          this->gameMap.at(x1 + this->size_y * y1) = this->gameMap2.at(x1 + this->size_y * y1);
    }
  if (this->drawWalls)
    {
      for (int i = 0; i < this->size_x * this->size_y; i++)
        {
          if ((i < this->size_x) || ((i % this->size_x) == 0) || ((i % this->size_x) == this->size_x - 1))
            this->gameMap.at(i).terrain = GameNamespace::TerrainType::GROUND;
          if (i >= (this->size_x * (this->size_y - 1)))
            this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
        }

    }
  else
    {
      for (int i = 0; i < this->size_x * this->size_y; i++)
        if ((i < this->size_x) || ((i % this->size_x) == 0) || ((i % this->size_x) == this->size_x - 1) || (i >= (this->size_x * (this->size_y - 1))))
          this->gameMap.at(i).terrain = GameNamespace::TerrainType::AIR;
    }

  for (int i = 0; i < this->size_x * this->size_y; i++)
    if (this->gameMap.at(i).terrain == GameNamespace::TerrainType::GROUND)
      this->setBlockProperties(this->gameMap.at(i).x, this->gameMap.at(i).y);
}

void	GameNamespace::GameEngine::backgroundGen()
{
  this->gameCamera = smgr->addCameraSceneNode(nullptr,
                                              irr::core::vector3df(this->the_farthest_map_point / 2,
                                                                   -this->size_y / 2, -100),
                                              irr::core::vector3df(this->the_farthest_map_point / 2,
                                                                   -this->size_y / 2, 0),
                                              -1, true);
  this->water_mesh = this->smgr->addHillPlaneMesh("water",
						  irr::core::dimension2d<irr::f32>(20,10),
						  irr::core::dimension2d<irr::u32>(80,80), nullptr, 0,
                                                  irr::core::dimension2d<irr::f32>(0,0),
                                                  irr::core::dimension2d<irr::f32>(10,10));
  this->sea = this->smgr->addWaterSurfaceSceneNode(this->water_mesh->getMesh(0),
                                                   0.5f, 300.0f, 0.5f);
  this->sea->setMaterialTexture(0, this->driver->getTexture("./ressources/textures/terrain/detail_terrain.jpg"));
  this->sea->setMaterialTexture(1, this->driver->getTexture("./ressources/textures/water/water.jpg"));
  this->sea->setMaterialFlag(irr::video::EMF_LIGHTING, true);
  this->sea->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);
  this->sea->setPosition(irr::core::vector3df(0, this->max_y *
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
  for (unsigned int i = 0; i < this->number_of_teams; i++)
    {
      for (unsigned int j = 0; j < this->worms_per_team; j++)
	this->worms_relative_pos.push_back(this->wormsPosGen());
      if (i < (this->number_of_teams - this->number_of_bot_teams))
	this->teams.emplace_back(this->worms_per_team, i, this->worms_relative_pos, this->worms, this->device, this->worm, true);
      else
	this->teams.emplace_back(this->worms_per_team, i, this->worms_relative_pos, this->worms, this->device, this->worm, false);
      this->worm_mesh.push_back(this->worms);
      this->worms_relative_pos.clear();
    }
}

irr::core::vector3df	GameNamespace::GameEngine::wormsPosGen()
{
  int	x;
  int	y;
  int	z = 0;
  
  for (int placed = 0; placed == 0;)
    {
      x = rand() % this->size_x;
      y = rand() % this->size_y;
      if (((y + 1) < this->size_y - 1) && ((y - 1) > 0) &&
	  (this->gameMap.at(x + this->size_y * y).terrain) == GameNamespace::TerrainType::AIR
	  && (this->gameMap.at(x + this->size_y * (y - 1)).terrain) == GameNamespace::TerrainType::AIR
	  && (this->gameMap.at(x + this->size_y * (y + 1)).terrain) == GameNamespace::TerrainType::GROUND)
	placed = 1;
    }
  this->gameMap.at(x + this->size_y * y).terrain = GameNamespace::TerrainType::WORM;
  return (irr::core::vector3df(static_cast<float>(x * this->block_size), static_cast<float>((-y * (this->block_size / 3)) - 2.30), static_cast<float>(z)));
}
