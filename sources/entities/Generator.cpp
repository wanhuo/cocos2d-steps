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
Generator::Generator()
{
}

Generator::~Generator()
{
}

/**
 *
 *
 *
 */
void Generator::create()
{
    bool n = false;

    auto plate = static_cast<Plate*>(Application->environment->plates->_create());

    plate->setPositionX(this->x);
    plate->setPositionY(this->y - 5);
    plate->setPositionZ(this->z);

    if(Application->environment->plates->count >= 5)
    {
      if(this->s2 < 1 && probably(2))
      {
        plate->setType(Plate::TYPE_SPIKES);
        this->s1 = 2;
      }
      else if((this->length - this->count) > 1 && this->s1 < 1 && this->direction && probably(2))
      {
        plate->setType(Plate::TYPE_MOVED_1);
        this->length++;
        this->s2 = 2;
      }
      else if((this->length - this->count) > 1 && this->s1 < 1 && !this->direction && probably(50))
      {
        plate->setType(Plate::TYPE_MOVED_2);
        this->length++;
        this->s2 = 2;
      }
      else if(this->count >= this->length && this->s1 < 1 && this->direction && probably(2))
      {
        plate->setType(Plate::TYPE_MOVED_3);
        this->s2 = 2;
      }
      else if(this->count >= this->length && this->s1 < 1 && !this->direction && probably(2))
      {
        plate->setType(Plate::TYPE_MOVED_4);
        this->s2 = 2;
      }
      else if(probably(2))
      {
        plate->setType(Plate::TYPE_DIAMOND);
      }
      else if(probably(2))
      {
        plate->setType(Plate::TYPE_CRYSTAL);
      }
      else if(probably(2))
      {
        plate->setType(Plate::TYPE_ENERGY);
      }
      else if(probably(2))
      {
        //plate->setType(Plate::TYPE_STAR);
      }
      else if(probably(2))
      {
        //plate->setType(Plate::TYPE_HEART);
      }
      else if(this->count > 1 && probably(20)&&false)
      {
        this->length++;
        this->length++;

        auto p = static_cast<Plate*>(Application->environment->plates->_create());
        auto c = static_cast<Plate*>(Application->environment->cannons->_create());

        if(this->direction)
        {
          p->setPositionX(this->x);
          p->setPositionY(this->y - 5);
          p->setPositionZ(this->z + (3.0 * (probably(50) ? 1 : -1)));
          c->setPositionX(this->x);
          c->setPositionY(this->y - 5);
          c->setPositionZ(this->z + (3.0 * (probably(50) ? 1 : -1)));
        }
        else
        {
          p->setPositionX(this->x + (3.0 * (probably(50) ? 1 : -1)));
          p->setPositionY(this->y - 5);
          p->setPositionZ(this->z);
          c->setPositionX(this->x + (3.0 * (probably(50) ? 1 : -1)));
          c->setPositionY(this->y - 5);
          c->setPositionZ(this->z);
        }
    p->setOpacity(0);
    c->setOpacity(0);

    p->runAction(
      Spawn::create(
        EaseSineOut::create(
          MoveBy::create(0.5, Vec3(0, 5, 0))
        ),
        FadeTo::create(0.5, 255),
        nullptr
      )
    );

    c->runAction(
      Spawn::create(
        EaseSineOut::create(
          MoveBy::create(0.5, Vec3(0, 5, 0))
        ),
        FadeTo::create(0.5, 255),
        nullptr
      )
    );
      }
    }

    plate->setPositionX(this->x);
    plate->setPositionY(this->y - 5);
    plate->setPositionZ(this->z);

    plate->startPositionX = this->x;
    plate->startPositionY = this->y;
    plate->startPositionZ = this->z;

    plate->setOpacity(0);

    plate->runAction(
      Spawn::create(
        EaseSineOut::create(
          MoveBy::create(0.5, Vec3(0, 5, 0))
        ),
        FadeTo::create(0.5, 255),
        nullptr
      )
    );

    this->s1--;
    this->s2--;

    if(Application->environment->plates->count <= 1)
    {
      plate->setTexture("plate-texture-state-2.png");
    }

    //this->y += 0.5f;

    if(this->direction)
    {
      this->x += 1.5f;
    }
    else
    {
      this->z -= 1.5f;
    }

    if(++this->count > this->length)
    {
      this->count = 0;
      this->length = random(2, 10);

      this->direction = !this->direction;
      //plates->last()->setColor(Color3B(0, 0, 255));
      
      if(this->direction)
      {
        this->z += 1.5f;
      }
      else
      {
        this->x -= 1.5f;
      }
      this->y -= 0.5f;
      
      this->y += 0.5f;
      if(this->direction)
      {
        this->x += 1.5f;
      }
      else
      {
        this->z -= 1.5f;
      }
    }
}

void Generator::destroy()
{
  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates->element(i));

    if(plate->getPositionZ() - Application->environment->character->getPositionZ() > MAX_FREE_PLATES || Application->environment->character->getPositionX() - plate->getPositionX() > MAX_FREE_PLATES)
    {
      plate->runAction(
        Spawn::create(
          Sequence::create(
            EaseSineInOut::create(
              MoveBy::create(0.2, Vec3(0, 1.0, 0))
            ),
            EaseSineInOut::create(
              MoveBy::create(0.4, Vec3(0, -6.0, 0))
            ),
            CallFunc::create([=] () {
              plate->_destroy(true);
            }),
            nullptr
          ),
          Sequence::create(
            DelayTime::create(0.3),
            FadeOut::create(0.1),
            nullptr
          ),
          nullptr
        )
      );

      plate->clearDecoration(false, true);
    }
  }
}

/**
 *
 *
 *
 */
void Generator::clear()
{
  this->x = 0;
  this->y = 0;
  this->z = 0;

  this->count = 0;
  this->length = 5;

  this->s1 = 0;
  this->s2 = 0;

  this->direction = true;

  Application->environment->runAction(
    Repeat::create(
      CallFunc::create([=] () {
      this->create();
      }), MAX_PLATES
    )
  );
}
