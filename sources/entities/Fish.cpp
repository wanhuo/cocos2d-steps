/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @version of cocos2d is 3.5
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
Fish::Fish()
: Cube("fish.obj")
{
  this->collider = new Entity3D("cube.obj", Application->environment->plane);
  this->shadow = new Shadow("fish-shadow.obj", Application->environment->plane);

  this->setTexture("fish-texture-3.png");
  this->setScheduleUpdate(true);
}

Fish::Fish(const char* file, Node* parent)
: Cube(file, parent)
{
  this->collider = new Entity3D("cube.obj", Application->environment->plane);
  this->setScheduleUpdate(true);
}

Fish::~Fish()
{
}

/**
 *
 *
 *
 */
void Fish::onCreate()
{
  Cube::onCreate();

  auto position = false;
  auto count = 5;

  while(!position && count > 0)
  {
    auto environment = Application->environment->position();
    auto collision = false;

    auto x = environment.x - 0.0;
    auto y = environment.y - 4.0;
    auto z = environment.z - 0.0;

    this->setPositionX(x);
    this->setPositionY(y);
    this->setPositionZ(z);

    this->collider->setPosition3D(this->getPosition3D());
    this->collider->setScaleX(10);
    this->collider->setScaleY(10);
    this->collider->setScaleZ(2);

    auto box = this->collider->getAABB();

    for(int i = 0; i < Application->environment->plates->count; i++)
    {
      if(box.intersects(static_cast<Entity3D*>(Application->environment->plates->element(i))->getAABB()))
      {
        collision = true;
        break;
      }
    }

    if(!Application->cameras.d->isVisibleInFrustum(&this->getAABB()))
    {
      collision = true;
    }

    if(!collision)
    {
      position = true;
    }

    count--;
  }

  if(position)
  {
    this->speed.x = 4.8;
    this->speed.y = 15.0;

    this->vector.x = 1.0;
    this->vector.y = 1.0;

    this->ripple1 = false;
    this->ripple2 = false;
  }
  else
  {
    this->runAction(
      Sequence::create(
        DelayTime::create(0.1),
        CallFunc::create([=] () {
          this->_destroy(true);
        }),
        nullptr
      )
    );
  }
}

void Fish::onDestroy(bool action)
{
  Cube::onDestroy(action);
}

/**
 *
 *
 *
 */
void Fish::update(float time)
{
  Cube::update(time);

  /**
   *
   *
   *
   */
  auto x = this->getPositionX() + this->vector.x * this->speed.x * time;
  auto y = this->getPositionY() + this->vector.y * this->speed.y * time;
  auto z = this->getPositionZ();

  auto r = atan2(this->vector.x, this->vector.y) * 180 / M_PI - 90;

  this->setPositionX(x);
  this->setPositionY(y);
  this->setPositionZ(z);

  this->setRotation3D(Vec3(0, 0, r));

  this->vector.y -= 1.2 * time;

  if(y <= -150.0)
  {
    this->_destroy(true);
  }

  if(!this->ripple1)
  {
    if(this->vector.y > 0)
    {
      if(y >= 0)
      {
  Sound->play("water-splash-" + patch::to_string(random(1, 7)));
        this->ripple1 = true;
        Application->environment->createRipple(x, z, 0.5);

        for(int i = 0; i < 5; i++)
        {
          auto particle = Application->environment->createParticle(x, y+1, z);
        }
      }
    }
  }

  if(!this->ripple2)
  {
    if(this->vector.y < 0)
    {
      if(y <= 0)
      {
        
  Sound->play("water-splash-" + patch::to_string(random(1, 7)));
        this->ripple2 = true;
        Application->environment->createRipple(x, z, 0.5);

        for(int i = 0; i < 5; i++)
        {
          auto particle = Application->environment->createParticle(x, y+1, z);
        }
      }
    }
  }
}

/**
 *
 *
 *
 */
Fish* Fish::deepCopy()
{
  return new Fish;
}
