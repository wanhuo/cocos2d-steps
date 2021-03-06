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
Present* Present::instance = nullptr;

/**
 *
 *
 *
 */
Present* Present::getInstance()
{
  return Present::instance;
}

/**
 *
 *
 *
 */
Present::Present()
: Finish()
{
  if(!Present::instance) Present::instance = this;

  this->background = new BackgroundColor(this, Color4B(0.0, 0.0, 0.0, 200.0));
  this->background->setLocalZOrder(-1);

  this->element = new Gift(this);
}

Present::~Present()
{
}

/**
 *
 *
 *
 */
void Present::onShow()
{
  Popup::onShow();

  /**
   *
   *
   *
   */
  switch(Application->state)
  {
    default:
    break;
    case Game::PRESENT:
    break;
    case Game::MISSION_COMPLETE:
    this->missions->_create();
    this->missions->setPosition3D(Vec3(Application->getFrustumWidth() / 2, Application->getFrustumHeight() / 2 - 3.5 - 12.0, 0));
    this->missions->runAction(
      EaseSineOut::create(
        MoveBy::create(0.5, Vec2(0, 10))
      )
    );

    this->missions->plane->setTouchEnabled(false);

    if(Application->counter->values.b.mission)
    {
      this->missions->general->text->stopAllActions();
      this->missions->general->text->setText("missions-finish-complete");
      this->missions->general->text->data(MissionsFactory::getInstance()->getPreviousMission()->id);
    }
    break;
  }

  /**
   *
   *
   *
   */
  this->element->_create();
}

void Present::onHide(Callback callback)
{
  Finish::onHide(callback);

  /**
   *
   *
   *
   */
  this->element->_destroy();
}

/**
 *
 *
 *
 */
void Present::show()
{
  Popup::show();
}

void Present::hide(Callback callback)
{
  this->missions->_destroy();
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
