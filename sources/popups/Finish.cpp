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

  this->buttons.like = new Button("like-button.png", 2, 1, this, std::bind(&Game::onRate, Application), true);
  this->buttons.noad = new Button("noad-button.png", 2, 1, this, std::bind(&Game::onRate, Application), true);
  this->buttons.share = new Button("share-button.png", 2, 1, this, std::bind([=] () {
    this->hide([=] () {
      Store::getInstance()->show();
    });
  }), true);
  this->buttons.leaderboards = new Button("leaderboard-button.png", 2, 1, this, std::bind(&Game::onLeaderboards, Application), true);
  this->buttons.video = new Button("video-button.png", 1, 2, this, std::bind(&Game::onLeaderboards, Application), true);

  this->texts.tap = new Text("finish-tap", this, true);
  this->texts.video = new Text("video", this->buttons.video, true);

  this->buttons.video->setPosition(Application->getCenter().x, 350);

  this->texts.tap->setPosition(Application->getCenter().x, 230);
  this->texts.video->setPosition(this->buttons.video->getWidth() / 2 + 70, this->buttons.video->getHeight() / 2 - 15);
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

  this->buttons.like->setPosition(Application->getCenter().x - 250, -100);
  this->buttons.noad->setPosition(Application->getCenter().x - 85, -100);
  this->buttons.share->setPosition(Application->getCenter().x + 85, -100);
  this->buttons.leaderboards->setPosition(Application->getCenter().x + 250, -100);
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
void Finish::onTouchStart(cocos2d::Touch* touch, cocos2d::Event* e)
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

  this->setOpacity(255);

  this->buttons.leaderboards->runAction(
    Sequence::create(
      DelayTime::create(0),
      EaseSineOut::create(
        MoveBy::create(0.2, Vec2(0, 200))
      ),
      nullptr
    )
  );
  this->buttons.share->runAction(
    Sequence::create(
      DelayTime::create(0.1),
      EaseSineOut::create(
        MoveBy::create(0.2, Vec2(0, 200))
      ),
      nullptr
    )
  );
  this->buttons.noad->runAction(
    Sequence::create(
      DelayTime::create(0.2),
      EaseSineOut::create(
        MoveBy::create(0.2, Vec2(0, 200))
      ),
      nullptr
    )
  );
  this->buttons.like->runAction(
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

void Finish::hide(Callback callback)
{
  this->texts.tap->stopAllActions();

  this->runAction(
    Sequence::create(
      FadeOut::create(0.2),
      CallFunc::create([=] () {
        Popup::hide(callback);
      }),
      nullptr
    )
  );
}
