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
  this->shadow = new Shadow("plate-down-shadow.obj", Application->environment->plane);
  this->shadow->setColor(Color3B(0, 0, 0));
  this->shadow->setOpacity(30);

  this->setScheduleUpdate(true);

  this->setTexture("plate-texture-state-1.png");

  this->removable = false;
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

  /**
   *
   *
   *
   */
  this->enable = false;

  this->runAction(
    Sequence::create(
      MoveBy::create(0.5, Vec3(0, 2.4, 0)),
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

void Down::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
void Down::setPlate(Plate* plate)
{
  Decoration::setPlate(plate);
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
