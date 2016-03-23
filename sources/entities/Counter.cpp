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
  this->texts.score = new Text("counter", this, true);
  this->texts.coins = new Text("counter", this, true);

  this->texts.score->setPosition(Application->getCenter().x, Application->getHeight() - 200);
  this->texts.coins->setPosition(Application->getWidth() - 100, Application->getHeight() - 40);

  this->setCameraMask(4);
  this->reset();
}

Counter::~Counter()
{
}

/**
 *
 *
 *
 */
void Counter::onCount()
{
  this->value++;
}

/**
 *
 *
 *
 */
void Counter::onBest()
{
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
  this->value = 0;
}

void Counter::save()
{
}
