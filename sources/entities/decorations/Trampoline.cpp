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
Trampoline::Trampoline(Node* parent)
: Decoration("", parent)
{
  this->removable = false;
}

Trampoline::~Trampoline()
{
}

/**
 *
 *
 *
 */
void Trampoline::onPickup()
{
  auto element = Application->environment->character->plates.current;

  int l = 0;
  int r = 0;
  int count = 5;
  int remove = 1;

  float time = 0.1;

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
      if(element->type == Plate::FINISH)
      {
        break;
      }
    }

    if(!element || element == NULL || element->behavior == Plate::DYNAMIC || element->type == Plate::SPIKES || element->type == Plate::GATE || element->type == Plate::SAW || element->type == Plate::DOWN || element->type == Plate::TRAP)
    {
      if(i >= count - 1)
      {
        Application->environment->generator->create(true);
        {
          count++;
          remove++;
        }
      }
    }

    element->runAction(
      Sequence::create(
        DelayTime::create(time * i),
        CallFunc::create(CC_CALLBACK_0(Plate::onCount, element)),
        CallFunc::create(CC_CALLBACK_0(Character::onSound, Application->environment->character, "character-jump")),
        CallFunc::create(CC_CALLBACK_0(Counter::onCount, Application->counter)),
        nullptr
      )
    );
  }

  Application->environment->character->setManual(false);
  Application->environment->character->plane->runAction(
    Sequence::create(
      ScaleTo::create(time * count / 2, 0.8, 1.4, 0.8),
      ScaleTo::create(time * count / 2, 1.0, 1.0, 1.0),
      nullptr
    )
  );
  Application->environment->character->runAction(
    Spawn::create(
      Sequence::create(
        CallFunc::create([=] () {
           Application->environment->plane->runAction(
            EaseSineIn::create(
              MoveBy::create(time* count / 2, Vec3(-0.75 * l, 0, 0.75 * r))
            )
          );
        }),
        EaseSineIn::create(
          MoveBy::create(time * count / 2, Vec3(0.75 * l, 1.0 + 0.2 * remove, -0.75 * r))
        ),
        CallFunc::create([=] () {
          Application->environment->plane->runAction(
            EaseSineIn::create(
              MoveBy::create(time * count / 2, Vec3(-0.75 * l, 0, 0.75 * r))
            )
          );
        }),
        EaseSineIn::create(
          MoveBy::create(time * count / 2, Vec3(0.75 * l, -1.0 - 0.2 * remove, -0.75 * r))
        ),
        CallFunc::create([=] () {
          Application->environment->character->setManual(true);
          Application->environment->character->plates.current = element;
          Application->environment->character->onLandSuccessful(Character::NONE, element);

          if(Application->environment->numberOfRunningActions() < 2)
          {
            Application->environment->runAction(
              Shake::create(0.2, 0.2)
            );
          }
        }),
        nullptr
      ),
      Sequence::create(
        RotateGlobalBy::create(time * count, Vec3(0, 90 * count * (probably(50) ? 1 : -1), 0)),
        nullptr
      ),
      nullptr
    )
  );
  Application->environment->character->runAction(
    Repeat::create(
      Sequence::create(
        DelayTime::create(time),
        CallFunc::create([=] () {
          Application->environment->generator->create(true);
        }),
        nullptr
      ), count - remove
    )
  );

  Sound->play("up");
}
