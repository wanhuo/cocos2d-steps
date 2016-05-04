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

#ifndef _GIFT_H_
#define _GIFT_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Gift : public Button3D
{
  /**
   *
   *
   *
   */
  public:
  class Diamond : public Entity3D
  {
    /**
     *
     *
     *
     */
    protected:
    Vec3 direction;
    Vec3 speed;

    /**
     *
     *
     *
     */
    public:
    Diamond();
  ~Diamond();

   virtual void onCreate();
   virtual void onDestroy(bool action = false);

   virtual void update(float time);

   virtual Diamond* deepCopy();
  };

  /**
   *
   *
   *
   */
  public:
  class Element : public Entity3D
  {
    /**
     *
     *
     *
     */
    protected:
    BillBoard* window;
    Entity3D* diamond;
    Text* text;

    /**
     *
     *
     *
     */
    public:
    Element(Node* parent);
  ~Element();

   virtual void onCreate();
   virtual void onDestroy(bool action = false);
  };

  /**
   *
   *
   *
   */
  private:
  string texture;
  vector<string> textures = {
    "ui/gift-texture-1.png",
    "ui/gift-texture-2.png",
    "ui/gift-texture-3.png",
    "ui/gift-texture-4.png",
    "ui/gift-texture-5.png",
    "ui/gift-texture-6.png",
    "ui/gift-texture-7.png",
    "ui/gift-texture-8.png",
    "ui/gift-texture-9.png",
    "ui/gift-texture-10.png",
    "ui/gift-texture-11.png",
    "ui/gift-texture-12.png",
    "ui/gift-texture-13.png",
    "ui/gift-texture-14.png"
  };

  /**
   *
   *
   *
   */
  protected:

  /**
   *
   *
   *
   */
  public:
  Gift(Node* parent);
 ~Gift();

  Pool* elements;
  Element* element;

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onTouch(cocos2d::Touch* touch, Event* e);
};

#endif
