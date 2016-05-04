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
: Popup("ui/store-background-texture.png")
{
  instance = this;

  this->texts.claim = new Text("present-claim", this);
  this->texts.con = new Text("present-con", this);

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
  Popup::onHide(callback);

  /**
   *
   *
   *
   */
  this->element->_destroy();

  this->texts.claim->_destroy();
  this->texts.con->_destroy();
}

/**
 *
 *
 *
 */
void Present::onTouchStart(cocos2d::Touch* touch, cocos2d::Event* e)
{
  this->hide([=] () {
    Application->changeState(Game::FINISH);
  });
}

/**
 *
 *
 *
 */
void Present::show()
{
  this->texts.claim->_create();
  this->texts.con->_create();

  this->texts.claim->setOpacity(0);
  this->texts.con->setOpacity(0);

  this->texts.claim->setPosition(Application->getWidth() / 2, 100);
  this->texts.con->setPosition(Application->getWidth() / 2, 100);

  this->texts.claim->runAction(
    Sequence::create(
      FadeIn::create(0.2),
      CallFunc::create([=] () {
      this->texts.claim->runAction(
        RepeatForever::create(
          Sequence::create(
            FadeOut::create(0.5),
            FadeIn::create(0.5),
            nullptr
          )
        )
      );
      }),
      nullptr
    )
  );

  Popup::show();
}

void Present::hide(Callback callback)
{
  Popup::hide(callback);
}
