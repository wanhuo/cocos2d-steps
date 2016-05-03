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
TypeMoved::TypeMoved()
: Special("plate-type-moved.obj")
{
  this->shadow = new Shadow("plate-bottom-shadow.obj");
  this->shadow->setMinScale(Vec3(1.0, 1.0, 1.0));
  this->shadow->setPosition(0.02);

  this->plane = new Decoration("decoration-move-plane.obj", Application->environment->plane);
  this->spikes = new Decoration("decoration-move-spikes.obj", Application->environment->plane);

  this->plane->unremovable = true;
  this->spikes->unremovable = true;

  this->setScheduleUpdate(true);
}

TypeMoved::~TypeMoved()
{
}

/**
 *
 *
 *
 */
void TypeMoved::onCreate()
{
  Special::onCreate();
}

void TypeMoved::onDestroy(bool action)
{
  Special::onDestroy(action);
}

/**
 *
 *
 *
 */
void TypeMoved::setPlate(Plate* plate)
{
  Special::setPlate(plate);

  /**
   *
   *
   *
   */
  this->plate->behavior = Plate::DYNAMIC;

  this->plane->_create();
  this->spikes->_create();

  this->plane->setPosition3D(Vec3(this->plate->getPositionX(), 0, this->plate->getPositionZ()));
  this->spikes->setPosition3D(Vec3(this->plate->getPositionX(), 0, this->plate->getPositionZ()));

  this->getDecorations().push_back(this->plane);
  this->getDecorations().push_back(this->spikes);
}
