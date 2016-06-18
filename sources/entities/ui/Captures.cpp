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
Captures::Captures()
{
  this->texts.score = new Text("counter-score", nullptr, TextHAlignment::LEFT);
  this->texts.score->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);
  this->texts.score->setScale(0.35);
  this->texts.score->_create();

  this->texts.score->retain();
}

Captures::~Captures()
{
}

/**
 *
 *
 *
 */
void Captures::update()
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();

  this->texts.score->data(Application->counter->values.current);

  this->texts.score->setPosition(x - 165, y + 70);
}

/**
 *
 *
 *
 */
void Captures::visit(Renderer *renderer, const Mat4& transform, uint32_t state)
{
  Sprite::visit(renderer, transform, state);

  /**
   *
   *
   *
   */
  this->texts.score->visit(renderer, transform, state);
}
