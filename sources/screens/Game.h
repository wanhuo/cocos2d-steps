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

#ifndef _GAME_H_
#define _GAME_H_

#include "Entity.h"
#include "TiledEntity.h"
#include "AnimatedEntity.h"
#include "Entity3D.h"
#include "Button.h"
#include "Text.h"
#include "Background.h"
#include "BackgroundColor.h"
#include "Screen.h"
#include "Pool.h"

#include "Generator.h"

#include "Dust.h"

#include "Environment.h"
#include "Cube.h"
#include "Shadow.h"
#include "Decoration.h"
#include "Special.h"
#include "Pickup.h"
#include "Up.h"
#include "Down.h"
#include "Diamond.h"
#include "Crystal.h"
#include "Energy.h"
#include "Star.h"
#include "Heart.h"
#include "Plate.h"
#include "Character.h"
#include "Particle.h"
#include "Fish.h"
#include "Ripple.h"

#include "Spike.h"
#include "Saw.h"
#include "Door.h"
#include "Copter.h"

#include "TypeSaw.h"
#include "TypeGate.h"
#include "TypeCopter.h"

#include "Counter.h"

#include "Menu.h"
#include "Finish.h"
#include "Store.h"

#include "Color.h"

#include "RotateGlobalBy.h"
#include "Shake.h"

#include "Item.h"

/**
 *
 *
 *
 */
#define Application Game::getInstance()

/**
 *
 *
 *
 */
class Game : public Screen
{
  /**
   *
   *
   *
   */
  private:
  static Game* instance;

  struct Cameras {
    Camera* d;
    Camera* c;
    Camera* s;
    Camera* e;
  };

  const static int SCALE_FACTOR = 70;

  const static int NEAR = 1;
  const static int FAR = 100;

  /**
   *
   *
   *
   */
  public:
  const static int SOUND_DISTANCE = 5;

  enum State {
    NONE,
    MENU,
    GAME,
    LOSE,
    STORE
  };

  /**
   *
   *
   *
   */
  private:
  float startCameraX;
  float startCameraY;
  float startCameraZ;

  float startCameraRotationX;
  float startCameraRotationY;
  float startCameraRotationZ;

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

  /**
   *
   *
   *
   */
  public:
  static Game* getInstance();

  Game();
 ~Game();

  Environment* environment;
  Cameras cameras;

  Counter* counter;

  State state = NONE;

  virtual void onTouchStart(cocos2d::Touch* touch, Event* event);
  virtual void onTouchFinish(cocos2d::Touch* touch, Event* event);

  virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, Event *event);
  virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, Event *event);

  virtual void onEnter();
  virtual void onExit();

  virtual void onBack();

  virtual void onLeaderboards();
  virtual void onAchievements();
  virtual void onRate();
  virtual void onLike();
  virtual void onShare();
  virtual void onTwitter();
  virtual void onFacebook();
  virtual void onMail();
  virtual void onRestorePurchases();

  virtual void onMenu();
  virtual void onGame();
  virtual void onLose();
  virtual void onStore();

  virtual void onNoad();

  virtual void changeState(State state);

  virtual void updateMenu(float time);
  virtual void updateGame(float time);
  virtual void updateLose(float time);
  virtual void updateStore(float time);

  virtual void updateStates(float time);

  virtual void update(float time);
};

#endif
