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
EnvironmentStoreTexture::EnvironmentStoreTexture(Json* parameters)
: EnvironmentStoreItem(parameters)
{
  switch(this->parameters.index)
  {
    default:
    this->setTexture("textures/" + patch::to_string(this->parameters.index) + "/textures-plate.png");
    break;
    case 1:
    this->setTexture("textures/random.png");
    break;
  }

  switch(this->parameters.index)
  {
    default:
    this->positions = Vec3(0.0, 0.40, 0.75);
    break;
    case 1:
    this->positions = Vec3(0.0, 0.75, 0.75);
    this->setScale(1.5);
    break;
  }

  Application->environment->store.textures.plane->pushBackCustomItem(this->elements.plane);
}

EnvironmentStoreTexture::~EnvironmentStoreTexture()
{
}

/**
 *
 *
 *
 */
void EnvironmentStoreTexture::onCreate()
{
  EnvironmentStoreItem::onCreate();
}

void EnvironmentStoreTexture::onDestroy(bool action)
{
  EnvironmentStoreItem::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentStoreTexture::onTouch(cocos2d::Touch* touch, Event* e)
{
  EnvironmentStoreItem::onTouch(touch, e);

  /**
   *
   *
   *
   */
}
