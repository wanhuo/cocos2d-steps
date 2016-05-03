/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 *
 * License: Tooflya Inc. Software License v1.
 *
 * Licensee may not use this software for commercial purposes. For the purpose of this license,
 * commercial purposes means that a 3rd party has to pay in order to access Software or that
 * the Website that runs Software is behind a paywall. In consideration of the License granted
 * under clause 2, Licensee shall pay Licensor a fee, via Credit-Card, PayPal or any other
 * mean which Licensor may deem adequate. Failure to perform payment shall construe as material
 * breach of this Agreement. This software is provided under an AS-IS basis and without any support,
 * updates or maintenance. Nothing in this Agreement shall require Licensor to provide Licensee with
 * support or fixes to any bug, failure, mis-performance or other defect in The Software.
 *
 * @cocos2d
 *
 */

#ifndef _STORE_H_
#define _STORE_H_

#include "Popup.h"

#include "BackgroundScroll.h"

/**
 *
 *
 *
 */
class Store : public Popup
{
  /**
   *
   *
   *
   */
  public:
  class Position : public BackgroundColor {

    /**
     *
     *
     *
     */
    private:
    enum State {
      NONE,
      MISSIONS,
      DIAMONDS,
      UNLOCKED,
      SELECTED
    };

    struct Parameters {
      const char* id;
      int index;
      int missions;
      int diamonds;
    };

    struct Texts {
      Text* missions;
      Text* diamonds;
    };

    /**
     *
     *
     *
     */
    protected:
    int state;

    Parameters parameters;
    Texts texts;

    Entity* lock;
    Entity* diamond;

    TiledEntity* texture;

    /**
     *
     *
     *
     */
    public:
    const static int WIDTH = 218;
    const static int HEIGHT = 184;

    const static int PX = 16;
    const static int PY = 20;

    Position(Node* parent, Json* parameters);
   ~Position();

    virtual void setState(State state);
    virtual void saveState();
    virtual void updateState();

    virtual void onEnter();
    virtual void onExit();

    virtual void onTouchStart(cocos2d::Touch* touch, Event* e);
    virtual void onTouchFinish(cocos2d::Touch* touch, Event* e);
    virtual void onTouchCancelled(cocos2d::Touch* touch, Event* e);

    virtual void onTouch(cocos2d::Touch* touch, Event* e);

    virtual void onSelect();
    virtual void onPurchase();
  };

  /**
   *
   *
   *
   */
  private:
  static Store* instance;

  struct Buttons {
    Button* back;
  };

  BackgroundScroll* scroll;

  /**
   *
   *
   *
   */
  protected:
  const static int ROW = 3;

  Buttons buttons;

  vector<Position*> positions;

  /**
   *
   *
   *
   */
  public:
  static Store* getInstance();

  Store();
 ~Store();

  virtual void onShow();
  virtual void onHide(Callback callback = NULL);

  virtual void show();
  virtual void hide(Callback callback = NULL);

  virtual void onEnter();
  virtual void onExit();

  virtual void update();
};

#endif
