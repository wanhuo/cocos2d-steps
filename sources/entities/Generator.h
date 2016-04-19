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

#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Plate;

/**
 *
 *
 *
 */
class Generator : public Ref
{
  /**
   *
   *
   *
   */
  private:
  const static int ROUTE_LENGTH_MAX = 3;
  const static int ROUTE_LENGTH_MIN = 0;

  /**
   *
   *
   *
   */
  protected:
  struct Conditions {
    int s1;
    int s2;
    int s3;
  };

  Conditions conditions;

  /**
   *
   *
   *
   */
  public:
  const static int PLATES_START = 8;
  const static int PLATES_SAVE = 5;
  const static int PLATES_FINISH = 300;
  const static int PLATES_FINISH_BONUS = 22;
  const static int PLATES_PROBABILITY = 50;

  Generator();
 ~Generator();

  float x;
  float y;
  float z;

  int index;
  int count;
  int length;
  int resets;

  bool direction;
  bool bonus;

  virtual Plate* create();
  virtual void destroy(bool manual = false);

  virtual void clear();
};

#endif
