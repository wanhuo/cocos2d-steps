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
R::R()
: Entity3D("diamond.obj", false)
{
  this->setScheduleUpdate(true);
}

R::~R()
{
}

/**
 *
 *
 *
 */
void R::onCreate()
{
  Entity3D::onCreate();

  /**
   *
   *
   *
   */
  this->setTexture(Application->environment->getTextureState1());

  this->setColor(Color3B(0.0, 243.0, 120.0));

  this->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->setScale(0.2);

  this->direction = Vec3(random(0.2, 0.5) * (probably(50) ? 1 : -1), 1.0, random(0.2, 0.5) * (probably(50) ? 1 : -1));
  this->speed = Vec3(random(0.02, 0.1), random(0.1, 0.2), random(0.02, 0.1));

  this->runAction(
    RepeatForever::create(
      RotateBy::create(random(1.0, 2.0), Vec3(360.0, 360.0, 360.0))
    )
  );
}

void R::onDestroy(bool action)
{
  Entity3D::onDestroy(action);
}

/**
 *
 *
 *
 */
void R::animation1()
{
  this->animation = ANIMATION_1;
}

void R::animation2()
{
  this->animation = ANIMATION_2;

  auto x = random(0.0f, Application->getFrustumWidth());
  auto y = random(0.0f, Application->getFrustumHeight());
  auto z = 0;

  this->stopAllActions();
  this->setPosition3D(Vec3(x, y, z));
  this->setRotation3D(Vec3(0, 0, 0));
  this->setScale(0);

  this->runAction(
    Sequence::create(
      DelayTime::create(random(0.0, 1.0)),
      EaseBounceOut::create(
        ScaleTo::create(0.5, 0.8)
      ),
      CallFunc::create([=] () {
      Sound->play("pickup-diamond");
      }),
      DelayTime::create(1.0),
      EaseSineIn::create(
        MoveTo::create(random(0.5, 1.0), Vec3(Application->getFrustumWidth() - 0.4, Application->getFrustumHeight() - 0.7, 0))
      ),
      CallFunc::create([=] () {
      Sound->play("pickup-diamond");

      Application->counter->add(2);
      Application->counter->icon->runAction(
        Sequence::create(
          ScaleTo::create(0.0, 0.9),
          ScaleTo::create(0.1, 0.8),
          nullptr
        )
      );
      }),
      CallFunc::create([=] () {
      this->_destroy();
      }),
      nullptr
    )
  );

  this->runAction(
    RepeatForever::create(
      RotateBy::create(5.0, Vec3(0.0, 360.0, 0.0))
    )
  );
}

/**
 *
 *
 *
 */
void R::update(float time)
{
  if(this->animation == ANIMATION_1)
  {
    auto x = this->getPositionX();
    auto y = this->getPositionY();
    auto z = this->getPositionZ();

   /* x += this->direction.x * this->speed.x * Present::getInstance()->time;
    y += this->direction.y * this->speed.y * Present::getInstance()->time;
    z += this->direction.z * this->speed.z * Present::getInstance()->time;

    this->setPosition3D(Vec3(x, y, z));

    this->speed.y -= 0.008 * Present::getInstance()->time;*/
  }
}

/**
 *
 *
 *
 */
R* R::deepCopy()
{
  return new R;
}
