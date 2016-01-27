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

#ifndef _WHALE_H_
#define _WHALE_H_

#include "Fish.h"

/**
 *
 *
 *
 */
class Whale : public Fish
{
  /**
   *
   *
   *
   */
  private:

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
  const static int TIME = 2;

  const static int STATE_NONE = 0;
  const static int STATE_SLEEP = 1;
  const static int STATE_NORMAL = 2;

  Whale(Environment* environment);
 ~Whale();

  int state;

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onSleep();
  virtual void onNormal();

  virtual void changeState(int state);

  virtual void updateSleep(float time);
  virtual void updateNormal(float time);

  virtual void updateStates(float time);

  virtual void update(float time);
};

#endif
