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
  this->parameters.facebook = Json_getInt(parameters, "facebook", 0);
  this->parameters.twitter = Json_getInt(parameters, "twitter", 0);

  this->shadow = new Shadow("plate-bottom-shadow.obj", nullptr);
  this->shadow->setMinScale(Vec3(1.2, 1.0, 1.2));
  this->shadow->setMaxScale(Vec3(1.2, 1.0, 1.2));
  this->shadow->setOffset(Vec3(0.15, 0.0, 0.15));

  this->elements.lock = new Entity3D("store-unlock.obj", false);
  this->elements.facebook = new Entity3D("store-plate.obj", false);
  this->elements.twitter = new Entity3D("store-plate.obj", false);

  this->elements.lock->setTexture("textures/store-unlock-texture.png");
  this->elements.facebook->setTexture("ui/facebook-texture.png");
  this->elements.twitter->setTexture("ui/twitter-texture.png");

  this->elements.facebook->setScale(0.5);
  this->elements.twitter->setScale(0.5);

  this->elements.plane = cocos2d::ui::Layout::create();
  this->elements.plane->setContentSize(Size(3.0, 10.0));
  this->elements.plane->addChild(this);
  this->elements.plane->addChild(this->shadow);
  this->elements.plane->addChild(this->elements.lock);
  this->elements.plane->addChild(this->elements.facebook);
  this->elements.plane->addChild(this->elements.twitter);

  this->setScheduleUpdate(true);

  this->state = Storage::get(this->parameters.id);

  if(!this->state)
  {
    if(this->parameters.index <= 2)
    {
      this->state = STATE_UNLOCKED;
    }
    else
    {
      if(this->parameters.facebook)
      {
        this->state = STATE_FACEBOOK;
      }
      else if(this->parameters.twitter)
      {
        this->state = STATE_TWITTER;
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
  }
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
  this->elements.lock->_create();
  this->elements.facebook->_create();
  this->elements.twitter->_create();
}

void EnvironmentStoreItem::onDestroy(bool action)
{
  Cube::onDestroy(action);

  /**
   *
   *
   *
   */
  this->elements.lock->_destroy(action);
  this->elements.facebook->_destroy(action);
  this->elements.twitter->_destroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentStoreItem::onEnter()
{
  Cube::onEnter();

  /**
   *
   *
   *
   */
  this->setPosition3D(this->positions);
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->elements.lock->setPosition3D(Vec3(0.0, 0.0, 0.75));
  this->elements.lock->setRotation3D(Vec3(0.0, 0.0, 0.00));

  this->elements.facebook->setPosition3D(Vec3(0.0, 3.0, 0.75));
  this->elements.facebook->setRotation3D(Vec3(0.0, 0.0, 0.00));

  this->elements.twitter->setPosition3D(Vec3(0.0, 3.0, 0.75));
  this->elements.twitter->setRotation3D(Vec3(0.0, 0.0, 0.00));

  this->position = POSITION_NORMAL;

  this->updateState();
}

void EnvironmentStoreItem::onExit()
{
  Cube::onExit();
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
void EnvironmentStoreItem::changeState(int state)
{
  this->state = state;

  this->saveState();
  this->updateState();
}

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
      this->elements.lock->stopAllActions();
      this->elements.facebook->stopAllActions();
      this->elements.twitter->stopAllActions();

      this->runAction(MoveTo::create(0.2, this->positions));
      this->elements.lock->runAction(MoveTo::create(0.2, Vec3(0.0, 0.0, 0.75)));
      this->elements.facebook->runAction(MoveTo::create(0.2, Vec3(0.0, 3.0, 0.75)));
      this->elements.twitter->runAction(MoveTo::create(0.2, Vec3(0.0, 3.0, 0.75)));

      this->runAction(RotateTo::create(0.2, Vec3(0.0, 0.0, 0.0)));
      this->elements.lock->runAction(RotateTo::create(0.2, Vec3(0.0, 0.0, 0.0)));
      this->elements.facebook->runAction(RotateTo::create(0.2, Vec3(0.0, 0.0, 0.0)));
      this->elements.twitter->runAction(RotateTo::create(0.2, Vec3(0.0, 0.0, 0.0)));
      break;
    }
    break;
    case POSITION_UP:

    switch(this->position)
    {
      case POSITION_NORMAL:
      Sound->play("select");

      this->runAction(MoveTo::create(0.2, this->positions + Vec3(0.0, 1.0, 0.0)));
      this->elements.lock->runAction(MoveTo::create(0.2, Vec3(0.0, 1.0, 0.75)));
      this->elements.facebook->runAction(MoveTo::create(0.2, Vec3(0.0, 4.0, 0.75)));
      this->elements.twitter->runAction(MoveTo::create(0.2, Vec3(0.0, 4.0, 0.75)));

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

      this->elements.facebook->runAction(
        RepeatForever::create(
          Sequence::create(
            RotateBy::create(2.0, Vec3(0.0, 360.0, 0.0)),
            RotateBy::create(0.0, Vec3(0.0, 0.0, 0.0)),
            nullptr
          )
        )
      );

      this->elements.twitter->runAction(
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
void EnvironmentStoreItem::updateState()
{
  switch(this->state)
  {
    case STATE_MISSIONS:
    if(this->parameters.missions <= MissionsFactory::getInstance()->getCompletedMissionsCount())
    {
      this->changeState(STATE_DIAMONDS);
    }
    break;
  }

  switch(this->state)
  {
    case STATE_DIAMONDS:
    case STATE_MISSIONS:
    this->setVisible(false);

    this->elements.lock->setVisible(true);
    this->elements.facebook->setVisible(false);
    this->elements.twitter->setVisible(false);
    break;
    case STATE_UNLOCKED:
    this->setVisible(true);
    this->elements.lock->setVisible(false);
    this->elements.facebook->setVisible(false);
    this->elements.twitter->setVisible(false);
    break;
    case STATE_FACEBOOK:
    this->setVisible(false);
    this->elements.lock->setVisible(true);
    this->elements.facebook->setVisible(true);
    this->elements.twitter->setVisible(false);
    break;
    case STATE_TWITTER:
    this->setVisible(false);
    this->elements.lock->setVisible(true);
    this->elements.facebook->setVisible(false);
    this->elements.twitter->setVisible(true);
    break;
  }
}

void EnvironmentStoreItem::saveState()
{
  Storage::set(this->parameters.id, this->state);
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
