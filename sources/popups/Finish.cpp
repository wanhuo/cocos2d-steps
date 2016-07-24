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
Finish* Finish::instance = nullptr;

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
  if(!instance) instance = this;

  this->buttons.rate = new Button("rate-button.png", 2, 1, this, std::bind(&Game::onRate, Application));
  this->buttons.leaderboards = new Button("leaderboard-button.png", 2, 1, this, std::bind(&Game::onLeaderboards, Application));
  this->buttons.restart = new Button("restart-button.png", 2, 1, this, std::bind([=] () {
    Application->capture->bind(false);
    this->hide([=] () {
      Application->changeState(Game::MENU);
    });
  }));
  this->buttons.store = new Button("store-button.png", 2, 1, this, std::bind([=] () {
    if(!Application->environment->store.controller->nextElement().type)
    {
      Application->changeState(Game::STORE);
    }
    else
    {
    }
  }));
  this->buttons.present = new Present(this);
  this->buttons.video = new Video(this);

  this->missions = new EnvironmentMissionsFinish(this);
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

  /**
   *
   *
   *
   */
  if(Application->counter->values.b.special)
  {
    Application->counter->values.b.special = false;
  }
  else if(Application->counter->values.b.daily)
  {
    Application->counter->values.b.daily = false;
  }
  else if(Application->counter->values.b.mission)
  {
    Application->counter->values.b.mission = false;

    if(!MissionsFactory::getInstance()->getCurrentMission())
    {
      this->missions->plane->removeItem(1);
      Finish::getInstance()->missions->plane->removeItem(1);
    }
  }

  if(Application->counter->values.b.mission || Application->counter->values.b.special || Application->counter->values.b.daily)
  {
    /*Present::getInstance()->missions->_destroy();
    Present::getInstance()->element->runAction(
      Sequence::create(
        ScaleTo::create(0.5, 0),
        CallFunc::create([=] () {
        Present::getInstance()->element->_destroy();
        Present::getInstance()->onShow();
        }),
        nullptr
      )
    );*/
  }
  else
  {
    /**
     *
     *
     *
     */
    this->buttons.rate->_create()->setCameraMask(4);
    this->buttons.restart->_create()->setCameraMask(4);
    this->buttons.leaderboards->_create()->setCameraMask(4);
    this->buttons.present->_create()->setCameraMask(4);
    this->buttons.video->_create()->setCameraMask(4);
    this->buttons.store->_create()->setCameraMask(4);

    this->buttons.rate->bind(false);
    this->buttons.restart->bind(false);
    this->buttons.leaderboards->bind(false);
    this->buttons.store->bind(false);

    this->buttons.rate->setPosition(Application->getCenter().x - 200, 0);
    this->buttons.restart->setPosition(Application->getCenter().x, 0);
    this->buttons.leaderboards->setPosition(Application->getCenter().x + 200, 0);
    this->buttons.present->setPosition(Application->getCenter().x - 260, Application->getCenter().y - 10);
    this->buttons.video->setPosition(Application->getCenter().x - 260, Application->getCenter().y - 10 + 164);
    this->buttons.store->setPosition(Application->getCenter().x + 260, Application->getCenter().y - 10);

    this->buttons.leaderboards->runAction(
      Sequence::create(
        DelayTime::create(0.1),
        EaseSineOut::create(
          MoveBy::create(0.2, Vec2(0, 200))
        ),
        DelayTime::create(0.3),
        CallFunc::create([=] () {
        this->buttons.leaderboards->bind(true);
        }),
        nullptr
      )
    );
    this->buttons.restart->runAction(
      Sequence::create(
        DelayTime::create(0.0),
        EaseSineOut::create(
          MoveBy::create(0.2, Vec2(0, 200))
        ),
        DelayTime::create(0.3),
        CallFunc::create([=] () {
        this->buttons.restart->bind(true);
        }),
        nullptr
      )
    );
    this->buttons.rate->runAction(
      Sequence::create(
        DelayTime::create(0.1),
        EaseSineOut::create(
          MoveBy::create(0.2, Vec2(0, 200))
        ),
        DelayTime::create(0.3),
        CallFunc::create([=] () {
        this->buttons.rate->bind(true);
        }),
        nullptr
      )
    );

    this->buttons.store->stopAllActions();
    this->buttons.store->runAction(
      Sequence::create(
        DelayTime::create(0.0),
        CallFunc::create([=] () {
        this->buttons.store->bind(true);
        }),
        nullptr
      )
    );

    this->buttons.present->runAction(
      Sequence::create(
        DelayTime::create(0.0),
        nullptr
      )
    );

    this->buttons.video->runAction(
      Sequence::create(
        DelayTime::create(0.0),
        nullptr
      )
    );

    this->runAction(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        Vote::update();
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

  {
    if(Application->environment->store.controller->nextElement().type)
    {
      this->buttons.store->setCurrentFrameIndex(0);
      this->buttons.store->runAction(
        RepeatForever::create(
          Sequence::create(
            ScaleTo::create(0.25, 1.05),
            ScaleTo::create(0.25, 0.95),
            nullptr
          )
        )
      );
    }
  }
}

void Finish::onHide(Callback callback)
{
  Popup::onHide(callback);

  /**
   *
   *
   *
   */
  this->buttons.rate->_destroy();
  this->buttons.restart->_destroy();
  this->buttons.leaderboards->_destroy();
  this->buttons.present->_destroy();
  this->buttons.video->_destroy();
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
  this->runAction(
    Sequence::create(
      FadeOut::create(0.2),
      CallFunc::create([=] () {
        Popup::hide(callback);
      }),
      nullptr
    )
  );

  this->missions->runAction(
    Sequence::create(
      FadeOut::create(0.2),
      CallFunc::create([=] () {
      this->missions->_destroy();
      }),
      nullptr
    )
  );
}
