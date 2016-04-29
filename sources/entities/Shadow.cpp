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

#include "Game.h"

/**
 *
 *
 *
 */
Shadow::Shadow(const char* file)
: Entity3D(file, Application->environment->plane)
{
  this->setColor(Color3B(0, 0, 0));
  this->setOpacity(30);

  this->setLightMask(2048);
}

Shadow::~Shadow()
{
}

/**
 *
 *
 *
 */
void Shadow::setMaxScale(Vec3 scale)
{
  this->maxScale = scale;
}

void Shadow::setMinScale(Vec3 scale)
{
  this->minScale = scale;
}

void Shadow::setSize(float size)
{
  this->size = size;
}

void Shadow::setPosition(float position)
{
  this->position = position;
}

Vec3 Shadow::getMaxScale()
{
  return this->maxScale;
}

Vec3 Shadow::getMinScale()
{
  return this->minScale;
}

float Shadow::getSize()
{
  return this->size;
}

float Shadow::getPosition()
{
  return this->position;
}
