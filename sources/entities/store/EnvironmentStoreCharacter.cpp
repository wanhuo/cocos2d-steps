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
    break;
    case 1:
    this->setTexture("textures/random.png");
    break;
    case 21:
    this->setTexture("characters/21/character-texture.png");
    break;
    case 22:
    this->setTexture("characters/22/character-texture.png");
    break;
    case 23:
    this->setTexture("characters/23/character-texture.png");
    break;
    case 24:
    this->setTexture("characters/24/character-texture.png");
    break;
    case 25:
    this->setTexture("characters/25/character-texture.png");
    break;
    case 26:
    this->setTexture("characters/26/character-texture.png");
    break;
    case 27:
    this->setTexture("characters/27/character-texture.png");
    break;
    case 28:
    this->setTexture("characters/28/character-texture.png");
    break;
  }

  switch(this->parameters.index)
  {
    default:
    this->setColor(Color3B(0.0, 207.0, 255.0));
    break;
    case 1:
    case 3:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    this->setColor(Color3B(255.0, 255.0, 255.0));
    break;
  }

  this->positions = Vec3(0.0, 0.75, 0.75);

  this->setScale(1.5);

  Application->environment->store.characters.plane->pushBackCustomItem(this->elements.plane);

  /**
   *
   *
   *
   */
  if(this->parameters.index == 4)
  {
    auto test = new Entity3D("character-2.obj", this->elements.plane);
    test->setPosition3D(Vec3(0.0+10.5, 0.75-0.7, 0.75+0.75));
    test->setScaleX(22.5);
    test->setScaleY(0.1);
    test->setScaleZ(3.0);
    test->setColor(Color3B(67, 150, 255));
    test->setTexture(Application->environment->getTextureState1());
    test->_create();

    auto th = new Entity3D(this->elements.plane);
    th->setRotation3D(Vec3(-90, 0, 0));
    th->setPosition3D(Vec3(-0.5, 0.2, 2.4));
    th->_create();

    auto text = new Text("store-type-1", th, TextHAlignment::LEFT, true);
    text->setScale(0.008);
  }

  else if(this->parameters.index == 12)
  {
    auto test = new Entity3D("character-2.obj", this->elements.plane);
    test->setPosition3D(Vec3(0.0+7.5, 0.75-0.7, 0.75+0.75));
    test->setScaleX(16.5);
    test->setScaleY(0.1);
    test->setScaleZ(3.0);
    test->setColor(Color3B(180, 0, 255));
    test->setTexture(Application->environment->getTextureState1());
    test->_create();

    auto th = new Entity3D(this->elements.plane);
    th->setRotation3D(Vec3(-90, 0, 0));
    th->setPosition3D(Vec3(-0.5, 0.2, 2.4));
    th->_create();

    auto text = new Text("store-type-2", th, TextHAlignment::LEFT, true);
    text->setScale(0.008);
  }

  else if(this->parameters.index == 18)
  {
    auto test = new Entity3D("character-2.obj", this->elements.plane);
    test->setPosition3D(Vec3(0.0+4.5, 0.75-0.7, 0.75+0.75));
    test->setScaleX(10.5);
    test->setScaleY(0.1);
    test->setScaleZ(3.0);
    test->setColor(Color3B(255, 150, 0));
    test->setTexture(Application->environment->getTextureState1());
    test->_create();

    auto th = new Entity3D(this->elements.plane);
    th->setRotation3D(Vec3(-90, 0, 0));
    th->setPosition3D(Vec3(-0.5, 0.2, 2.4));
    th->_create();

    auto text = new Text("store-type-3", th, TextHAlignment::LEFT, true);
    text->setScale(0.008);
  }
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
