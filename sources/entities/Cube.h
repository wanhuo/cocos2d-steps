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

#ifndef _CUBE_H_
#define _CUBE_H_

#include "Entity3D.h"

/**
 *
 *
 *
 */
class Cube : public Entity3D
{
  /**
   *
   *
   *
   */
  private:
  const static int DEPTH = 50;
  const static int SHADOW_SIZE = 2;

  /**
   *
   *
   *
   */
  protected:
  Entity3D* shadow = nullptr;

  /**
   *
   *
   *
   */
  public:
  Cube(const char* file, Node* parent = nullptr);
 ~Cube();

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void createShadow();
  virtual void destroyShadow();

  virtual void update(float time);
};

#endif
