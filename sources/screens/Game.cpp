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

  /**
   *
   *
   *
   *
   */
  this->cameras.d = Camera::createOrthographic(this->getWidth() / SCALE_FACTOR, this->getHeight() / SCALE_FACTOR, NEAR, FAR);
  this->cameras.s = Camera::create();
  this->cameras.e = Camera::createOrthographic(this->getWidth() / SCALE_FACTOR, this->getHeight() / SCALE_FACTOR, NEAR, FAR);

  this->cameras.d->setCameraFlag(CameraFlag::DEFAULT);
  this->cameras.s->setCameraFlag(CameraFlag::USER1);
  this->cameras.e->setCameraFlag(CameraFlag::USER2);

  this->cameras.d->setDepth(1);
  this->cameras.s->setDepth(0);
  this->cameras.e->setDepth(0);

  float x = -(this->getWidth() / SCALE_FACTOR) / 2;
  float y = -(this->getHeight() / SCALE_FACTOR) / 2 + 40;
  float z = 45;

  float rx = -40;
  float ry = 0;
  float rz = 0;

  this->startCameraX = x;
  this->startCameraY = y;
  this->startCameraZ = z;

  this->cameras.d->setPosition3D(Vec3(x, y, z));
  this->cameras.d->setRotation3D(Vec3(rx, ry, rz));

  this->addChild(this->cameras.d);
  this->addChild(this->cameras.s);
  this->addChild(this->cameras.e);

  this->counter = new Counter;
  this->environment = new Environment(this);

  this->environment->create();

  this->changeState(STATE_MENU);
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
  if(!this->environment->whale->Node::state->create)
  {
    switch(this->state)
    {
      case STATE_MENU:
      this->changeState(STATE_GAME);
      break;
      case STATE_LOSE:
      this->changeState(STATE_GAME);
      break;
      case STATE_GAME:
      if(touch->getLocation().x < this->getWidth() / 2)
      {
        this->environment->onTurnLeft();
      }
      else
      {
        this->environment->onTurnRight();
      }
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Game::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, Event *event)
{
  if(!this->environment->whale->Node::state->create)
  {
    switch(this->state)
    {
      case STATE_GAME:
      switch(key)
      {
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
        this->environment->onTurnLeft();
        break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
        this->environment->onTurnRight();
        break;
      }
      break;
    }
  }
}

void Game::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, Event *event)
{
}

/**
 *
 *
 *
 */
void Game::onEnter()
{
  Screen::onEnter();

  Internal::onStart();

  /**
   *
   *
   *
   */
  this->updateSoundState();
  this->updateState();

  /**
   *
   *
   *
   */
  Events::onScreenChanged("Game");
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
void Game::onPlay()
{
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

void Game::onScores()
{
  Events::onScores();
}

void Game::onAchievements()
{
  Events::onAchievements();
}

void Game::onSound()
{
  Events::onSound();

  /**
   *
   *
   *
   */
  this->updateSoundState();
}

void Game::onStore()
{
}

void Game::onMissions()
{
}

void Game::onTutorial()
{
}

void Game::onCredits()
{
}

void Game::onNoad()
{
  Purchase::purchaseItem("com.ketchapp.exodus.remove.ads", [=] (bool status) {
    if(status)
    {
      this->onNoadAction();
    }
  });
}

void Game::onNoadAction()
{
  if(!this->parameters.ad)
  {
    this->parameters.ad = true;

    Storage::set("state.ad.disabled", true);
  }
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
  //Finish::getInstance()->show();

  this->environment->onMenu();
}

void Game::onGame()
{
  this->environment->onGame();

  this->cameras.d->setPositionX(this->startCameraX);
  this->cameras.d->setPositionY(this->startCameraY);
  this->cameras.d->setPositionZ(this->startCameraZ);

  this->counter->reset();
}

void Game::onLose()
{
  //Finish::getInstance()->show();

  this->environment->onLose();

  this->counter->save();
}

/**
 *
 *
 *
 */
void Game::changeState(int state)
{
  if(this->state != state)
  {
    this->state = state;

    switch(this->state)
    {
      case STATE_MENU:
      this->onMenu();
      break;
      case STATE_GAME:
      this->onGame();
      break;
      case STATE_LOSE:
      this->onLose();
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Game::updateSoundState()
{
}

/**
 *
 *
 *
 */
void Game::updateState()
{
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

/**
 *
 *
 *
 */
void Game::updateStates(float time)
{
  switch(this->state)
  {
    case STATE_MENU:
    this->updateMenu(time);
    break;
    case STATE_GAME:
    this->updateGame(time);
    break;
    case STATE_LOSE:
    this->updateLose(time);
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
