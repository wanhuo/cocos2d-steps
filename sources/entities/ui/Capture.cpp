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
  this->element->setLocalZOrder(-1);

  this->setPosition(Application->getWidth() / 2, Application->getHeight() / 2);
  this->setCameraMask(4);
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
  this->setRotation(0);
  this->setScale(1.5);

  this->runAction(
    Spawn::create(
      ScaleTo::create(0.2, 1.0),
      RotateTo::create(0.2, - 15.0),
      nullptr
    )
  );

  Sound->play("capture");
}

void Capture::onDestroy(bool action)
{
  Entity::onDestroy(action);

  /**
   *
   *
   *
   */
}

/**
 *
 *
 *
 */
void Capture::onTouchStart(cocos2d::Touch* touch, Event* e)
{
  this->stopActionByTag(101);
  this->Node::runAction(
    EaseSineIn::create(
      ScaleTo::create(0.2, 0.9)
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
      ScaleTo::create(0.2, 1.0)
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
      ScaleTo::create(0.2, 1.0)
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
  this->runAction(
    Spawn::create(
      ScaleTo::create(0.2, 2.0),
      RotateTo::create(0.2, 0),
      Sequence::create(
        DelayTime::create(0.2),
        CallFunc::create([=] () {
        }),
        nullptr
      ),
      nullptr
    )
  );
}

/**
 *
 *
 *
 */
void Capture::screenshot(string texture)
{
  auto size = Director::getInstance()->getOpenGLView()->getFrameSize();

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
  this->element->setTexture(texture.c_str());
  this->element->setScale(this->getWidth() / size.width);
  this->element->setTextureRect(Rect(0, size.height - size.width, size.width, size.width));
  this->element->setPosition(this->getWidth() / 2, this->getHeight() / 2);

  /**
   *
   *
   *
   */
  this->_create();
}
