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
Portal::Portal(Node* parent)
: Decoration("decoration-portal.obj", parent)
{
  this->removable = false;

  this->setScale(0.8);
  this->setScaleY(0.1);
}

Portal::~Portal()
{
}

/**
 *
 *
 *
 */
void Portal::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
  this->enable = true;

  this->runAction(
    RepeatForever::create(
      RotateBy::create(0.5, Vec3(0.0, 360.0, 0.0))
    )
  );
}

void Portal::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
void Portal::onPickup()
{
  if(this->enable)
  {
    this->enable = false;

    if(Application->environment->character->getManual())
    {
      Sound->play("portal-in");

      Application->environment->character->setManual(false);
      Application->environment->character->plane->stopAllActions();
      Application->environment->character->plane->runAction(
        Spawn::create(
          Repeat::create(
            RotateBy::create(0.1, Vec3(0.0, 90.0, 0.0)), 5
          ),
          ScaleTo::create(0.5, 0.5, 0.0, 0.5),
          Sequence::create(
            MoveBy::create(0.5, Vec3(0.0, -1.0, 0.0)),
            CallFunc::create([=] () {
              Application->environment->character->setVisible(false);
              Application->environment->character->plane->setVisible(false);
              Application->environment->character->shadow->setVisible(false);

              /**
               *
               *
               *
               */
              auto element = Application->environment->character->plates.current;
              auto stage = element->getStage();

              int l = 0;
              int r = 0;
              int count = 10;

              float time = 0.08;

              for(int i = 0; i < count; i++)
              {
                auto plates = Application->environment->character->getPlatesNearWithDefaults(element);

                if(plates.plates[Plate::LEFT])
                {
                  l++;
                  element = plates.plates[Plate::LEFT];
                }
                else
                {
                  r++;
                  element = plates.plates[Plate::RIGHT];
                }

                if(element)
                {
                  if(i >= count - 1)
                  {
                  }
                  else
                  {
                    this->runAction(
                      Sequence::create(
                        DelayTime::create(time * i),
                        CallFunc::create(CC_CALLBACK_0(Plate::onCount, element)),
                        CallFunc::create(CC_CALLBACK_0(Character::onSound, Application->environment->character)),
                        CallFunc::create(CC_CALLBACK_0(Counter::onCount, Application->counter)),
                        nullptr
                      )
                    );
                  }
                }
              }

              
      Application->environment->character->runAction(
        Spawn::create(
          Sequence::create(
            CallFunc::create([=] () {
               Application->environment->plane->runAction(
                EaseSineIn::create(
                  MoveBy::create(time* (count - 1) / 2, Vec3(-0.75 * l, 0, 0.75 * r))
                )
              );
            }),
            EaseSineIn::create(
              MoveBy::create(time * (count - 1) / 2, Vec3(0.75 * l, 0, -0.75 * r))
            ),
            CallFunc::create([=] () {
              Application->environment->plane->runAction(
                EaseSineIn::create(
                  MoveBy::create(time * (count - 1) / 2, Vec3(-0.75 * l, 0, 0.75 * r))
                )
              );
            }),
            EaseSineIn::create(
              MoveBy::create(time * (count - 1) / 2, Vec3(0.75 * l, 0, -0.75 * r))
            ),
            CallFunc::create([=] () {
              Application->environment->character->setVisible(true);
              Application->environment->character->plane->setVisible(true);
              Application->environment->character->shadow->setVisible(true);
              Application->environment->character->plates.current = element;
              Application->environment->character->onLandSuccessful(Character::NONE, element);

              /**
               *
               *
               *
               */
              Sound->play("portal-out");

              Application->environment->character->plane->runAction(
                Spawn::create(
                  MoveBy::create(0.5, Vec3(0.0, 1.0 + (element->getStage() - stage) * 0.8, 0.0)),
                  ScaleTo::create(0.5, 1.0, 1.0, 1.0),
                  Sequence::create(
                    Repeat::create(
                      RotateBy::create(0.1, Vec3(0.0, -90.0, 0.0)), 5
                    ),
                    CallFunc::create([=] () {
                    Application->environment->character->setManual(true);
                    }),
                    nullptr
                  ),
                  nullptr
                )
              );
            }),
            nullptr
          ),
          nullptr
        )
      );
      Application->environment->runAction(
        Repeat::create(
          Sequence::create(
            DelayTime::create(time),
            CallFunc::create([=] () {
              Application->environment->generator->create(true);
            }),
            nullptr
          ), count - 1
        )
      );
            }),
            nullptr
          ),
          nullptr
        )
      );
    }
  }
}
