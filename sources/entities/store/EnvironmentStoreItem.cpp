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
EnvironmentStoreItem::EnvironmentStoreItem(Json* parameters)
: Cube(patch::to_string(Json_getString(parameters, "file", "")) + ".obj", nullptr)
{
  this->parameters.id = Json_getString(parameters, "id", "");
  this->parameters.index = Json_getInt(parameters, "index", 0);
  this->parameters.missions = Json_getInt(parameters, "missions", 0);
  this->parameters.diamonds = Json_getInt(parameters, "diamonds", 0);

  this->shadow = new Shadow("plate-bottom-shadow.obj", nullptr);
  this->shadow->setMinScale(Vec3(1.2, 1.0, 1.0));
  this->shadow->setMaxScale(Vec3(1.2, 1.0, 1.0));
  this->shadow->setOffset(Vec3(0.15, 0.0, 0.4));

  this->setScheduleUpdate(true);
}

EnvironmentStoreItem::~EnvironmentStoreItem()
{
}

/**
 *
 *
 *
 */
void EnvironmentStoreItem::onCreate()
{
  Cube::onCreate();

  /**
   *
   *
   *
   */
  this->state = Storage::get(this->parameters.id);

  if(!this->state)
  {
    if(this->parameters.index == 0)
    {
      this->state = STATE_UNLOCKED;
    }
    else if(this->parameters.index == 1)
    {
      this->state = STATE_SELECTED;
    }
    else
    {
      if(MissionsFactory::getInstance()->getCompletedMissionsCount() < this->parameters.missions)
      {
        this->state = STATE_MISSIONS;
      }
      else
      {
        this->state = STATE_DIAMONDS;
      }
    }
  }

  this->setPosition3D(this->positions);
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->position = POSITION_NORMAL;
}

void EnvironmentStoreItem::onDestroy(bool action)
{
  Cube::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentStoreItem::onTouchStart(cocos2d::Touch* touch, Event* e)
{
  /**
   *
   *
   *
   */
  Node::onTouchStart(touch, e);
}

void EnvironmentStoreItem::onTouchFinish(cocos2d::Touch* touch, Event* e)
{
  /**
   *
   *
   *
   */
  Node::onTouchFinish(touch, e);
}

void EnvironmentStoreItem::onTouchCancelled(cocos2d::Touch* touch, Event* e)
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
void EnvironmentStoreItem::onTouch(cocos2d::Touch* touch, Event* e)
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
void EnvironmentStoreItem::changePosition(Position position)
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

      this->runAction(
        MoveTo::create(0.2, this->positions)
      );

      this->runAction(
        RotateTo::create(0.2, Vec3(0.0, 0.0, 0.0))
      );
      break;
    }
    break;
    case POSITION_UP:

    switch(this->position)
    {
      case POSITION_NORMAL:
      Sound->play("touch");

      this->runAction(
        MoveTo::create(0.2, this->positions + Vec3(0.0, 1.0, 0.0))
      );

      this->runAction(
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
void EnvironmentStoreItem::update(float time)
{
  Cube::update(time);

  /**
   *
   *
   *
   */
  this->shadow->setRotation3D(this->getRotation3D());
}
