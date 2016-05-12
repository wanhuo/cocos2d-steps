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
EnvironmentStoreCharacter::EnvironmentStoreCharacter(Json* parameters)
: EnvironmentStoreItem(parameters)
{
  switch(this->parameters.index)
  {
    default:
    this->setTexture(Application->environment->getTextureState1());
    this->setColor(Application->environment->character->getColor());
    break;
    case 1:
    this->setTexture("textures/random.png");
    break;
  }

  this->positions = Vec3(0.0, 0.75, 0.75);

  this->setScale(1.5);

  auto plane = cocos2d::ui::Layout::create();
  plane->setContentSize(Size(3.0, 10.0));
  plane->addChild(this);
  plane->addChild(this->lock);
  plane->addChild(this->shadow);

  Application->environment->store.characters.plane->pushBackCustomItem(plane);
}

EnvironmentStoreCharacter::~EnvironmentStoreCharacter()
{
}

/**
 *
 *
 *
 */
void EnvironmentStoreCharacter::onCreate()
{
  EnvironmentStoreItem::onCreate();
}

void EnvironmentStoreCharacter::onDestroy(bool action)
{
  EnvironmentStoreItem::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentStoreCharacter::onTouch(cocos2d::Touch* touch, Event* e)
{
  EnvironmentStoreItem::onTouch(touch, e);

  /**
   *
   *
   *
   */
}
