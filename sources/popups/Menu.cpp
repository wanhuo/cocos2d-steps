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

  this->buttons.leaderboards = new Button("leaderboard-button.png", 2, 1, this, std::bind(&Game::onLeaderboards, Application), true);
  this->buttons.sound = new Button("sound-button.png", 2, 2, this, std::bind(&Menu::onSound, this), true);
  this->buttons.store = new Button("store-button.png", 2, 1, this, std::bind([=] () {
    this->hide([=] () {
      Application->changeState(Game::STORE);
    });
  }), true);
  this->buttons.missions = new Button("missions-button.png", 2, 1, this, std::bind([=] () {
    this->hide([=] () {
      Application->changeState(Game::MISSIONS);
    });
  }), true);

  this->texts.tap->setPosition(Application->getCenter().x, 230);

  this->setCascadeOpacityEnabled(true);

  this->bind(false);
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

  this->buttons.store->setPosition(Application->getCenter().x - 250, -100);
  this->buttons.missions->setPosition(Application->getCenter().x - 85, -100);
  this->buttons.sound->setPosition(Application->getCenter().x + 85, -100);
  this->buttons.leaderboards->setPosition(Application->getCenter().x + 250, -100);
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

  this->setOpacity(255);

  this->buttons.store->runAction(
    Sequence::create(
      DelayTime::create(0),
      EaseSineOut::create(
        MoveBy::create(0.2, Vec2(0, 200))
      ),
      nullptr
    )
  );
  this->buttons.missions->runAction(
    Sequence::create(
      DelayTime::create(0.1),
      EaseSineOut::create(
        MoveBy::create(0.2, Vec2(0, 200))
      ),
      nullptr
    )
  );
  this->buttons.sound->runAction(
    Sequence::create(
      DelayTime::create(0.2),
      EaseSineOut::create(
        MoveBy::create(0.2, Vec2(0, 200))
      ),
      nullptr
    )
  );
  this->buttons.leaderboards->runAction(
    Sequence::create(
      DelayTime::create(0.3),
      EaseSineOut::create(
        MoveBy::create(0.2, Vec2(0, 200))
      ),
      nullptr
    )
  );

  this->texts.tap->setOpacity(0);
  this->texts.tap->runAction(
    Sequence::create(
      DelayTime::create(0.5),
      FadeIn::create(0.5),
      CallFunc::create([=] () {
        this->texts.tap->runAction(
          RepeatForever::create(
            Sequence::create(
              FadeOut::create(0.5),
              FadeIn::create(0.5),
              DelayTime::create(0.2),
              nullptr
            )
          )
        );
      }),
      nullptr
    )
  );
}

void Menu::hide(Callback callback)
{
  Popup::hide(callback);
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

    this->buttons.sound->setCurrentFrameIndex(2);
  }
  else
  {
    Music->changeState(true);
    Sound->changeState(true);

    this->buttons.sound->setCurrentFrameIndex(0);
  }
}
