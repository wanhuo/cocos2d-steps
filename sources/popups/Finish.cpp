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
Finish* Finish::instance;

/**
 *
 *
 *
 */
Finish* Finish::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Finish::Finish()
: Popup()
{
  instance = this;

  this->texts.tap = new Text("finish-tap", this, true);

  this->buttons.like = new Button("like-button.png", 2, 1, this, std::bind(&Game::onRate, Application), true);
  this->buttons.noad = new Button("noad-button.png", 2, 1, this, std::bind(&Game::onRate, Application), true);
  this->buttons.share = new Button("share-button.png", 2, 1, this, std::bind([=] () {
    this->hide([=] () {
      Store::getInstance()->show();
    });
  }), true);
  this->buttons.leaderboards = new Button("leaderboard-button.png", 2, 1, this, std::bind(&Game::onLeaderboards, Application), true);

  this->texts.tap->setPosition(Application->getCenter().x, 230);

  this->buttons.like->setPosition(Application->getCenter().x - 250, 100);
  this->buttons.noad->setPosition(Application->getCenter().x - 85, 100);
  this->buttons.share->setPosition(Application->getCenter().x + 85, 100);
  this->buttons.leaderboards->setPosition(Application->getCenter().x + 250, 100);
}

Finish::~Finish()
{
}

/**
 *
 *
 *
 */
void Finish::onShow()
{
  Popup::onShow();

  Events::onScreenChanged("Finish");
}

void Finish::onHide(Callback callback)
{
  Popup::onHide(callback);
}

/**
 *
 *
 *
 */
void Finish::onTouch(cocos2d::Touch* touch, cocos2d::Event* e)
{
  this->hide([=] () {
    Application->changeState(Game::MENU);
  });
}

/**
 *
 *
 *
 */
void Finish::show()
{
  Popup::show();
}

void Finish::hide(Callback callback)
{
  Popup::hide(callback);
}
