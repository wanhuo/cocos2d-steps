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
Character::Character(Environment* environment)
: Cube("cube.obj", environment->plane)
{
  this->environment = environment;

  this->plane = new Entity3D(this, true);
  this->plane->setPosition3D(Vec3(0, 0, 0));
  this->plane->setRotation3D(Vec3(0, 0, 0));

  this->setTexture("cube-texture.png");

  this->setScheduleUpdate(true);
}

Character::~Character()
{
}

/**
 *
 *
 *
 */
void Character::onCreate()
{
  Cube::onCreate();

  /**
   *
   *
   *
   */
  this->changeState(STATE_NORMAL);

  this->manual = true;

  this->time = 0;
  this->lives = 0;
  this->sound = 1;

  this->plates.current = nullptr;
  this->plates.previous = nullptr;

  this->setPosition3D(Vec3(0, -4.1, 0));
  this->setRotation3D(Vec3(0, 0, 0));

  this->setOpacity(0);

  this->runAction(
    Spawn::create(
      EaseSineOut::create(
        MoveBy::create(0.5, Vec3(0, 5, 0))
      ),
      FadeTo::create(0.5, 255),
      nullptr
    )
  );
}

void Character::onDestroy(bool action)
{
  Cube::onDestroy(action);
}

/**
 *
 *
 *
 */
bool Character::onTouch()
{
  if(this->numberOfRunningActions() < 1 && this->manual)
  {
    switch(this->state)
    {
      case STATE_NORMAL:
      this->changeState(STATE_JUMP);

      return true;
      break;
    }
  }

  return false;
}

/**
 *
 *
 *
 */
void Character::onTurnLeft()
{
  if(this->onTouch())
  {
    auto x = this->getPositionX();
    auto y = this->getPositionY();
    auto z = this->getPositionZ() - 1.5;

    this->runAction(
      Sequence::create(
        MoveBy::create(0.05, Vec3(0, 0.5, -0.75)),
        MoveTo::create(0.05, Vec3(x, y, z)),
        CallFunc::create([=] () {
        this->changeState(STATE_NORMAL);

        this->onTurn(TURN_LEFT);
        }),
        nullptr
      )
    );

    this->onMoveLeft();
  }
}

void Character::onTurnRight()
{
  if(this->onTouch())
  {
    auto x = this->getPositionX() + 1.5;
    auto y = this->getPositionY();
    auto z = this->getPositionZ();

    this->runAction(
      Sequence::create(
        MoveBy::create(0.05, Vec3(0.75, 0.5, 0)),
        MoveTo::create(0.05, Vec3(x, y, z)),
        CallFunc::create([=] () {
        this->changeState(STATE_NORMAL);

        this->onTurn(TURN_RIGHT);
        }),
        nullptr
      )
    );

    this->onMoveRight();
  }
}

void Character::onTurnUpdate(int index, Plate* custom)
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  auto plate = custom ? custom : this->plates.current;

  if(plate && (custom || plate->getNumberOfRunningActions() < 3))
  {
    plate->setTexture("plate-texture-2.png");

    Application->counter->onCount();

    for(int i = 0; i < PARTICLES_COUNT; i++)
    {
      auto particle = static_cast<Entity3D*>(this->environment->particles->_create());

      particle->setTexture("cube-texture.png");

      particle->setScale(random(0.5, 1.0));
      particle->setPositionX(x);
      particle->setPositionY(y - 0.5);
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

      if(plate->decoration)
      {
        if(plate->decoration->removable)
        {
          particle->setColor(plate->decoration->getColor());
        }
        else
        {
          particle->setColor(this->getColor());
        }
      }
      else
      {
        particle->setColor(this->getColor());
      }
    }

    if(plate->decoration)
    {
      plate->decoration->onPickup();
      plate->clearDecoration(!this->manual);
    }

    this->environment->generator->spawn();

    Sound->play("character-jump", this->sound);

    this->sound += 0.01f;
  }
  else
  {
    this->changeState(STATE_FALL);

    Application->environment->createRipple(x, z, 2);

    switch(index)
    {
      case TURN_LEFT:
      this->runAction(
        Spawn::create(
          MoveBy::create(0.5, Vec3(0, -10, -1.5)),
          RotateBy::create(0.5, Vec3(-125, 0, 0)),
          Sequence::create(
            DelayTime::create(0.2),
            FadeOut::create(0.3),
            CallFunc::create([=] () {
            Application->changeState(Game::STATE_LOSE);
            }),
            nullptr
          ),
          nullptr
        )
      );
      break;
      case TURN_RIGHT:
      this->runAction(
        Spawn::create(
          MoveBy::create(0.5, Vec3(1.5, -10, 0)),
          RotateBy::create(0.5, Vec3(0, 0, 125)),
          Sequence::create(
            DelayTime::create(0.2),
            FadeOut::create(0.3),
            CallFunc::create([=] () {
            Application->changeState(Game::STATE_LOSE);
            }),
            nullptr
          ),
          nullptr
        )
      );
      break;
    }

    Sound->play("water");
  }
}

