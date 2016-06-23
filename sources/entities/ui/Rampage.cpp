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

Rampage::Rampage(Node* parent)
: Spine("insane.json", "insane.atlas", 1.0, parent)
{
  this->animations.animation = {1, "animation", false};

  this->setCameraMask(4);
}

Rampage::~Rampage()
{
}

/**
 *
 *
 *
 */
void Rampage::onCreate()
{
  Spine::onCreate();

  /**
   *
   *
   *
   */
  this->setOpacity(0);
  this->setPosition(Application->getCenter().x, Application->getHeight() - 380);

  this->clearTracks();
  this->setAnimation(this->animations.animation);
  this->setTimeScale(2.0);

  this->stopAllActions();

  this->runAction(
    FadeIn::create(2.0)
  );
}

void Rampage::onDestroy(bool action)
{
  Spine::onDestroy(action);
}

/**
 *
 *
 *
 */
void Rampage::onAnimationFinish(int index)
{
  Spine::onAnimationFinish(index);

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      FadeOut::create(0.5),
      CallFunc::create([=] () {
      this->_destroy();
      }),
      nullptr
    )
  );
}
