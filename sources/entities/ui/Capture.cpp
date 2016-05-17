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
Capture::Capture(Node* parent)
: Entity("capture.png", parent)
{
  this->element = new Entity(this, true);
  this->element->setGlobalZOrder(1000);
  this->element->setLocalZOrder(-1);

  this->setPosition(Application->getWidth() / 2, Application->getHeight() / 2);
  this->setGlobalZOrder(1000);
  this->setCameraMask(8);
  this->bind(true);
}

Capture::~Capture()
{
}

/**
 *
 *
 *
 */
void Capture::onCreate()
{
  Entity::onCreate();

  /**
   *
   *
   *
   */
  this->state = STATE_NORMAL;

  /**
   *
   *
   *
   */
  this->setRotation(0);
  this->setScale(1.0);

  this->runAction(
    Spawn::create(
      ScaleTo::create(0.2, 0.5),
      RotateTo::create(0.2, -15.0),
      nullptr
    )
  );

  Sound->play("capture");
}

void Capture::onDestroy(bool action)
{
  Entity::onDestroy(action);
}

/**
 *
 *
 *
 */
void Capture::onTouchStart(cocos2d::Touch* touch, Event* e)
{
  if(this->getActionByTag(1)) return;

  this->stopActionByTag(101);
  this->Node::runAction(
    EaseSineIn::create(
      ScaleTo::create(0.1, this->state == STATE_NORMAL ? 0.45 : 1.25)
    ), 101
  );

  /**
   *
   *
   *
   */
  Node::onTouchStart(touch, e);
}

void Capture::onTouchFinish(cocos2d::Touch* touch, Event* e)
{
  this->stopActionByTag(101);
  this->Node::runAction(
    EaseSineIn::create(
      ScaleTo::create(0.1, this->state == STATE_NORMAL ? 0.5 : 1.3)
    ), 101
  );

  /**
   *
   *
   *
   */
  Node::onTouchFinish(touch, e);
}

void Capture::onTouchCancelled(cocos2d::Touch* touch, Event* e)
{
  this->stopActionByTag(101);
  this->Node::runAction(
    EaseSineIn::create(
      ScaleTo::create(0.1, this->state == STATE_NORMAL ? 0.5 : 1.3)
    ), 101
  );

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
void Capture::onTouch(cocos2d::Touch* touch, Event* e)
{
  Entity::onTouch(touch, e);

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_NORMAL:
    this->state = STATE_ACTIVE;

    this->runAction(
      Spawn::create(
        ScaleTo::create(0.2, 1.3),
        RotateTo::create(0.2, 0),
        Sequence::create(
          DelayTime::create(0.2),
          CallFunc::create([=] () {
          Application->onShare();
          }),
          nullptr
        ),
        nullptr
      ), 1
    );
    Application->d->runAction(
      FadeTo::create(0.2, 200)
    );
    break;
    case STATE_ACTIVE:
    this->state = STATE_NORMAL;

    this->runAction(
      Spawn::create(
        ScaleTo::create(0.2, 0.5),
        RotateTo::create(0.2, -15.0),
        nullptr
      ), 1
    );
    Application->d->runAction(
      FadeTo::create(0.2, 0)
    );
    break;
  }
}

/**
 *
 *
 *
 */
void Capture::screenshot(string texture)
{
  this->_create();

  /**
   *
   *
   *
   */
  Director::getInstance()->getTextureCache()->removeTextureForKey(texture.c_str());

  /**
   *
   *
   *
   */
   Application->counter->texts.name->setOpacity(255);
  auto image = cocos2d::utils::captureNode(Application->counter->texts.name);
  image->saveToFile(FileUtils::getInstance()->getWritablePath() + "a.png", true);
   Application->counter->texts.name->setOpacity(0);

  /**
   *
   *
   *
   */
  this->element->setTexture(texture.c_str());
  this->element->setScale(this->getWidth() / this->element->getWidth());
  this->element->setPosition(this->getWidth() / 2, this->getHeight() / 2);
}

/**
 *
 *
 *
 */
bool Capture::containsTouchLocation(cocos2d::Touch* touch)
{
  switch(this->state)
  {
    case STATE_NORMAL:
    return Entity::containsTouchLocation(touch);
    break;
    case STATE_ACTIVE:
    return true;
    break;
  }

  return false;
}
