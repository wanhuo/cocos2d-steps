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
Ripple::Ripple()
: Entity3D()
{
  this->setLightMask(2);

  for(int i = 0; i < 2; i++)
  {
    this->ripples[i] = new Entity3D("ripple.obj", this);
  }
}

Ripple::~Ripple()
{
}

/**
 *
 *
 *
 */
void Ripple::onCreate()
{
  Entity3D::onCreate();

  /**
   *
   *
   *
   */
  auto rotate = random(0.0, 360.0);

  for(int i = 0; i < 2; i++)
  {
    auto ripple = this->ripples[i]->_create();

    ripple->setPosition3D(Vec3(0, 0, 0));
    ripple->setRotation3D(Vec3(0, rotate, 0));

    ripple->setScaleX(0);
    ripple->setScaleZ(0);

    ripple->setOpacity(255);

    ripple->runAction(
      Spawn::create(
        Sequence::create(
          ScaleTo::create(0.5, 0.2 + (i * 0.5), 1.0, 0.2 + (i * 0.5)),
          ScaleTo::create(1.5, 0.8 + (i * 0.5), 1.0, 0.8 + (i * 0.5)),
          CallFunc::create([=] () {
            this->_destroy(true);
          }),
          nullptr
        ),
        Sequence::create(
          DelayTime::create(1.0),
          FadeOut::create(1.0),
          nullptr
        ),
        nullptr
      )
    );

    rotate += 120;
  }
}

void Ripple::onDestroy(bool action)
{
  Entity3D::onDestroy(action);

  /**
   *
   *
   *
   */
  for(int i = 0; i < 2; i++)
  {
    this->ripples[i]->_destroy();
  }
}

/**
 *
 *
 *
 */
Ripple* Ripple::deepCopy()
{
  return new Ripple;
}
