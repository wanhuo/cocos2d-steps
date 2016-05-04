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

#ifndef _PRESENTION_H_
#define _PRESENTION_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Presention : public Pickup
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
  string texture;
  vector<string> textures = {
    "ui/gift-texture-1.png",
    "ui/gift-texture-2.png",
    "ui/gift-texture-3.png",
    "ui/gift-texture-4.png",
    "ui/gift-texture-5.png",
    "ui/gift-texture-6.png",
    "ui/gift-texture-7.png",
    "ui/gift-texture-8.png",
    "ui/gift-texture-9.png",
    "ui/gift-texture-10.png",
    "ui/gift-texture-11.png",
    "ui/gift-texture-12.png",
    "ui/gift-texture-13.png",
    "ui/gift-texture-14.png"
  };

  /**
   *
   *
   *
   */
  public:
  Presention();
 ~Presention();

  virtual void onCreate();
  virtual void onDestroy(bool action = false);

  virtual void onPickup();

  virtual void setPlate(Plate* plate, bool animated = true);

  virtual const Color3B& getColor(void) const override;

  Presention* deepCopy();
};

#endif
