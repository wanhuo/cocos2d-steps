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
Decoration::Decoration(const char* file)
: Entity3D(file)
{
}

Decoration::~Decoration()
{
}

/**
 *
 *
 *
 */
void Decoration::onCreate()
{
  Entity3D::onCreate();

  /**
   *
   *
   *
   */
  this->setOpacity(0);
}

void Decoration::onDestroy(bool action)
{
  Entity3D::onDestroy(action);
}

/**
 *
 *
 *
 */
void Decoration::onPickup()
{
}

/**
 *
 *
 *
 */
void Decoration::setPlate(Plate* plate, bool animated)
{
  this->setPosition3D(plate->getPosition3D());

  if(animated)
  {
    this->runAction(
      Spawn::create(
        EaseSineOut::create(
          MoveBy::create(0.5, Vec3(0, 5, 0))
        ),
        FadeTo::create(0.5, 255),
        nullptr
      )
    );
  }
}

/**
 *
 *
 *
 */
void Decoration::remove(bool force)
{
  if(force)
  {
    this->_destroy(true);
  }
  else
  {
    this->runAction(
      Spawn::create(
        Sequence::create(
          EaseSineInOut::create(
            MoveBy::create(0.2, Vec3(0, 1.0, 0))
          ),
          EaseSineInOut::create(
            MoveBy::create(0.4, Vec3(0, -6.0, 0))
          ),
          CallFunc::create([=] () {
            this->_destroy(true);
          }),
          nullptr
        ),
        Sequence::create(
          DelayTime::create(0.3),
          FadeOut::create(0.1),
          nullptr
        ),
        nullptr
      )
    );
  }
}

bool Decoration::status()
{
  return false;
}

/**
 *
 *
 *
 */
const char* Decoration::getParticleTexture()
{
  return "";
}
