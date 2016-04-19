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
Counter::Counter(Node* parent)
: Background(parent)
{
  this->holder = new BackgroundColor(this, Color4B::RED);
  this->holder->setContentSize(Size(0, 0));
  this->holder->setCascadeOpacityEnabled(true);

  this->starBackground = new Entity("counter-star.png", this->holder);
  this->starBackground->setPosition(0, -80);
  this->starBackground->setPosition(0, 25);
  this->starBackground->setCascadeOpacityEnabled(true);
  this->starBackground->setOpacity(0);
  this->starBackground->setScale(1.5);

  this->bonusBackground = new Entity("counter-bonus.png", this->holder);
  this->bonusBackground->setPosition(0, -80);
  this->bonusBackground->setCascadeOpacityEnabled(true);
  this->bonusBackground->setOpacity(0);
  this->bonusBackground->setScale(1.5);

  this->starAction = ProgressTimer::create(new Entity("counter-star.png"));
  this->starAction->setType(ProgressTimer::Type::RADIAL);
  this->starBackground->addChild(this->starAction);
  this->starAction->getSprite()->setOpacity(150);
  this->starAction->getSprite()->setScale(0.8);
  this->starAction->setPosition(this->starBackground->getWidth() / 2, this->starBackground->getHeight() / 2);

  this->icon = new Entity("coins-icon.png", this, true);

  this->texts.name = new Text("name", this, true);
  this->texts.score = new Text("counter-score", this->holder, true);
  this->texts.coins = new Text("counter-coins", this, true);
  this->texts.best1 = new Text("counter-best", this, true);
  this->texts.best2 = new Text("counter-best-new", this, true);
  this->texts.bonus = new Text("counter-bonus", this->bonusBackground, true);

  this->texts.best1->setPosition(Application->getCenter().x, Application->getHeight() - 300);

  this->holder->setOpacity(0);
  this->texts.best1->setOpacity(0);
  this->texts.best2->setOpacity(0);

  this->setCameraMask(4);

  this->holder->setPosition(Application->getCenter().x, Application->getHeight() - 200);
  this->texts.name->setPosition(Application->getCenter().x, Application->getHeight() - 300);
  this->texts.score->setPosition(0, 0);
  this->texts.bonus->setPosition(this->bonusBackground->getWidth() / 2, this->bonusBackground->getHeight() / 2 - 12);

  this->reset();

  this->icon->setGlobalZOrder(100);
  this->texts.coins->setGlobalZOrder(100);
}

Counter::~Counter()
{
}

/**
 *
 *
 *
 */
void Counter::onMenu()
{
  this->update();

  this->holder->runAction(
    FadeTo::create(0.2, 0)
  );

  this->texts.name->runAction(
    FadeTo::create(0.2, 255)
  );

  this->texts.best1->runAction(
    FadeTo::create(0.2, 0)
  );

  this->texts.best2->runAction(
    FadeTo::create(0.2, 0)
  );
}

void Counter::onGame()
{
  if(!Application->environment->generator->bonus)
  {
    this->bonusBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 255),
        Sequence::create(
          CallFunc::create([=] () {
            this->bonusBackground->setVisible(true);
          }),
          MoveTo::create(0.2, Vec2(0, -80)),
          nullptr
        ),
        nullptr
      )
    );
  }

  this->update();

  this->texts.name->runAction(
    FadeTo::create(0.2, 0)
  );
}

void Counter::onFinish()
{
  if(Application->environment->generator->bonus)
  {
  }
  else
  {
    this->bonusBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 0),
        Sequence::create(
          MoveTo::create(0.2, Vec2(0, 0)),
          CallFunc::create([=] () {
            this->bonusBackground->setVisible(false);
          }),
          nullptr
        ),
        nullptr
      )
    );
  }
}

void Counter::onLose()
{
  this->bonusBackground->runAction(
    Spawn::create(
      FadeTo::create(0.2, 0),
      Sequence::create(
        MoveTo::create(0.2, Vec2(0, 0)),
        CallFunc::create([=] () {
          this->bonusBackground->setVisible(false);
        }),
        nullptr
      ),
      nullptr
    )
  );

  this->update();

  this->holder->runAction(
    FadeTo::create(0.2, 255)
  );

  if(true)
  {
    this->onBest();
  }
  else
  {
    this->onRegular();
  }
}

