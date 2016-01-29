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

#ifndef _PLATE_H_
#define _PLATE_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Plate : public Cube
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

  /**
   *
   *
   *
   */
  public:
  const static int TYPE_NORMAL = 0;
  const static int TYPE_SPIKES = 1;
  const static int TYPE_DIAMOND = 2;
  const static int TYPE_CRYSTAL = 3;
  const static int TYPE_ENERGY = 4;
  const static int TYPE_STAR = 5;
  const static int TYPE_HEART = 6;

  const static int TYPE_MOVED_1 = 20;
  const static int TYPE_MOVED_2 = 21;

  const static int TYPE_MOVED_3 = 22;
  const static int TYPE_MOVED_4 = 23;

  const static int TYPE_MOVED_5 = 24;
  const static int TYPE_MOVED_6 = 25;

  Plate();
 ~Plate();

  int type;

  bool LEFT;
  bool RIGHT;

  bool moved;
  bool position;

  float startPositionX = 0;
  float startPositionY = 0;
  float startPositionZ = 0;

  Decoration* decoration = nullptr;
  Entity3D* special = nullptr;

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void setOpacity(GLubyte opacity);
  virtual void setPositionX(float x);
  virtual void setPositionY(float y);
  virtual void setPositionZ(float z);
  virtual void setPosition3D(Vec3 position);
  virtual Action* runAction(Action* action);

  virtual void setType(int type, bool animated = true);

  virtual void clearDecoration(bool force = false, bool animated = false);

  virtual void update(float time);

  Plate* deepCopy();
};

#endif
