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
Dust::Dust()
: Entity("dust.png")
{
  this->setCameraMask(4);
  this->setScheduleUpdate(true);
}

Dust::~Dust()
{
}

/**
 *
 *
 *
 */
void Dust::onCreate()
{
  Entity::onCreate();

  /**
   *
   *
   *
   */
  auto x = random(-Application->getWidth(), Application->getWidth()*2);
  auto y = random(Application->getHeight(), Application->getHeight()-300);

  this->setPosition(x, y);
  this->setOpacity(0);
  this->setScale(0);

  this->vector.x = random(-1.0, 1.0);
  this->vector.y = random(-1.0, 1.0);

  this->speed.x = random(0.1, 0.9);
  this->speed.y = random(0.1, 0.9);

  this->runAction(
    Spawn::create(
      FadeIn::create(random(0.0, 2.0)),
      ScaleTo::create(random(0.0, 2.0), random(0.0, 1.5)),
      nullptr
    )
  );
}

void Dust::onDestroy(bool action)
{
  Entity::onDestroy(action);

  /**
   *
   *
   *
   */
}

/**
 *
 *
 *
 */
void Dust::update(float time)
{
  auto x = this->getPositionX() + this->vector.x * this->speed.x;
  auto y = this->getPositionY() + this->vector.y * this->speed.y;

  this->setPosition(x, y);

  this->vector.x += random(-0.1, 0.1);
  this->vector.y += random(-0.1, 0.1);

  if(this->getPositionY() < 0)
  {
    this->_destroy(true);
  }
}

/**
 *
 *
 *
 */
Dust* Dust::deepCopy()
{
  return new Dust;
}
