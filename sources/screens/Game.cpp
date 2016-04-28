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
Game* Game::instance;

/**
 *
 *
 *
 */
Game* Game::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Game::Game()
{
  instance = this;

  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerAcceleration::create([=] (Acceleration* acceleration, Event* e) {
    this->environment->onAccelerate(acceleration, e);
  }), this);

  Device::setAccelerometerEnabled(true);

  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui.plist");

  this->cameras.d = Camera::createOrthographic(this->getWidth() / SCALE_FACTOR, this->getHeight() / SCALE_FACTOR, NEAR, FAR);
  this->cameras.c = Camera::createOrthographic(this->getWidth() / SCALE_FACTOR, this->getHeight() / SCALE_FACTOR, NEAR, FAR);
  this->cameras.s = Camera::create();
  //this->cameras.e = Camera::createOrthographic(this->getWidth() / SCALE_FACTOR, this->getHeight() / SCALE_FACTOR, NEAR, FAR);

  this->cameras.d->setCameraFlag(CameraFlag::DEFAULT);
  this->cameras.c->setCameraFlag(CameraFlag::USER1);
  this->cameras.s->setCameraFlag(CameraFlag::USER2);
  //this->cameras.e->setCameraFlag(CameraFlag::USER3);

  this->cameras.d->setDepth(1);
  this->cameras.s->setDepth(2);
  this->cameras.c->setDepth(3);
  //this->cameras.e->setDepth(4);

  float x = -(this->getWidth() / SCALE_FACTOR) / 2 - 39.35;
  float y = -(this->getHeight() / SCALE_FACTOR) / 2 + 55;
  float z = 45;

  float rx = -40;
  float ry = -40;
  float rz = 0;

  this->startCameraX = x;
  this->startCameraY = y;
  this->startCameraZ = z;

  this->startCameraRotationX = rx;
  this->startCameraRotationY = ry;
  this->startCameraRotationZ = rz;

  this->cameras.d->setPosition3D(Vec3(x, y, z));
  this->cameras.d->setRotation3D(Vec3(rx, ry, rz));

  this->cameras.c->setPosition3D(Vec3(-(this->getWidth() / SCALE_FACTOR) + 0.5, -(this->getHeight() / SCALE_FACTOR) + 0.7, NEAR + 1));
  this->cameras.c->setRotation3D(Vec3(0, 0, 0));

  this->addChild(this->cameras.d);
  this->addChild(this->cameras.s);
  this->addChild(this->cameras.c);
  //this->addChild(this->cameras.e);

  this->counter = new Counter(this);
  this->environment = new Environment(this);

  this->environment->create();

  this->s = new BackgroundColor(this, Color4B(255, 255, 255, 0));
  this->s->setGlobalZOrder(200);
  this->s->setCameraMask(4);

  Music->play("music-1");
}

Game::~Game()
{
}

/**
 *
 *
 *
 */
void Game::onTouchStart(cocos2d::Touch* touch, Event* event)
{
  switch(this->state)
  {
    case MENU:
    Menu::getInstance()->hide();

    this->changeState(GAME);
    break;
    case GAME:
    this->environment->onTurn();
    break;
  }
}

void Game::onTouchFinish(cocos2d::Touch* touch, Event* event)
{
  switch(this->state)
  {
    default:
    this->environment->onTurn(false);
    break;
  }
}

/**
 *
 *
 *
 */
void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, Event *event)
{
  switch(this->state)
  {
    case LOSE:
    Finish::getInstance()->hide();

    this->changeState(MENU);
    break;
    case MENU:
    Menu::getInstance()->hide();

    this->changeState(GAME);
    break;
    case GAME:
    this->environment->onTurn();
    break;
  }
}

void Game::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, Event *event)
{
  this->environment->onTurn(false);
}

/**
 *
 *
 *
 */
void Game::onEnter()
{
  Screen::onEnter();

  /**
   *
   *
   *
   */
  Internal::onStart();

  /**
   *
   *
   *
   */
  Events::onScreenChanged("Game");

  this->changeState(MENU);
}

void Game::onExit()
{
  Screen::onExit();
}

/**
 *
 *
 *
 */
void Game::onBack()
{
}

/**
 *
 *
 *
 */
void Game::onLeaderboards()
{
  Events::onLeaderboards();
}

void Game::onAchievements()
{
  Events::onAchievements();
}

void Game::onRate()
{
  Events::onRate();
}

void Game::onLike()
{
  Events::onLike();
}

void Game::onShare()
{
  Events::onShare();
}

void Game::onTwitter()
{
  Events::onTwitter();
}

void Game::onFacebook()
{
  Events::onFacebook();
}

void Game::onMail()
{
  Events::onMail();
}

void Game::onRestorePurchases()
{
  Events::onRestorePurchases();
}

/**
 *
 *
 *
 */
void Game::onMenu()
{
  this->setPosition3D(Vec3(0, 0, 0));

  this->environment->onMenu();
  this->counter->onMenu();

  Menu::getInstance()->show();

  this->counter->reset();
}

void Game::onGame()
{
  this->stopAllActions();

  Music->volume(1.0);
  Music->play("music-2", true);

  this->environment->onGame();
  this->counter->onGame();
}

void Game::onLose()
{
  this->runAction(
    Repeat::create(
      Sequence::create(
        CallFunc::create([=] () {
          Music->volume(Music->volume() - 0.05);
        }),
        DelayTime::create(0.1),
        nullptr
      ), 20
    )
  );

  this->environment->onLose();
  this->counter->onLose();

  Finish::getInstance()->show();

  this->counter->save();
}

void Game::onStore()
{
  this->counter->onStore();

  Store::getInstance()->show();
}

void Game::onFinish()
{
  this->counter->onFinish();
  this->environment->onFinish();
}

/**
 *
 *
 *
 */
void Game::onNoad()
{
}

/**
 *
 *
 *
 */
void Game::changeState(State state)
{
  if(this->state != state)
  {
    this->state = state;

    switch(this->state)
    {
      case MENU:
      this->onMenu();
      break;
      case GAME:
      this->onGame();
      break;
      case LOSE:
      this->onLose();
      break;
      case STORE:
      this->onStore();
      break;
      case FINISH:
      this->onFinish();
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Game::updateMenu(float time)
{
}

void Game::updateGame(float time)
{
}

void Game::updateLose(float time)
{
}

void Game::updateStore(float time)
{
}

void Game::updateFinish(float time)
{
}

/**
 *
 *
 *
 */
void Game::updateStates(float time)
{
  switch(this->state)
  {
    case MENU:
    this->updateMenu(time);
    break;
    case GAME:
    this->updateGame(time);
    break;
    case LOSE:
    this->updateLose(time);
    break;
    case STORE:
    this->updateStore(time);
    break;
    case FINISH:
    this->updateFinish(time);
    break;
  }

  this->environment->update(time);
}

/**
 *
 *
 *
 */
void Game::update(float time)
{
  Screen::update(time);

  /**
   *
   *
   *
   */
  this->updateStates(time);
}
