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

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Cube.h"

/**
 *
 *
 *
 */
class Character : public Cube
{
  /**
   *
   *
   *
   */
  private:
  const static int STATE_COPTER_TURNS = 10;

  /**
   *
   *
   *
   */
  protected:
  bool botEnabled;
  bool botWait;

  bool autoTurnLeft;
  bool autoTurnRight;
  bool manual;

  float soundTime;
  float soundTimeElapsed;

  float botTime;
  float botTimeElapsed;

  float botWaitTime;
  float botWaitTimeElapsed;

  float sound;
  float time;

  float turns;

  int lives;
  int steps;

  /**
   *
   *
   *
   */
  public:
  Entity3D* plane;

  enum State {
    NORMAL,
    JUMP,
    FALL,
    CRASH,
    HIT,
    STATE_COPTER
  };

  enum Crash {
    UNDEFINED,
    CATCH,
    SPIKES,
    DOWN,
    GATE,
    COPTER
  };

  enum Turn {
    NONE,
    LEFT,
    RIGHT
  };

  struct Plates {
    Plate* current = nullptr;
    Plate* previous = nullptr;
  };

  struct Nears {
    Plate* plates[2];

    /**
     *
     *
     *
     */
    Plate* next() {
      if(this->plates[0] && this->plates[1]) {
        return probably(50) ? this->plates[0] : this->plates[1];
      } else {
        if(this->plates[0]) return this->plates[0];
        if(this->plates[1]) return this->plates[1];
      }

      return nullptr;
    }
  };

  /**
   *
   *
   *
   */
  public:
  Character();
 ~Character();

  State state;
  Plates plates;

  virtual void reset();

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onSound(string file = "character-jump");

  virtual void onNormal();
  virtual void onJump();
  virtual void onFall();
  virtual void onCrash(Crash crash = UNDEFINED);
  virtual void onHit();
  virtual void onCopter();

  virtual bool onTouch();

  virtual void onTurn(bool action = true, bool set = true);
  virtual void onTurnLeft(bool action = true, bool set = true);
  virtual void onTurnRight(bool action = true, bool set = true);

  virtual void onTurnUpdate(Plate* custom = nullptr);
  virtual void onTurnUpdate(Turn index, Plate* custom = nullptr);
  virtual void onTurn(Turn index);

  virtual void onLandSuccessful(Turn turn, Plate* plate, bool proceed = true);
  virtual void onLandFail(Turn turn, Plate* plate);

  virtual void onMoveLeft();
  virtual void onMoveRight();

  virtual void onEnvironmentMoveLeft();
  virtual void onEnvironmentMoveRight();

  virtual bool getManual();
  virtual bool setManual(bool manual);

  virtual int addLive(int count = 1);
  virtual int removeLive(int count = 1);

  virtual bool isPlateLeftBlocked();
  virtual bool isPlateRightBlocked();

  virtual Plate* getPlateLeft(Plate* current = nullptr);
  virtual Plate* getPlateRight(Plate* current = nullptr);

  virtual Plate* getPlateLeftWithDefaults(Plate* current = nullptr);
  virtual Plate* getPlateRightWithDefaults(Plate* current = nullptr);

  virtual Nears getPlatesNear(Plate* current = nullptr);
  virtual Nears getPlatesNearWithDefaults(Plate* current = nullptr);

  virtual void changeState(State state, Crash crash = UNDEFINED);

  virtual void updateNormal(float time);
  virtual void updateJump(float time);
  virtual void updateFall(float time);
  virtual void updateCrash(float time);
  virtual void updateHit(float time);
  virtual void updateCopter(float time);

  virtual void updateStates(float time);

  virtual void update(float time);

  /**
   *
   *
   *
   */
  public:
  virtual void setPosition3D(const Vec3& position);
  virtual void setPositionX(float x);
  virtual void setPositionY(float y);
  virtual void setPositionZ(float z);

  virtual Vec3 getPosition3D() const;
  virtual float getPositionX();
  virtual float getPositionY();
  virtual float getPositionZ();
};

#endif
