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
Route::Route(Environment* environment, Generator* generator)
{
  this->environment = environment;
  this->generator = generator;
}

Route::~Route()
{
}

/**
 *
 *
 *
 */
void Route::spawn(Route* route)
{
  if(!route)
  {
    bool n = false;

    for(int i = 0; i < this->environment->plates->count; i++)
    {
      auto plate = this->environment->plates->element(i);

      float x1 = round(plate->getPositionX());
      float y1 = round(plate->getPositionY());
      float z1 = round(plate->getPositionZ());

      float x2 = round(this->x);
      float y2 = round(this->y);
      float z2 = round(this->z);

      if(x1 == x2 && z1 == z2)
      {
        this->disable = true;
        break;
      }
    }

    if(this->disable) return;

    auto plate = static_cast<Plate*>(this->environment->plates->_create());

    plate->setPositionX(this->x);
    plate->setPositionY(this->y - 5);
    plate->setPositionZ(this->z);

    if(this->environment->plates->count >= 5)
    {
      if(this->s2 < 1 && probably(10))
      {
        plate->setType(Plate::TYPE_SPIKES);
        this->s1 = 2;
      }
      else if((this->length - this->counter) > 1 && this->s1 < 1 && this->direction && probably(10))
      {
        plate->setType(Plate::TYPE_MOVED_1);
        this->length++;
        this->s2 = 2;
      }
      else if((this->length - this->counter) > 1 && this->s1 < 1 && !this->direction && probably(10))
      {
        plate->setType(Plate::TYPE_MOVED_2);
        this->length++;
        this->s2 = 2;
      }
      else if(this->counter >= this->length && this->s1 < 1 && this->direction && probably(10))
      {
        plate->setType(Plate::TYPE_MOVED_3);
        this->s2 = 2;
      }
      else if(this->counter >= this->length && this->s1 < 1 && !this->direction && probably(10))
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
      else if(probably(20))
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

    if(this->environment->plates->count <= 1)
    {
      plate->setTexture("plate-texture-2.png");
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
  }
  else
  {
    this->x = route->x;
    this->y = route->y;
    this->z = route->z;

    this->direction = !route->direction;
    
    this->y += 0.5f;
    
    if(this->direction)
    {
      this->x += 1.5f;
    }
    else
    {
      this->z -= 1.5f;
    }

    this->counter = 0;
    this->length = random(2, 5);
  }

  this->counter++;

  if(this->counter > this->length)
  {
    this->counter = 0;
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
    this->generator->onCreateRoute(this);//this->disable = true;
    
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
