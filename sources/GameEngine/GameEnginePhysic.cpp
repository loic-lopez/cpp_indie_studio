/*
** GameEnginePhysic.cpp for cpp_indie_studio in /home/dupil_l/cpp_indie_studio/GameEnginePhysic.cpp
**
** Made by Loïc Dupil
** Login   <loic.dupil@epitech.eu>
**
** Started on  Tue Jun 13 11:12:08 2017 Loïc Dupil
** Last update Tue Jun 13 11:12:08 2017 Loïc Dupil
*/

#include "GameEngine/GameEngine.hpp"

void 	GameNamespace::GameEngine::ClearObject()
{
  for (std::list<btRigidBody *>::iterator iterator = this->rigidBodyObjects.begin(); iterator != this->rigidBodyObjects.end(); iterator++)
    {
      btRigidBody *object = *iterator;
      irr::scene::ISceneNode *node = static_cast<irr::scene::ISceneNode *>(object->getUserPointer());
      node->remove();
      this->World->removeRigidBody(object);
      delete object->getMotionState();
      delete object->getCollisionShape();
      delete object;
    }
  this->rigidBodyObjects.clear();
}

void 	GameNamespace::GameEngine::UpdateRender(btRigidBody *TObject)
{
  irr::scene::ISceneNode	*Node = static_cast<irr::scene::ISceneNode *>(TObject->getUserPointer());
  btVector3			point = TObject->getCenterOfMassPosition();

  Node->setPosition(irr::core::vector3df((irr::f32)point[0], (irr::f32)point[2], (irr::f32)point[2]));
}

void 	GameNamespace::GameEngine::UpdatePhysics(irr::u32 TDeltaTime)
{
  this->World->stepSimulation(TDeltaTime * 0.001f, 60);
  for (std::list<btRigidBody *>::iterator iterator = this->rigidBodyObjects.begin(); iterator != this->rigidBodyObjects.end(); iterator++)
    {
      this->UpdateRender(*iterator);
    }
}