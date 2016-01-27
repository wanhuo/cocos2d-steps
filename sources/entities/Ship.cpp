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
Ship::Ship()
: Cube("ship.obj")
{
  this->setScheduleUpdate(true);
}

Ship::~Ship()
{
}

/**
 *
 *
 *
 */
void Ship::onCreate()
{
  Cube::onCreate();

  /**
   *
   *
   *
   */
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
          Application->environment->createRipple(this->getPositionX(), this->getPositionZ());
        }),
        nullptr
      )
    )
  );

  float x = Application->environment->character->getPositionX() + random(-10.0, 10.0);
  float y = 0;
  float z = Application->environment->character->getPositionZ() + random(-10.0, 10.0);

  this->setPosition3D(Vec3(x, y, z));
  this->setRotation3D(Vec3(0, 0, 0));

  this->vector.x = random(-1.0, 1.0);
  this->vector.y = 0;
  this->vector.z = random(-1.0, 1.0);

  this->speed.x = random(0.01, 0.05);
  this->speed.y = 0;
  this->speed.z = random(0.01, 0.05);

  this->changeState(STATE_NORMAL);
}

void Ship::onDestroy(bool action)
{
  Cube::onDestroy(action);
}

/**
 *
 *
 *
 */
void Ship::onNormal()
{
}

void Ship::onCrash()
{
  this->stopAllActions();

  float x = this->getPositionX();
  float y = this->getPositionY();
  float z = this->getPositionZ();

  this->runAction(
    Spawn::create(
      Sequence::create(
        MoveBy::create(2.0, Vec3(0, -10, 0)),
        CallFunc::create([=] () {
          this->_destroy(true);
        }),
        nullptr
      ),
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
          for(int i = 0; i < 5; i++)
          {
            Application->environment->createParticle(x, y + 1, z);
          }
        }),
        nullptr
      ),
      RotateBy::create(0.5, Vec3(0, 0, 45)),
      nullptr
    )
  );
}

/**
 *
 *
 *
 */
void Ship::changeState(int state)
{
  if(this->state != state)
  {
    this->state = state;

    switch(this->state)
    {
      case STATE_NORMAL:
      this->onNormal();
      break;
      case STATE_CRASH:
      this->onCrash();
      break;
  }
  }
}

/**
 *
 *
 *
 */
void Ship::updateNormal(float time)
{
  auto x = this->getPositionX() + this->vector.x * this->speed.x;
  auto y = this->getPositionY();
  auto z = this->getPositionZ() + this->vector.z * this->speed.z;

  auto r = atan2(this->vector.x, this->vector.z) * 180 / M_PI - 90;

  this->setPosition3D(Vec3(x, y, z));
  this->setRotation3D(Vec3(this->getRotation3D().x, r, this->getRotation3D().z));

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    Entity3D* plate = static_cast<Entity3D*>(Application->environment->plates->element(i));

    if(this->getAABB().intersects(plate->getAABB()))
    {
      this->changeState(STATE_CRASH);
      break;
    }
  }

  if(!Application->cameras.d->isVisibleInFrustum(&this->getAABB()))
  {
    this->changeState(STATE_CRASH);
  }
}

void Ship::updateCrash(float time)
{
}

/**
 *
 *
 *
 */
void Ship::updateStates(float time)
{
  switch(this->state)
  {
    case STATE_NORMAL:
    this->updateNormal(time);
    break;
    case STATE_CRASH:
    this->updateCrash(time);
    break;
  }
}

/**
 *
 *
 *
 */
void Ship::update(float time)
{
  Cube::update(time);

  /**
   *
   *
   *
   */
  this->updateStates(time);
}

/**
 *
 *
 *
 */
Ship* Ship::deepCopy()
{
  return new Ship;
}
