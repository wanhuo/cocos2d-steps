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
TypeMoved4::TypeMoved4()
: TypeMoved()
{
}

TypeMoved4::~TypeMoved4()
{
}

/**
 *
 *
 *
 */
void TypeMoved4::start()
{
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
          auto action = EaseSineInOut::create(
            MoveBy::create(0.15, Vec3(-1.5, 0, 0))
          );

          this->runAction(action->clone());
          this->plate->moved = true;

          if(Application->environment->character->plates.current == this->plate && Application->environment->character->getManual() && Application->environment->character->state == Character::STATE_NORMAL)
          {
            Application->environment->character->plane->Node::runAction(action->clone(), 400);
          }
        }),
        DelayTime::create(0.6),
        CallFunc::create([=] () {
          auto action = EaseSineInOut::create(
            MoveBy::create(0.15, Vec3(1.5, 0, 0))
          );

          this->runAction(action->clone());
          this->runAction(
            Sequence::create(
              //DelayTime::create(0.15),
              CallFunc::create([=] () {
                this->plate->moved = false;
              }),
              nullptr
            )
          );

          if(Application->environment->character->plates.current == this->plate && Application->environment->character->getManual() && Application->environment->character->state == Character::STATE_NORMAL)
          {
            Application->environment->character->plane->Node::runAction(action->clone(), 400);
          }
        }),
        DelayTime::create(0.6),
        nullptr
      )
    )
  );
}

/**
 *
 *
 *
 */
TypeMoved4* TypeMoved4::deepCopy()
{
  return new TypeMoved4;
}
