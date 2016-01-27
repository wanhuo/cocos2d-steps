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
Plate::Plate()
: Cube("plate.obj")
{
}

Plate::~Plate()
{
}

/**
 *
 *
 *
 */
void Plate::onCreate()
{
  Cube::onCreate();

  /**
   *
   *
   *
   */
  this->setType(TYPE_NORMAL);
  this->setColor(Color3B(255, 132, 42));

  this->runAction(
    RepeatForever::create(
      Sequence::create(
        DelayTime::create(random(1.0, 5.0)),
        CallFunc::create([=] () {
          Application->environment->createRipple(this->getPositionX(), this->getPositionZ(), 1.25);
        }),
        nullptr
      )
    )
  );
}

void Plate::onDestroy(bool action)
{
  Cube::onDestroy(action);

  /**
   *
   *
   *
   */
  this->clearDecoration(true);
}

/**
 *
 *
 *
 */
void Plate::setType(int type, bool animated)
{
  this->type = type;

  switch(this->type)
  {
    case TYPE_SPIKES:
    this->decoration = static_cast<Decoration*>(Application->environment->spikes->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_DIAMOND:
    this->decoration = static_cast<Decoration*>(Application->environment->diamonds->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_CRYSTAL:
    this->decoration = static_cast<Decoration*>(Application->environment->crystals->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_ENERGY:
    this->decoration = static_cast<Decoration*>(Application->environment->energies->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_STAR:
    this->decoration = static_cast<Decoration*>(Application->environment->stars->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_HEART:
    this->decoration = static_cast<Decoration*>(Application->environment->hearts->_create());
    this->decoration->setPlate(this, animated);
    break;
  }
}

/**
 *
 *
 *
 */
void Plate::clearDecoration(bool force, bool animated)
{
  if(this->decoration)
  {
    if(this->decoration->removable || force || animated)
    {
      this->decoration->remove(force);
      this->decoration = nullptr;
    }
  }
}

/**
 *
 *
 *
 */
void Plate::update(float time)
{
  Cube::update(time);
}

/**
 *
 *
 *
 */
Plate* Plate::deepCopy()
{
  return new Plate;
}