void Character::onTurn(int index)
{
  this->time = 0;

  int x = this->getPositionX() / 1.5;
  int z = this->getPositionZ() / 1.5;

  this->plates.current = nullptr;

  for(int i = 0; i < this->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(this->environment->plates->element(i));

    int px = plate->getPositionX() / 1.5;
    int pz = plate->getPositionZ() / 1.5;

    if(px == x && pz == z)
    {
      this->plates.current = plate;
      break;
    }
  }

  this->onTurnUpdate(index);
}

/**
 *
 *
 *
 */
void Character::onMoveLeft()
{
  Application->cameras.d->runAction(
    MoveBy::create(0.1, Vec3(-sqrt(pow(1.5, 2) / 2), 0.0, -sqrt(pow(1.5, 2) / 2)))
  );

  Application->environment->water->runAction(
    MoveBy::create(0.1, Vec3(0.0, 0.0, -1.5))
  );
}

void Character::onMoveRight()
{
  Application->cameras.d->runAction(
    MoveBy::create(0.1, Vec3(sqrt(pow(1.5, 2) / 2), 0.0, -sqrt(pow(1.5, 2) / 2)))
  );

  Application->environment->water->runAction(
    MoveBy::create(0.1, Vec3(1.5, 0.0, 0.0))
  );
}

/**
 *
 *
 *
 */
void Character::onNormal()
{
}

void Character::onJump()
{
  this->plates.current = nullptr;
  this->stopAllActions();
}

void Character::onFall()
{
}

void Character::onCrash()
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  //this->setColor(Color3B(255, 0, 0));

  for(int i = 0; i < PARTICLES_COUNT * 2; i++)
  {
    //this->environment->createParticle(x, y, z)->setColor(this->getColor());
  }

  this->runAction(
    Spawn::create(
      Sequence::create(
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(0, 5, 0))
        ),
        EaseSineInOut::create(
          MoveBy::create(0.5, Vec3(0, -5, 0))
        ),
        nullptr
      ),
      RotateBy::create(1.0, Vec3(random(-100, 100), random(-100, 100), random(-100, 100))),
      Sequence::create(
        DelayTime::create(1.0),
        CallFunc::create([=] () {
        Application->changeState(Game::STATE_LOSE);
        }),
        nullptr
      ),
      nullptr
    )
  );

  Sound->play("character-hit");
}

void Character::onHit()
{
  this->plates.current->clearDecoration(true);

  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  //this->setColor(Color3B(255, 0, 0));

  for(int i = 0; i < PARTICLES_COUNT * 2; i++)
  {
    this->environment->createParticle(x, y, z)->setColor(this->getColor());
  }

  /*this->runAction(
    Sequence::create(
      DelayTime::create(0.5),
      TintTo::create(0.1, Color3B(33, 104, 193)),
      CallFunc::create([=] () {
        this->changeState(STATE_NORMAL);
      }),
      nullptr
    )
  );*/

  Sound->play("character-hit");
}

/**
 *
 *
 *
 */
Plate* Character::getPlateRight(Plate* current)
{
  int x = (current ? current->getPositionX() : this->plates.current->getPositionX()) / 1.5;
  int y = (current ? current->getPositionY() : this->plates.current->getPositionY()) / 1.5;
  int z = (current ? current->getPositionZ() : this->plates.current->getPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates->element(i));
    auto position = plate->getPosition3D();

    int px = position.x / 1.5;
    int py = position.y / 1.5;
    int pz = position.z / 1.5;

    if(px == x && pz == z - 1 && !(px == x && pz == z))
    {
      plate->LEFT = true;
      plate->RIGHT = false;

      return plate;
    }
  }

  return this->getPlateRightWithDefaults(current);
}

