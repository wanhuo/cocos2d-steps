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
Sample::Sample(const char* file)
{
  this->texture = new Entity(file, this, true);
  this->texture->getTexture()->setTexParameters({GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT});
  this->texture->getTexture()->setAliasTexParameters();
}

Sample::~Sample()
{
}

/**
 *
 *
 *
 */
void Sample::onEnter()
{
  Screen::onEnter();

  /**
   *
   *
   *
   */
  this->texturePosition = 0;
}

void Sample::onExit()
{
  Screen::onExit();
}

/**
 *
 *
 *
 */
void Sample::onBack()
{
  this->hide();
}

/**
 *
 *
 *
 */
void Sample::show()
{
  Director::getInstance()->pushScene(TransitionFade::create(0.2, this, Color3B::WHITE));
}

void Sample::hide()
{
  Director::getInstance()->popScene(TransitionFade::create(0.2, Director::getInstance()->getPreviousScene(), Color3B::WHITE));
}

/**
 *
 *
 *
 */
void Sample::update(float time)
{
  Screen::update(time);

  /**
   *
   *
   *
   */
  this->texturePosition -= 0.015;

  /**
   *
   *
   *
   */
  this->texture->setTextureRect(Rect(this->texturePosition, this->texturePosition, this->getWidth(), this->getHeight()));
}
