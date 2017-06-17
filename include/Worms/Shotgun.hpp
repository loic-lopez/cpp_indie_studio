//
// Shotgun.hpp for shotgun in /home/deneub_s/cpp_indie_studio/include/Worms
// 
// Made by Stanislas Deneubourg
// Login   <deneub_s@epitech.net>
// 
// Started on  Thu Jun  1 07:54:52 2017 Stanislas Deneubourg
// Last update Thu Jun  1 08:07:02 2017 Stanislas Deneubourg
//

#ifndef	SHOTGUN_HPP
#define	SHOTGUN_HPP

#include "Interface/IWeapon.hpp"

#define	SHOTGUN_BULLETS_PER_CHARGER 10
#define	SHOTGUN_BULLET_SPEED	2.0f
#define SHOTGUN_BULLET_RANGE	25.0f

class	Shotgun : public IWeapon
{
private:
  struct Bullet
  {
    irr::scene::ISceneNode 	*bullet;
    irr::f32 			startBulletX;
    irr::f32 			startBulletRotationY;

    Bullet(const irr::core::vector3df &position,
	   const irr::core::vector3df &rotation,
	   irr::IrrlichtDevice *device, irr::core::aabbox3d<irr::f32> const &uziBox);
    void	deleteBullet();
  };
  float			splash_damage_range;
  float			weight;
  int 			damagePerBullet;
  int			chargerNumber;
  irr::IrrlichtDevice	*device;
  irr::scene::ISceneNode	*shotgunSceneNode;
  irr::core::aabbox3d<irr::f32>	shotgunBox;
  irrklang::ISoundEngine	*soundEngine;
  std::vector<Bullet>		firedBullets;
  
public:
  explicit Shotgun(irr::IrrlichtDevice *device, irrklang::ISoundEngine *soundEngine);
  ~Shotgun() override;

  bool	fire() 		override;
  void	showWeapon(const irr::core::vector3df &position, const irr::core::vector3df &rotation) 	override;
  void	deleteWeapon() 	override;
  void	setWeaponPosition(const irr::core::vector3df &position) override;
  void	setWeaponRotation(const irr::core::vector3df &rotation) override;
  bool	updateBullets() override;
  irr::core::vector3df	const &getWeaponRotation() const override;
};

#endif
