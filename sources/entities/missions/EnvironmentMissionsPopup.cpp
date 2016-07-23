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

  this->action = new Text("missions-action", this);
  this->action->setPosition(this->getWidth() / 2, this->getHeight() / 2 + 10);
  this->action->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);
  this->action->setLocalZOrder(10);

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
  auto m = structure;
  auto c = m->complete.at(mission);

  this->element->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(c.preview));
  this->element->updateTexturePoistion();
  this->text->data(max(0.0f, min(c.elapsed, c.target)), c.target);

  switch(m->state)
  {
    case MissionStruct::STATE_CURRENT:
    this->action->_create();

    if(c.best > 0) this->action->setText("missions-action-best");
    else if(c.games > 0) this->action->setText("missions-action-games");
    else if(c.points > 0) this->action->setText("missions-action-points");
    else if(c.special_progress_14 > 0 || c.special_once_14 > 0) this->action->setText("missions-action-14");
    else this->action->_destroy();
    break;
    case MissionStruct::STATE_CLAIM:
    case MissionStruct::STATE_FINISHED:
    case MissionStruct::STATE_LOCKED:
    this->action->_destroy();
    break;
  }

  switch(m->state)
  {
    case MissionStruct::STATE_CURRENT:
    case MissionStruct::STATE_CLAIM:
    case MissionStruct::STATE_FINISHED:
    this->text->setVisible(true);

    if(c.elapsed >= c.target)
    {
      switch(m->type)
      {
        case MissionStruct::TYPE_PROGRESS:
        this->action->_destroy();
        break;
      }

      this->element->setCurrentFrameIndex(2);
    }
    else if(c.elapsed > 0 || c.games > 0 || c.points > 0 || c.best > 0 || c.special_progress_14 > 0 || c.special_once_14 > 0)
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
