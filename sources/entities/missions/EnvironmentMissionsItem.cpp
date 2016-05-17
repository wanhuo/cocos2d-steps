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
EnvironmentMissionsItem::EnvironmentMissionsItem(int index)
: Cube("gift-missions.obj", nullptr)
{
  this->mission = MissionsFactory::getInstance()->getMission(index);

  this->parameters.index = index + 1;

  this->shadow = new Shadow("plate-bottom-shadow.obj", nullptr);
  this->shadow->setMinScale(Vec3(1.2, 1.0, 1.2));
  this->shadow->setMaxScale(Vec3(1.2, 1.0, 1.2));
  this->shadow->setOffset(Vec3(0.15, 0.0, 0.15));

  this->elements.lock = new Entity3D("store-unlock.obj", false);
  this->elements.lock->setTexture("ui/video-texture.png");

  this->elements.plane = cocos2d::ui::Layout::create();
  this->elements.plane->setContentSize(Size(3.0, 10.0));
  this->elements.plane->addChild(this);
  this->elements.plane->addChild(this->shadow);
  this->elements.plane->addChild(this->elements.lock);

  Application->environment->missions.missions.plane->pushBackCustomItem(this->elements.plane);

  switch(this->parameters.index)
  {
    case 1:
    this->setTexture("ui/gift-texture-1.png");
    break;
    case 2:
    this->setTexture("ui/gift-texture-2.png");
    break;
    case 3:
    this->setTexture("ui/gift-texture-3.png");
    break;
    default:
    this->setTexture("ui/gift-texture-4.png");
    break;
  }

  this->setScheduleUpdate(true);

  this->positions = Vec3(-2.0, 0.75, 2.75);
}

EnvironmentMissionsItem::~EnvironmentMissionsItem()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsItem::onCreate()
{
  Cube::onCreate();

  /**
   *
   *
   *
   */
  this->elements.lock->_create();
}

void EnvironmentMissionsItem::onDestroy(bool action)
{
  Cube::onDestroy(action);

  /**
   *
   *
   *
   */
  this->elements.lock->_destroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsItem::onEnter()
{
  Cube::onEnter();

  /**
   *
   *
   *
   */
  this->setPosition3D(this->positions);
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->elements.lock->setPosition3D(Vec3(-2.0, 0.0, 2.75));
  this->elements.lock->setRotation3D(Vec3(0.0, 0.0, 0.00));

  this->position = POSITION_NORMAL;

  this->updateState();
}

void EnvironmentMissionsItem::onExit()
{
  Cube::onExit();
}

/**
 *
 *
 *
 */
void EnvironmentMissionsItem::onTouchStart(cocos2d::Touch* touch, Event* e)
{
  /**
   *
   *
   *
   */
  Node::onTouchStart(touch, e);
}

void EnvironmentMissionsItem::onTouchFinish(cocos2d::Touch* touch, Event* e)
{
  /**
   *
   *
   *
   */
  Node::onTouchFinish(touch, e);
}

void EnvironmentMissionsItem::onTouchCancelled(cocos2d::Touch* touch, Event* e)
{
  /**
   *
   *
   *
   */
  Node::onTouchCancelled(touch, e);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsItem::onTouch(cocos2d::Touch* touch, Event* e)
{
  /**
   *
   *
   *
   */
  Sound->play("touch");
}

/**
 *
 *
 *
 */
void EnvironmentMissionsItem::changeState(int state)
{
}

void EnvironmentMissionsItem::changePosition(Position position)
{
  switch(position)
  {
    case POSITION_NORMAL:

    switch(this->position)
    {
      case POSITION_NORMAL:
      break;
      case POSITION_UP:
      this->stopAllActions();
      this->elements.lock->stopAllActions();

      this->runAction(MoveTo::create(0.2, this->positions));
      this->elements.lock->runAction(MoveTo::create(0.2, Vec3(-2.0, 0.0, 2.75)));

      this->runAction(RotateTo::create(0.2, Vec3(0.0, 0.0, 0.0)));
      this->elements.lock->runAction(RotateTo::create(0.2, Vec3(0.0, 0.0, 0.0)));
      break;
    }
    break;
    case POSITION_UP:

    switch(this->position)
    {
      case POSITION_NORMAL:
      Sound->play("touch");

      this->runAction(MoveTo::create(0.2, this->positions + Vec3(0.0, 1.0, 0.0)));
      this->elements.lock->runAction(MoveTo::create(0.2, Vec3(-2.0, 1.0, 2.75)));

      this->runAction(
        RepeatForever::create(
          Sequence::create(
            RotateBy::create(2.0, Vec3(0.0, 360.0, 0.0)),
            RotateBy::create(0.0, Vec3(0.0, 0.0, 0.0)),
            nullptr
          )
        )
      );

      this->elements.lock->runAction(
        RepeatForever::create(
          Sequence::create(
            RotateBy::create(2.0, Vec3(0.0, 360.0, 0.0)),
            RotateBy::create(0.0, Vec3(0.0, 0.0, 0.0)),
            nullptr
          )
        )
      );
      break;
      case POSITION_UP:
      break;
    }
    break;
  }

  this->position = position;
}

/**
 *
 *
 *
 */
void EnvironmentMissionsItem::updateState()
{
  this->setVisible(false);
  this->elements.lock->setVisible(false);

  switch(this->mission->state)
  {
    case MissionStruct::STATE_CURRENT:
    case MissionStruct::STATE_CLAIM:
    this->setVisible(true);
    break;
    case MissionStruct::STATE_LOCKED:
    this->elements.lock->setVisible(true);
    break;
  }
}

void EnvironmentMissionsItem::saveState()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsItem::setTexture(const std::string& file)
{
  Cube::setTexture(file);

  this->setLightMask(1);

  for(auto element : this->getChildren())
  {
    static_cast<Sprite3D*>(element)->setTexture(file);
    static_cast<Sprite3D*>(element)->setLightMask(1);
  }
}

/**
 *
 *
 *
 */
void EnvironmentMissionsItem::update(float time)
{
  Cube::update(time);

  /**
   *
   *
   *
   */
  this->shadow->setRotation3D(this->getRotation3D());
}
