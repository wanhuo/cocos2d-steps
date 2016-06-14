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
Spikes::Spikes(Node* parent)
: Decoration("spikes.obj", parent)
{
  this->setColor(Color3B(255.0, 60.0, 60.0));

  this->removable = false;
  this->stopable = true;
}

Spikes::~Spikes()
{
}

/**
 *
 *
 *
 */
void Spikes::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->e = false;
  this->pause = 0.2;

  /**
   *
   *
   *
   */
  this->setScale(1.0);
}

void Spikes::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
void Spikes::setPlate(Plate* plate)
{
  Decoration::setPlate(plate);
}

void Spikes::start()
{
  Decoration::start();

  /**
   *
   *
   *
   */
  if(this->getScaleY() == 1.0)
  {
    this->runAction(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
          this->runAction(
            RepeatForever::create(
              Sequence::create(
                MoveBy::create(0.2, Vec3(0, 0.8, 0)),
                DelayTime::create(this->pause),
                MoveBy::create(0.2, Vec3(0, -0.8, 0)),
                DelayTime::create(this->pause * 2),
                nullptr
              )
            )
          );
        }),
        nullptr
      )
    );
  }
  else
  {
    this->runAction(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
          this->runAction(
            RepeatForever::create(
              Sequence::create(
                ScaleTo::create(0.2, 1.0, 6.0, 1.0),
                DelayTime::create(this->pause),
                ScaleTo::create(0.2, 1.0, 0.0, 1.0),
                DelayTime::create(this->pause * 2),
                nullptr
              )
            )
          );
        }),
        nullptr
      )
    );
  }

  this->runAction(
    Sequence::create(
      DelayTime::create(0.5),
      CallFunc::create([=] () {
        this->runAction(
          RepeatForever::create(
            Sequence::create(
              DelayTime::create(this->pause / 2),
              CallFunc::create([=] () {
                Sound->play("decoration-spike", this, [=] () -> float {
                  return this->getParent()->getPosition3D().distance(Application->environment->character->getPosition3D());
                }, Game::SOUND_DISTANCE);
                this->enable = true;
              }),
              DelayTime::create(0.4),
              CallFunc::create([=] () {
                this->enable = false;
              }),
              DelayTime::create(this->pause * 2 + 0.1),
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
Character::Crash Spikes::status()
{
  return this->enable || this->e ? Character::Crash::SPIKES : Character::Crash::UNDEFINED;
}
