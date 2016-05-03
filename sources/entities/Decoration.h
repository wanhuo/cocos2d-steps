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

#ifndef _DECORATION_H_
#define _DECORATION_H_

#include "Game.h"
#include "Character.h"

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
class Decoration : public Cube
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
  Plate* plate = nullptr;

  /**
   *
   *
   *
   */
  public:
  Decoration(string file, Node* parent);
  Decoration(string file);
  Decoration(Node* parent);
  Decoration();
 ~Decoration();

  bool unremovable = false;
  bool removable = false;
  bool stopable = false;
  bool enable = false;

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onPickup();
  virtual void onSound();

  virtual void setPlate(Plate* plate, bool animated = true);

  virtual Character::Crash status();

  virtual Decoration* deepCopy();
};

#endif
