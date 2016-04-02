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
class Plate : public Replace
{
  /**
   *
   *
   *
   */
  protected:
  int index;

  float startPositionX;
  float startPositionY;
  float startPositionZ;

  /**
   *
   *
   *
   */
  public:
  enum Type {
    NORMAL,
    BEST,
    SPIKES,
    UP,
    DOWN,
    DIAMOND,
    CRYSTAL,
    ENERGY,
    STAR,
    HEART,
    MOVED1,
    MOVED2,
    MOVED3,
    MOVED4
  };

  enum Side {
    LEFT,
    RIGHT
  };

  enum Behavior {
    STATIC,
    DYNAMIC
  };

  /**
   *
   *
   *
   */
  public:
  Plate();
 ~Plate();

  Type type;
  Behavior behavior;

  bool direction;
  bool position[2];
  bool moved;
  bool blocked;

  Decoration* decoration = nullptr;

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onRemove();
  virtual void onCount();

  virtual int getIndex();

  virtual float getStartPositionX();
  virtual float getStartPositionY();
  virtual float getStartPositionZ();

  virtual void setIndex(int index);

  virtual void setStartPositionX(float x);
  virtual void setStartPositionY(float y);
  virtual void setStartPositionZ(float z);

  virtual void setType(Type type, bool animated = true);

  virtual void remove();

  virtual void clearDecoration(bool force = false, bool animated = false);

  Plate* deepCopy();
};

#endif
