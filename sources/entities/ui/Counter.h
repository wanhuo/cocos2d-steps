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

#ifndef _COUNTER_H_
#define _COUNTER_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Counter : public Background
{
  /**
   *
   *
   *
   */
  private:
  struct Texts {
    Text* name;
    Text* stage;
    Text* score;
    Text* coins;
    Text* best;
    Text* bonus;
  };

  struct Count {
    int add = 0;
    int remove = 0;
  };

  /**
   *
   *
   *
   */
  protected:
  Count count;

  ProgressTimer* starAction;

  struct BoolValues {
    bool mission = false;
    bool best = false;

    bool special = false;
    bool daily = false;
  };

  struct Values {
    BoolValues b;

    int current = 0;
    int best = 0;
    int start = 0;
    int coins = 0;
  };

  /**
   *
   *
   *
   */
  public:
  Counter(Node* parent);
 ~Counter();

  Texts texts;
  Values values;

  MissionUpdateOnce missionUpdateOnce;
  MissionUpdateProgress missionUpdateProgress;

  BackgroundColor* holder;

  Entity* starBackground;
  Entity* bonusBackground;

  CameraEntity3D* icon;

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

  virtual void onStarStart();
  virtual void onStarFinish();
  virtual void onStarUpdate();

  virtual void onCount();
  virtual void onCoins();

  virtual void onBest();
  virtual void onRegular();

  virtual void reset(bool init = false);
  virtual void save();

  virtual void add(int count);
  virtual void remove(int count);

  virtual void update();

  virtual MissionUpdate getMissionsUpdate() const;
  virtual void resetMissionsUpdate();

  void resetOnceMissionsUpdate();
  void resetProgressMissionsUpdate();
};

#endif
