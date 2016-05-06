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
TypeBest::TypeBest()
: Special("plate-type-best.obj")
{
  /*this->plane = new Entity3D(this, true);
  this->plane->setRotation3D(Vec3(-90.0, 0.0, 0.0));
  this->plane->setPosition3D(Vec3(0.0, 0.45, 0.0));

  this->texts.a = new Text("best-word-a", this->plane, true);
  this->texts.b = new Text("best-word-b", this->plane, true);

  this->texts.as = new Text("best-word-a", this->plane, true);
  this->texts.bs = new Text("best-word-b", this->plane, true);

  this->texts.a->setScale(0.02);
  this->texts.b->setScale(0.02);

  this->texts.as->setScale(0.02);
  this->texts.bs->setScale(0.02);

  this->texts.a->setPosition3D(Vec3(-this->texts.b->getWidthScaled(), 0.0, 0.0));
  this->texts.b->setPosition3D(Vec3(this->texts.b->getWidthScaled(), 0.0, 0.0));

  this->texts.as->setPosition3D(Vec3(-this->texts.bs->getWidthScaled() - 0.4, -0.1, 0.0));
  this->texts.bs->setPosition3D(Vec3(this->texts.bs->getWidthScaled() - 0.4, -0.1, 0.0));

  this->texts.a->setColor(Color3B::RED);
  this->texts.b->setColor(Color3B::RED);

  this->texts.as->setColor(Color3B::BLACK);
  this->texts.bs->setColor(Color3B::BLACK);

  this->texts.as->setGlobalZOrder(-50);
  this->texts.bs->setGlobalZOrder(-50);

  this->texts.as->setOpacity(30);
  this->texts.bs->setOpacity(30);*/
}

TypeBest::~TypeBest()
{
}

/**
 *
 *
 *
 */
void TypeBest::onCreate()
{
  Special::onCreate();

  /**
   *
   *
   *
   */
  /*this->texts.a->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(-1.0, 0.0, 0.0))
        ),
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(1.0, 0.0, 0.0))
        ),
        nullptr
      )
    )
  );

  this->texts.b->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(1.0, 0.0, 0.0))
        ),
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(-1.0, 0.0, 0.0))
        ),
        nullptr
      )
    )
  );

  this->texts.as->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(-1.0, 0.0, 0.0))
        ),
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(1.0, 0.0, 0.0))
        ),
        nullptr
      )
    )
  );

  this->texts.bs->runAction(
    RepeatForever::create(
      Sequence::create(
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(1.0, 0.0, 0.0))
        ),
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(-1.0, 0.0, 0.0))
        ),
        nullptr
      )
    )
  );*/
}

void TypeBest::onDestroy(bool action)
{
  Special::onDestroy(action);

  /**
   *
   *
   *
   */
}

/**
 *
 *
 *
 */
void TypeBest::setPlate(Plate* plate)
{
  Special::setPlate(plate);

  /**
   *
   *
   *
   */
  //this->setRotation3D(Vec3(0.0, this->plate->getDirection() ? 270.0 : 0.0, 0.0));
}

/**
 *
 *
 *
 */
TypeBest* TypeBest::deepCopy()
{
  return new TypeBest;
}
