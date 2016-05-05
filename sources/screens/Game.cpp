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

  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/ui.plist");

  this->cameras.d = Camera::createOrthographic(this->getWidth() / SCALE_FACTOR, this->getHeight() / SCALE_FACTOR, NEAR, FAR);
  this->cameras.s = Camera::create();
  this->cameras.e = Camera::create();

  this->cameras.d->setCameraFlag(1);
  this->cameras.s->setCameraFlag(4);
  this->cameras.e->setCameraFlag(8);

  this->cameras.d->setDepth(1);
  this->cameras.s->setDepth(2);
  this->cameras.e->setDepth(4);

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

  this->addChild(this->cameras.d);
  this->addChild(this->cameras.s);
  this->addChild(this->cameras.e);

  this->environment = new Environment(this);
  this->environment->create();

  this->counter = new Counter(this);

  this->s = new BackgroundColor(this, Color4B(255, 255, 255, 0));
  this->s->setCameraMask(8);

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

void Game::onFinish()
{
  this->counter->onFinish();
  this->environment->onFinish();

  Finish::getInstance()->show();
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

  this->counter->save();

  /**
   *
   *
   *
   */
  this->parameters.elapsed.ad++;
  this->parameters.elapsed.present++;
  this->parameters.elapsed.video++;this->changeState(PRESENT);return;

  if(Heyzap::available(Config::AD_TYPE_VIDEO) && this->parameters.elapsed.video >= this->parameters.video)
  {
    this->changeState(WATCH);
  }
  else if(Application->parameters.showPresent)
  {
    this->changeState(PRESENT);
  }
  else if(Application->counter->values.coins >= 100)
  {
    this->changeState(OPEN);
  }
  else
  {
    this->changeState(FINISH);
  }

  if(this->parameters.elapsed.ad >= this->parameters.ad)
  {
    this->parameters.elapsed.ad = 0;

    Heyzap::show(Config::AD_TYPE_INTERSTITIAL);
  }
}

void Game::onStore()
{
  this->counter->onStore();
  this->environment->onStore();

  Store::getInstance()->show();
}

void Game::onMissions()
{
  this->counter->onMissions();
  this->environment->onMissions();

  Missions::getInstance()->show();
}

void Game::onPresent()
{
  this->counter->onPresent();
  this->environment->onPresent();

  Application->parameters.showPresent = false;

  Present::getInstance()->show();
}

void Game::onOpen()
{
  this->counter->onOpen();
  this->environment->onOpen();

  Open::getInstance()->show();
}

void Game::onWatch()
{
  this->counter->onWatch();
  this->environment->onWatch();

  Watch::getInstance()->show();
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
      case FINISH:
      this->onFinish();
      break;
      case LOSE:
      this->onLose();
      break;
      case STORE:
      this->onStore();
      break;
      case MISSIONS:
      this->onMissions();
      break;
      case PRESENT:
      this->onPresent();
      break;
      case OPEN:
      this->onOpen();
      break;
      case WATCH:
      this->onWatch();
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

void Game::updateFinish(float time)
{
}

void Game::updateLose(float time)
{
}

void Game::updateStore(float time)
{
}

void Game::updateMissions(float time)
{
}

void Game::updatePresent(float time)
{
}

void Game::updateOpen(float time)
{
}

void Game::updateWatch(float time)
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
    case FINISH:
    this->updateFinish(time);
    break;
    case LOSE:
    this->updateLose(time);
    break;
    case STORE:
    this->updateStore(time);
    break;
    case MISSIONS:
    this->updateMissions(time);
    break;
    case PRESENT:
    this->updatePresent(time);
    break;
    case OPEN:
    this->updateOpen(time);
    break;
    case WATCH:
    this->updateWatch(time);
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

/**
 *
 *
 *
 */
void Game::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
  this->drawCommand.init(100);
  this->drawCommand.func = CC_CALLBACK_0(Game::onDraw, this, renderer, transform, flags);

  renderer->addCommand(&this->drawCommand);
}

void Game::onDraw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
 /*GLuint FramebufferName = 0;
 glGenFramebuffers(1, &FramebufferName);
 glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

 GLuint depthTexture;
 glGenTextures(1, &depthTexture);
 glBindTexture(GL_TEXTURE_2D, depthTexture);
 glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

 glFramebufferTextureEXT(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

 glDrawBuffer(GL_NONE); // No color buffer is drawn to.

 if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
 {
  log("A");
 }
 else
 {
  log("B");
 }*/
}
