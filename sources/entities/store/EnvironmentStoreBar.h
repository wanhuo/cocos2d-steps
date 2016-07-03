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

#ifndef _ENVIRONMENTSTOREBAR_H_
#define _ENVIRONMENTSTOREBAR_H_

#include "Game.h"

/**
 *
 *
 *
 */
class EnvironmentStoreBar : public Background
{
  /**
   *
   *
   *
   */
  public:
  class EnvironmentStoreBarButton : public BackgroundColor
  {
    /**
     *
     *
     *
     */
    protected:
    Text* text;

    /**
     *
     *
     *
     */
    public:
    EnvironmentStoreBarButton(Node* parent);
   ~EnvironmentStoreBarButton();

    int index;

    virtual void onEnter();
    virtual void onExit();

    virtual void onTouchStart(cocos2d::Touch* touch, Event* e);
    virtual void onTouchFinish(cocos2d::Touch* touch, Event* e);
    virtual void onTouchCancelled(cocos2d::Touch* touch, Event* e);

    virtual void onTouch(cocos2d::Touch* touch, Event* e);
  };

  /**
   *
   *
   *
   */
  public:
  class EnvironmentStoreBarButtonCharacters : public EnvironmentStoreBarButton
  {
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
    EnvironmentStoreBarButtonCharacters(Node* parent);
   ~EnvironmentStoreBarButtonCharacters();
  };

  /**
   *
   *
   *
   */
  public:
  class EnvironmentStoreBarButtonTextures : public EnvironmentStoreBarButton
  {
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
    EnvironmentStoreBarButtonTextures(Node* parent);
   ~EnvironmentStoreBarButtonTextures();
  };

  /**
   *
   *
   *
   */
  private:
  struct Buttons {
    Button* play;
    Button* lock;
    Button* facebook;
    Button* twitter;
    Button* back;
  };

  struct Backgrounds {
    Background* missions;
    Background* diamonds;
    Background* random;
    Background* facebook;
    Background* twitter;
  };

  struct Texts {
    Text* back;
    Text* missions;
    Text* diamonds;
    Text* random;
    Text* facebook;
    Text* twitter;
  };

  EnvironmentStoreItem* selectedCharacter;
  EnvironmentStoreItem* selectedTexture;

  /**
   *
   *
   *
   */
  protected:
  Backgrounds backgrounds;
  Buttons buttons;
  Texts texts;

  CameraEntity3D* diamond;

  /**
   *
   *
   *
   */
  public:
  EnvironmentStoreBar();
 ~EnvironmentStoreBar();

  struct Element {
    int type;
    int index;
  };

  int index;

  EnvironmentStoreBarButton* characters;
  EnvironmentStoreBarButton* textures;
  EnvironmentStoreBarButton* toogle;

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onCreateCharacters();
  virtual void onCreateTextures();

  virtual void onChange(int index);

  virtual void onSelect(EnvironmentStoreItem* element);
  virtual void onSelectCharacter(int index);
  virtual void onSelectTexture(int index);

  virtual int randomCharacter(bool locked = false);
  virtual int randomTexture(bool locked = false);

  virtual Element nextElement();
};

#endif
