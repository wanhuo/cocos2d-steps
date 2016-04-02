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
Diamond::Diamond()
: Pickup("diamond.obj")
{
  this->setTexture("crystal-texture.png");

  this->test = new Entity3D("diamond-circle.obj", this, true);

  this->setScale(1.2);

  this->test->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0, 360, 0))
    )
  );

  this->test->setTexture("crystal-circle-texture.png");
}

Diamond::~Diamond()
{
}

/**
 *
 *
 *
 */
void Diamond::onPickup()
{
  Application->counter->onCoins();

  Sound->play("pickup-diamond");
}

/**
 *
 *
 *
 */
const char* Diamond::getParticleTexture()
{
  return "diamond-texture.png";
}

/**
 *
 *
 *
 */
Diamond* Diamond::deepCopy()
{
  return new Diamond;
}