void Counter::onStore()
{
  this->texts.name->runAction(
    FadeTo::create(0.2, 0)
  );
}

/**
 *
 *
 *
 */
void Counter::onStarStart()
{
  if(this->bonusBackground->isVisible())
  {
    this->bonusBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 0),
        Sequence::create(
          MoveTo::create(0.2, Vec2(0, 0)),
          CallFunc::create([=] () {
            this->bonusBackground->setVisible(false);

            this->starBackground->runAction(
              Spawn::create(
                FadeTo::create(0.2, 150),
                Sequence::create(
                  CallFunc::create([=] () {
                    this->starBackground->setVisible(true);
                  }),
                  MoveTo::create(0.2, Vec2(0, -80)),
                  nullptr
                ),
                nullptr
              )
            );
          }),
          nullptr
        ),
        nullptr
      )
    );
  }
  else
  {
  }
}

void Counter::onStarFinish()
{
  if(Application->environment->generator->bonus)
  {
    this->starBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 0),
        Sequence::create(
          CallFunc::create([=] () {
            this->starBackground->setVisible(false);
          }),
          MoveTo::create(0.2, Vec2(0, 0)),
          nullptr
        ),
        nullptr
      )
    );
  }
  else
  {
    this->starBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 0),
        Sequence::create(
          MoveTo::create(0.2, Vec2(0, 0)),
          CallFunc::create([=] () {
            this->starBackground->setVisible(false);

            if(Application->state == Game::GAME)
            {
              this->bonusBackground->runAction(
                Spawn::create(
                  FadeTo::create(0.2, 255),
                  Sequence::create(
                    CallFunc::create([=] () {
                      this->bonusBackground->setVisible(true);
                    }),
                    MoveTo::create(0.2, Vec2(0, -80)),
                    nullptr
                  ),
                  nullptr
                )
              );
            }
          }),
          nullptr
        ),
        nullptr
      )
    );
  }
}

void Counter::onStarUpdate()
{
  this->starAction->setPercentage(Application->environment->starTimeElapsed / Application->environment->starTime * 100);
}

/**
 *
 *
 *
 */
void Counter::onCount()
{
  if(this->values.current < 1) {
    this->holder->runAction(
      FadeTo::create(0.2, 255)
    );
  }

  this->values.start += (Application->environment->star ? 2 : 1);
  this->values.current += (Application->environment->star ? 2 : 1);

  if(this->values.current > this->values.best)
  {
    this->values.best = this->values.current;
  }

  this->update();

  Application->environment->water->setColor(Application->environment->color->get());
}

void Counter::onCoins()
{
  this->values.coins++;

  this->update();
}

/**
 *
 *
 *
 */
void Counter::onBest()
{
  this->texts.best1->runAction(
    FadeTo::create(0.2, 255)
  );
}

void Counter::onRegular()
{
}

/**
 *
 *
 *
 */
void Counter::reset()
{Storage::set("application.score.best", 0);
  this->values.start = 0;
  this->values.current = 0;
  this->values.bonus = Generator::PLATES_FINISH;
  this->values.best = Storage::get("application.score.best");
}

void Counter::save()
{
  Storage::set("application.score.best", this->values.best);
}

/**
 *
 *
 *
 */
void Counter::update()
{
  this->texts.score->data(this->values.current);
  this->texts.bonus->data(this->values.bonus - (Application->environment->character->plates.current ? Application->environment->character->plates.current->getIndex() : 0));
  this->texts.best1->data(this->values.best);
  this->texts.coins->data(this->values.coins);
  this->texts.coins->setPosition(Application->getWidth() - this->texts.coins->getWidth() - 60, Application->getHeight() - 60);

  this->icon->setPosition(this->texts.coins->getPositionX() + this->texts.coins->getWidth() / 2 + 30, Application->getHeight() - 50);

  if(this->values.current > this->values.best)
  {
    this->onBest();
  }
}
