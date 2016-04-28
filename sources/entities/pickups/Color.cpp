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
Color::Color()
: Pickup("color.obj")
{
  this->setTexture("color-texture.png");

  this->glow->setColor(Color3B::WHITE);
  this->glow->setScale(0.006);
}

Color::~Color()
{
}

/**
 *
 *
 *
 */
void Color::onCreate()
{
  Pickup::onCreate();

  /**
   *
   *
   *
   */
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
          this->runAction(
            TintTo::create(0.5, random(0.0, 255.0), random(0.0, 255.0), random(0.0, 255.0))
          );
        }),
        DelayTime::create(0.5),
        nullptr
      )
    )
  );
}

void Color::onDestroy(bool action)
{
  Pickup::onDestroy(action);
}

/**
 *
 *
 *
 */
void Color::onPickup()
{
  Pickup::onPickup();

  /**
   *
   *
   *
   */
  Application->environment->character->color = this->getColor();
  Application->environment->character->runAction(
    TintTo::create(0.5, this->getColor())
  );
}

/**
 *
 *
 *
 */
void Color::setPlate(Plate* plate, bool animated)
{
  Decoration::setPlate(plate, animated);

  /**
   *
   *
   *
   */
  this->setPositionY(this->getPositionY() + 1.0f);
}

/**
 *
 *
 *
 */
Color* Color::deepCopy()
{
  return new Color;
}
