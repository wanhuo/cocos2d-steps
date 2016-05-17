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
EnvironmentMissionsNotify::EnvironmentMissionsNotify()
: BackgroundColor(nullptr, Color4B(255.0, 255.0, 255.0, 255.0))
{
  this->setIgnoreAnchorPointForPosition(false);

  this->setAnchorPoint(Vec2(0.5, 1.0));
  this->setContentSize(Size(Application->getWidth(), 100));
  this->setPosition(Application->getWidth() / 2, Application->getHeight() + 100);

  this->text = new Text("missions-complete", this, true);
  this->text->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);

  Director::getInstance()->setNotificationNode(this);

  this->setCameraMask(4);
}

EnvironmentMissionsNotify::~EnvironmentMissionsNotify()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsNotify::onCreate()
{
  BackgroundColor::onCreate();

  /**
   *
   *
   *
   */
  this->runAction(
    Sequence::create(
      MoveBy::create(0.2, Vec2(0, -100)),
      DelayTime::create(1.0),
      MoveBy::create(0.2, Vec2(0, 100)),
      CallFunc::create([=] () {
      this->_destroy(true);
      }),
      nullptr
    )
  );
}

void EnvironmentMissionsNotify::onDestroy(bool action)
{
  BackgroundColor::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsNotify::onEnter()
{
  BackgroundColor::onEnter();
}

void EnvironmentMissionsNotify::onExit()
{
  BackgroundColor::onExit();
}
