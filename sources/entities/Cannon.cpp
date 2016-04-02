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
Cannon::Cannon()
: Decoration("cannon.obj")
{
  this->weapon = new Entity3D("cannon-weapon.obj", this, true);
}

Cannon::~Cannon()
{
}

/**
 *
 *
 *
 */
void Cannon::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->weapon->setScaleX(0);

  this->weapon->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseSineInOut::create(
          ScaleTo::create(1.0, 14.0, 1.0, 1.0)
        ),
        EaseSineInOut::create(
          ScaleTo::create(1.0, 2.0, 1.0, 1.0)
        ),
        nullptr
      )
    )
  );
}

void Cannon::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
Cannon* Cannon::deepCopy()
{
  return new Cannon;
}
