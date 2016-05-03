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
Environment::Environment(Node* parent)
: Background(parent)
{
  this->updateData();
}

Environment::~Environment()
{
}

/**
 *
 *
 *
 */
void Environment::onAccelerate(Acceleration* acceleration, Event* e)
{
  this->accelerometerX = acceleration->x * ACCELEROMETER_FACTOR;
  this->accelerometerY = acceleration->y * ACCELEROMETER_FACTOR;
  this->accelerometerZ = acceleration->z * ACCELEROMETER_FACTOR;
}

/**
 *
 *
 *
 */
void Environment::create()
{
  this->plane = new Entity3D(this, true);
  this->plane->setRotation3D(Vec3(0, 0, 0));
  this->plane->setPosition3D(Vec3(0, 0, 0));

  this->ground = new Ground(this);

  this->starts = new Pool(new Start, this->plane);
  this->downs = new Pool(new Down, this->plane);
  this->cubs = new Pool(new Cub, this->plane);
  this->diamonds = new Pool(new Diamond, this->plane);
  this->crystals = new Pool(new Crystal, this->plane);
  this->energies = new Pool(new Energy, this->plane);
  this->stars = new Pool(new Star, this->plane);
  this->hearts = new Pool(new Heart, this->plane);
  this->colors = new Pool(new Color, this->plane);

  this->particles = new Pool(new Particle, this->plane);

  this->plates.normal = new Pool(new Plate, this->plane);
  this->plates.finish = new Pool(new TypeFinish, this->plane);
  this->plates.best = new Pool(new TypeBest, this->plane);
  this->plates.bonus = new Pool(new TypeBonus, this->plane);
  this->plates.spikes = new Pool(new TypeSpikes, this->plane);
  this->plates.trampolines = new Pool(new TypeTrampoline, this->plane);
  this->plates.saws = new Pool(new TypeSaw, this->plane);
  this->plates.gates = new Pool(new TypeGate, this->plane);
  this->plates.copters = new Pool(new TypeCopter, this->plane);
  this->plates.traps = new Pool(new TypeTrap, this->plane);
  this->plates.moveups = new Pool(new TypeMoveUp, this->plane);
  this->plates.moved1 = new Pool(new TypeMoved1, this->plane);
  this->plates.moved2 = new Pool(new TypeMoved2, this->plane);
  this->plates.moved3 = new Pool(new TypeMoved3, this->plane);
  this->plates.moved4 = new Pool(new TypeMoved4, this->plane);

  this->character = new Character;
  this->generator = new Generator;

  this->characterActionHolder = new Background(this);
  this->characterActionHolder->setContentSize(Size(Application->getWidth(), 0));
  this->characterActionHolder->setPosition(Vec2(0, 870));
  this->characterActionHolder->setCascadeOpacityEnabled(true);
  this->characterActionHolder->setCameraMask(4);

  this->characterActionBackground = new BackgroundColor(this->characterActionHolder, Color4B(255, 255, 255, 150));
  this->characterActionBackground->setContentSize(Size(Application->getWidth() - 100, 40));
  this->characterActionBackground->setAnchorPoint(Vec2(0, 0));
  this->characterActionBackground->setPosition(Vec2(50, 10));
  this->characterActionBackground->setCameraMask(4);

  this->characterAction = new BackgroundColor(this->characterActionHolder, Color4B(255, 255, 255, 150));
  this->characterAction->setContentSize(Size(Application->getWidth() - 110, 30));
  this->characterAction->setAnchorPoint(Vec2(0, 0));
  this->characterAction->setPosition(Vec2(55, 15));
  this->characterAction->setCameraMask(4);

  this->characterActionHolder->setScale(0);
  this->characterActionHolder->setOpacity(0);

  this->onGame();

  this->light.natural = AmbientLight::create(Color3B(150, 150, 150));
  this->light.environment = DirectionLight::create(Vec3(0.5, -1.0, 0.0), Color3B(120, 120, 120));
  this->light.character = SpotLight::create(Vec3(0, 0, 0), Vec3(0, 0, 0), Color3B(255, 255, 255), 320.0f, 0.0f, 20.0f);

  this->plane->addChild(this->light.environment);
  this->plane->addChild(this->light.natural);
  this->plane->addChild(this->light.character);
}

/**
 *
 *
 *
 */
