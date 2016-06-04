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
#include "CameraEntity3D.h"
#include "Button.h"
#include "Text.h"
#include "Background.h"
#include "BackgroundColor.h"
#include "Screen.h"
#include "Pool.h"
#include "Spine.h"

#include "Counter.h"
#include "Capture.h"
#include "Button3D.h"
#include "Gift.h"
#include "Video.h"
#include "Unlock.h"

#include "Generator.h"
#include "Letters.h"

#include "Letter.h"

#include "Environment.h"
#include "Ground.h"
#include "Cube.h"
#include "Shadow.h"
#include "Decoration.h"
#include "Special.h"
#include "Portal.h"
#include "Trampoline.h"
#include "Down.h"
#include "Character.h"
#include "Enemy.h"
#include "Particle.h"

#include "Pickup.h"
#include "Diamond.h"
#include "Crystal.h"
#include "Energy.h"
#include "Heart.h"
#include "Star.h"
#include "Color.h"
#include "Presention.h"
#include "Insane.h"
#include "Let.h"

#include "Start.h"
#include "Spikes.h"
#include "Trap.h"
#include "Saw.h"
#include "Door.h"
#include "Copter.h"
#include "Cub.h"

#include "Plate.h"
#include "TypeSimple.h"
#include "TypeDuel.h"
#include "TypeBest.h"
#include "TypeBonus.h"
#include "TypeFinish.h"
#include "TypeSaw.h"
#include "TypeGate.h"
#include "TypeCopter.h"
#include "TypeSpikes.h"
#include "TypeTrap.h"
#include "TypePortal.h"
#include "TypeTrampoline.h"
#include "TypeMoveUp.h"
#include "TypeMoved.h"
#include "TypeMoved1.h"
#include "TypeMoved2.h"
#include "TypeMoved3.h"
#include "TypeMoved4.h"
#include "TypeMoved5.h"

#include "Menu.h"
#include "Finish.h"
#include "Open.h"
#include "Present.h"
#include "Watch.h"

#include "EnvironmentStoreItem.h"
#include "EnvironmentStoreCharacter.h"
#include "EnvironmentStoreTexture.h"
#include "EnvironmentStoreBar.h"

#include "EnvironmentMissionsItem.h"
#include "EnvironmentMissionsPopup.h"
#include "EnvironmentMissionsDailyPopup.h"
#include "EnvironmentMissionsKetchappPopup.h"
#include "EnvironmentMissionsNotify.h"
#include "EnvironmentMissionsBar.h"
#include "EnvironmentMissionsFinish.h"
#include "EnvironmentMissionsFinishGeneral.h"
#include "EnvironmentMissionsFinishKetchapp.h"
#include "EnvironmentMissionsFinishDaily.h"

#include "RotateGlobalBy.h"
#include "Shake.h"

/**
 *
 *
 *
 */
#define SERVICES_LEADERBOARD_BEST_SCORE 0
#define SERVICES_LEADERBOARD_STAGES_COUNT 1

/**
 *
 *
 *
 */
#define Application Game::getInstance()
#define Generators Application->environment->generator
#define s(parameter) to_string(parameter)

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
    Camera* s;
    Camera* e;
    Camera* c;
    Camera* u;
  };
  
  struct Elapsed {
    int ad = -1;
    int video = 0;
    int present = random(0, 15);
  };

  struct Parameters {
    bool showPresent = false;
    bool showVideo = false;

    string presentTexture = "ui/gift-texture-1.png";

    int ad = 4;
    int video = 4;
    int present = 15;

    Elapsed elapsed;
  };

  const static int SCALE_FACTOR = 70;

  const static int NEAR = 1;
  const static int FAR = 10000;

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
    FINISH,
    LOSE,
    STORE,
    MISSIONS,
    PRESENT,
    OPEN,
    WATCH,
    MISSION_COMPLETE
  };

  /**
   *
   *
   *
   */
  public:
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
  public:
  static Game* getInstance();

  Game();
 ~Game();

  Parameters parameters;

  BackgroundColor* s;
  BackgroundColor* d;

  Entity* i;

  Environment* environment;
  Cameras cameras;

  Counter* counter;
  Capture* capture;

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
  virtual void onFinish();
  virtual void onLose();
  virtual void onStore();
  virtual void onMissions();
  virtual void onPresent();
  virtual void onOpen();
  virtual void onWatch();
  virtual void onMissionComplete();

  virtual void onNoad();

  virtual float getFrustumWidth() { return this->getWidth() / SCALE_FACTOR; }
  virtual float getFrustumHeight() { return this->getHeight() / SCALE_FACTOR; }

  virtual void changeState(State state);

  virtual void updateMenu(float time);
  virtual void updateGame(float time);
  virtual void updateLose(float time);
  virtual void updateStore(float time);
  virtual void updateMissions(float time);
  virtual void updatePresent(float time);
  virtual void updateFinish(float time);
  virtual void updateOpen(float time);
  virtual void updateWatch(float time);
  virtual void updateMissionComplete(float time);

  virtual void updateStates(float time);

  virtual void update(float time);
};

#endif
