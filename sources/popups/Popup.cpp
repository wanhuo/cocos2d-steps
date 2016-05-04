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
Popup::Popup()
{
  this->retain();
  this->bind(true);

  this->state->create = true;

  this->setScheduleUpdate(true);
}

Popup::Popup(const char* textureFilename)
: Popup()
{
  this->background = new Entity(textureFilename, this, true);
  this->background->setLocalZOrder(-1);
  this->background->getTexture()->setTexParameters({GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT});

  this->background->setPosition(Application->getCenter().x, Application->getCenter().y);
}

Popup::~Popup()
{
}

/**
 *
 *
 *
 */
void Popup::onShow()
{
  this->backgroundPosition = 0;
}

void Popup::onHide(Callback callback)
{
  Application->removeChild(this);

  if(callback)
  {
    callback();
  }
}

/**
 *
 *
 *
 */
void Popup::show()
{
  Application->addChild(this);
  this->setCameraMask(4);

  this->onShow();
}

void Popup::hide(Callback callback)
{
  this->onHide(callback);
}

/**
 *
 *
 *
 */
bool Popup::containsTouchLocation(cocos2d::Touch* touch)
{
  return true;
}

/**
 *
 *
 *
 */
void Popup::update(float time)
{
  if(this->background)
  {
    this->backgroundPosition += this->backgroundSpeed;
    this->background->setTextureRect(Rect(this->backgroundPosition, this->backgroundPosition, Application->getWidth(), Application->getHeight()));

    // TODO: Check 64-bit proccessors for large number penalty.
  }
}
