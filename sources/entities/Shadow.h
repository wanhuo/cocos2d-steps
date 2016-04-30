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

#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Shadow : public Entity3D
{
  /**
   *
   *
   *
   */
  protected:
  float size = 2.1;
  float position = 0.0;

  Vec3 maxScale = Vec3(10, 10, 10);
  Vec3 minScale = Vec3(0, 0, 0);

  Vec3 offset = Vec3(0.0, 0.0, 0.0);

  /**
   *
   *
   *
   */
  public:
  Shadow(const char* file);
 ~Shadow();

  virtual void setMaxScale(Vec3 scale);
  virtual void setMinScale(Vec3 scale);

  virtual void setOffset(Vec3 offset);

  virtual void setSize(float size);
  virtual void setPosition(float position);

  virtual Vec3 getMaxScale();
  virtual Vec3 getMinScale();

  virtual Vec3 getOffset();

  virtual float getSize();
  virtual float getPosition();
};

#endif
