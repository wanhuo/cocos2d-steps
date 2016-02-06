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

#include "ui/CocosGUI.h"

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
  private:
  static Store* instance;

  struct Parameters {
    float time = 0.6;
    float height = 930;
    float opacity = 200;
    float padding = 200;
  };

  struct Buttons {
    Button* close;
    Button* facebook;
    Button* twitter;
    Button* mail;
    Button* restore;
  };

  struct Texts
  {
    Text* title[23];
  };

  /**
   *
   *
   *
   */
  protected:
  Buttons buttons;

  Entity* background;
  cocos2d::ui::ScrollView* scroll;

  Background* holder;
  Background* decorations;

  Entity* decoration1;
  Entity* decoration2;
  Entity* decoration3;

  Entity* powered1;
  Entity* powered2;

  Parameters parameters;
  Texts texts;

  float size;

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

  virtual void update(float time);
};

#endif
