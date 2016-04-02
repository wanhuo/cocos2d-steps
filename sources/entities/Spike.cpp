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
Spike::Spike()
: Decoration("spike.obj")
{
  this->setTexture("spike-texture.png");

  this->removable = false;
  this->stopable = true;
}

Spike::~Spike()
{
}

/**
 *
 *
 *
 */
void Spike::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->enable = false;

  this->runAction(
    Sequence::create(
      DelayTime::create(0.5),
      CallFunc::create([=] () {
        this->runAction(
          RepeatForever::create(
            Sequence::create(
              MoveBy::create(0.2, Vec3(0, 0.8, 0)),
              DelayTime::create(0.2),
              MoveBy::create(0.2, Vec3(0, -0.8, 0)),
              DelayTime::create(0.2),
              nullptr
            )
          )
        );
      }),
      nullptr
    )
  );

  this->runAction(
    Sequence::create(
      DelayTime::create(0.5),
      CallFunc::create([=] () {
        this->runAction(
          RepeatForever::create(
            Sequence::create(
              DelayTime::create(0.1),
              CallFunc::create([=] () {
                this->enable = true;
              }),
              DelayTime::create(0.5),
              CallFunc::create([=] () {
                this->enable = false;
              }),
              DelayTime::create(0.2),
              nullptr
            )
          )
        );
      }),
      nullptr
    )
  );
}

void Spike::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
void Spike::setPlate(Plate* plate)
{
  Decoration::setPlate(plate);
}

/**
 *
 *
 *
 */
Character::Crash Spike::status()
{
  return this->enable ? Character::Crash::SPIKES : Character::Crash::UNDEFINED;
}

/**
 *
 *
 *
 */
Spike* Spike::deepCopy()
{
  return new Spike;
}
