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
Whale::Whale(Environment* environment)
: Fish("whale.obj", environment->plane)
{
  this->setTexture("whale-texture.png");
  this->setScheduleUpdate(true);
}

Whale::~Whale()
{
}

/**
 *
 *
 *
 */
void Whale::onCreate()
{
  Fish::onCreate();

  /**
   *
   *
   *
   */
  auto plate = Application->environment->character->plates.current;

  auto x = plate->getPositionX();
  auto z = plate->getPositionZ();

  this->setPosition3D(Vec3(x - 2, this->getPositionY(), z));

  Sound->play("whale");
}

void Whale::onDestroy(bool action)
{
  Fish::onDestroy(action);

  /**
   *
   *
   *
   */
  this->changeState(STATE_SLEEP);
}

/**
 *
 *
 *
 */
void Whale::onSleep()
{
}

void Whale::onNormal()
{
  this->_create();
}

/**
 *
 *
 *
 */
void Whale::changeState(int state)
{
  if(this->state != state)
  {
    this->state = state;

    switch(this->state)
    {
      case STATE_SLEEP:
      this->onSleep();
      break;
      case STATE_NORMAL:
      this->onNormal();
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Whale::updateSleep(float time)
{
}

void Whale::updateNormal(float time)
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  this->collider->setPosition3D(this->getPosition3D());
  this->collider->setScaleX(2);
  this->collider->setScaleY(2);
  this->collider->setScaleZ(2);

  auto box = this->collider->getAABB();

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Entity3D*>(Application->environment->plates->element(i));

    if(box.intersects(plate->getAABB()))
    {
      plate->_destroy(true);
    }
  }

  if(this->getAABB().intersects(Application->environment->character->getAABB()))
  {
    Application->environment->character->_destroy(true);
    Application->changeState(Game::LOSE);
  }
}

/**
 *
 *
 *
 */
void Whale::updateStates(float time)
{
  switch(this->state)
  {
    case STATE_SLEEP:
    this->updateSleep(time);
    break;
    case STATE_NORMAL:
    this->updateNormal(time);
    break;
  }
}

/**
 *
 *
 *
 */
void Whale::update(float time)
{
  Fish::update(time * 2);

  /**
   *
   *
   *
   */
  this->updateStates(time);
}
