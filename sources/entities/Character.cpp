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
: Cube("cube2.obj")
{
  this->plane = new Entity3D(Application->environment->plane, true);
  this->plane->addChild(this);

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
void Character::reset()
{
  this->changeState(NORMAL);

  this->autoTurnLeft = false;
  this->autoTurnRight = false;

  this->manual = true;

  this->time = 0;
  this->lives = 0;
  this->sound = 1;

  this->plates.current = nullptr;
  this->plates.previous = nullptr;

  this->setPosition3D(Vec3(0, -1.1, 0));
  this->setRotation3D(Vec3(0, 0, 0));

  this->setOpacity(255);

  this->stopAllActions();
  this->plane->stopAllActions();

  this->runAction(
    EaseBounceOut::create(
      MoveTo::create(0.5, Vec3(0.0, 0.9, 0.0))
    )
  );

  /*this->plane->runAction(
    RepeatForever::create(
      Sequence::create(
        ScaleTo::create(0.2, 1.0, 1.2, 1.0),
        ScaleTo::create(0.2, 1.0, 1.0, 1.0),
        nullptr
      )
    )
  );*/
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
  this->reset();
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
  if(this->numberOfRunningActions() < 2 && this->manual)
  {
    if(this->plates.current)
    {
      if(this->plates.current->moved && !this->plates.current->avoid)
      {
        return false;
      }
    }

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
void Character::onTurnLeft(bool action, bool set)
{
  if(action)
  {
    if(set)
    {
      this->autoTurnLeft = true;
    }

    auto previous = this->plates.current;

    if(!this->isPlateRightBlocked() && this->onTouch())
    {
      auto next = this->getPlateRight(previous);

      if(next)
      {
        next->pauseSchedulerAndActions();
      }

      this->runAction(
        Spawn::create(
          RotateGlobalBy::create(0.1, Vec3(-90, 0, 0)),
          Sequence::create(
            MoveBy::create(0.05, Vec3(0.0, 0.2, -0.75)),
            MoveBy::create(0.05, Vec3(0.0, -0.2 - (this->getPositionY() - 0.9), -0.75)),
            CallFunc::create([=] () {
              if(next)
              {
                next->resumeSchedulerAndActions();
              }

              this->changeState(NORMAL);

              this->onTurn(LEFT);
            }),

            /**
             *
             * @Optional.
             * Uncomment this to enable auto turning.
             *
             *
            CallFunc::create([=] () {
              this->updateNormal(0);

              if(this->autoTurnLeft && this->state == NORMAL && this->manual)
              {
                this->runAction(
                  Sequence::create(
                    //DelayTime::create(0.05),
                    CallFunc::create([=] () {
                      if(this->autoTurnLeft && this->state == NORMAL && this->manual)
                      {
                        this->stopAllActions();
                        this->onTurnLeft(true, false);
                      }
                    }),
                    nullptr
                  )
                );
              }
            }),*/
            nullptr
          ),
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

void Character::onTurnRight(bool action, bool set)
{
  if(action)
  {
    if(set)
    {
      this->autoTurnRight = true;
    }

    auto previous = this->plates.current;

    if(!this->isPlateLeftBlocked() && this->onTouch())
    {
      auto next = this->getPlateLeft(previous);

      if(next)
      {
        next->pauseSchedulerAndActions();
      }

      this->runAction(
        Spawn::create(
          RotateGlobalBy::create(0.1, Vec3(0, 0, -90)),
          Sequence::create(
            MoveBy::create(0.05, Vec3(0.75, 0.2, 0)),
            MoveBy::create(0.05, Vec3(0.75, -0.2 - (this->getPositionY() - 0.9), 0)),
            CallFunc::create([=] () {
              if(next)
              {
                next->resumeSchedulerAndActions();
              }

              this->changeState(NORMAL);

              this->onTurn(RIGHT);
            }),

            /**
             *
             * @Optional.
             * Uncomment this to enable auto turning.
             *
             *
            CallFunc::create([=] () {
              this->updateNormal(0);

              if(this->autoTurnRight && this->state == NORMAL && this->manual)
              {
                this->runAction(
                  Sequence::create(
                    //DelayTime::create(0.05),
                    CallFunc::create([=] () {
                      if(this->autoTurnRight && this->state == NORMAL && this->manual)
                      {
                        this->stopAllActions();
                        this->onTurnRight(true, false);
                      }
                    }),
                    nullptr
                  )
                );
              }
            }),*/
            nullptr
          ),
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
bool Character::getManual()
{
  return this->manual;
}

bool Character::setManual(bool manual)
{
  this->manual = manual;

  return this->manual;
}

/**
 *
 *
 *
 */
int Character::addLive(int count)
{
  this->lives += count;

  return this->lives;
}

int Character::removeLive(int count)
{
  this->lives -= count;

  return this->lives;
}

/**
 *
 *
 *
 */
bool Character::isPlateLeftBlocked()
{
  if(this->getPlateLeft())
  {
    return this->getPlateLeft()->blocked;
  }

  return false;
}

bool Character::isPlateRightBlocked()
{
  if(this->getPlateRight())
  {
    return this->getPlateRight()->blocked;
  }

  return false;
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

  if(plate)
  {
    this->onLandSuccessful(turn, plate);
  }
  else
  {
    this->onLandFail(turn, plate);
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

    if(px == x && pz == z /*&& !plate->moved*/)
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
void Character::onLandSuccessful(Turn turn, Plate* plate, bool proceed)
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  if(plate->behavior == Plate::DYNAMIC)
  {
    if(plate->numberOfRunningActions() > 1)
    {
      return this->onLandFail(turn, plate);
    }
  }

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
        particle->setTexture("character-texture.png");
      }
    }
    else
    {
      particle->setTexture("character-texture.png");
    }
  }

  if(proceed)
  {
    if(plate->decoration)
    {
      plate->decoration->onPickup();
      plate->clearDecoration(!this->manual);
    }
  }

  Application->environment->generator->create();

  Sound->play("character-jump", this->sound);

  this->sound += 0.01f;
}

void Character::onLandFail(Turn turn, Plate* plate)
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
  Application->environment->plane->runAction(
    MoveBy::create(0.1, Vec3(0, 0, 1.5))
  );
}

void Character::onMoveRight()
{
  Application->environment->plane->runAction(
    MoveBy::create(0.1, Vec3(-1.5, 0, 0))
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

void Character::onCrash(Crash crash)
{
  this->plane->stopAllActions();

  switch(crash)
  {
    case SPIKES:
    this->runAction(
      Sequence::create(
        ScaleTo::create(0.1, 1.2),
        EaseSineIn::create(
          ScaleTo::create(0.3, 1.0)
        ),
        CallFunc::create([=] () {
          Application->changeState(Game::LOSE);
        }),
        MoveBy::create(2.0, Vec3(0, -0.8, 0)),
        nullptr
      )
    );
    break;
    case DOWN:
    this->runAction(
      Sequence::create(
        MoveBy::create(0.15, Vec3(0.0, -0.9, 0.0)),
        CallFunc::create([=] () {
          Application->changeState(Game::LOSE);
        }),
        nullptr
      )
    );
    break;
    case CATCH:
    this->runAction(
      Spawn::create(
        RotateGlobalBy::create(0.3, Vec3((this->plates.current->direction ? 0 : 20), 0, (this->plates.current->direction ? -20 : 0))),
        Sequence::create(
          EaseSineOut::create(
            MoveBy::create(0.5, Vec3(0, -1, 0))
          ),
          CallFunc::create([=] () {
            this->_destroy();
            Application->changeState(Game::LOSE);
          }),
          nullptr
        ),
        nullptr
      )
    );
    break;
  }

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
  if(!this->plates.current)
  {
    if(!current)
    {
      return nullptr;
    }
  }

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
      plate->position[Plate::LEFT] = true;
      plate->position[Plate::RIGHT] = false;

      return plate;
    }
  }

  return this->getPlateRightWithDefaults(current);
}

Plate* Character::getPlateLeft(Plate* current)
{
  if(!this->plates.current)
  {
    if(!current)
    {
      return nullptr;
    }
  }

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
      plate->position[Plate::LEFT] = false;
      plate->position[Plate::RIGHT] = true;

      return plate;
    }
  }

  return this->getPlateLeftWithDefaults(current);
}

Plate* Character::getPlateRightWithDefaults(Plate* current)
{
  int x = (current ? current->getStartPositionX() : this->plates.current->getStartPositionX()) / 1.5;
  int y = (current ? current->getStartPositionY() : this->plates.current->getStartPositionY()) / 1.5;
  int z = (current ? current->getStartPositionZ() : this->plates.current->getStartPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
    int py = position.y / 1.5;
    int pz = position.z / 1.5;

    if(px == x && pz == z - 1 && !(px == x && pz == z))
    {
      plate->position[Plate::LEFT] = true;
      plate->position[Plate::RIGHT] = false;

      return plate;
    }
  }

  return nullptr;
}

Plate* Character::getPlateLeftWithDefaults(Plate* current)
{
  int x = (current ? current->getStartPositionX() : this->plates.current->getStartPositionX()) / 1.5;
  int y = (current ? current->getStartPositionY() : this->plates.current->getStartPositionY()) / 1.5;
  int z = (current ? current->getStartPositionZ() : this->plates.current->getStartPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
    int py = position.y / 1.5;
    int pz = position.z / 1.5;

    if(px == x + 1 && pz == z && !(px == x && pz == z))
    {
      plate->position[Plate::LEFT] = false;
      plate->position[Plate::RIGHT] = true;

      return plate;
    }
  }

  return nullptr;
}

Character::Nears Character::getPlatesNear(Plate* current)
{
  Nears nears;

  nears.plates[Plate::LEFT] = this->getPlateLeft(current);
  nears.plates[Plate::RIGHT] = this->getPlateRight(current);

  return nears;
}

Character::Nears Character::getPlatesNearWithDefaults(Plate* current)
{
  Nears nears;

  nears.plates[Plate::LEFT] = this->getPlateLeftWithDefaults(current);
  nears.plates[Plate::RIGHT] = this->getPlateRightWithDefaults(current);

  return nears;
}

/**
 *
 *
 *
 */
void Character::changeState(State state, Crash crash)
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
      this->onCrash(crash);
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
        if(this->plates.current->decoration->stopable)
        {
          this->plates.current->decoration->stopAllActions();
        }

        if(--this->lives < 0)
        {
          this->changeState(CRASH, this->plates.current->decoration->status());
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
}

/**
 *
 *
 *
 */
void Character::setPosition3D(const Vec3& position)
{
  this->plane->setPosition3D(position);
}

void Character::setPositionX(float x)
{
  this->plane->setPositionX(x);
}

void Character::setPositionY(float y)
{
  this->plane->setPositionY(y);
}

void Character::setPositionZ(float z)
{
  this->plane->setPositionZ(z);
}

Vec3 Character::getPosition3D() const
{
  return this->plane->getPosition3D();
}

float Character::getPositionX()
{
  return this->plane->getPositionX();
}

float Character::getPositionY()
{
  return this->plane->getPositionY();
}

float Character::getPositionZ()
{
  return this->plane->getPositionZ();
}
