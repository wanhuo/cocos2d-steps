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
Cube::Cube(string file, Node* parent)
: Entity3D(file, parent)
{
}

Cube::Cube(Node* parent)
: Entity3D(parent)
{
}

Cube::~Cube()
{
  if(this->shadow)
  {
    this->shadow->removeFromParent();
  }
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
    auto position = this->getPosition3D();

    this->shadow->_create();

    this->shadow->setVisible(true);
    this->shadow->setPositionX(position.x);
    this->shadow->setPositionZ(position.z);
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
    this->shadow->setPositionX(position.x + this->shadow->getOffset().x);
    this->shadow->setPositionY(this->shadow->getPosition() + this->shadow->getOffset().y);
    this->shadow->setPositionZ(position.z + this->shadow->getOffset().z);

    this->shadow->setScaleX(max(this->shadow->getMinScale().x, min(this->shadow->getMaxScale().x, position.y - this->shadow->getPosition())));
    this->shadow->setScaleZ(max(this->shadow->getMinScale().z, min(this->shadow->getMaxScale().z, position.y - this->shadow->getPosition())));

    if(!Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget(this->shadow))
    {
      this->shadow->setOpacity(max(0.0f, min(30.0f, 30.0f - (position.y * this->shadow->getSize()))));
    }
  }
}
