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
Laser::Laser(Node* parent)
: Decoration("decoration-laser.obj", parent)
{
  this->element = static_cast<Sprite3D*>(this->getChildByName("trap"));
  this->state1 = static_cast<Sprite3D*>(this->getChildByName("state1"));
  this->state2 = static_cast<Sprite3D*>(this->getChildByName("state2"));

  this->removable = false;
  this->stopable = false;
  this->unremovable = true;

  this->setLightMask(1);

  this->element->setLightMask(1);
  this->state1->setLightMask(0);
  this->state2->setLightMask(0);

  this->element->_destroy();
  this->state1->_destroy();
  this->state2->_destroy();
}

Laser::~Laser()
{
}

/**
 *
 *
 *
 */
void Laser::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->element->_create();

  this->element->setTexture("ui/laser-texture.png");
  this->state1->setTexture("ui/laser-texture.png");
  this->state2->setTexture("ui/laser-texture.png");
}

void Laser::onDestroy(bool action)
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
void Laser::setPlate(Plate* plate)
{
  Decoration::setPlate(plate);
}

/**
 *
 *
 *
 */
void Laser::start()
{
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
        this->runAction(
          Sequence::create(
            CallFunc::create([=] () {
            this->sound = Sound->play("decoration-laser", this, [=] () -> float {
              return this->getParent()->getPosition3D().distance(Application->environment->character->getPosition3D());
            }, Game::SOUND_DISTANCE);
            this->enable = true;
            }),
            Repeat::create(
              Sequence::create(
                CallFunc::create([=] () {
                this->state1->_create();
                this->state2->_destroy();
                }),
                DelayTime::create(2.0 / 60.0),
                CallFunc::create([=] () {
                this->state1->_destroy();
                this->state2->_create();
                }),
                DelayTime::create(2.0 / 60.0),
                nullptr
              ), 1.0 / (2.0 / 60.0) / 2
            ),
            CallFunc::create([=] () {
            this->state1->_destroy();
            this->state2->_destroy();

            this->enable = false;

            Sound->stop(this->sound);
            }),
            nullptr
          )
        );
        }),
        DelayTime::create(2.0),
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
Character::Crash Laser::status()
{
  return this->enable ? Character::Crash::LASER : Character::Crash::UNDEFINED;
}
