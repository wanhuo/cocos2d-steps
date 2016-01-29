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

#include "Game.h"

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
  const static int TURN_LEFT = 1;
  const static int TURN_RIGHT = 2;

  const static int PARTICLES_COUNT = 10;

  Environment* environment;

  /**
   *
   *
   *
   */
  protected:
  float sound;
  float time;

  Entity3D* plane;

  Pool* numbers;

  /**
   *
   *
   *
   */
  public:
  struct NearPlates
  {
    Plate* LEFT = nullptr;
    Plate* RIGHT = nullptr;

    Plate* next()
    {
      if(LEFT && RIGHT)
      {
        return probably(50) ? LEFT : RIGHT;
      }
      else
      {
        if(LEFT) return LEFT;
        if(RIGHT) return RIGHT;
      }
    }
  };

  struct Plates
  {
    Plate* current;
    Plate* previous;
  };

  const static int STATE_NONE = 0;
  const static int STATE_NORMAL = 1;
  const static int STATE_JUMP = 2;
  const static int STATE_FALL = 3;
  const static int STATE_CRASH = 4;
  const static int STATE_HIT = 5;

  Character(Environment* environment);
 ~Character();

  int state;
  int lives;

  bool manual;

  Plates plates;

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onNormal();
  virtual void onJump();
  virtual void onFall();
  virtual void onCrash();
  virtual void onHit();

  virtual bool onTouch();

  virtual void onTurnLeft();
  virtual void onTurnRight();
  virtual void onTurnUpdate(int index, Plate* custom = nullptr);
  virtual void onTurn(int index);

  virtual void onMoveLeft();
  virtual void onMoveRight();

  virtual Plate* getPlateLeft(Plate* current = nullptr);
  virtual Plate* getPlateRight(Plate* current = nullptr);

  virtual Plate* getPlateLeftWithDefaults(Plate* current = nullptr);
  virtual Plate* getPlateRightWithDefaults(Plate* current = nullptr);

  virtual NearPlates getPlatesNear(Plate* current = nullptr);

  virtual void changeState(int state);

  virtual void updateNormal(float time);
  virtual void updateJump(float time);
  virtual void updateFall(float time);
  virtual void updateCrash(float time);
  virtual void updateHit(float time);

  virtual void updateStates(float time);

  virtual void update(float time);
};

#endif