Plate* Character::getPlateLeft(Plate* current)
{
  int x = (current ? current->getPositionX() : this->plates.current->getPositionX()) / 1.5;
  int y = (current ? current->getPositionY() : this->plates.current->getPositionY()) / 1.5;
  int z = (current ? current->getPositionZ() : this->plates.current->getPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates->element(i));
    auto position = plate->getPosition3D();

    int px = position.x / 1.5;
    int py = position.y / 1.5;
    int pz = position.z / 1.5;

    if(px == x + 1 && pz == z && !(px == x && pz == z))
    {
      plate->LEFT = false;
      plate->RIGHT = true;

      return plate;
    }
  }

  return this->getPlateLeftWithDefaults(current);
}

Plate* Character::getPlateRightWithDefaults(Plate* current)
{
  int x = (current ? current->startPositionX : this->plates.current->startPositionX) / 1.5;
  int y = (current ? current->startPositionY : this->plates.current->startPositionY) / 1.5;
  int z = (current ? current->startPositionZ : this->plates.current->startPositionZ) / 1.5;

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates->element(i));
    auto position = Vec3(plate->startPositionX, plate->startPositionY, plate->startPositionZ);

    int px = position.x / 1.5;
    int py = position.y / 1.5;
    int pz = position.z / 1.5;

    if(px == x && pz == z - 1 && !(px == x && pz == z))
    {
      plate->LEFT = true;
      plate->RIGHT = false;

      return plate;
    }
  }

  return nullptr;
}

Plate* Character::getPlateLeftWithDefaults(Plate* current)
{
  int x = (current ? current->startPositionX : this->plates.current->startPositionX) / 1.5;
  int y = (current ? current->startPositionY : this->plates.current->startPositionY) / 1.5;
  int z = (current ? current->startPositionZ : this->plates.current->startPositionZ) / 1.5;

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates->element(i));
    auto position = Vec3(plate->startPositionX, plate->startPositionY, plate->startPositionZ);

    int px = position.x / 1.5;
    int py = position.y / 1.5;
    int pz = position.z / 1.5;

    if(px == x + 1 && pz == z && !(px == x && pz == z))
    {
      plate->LEFT = false;
      plate->RIGHT = true;

      return plate;
    }
  }

  return nullptr;
}

Character::NearPlates Character::getPlatesNear(Plate* current)
{
  Character::NearPlates plates;

  plates.LEFT = this->getPlateLeft(current);
  plates.RIGHT = this->getPlateRight(current);

  return plates;
}

/**
 *
 *
 *
 */
void Character::changeState(int state)
{
  if(this->state != state)
  {
    this->state = state;

    switch(this->state)
    {
      case STATE_NORMAL:
      this->onNormal();
      break;
      case STATE_JUMP:
      this->onJump();
      break;
      case STATE_FALL:
      this->onFall();
      break;
      case STATE_CRASH:
      this->onCrash();
      break;
      case STATE_HIT:
      this->onHit();
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Character::updateNormal(float time)
{
  if(this->plates.current && this->manual)
  {
    if(this->plates.current->decoration)
    {   
      if(this->plates.current->decoration->status())
      {
        if(--this->lives < 0)
        {
          this->changeState(STATE_CRASH);
        }
        else
        {
          this->changeState(STATE_HIT);
        }
      } 
    }
  }
}

void Character::updateJump(float time)
{
}

void Character::updateFall(float time)
{
}

void Character::updateCrash(float time)
{
}

void Character::updateHit(float time)
{
}

/**
 *
 *
 *
 */
void Character::updateStates(float time)
{
  switch(this->state)
  {
    case STATE_NORMAL:
    this->updateNormal(time);
    break;
    case STATE_JUMP:
    this->updateJump(time);
    break;
    case STATE_FALL:
    this->updateFall(time);
    break;
    case STATE_CRASH:
    this->updateCrash(time);
    break;
    case STATE_HIT:
    this->updateHit(time);
    break;
  }
}

/**
 *
 *
 *
 */
void Character::update(float time)
{
  this->updateStates(time);

  /**
   *
   *
   *
   */
  if(this->manual)
  {
    this->time += time;

    if(this->time >= Whale::TIME && Application->counter->value > 0)
    {
      Application->environment->whale->changeState(Whale::STATE_NORMAL);
    }
  }
}
