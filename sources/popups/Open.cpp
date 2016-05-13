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
Open* Open::instance = nullptr;

/**
 *
 *
 *
 */
Open* Open::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Open::Open()
: Finish()
{
  if(!instance) instance = this;

  this->background = new BackgroundColor(this, Color4B(0.0, 0.0, 0.0, 200.0));
  this->background->setLocalZOrder(-1);

  this->element = new Unlock(this);

  this->text = new Text("price", this);
  this->diamond = new CameraEntity3D("diamond.obj", Application, false,
  {
    Camera::createOrthographic(Application->getFrustumWidth(), Application->getFrustumHeight(), 1, 100),
    Vec3(0, 0, 2),
    Vec3(0, 0, 0),
    Application,
    3
  },
  {
    {DirectionLight::create(Vec3(1.0, -1.0, -1.0), Color3B(200, 200, 200)), Application},
    {AmbientLight::create(Color3B(120, 120, 120)), Application}
  });
  this->diamond->setTexture(Application->environment->getTextureState1());
  this->diamond->setPosition3D(Vec3(Application->getFrustumWidth() / 2 + 0.7, 4.3, 0));
  this->diamond->setRotation3D(Vec3(0, 0, 0));
  this->diamond->setColor(Color3B(0.0, 243.0, 120.0));
  this->diamond->setScale(0.7);
  this->diamond->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0, 100, 0))
    )
  );

  this->text->setPosition(Application->getWidth() / 2 - 20, 300);
}

Open::~Open()
{
}

/**
 *
 *
 *
 */
void Open::onShow()
{
  Popup::onShow();

  /**
   *
   *
   *
   */
  this->element->_create();

  /**
   *
   *
   *
   */
  this->text->_create()->setCameraMask(4);
  this->diamond->_create();
}

void Open::onHide(Callback callback)
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
void Open::onTouchStart(cocos2d::Touch* touch, cocos2d::Event* e)
{
  if(!this->element->touch->binded)
  {
    Finish::onTouchStart(touch, e);
  }
}

/**
 *
 *
 *
 */
void Open::show()
{
  Finish::show();
}

void Open::hide(Callback callback)
{
  Finish::hide(callback);
}
