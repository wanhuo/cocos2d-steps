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
EnvironmentMissionsPopup::EnvironmentMissionsPopup(Node* parent)
: BackgroundColor(parent, Color4B(71.0, 132.0, 164.0, 255.0))
{
  this->setIgnoreAnchorPointForPosition(false);

  this->setAnchorPoint(Vec2(0.5, 1.0));
  this->setContentSize(Size(650, 400));
  this->setPosition(0, Application->getHeight() - 120 - 1000);

  this->background = new BackgroundColor(this, Color4B(95.0, 165.0, 196.0, 255.0));
  this->background->setIgnoreAnchorPointForPosition(false);
  this->background->setContentSize(Size(400, 80));
  this->background->setAnchorPoint(Vec2(0.5, 0.5));
  this->background->setPosition(this->getContentSize().width / 2, this->getContentSize().height);

  this->texts.background = new Text("missions-title", this->background, true);
  this->texts.mission = new Text("missions-mission", this, true);

  this->texts.background->setPosition(this->background->getContentSize().width / 2, this->background->getContentSize().height / 2);
  this->texts.mission->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 100);

  for(int i = 0; i < 3; i++) this->missions.push_back(new MissionTask(this));

  this->setVisible(false);
}

EnvironmentMissionsPopup::~EnvironmentMissionsPopup()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsPopup::onCreate()
{
  BackgroundColor::onCreate();
}

void EnvironmentMissionsPopup::onDestroy(bool action)
{
  BackgroundColor::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsPopup::onEnter()
{
  BackgroundColor::onEnter();
}

void EnvironmentMissionsPopup::onExit()
{
  BackgroundColor::onExit();
}

/**
 *
 *
 *
 */
void EnvironmentMissionsPopup::updateData(int index)
{
  this->setVisible(true);

  /**
   *
   *
   *
   */
  this->texts.background->data(index, MissionsFactory::getInstance()->getMissionsCount());

  /**
   *
   *
   *
   */
  if(Application->environment->missions.controller->selectedMission->mission)
  {
    switch(Application->environment->missions.controller->selectedMission->mission->type)
    {
      case framework::MissionStruct::TYPE_ONCE:
      this->texts.mission->setText("missions-mission-1");
      break;
      case framework::MissionStruct::TYPE_PROGRESS:
      this->texts.mission->setText("missions-mission-2");
      break;
    }

    /**
     *
     *
     *
     */
    auto counter = 0;

    for(int i = 0; i < 3; i++) this->missions.at(i)->_destroy();
    for(int i = 0; i < Application->environment->missions.controller->selectedMission->mission->complete.size(); i++)
    {
      this->missions.at(counter)->_create();
      this->missions.at(counter)->updateData(counter);

      counter++;
    }

    switch(Application->environment->missions.controller->selectedMission->mission->complete.size())
    {
      case 1:
      this->missions.at(0)->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 - 50);
      break;
      case 2:
      this->missions.at(0)->setPosition(this->getContentSize().width / 2 - 100, this->getContentSize().height / 2 - 50);
      this->missions.at(1)->setPosition(this->getContentSize().width / 2 + 100, this->getContentSize().height / 2 - 50);
      break;
      case 3:
      this->missions.at(0)->setPosition(this->getContentSize().width / 2 - 200, this->getContentSize().height / 2 - 50);
      this->missions.at(1)->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 - 50);
      this->missions.at(2)->setPosition(this->getContentSize().width / 2 + 200, this->getContentSize().height / 2 - 50);
      break;
    }
  }

  this->setCameraMask(4);
}

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
EnvironmentMissionsPopup::MissionTask::MissionTask(Node* parent)
: Entity("missions-background.png", parent)
{
  this->setCascadeOpacityEnabled(true);

  this->text = new Text("missions-data", this, true);
  this->text->setPosition(this->getWidth() / 2, 20);

  this->element = new TiledEntity("missions-1.png", 4, 1, this, true);
  this->element->setPosition(this->getWidth() / 2, this->getHeight() / 2 + 11.5);
  this->element->setLocalZOrder(-2);

  this->element2 = new TiledEntity("missions-1.png", 4, 1, this);
  this->element2->setAnchorPoint(Vec2(0.5, 0.0));
  this->element2->setPosition(this->getWidth() / 2, this->getHeight() / 2 + 11.5 - this->element2->getHeight() / 2);
  this->element2->setLocalZOrder(-1);
}

EnvironmentMissionsPopup::MissionTask::~MissionTask()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsPopup::MissionTask::onCreate()
{
  Entity::onCreate();
}

void EnvironmentMissionsPopup::MissionTask::onDestroy(bool action)
{
  Entity::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsPopup::MissionTask::onEnter()
{
  Entity::onEnter();
}

void EnvironmentMissionsPopup::MissionTask::onExit()
{
  Entity::onExit();

  /**
   *
   *
   *
   */
  this->element2->_destroy();
}

/**
 *
 *
 *
 */
void EnvironmentMissionsPopup::MissionTask::updateData(int mission, MissionStruct* structure)
{
  auto m = structure ? structure : Application->environment->missions.controller->selectedMission->mission;
  auto c = m->complete.at(mission);

  this->element->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(c.preview));
  this->element->updateTexturePoistion();
  this->text->data(min(c.elapsed, c.target), c.target);

  switch(m->state)
  {
    case MissionStruct::STATE_CURRENT:
    case MissionStruct::STATE_CLAIM:
    case MissionStruct::STATE_FINISHED:
    this->text->setVisible(true);

    if(c.elapsed >= c.target)
    {
      this->element->setCurrentFrameIndex(2);
    }
    else if(c.elapsed > 0)
    {
      this->element->setCurrentFrameIndex(1);
    }
    else
    {
      this->element->setCurrentFrameIndex(0);
    }
    break;
    case MissionStruct::STATE_LOCKED:
    this->text->setVisible(false);

    this->element->setCurrentFrameIndex(3);
    break;
  }

  switch(m->state)
  {
    case MissionStruct::STATE_CURRENT:
    switch(m->type)
    {
      case MissionStruct::TYPE_ONCE:
      if(c.elapsed > 0)
      {
        this->element->setCurrentFrameIndex(0);

        auto constant = this->element2->getHeight();
        auto time = random(0.02, 0.06);

        this->element2->data = 100;

        this->element2->_create();
        this->element2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(c.preview));
        this->element2->updateTexturePoistion();
        this->element2->setCurrentFrameIndex(1);

        this->element2->stopAllActions();
        this->element2->runAction(
          Repeat::create(
            Sequence::create(
              DelayTime::create(time),
              CallFunc::create([=] () {
              this->element2->setTextureRect(Rect(
                this->element2->getFramesCoordinatesX()[1],
                this->element2->getFramesCoordinatesY()[1] - (this->element2->getTextureRect().size.height - constant),
                this->element2->getWidth(),
                this->element2->getHeight() / 100 * --this->element2->data
              ));

              if(this->element2->data <= 0)
              {
                this->element2->_destroy();
              }
              }),
              nullptr
            ),
            101
          )
        );
        this->element2->runAction(
          Repeat::create(
            Sequence::create(
              DelayTime::create(((time * 100) / c.elapsed) - 0.02),
              CallFunc::create([=] () {
              this->text->data(max(0.0f, min(--m->complete.at(mission).elapsed, c.target)), c.target);
              }),
              nullptr
            ), c.elapsed
          )
        );
      }
      break;
      case MissionStruct::TYPE_PROGRESS:
      break;
    }
    break;
  }
}
