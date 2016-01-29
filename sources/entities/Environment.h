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
class Whale;

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

  /**
   *
   *
   *
   */
  protected:
  float createFishTime = 0;
  float createFishTimeElapsed = 0;

  /**
   *
   *
   *
   */
  public:
  const static int DUSTS_COUNT = 50;

  const static int MAX_FISH_COUNT = 5;
  const static int MAX_SHIP_COUNT = 2;

  const static int MIN_FISH_TIME = 1;
  const static int MAX_FISH_TIME = 3;

  Environment(Node* parent);
 ~Environment();

  Character* character;
  Whale* whale;

  Generator* generator;

  Pool* dusts;

  Pool* spikes;
  Pool* diamonds;
  Pool* crystals;
  Pool* energies;
  Pool* stars;
  Pool* hearts;

  Pool* plates;
  Pool* particles;
  Pool* fishes;
  Pool* leafs;
  Pool* ripples;

  Entity3D* plane;
  Entity3D* water;

  virtual void create();

  virtual Node* createRipple(float x, float z, float scale = 1.0);
  virtual Node* createParticle(float x, float y, float z);

  virtual Vec3 position();

  virtual void onTurnLeft();
  virtual void onTurnRight();

  virtual void onMenu();
  virtual void onGame();
  virtual void onLose();

  virtual void updateDusts(float time);
  virtual void updateFishes(float time);

  virtual void updateMenu(float time);
  virtual void updateGame(float time);
  virtual void updateLose(float time);

  virtual void update(float time);
};

#endif
