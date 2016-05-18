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
Diamond::Diamond()
: Pickup("diamond.obj")
{
  this->setColor(Color3B(0.0, 243.0, 120.0));
  this->glow->setColor(Color3B(168.0, 244.0, 203.0));
}

Diamond::~Diamond()
{
}

/**
 *
 *
 *
 */
void Diamond::onPickup()
{
  /**
   *
   * @Missions
   * Update missions with coins.
   *
   */
  if(MissionsFactory::getInstance()->isListenen())
  {
    Application->counter->missionUpdateOnce.coins++;
    Application->counter->missionUpdateProgress.coins++;

    Events::updateMissions();
  }

  Application->counter->onCoins();

  Sound->play("pickup-diamond");
}

/**
 *
 *
 *
 */
Diamond* Diamond::deepCopy()
{
  return new Diamond;
}
