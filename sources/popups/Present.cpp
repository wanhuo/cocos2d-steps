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
Present* Present::instance;

/**
 *
 *
 *
 */
Present* Present::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Present::Present()
: Finish()
{
  instance = this;

  this->background = new BackgroundColor(this, Color4B(0.0, 0.0, 0.0, 200.0));
  this->background->setLocalZOrder(-1);

  this->element = new Gift(this);
}

Present::~Present()
{
}

/**
 *
 *
 *
 */
void Present::onShow()
{
  Popup::onShow();

  /**
   *
   *
   *
   */
  this->element->_create();
}

void Present::onHide(Callback callback)
{
  Finish::onHide(callback);

  /**
   *
   *
   *
   */
  this->element->_destroy();
}

/**
 *
 *
 *
 */
void Present::onTouchStart(cocos2d::Touch* touch, cocos2d::Event* e)
{
  if(!this->element->touch->binded)
  {
    Finish::onTouchStart(touch, e);
  }
}

/**
 *
 *
 *
 */
void Present::show()
{
  Finish::show();
}

void Present::hide(Callback callback)
{
  Finish::hide(callback);
}