Entity3D* Environment::createParticle(float x, float y, float z)
{
  auto particle = static_cast<Entity3D*>(this->particles->_create());

  particle->setScaleX(random(0.5, 1.5));
  particle->setScaleY(0.0);
  particle->setScaleZ(random(0.5, 1.5));

  particle->setPositionX(x);
  particle->setPositionY(y);
  particle->setPositionZ(z);

  particle->runAction(
    Spawn::create(
      Sequence::create(
        EaseSineOut::create(
          ScaleTo::create(random(0.2, 0.5), particle->getScaleX(), 1.0, particle->getScaleZ())
        ),
        EaseSineOut::create(
          ScaleTo::create(random(0.2, 0.5), 0.0)
        ),
        CallFunc::create([=] () {
          particle->_destroy(true);
        }),
        nullptr
      ),
      Sequence::create(
        EaseSineOut::create(
          MoveBy::create(random(0.2, 0.5), Vec3(random(0.5, 1.2) * (probably(50) ? 1 : -1), 0.0, random(0.5, 1.2) * (probably(50) ? 1 : -1)))
        ),
        nullptr
      ),
      nullptr
    )
  );

  return particle;
}

/**
 *
 *
 *
 */
string Environment::getTextureState1()
{
  return "textures/" + to_string(this->pack) + "/textures-state-1.png";
}

string Environment::getTextureState2()
{
  return "textures/" + to_string(this->pack) + "/textures-state-2.png";
}

/**
 *
 *
 *
 */
void Environment::updateData()
{
  this->level = max(1, Storage::get("application.current.level"));
  this->pack = max(1, Storage::get("store.texture.selected"));

  Director::getInstance()->getTextureCache()->addImageAsync(this->getTextureState1(), nullptr);
  Director::getInstance()->getTextureCache()->addImageAsync(this->getTextureState2(), nullptr);
}

void Environment::updateLevel()
{
  Storage::set("application.current.level", ++this->level);
}

/**
 *
 *
 *
 */
void Environment::onTurn(bool action)
{
  this->setPosition3D(Vec3(0, 0, 0));

  this->character->onTurn(action);
}

/**
 *
 *
 *
 */
void Environment::onMenu()
{
  this->updateData();

  this->finishStar();

  this->platesTime = 1.0;
  this->platesTimeElapsed = 0;

  this->character->reset();

  this->ground->reset();
  this->generator->reset();

  this->setPosition3D(Vec3(0, 0, 0));

  this->plane->setPosition3D(Vec3(0, 0, 0));
}

void Environment::onGame()
{
  this->onTurn();
}

void Environment::onLose()
{
  this->finishStar();
}

void Environment::onCopter()
{
}

void Environment::onFinish()
{
  this->generator->reset();

  this->platesTime = 1.0;
  this->platesTimeElapsed = 0;
}

/**
 *
 *
 *
 */
void Environment::startStar()
{
  this->star = true;

  this->starTime = STAR_TIME;
  this->starTimeElapsed = 0;

  Application->counter->onStarStart();
}

void Environment::finishStar()
{
  this->star = false;

  Application->counter->onStarFinish();
}

/**
 *
 *
 *
 */
void Environment::updateLight(float time)
{
  auto x = this->character->getPositionX();
  auto y = 20.0f;
  auto z = this->character->getPositionZ();

  this->light.character->setPosition3D(Vec3(x, y, z));
}

/**
 *
 *
 *
 */
void Environment::updateMenu(float time)
{
}

void Environment::updateLose(float time)
{
}

void Environment::updateGame(float time)
{
  if(this->character->state != Character::CRASH)
  {
    this->platesTimeElapsed += time;

    if(this->platesTimeElapsed >= this->platesTime)
    {
      this->platesTime = max(0.3, this->platesTime - 0.01);
      this->platesTimeElapsed = 0;

      this->generator->destroy();
    }
  }
}

/**
 *
 *
 *
 */
void Environment::updateStar(float time)
{
  if(this->star)
  {
    Application->counter->onStarUpdate();

    this->starTimeElapsed += time;

    if(this->starTimeElapsed >= this->starTime)
    {
      this->finishStar();
    }
  }
}

/**
 *
 *
 *
 */
void Environment::update(float time)
{
  switch(Application->state)
  {
    case Game::MENU:
    this->updateMenu(time);
    break;
    case Game::GAME:
    this->updateGame(time);
    break;
    case Game::LOSE:
    this->updateLose(time);
    break;
  }

  this->updateLight(time);
  this->updateStar(time);
}
