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
Crystal::Crystal()
: Pickup("diamond.obj")
{
  this->setColor(Color3B(239.0, 87.0, 255.0));
  this->glow->setColor(Color3B(230.0, 190.0, 255.0));
}

Crystal::~Crystal()
{
}

/**
 *
 *
 *
 */
void Crystal::onPickup()
{
  /**
   *
   * @Missions
   * Update missions with crystals.
   *
   */
  if(MissionsFactory::getInstance()->isListenen())
  {
    Application->counter->missionUpdateOnce.special_once_1++;
    Application->counter->missionUpdateProgress.special_progress_1++;

    Events::updateMissions();
  }

  auto next = Application->environment->character->plates.current;

  for(int i = 0; i < 5; i++)
  {
    next = Application->environment->character->getPlatesNear(next).next();

    if(next)
    {
      if(next->getDecorations().size() || next->behavior == Plate::DYNAMIC || next->type == Plate::FINISH)
      {
        continue;
      }
      else
      {
        next->setType(Plate::DIAMOND, false);

        for(auto decoration : next->getDecorations())
        {
          decoration->setPosition3D(this->getPosition3D());
          decoration->runAction(
            MoveTo::create(0.05 * (i + 1), Vec3(next->getPositionX(), 1.6f + next->getStage() * 0.8, next->getPositionZ()))
          );
        }
      }
    }
    else
    {
      return;
    }
  }

  Sound->play("pickup-diamond");
}

/**
 *
 *
 *
 */
Crystal* Crystal::deepCopy()
{
  return new Crystal;
}
