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
  this->setPosition(Application->getWidth() / 2, Application->getHeight() / 2 + 70);
  this->setRotation(3.0);
  this->setScale(1.0);

  this->runAction(
    ScaleTo::create(0.2, 0.5)
  );

  this->runAction(
    RepeatForever::create(
      Sequence::create(
        RotateTo::create(0.5, -3.0),
        RotateTo::create(0.5, 3.0),
        nullptr
      )
    )
  );

  Finish::getInstance()->missions->_create();

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

    this->stopAllActions();
    this->runAction(
      Spawn::create(
        ScaleTo::create(0.2, 1.3),
        RotateTo::create(0.2, 0),
        MoveTo::create(0.2, Vec2(Application->getWidth() / 2, Application->getHeight() / 2)),
        Sequence::create(
          DelayTime::create(0.5),
          CallFunc::create([=] () {
          Application->onShare();
          }),
          nullptr
        ),
        nullptr
      )
    );
    Application->d->runAction(
      FadeTo::create(0.2, 200)
    );
    break;
    case STATE_ACTIVE:
    this->state = STATE_NORMAL;

    this->stopAllActions();
    this->runAction(
      Spawn::create(
        ScaleTo::create(0.2, 0.5),
        RotateTo::create(0.2, 3.0),
        MoveTo::create(0.2, Vec2(Application->getWidth() / 2, Application->getHeight() / 2 + 70)),
        Sequence::create(
          DelayTime::create(0.2),
          CallFunc::create([=] () {
          this->runAction(
            RepeatForever::create(
              Sequence::create(
                RotateTo::create(0.5, -3.0),
                RotateTo::create(0.5, 3.0),
                nullptr
              )
            )
          );
          }),
          nullptr
        ),
        nullptr
      ), 1
    );
    Application->d->runAction(
      FadeTo::create(0.2, 0)
    );
    break;
  }

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
void Capture::screenshot(string texture)
{
  this->_create();

  /**
   *
   *
   *
   */
  Director::getInstance()->getTextureCache()->removeUnusedTextures();
  Director::getInstance()->getTextureCache()->removeTextureForKey(texture.c_str());

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
void Capture::animation()
{
  this->_create();

  /**
   *
   *
   *
   */
  this->element->initWithTexture(Application->capturing.textures.at(0)->getSprite()->getTexture());
  this->element->setScale(this->getWidth() / this->element->getWidth());
  this->element->setScaleY(this->element->getScaleY() * -1);
  this->element->setPosition(this->getWidth() / 2, this->getHeight() / 2);

  /**
   *
   *
   *
   */
  this->unschedule("?");
  this->schedule([=] (float time) {
    if(Application->capturing.frame <= 0)
    {
      Application->capturing.frame = Application->capturing.frames;
    }

    this->element->Sprite::setTexture(Application->capturing.textures.at(--Application->capturing.frame)->getSprite()->getTexture());
  }, 1.0 / 60.0, "?");
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
