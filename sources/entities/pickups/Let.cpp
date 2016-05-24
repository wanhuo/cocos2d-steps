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
Let::Let(char letter)
: Pickup((((string) "letter-.obj").insert(7, 1, letter)).c_str())
{
  this->letter = letter;

  this->setColor(Color3B(255.0, 170.0, 0.0));
  this->glow->setColor(Color3B(252.0, 252.0, 136.0));
  this->glow->setPosition(0, 0.4);
}

Let::~Let()
{
}

/**
 *
 *
 *
 */
void Let::onCreate()
{
  Pickup::onCreate();

  /**
   *
   *
   *
   */
  this->setColor(Color3B(255.0, 170.0, 0.0));
  this->glow->setColor(Color3B(252.0, 252.0, 136.0));
  this->setTexture(Application->environment->getTextureState1());
}

void Let::onDestroy(bool action)
{
  Pickup::onDestroy(action);
}

/**
 *
 *
 *
 */
void Let::onPickup()
{
  Pickup::onPickup();

  /**
   *
   *
   *
   */
  if(Application->environment->character->plates.current->type == Plate::FINISH)
  {
    Application->environment->missions.controller->popups.ketchapp->update(this->letter);
  }
  else
  {
    Application->environment->missions.controller->popups.daily->update(this->letter);
  }

  Sound->play("pickup-gift");
}

/**
 *
 *
 *
 */
void Let::setPlate(Plate* plate, bool animated)
{
  Decoration::setPlate(plate, animated);

  /**
   *
   *
   *
   */
  this->setPositionY(this->getPositionY() + 0.8f);
}

/**
 *
 *
 *
 */
Let* Let::deepCopy()
{
  return new Let(this->letter);
}
