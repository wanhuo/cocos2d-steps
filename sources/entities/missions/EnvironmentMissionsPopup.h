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

#ifndef _ENVIRONMENTMISSIONSPOPUP_H_
#define _ENVIRONMENTMISSIONSPOPUP_H_

#include "Game.h"

/**
 *
 *
 *
 */
class EnvironmentMissionsPopup : public BackgroundColor
{
  /**
   *
   *
   *
   */
  public:
  class MissionTask : public Entity
  {
    /**
     *
     *
     *
     */
    public:
    MissionTask(Node* parent);
   ~MissionTask();

    Text* text;
    Text* action;

    TiledEntity* element;
    TiledEntity* element2;

    virtual void onCreate();
    virtual void onDestroy(bool action = false);

    virtual void onEnter();
    virtual void onExit();

    virtual void updateData(int mission, MissionStruct* structure = nullptr);
  };

  /**
   *
   *
   *
   */
  private:
  struct Texts {
    Text* background;
    Text* mission;
  };

  vector<MissionTask*> missions;

  /**
   *
   *
   *
   */
  protected:
  Texts texts;

  BackgroundColor* background;

  /**
   *
   *
   *
   */
  public:
  EnvironmentMissionsPopup(Node* parent);
 ~EnvironmentMissionsPopup();

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onEnter();
  virtual void onExit();

  virtual void updateData(int index);
};

#endif
