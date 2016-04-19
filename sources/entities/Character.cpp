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
: Cube("cube12.obj")//(patch::to_string("cube") + patch::to_string(random(1, 10)) + patch::to_string(".obj")).c_str())
{
  this->shadow = new Shadow("plate-down-shadow.obj", Application->environment->plane);
  this->shadow->setColor(Color3B(0, 0, 0));
  this->shadow->setMaxScale(Vec3(2.5, 2.5, 2.5));

  this->plane = new Entity3D(Application->environment->plane, true);
  this->plane->addChild(this);

  this->setTexture("cube12-texture.png");

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

  this->botEnabled = false;
  this->botWait = false;

  this->botTime = 0.00;
  this->botTimeElapsed = 0;

  this->botWaitTime = 0.2;
  this->botWaitTimeElapsed = 0;

  this->autoTurnLeft = false;
  this->autoTurnRight = false;

  this->manual = true;

  this->turns = 0;
  this->time = 0;
  this->lives = 0;
  this->steps = 0;
  this->sound = 1;

  this->soundTime = 0.5;
  this->soundTimeElapsed = 0;

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

  this->plane->runAction(
    RepeatForever::create(
      Sequence::create(
        ScaleTo::create(0.2, 1.0, 1.2, 1.0),
        ScaleTo::create(0.2, 1.0, 1.0, 1.0),
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
void Character::onSound(string file)
{
  Sound->play(file, false, this->sound, 1.0);

  this->soundTimeElapsed = 0;

  this->sound += 0.05f;
  this->steps++;
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
void Character::onTurn(bool action, bool set)
{
  if(action)
  {
    if(this->state == STATE_COPTER)
    {
      this->turns++;

      if(this->turns < STATE_COPTER_TURNS)
      {
        Application->counter->onCount();  

        this->onSound();

        return;
      }
      else
      {
        Sound->play("copter-success");

        Application->environment->characterActionHolder->runAction(
          Spawn::create(
            EaseSineInOut::create(
              ScaleTo::create(0.2, 1.2)
            ),
            EaseSineInOut::create(
              FadeOut::create(0.2)
            ),
            nullptr
          )
        );

        this->updateStates(0);

        this->changeState(NORMAL);
      }
    }

    this->turns = 0;

    if(this->getPlatesNearWithDefaults().plates[Plate::RIGHT])
    {
      this->onTurnLeft(action, set);
    }
    else
    {
      this->onTurnRight(action, set);
    }
  }
  else
  {
    this->onTurnLeft(action, set);
    this->onTurnRight(action, set);
  }
}

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
    if(plate->numberOfRunningActions() > 2)
    {
      return this->onLandFail(turn, plate);
    }
  }

  plate->onCount();

  Application->counter->onCount();

  string texture = "character-texture.png";

  for(Decoration* decoration : plate->getDecorations())
  {
    if(decoration->removable)
    {
      texture = decoration->getParticleTexture();
    }

    if(proceed)
    {
      decoration->onPickup();

      plate->clearDecorations(!this->manual);
    }
  }

  for(int i = 0; i < 10; i++)
  {
    auto particle = Application->environment->createParticle(x, y - 0.5, z);
    particle->setTexture(texture);
  }

  Application->environment->generator->create();

  this->onSound();

  if(plate->type == Plate::FINISH)
  {
    this->changeState(STATE_FINISH);
  }
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

  this->onEnvironmentMoveLeft();
}

void Character::onMoveRight()
{
  Application->environment->plane->runAction(
    MoveBy::create(0.1, Vec3(-1.5, 0, 0))
  );

  this->onEnvironmentMoveRight();
}

/**
 *
 *
 *
 */
void Character::onEnvironmentMoveLeft()
{
  for(int i = 0; i < Application->environment->dusts->count; i++)
  {
    Application->environment->dusts->element(i)->runAction(
      EaseSineInOut::create(
        MoveBy::create(0.25, Vec2(100.5, -100.5))
      )
    );
  }
}

void Character::onEnvironmentMoveRight()
{
  for(int i = 0; i < Application->environment->dusts->count; i++)
  {
    Application->environment->dusts->element(i)->runAction(
      EaseSineInOut::create(
        MoveBy::create(0.25, Vec2(-100.5, -100.5))
      )
    );
  }
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
    Application->environment->characterActionHolder->runAction(
      Spawn::create(
        EaseSineInOut::create(
          ScaleTo::create(0.2, 1.2)
        ),
        EaseSineInOut::create(
          FadeOut::create(0.2)
        ),
        nullptr
      )
    );

  this->plane->stopAllActions();

  switch(crash)
  {
    case SPIKES:
    this->runAction(
      Spawn::create(
        Sequence::create(
          ScaleTo::create(0.1, 1.2),
          EaseSineIn::create(
            ScaleTo::create(0.3, 1.0)
          ),
          DelayTime::create(1.0),
          CallFunc::create([=] () {
            Application->changeState(Game::LOSE);
          }),
          nullptr
        ),
        Sequence::create(
          DelayTime::create(0.4),
          MoveBy::create(2.0, Vec3(0, -0.8, 0)),
          nullptr
        ),
        nullptr
      )
    );
    break;
    case DOWN:
    this->runAction(
      Sequence::create(
        MoveBy::create(0.1f, Vec3(0.0, -0.9, 0.0)),
        DelayTime::create(1.0),
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
        MoveTo::create(0.1, Vec3(this->getPositionX(), 0.9, this->getPositionZ())),
        RotateGlobalBy::create(0.3, Vec3((this->plates.current->getDirection() ? 0 : 20), 0, (this->plates.current->getDirection() ? 20 : 0))),
        Sequence::create(
          EaseSineOut::create(
            MoveBy::create(0.5, Vec3(0, -1, 0))
          ),
          DelayTime::create(1.0),
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
    case GATE:
    this->plane->runAction(
      Sequence::create(
        ScaleTo::create(0.1, this->plates.current->getDirection() ? 1.0 : 0.1, 1.0, this->plates.current->getDirection() ? 0.1 : 1.0),
        DelayTime::create(1.0),
        CallFunc::create([=] () {
          Application->changeState(Game::LOSE);
        }),
        nullptr
      )
    );
    break;
    case COPTER:
    this->changeState(STATE_COPTER);
    break;
  }

  switch(crash)
  {
    case SPIKES:
    Sound->play("character-destroy-spikes");
    break;
    case DOWN:
    Sound->play("character-destroy-smash");
    break;
    case CATCH:
    Sound->play("character-destroy-catch");
    break;
    case GATE:
    Sound->play("character-destroy-smash");
    break;
    case COPTER:
    break;
  }
}

void Character::onHit()
{
  this->plates.current->clearDecorations(true);

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

void Character::onCopter()
{
  Application->environment->characterActionHolder->stopAllActions();
  Application->environment->characterActionHolder->setOpacity(255);
  Application->environment->characterActionHolder->setScale(0);
  Application->environment->characterActionHolder->runAction(
    EaseSineInOut::create(
      ScaleTo::create(0.5, 1.0)
    )
  );

  this->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.2, Vec3(0, 0.8, 0))
      ),
      CallFunc::create([=] () {
        this->runAction(
          RepeatForever::create(
            Sequence::create(
              EaseSineOut::create(
                MoveBy::create(0.5, Vec3(0, -0.4, 0))
              ),
              EaseSineOut::create(
                MoveBy::create(0.5, Vec3(0, 0.4, 0))
              ),
              nullptr
            )
          )
        );
      }),
      nullptr
    )
  );
}

void Character::onFinish()
{
  Application->changeState(Game::FINISH);

  this->plane->stopAllActions();
  this->plane->runAction(
      Sequence::create(
        DelayTime::create(0.6),
        EaseSineOut::create(
          ScaleTo::create(0.15, 0.8, 1.6, 0.8)
        ),
        EaseSineInOut::create(
          ScaleTo::create(0.5, 1.0, 1.0, 1.0)
        ),
        nullptr
      )
  );
  this->plane->runAction(
      Sequence::create(
        DelayTime::create(0.25),
        EaseSineInOut::create(
          ScaleTo::create(0.5, 1.2, 0.8, 1.2)
        ),
        nullptr
      )
  );

  this->runAction(
    Spawn::create(
      Sequence::create(
        DelayTime::create(0.5),
        RotateGlobalBy::create(0.5, Vec3(0, 180, 0)),
        RotateGlobalBy::create(0.5, Vec3(0, 720, 0)),
        nullptr
      ),
      Sequence::create(
        EaseSineOut::create(
          MoveBy::create(0.25, Vec3(0, 3, 0))
        ),
        EaseSineOut::create(
          MoveBy::create(0.35, Vec3(0, -1, 0))
        ),
        CallFunc::create([=] () {
        this->shadow->setVisible(false);
        }),
        EaseSineOut::create(
          MoveBy::create(0.5, Vec3(0, 18, 0))
        ),
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        this->shadow->setVisible(true);
        }),
        EaseSineIn::create(
          MoveBy::create(0.5, Vec3(0, -20, 0))
        ),
        CallFunc::create([=] () {
          Application->changeState(Game::GAME);

          Application->environment->runAction(
            Shake::create(0.5, 0.2)
          );

          this->changeState(NORMAL);
          this->onLandSuccessful(NONE, this->plates.current);

          Sound->play("landing-" + patch::to_string(random(1, 4)));

          if(Application->environment->generator->bonus)
          {
            Music->play("music-3", true);
          }
          else
          {
            Music->play("music-2", true);
          }
        }),
        nullptr
      ),
      nullptr
    )
  );

  Sound->play("character-finish");
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
  if(!this->plates.current)
  {
    if(!current)
    {
      return nullptr;
    }
  }

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
  if(!this->plates.current)
  {
    if(!current)
    {
      return nullptr;
    }
  }

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
      case STATE_COPTER:
      this->onCopter();
      break;
      case STATE_FINISH:
      this->onFinish();
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
    for(auto decoration : this->plates.current->getDecorations())
    {
      if(decoration->status())
      {
        if(decoration->stopable)
        {
          decoration->stopAllActions();
        }
  
        if(--this->lives < 0)
        {
          this->changeState(CRASH, decoration->status());
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

void Character::updateCopter(float time)
{
  this->turns -= 0.01;

  Application->environment->characterAction->setScaleX(min(1.0f, max(0.0f, this->turns / STATE_COPTER_TURNS)));
}

void Character::updateFinish(float time)
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
    case STATE_COPTER:
    this->updateCopter(time);
    break;
    case STATE_FINISH:
    this->updateFinish(time);
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
  Cube::update(time);

  /**
   *
   *
   *
   */
  this->updateStates(time);

  /**
   *
   *
   *
   */
  this->soundTimeElapsed += time;

  if(this->soundTimeElapsed >= this->soundTime)
  {
    this->steps = 0;
    this->sound = 1;
  }

  /**
   *
   *
   *
   */
  if(this->botEnabled)
  {
    this->botTimeElapsed += time;

    if(this->botTimeElapsed >= this->botTime)
    {
      this->botTimeElapsed = this->state == STATE_COPTER ? -0.1 : 0.0;

      if(Application->environment->character->plates.current)
      {
        auto element = Application->environment->character->plates.current;
        auto plates = Application->environment->character->getPlatesNear(element);

        if(plates.plates[Plate::LEFT])
        {
          element = plates.plates[Plate::LEFT];
        }
        else
        {
          element = plates.plates[Plate::RIGHT];
        }

        if(element)
        {
          for(auto decoration : element->getDecorations())
          {
            if((decoration->enable || element->moved) && element->type != Plate::COPTER)
            {
              return;
            }
          }

          if(element->getDecorations().size())
          {
            if(!this->botWait && this->plates.previous)
            {
              if(this->plates.previous->getDecorations().size()) this->botWait = true;
            }
          }

          if(this->botWait)
          {
            this->botWaitTimeElapsed += time;

            if(this->botWaitTimeElapsed >= this->botWaitTime)
            {
              this->botWaitTimeElapsed = 0;
              this->botWait = false;
            }
          }

          if((this->state == NORMAL || this->state == STATE_COPTER) && !this->botWait)
          {
            this->onTurn();
          }
        }
      }
    }
  }
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
