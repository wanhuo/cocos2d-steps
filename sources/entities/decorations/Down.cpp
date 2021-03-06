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
Down::Down()
: Decoration("plate-down.obj")
{
  this->shadow = new Shadow("plate-shadow.obj");
  this->setScheduleUpdate(true);

  this->removable = false;

  this->setLightMask(0);
}

Down::~Down()
{
}

/**
 *
 *
 *
 */
void Down::onCreate()
{
  Decoration::onCreate();
}

void Down::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
void Down::onSound()
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
void Down::setPlate(Plate* plate, bool animated)
{
  Decoration::setPlate(plate);

  /**
   *
   *
   *
   */
  this->setPositionY(this->getPositionY() + 2.4);
  this->shadow->setPosition(plate->getStage() * 0.8);
}

/**
 *
 *
 *
 */
void Down::start()
{
  Decoration::start();

  /**
   *
   *
   *
   */
  this->enable = false;

  this->runAction(
    Sequence::create(
      DelayTime::create(0.5),
      CallFunc::create([=] () {
        this->runAction(
          RepeatForever::create(
            Sequence::create(
              EaseBounceOut::create(
                MoveBy::create(0.6, Vec3(0, -2.0, 0))
              ),
              DelayTime::create(0.6),
              MoveBy::create(0.2, Vec3(0, 2.0, 0)),
              DelayTime::create(0.6),
              nullptr
            )
          )
        );
      }),
      nullptr
    )
  );

  this->runAction(
    Sequence::create(
      DelayTime::create(0.6),
      CallFunc::create([=] () {
        this->runAction(
          RepeatForever::create(
            Sequence::create(
              CallFunc::create([=] () {
                this->enable = true;
                this->plate->moved = true;
                this->plate->blocked = true;
              }),
              DelayTime::create(0.6),
              DelayTime::create(0.6),
              CallFunc::create([=] () {
                this->enable = false;
                this->plate->moved = false;
                this->plate->blocked = false;
              }),
              DelayTime::create(0.2),
              DelayTime::create(0.6),
              nullptr
            )
          )
        );
      }),
      nullptr
    )
  );

  this->runAction(
    Sequence::create(
      DelayTime::create(0.6),
      CallFunc::create([=] () {
        this->runAction(
          RepeatForever::create(
            Sequence::create(
              DelayTime::create(0.3),
              CallFunc::create([=] () {
                this->onSound();

                Application->environment->runAction(
                  Shake::create(0.1, 0.05)
                );
              }),
              DelayTime::create(1.7),
              nullptr
            )
          )
        );
      }),
      nullptr
    )
  );
}

/**
 *
 *
 *
 */
Character::Crash Down::status()
{
  return this->enable ? Character::Crash::DOWN : Character::Crash::UNDEFINED;
}

/**
 *
 *
 *
 */
Down* Down::deepCopy()
{
  return new Down;
}
