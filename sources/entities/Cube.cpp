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
Cube::Cube(const char* file, Node* parent)
: Entity3D(file, parent)
{
}

Cube::~Cube()
{
}

/**
 *
 *
 *
 */
void Cube::onCreate()
{
  Entity3D::onCreate();

  /**
   *
   *
   *
   */
  this->createShadow();
  this->setOpacity(255);
}

void Cube::onDestroy(bool action)
{
  Entity3D::onDestroy(action);

  /**
   *
   *
   *
   */
  this->destroyShadow();
}

/**
 *
 *
 *
 */
void Cube::createShadow()
{
  if(this->shadow)
  {
    this->shadow->_create();
  }
}

void Cube::destroyShadow()
{
  if(this->shadow)
  {
    this->shadow->_destroy();
  }
}

/**
 *
 *
 *
 */
void Cube::update(float time)
{
  auto position = this->getPosition3D();

  if(this->shadow)
  {
    this->shadow->setPositionX(position.x);
    this->shadow->setPositionY(0);
    this->shadow->setPositionZ(position.z);

    this->shadow->setScaleX(max(0.0f, position.y / SHADOW_SIZE));
    this->shadow->setScaleZ(max(0.0f, position.y / SHADOW_SIZE));
  }

  this->setOpacity(position.y >= 0 ? 255 : max(0.0, 255.0 + (position.y * DEPTH)));
}
