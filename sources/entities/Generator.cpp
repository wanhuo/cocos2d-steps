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
  if((!this->bonus && this->index <= PLATES_FINISH) || (this->bonus && this->index <= PLATES_FINISH_BONUS))
  {
    if(++this->count > this->length)
    {
      this->count = 0;
      this->length = random(ROUTE_LENGTH_MIN, ROUTE_LENGTH_MAX);

      this->direction = !this->direction;

      if(this->direction)
      {
        this->x += 1.5f;
        this->z += 1.5f;
      }
      else
      {
        this->x -= 1.5f;
        this->z -= 1.5f;
      }
    }

    auto plate = static_cast<Plate*>(Application->environment->plates->_create());

    plate->setDirection(this->direction);

    plate->setPositionX(this->x - 0);
    plate->setPositionY(this->y - 1);
    plate->setPositionZ(this->z - 0);

    plate->setIndex(this->index);

    if(this->bonus)
    {
      if(this->index < 1)
      {
      }
      else if(this->index >= PLATES_FINISH_BONUS)
      {
          plate->setType(Plate::FINISH);
      }
      else
      {
        plate->setType(Plate::DIAMOND);

        if(this->conditions.s1 < 1)
        {
          plate->setType(Plate::CUB);

          this->conditions.s1 = random(2, 6);
        }
      }
    }
    else
    {
      if(this->resets == 0 && Application->environment->plates->count <= 1)
      {
        plate->setType(Plate::START);
      }

      if(this->index >= PLATES_START)
      {
        if(this->index == Application->counter->values.best)
        {
          plate->setType(Plate::BEST);
        }

        if(this->index == PLATES_FINISH)
        {
          plate->setType(Plate::FINISH);
        }
        else if(probably(PLATES_PROBABILITY))
        {
          if(this->conditions.s2 < 1 && probably(10))
          {
            plate->setType(Plate::SPIKES);

            this->conditions.s1 = 2;
            this->conditions.s2 = 2;
          }
          else if(this->conditions.s2 < 1 && probably(10))
          {
            plate->setType(Plate::UP);

            this->conditions.s1 = 2;
            this->conditions.s2 = 2;
          }
          else if(this->conditions.s2 < 1 && probably(10))
          {
            plate->setType(Plate::DOWN);

            this->conditions.s1 = 2;
            this->conditions.s2 = 2;
          }
          else if((this->length - this->count) > 1 && this->conditions.s1 < 1 && this->direction && probably(10))
          {
            plate->setType(Plate::MOVED1);

            this->length++;
            this->conditions.s2 = 2;
          }
          else if((this->length - this->count) > 1 && this->conditions.s1 < 1 && !this->direction && probably(10))
          {
            plate->setType(Plate::MOVED2);

            this->length++;
            this->conditions.s2 = 2;
          }
          else if(this->count >= this->length && this->conditions.s1 < 1 && this->direction && probably(10))
          {
            plate->setType(Plate::MOVED3);

            this->conditions.s2 = 2;
          }
          else if(this->count >= this->length && this->conditions.s1 < 1 && !this->direction && probably(10))
          {
            plate->setType(Plate::MOVED4);

            this->conditions.s2 = 2;
          }
          else if(this->count > 0 && this->count < this->length && this->conditions.s1 < 1 && probably(10))
          {
            plate->setType(Plate::MOVED5);

            this->conditions.s2 = 2;
          }
          else if(probably(2))
          {
            plate->setType(Plate::DIAMOND);
          }
          else if(probably(2))
          {
            plate->setType(Plate::CRYSTAL);
          }
          else if(probably(2))
          {
            plate->setType(Plate::ENERGY);
          }
          else if(probably(20))
          {
            plate->setType(Plate::STAR);
          }
          else if(probably(2))
          {
            //plate->setType(Plate::HEART);
          }
          else if(this->count > 0 && this->conditions.s1 < 1 && this->conditions.s2 < 1 && probably(20))
          {
            plate->setType(Plate::SAW);

            this->length++;
            this->length++;

            this->conditions.s1 = 2;
            this->conditions.s2 = 2;
          }
          else if(this->count > 0 && this->conditions.s1 < 1 && this->conditions.s2 < 1 && probably(20))
          {
            plate->setType(Plate::GATE);

            this->length++;
            this->length++;

            this->conditions.s1 = 2;
            this->conditions.s2 = 2;
          }
          else if(probably(5))
          {
            plate->setType(Plate::COPTER);

            this->conditions.s1 = 2;
            this->conditions.s2 = 2;
          }
        }
      }
    }

    plate->setPositionX(this->x - 0);
    plate->setPositionY(this->y - 1);
    plate->setPositionZ(this->z - 0);

    plate->setStartPositionX(this->x);
    plate->setStartPositionY(this->y);
    plate->setStartPositionZ(this->z);

    this->index++;

    this->conditions.s1--;
    this->conditions.s2--;
    this->conditions.s3--;

    if(this->direction)
    {
      this->x += 1.5f;
    }
    else
    {
      this->z -= 1.5f;
    }

    this->destroy(true);

    return plate;
  }

  return nullptr;
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
      if(Application->counter->values.start >= PLATES_SAVE)
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
  this->resets = 0;
  this->length = random(3, PLATES_START);

  this->conditions.s1 = 0;
  this->conditions.s2 = 0;
  this->conditions.s3 = 0;

  this->direction = true;
  this->bonus = false;

  Application->environment->stopAllActions();
  Application->environment->runAction(
    Repeat::create(
      CallFunc::create([=] () {
      this->create();
      }), PLATES_START
    )
  );
}
