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

  this->buttons.like = new Button("like-button.png", 2, 1, this, std::bind(&Game::onFacebookLike, Application));
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
      Application->changeState(Game::OPEN);
    }
  }));
  this->buttons.gift = new Button("gift-button.png", 4, 1, this, std::bind([=] () {
    if(this->buttonsTime1 - Times::now() < 0)
    {
      this->buttonsTime1 = Times::now() + Times::minute() * 45;
      Storage::set("timers.gift.time", s(this->buttonsTime1));

      this->buttons.gift->stopAllActions();
      this->buttons.gift->setCurrentFrameIndex(2);

      this->texts.gift->setVisible(true);

      Application->changeState(Game::PRESENT);
    }
  }));
  this->buttons.video = new Button("video-button.png", 4, 1, this, std::bind([=] () {
    if(this->buttonsTime2 - Times::now() < 0)
    {
      this->buttonsTime2 = Times::now() + Times::minute() * 5;
      Storage::set("timers.video.time", s(this->buttonsTime2));

      this->buttons.video->stopAllActions();
      this->buttons.video->setCurrentFrameIndex(2);

      this->texts.video->setVisible(true);

      Application->changeState(Game::WATCH);
    }
  }));

  this->texts.gift = new Text("time", this->buttons.gift, true);
  this->texts.video = new Text("time", this->buttons.video, true);

  this->texts.gift->setPosition(this->buttons.gift->getWidth() / 2, 30);
  this->texts.video->setPosition(this->buttons.video->getWidth() / 2, 30);

  this->missions = new EnvironmentMissionsFinish(this);

  this->setScheduleUpdate(true);
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
    this->buttons.like->_create()->setCameraMask(4);
    this->buttons.rate->_create()->setCameraMask(4);
    this->buttons.restart->_create()->setCameraMask(4);
    this->buttons.leaderboards->_create()->setCameraMask(4);
    this->buttons.gift->_create()->setCameraMask(4);
    this->buttons.video->_create()->setCameraMask(4);
    this->buttons.store->_create()->setCameraMask(4);

    this->buttons.like->bind(false);
    this->buttons.rate->bind(false);
    this->buttons.restart->bind(false);
    this->buttons.leaderboards->bind(false);
    this->buttons.gift->bind(false);
    this->buttons.video->bind(false);
    this->buttons.store->bind(false);

    this->buttons.like->setPosition(80, Application->getHeight() + 120);
    this->buttons.rate->setPosition(Application->getCenter().x - 200, 0);
    this->buttons.restart->setPosition(Application->getCenter().x, 0);
    this->buttons.leaderboards->setPosition(Application->getCenter().x + 200, 0);
    this->buttons.gift->setPosition(Application->getCenter().x + 260, Application->getCenter().y - 10);
    this->buttons.video->setPosition(Application->getCenter().x + 260, Application->getCenter().y - 10 + 164);
    this->buttons.store->setPosition(Application->getCenter().x - 260, Application->getCenter().y - 10);

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

    this->buttons.like->runAction(
      Sequence::create(
        DelayTime::create(0.3),
        EaseSineOut::create(
          MoveBy::create(0.2, Vec2(0, -200))
        ),
        DelayTime::create(0.3),
        CallFunc::create([=] () {
        this->buttons.like->bind(true);
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

    this->buttons.gift->stopAllActions();
    this->buttons.gift->runAction(
      Sequence::create(
        DelayTime::create(0.0),
        CallFunc::create([=] () {
        this->buttons.gift->bind(true);
        }),
        nullptr
      )
    );

    this->buttons.video->stopAllActions();
    this->buttons.video->runAction(
      Sequence::create(
        DelayTime::create(0.0),
        CallFunc::create([=] () {
        this->buttons.video->bind(true);
        }),
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
    string time = Storage::get("timers.gift.time", true);
    this->buttonsTime1 = time.length() > 0 ? std::stoll(time.c_str()) : 0;

    if(this->buttonsTime1 - Times::now() < 0)
    {
      this->buttons.gift->runAction(
        RepeatForever::create(
          Sequence::create(
            ScaleTo::create(0.25, 1.05),
            ScaleTo::create(0.25, 0.95),
            nullptr
          )
        )
      );
      this->buttons.gift->setCurrentFrameIndex(0);
      this->texts.gift->setVisible(false);
    }
    else
    {
      this->buttons.gift->setCurrentFrameIndex(2);
      this->texts.gift->setVisible(true);
    }
  }

  {
    string time = Storage::get("timers.video.time", true);
    this->buttonsTime2 = time.length() > 0 ? std::stoll(time.c_str()) : 0;

    if(this->buttonsTime2 - Times::now() < 0)
    {
      this->buttons.video->runAction(
        RepeatForever::create(
          Sequence::create(
            ScaleTo::create(0.25, 1.05),
            ScaleTo::create(0.25, 0.95),
            nullptr
          )
        )
      );
      this->buttons.video->setCurrentFrameIndex(0);
      this->texts.video->setVisible(false);
    }
    else
    {
      this->buttons.video->setCurrentFrameIndex(2);
      this->texts.video->setVisible(true);
    }
  }

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
  this->buttons.like->_destroy();
  this->buttons.rate->_destroy();
  this->buttons.restart->_destroy();
  this->buttons.leaderboards->_destroy();
  this->buttons.gift->_destroy();
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

/**
 *
 *
 *
 */
void Finish::update(float time)
{
  Popup::update(time);

  /**
   *
   *
   *
   */
  {
    long long t = this->buttonsTime1 - Times::now();

    if(t >= 0)
    {
      string h = "" + patch::to_string(Times::hours(t));
      string m = "" + patch::to_string(Times::minutes(t));
      string s = "" + patch::to_string(Times::seconds(t));

      if(Times::hours(t) < 10) h = "0" + h;
      if(Times::minutes(t) < 10) m = "0" + m;
      if(Times::seconds(t) < 10) s = "0" + s;

      this->texts.gift->data(h, m, s);

      if(t <= 0)
      {
        this->buttons.gift->runAction(
          RepeatForever::create(
            Sequence::create(
              ScaleTo::create(0.25, 1.05),
              ScaleTo::create(0.25, 0.95),
              nullptr
            )
          )
        );
        this->buttons.gift->setCurrentFrameIndex(0);
        this->texts.gift->setVisible(false);
      }
    }
  }

  /**
   *
   *
   *
   */
  {
    long long t = this->buttonsTime2 - Times::now();

    if(t >= 0)
    {
      string h = "" + patch::to_string(Times::hours(t));
      string m = "" + patch::to_string(Times::minutes(t));
      string s = "" + patch::to_string(Times::seconds(t));

      if(Times::hours(t) < 10) h = "0" + h;
      if(Times::minutes(t) < 10) m = "0" + m;
      if(Times::seconds(t) < 10) s = "0" + s;

      this->texts.video->data(h, m, s);

      if(t <= 0)
      {
        this->buttons.video->runAction(
          RepeatForever::create(
            Sequence::create(
              ScaleTo::create(0.25, 1.05),
              ScaleTo::create(0.25, 0.95),
              nullptr
            )
          )
        );
        this->buttons.video->setCurrentFrameIndex(0);
        this->texts.video->setVisible(false);
      }
    }
  }
}
