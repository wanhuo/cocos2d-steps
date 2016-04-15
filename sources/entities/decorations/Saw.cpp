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
Saw::Saw()
: Decoration("saw.obj")
{
  this->setColor(Color3B(255.0, 60.0, 60.0));

  this->removable = false;
  this->stopable = true;
}

Saw::~Saw()
{
}

/**
 *
 *
 *
 */
void Saw::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        DelayTime::create(0.25f),
        CallFunc::create([=] () {
          Sound->play("decoration-saw", this, [=] () -> float {
            return this->getParent()->getPosition3D().distance(Application->environment->character->getPosition3D());
          }, Game::SOUND_DISTANCE);
          this->enable = true;
        }),
        DelayTime::create(0.5f),
        CallFunc::create([=] () {
          this->enable = false;
        }),
        DelayTime::create(1.0f),
        CallFunc::create([=] () {
          Sound->play("decoration-saw", this, [=] () -> float {
            return this->getParent()->getPosition3D().distance(Application->environment->character->getPosition3D());
          }, Game::SOUND_DISTANCE);

          this->enable = true;
        }),
        DelayTime::create(0.5f),
        CallFunc::create([=] () {
          this->enable = false;
        }),
        DelayTime::create(0.75f),
        nullptr
      )
    )
  );
}

void Saw::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
void Saw::setPlate(Plate* plate)
{
  Decoration::setPlate(plate);
}

/**
 *
 *
 *
 */
Character::Crash Saw::status()
{
  return this->enable ? Character::Crash::SPIKES : Character::Crash::UNDEFINED;
}

/**
 *
 *
 *
 */
Saw* Saw::deepCopy()
{
  return new Saw;
}
