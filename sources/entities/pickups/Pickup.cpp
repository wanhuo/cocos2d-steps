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
  this->shadow = new Shadow("pickup-shadow.obj");

  this->window = BillBoard::create();
  this->window->_destroy();
  Application->environment->plane->addChild(this->window);

  this->glow = new Entity("ui/glow.png", this->window, true);
  this->glow->setScale(0.011);

  this->removable = true;

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
  this->stopAllActions();
  this->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0, 100, 0))
    )
  );

  this->window->_create();
}

void Pickup::onDestroy(bool action)
{
  Decoration::onDestroy(action);

  /**
   *
   *
   *
   */
  this->window->_destroy(action);
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
void Pickup::setPlate(Plate* plate, bool animated)
{
  Decoration::setPlate(plate, animated);

  /**
   *
   *
   *
   */
  this->setPositionY(this->getPositionY() + 1.2f);
}

/**
 *
 *
 *
 */
void Pickup::setVisible(bool visible)
{
  Decoration::setVisible(visible);

  /**
   *
   *
   *
   */
  this->window->setVisible(visible);
}

/**
 *
 *
 *
 */
void Pickup::update(float time)
{
  Decoration::update(time);

  /**
   *
   *
   *
   */
  auto x = this->getPositionX() + 0.2;
  auto y = this->getPositionY() - 0.25;
  auto z = this->getPositionZ() - 0.2;

  this->window->setPosition3D(Vec3(x, y, z));
}
