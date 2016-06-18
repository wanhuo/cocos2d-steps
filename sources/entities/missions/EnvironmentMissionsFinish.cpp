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

  this->plane = PageView::create();
  this->plane->setDirection(PageView::Direction::HORIZONTAL);
  //this->plane->setBounceEnabled(true);
  this->plane->setCascadeOpacityEnabled(true);
  this->plane->setScrollBarEnabled(false);
  this->plane->setContentSize(Size(Application->getWidth(), 300));
  this->plane->setPosition(Vec2(0, -5));

  this->general = new EnvironmentMissionsFinishGeneral;

  this->plane->pushBackCustomItem(new EnvironmentMissionsFinishDaily);

  if(MissionsFactory::getInstance()->getCurrentMission())
  {
    this->plane->pushBackCustomItem(this->general);
  }

  if(Application->environment->missions.special)
  {
    this->plane->pushBackCustomItem(new EnvironmentMissionsFinishKetchapp);
  }

  this->addChild(this->plane);

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
  this->stopAllActions();
  this->setPosition3D(Vec3(Application->getFrustumWidth() / 2, Application->getFrustumHeight() / 2 - 3.5, 0));

  this->setOpacity(255);
  this->setCameraMask(32);

  this->plane->stopAllActions();
  this->plane->getInnerContainer()->stopAllActions();
  this->plane->stopAutoScroll();

  if(MissionsFactory::getInstance()->getCurrentMission() && !Application->counter->values.b.mission && !Application->counter->values.b.special && !Application->counter->values.b.daily)
  {
    this->plane->setTouchEnabled(true);
    this->plane->runAction(
      Sequence::create(
        DelayTime::create(2.0),
        CallFunc::create([=] () {
        this->plane->scrollToItem(1);
        }),
        nullptr
      )
    );
  }

  if(Application->counter->values.b.special)
  {
    this->plane->getInnerContainer()->setPosition(Vec2(-Application->getWidth() * ((MissionsFactory::getInstance()->getCurrentMission() || Application->counter->values.b.mission) ? 2 : 1), 0));
  }
  else if(Application->counter->values.b.daily)
  {
    this->plane->getInnerContainer()->setPosition(Vec2(0, 0));
  }
  else if(Application->counter->values.b.mission)
  {
    this->plane->getInnerContainer()->setPosition(Vec2(-Application->getWidth() * ((MissionsFactory::getInstance()->getCurrentMission() || Application->counter->values.b.mission) ? 1 : 0), 0));
  }
  else
  {
    if(Finish::getInstance()->missions->notificationKetchapp)
    {
      this->plane->getInnerContainer()->setPosition(Vec2(-Application->getWidth() * ((MissionsFactory::getInstance()->getCurrentMission() || Application->counter->values.b.mission) ? 2 : 1), 0));
    }
    else if(Finish::getInstance()->missions->notificationDaily)
    {
      this->plane->getInnerContainer()->setPosition(Vec2(0, 0));
    }
    else
    {
      this->plane->getInnerContainer()->setPosition(Vec2(-Application->getWidth() * ((MissionsFactory::getInstance()->getCurrentMission() || Application->counter->values.b.mission) ? 1 : 0), 0));
    }
  }

  Finish::getInstance()->missions->notificationKetchapp = false;
  Finish::getInstance()->missions->notificationDaily = false;
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
