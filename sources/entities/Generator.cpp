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
Plate* Generator::create()
{
    auto plate = static_cast<Plate*>(Application->environment->plates->_create());

    plate->setPositionX(this->x);
    plate->setPositionY(this->y - 1);
    plate->setPositionZ(this->z);

    plate->setIndex(this->index);

    if(this->index >= PLATES_START)
    {
      if(this->index == Application->counter->values.best)
      {
        plate->setType(Plate::BEST);
      }
      else if(this->s2 < 1 && probably(10))
      {
        plate->setType(Plate::SPIKES);
        this->s1 = 2;
        this->s2 = 2;
      }
      else if(this->s2 < 1 && probably(10))
      {
        plate->setType(Plate::UP);
        this->s1 = 2;
        this->s2 = 2;
      }
      else if(this->s2 < 1 && probably(10))
      {
        plate->setType(Plate::DOWN);
        this->s1 = 2;
        this->s2 = 2;
      }
      else if((this->length - this->count) > 1 && this->s1 < 1 && this->direction && probably(10))
      {
        plate->setType(Plate::MOVED1);
        this->length++;
        this->s2 = 2;
      }
      else if((this->length - this->count) > 1 && this->s1 < 1 && !this->direction && probably(10))
      {
        plate->setType(Plate::MOVED2);
        this->length++;
        this->s2 = 2;
      }
      else if(this->count >= this->length && this->s1 < 1 && this->direction && probably(10))
      {
        plate->setType(Plate::MOVED3);
        this->s2 = 2;
      }
      else if(this->count >= this->length && this->s1 < 1 && !this->direction && probably(10))
      {
        plate->setType(Plate::MOVED4);
        this->s2 = 2;
      }
      else if(this->s1 < 1 && probably(10))
      {
        plate->setType(Plate::MOVED5);
        this->s2 = 2;
      }
      else if(probably(200))
      {
        plate->setType(Plate::DIAMOND);
      }
      else if(probably(2) && false)
      {
        plate->setType(Plate::CRYSTAL);
      }
      else if(probably(20))
      {
        plate->setType(Plate::ENERGY);
      }
      else if(probably(2))
      {
        //plate->setType(Plate::TYPE_STAR);
      }
      else if(probably(2))
      {
        //plate->setType(Plate::TYPE_HEART);
      }
      else if(this->count > 1 && this->s3 < 0 && probably(50) && false)
      {
        this->s3 = 10;

        this->length++;
        this->length++;

        auto p = static_cast<Plate*>(Application->environment->plates->_create());
        p->setIndex(this->index);

        if(this->direction)
        {
          p->setPositionX(this->x);
          p->setPositionY(this->y - 1);
          p->setPositionZ(this->z - 3.0);
        }
        else
        {
          p->setPositionX(this->x + 3.0);
          p->setPositionY(this->y - 1);
          p->setPositionZ(this->z);
        }

        p->setType(Plate::CANNON);

        p->runAction(
          Spawn::create(
            EaseBounceOut::create(
              MoveBy::create(0.5, Vec3(0, 1, 0))
            ),
            nullptr
          )
        );

        if(this->direction)
        {
          p->decoration->setRotation3D(Vec3(0, -90, 0));
        }
        else
        {
          p->decoration->setRotation3D(Vec3(0, 180, 0));
        }
      }
    }

    plate->setPositionX(this->x);
    plate->setPositionY(this->y - 1);
    plate->setPositionZ(this->z);

    plate->setStartPositionX(this->x);
    plate->setStartPositionY(this->y);
    plate->setStartPositionZ(this->z);

    plate->runAction(
      Spawn::create(
        EaseBounceOut::create(
          MoveBy::create(0.5, Vec3(0, 1, 0))
        ),
        nullptr
      )
    );

    this->index++;

    this->s1--;
    this->s2--;
    this->s3--;

    if(Application->environment->plates->count <= 1)
    {
      plate->setTexture("plate-texture-state-2.png");

      plate->decoration = static_cast<Decoration*>(Application->environment->start->_create());
      plate->decoration->setTexture("start-texture.png");
      plate->decoration->setPlate(plate, true);
      plate->decoration->setRotation3D(Vec3(0, 0, 0));
    }

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
      this->length = random(ROUTE_LENGTH_MIN, ROUTE_LENGTH_MAX);

      this->direction = !this->direction;

      if(this->direction)
      {
        this->z += 1.5f;
      }
      else
      {
        this->x -= 1.5f;
      }

      if(this->direction)
      {
        this->x += 1.5f;
      }
      else
      {
        this->z -= 1.5f;
      }
    }

    plate->direction = this->direction;

    this->destroy(true);

    return plate;
}

void Generator::destroy(bool manual)
{
  switch(Application->state)
  {
    case Game::GAME:
    if(manual)
    {
      if(Application->environment->character->plates.current)
      {
        for(int i = 0; i < Application->environment->plates->count; i++)
        {
          Plate* element = static_cast<Plate*>(Application->environment->plates->element(i));

          if(element->getIndex() < Application->environment->character->plates.current->getIndex() - 5)
          {
            element->remove();
          }
        }
      }
    }
    else
    {
      if(Application->counter->values.current >= PLATES_SAVE)
      {
        Plate* plate = nullptr;

        for(int i = 0; i < Application->environment->plates->count; i++)
        {
          Plate* element = static_cast<Plate*>(Application->environment->plates->element(i));

          if(!plate)
          {
            plate = element;
          }
          else
          {
            if(element->getIndex() < plate->getIndex())
            {
              plate = element;
            }
          }
        }

        if(plate)
        {
          plate->remove();
        }
      }
    }
    break;
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

  this->index = 0;
  this->count = 0;
  this->length = random(3, PLATES_START);

  this->s1 = 0;
  this->s2 = 0;

  this->direction = true;

  Application->environment->stopAllActions();
  Application->environment->runAction(
    Repeat::create(
      CallFunc::create([=] () {
      this->create();
      }), PLATES_START
    )
  );
  /*Application->environment->runAction(
    RepeatForever::create(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create(CC_CALLBACK_0(Generator::destroy, this, false)),
        nullptr
      )
    )
  );*/
}
