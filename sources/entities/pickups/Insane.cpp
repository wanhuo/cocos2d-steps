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
Insane::Insane()
: Pickup("energy.obj", Application->environment->plane)
{
  this->setColor(Color3B(255.0, 55.0, 0.0));
  this->glow->setColor(Color3B(252.0, 52.0, 136.0));
}

Insane::~Insane()
{
}

/**
 *
 *
 *
 */
void Insane::onCreate()
{
  Pickup::onCreate();

  /**
   *
   *
   *
   */
  auto action = EaseBounceOut::create(
    ScaleTo::create(0.5, 1.0)
  );

  this->setScale(0);
  this->window->setScale(0);
  this->shadow->setScale(0);

  this->glow->setOpacity(150);
  this->glow->setScale(0.011);

  this->runAction(action->clone());
  this->window->runAction(action->clone());
  this->shadow->runAction(action->clone());

  this->setTexture(Application->environment->getTextureState1());

  this->runAction(
    DelayTime::create(1.0)
  );

  this->glow->runAction(
      RepeatForever::create(
        Sequence::create(
          ScaleTo::create(0.5, 0.011),
          ScaleTo::create(0.5, 0.005),
          nullptr
        )
      )
  );
}

void Insane::onDestroy(bool action)
{
  Pickup::onDestroy(action);
}

/**
 *
 *
 *
 */
void Insane::onRemove()
{
  this->runAction(
    Sequence::create(
      ScaleTo::create(0.2, 0),
      CallFunc::create([=] () {
      this->plate->clearDecorations();
      }),
      nullptr
    )
  );

  this->glow->stopAllActions();
  this->glow->runAction(
    Spawn::create(
      FadeOut::create(0.2),
      ScaleTo::create(0.2,  0.040),
      nullptr
    )
  );
}

void Insane::onPickup()
{
  Pickup::onPickup();

  /**
   *
   *
   *
   */
  Application->environment->character->changeState(Character::STATE_INSANE);

  /**
   *
   *
   *
   */
  Sound->play("pickup-insane");
}

/**
 *
 *
 *
 */
void Insane::setPlate(Plate* plate, bool animated)
{
  Decoration::setPlate(plate, animated);

  /**
   *
   *
   *
   */
  this->setPositionY(plate->getStage() * 0.8 + 1.6);
  this->shadow->setPosition(plate->getStage() * 0.8);
}
