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
TypeCopter::TypeCopter()
: Special("plate-type-copter.obj")
{
  this->copter = new Copter(this);
}

TypeCopter::~TypeCopter()
{
}

/**
 *
 *
 *
 */
void TypeCopter::onCreate()
{
  Special::onCreate();

  /**
   *
   *
   *
   */
  this->setTexture("plate-texture-state-1-copter.png");
}

void TypeCopter::onDestroy(bool action)
{
  Special::onDestroy(action);
}

/**
 *
 *
 *
 */
void TypeCopter::setPlate(Plate* plate)
{
  Special::setPlate(plate);

  /**
   *
   *
   *
   */
  this->copter->_create();
  this->copter->setPosition3D(Vec3(0, 0, 0));

  this->getDecorations().push_back(this->copter);
}

/**
 *
 *
 *
 */
TypeCopter* TypeCopter::deepCopy()
{
  return new TypeCopter;
}
