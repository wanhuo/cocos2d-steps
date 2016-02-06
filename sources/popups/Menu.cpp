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

  this->backgrounds.top = new Entity("menu-background-1.png", this, true);
  this->backgrounds.bottom = new Entity("menu-background-2.png", this, true);

  this->buttons.play = new Button("play-button.png", 2, 2, this->backgrounds.bottom, std::bind([=] () {
    this->hide([=] () {
      Application->changeState(Game::GAME);
    });
  }), true);
  this->buttons.tutorial = new Button("tutorial-button.png", 1, 2, this->backgrounds.bottom, std::bind([=] () {
    this->hide([=] () {
      Application->changeState(Game::GAME);
    });
  }), true);
  this->buttons.like = new Button("like-button.png", 1, 2, this->backgrounds.bottom, std::bind(&Game::onLike, Application), true);
  this->buttons.rate = new Button("rate-button.png", 1, 2, this->backgrounds.bottom, std::bind(&Game::onRate, Application), true);
  this->buttons.share = new Button("share-button.png", 1, 2, this->backgrounds.bottom, std::bind(&Game::onShare, Application), true);
  this->buttons.leaderboards = new Button("leaderboard-button.png", 1, 2, this->backgrounds.bottom, std::bind(&Game::onLeaderboards, Application), true);
  this->buttons.achievements = new Button("achievements-button.png", 1, 2, this->backgrounds.bottom, std::bind(&Game::onAchievements, Application), true);
  this->buttons.sound = new Button("sound-button.png", 2, 2, this->backgrounds.bottom, std::bind(&Menu::onSound, this), true);
  this->buttons.noad = new Button("noad-button.png", 1, 2, this->backgrounds.bottom, std::bind(&Game::onNoad, Application), true);
  this->buttons.store = new Button("store-button.png", 1, 2, this->backgrounds.bottom, std::bind([=] () {
    this->hide([=] () {
      Store::getInstance()->show();
    });
  }), true);
  this->buttons.missions = new Button("missions-button.png", 1, 2, this->backgrounds.bottom, std::bind([=] () {
    this->hide([=] () {
      Missions::getInstance()->show();
    });
  }), true);
  this->buttons.about = new Button("about-button.png", 1, 2, this->backgrounds.bottom, std::bind([=] () {
    this->hide([=] () {
      About::getInstance()->show();
    });
  }), true);

  this->buttons.play->setPosition(this->backgrounds.bottom->getWidth() / 2, this->backgrounds.bottom->getHeight());
  this->buttons.like->setPosition(this->backgrounds.bottom->getWidth() / 2 - 200, this->backgrounds.bottom->getHeight() - 100);
  this->buttons.rate->setPosition(this->backgrounds.bottom->getWidth() / 2 - 290, this->backgrounds.bottom->getHeight() - 100);
  this->buttons.leaderboards->setPosition(this->backgrounds.bottom->getWidth() / 2 + 200, this->backgrounds.bottom->getHeight() - 100);
  this->buttons.achievements->setPosition(this->backgrounds.bottom->getWidth() / 2 + 290, this->backgrounds.bottom->getHeight() - 100);
  this->buttons.share->setPosition(this->backgrounds.bottom->getWidth() / 2 + 50, this->backgrounds.bottom->getHeight() - 200);
  this->buttons.missions->setPosition(this->backgrounds.bottom->getWidth() / 2 + 150, this->backgrounds.bottom->getHeight() - 200);
  this->buttons.store->setPosition(this->backgrounds.bottom->getWidth() / 2 + 250, this->backgrounds.bottom->getHeight() - 200);
  this->buttons.sound->setPosition(this->backgrounds.bottom->getWidth() / 2 - 50, this->backgrounds.bottom->getHeight() - 200);
  this->buttons.tutorial->setPosition(this->backgrounds.bottom->getWidth() / 2 - 150, this->backgrounds.bottom->getHeight() - 200);
  this->buttons.noad->setPosition(this->backgrounds.bottom->getWidth() / 2 - 250, this->backgrounds.bottom->getHeight() - 200);
  this->buttons.about->setPosition(this->backgrounds.bottom->getWidth() / 2, this->backgrounds.bottom->getHeight() - 300);
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

  /**
   *
   *
   *
   */
  this->updateSoundState();

  /**
   *
   *
   *
   */
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
  this->backgrounds.top->setPosition(Application->getCenter().x, Application->getHeight() + this->backgrounds.top->getHeight() / 2);
  this->backgrounds.bottom->setPosition(Application->getCenter().x, 0 - this->backgrounds.bottom->getHeight() / 2);

  this->backgrounds.top->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.4, Vec2(0, -this->backgrounds.top->getHeight()))
      ),
      EaseSineInOut::create(
        MoveBy::create(0.2, Vec2(0, 150))
      ),
      EaseSineInOut::create(
        MoveBy::create(0.3, Vec2(0, -100))
      ),
      nullptr
    )
  );

  this->backgrounds.bottom->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.4, Vec2(0, this->backgrounds.bottom->getHeight()))
      ),
      EaseSineInOut::create(
        MoveBy::create(0.2, Vec2(0, -150))
      ),
      EaseSineInOut::create(
        MoveBy::create(0.3, Vec2(0, 100))
      ),
      nullptr
    )
  );
}

void Menu::hide(Callback callback)
{
  this->backgrounds.top->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.3, Vec2(0, -50))
      ),
      EaseSineInOut::create(
        MoveBy::create(0.4, Vec2(0, this->backgrounds.top->getHeight() * 1.5))
      ),
      nullptr
    )
  );

  this->backgrounds.bottom->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.3, Vec2(0, 50))
      ),
      EaseSineInOut::create(
        MoveBy::create(0.4, Vec2(0, -this->backgrounds.bottom->getHeight() * 1.5))
      ),
      CallFunc::create([=] () {
        this->onHide(callback);
      }),
      nullptr
    )
  );
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
