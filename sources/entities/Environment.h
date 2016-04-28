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

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Character;
class Ground;
class Decoration;

/**
 *
 *
 *
 */
class Environment : public Background
{
  /**
   *
   *
   *
   */
  private:
  struct Light {
    BaseLight* environment;
    BaseLight* natural;
    BaseLight* character;
  };

  struct Plates {
  };

  /**
   *
   *
   *
   */
  private:
  const static int ACCELEROMETER_FACTOR = 10;
  const static int ACCELERATION_FACTOR = 10;

  float accelerometerX = 0;
  float accelerometerY = 0;
  float accelerometerZ = 0;

  float accelerationX = 0;
  float accelerationY = 0;
  float accelerationZ = 0;

  float platesTime;
  float platesTimeElapsed;

  /**
   *
   *
   *
   */
  public:
  const static int STAR_TIME = 5;

  Environment(Node* parent);
 ~Environment();

  bool star;

  float starTime;
  float starTimeElapsed;

  Light light;

  Character* character;

  Generator* generator = nullptr;

  Entity3D* plane;

  Pool* starts;
  Pool* spikes;
  Pool* ups;
  Pool* downs;
  Pool* cubs;
  Pool* diamonds;
  Pool* crystals;
  Pool* energies;
  Pool* stars;
  Pool* hearts;
  Pool* colors;

  Pool* plates;
  Pool* plates_spikes;
  Pool* plates_up;
  Pool* plates_saw;
  Pool* plates_gate;
  Pool* plates_copter;
  Pool* particles;

  Ground* ground;

  Background* characterActionHolder;
  BackgroundColor* characterActionBackground;
  BackgroundColor* characterAction;

  virtual void create();

  virtual Entity3D* createParticle(float x, float y, float z);

  virtual void onAccelerate(Acceleration* acceleration, Event* e);

  virtual void onTurn(bool action = true);

  virtual void onMenu();
  virtual void onGame();
  virtual void onLose();
  virtual void onCopter();
  virtual void onFinish();

  virtual void startStar();
  virtual void finishStar();

  virtual void updateLight(float time);

  virtual void updateStar(float time);

  virtual void updateMenu(float time);
  virtual void updateGame(float time);
  virtual void updateLose(float time);

  virtual void update(float time);
};

#endif
