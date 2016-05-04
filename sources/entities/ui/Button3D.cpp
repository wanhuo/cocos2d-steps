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
Button3D::Button3D(string file, string texture, Node* parent, CameraStruct camera, const vector<LightStruct> vec)
: CameraEntity3D(file, parent, false, camera, vec)
{
  this->texture = texture;

  this->setTexture(this->texture);

  this->bind(true);
}

Button3D::~Button3D()
{
}

/**
 *
 *
 *
 */
void Button3D::onCreate()
{
  CameraEntity3D::onCreate();

  /**
   *
   *
   *
   */
  for(auto child : this->getChildren())
  {
    child->_create();

    static_cast<Sprite3D*>(child)->setTexture(this->texture);
    static_cast<Sprite3D*>(child)->setLightMask(this->index);
  }

  this->setCameraMask(this->index);
}

void Button3D::onDestroy(bool action)
{
  CameraEntity3D::onDestroy(action);

  /**
   *
   *
   *
   */
  for(auto child : this->getChildren())
  {
    child->_destroy();
  }
}

/**
 *
 *
 *
 */
void Button3D::onTouchStart(cocos2d::Touch* touch, Event* e)
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

void Button3D::onTouchFinish(cocos2d::Touch* touch, Event* e)
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

void Button3D::onTouchCancelled(cocos2d::Touch* touch, Event* e)
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
void Button3D::onTouch(cocos2d::Touch* touch, Event* e)
{
  /**
   *
   *
   *
   */
  Sound->play("touch");
}
