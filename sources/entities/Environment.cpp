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
  this->plane->setRotation3D(Vec3(0, 0, 0));
  this->plane->setPosition3D(Vec3(0, 0, 0));

  this->water = new Entity3D("water.obj", this, true);
  this->water->setRotation3D(Vec3(0, 0, 0));
  this->water->setPosition3D(Vec3(0, 0, 0));
  this->water->setColor(Color3B(84, 205, 240));
  this->water->setOpacity(220);

  this->dusts = new Pool(new Dust, this);

  this->start = new Decoration("start.obj", this->plane);

  this->spikes = new Pool(new Spike, this->plane);
  this->ups = new Pool(new Up, this->plane);
  this->downs = new Pool(new Down, this->plane);
  this->diamonds = new Pool(new Diamond, this->plane);
  this->crystals = new Pool(new Crystal, this->plane);
  this->energies = new Pool(new Energy, this->plane);
  this->stars = new Pool(new Star, this->plane);
  this->hearts = new Pool(new Heart, this->plane);

  this->plates = new Pool(new Plate, this->plane);
  this->particles = new Pool(new Particle, this->plane);
  this->fishes = new Pool(new Fish, this->plane);
  this->ripples = new Pool(new Ripple, this->plane);

  this->plates_spikes = new Pool(new Special("plate-type-spike.obj"), this->plane);
  this->plates_up = new Pool(new Special("plate-type-up.obj"), this->plane);
  this->plates_saw = new Pool(new TypeSaw, this->plane);
  this->plates_gate = new Pool(new TypeGate, this->plane);
  this->plates_copter = new Pool(new TypeCopter, this->plane);

  this->character = new Character;
  this->generator = new Generator;

  this->characterActionHolder = new Background(this);
  this->characterActionHolder->setContentSize(Size(Application->getWidth(), 40));
  this->characterActionHolder->setPosition(Vec2(0, 950));
  this->characterActionHolder->setCameraMask(4);

  this->characterActionBackground = new BackgroundColor(this->characterActionHolder, Color4B(255, 255, 255, 50));
  this->characterActionBackground->setContentSize(Size(Application->getWidth() - 100, 40));
  this->characterActionBackground->setAnchorPoint(Vec2(0, 0));
  this->characterActionBackground->setPosition(Vec2(50, 10));
  this->characterActionBackground->setCameraMask(4);

  this->characterAction = new BackgroundColor(this->characterActionHolder, Color4B(255, 255, 255, 50));
  this->characterAction->setContentSize(Size(Application->getWidth() - 110, 30));
  this->characterAction->setAnchorPoint(Vec2(0, 0));
  this->characterAction->setPosition(Vec2(55, 15));
  this->characterAction->setCameraMask(4);

  this->characterActionHolder->setScale(0);

  this->onGame();

  this->color = new Color(255, 84, 205, 250);

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
Vec3 Environment::position()
{
  auto x = this->character->getPositionX() + random(-5.0, 5.0);
  auto y = 0;
  auto z = this->character->getPositionZ() + random(-5.0, 5.0);

  return Vec3(x, y, z);
}

/**
 *
 *
 *
 */
void Environment::onTurn(bool action)
{
  this->character->onTurn(action);
}

/**
 *
 *
 *
 */
void Environment::onMenu()
{
  this->plates->clear(true);
  this->plates_spikes->clear(true);
  this->plates_up->clear(true);
  this->plates_saw->clear(true);
  this->plates_gate->clear(true);
  this->plates_copter->clear(true);

  this->spikes->clear(true);
  this->ups->clear(true);
  this->downs->clear(true);

  this->ripples->clear(true);

  this->generator->clear();

  this->character->_destroy();
  this->character = new Character;

  this->character->_create();
  this->character->reset();

  this->plane->setPosition3D(Vec3(0, 0, 0));
  this->water->setRotation3D(Vec3(0, 0, 0));
  this->water->setPosition3D(Vec3(0, 0, 0));
}

void Environment::onGame()
{
  this->onTurn();
}

void Environment::onLose()
{
  this->stopAllActions();
}

void Environment::onCopter()
{
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
  this->updateLight(time);
  //this->updateFishes(time);

  //this->updateCamera(time);

}
