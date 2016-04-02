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
Item::Item(Node* parent)
: Entity("store-item.png", parent, true)
{
  this->text = new Text("item-name", this, true);
  this->lock = new Entity("store-lock-icon.png", this);

  this->text->setPosition(this->getWidth() / 2, 20);
  this->lock->setPosition(this->getWidth() / 2, this->getHeight() / 2 + 20);
}

Item::~Item()
{
}

/**
 *
 *
 *
 */
void Item::onCreate()
{
  Entity::onCreate();

  /**
   *
   *
   *
   */
}

void Item::onDestroy(bool action)
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
void Item::onEnter()
{
  Entity::onEnter();

  /**
   *
   *
   *
   */
  if(probably(50))
  {
    this->lock->_create();

    this->bind(false);
  }
  else
  {
    this->bind(true, false);
  }
}

void Item::onExit()
{
  Entity::onExit();

  /**
   *
   *
   *
   */
  this->lock->_destroy();
}
