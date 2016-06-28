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

  Modal::show();

  /*this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListenerAcceleration::create([=] (Acceleration* acceleration, Event* e) {
    this->environment->onAccelerate(acceleration, e);
  }), this);

  Device::setAccelerometerEnabled(true);*/

  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/ui.plist");

  this->cameras.d = Camera::createOrthographic(this->getWidth() / SCALE_FACTOR, this->getHeight() / SCALE_FACTOR, NEAR, FAR);
  this->cameras.c = Camera::createOrthographic(this->getWidth() / SCALE_FACTOR, this->getHeight() / SCALE_FACTOR, NEAR, FAR);
  this->cameras.s = Camera::create();
  this->cameras.e = Camera::create();
  this->cameras.f = Camera::create();
  this->cameras.g = Camera::create();

  this->cameras.d->setCameraFlag(1);
  this->cameras.f->setCameraFlag(2);
  this->cameras.s->setCameraFlag(4);
  this->cameras.e->setCameraFlag(8);
  this->cameras.g->setCameraFlag(9);
  this->cameras.c->setCameraFlag(16);

  this->cameras.d->setDepth(1);
  this->cameras.f->setDepth(1);
  this->cameras.s->setDepth(2);
  this->cameras.e->setDepth(4);
  this->cameras.c->setDepth(8);
  this->cameras.g->setDepth(9);

  this->generateFrameBuffer();

  float x = -this->getFrustumWidth() / 2 - (this->getWidth() > this->getHeight() ? 41.5 : 39.5);
  float y = -this->getFrustumHeight() / 2 + (this->getWidth() > this->getHeight() ? 58.0 : 55.0);
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

  this->cameras.c->setPosition3D(Vec3(0, 0, 2));
  this->cameras.c->setRotation3D(Vec3(0, 0, 0));

  this->addChild(this->cameras.d);
  this->addChild(this->cameras.s);
  this->addChild(this->cameras.e);
  this->addChild(this->cameras.c);
  this->addChild(this->cameras.f);
  this->addChild(this->cameras.g);

  this->environment = new Environment(this);
  this->environment->create();

  this->giphy = new Giphy(this);

  this->counter = new Counter(this);
  this->capture = new Capture(this);

  this->rampage = new Rampage(this);

  this->s = new BackgroundColor(this, Color4B(255, 255, 255, 0));
  this->d = new BackgroundColor(this, Color4B(0, 0, 0, 0));

  this->i = new Entity("insane-background.png", this);
  this->i->setPosition(this->getCenter().x, this->getCenter().y);

  this->s->setCameraMask(8);
  this->d->setCameraMask(8);
  this->i->setCameraMask(8);
}

Game::~Game()
{
}

/**
 *
 *
 *
 */
void Game::generateFrameBuffer()
{  if(Screenshot::support())
  {
  auto size = Size(Director::getInstance()->getWinSizeInPixels().width, Director::getInstance()->getWinSizeInPixels().height);

  this->frameBuffer = FrameBuffer::create(1, size.width / FRAME_BUFFER_FACTOR, size.height / FRAME_BUFFER_FACTOR);

  auto rt = RenderTarget::create(size.width / FRAME_BUFFER_FACTOR, size.height / FRAME_BUFFER_FACTOR);
  auto rtDS = RenderTargetDepthStencil::create(size.width / FRAME_BUFFER_FACTOR, size.height / FRAME_BUFFER_FACTOR);
  this->frameBuffer->attachRenderTarget(rt);
  this->frameBuffer->attachDepthStencilTarget(rtDS);

  this->generate = Sprite::createWithTexture(this->getFrameBuffer()->getRenderTarget()->getTexture());
  this->generate->setScaleX(1 * FRAME_BUFFER_FACTOR);
  this->generate->setScaleY(-1 * FRAME_BUFFER_FACTOR);
  this->generate->setPosition(size.width / 2, size.height / 2);
  this->generate->setCameraMask(2);
  this->generate->setGlobalZOrder(1);
  this->addChild(this->generate);


    for(int i = 0; i < CAPTURE_FPS * CAPTURE_TIME; i++)
    {
      auto render = RenderTexture::create(size.width / FRAME_BUFFER_FACTOR / CAPTURE_SCALE, size.width / FRAME_BUFFER_FACTOR / CAPTURE_SCALE, Texture2D::PixelFormat::RGB565);
      render->retain();

      this->capturing.textures.push_back(render);
    }

  this->captures = new Captures();
  this->captures->initWithTexture(this->generate->getTexture());
  this->captures->setScaleX(1.0 * Game::FRAME_BUFFER_FACTOR / CAPTURE_SCALE);
  this->captures->setScaleY(-1.0 * Game::FRAME_BUFFER_FACTOR / CAPTURE_SCALE);
  this->captures->setPosition(this->getWidth() / CAPTURE_SCALE / 2, this->getHeight() / CAPTURE_SCALE / 2 - CAPTURE_POSITION / CAPTURE_SCALE);

  this->cameras.d->setFrameBufferObject(this->getFrameBuffer());
  }
}

/**
 *
 *
 *
 */
