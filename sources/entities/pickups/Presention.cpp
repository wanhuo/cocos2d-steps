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
Presention::Presention()
: Pickup("gift.obj")
{
  this->glow->setColor(Color3B::WHITE);
  this->glow->setScale(0.006);
}

Presention::~Presention()
{
}

/**
 *
 *
 *
 */
void Presention::onCreate()
{
  Pickup::onCreate();

  /**
   *
   *
   *
   */
  this->texture = this->textures.at(random(0, (int) this->textures.size() - 1));

  for(auto child : this->getChildren()) { static_cast<Sprite3D*>(child)->setTexture(this->texture); }

  Application->parameters.elapsed.present = 0;
}

void Presention::onDestroy(bool action)
{
  Pickup::onDestroy(action);
}

/**
 *
 *
 *
 */
void Presention::onPickup()
{
  Pickup::onPickup();

  /**
   *
   *
   *
   */
  Application->parameters.showPresent = true;
}

/**
 *
 *
 *
 */
void Presention::setPlate(Plate* plate, bool animated)
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
Presention* Presention::deepCopy()
{
  return new Presention;
}
