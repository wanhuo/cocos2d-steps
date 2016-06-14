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
Trap::Trap(Node* parent)
: Decoration("decoration-trap.obj", parent)
{
  this->decorations = new Pool(new Decoration("decoration-trap-spikes.obj"), this);

  this->setColor(Color3B(255.0, 60.0, 60.0));

  this->removable = false;
  this->stopable = true;
}

Trap::~Trap()
{
}

/**
 *
 *
 *
 */
void Trap::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  auto decoration1 = static_cast<Decoration*>(this->decorations->_create());
  auto decoration2 = static_cast<Decoration*>(this->decorations->_create());

  decoration1->setColor(Color3B(255.0, 60.0, 60.0));
  decoration2->setColor(Color3B(255.0, 60.0, 60.0));

  decoration1->setPosition3D(Vec3(0.0, 0.3, 0.0));
  decoration2->setPosition3D(Vec3(0.0, 0.3, 0.0));

  decoration1->setRotation3D(Vec3(0.0, 0.0, 0.0));
  decoration2->setRotation3D(Vec3(0.0, 180.0, 0.0));
}

void Trap::onDestroy(bool action)
{
  Decoration::onDestroy(action);

  /**
   *
   *
   *
   */
  this->decorations->clear(true);
}

/**
 *
 *
 *
 */
void Trap::setPlate(Plate* plate, bool animated)
{
  this->plate = plate;
}

/**
 *
 *
 *
 */
void Trap::start()
{
  Decoration::start();

  /**
   *
   *
   *
   */
  auto decoration1 = static_cast<Decoration*>(this->decorations->element(0));
  auto decoration2 = static_cast<Decoration*>(this->decorations->element(1));

  decoration1->runAction(
    RepeatForever::create(
      Sequence::create(
        RotateBy::create(0.05, Vec3(0.0, 0.0, 90.0)),
        DelayTime::create(0.2),
        RotateBy::create(0.2, Vec3(0.0, 0.0, -90.0)),
        DelayTime::create(1.2),
        nullptr
      )
    )
  );

  decoration2->runAction(
    RepeatForever::create(
      Sequence::create(
        RotateBy::create(0.05, Vec3(0.0, 0.0, -90.0)),
        DelayTime::create(0.2),
        RotateBy::create(0.2, Vec3(0.0, 0.0, 90.0)),
        DelayTime::create(1.2),
        nullptr
      )
    )
  );

  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
          Sound->play("decoration-spike", this, [=] () -> float {
            return this->getParent()->getPosition3D().distance(Application->environment->character->getPosition3D());
          }, Game::SOUND_DISTANCE);
          this->enable = true;
          this->plate->blocked = true;
        }),
        DelayTime::create(0.3),
        CallFunc::create([=] () {
          this->enable = false;
          this->plate->blocked = false;
        }),
        DelayTime::create(1.35),
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
Character::Crash Trap::status()
{
  return this->enable ? Character::Crash::TRAP : Character::Crash::UNDEFINED;
}
