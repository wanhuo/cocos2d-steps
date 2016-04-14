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
Energy::Energy()
: Pickup("energy.obj")
{
  this->setTexture("energy-texture.png");
}

Energy::~Energy()
{
}

/**
 *
 *
 *
 */
void Energy::onPickup()
{
  this->onClear();

  this->count = 0;

  Application->environment->character->stopAllActions();
  Application->environment->character->setManual(false);

  this->action = CallFunc::create([=] () {
    auto next = Application->environment->character->getPlatesNear().next();

    if(next)
    {
      if(!next->moved && !next->blocked && next->type != Plate::DOWN)
      {
        float x;
        float z;

        if(next->position[Plate::LEFT])
        {
          x = 0.0;
          z = -1.5;

          Application->environment->character->onMoveLeft();
        }

        if(next->position[Plate::RIGHT])
        {
          x = 1.5;
          z = 0.0;

          Application->environment->character->onMoveRight();
        }

        Application->environment->character->plates.current = next;

        Application->environment->character->runAction(
          Spawn::create(
            RotateGlobalBy::create(0.1, Vec3(60 * z, 0, -60 * x)),
            Sequence::create(
              MoveBy::create(0.1, Vec3(x, (Application->environment->character->getPositionY() - 0.9), z)),
              CallFunc::create([=] () {
                if((++this->count < COUNT || next->behavior == Plate::DYNAMIC) && next->type != Plate::UP)
                {
                  Application->environment->character->runAction(this->action);
                }
                else
                {
                  this->onClear();

                  Application->environment->character->runAction(
                    Sequence::create(
                      DelayTime::create(0.1),
                      CallFunc::create([=] () {
                      if(next->type != Plate::UP)
                      {
                        Application->environment->character->setManual(true);
                      }
                      }),
                      nullptr
                    )
                  );
                }

                Application->environment->character->onTurnUpdate(next);
              }),
              nullptr
            ),
            nullptr
          )
        );
      }
      else
      {
        Application->environment->character->setManual(true);
      }
    }
    else
    {
      Application->environment->character->setManual(true);
    }
  });

  this->action->retain();

  Application->environment->character->runAction(this->action);

  Sound->play("pickup-energy");
}

void Energy::onClear()
{
  if(this->action)
  {
    this->action->release();
    this->action = nullptr;
  }
}

/**
 *
 *
 *
 */
const char* Energy::getParticleTexture()
{
  return "energy-texture.png";
}

/**
 *
 *
 *
 */
Energy* Energy::deepCopy()
{
  return new Energy;
}