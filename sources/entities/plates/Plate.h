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
  vector<Decoration*> decorations;

  /**
   *
   *
   *
   */
  protected:
  int index;
  int stage;

  bool direction;

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
    NORMAL, // 0

    START, // 1
    FINISH, // 2
    BEST, // 3
    BONUS, // 4

    DIAMOND, // 5
    CRYSTAL, // 6
    ENERGY, // 7
    STAR, // 8
    HEART, // 9
    COLOR, // 10

    SPIKES, // 11
    TRAMPOLINE, // 12
    DOWN, // 13
    CUB, // 14
    SAW, // 15
    GATE, // 16
    COPTER, // 17
    TRAP, // 18

    MOVE_UP, // 19
    MOVED1, // 20
    MOVED2, // 21
    MOVED3, // 22
    MOVED4, // 23,

    PRESENTION, // 24
    LETTER, // 25,

    PORTAL, // 26

    MOVED5 // 27
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

  bool position[2];
  bool moved;
  bool avoid;
  bool blocked;

  Special* special = nullptr;

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onPrepare();
  virtual void onRemove(bool complete = true);

  virtual void onCount();
  virtual void onUncount();

  virtual bool getDirection();
  virtual int getIndex();
  virtual int getStage();

  virtual float getStartPositionX();
  virtual float getStartPositionY();
  virtual float getStartPositionZ();

  virtual vector<Decoration*> &getDecorations();

  virtual void setDirection(bool direction);
  virtual void setIndex(int index);

  virtual void setStartPositionX(float x);
  virtual void setStartPositionY(float y);
  virtual void setStartPositionZ(float z);

  virtual void setType(int type, bool animated = true, char data = ' ');
  virtual void setStage(int stage);

  virtual void prepare();
  virtual void remove(bool complete = true);

  virtual void start();

  virtual bool conditions(int type);

  virtual void clearDecorations();
  virtual void clearSpecial();

  Plate* deepCopy();

  /**
   *
   *
   *
   */
  virtual void setOpacity(GLubyte opacity);
  virtual void setVisibility(bool visible);

  virtual void setPositionX(float x);
  virtual void setPositionY(float y);
  virtual void setPositionZ(float z);

  virtual void setPosition3D(Vec3 position);

  virtual void setTexture(const std::string& texture);
};

#endif
