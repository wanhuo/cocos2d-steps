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
Character::Character()
: Cube("cube.obj", Application->environment->plane)
{
  this->setTexture("character-texture.png");

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
  this->changeState(NORMAL);

  this->autoTurnLeft = false;
  this->autoTurnRight = false;

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
      case NORMAL:
      this->changeState(JUMP);

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
void Character::onTurnLeft(bool action)
{
  if(action)
  {
    this->autoTurnLeft = true;

    if(this->onTouch())
    {
      this->runAction(
        Sequence::create(
          MoveBy::create(0.05, Vec3(0.0, 0.25, -0.75)),
          MoveBy::create(0.05, Vec3(0.0, -0.25, -0.75)),
          CallFunc::create([=] () {
            this->changeState(NORMAL);

            this->onTurn(LEFT);
          }),

          /**
           *
           * @Optional.
           * Uncomment this to enable auto turning.
           *
           *
          DelayTime::create(0.05),
          CallFunc::create([=] () {
            if(this->autoTurnLeft)
            {
              this->onTurnLeft();
            }
          }),
           */
          nullptr
        )
      );

      this->onMoveLeft();
    }
  }
  else
  {
    this->autoTurnLeft = false;
  }
}

void Character::onTurnRight(bool action)
{
  if(action)
  {
    this->autoTurnRight = true;

    if(this->onTouch())
    {
      this->runAction(
        Sequence::create(
          MoveBy::create(0.05, Vec3(0.75, 0.25, 0)),
          MoveBy::create(0.05, Vec3(0.75, -0.25, 0)),
          CallFunc::create([=] () {
            this->changeState(NORMAL);

            this->onTurn(RIGHT);
          }),

          /**
           *
           * @Optional.
           * Uncomment this to enable auto turning.
           *
           *
          DelayTime::create(0.05),
          CallFunc::create([=] () {
            if(this->autoTurnRight)
            {
              this->onTurnRight();
            }
          }),
           */
          nullptr
        )
      );

      this->onMoveRight();
    }
  }
  else
  {
    this->autoTurnRight = false;
  }
}

/**
 *
 *
 *
 */
void Character::onTurnUpdate(Plate* custom)
{
  this->onTurnUpdate(NONE, custom);
}

void Character::onTurnUpdate(Turn turn, Plate* custom)
{
  auto plate = custom ? custom : this->plates.current;

  if(plate && (custom || plate->getNumberOfRunningActions() < 3))
  {
    this->onLandSuccessful(turn, plate);
  }
  else
  {
    this->onLandFail(turn);
  }
}

void Character::onTurn(Turn turn)
{
  this->time = 0;

  int x = this->getPositionX() / 1.5;
  int z = this->getPositionZ() / 1.5;

  this->plates.current = nullptr;

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates->element(i));

    int px = plate->getPositionX() / 1.5;
    int pz = plate->getPositionZ() / 1.5;

    if(px == x && pz == z)
    {
      this->plates.current = plate;
      break;
    }
  }

  this->onTurnUpdate(turn);
}

/**
 *
 *
 *
 */
void Character::onLandSuccessful(Turn turn, Plate* plate)
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  plate->onCount();

  Application->counter->onCount();

  for(int i = 0; i < 10; i++)
  {
    auto particle = Application->environment->createParticle(x, y - 0.5, z);

    if(plate->decoration)
    {
      if(plate->decoration->removable)
      {
        particle->setTexture(plate->decoration->getParticleTexture());
      }
      else
      {
        particle->setTexture("particle-character-texture.png");
      }
    }
    else
    {
      particle->setTexture("particle-character-texture.png");
    }
  }

  if(plate->decoration)
  {
    plate->decoration->onPickup();
    plate->clearDecoration(!this->manual);
  }

  Application->environment->generator->create();

  Sound->play("character-jump", this->sound);

  this->sound += 0.01f;
}

void Character::onLandFail(Turn turn)
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  this->changeState(FALL);

  Application->environment->createRipple(x, z, 2);

  switch(turn)
  {
    case LEFT:
    this->runAction(
      Spawn::create(
        MoveBy::create(0.5, Vec3(0, -10, -1.5)),
        RotateBy::create(0.5, Vec3(-125, 0, 0)),
        Sequence::create(
          DelayTime::create(0.2),
          FadeOut::create(0.3),
          CallFunc::create([=] () {
          Application->changeState(Game::LOSE);
          }),
          nullptr
        ),
        nullptr
      )
    );
    break;
    case RIGHT:
    this->runAction(
      Spawn::create(
        MoveBy::create(0.5, Vec3(1.5, -10, 0)),
        RotateBy::create(0.5, Vec3(0, 0, 125)),
        Sequence::create(
          DelayTime::create(0.2),
          FadeOut::create(0.3),
          CallFunc::create([=] () {
          Application->changeState(Game::LOSE);
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

  for(int i = 0; i < 10 * 2; i++)
  {
    //Application->environment->createParticle(x, y, z)->setColor(this->getColor());
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
        Application->changeState(Game::LOSE);
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

  for(int i = 0; i < 10 * 2; i++)
  {
    Application->environment->createParticle(x, y, z)->setColor(this->getColor());
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
void Character::changeState(State state)
{
  if(this->state != state)
  {
    this->state = state;

    switch(this->state)
    {
      case NORMAL:
      this->onNormal();
      break;
      case JUMP:
      this->onJump();
      break;
      case FALL:
      this->onFall();
      break;
      case CRASH:
      this->onCrash();
      break;
      case HIT:
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
          this->changeState(CRASH);
        }
        else
        {
          this->changeState(HIT);
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
    case NORMAL:
    this->updateNormal(time);
    break;
    case JUMP:
    this->updateJump(time);
    break;
    case FALL:
    this->updateFall(time);
    break;
    case CRASH:
    this->updateCrash(time);
    break;
    case HIT:
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
      //Application->environment->whale->changeState(Whale::STATE_NORMAL);
    }
  }
}
