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
}

Environment::~Environment()
{
}

/**
 *
 *
 *
 */
void Environment::create()
{
  this->plane = new Entity3D(this, true);
  this->plane->setRotation3D(Vec3(0, 45, 0));
  this->plane->setPosition3D(Vec3(0, 0, 0));

  this->water = new Entity3D("water.obj", this->plane, true);
  this->water->setRotation3D(Vec3(0, 0, 0));
  this->water->setPosition3D(Vec3(0, 0, 0));
  this->water->setColor(Color3B(128, 218, 189));
  this->water->setOpacity(220);

  this->dusts = new Pool(new Dust, this);

  this->spikes = new Pool(new Spike, this->plane);
  this->diamonds = new Pool(new Diamond, this->plane);
  this->crystals = new Pool(new Crystal, this->plane);
  this->energies = new Pool(new Energy, this->plane);
  this->stars = new Pool(new Star, this->plane);
  this->hearts = new Pool(new Heart, this->plane);

  this->plates = new Pool(new Plate, this->plane);
  this->particles = new Pool(new Particle, this->plane);
  this->fishes = new Pool(new Fish, this->plane);
  this->ripples = new Pool(new Ripple, this->plane);
  this->ships = new Pool(new Ship, this->plane);

  this->character = new Character(this);
  this->whale = new Whale(this);

  this->generator = new Generator(this);

  this->onGame();
}

/**
 *
 *
 *
 */
Node* Environment::createRipple(float x, float z, float scale)
{
  auto ripple = this->ripples->_create();

  ripple->setPositionX(x);
  ripple->setPositionY(0);
  ripple->setPositionZ(z);

  ripple->setScaleX(scale);
  ripple->setScaleZ(scale);

  return ripple;
}

Node* Environment::createParticle(float x, float y, float z)
{
  auto particle = this->particles->_create();

  particle->setPositionX(x + random(-1.0, 1.0));
  particle->setPositionY(y - 0.45);
  particle->setPositionZ(z + random(-1.0, 1.0));

  particle->setColor(Color3B(128, 218, 189));

  return particle;
}

/**
 *
 *
 *
 */
Vec3 Environment::position()
{
  auto x = this->character->getPositionX() + random(-10.0, 10.0);
  auto y = 0;
  auto z = this->character->getPositionZ() + random(-10.0, 10.0);

  return Vec3(x, y, z);
}

/**
 *
 *
 *
 */
void Environment::onTurnLeft()
{
  this->character->onTurnLeft();
}

void Environment::onTurnRight()
{
  this->character->onTurnRight();
}

/**
 *
 *
 *
 */
void Environment::onMenu()
{
}

void Environment::onGame()
{
  this->generator->release();
  this->generator = new Generator(this);

  this->plates->clear();
  this->ripples->clear();

  this->runAction(
    Repeat::create(
      Sequence::create(
        CallFunc::create([=] () {
          this->generator->spawn();
        }),
        DelayTime::create(0.0),
        nullptr
      ), 20
    )
  );

  this->character->_create();

  this->water->setRotation3D(Vec3(0, 0, 0));
  this->water->setPosition3D(Vec3(0, 0, 0));
}

void Environment::onLose()
{
  this->character->_destroy(true);
}

/**
 *
 *
 *
 */
void Environment::updateDusts(float time)
{
  if(this->dusts->count < DUSTS_COUNT)
  {
    this->dusts->_create();
  }
}

/**
 *
 *
 *
 */
void Environment::updateFishes(float time)
{
  if(this->fishes->count < MAX_FISH_COUNT)
  {
    this->createFishTimeElapsed += time;

    if(this->createFishTimeElapsed >= this->createFishTime)
    {
      this->createFishTime = random<float>(MIN_FISH_TIME, MAX_FISH_TIME);
      this->createFishTimeElapsed = 0;

      this->fishes->_create();
    }
  }
}

void Environment::updateShips(float time)
{
  if(this->ships->count < MAX_SHIP_COUNT)
  {
    if(probably(1))
    {
      //this->ships->_create();
    }
  }
}

/**
 *
 *
 *
 */
void Environment::updateMenu(float time)
{
}

void Environment::updateGame(float time)
{
}

void Environment::updateLose(float time)
{
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
    case Game::STATE_MENU:
    this->updateMenu(time);
    break;
    case Game::STATE_GAME:
    this->updateGame(time);
    break;
    case Game::STATE_LOSE:
    this->updateLose(time);
    break;
  }

  this->updateDusts(time);
  this->updateFishes(time);
  this->updateShips(time);
}
