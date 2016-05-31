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
Copter::Copter(Node* parent)
: Decoration("copter.obj", parent)
{
  this->setColor(Color3B(255.0, 60.0, 60.0));

  this->removable = false;
  this->stopable = false;
  this->unremovable = true;
}
  
Copter::~Copter()
{
}

/**
 *
 *
 *
 */
void Copter::onCreate()
{
  Decoration::onCreate();
}

void Copter::onDestroy(bool action)
{
  Decoration::onDestroy(action);

  /**
   *
   *
   *
   */
  Sound->stop(this->sound);
}

/**
 *
 *
 *
 */
void Copter::setPlate(Plate* plate)
{
  Decoration::setPlate(plate);
}

void Copter::start()
{
  Decoration::start();

  /**
   *
   *
   *
   */
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
          this->sound = Sound->play("decoration-copter", this->getParent(), [=] () -> float {
            return this->getParent()->getPosition3D().distance(Application->environment->character->getPosition3D());
          }, Game::SOUND_DISTANCE);
          this->enable = true;
        }),
        EaseSineInOut::create(
          RotateBy::create(2.0, Vec3(0, 900, 0))
        ),
        CallFunc::create([=] () {
          this->enable = false;
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
Character::Crash Copter::status()
{
  if(this->enable)
  {
    this->stopAllActions();
    this->runAction(
      RepeatForever::create(
        RotateBy::create(1.0, Vec3(0, 900, 0))
      )
    );
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            this->sound = Sound->play("decoration-copter", this->getParent(), [=] () -> float {
              return this->getParent()->getPosition3D().distance(Application->environment->character->getPosition3D());
            }, Game::SOUND_DISTANCE);
            this->enable = true;
          }),
          DelayTime::create(1.0),
          nullptr
        )
      )
    );

    return Character::Crash::COPTER;
  }

  return Character::Crash::UNDEFINED;
}

/**
 *
 *
 *
 */
Copter* Copter::deepCopy()
{
  return new Copter;
}
