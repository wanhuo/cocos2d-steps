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
TypeGate::TypeGate()
: Special("plate.obj")
{
  this->decorations = new Pool(new Door, this);
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

  /**
   *
   *
   *
   */
  this->decorations->clear(true);
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
  auto decoration1 = static_cast<Decoration*>(this->decorations->_create());
  auto decoration2 = static_cast<Decoration*>(this->decorations->_create());

  decoration1->setPlate(this->plate, false);
  decoration2->setPlate(this->plate, false);

  decoration1->setPosition3D(Vec3(0.0, 0, 0));
  decoration2->setPosition3D(Vec3(0.0, 0, 0));

  decoration1->setRotation3D(Vec3(0, 0, 0));
  decoration2->setRotation3D(Vec3(0, 180, 0));

  this->getDecorations().push_back(decoration1);
  this->getDecorations().push_back(decoration2);
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
  this->decorations->element(0)->runAction(
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

  this->decorations->element(1)->runAction(
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
  return new TypeGate;
}
