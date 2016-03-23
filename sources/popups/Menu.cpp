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
Menu* Menu::instance;

/**
 *
 *
 *
 */
Menu* Menu::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Menu::Menu()
: Popup()
{
  instance = this;

  this->texts.tap = new Text("menu-tap", this, true);

  this->buttons.rate = new Button("rate-button.png", 1, 2, this, std::bind(&Game::onRate, Application), true);
  this->buttons.leaderboards = new Button("leaderboard-button.png", 1, 2, this, std::bind(&Game::onLeaderboards, Application), true);
  this->buttons.sound = new Button("sound-button.png", 2, 2, this, std::bind(&Menu::onSound, this), true);
  this->buttons.store = new Button("store-button.png", 1, 2, this, std::bind([=] () {
    this->hide([=] () {
      Store::getInstance()->show();
    });
  }), true);

  this->texts.tap->setPosition(Application->getCenter().x, 300);

  this->buttons.store->setPosition(Application->getCenter().x - 200, 200);
  this->buttons.rate->setPosition(Application->getCenter().x - 100, 200);
  this->buttons.sound->setPosition(Application->getCenter().x + 100, 200);
  this->buttons.leaderboards->setPosition(Application->getCenter().x + 200, 200);
}

Menu::~Menu()
{
}

/**
 *
 *
 *
 */
void Menu::onShow()
{
  Popup::onShow();

  this->updateSoundState();

  Events::onScreenChanged("Menu");
}

void Menu::onHide(Callback callback)
{
  Popup::onHide(callback);
}

/**
 *
 *
 *
 */
void Menu::onSound()
{
  Events::onSound();

  /**
   *
   *
   *
   */
  this->updateSoundState();
}

/**
 *
 *
 *
 */
void Menu::show()
{
  Popup::show();

  /**
   *
   *
   *
   */
}

void Menu::hide(Callback callback)
{
}

/**
 *
 *
 *
 */
void Menu::updateSoundState()
{
  if(!Music->enabled || !Sound->enabled)
  {
    Music->changeState(false);
    Sound->changeState(false);

    this->buttons.sound->setCurrentFrameIndex(0);
  }
  else
  {
    Music->changeState(true);
    Sound->changeState(true);

    this->buttons.sound->setCurrentFrameIndex(2);
  }
}
