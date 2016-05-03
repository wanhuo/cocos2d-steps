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
TypeSaw::TypeSaw()
: Special("plate-type-saw.obj")
{
  this->saws = new Pool(new Saw, this);
}

TypeSaw::~TypeSaw()
{
}

/**
 *
 *
 *
 */
void TypeSaw::onCreate()
{
  Special::onCreate();
}

void TypeSaw::onDestroy(bool action)
{
  Special::onDestroy(action);
}

/**
 *
 *
 *
 */
void TypeSaw::setPlate(Plate* plate)
{
  Special::setPlate(plate);

  /**
   *
   *
   *
   */
  auto decoration1 = static_cast<Decoration*>(this->saws->_create());
  auto decoration2 = static_cast<Decoration*>(this->saws->_create());

  decoration1->setPlate(this->plate, false);
  decoration2->setPlate(this->plate, false);

  decoration1->setPosition3D(Vec3(-0.3, 0.4, -1.5f));
  decoration2->setPosition3D(Vec3(+0.3, 0.4, +1.5f));

  decoration1->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseSineInOut::create(
          RotateBy::create(1.0, Vec3(720.0f, 0, 0))
        ),
        DelayTime::create(0.5f),
        EaseSineInOut::create(
          RotateBy::create(1.0, Vec3(-720.0f, 0, 0))
        ),
        DelayTime::create(0.5f),
        nullptr
      )
    )
  );

  decoration2->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseSineInOut::create(
          RotateBy::create(1.0, Vec3(-720.0f, 0, 0))
        ),
        DelayTime::create(0.5f),
        EaseSineInOut::create(
          RotateBy::create(1.0, Vec3(720.0f, 0, 0))
        ),
        DelayTime::create(0.5f),
        nullptr
      )
    )
  );

  decoration1->runAction(
    RepeatForever::create(
      Sequence::create(
        MoveBy::create(1.0, Vec3(0, 0, 3)),
        DelayTime::create(0.5f),
        MoveBy::create(1.0, Vec3(0, 0, -3)),
        DelayTime::create(0.5f),
        nullptr
      )
    )
  );

  decoration2->runAction(
    RepeatForever::create(
      Sequence::create(
        MoveBy::create(1.0, Vec3(0, 0, -3)),
        DelayTime::create(0.5f),
        MoveBy::create(1.0, Vec3(0, 0, 3)),
        DelayTime::create(0.5f),
        nullptr
      )
    )
  );

  this->getDecorations().push_back(decoration1);
  this->getDecorations().push_back(decoration2);
}

/**
 *
 *
 *
 */
TypeSaw* TypeSaw::deepCopy()
{
  return new TypeSaw;
}
