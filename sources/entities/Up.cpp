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
Up::Up()
: Decoration()
{
  //this->setTexture("spike-texture.png");

  this->removable = false;
}

Up::~Up()
{
}

/**
 *
 *
 *
 */
void Up::onCreate()
{
  Decoration::onCreate();

  /**
   *
   *
   *
   */
}

void Up::onDestroy(bool action)
{
  Decoration::onDestroy(action);
}

/**
 *
 *
 *
 */
void Up::onPickup()
{
  auto element = Application->environment->character->plates.current;

  int l = 0;
  int r = 0;
  float count = 5.0;
  float time = 0.5;

  for(int i = 0; i < count; i++)
  {
    auto plates = Application->environment->character->getPlatesNear(element);

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
  }

  Application->environment->character->runAction(
    Sequence::create(
      CallFunc::create([=] () {
        Application->environment->character->setManual(false);
      }),
      CallFunc::create([=] () {
        Application->cameras.d->runAction(
          EaseSineIn::create(
            MoveBy::create(time / 2, Vec3(-sqrt(pow(0.75, 2) / 2) * r, 0.0, -sqrt(pow(0.75, 2) / 2) * r))
          )
        );
        Application->cameras.d->runAction(
          EaseSineIn::create(
            MoveBy::create(time / 2, Vec3(sqrt(pow(0.75, 2) / 2) * l, 0.0, -sqrt(pow(0.75, 2) / 2) * l))
          )
        );
      }),
      EaseSineIn::create(
        MoveBy::create(time / 2, Vec3(0.75 * l, 1.0, -0.75 * r))
      ),
      CallFunc::create([=] () {
        Application->cameras.d->runAction(
          EaseSineIn::create(
            MoveBy::create(time / 2, Vec3(-sqrt(pow(0.75, 2) / 2) * r, 0.0, -sqrt(pow(0.75, 2) / 2) * r))
          )
        );
        Application->cameras.d->runAction(
          EaseSineIn::create(
            MoveBy::create(time / 2, Vec3(sqrt(pow(0.75, 2) / 2) * l, 0.0, -sqrt(pow(0.75, 2) / 2) * l))
          )
        );
      }),
      EaseSineIn::create(
        MoveBy::create(time / 2, Vec3(0.75 * l, -1.0, -0.75 * r))
      ),
      CallFunc::create([=] () {
        Application->environment->character->plates.current = element;
        Application->environment->character->setManual(true);
        Application->environment->character->onLandSuccessful(Character::NONE, element);
      }),
      nullptr
    )
  );
  Application->environment->character->runAction(
    Repeat::create(
      Sequence::create(
        DelayTime::create(time / count),
        CallFunc::create([=] () {
          Application->environment->generator->create();
        }),
        nullptr
      ), count
    )
  );

  Sound->play("pickup-energy");
}

/**
 *
 *
 *
 */
Up* Up::deepCopy()
{
  return new Up;
}
