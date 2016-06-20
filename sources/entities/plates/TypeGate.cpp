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
TypeGate::TypeGate(string file, bool direction)
: Special(file)
{
  this->direction = direction;

  if(this->direction)
  {
    this->decoration1 = new Door("decoration-door-right.obj", this);
    this->decoration2 = new Door("decoration-door-right.obj", this);
  }
  else
  {
    this->decoration1 = new Door("decoration-door-left.obj", this);
    this->decoration2 = new Door("decoration-door-right.obj", this);
  }
}

TypeGate::~TypeGate()
{
}

/**
 *
 *
 *
 */
void TypeGate::onCreate()
{
  Special::onCreate();
}

void TypeGate::onDestroy(bool action)
{
  Special::onDestroy(action);
}

/**
 *
 *
 *
 */
void TypeGate::setPlate(Plate* plate)
{
  Special::setPlate(plate);

  /**
   *
   *
   *
   */
  this->decoration1->_create();
  this->decoration2->_create();

  this->decoration1->setPlate(this->plate);
  this->decoration2->setPlate(this->plate);

  this->decoration1->setPosition3D(Vec3(0.0, 0, 0));
  this->decoration2->setPosition3D(Vec3(0.0, 0, 0));

  this->decoration1->setRotation3D(Vec3(0, 0, 0));
  this->decoration2->setRotation3D(Vec3(0, 180, 0));

  this->getDecorations().push_back(this->decoration1);
  this->getDecorations().push_back(this->decoration2);
}

/**
 *
 *
 *
 */
void TypeGate::start()
{
  Special::start();

  /**
   *
   *
   *
   */
  this->decoration1->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseBounceOut::create(
          MoveBy::create(0.5, Vec3(0, 0, -0.75))
        ),
        DelayTime::create(0.5),
        EaseBounceOut::create(
          MoveBy::create(0.5, Vec3(0, 0, 0.75))
        ),
        DelayTime::create(0.5),
        nullptr
      )
    )
  );

  this->decoration2->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseBounceOut::create(
          MoveBy::create(0.5, Vec3(0, 0, 0.75))
        ),
        DelayTime::create(0.5),
        EaseBounceOut::create(
          MoveBy::create(0.5, Vec3(0, 0, -0.75))
        ),
        DelayTime::create(0.5),
        nullptr
      )
    )
  );

  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
          this->plate->blocked = true;
        }),
        DelayTime::create(1.0),
        CallFunc::create([=] () {
          this->plate->blocked = false;
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
TypeGate* TypeGate::deepCopy()
{
  return new TypeGate(this->textureFileName, this->direction);
}
