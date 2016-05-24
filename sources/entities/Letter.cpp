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
Letter::Letter(string file)
: Entity3D("letter-" + file + ".obj")
{
  this->letter = file;
  this->setTexture("textures/2/textures-state-1.png");
  this->setCascadeOpacityEnabled(false);

  this->none = new Entity3D("letter-none.obj", this);
  this->none->setTexture("textures/2/textures-state-1.png");
  this->none->setPosition3D(Vec3(0, 0, 0));
  this->none->setLightMask(32);
}

Letter::~Letter()
{
}

/**
 *
 *
 *
 */
void Letter::onCreate()
{
  Entity3D::onCreate();
}

void Letter::onDestroy()
{
  Entity3D::onDestroy();
}

/**
 *
 *
 *
 */
void Letter::action()
{
  this->runAction(
    Sequence::create(
      RotateBy::create(1.0, Vec3(0.0, random(-90, 90), 0.0)),
      RotateTo::create(1.0, Vec3(0.0, 0.0, 0.0)),
      CallFunc::create([=] () {
      this->action();
      }),
      nullptr
    )
  );
}

/**
 *
 *
 *
 */
Letter* Letter::deepCopy()
{
  return new Letter(this->letter);
}
