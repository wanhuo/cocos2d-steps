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
TypeMoveUp::TypeMoveUp()
: Special("plate.obj")
{
  this->plane = new Decoration(this);
  this->plane->unremovable = true;

  this->decoration = new Decoration("decoration-move-up.obj", this->plane);
  this->decoration->unremovable = true;
}

TypeMoveUp::~TypeMoveUp()
{
}

/**
 *
 *
 *
 */
void TypeMoveUp::onCreate()
{
  Special::onCreate();
}

void TypeMoveUp::onDestroy(bool action)
{
  Special::onDestroy(action);
}

/**
 *
 *
 *
 */
void TypeMoveUp::setPlate(Plate* plate)
{
  Special::setPlate(plate);

  /**
   *
   *
   *
   */
  this->decoration->_create();
  this->decoration->setColor(Color3B(255.0, 60.0, 60.0));
  this->decoration->setPosition3D(Vec3(0.0, 0.0, 0.0));

  this->plane->_create();
  this->plane->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->plane->setRotation3D(Vec3(0.0, this->plate->getDirection() ? 0 : 90, 0.0));

  this->getDecorations().push_back(this->plane);

  this->plate->behavior = Plate::DYNAMIC;
  this->plate->avoid = true;
}

void TypeMoveUp::start()
{
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
          auto action = Sequence::create(
            DelayTime::create(0.1),
            CallFunc::create([=] () {
            this->plate->setStage(this->plate->getStage() + 2);

          if(Application->environment->character->plates.current == this->plate && Application->environment->character->state == Character::STATE_NORMAL)
          {
            Application->environment->character->plane->runAction(
            Sequence::create(
            EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0.8, 0))
            ),
            nullptr
          )
            );
          }
            }),
            EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0.8, 0))
            ),
            CallFunc::create([=] () {
            this->plate->setStage(this->plate->getStage() - 1);
            }),
            nullptr
          );

          this->runAction(action->clone());
          //this->plate->moved = true;
          //this->plate->blocked = true;


          this->decoration->runAction(
            EaseSineInOut::create(
              RotateBy::create(0.3, Vec3(0, 0,  90))
            )
          );
        }),
        DelayTime::create(0.2),
        CallFunc::create([=] () {
          //this->plate->moved = false;
        }),
        DelayTime::create(0.3),
        CallFunc::create([=] () {
          auto action = Sequence::create(
            EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, -0.8, 0))
            ),
              CallFunc::create([=] () {
            this->plate->setStage(this->plate->getStage() + 1);
              }),
            nullptr
          );

            this->plate->setStage(this->plate->getStage() - 2);
          //this->plate->moved = true;

          this->runAction(action->clone());
          this->runAction(
            Sequence::create(
              DelayTime::create(0.15),
              CallFunc::create([=] () {
                //this->plate->moved = false;
                //this->plate->blocked = false;
              }),
              nullptr
            )
          );

          if(Application->environment->character->plates.current == this->plate && Application->environment->character->getManual() && Application->environment->character->state == Character::STATE_NORMAL)
          {
            Application->environment->character->plane->runAction(
            Sequence::create(
            EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, -0.8, 0))
            ),
            nullptr
          )
            );
          }


          this->decoration->runAction(
            EaseSineInOut::create(
              RotateBy::create(0.3, Vec3(0, 0,  -90))
            )
          );
        }),
        DelayTime::create(0.6),
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
TypeMoveUp* TypeMoveUp::deepCopy()
{
  return new TypeMoveUp;
}
