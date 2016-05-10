/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * @copyright (c) 2016 by Igor Mats
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

#include "Store.h"

/**
 *
 *
 *
 */
Handler::Handler()
: Entity("handler.png", true)
{
  this->text = new Text("handler", this, true);
  this->text->setPosition(this->getWidth() / 2 + 2, this->getHeight() / 2 - 2);

  this->setCascadeOpacityEnabled(true);

  this->setScheduleUpdate(true);
}

Handler::~Handler()
{
}

/**
 *
 *
 *
 */
void Handler::onEnter()
{
  Entity::onEnter();

  /**
   *
   *
   *
   */
  this->setOpacity(0.0);
  this->setPosition(this->getParent()->getContentSize().width - 20, this->getParent()->getContentSize().height - 20 + 20);
}

void Handler::onExit()
{
  Entity::onExit();
}

/**
 *
 *
 *
 */
void Handler::show(int count)
{
  this->count = count;

  if(this->getOpacity() < 255)
  {
    if(count > 0)
    {
      this->setScale(1.0);

      this->runAction(
        Spawn::create(
          EaseSineInOut::create(
            FadeIn::create(0.5)
          ),
          EaseSineInOut::create(
            MoveBy::create(0.5, Vec2(0, -20.0))
          ),
          nullptr
        )
      );

      this->text->data(count);
    }
  }
  else
  {
    if(count > 0)
    {
      auto d = random(0.0, 1.0);

      this->runAction(
        DelayTime::create(d + 0.5)
      );

      this->text->runAction(
        Spawn::create(
          Sequence::create(
            DelayTime::create(d),
            ScaleTo::create(0.2, 0.0),
            ScaleTo::create(0.2, 1.0),
            nullptr
          ),
          Sequence::create(
            DelayTime::create(d),
            RotateTo::create(0.2, 720 * (probably(50) ? 1 : -1)),
            CallFunc::create([=] () {
            this->text->data(this->count);
            }),
            RotateTo::create(0.2, 720 * (probably(50) ? 1 : -1)),
            nullptr
          ),
          nullptr
        )
      );
    }
    else
    {
      this->runAction(
        EaseSineInOut::create(
          ScaleTo::create(0.2, 0.0)
        )
      );
    }
  }
}

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
MissionsHandler::MissionsHandler()
: Handler()
{
}

MissionsHandler::~MissionsHandler()
{
}

/**
 *
 *
 *
 */
void MissionsHandler::onEnter()
{
  Handler::onEnter();

  /**
   *
   *
   *
   */
  this->show(getValue());
}

void MissionsHandler::onExit()
{
  Handler::onExit();
}

/**
 *
 *
 *
 */
void MissionsHandler::update(float time)
{
  if(!this->getNumberOfRunningActions())
  {
    if(this->count != getValue())
    {
      this->show(getValue());
    }
  }
}

/**
 *
 *
 *
 */
int MissionsHandler::getValue()
{
  return MissionsFactory::getInstance()->getClaimedMissionsCount();
}

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
StoreHandler::StoreHandler()
: Handler()
{
}

StoreHandler::~StoreHandler()
{
}

/**
 *
 *
 *
 */
void StoreHandler::onEnter()
{
  Handler::onEnter();

  /**
   *
   *
   *
   */
  this->show(getValue());
}

void StoreHandler::onExit()
{
  Handler::onExit();
}

/**
 *
 *
 *
 */
void StoreHandler::update(float time)
{
  if(!this->getNumberOfRunningActions())
  {
    if(this->count != getValue())
    {
      this->show(getValue());
    }
  }
}

/**
 *
 *
 *
 */
int StoreHandler::getValue()
{
  return StoreCharactersHandler::getValue() + StoreEnvironmentsHandler::getValue();
}

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
StoreCharactersHandler::StoreCharactersHandler()
: Handler()
{
}

StoreCharactersHandler::~StoreCharactersHandler()
{
}

/**
 *
 *
 *
 */
void StoreCharactersHandler::onEnter()
{
  Handler::onEnter();

  /**
   *
   *
   *
   */
  this->show(getValue());
}

void StoreCharactersHandler::onExit()
{
  Handler::onExit();
}

/**
 *
 *
 *
 */
void StoreCharactersHandler::update(float time)
{
  if(!this->getNumberOfRunningActions())
  {
    if(this->count != getValue())
    {
      this->show(getValue());
    }
  }
}

/**
 *
 *
 *
 */
int StoreCharactersHandler::getValue()
{
  return 0;
}

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
StoreEnvironmentsHandler::StoreEnvironmentsHandler()
: Handler()
{
}

StoreEnvironmentsHandler::~StoreEnvironmentsHandler()
{
}

/**
 *
 *
 *
 */
void StoreEnvironmentsHandler::onEnter()
{
  Handler::onEnter();

  /**
   *
   *
   *
   */
  this->show(getValue());
}

void StoreEnvironmentsHandler::onExit()
{
  Handler::onExit();
}

/**
 *
 *
 *
 */
void StoreEnvironmentsHandler::update(float time)
{
  if(!this->getNumberOfRunningActions())
  {
    if(this->count != getValue())
    {
      this->show(getValue());
    }
  }
}

/**
 *
 *
 *
 */
int StoreEnvironmentsHandler::getValue()
{
  return 11;
}
