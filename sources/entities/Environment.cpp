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
  this->plane->setRotation3D(Vec3(0, 45, 0));
  this->plane->setPosition3D(Vec3(0, 0, 0));

  this->water = new Entity3D("water.obj", this->plane, true);
  this->water->setRotation3D(Vec3(0, 0, 0));
  this->water->setPosition3D(Vec3(0, 0, 0));
  this->water->setColor(Color3B(84, 205, 240));
  this->water->setOpacity(220);

  this->dusts = new Pool(new Dust, this);

  this->spikes = new Pool(new Spike, this->plane);
  this->diamonds = new Pool(new Diamond, this->plane);
  this->crystals = new Pool(new Crystal, this->plane);
  this->energies = new Pool(new Energy, this->plane);
  this->stars = new Pool(new Star, this->plane);
  this->hearts = new Pool(new Heart, this->plane);

  this->plates = new Pool(new Plate, this->plane);
  this->cannons = new Pool(new Cannon, this->plane);
  this->particles = new Pool(new Particle, this->plane);
  this->fishes = new Pool(new Fish, this->plane);
  this->ripples = new Pool(new Ripple, this->plane);
  this->leafs = new Pool(new Leaf, this->plane);

  this->plates_spikes = new Pool(new Entity3D("spike-plate.obj"), this->plane);

  this->character = new Character;

  this->generator = new Generator;

  this->onGame();
}

/**
 *
 *
 *
 */
Entity3D* Environment::createRipple(float x, float z, float scale)
{
  auto ripple = static_cast<Entity3D*>(this->ripples->_create());

  ripple->setPositionX(x);
  ripple->setPositionY(0);
  ripple->setPositionZ(z);

  ripple->setScaleX(scale);
  ripple->setScaleZ(scale);

  return ripple;
}

Entity3D* Environment::createParticle(float x, float y, float z)
{
  auto particle = static_cast<Entity3D*>(this->particles->_create());

  particle->setScale(random(0.5, 1.0));

  particle->setPositionX(x);
  particle->setPositionY(y);
  particle->setPositionZ(z);

  particle->runAction(
    Spawn::create(
      Sequence::create(
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
          MoveBy::create(random(0.2, 0.5), Vec3((random(0.5, 1.5) * (probably(50) ? 1 : -1)), random(0.5, 0.7), (random(0.5, 1.5) * (probably(50) ? 1 : -1))))
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
void Environment::onTurnLeft(bool action)
{
  this->character->onTurnLeft(action);
}

void Environment::onTurnRight(bool action)
{
  this->character->onTurnRight(action);
}

/**
 *
 *
 *
 */
void Environment::onMenu()
{
  this->plates->clear();

  this->ripples->clear();
  this->leafs->clear();
  this->cannons->clear();

  this->generator->clear();

  this->character->_create();

  this->water->setRotation3D(Vec3(0, 0, 0));
  this->water->setPosition3D(Vec3(0, 0, 0));
}

void Environment::onGame()
{
  this->onTurnRight(true);
}

void Environment::onLose()
{
  this->stopAllActions();
  this->character->_destroy(true);
  this->water->runAction(
                         RepeatForever::create(
                                               Sequence::create(
                                                                TintTo::create(1.0, random(0, 255), random(0, 255), random(0, 255)),
                                                                nullptr
                                                                )
                                               )
                         );
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
void Environment::updateCamera(float time)
{
  auto position = Application->cameras.d->getPosition3D();
  auto rotation = Application->cameras.d->getRotation3D();

  auto ax = 0.0;
  auto ay = 0.0;
  auto az = 0.0;

  ax = ACCELEROMETER_FACTOR / ACCELERATION_FACTOR * time * abs(this->accelerationX - this->accelerometerX);
  ay = ACCELEROMETER_FACTOR / ACCELERATION_FACTOR * time * abs(this->accelerationY - this->accelerometerY);
  az = ACCELEROMETER_FACTOR / ACCELERATION_FACTOR * time * abs(this->accelerationZ - this->accelerometerZ);

  ax = ax * (this->accelerationX < this->accelerometerX ? 1 : -1);
  ay = ay * (this->accelerationY < this->accelerometerY ? 1 : -1);
  az = az * (this->accelerationZ < this->accelerometerZ ? 1 : -1);

  this->accelerationX += ax;
  this->accelerationZ += az;

  position.x += ax;
  position.z += az;

  rotation.x += az;
  rotation.y += ax;

  Application->cameras.d->setPosition3D(Vec3(position.x, position.y, position.z));
  Application->cameras.d->setRotation3D(Vec3(rotation.x, rotation.y, rotation.z));
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

  this->updateDusts(time);
  //this->updateFishes(time);

  //this->updateCamera(time);
}
