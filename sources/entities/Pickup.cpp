/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 *
 * License: Tooflya Inc. Software License v1.
 *
 * Licensee may not use this software for commercial purposes. For the purpose of this license,
 * commercial purposes means that a 3rd party has to pay in order to access Software or that
 * the Website that runs Software is behind a paywall. In consideration of the License granted
 * under clause 2, Licensee shall pay Licensor a fee, via Credit-Card, PayPal or any other
 * mean which Licensor may deem adequate. Failure to perform payment shall construe as material
 * breach of this Agreement. This software is provided under an AS-IS basis and without any support,
 * updates or maintenance. Nothing in this Agreement shall require Licensor to provide Licensee with
 * support or fixes to any bug, failure, mis-performance or other defect in The Software.
 *
 * @cocos2d
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
Pickup::Pickup(const char* file)
: Decoration(file)
{
  this->removable = true;

  this->shadow = new Entity3D("pickup-shadow.obj", Application->environment->plane);
  this->shadow->setColor(Color3B(0, 0, 0));
  this->shadow->setOpacity(30);

  this->setScheduleUpdate(true);
}

Pickup::~Pickup()
{
}

/**
 *
 *
 *
 */
void Pickup::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0, 100, 0))
    )
  );

  this->shadow->_create();
}

void Pickup::onDestroy(bool action)
{
  Decoration::onDestroy(action);

  /**
   *
   *
   *
   */
  this->shadow->_destroy();
}

/**
 *
 *
 *
 */
void Pickup::onPickup()
{
}

/**
 *
 *
 *
 */
void Pickup::setPlate(Plate* plate)
{
  Decoration::setPlate(plate);

  /**
   *
   *
   *
   */
  this->setPositionY(this->getPositionY());
}

/**
 *
 *
 *
 */
void Pickup::update(float time)
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  this->shadow->setPositionX(x);
  this->shadow->setPositionY(y);
  this->shadow->setPositionZ(z);
}
