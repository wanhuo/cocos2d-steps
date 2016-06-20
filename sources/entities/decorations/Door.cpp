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
Door::Door(string file, Node* parent)
: Decoration(file, parent)
{
  this->engine = new Entity3D("door-engine.obj", this);
  this->engine->setColor(Color3B(255.0, 60.0, 60.0));

  this->removable = false;
  this->stopable = false;
  this->unremovable = true;

  this->setLightMask(0);
}

Door::~Door()
{
}

/**
 *
 *
 *
 */
void Door::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->engine->_create()->setPosition3D(Vec3(0.0, 1.15, 1.05));
}

void Door::onDestroy(bool action)
{
  Decoration::onDestroy(action);

  /**
   *
   *
   *
   */
  this->engine->_destroy(action);
}

/**
 *
 *
 *
 */
void Door::setPlate(Plate* plate)
{
  Decoration::setPlate(plate);
}

/**
 *
 *
 *
 */
void Door::start()
{
  this->engine->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseSineInOut::create(
          RotateBy::create(0.3, Vec3(0, 0, 180))
        ),
        DelayTime::create(0.7),
        EaseSineInOut::create(
          RotateBy::create(0.3, Vec3(0, 0, -180))
        ),
        DelayTime::create(0.7),
        nullptr
      )
    )
  );

  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
          this->enable = true;
        }),
        DelayTime::create(1.0),
        CallFunc::create([=] () {
          this->enable = false;
        }),
        DelayTime::create(1.0),
        nullptr
      )
    )
  );
}

/**
 *
 *
 *
 */
Character::Crash Door::status()
{
  return this->enable ? Character::Crash::GATE : Character::Crash::UNDEFINED;
}
