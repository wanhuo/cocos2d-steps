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
  this->icon = new Entity("coins-icon.png", this, true);

  this->texts.name = new Text("name", this, true);
  this->texts.score = new Text("counter-score", this, true);
  this->texts.coins = new Text("counter-coins", this, true);
  this->texts.best1 = new Text("counter-best", this, true);
  this->texts.best2 = new Text("counter-new-best", this, true);

  this->texts.best1->setPosition(Application->getCenter().x, Application->getHeight() - 300);
  this->texts.best2->setPosition(Application->getCenter().x, Application->getHeight() - 300);

  this->texts.score->setOpacity(0);
  this->texts.best1->setOpacity(0);
  this->texts.best2->setOpacity(0);

  this->setCameraMask(4);

  this->reset();
  this->update();

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
  this->texts.name->runAction(
    FadeTo::create(0.2, 255)
  );

  this->texts.score->runAction(
    FadeTo::create(0.2, 0)
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
  this->texts.name->runAction(
    FadeTo::create(0.2, 0)
  );
}

void Counter::onLose()
{
  this->texts.score->runAction(
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
void Counter::onCount()
{
  if(this->values.current < 1) {
    this->texts.score->runAction(
      FadeTo::create(0.2, 255)
    );
  }

  this->values.current++;

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
{
  this->values.current = 0;
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
  this->texts.best1->data(this->values.best);
  //this->texts.best2->data(this->values.best);
  this->texts.coins->data(this->values.coins);

  this->texts.name->setPosition(Application->getCenter().x, Application->getHeight() - 300);
  this->texts.score->setPosition(Application->getCenter().x, Application->getHeight() - 200);
  this->texts.coins->setPosition(Application->getWidth() - this->texts.coins->getWidth() - 60, Application->getHeight() - 60);

  this->icon->setPosition(this->texts.coins->getPositionX() + this->texts.coins->getWidth() / 2 + 30, Application->getHeight() - 50);

  if(this->values.current > this->values.best)
  {
    //this->on???;
  }
}
