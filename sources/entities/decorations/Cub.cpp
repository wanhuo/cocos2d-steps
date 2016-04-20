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
Cub::Cub()
: Decoration("plate-down.obj")
{
  this->shadow = new Shadow("plate-down-shadow.obj", Application->environment->plane);
  this->shadow->setColor(Color3B(0, 0, 0));
  this->shadow->setSize(0);
  this->shadow->setMaxScale(Vec3(2.5, 2.5, 2.5));

  this->setScheduleUpdate(true);

  this->setTexture("plate-texture-state-1.png");

  this->removable = false;
}

Cub::~Cub()
{
}

/**
 *
 *
 *
 */
void Cub::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->enable = false;

  this->setScaleY(3.2);
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        DelayTime::create(0.2),
        CallFunc::create([=] () {
            this->shadow->setVisible(true);
        }),
        MoveBy::create(0.5, Vec3(0, -25, 0)),
        CallFunc::create([=] () {
          this->enable = true;
          this->plate->moved = true;
          this->plate->blocked = true;
        }),
        MoveBy::create(0.1, Vec3(0, -5, 0)),
        CallFunc::create([=] () {
          this->onSound();

          Application->environment->runAction(
            Shake::create(0.5, 0.1)
          );
        }),
        EaseSineInOut::create(
          MoveBy::create(0.1, Vec3(0, 1, 0))
        ),
        EaseBounceOut::create(
          MoveBy::create(0.4, Vec3(0, -1, 0))
        ),
        DelayTime::create(random(0.0, 1.0)),
        CallFunc::create([=] () {
          this->enable = false;
          this->plate->moved = false;
          this->plate->blocked = false;
        }),
        EaseSineInOut::create(
          MoveBy::create(1.0, Vec3(0, 30, 0))
        ),
        nullptr
      )
    )
  );

  this->shadow->setVisible(false);
  this->shadow->setPositionY(0.01);
}

void Cub::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
void Cub::onSound()
{
  Sound->play("decoration-down", this, [=] () -> float {
    return this->getPosition3D().distance(Application->environment->character->getPosition3D());
  }, Game::SOUND_DISTANCE);
}

/**
 *
 *
 *
 */
void Cub::setPlate(Plate* plate, bool animated)
{
  Decoration::setPlate(plate, false);

  /**
   *
   *
   *
   */
  this->setPositionY(30.4);
}

/**
 *
 *
 *
 */
Character::Crash Cub::status()
{
  return this->enable ? Character::Crash::DOWN : Character::Crash::UNDEFINED;
}

/**
 *
 *
 *
 */
Cub* Cub::deepCopy()
{
  return new Cub;
}
