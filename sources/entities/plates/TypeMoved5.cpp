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
TypeMoved5::TypeMoved5()
: TypeMoved("")
{
  this->destroyShadow();
  this->shadow = nullptr;

  this->p = new Decoration("", Application->environment->plane);

  this->l = new Decoration("plate-type-moved-l.obj", this->p);
  this->r = new Decoration("plate-type-moved-r.obj", this->p);

  this->l->shadow = new Shadow("plate-bottom-shadow.obj", this->p);
  this->l->shadow->setMinScale(Vec3(0.5, 1.0, 1.2));
  this->l->shadow->setMaxScale(Vec3(0.5, 1.0, 1.2));
  this->l->shadow->setOffset(Vec3(0.40, 0.0, -0.23));

  this->r->shadow = new Shadow("plate-bottom-shadow.obj", this->p);
  this->r->shadow->setMinScale(Vec3(0.5, 1.0, 1.2));
  this->r->shadow->setMaxScale(Vec3(0.5, 1.0, 1.2));
  this->r->shadow->setOffset(Vec3(0.40, 0.0, -0.13));
}

TypeMoved5::~TypeMoved5()
{
}

/**
 *
 *
 *
 */
void TypeMoved5::onCreate()
{
  TypeMoved::onCreate();
}

void TypeMoved5::onDestroy(bool action)
{
  TypeMoved::onDestroy(action);
}

/**
 *
 *
 *
 */
void TypeMoved5::setPlate(Plate* plate)
{
  TypeMoved::setPlate(plate);

  /**
   *
   *
   *
   */
  this->p->_create();
  this->l->_create();
  this->r->_create();

  this->l->scheduleUpdate();
  this->r->scheduleUpdate();

  this->l->shadow->setPosition( - this->plate->getStage() * 0.8 - 0.4 + 0.01);
  this->r->shadow->setPosition( - this->plate->getStage() * 0.8 - 0.4 + 0.01);

  this->p->setPosition3D(Vec3(this->plate->getPositionX(), 0.4 + (plate->getStage() * 0.8), this->plate->getPositionZ()));
  this->p->setRotation3D(Vec3(0.0, (this->plate->getDirection() ? 270.0 : 0.0), 0.0));
  this->l->setPosition3D(Vec3(+ 0.75 / 2, 0, 0));
  this->r->setPosition3D(Vec3(- 0.75 / 2, 0, 0));

  this->getDecorations().push_back(this->p);
  this->getDecorations().push_back(this->l);
  this->getDecorations().push_back(this->r);
}

void TypeMoved5::start()
{
  this->l->runAction(
    RepeatForever::create(
      Sequence::create(
        MoveBy::create(0.15, Vec3(0.75, 0.0, 0.0)),
        DelayTime::create(0.5),
        MoveBy::create(0.15, Vec3(-0.75, 0.0, 0.0)),
        DelayTime::create(0.5),
        nullptr
      )
    )
  );

  this->r->runAction(
    RepeatForever::create(
      Sequence::create(
        MoveBy::create(0.15, Vec3(-0.75, 0.0, 0.0)),
        DelayTime::create(0.5),
        MoveBy::create(0.15, Vec3(0.75, 0.0, 0.0)),
        DelayTime::create(0.5),
        nullptr
      )
    )
  );

  this->plate->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
        this->plate->moved = true;

        if(Application->environment->character->plates.current == this->plate && Application->environment->character->getManual() && Application->environment->character->state == Character::STATE_NORMAL)
        {
          Application->environment->character->onLandFail(Character::NONE, this->plate);
        }
        }),
        DelayTime::create(0.15),
        DelayTime::create(0.5),
        DelayTime::create(0.15),
        CallFunc::create([=] () {
        this->plate->moved = false;
        }),
        DelayTime::create(0.5),
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
TypeMoved5* TypeMoved5::deepCopy()
{
  return new TypeMoved5;
}