FrameBuffer* Game::getFrameBuffer()
{
  return this->frameBuffer;
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
    default:
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
    default:
    break;
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

  this->runAction(
    Sequence::create(
      DelayTime::create(2.0),
      CallFunc::create([=] () {
      Music->play("music-1");
      }),
      nullptr
    )
  );
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

void Game::onFacebookLike()
{
  Events::onFacebookLike();
}

void Game::onTwitterLike()
{
  Events::onTwitterLike();
}

void Game::onShare(bool action, bool complete, const std::function<void(int)>& callback, const std::function<void(int, int)>& update)
{
  Events::onShare(action, complete, callback, update);
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
  this->capture->_destroy();

  this->cameras.d->setScale(0.6);
  this->cameras.d->setPosition3D(Vec3(this->startCameraX, this->startCameraY - 20, this->startCameraZ));
  this->cameras.d->setRotation3D(Vec3(this->startCameraRotationX + 15, this->startCameraRotationY - (this->getWidth() > this->getHeight() ? 4.0 : 1.8), this->startCameraRotationZ));
}

void Game::onGame()
{
  this->stopAllActions();

  Music->speed(1.0);
  Music->volume(1.0);
  Music->play("music-2", true);

  this->environment->onGame();
  this->counter->onGame();

    Application->cameras.d->runAction(
    Spawn::create(
      ScaleTo::create(0.5, 1.0),
      MoveTo::create(0.5, Vec3(this->startCameraX, this->startCameraY, this->startCameraZ)),
      RotateTo::create(0.5, Vec3(this->startCameraRotationX, this->startCameraRotationY, this->startCameraRotationZ)),
      nullptr
    )
  );

  /**
   *
   * @Missions
   * Update missions with games.
   *
   */
  if(MissionsFactory::getInstance()->isListenen())
  {
    Application->counter->missionUpdateProgress.games++;

    Events::updateMissions();
  }

  /**
   *
   * @Capture
   *
   */
  this->capturing.index = 0;
  this->capturing.frame = 1;
  this->capturing.frames = 0;

  this->capturing.time = 1.0 / CAPTURE_FPS;
  this->capturing.timeElapsed = 0;
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
  this->parameters.elapsed.video++;

  if(this->counter->values.b.mission || this->counter->values.b.special || this->counter->values.b.daily)
  {
    this->changeState(MISSION_COMPLETE);
  }
  else if(Application->parameters.showPresent)
  {
    this->changeState(PRESENT);
  }
  else if(this->environment->store.controller->nextElement().type)
  {
    this->changeState(OPEN);
  }
  else if(Heyzap::available(Config::AD_TYPE_VIDEO) && this->parameters.elapsed.video >= this->parameters.video)
  {
    this->parameters.elapsed.video = -1;
    this->changeState(WATCH);
  }
  else
  {
    this->changeState(FINISH);
  }

  if(Heyzap::available(Config::AD_TYPE_VIDEO) && this->parameters.elapsed.video >= this->parameters.video)
  {
    this->parameters.elapsed.ad--;
    this->parameters.elapsed.video--;
  }

  if(this->parameters.elapsed.ad >= this->parameters.ad)
  {
    this->parameters.elapsed.ad = -1;

    Heyzap::show(Config::AD_TYPE_INTERSTITIAL);
  }

  Analytics::sendEvent("Application", "onLose", ("Lose: " + patch::to_string(this->counter->values.current) + " points with " + patch::to_string(this->counter->values.best) + " best points").c_str());
}

void Game::onStore()
{
  this->counter->onStore();
  this->environment->onStore();

  Analytics::sendEvent("Application", "onStore", "Application onStore event");
}

void Game::onMissions()
{
  this->counter->onMissions();
  this->environment->onMissions();

  Analytics::sendEvent("Application", "onMissions", "Application onMissions event");
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

void Game::onMissionComplete()
{
  this->environment->onMissionComplete();

  Present::getInstance()->show();
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
      default:
      break;
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
      case MISSION_COMPLETE:
      this->onMissionComplete();
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

void Game::updateMissionComplete(float time)
{
}

/**
 *
 *
 *
 */
void Game::updateCapture(float time)
{
  if(Screenshot::support())
  {
    switch(this->state)
    {
      default:
      break;
      case GAME:
      case LOSE:
      if(!this->capture->Node::state->create)
      {
        this->capturing.timeElapsed += time;

        if(this->capturing.timeElapsed >= this->capturing.time || CAPTURE_FPS == 60)
        {
          this->capturing.timeElapsed = 0;

          auto lastRender = this->capturing.textures.at(this->capturing.textures.size() - 1);
          this->capturing.textures.erase(this->capturing.textures.begin() + this->capturing.textures.size() - 1);
          this->capturing.textures.insert(this->capturing.textures.begin(), lastRender);

          this->captures->setTexture(this->generate->getTexture());

          auto render = this->capturing.textures.at(0);

          render->beginWithClear(1, 1, 1, 1);
          this->captures->Sprite::visit();
          render->end();

          this->capturing.frames = min<int>(CAPTURE_FPS * CAPTURE_TIME - 1, this->capturing.frames + 1);
        }
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
void Game::updateStates(float time)
{
  this->updateCapture(time);

  switch(this->state)
  {
    default:
    break;
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
    case MISSION_COMPLETE:
    this->updateMissionComplete(time);
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
