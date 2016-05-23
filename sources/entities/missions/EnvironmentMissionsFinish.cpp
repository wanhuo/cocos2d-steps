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
EnvironmentMissionsFinish::EnvironmentMissionsFinish(Node* parent)
: BackgroundColor(Application, Color4B(71.0, 132.0, 164.0, 255.0))
{
  this->setIgnoreAnchorPointForPosition(false);

  this->setCascadeOpacityEnabled(true);
  this->setAnchorPoint(Vec2(0.5, 0.5));
  this->setContentSize(Size(Application->getWidth(), 210));
  this->setScale(0.015);

  this->plane = cocos2d::ui::ListView::create();
  this->plane->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
  this->plane->setBounceEnabled(true);
  this->plane->setScrollBarEnabled(false);
  this->plane->setContentSize(Size(Application->getWidth(), 300));
  this->plane->setPosition(Vec2(0, -45));
  this->plane->setMagneticType(cocos2d::ui::ListView::MagneticType::CENTER);

  this->addChild(this->plane);

  this->general = new EnvironmentMissionsFinishGeneral;

  this->plane->pushBackCustomItem(new EnvironmentMissionsFinishDaily);
  this->plane->pushBackCustomItem(this->general);

  if(Application->environment->missions.special)
  {
    this->plane->pushBackCustomItem(new EnvironmentMissionsFinishKetchapp);
  }

  this->_destroy();
}

EnvironmentMissionsFinish::~EnvironmentMissionsFinish()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsFinish::onCreate()
{
  BackgroundColor::onCreate();

  /**
   *
   *
   *
   */
  this->setPosition3D(Vec3(Application->getFrustumWidth() / 2, Application->getFrustumHeight() / 2 - 3.5, 0));

  this->setOpacity(255);
  this->setCameraMask(32);

  this->plane->setTouchEnabled(true);
  this->plane->runAction(
    Sequence::create(
      DelayTime::create(2.0),
      CallFunc::create([=] () {
      this->plane->scrollToItem(1, Vec2(0, 0), Vec2(0, 0));
      }),
      nullptr
    )
  );

  if(this->notificationKetchapp)
  {
    this->plane->getInnerContainer()->setPosition(Vec2(-Application->getWidth() * 2, 0));
  }
  else if(this->notificationDaily)
  {
    this->plane->getInnerContainer()->setPosition(Vec2(0, 0));
  }
  else
  {
    this->plane->getInnerContainer()->setPosition(Vec2(-Application->getWidth(), 0));
  }

  this->notificationKetchapp = false;
  this->notificationDaily = false;
}

void EnvironmentMissionsFinish::onDestroy(bool action)
{
  BackgroundColor::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsFinish::onEnter()
{
  BackgroundColor::onEnter();
}

void EnvironmentMissionsFinish::onExit()
{
  BackgroundColor::onExit();
}
