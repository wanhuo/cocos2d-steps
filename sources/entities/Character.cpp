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
: Cube("character-" + to_string(Application->environment->parameters.character) + ".obj")
{
  this->shadow = new Shadow("character-shadow.obj");
  this->shadow->setMaxScale(Vec3(2.5, 2.5, 2.5));

  this->plane = new Entity3D(Application->environment->plane, true);
  this->plane->addChild(this);

  if(Storage::get("character.color"))
  {
    auto r = Storage::get("character.color.r");
    auto g = Storage::get("character.color.g");
    auto b = Storage::get("character.color.b");

    this->color = Color3B(r, g, b);
  }
  else
  {
    this->color = Color3B(224.0, 95.0, 171.0);
  }

  this->setTexture(Application->environment->getTextureState1());

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
  if(!this->Node::state->create)
  {
    this->_create();
  }

  this->plane->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->plane->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->plane->setScale(1.0);

  this->plane->stopAllActions();

  this->plane->runAction(
    RepeatForever::create(
      Sequence::create(
        ScaleTo::create(0.2, 1.0, 1.2, 1.0),
        ScaleTo::create(0.2, 1.0, 1.0, 1.0),
        nullptr
      )
    )
  );

  /**
   *
   *
   *
   */
  this->changeState(STATE_NORMAL);

  this->autoTurnLeft = false;
  this->autoTurnRight = false;

  this->manual = true;
  this->automatecally = false;

  this->turns = 0;
  this->time = 0;
  this->lives = 0;
  this->steps = 0;
  this->sound = 1;

  this->soundTime = 0.5;
  this->soundTimeElapsed = 0;

  this->plates.current = nullptr;
  this->plates.previous = nullptr;

  this->setScale(1.0);

  this->setPosition3D(Vec3(0.0, 1.3, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->stopAllActions();

  switch(Application->environment->parameters.character)
  {
    default:
    this->setColor(this->color);
    break;
    case 3:
    this->setColor(Color3B(255.0, 255.0, 255.0));
    break;
  }
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
void Character::onSound()
{
  Sound->play("character-jump", false, this->sound, 1.0);

  this->soundTimeElapsed = 0;

  this->sound += 0.05 * (Application->environment->star ? 2 : 1);
  this->steps += 1.0 * (Application->environment->star ? 2 : 1);
}

/**
 *
 *
 *
 */
bool Character::onTouch()
{
  if(Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget(this) < 2 && this->manual)
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
      default:
      break;
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
void Character::onTurn(bool action, bool set, bool rotation, float time)
{
  if(Director::getInstance()->getActionManager()->getActionByTag(7, this->plane) && !action)
  {
    return;
  }

  if(action)
  {
    if(this->state == STATE_COPTER)
    {
      this->turns++;

      if(this->turns < STATE_COPTER_TURNS)
      {
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

        this->changeState(STATE_NORMAL);
      }
    }

    this->turns = 0;

    if(this->getPlatesNearWithDefaults().plates[Plate::RIGHT])
    {
      this->onTurnLeft(action, set, rotation, time);
    }
    else
    {
      this->onTurnRight(action, set, rotation, time);
    }
  }
  else
  {
    this->onTurnLeft(action, set, rotation, time);
    this->onTurnRight(action, set, rotation, time);
  }
}

void Character::onTurnLeft(bool action, bool set, bool rotation, float time)
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
        if(!this->getAutomatecally())
        {
          if(Application->environment->enemy && Application->environment->enemy->Node::state->create)
          {
            if(Application->environment->enemy->state != STATE_NORMAL && Application->environment->enemy->state != STATE_CRASH)
            {
              if(abs(Application->environment->enemy->plates.current->getIndex() - this->plates.current->getIndex()) < 3)
              {
                this->changeState(STATE_NORMAL);
                return;
              }
            }

            if(Application->environment->enemy->plates.current == next || Application->environment->enemy->plates.current == previous)
            {
              if(Application->environment->enemy->state == STATE_NORMAL)
              {
                Application->environment->enemy->plane->Node::runAction(
                  Sequence::create(
                    CallFunc::create([=] () {
                    Sound->play("insane-brick-" + to_string(random(1, 3)));
                    }),
                    CallFunc::create([=] () {
                    Application->environment->enemy->onTurn(true, true, true, 0.1);
                    }),
                    DelayTime::create(0.15),
                    CallFunc::create([=] () {
                    Application->environment->enemy->onTurn(true, true, true, 0.1);
                    }),
                    DelayTime::create(0.15),
                    CallFunc::create([=] () {
                    Application->environment->enemy->onTurn(true, true, true, 0.1);
                    }),
                    DelayTime::create(0.1),
                    nullptr
                  ), 7
                );
                Application->environment->character->plane->Node::runAction(
                  DelayTime::create(0.4), 7
                );
                Application->environment->enemy->setColor(Color3B::WHITE);
                Application->environment->enemy->plane->runAction(
                  Sequence::create(
                    DelayTime::create(0.1),
                    CallFunc::create([=] () {
                    Application->environment->enemy->setColor(Application->environment->enemy->color);
                    }),
                    nullptr
                  )
                );

                if(probably(20))
                {
                  Application->environment->enemy->plates.current->setType(Plate::DIAMOND, false);
                  for(auto decoration : Application->environment->enemy->plates.current->getDecorations())
                  {
                    decoration->setPosition3D(Application->environment->enemy->getPosition3D());
                    decoration->setPositionZ(decoration->getPositionZ() - 0.75);
                    decoration->runAction(
                      Spawn::create(
                        Sequence::create(
                          EaseSineOut::create(
                            MoveBy::create(0.15, Vec3(0.0, 3.0, -0.0))
                          ),
                          EaseSineIn::create(
                            MoveBy::create(0.1, Vec3(0.0, -1.0, 0.0))
                          ),
                          CallFunc::create([=] () {
                          decoration->onPickup();
                          decoration->_destroy();
                          }),
                          nullptr
                        ),
                        nullptr
                      )
                    );
                  }

                  Application->environment->enemy->plates.current->getDecorations().clear();
                }
              }
              else if(Application->environment->enemy->state != STATE_CRASH)
              {
                this->changeState(STATE_NORMAL);

                return;
              }
            }
          }
        }

        if(this->plates.current->getStage() != next->getStage())
        {
          this->changeState(STATE_NORMAL);
          return;
        }

        Director::getInstance()->getActionManager()->pauseTarget(next);
        Director::getInstance()->getScheduler()->pauseTarget(next);

        Director::getInstance()->getActionManager()->pauseTarget(next->special);
        Director::getInstance()->getScheduler()->pauseTarget(next->special);
      }

      int stage = next ? next->getStage() : 1;

      this->runAction(
        Spawn::create(
          RotateGlobalBy::create(time, Vec3(rotation ? -90 : 0, 0, 0)),
          Sequence::create(
            MoveBy::create(time / 2, Vec3(0.0, rotation ? 0.2 : 0, -0.75)),
            MoveBy::create(time / 2, Vec3(0.0, rotation ? (-0.2 - (this->getPositionY() - 1.3 - (stage * 0.8))) : 0, -0.75)),
            CallFunc::create([=] () {
              this->changeState(STATE_NORMAL);
              this->onTurn(LEFT);

              if(next)
              {
                Director::getInstance()->getActionManager()->resumeTarget(next);
                Director::getInstance()->getScheduler()->resumeTarget(next);

                Director::getInstance()->getActionManager()->resumeTarget(next->special);
                Director::getInstance()->getScheduler()->resumeTarget(next->special);
              }
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

      this->onMoveLeft(time);
    }
  }
  else
  {
    this->autoTurnLeft = false;
  }
}

void Character::onTurnRight(bool action, bool set, bool rotation, float time)
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
        if(!this->getAutomatecally())
        {
          if(Application->environment->enemy && Application->environment->enemy->Node::state->create)
          {
            if(Application->environment->enemy->state != STATE_NORMAL && Application->environment->enemy->state != STATE_CRASH)
            {
              if(abs(Application->environment->enemy->plates.current->getIndex() - this->plates.current->getIndex()) < 3)
              {
                this->changeState(STATE_NORMAL);
                return;
              }
            }

            if(Application->environment->enemy->plates.current == next || Application->environment->enemy->plates.current == previous)
            {
              if(Application->environment->enemy->state == STATE_NORMAL)
              {
                Application->environment->enemy->plane->Node::runAction(
                  Sequence::create(
                    CallFunc::create([=] () {
                    Sound->play("insane-brick-" + to_string(random(1, 3)));
                    }),
                    CallFunc::create([=] () {
                    Application->environment->enemy->onTurn(true, true, true, 0.1);
                    }),
                    DelayTime::create(0.15),
                    CallFunc::create([=] () {
                    Application->environment->enemy->onTurn(true, true, true, 0.1);
                    }),
                    DelayTime::create(0.15),
                    CallFunc::create([=] () {
                    Application->environment->enemy->onTurn(true, true, true, 0.1);
                    }),
                    DelayTime::create(0.1),
                    nullptr
                  ), 7
                );
                Application->environment->character->plane->Node::runAction(
                  DelayTime::create(0.4), 7
                );
                Application->environment->enemy->setColor(Color3B::WHITE);
                Application->environment->enemy->plane->runAction(
                  Sequence::create(
                    DelayTime::create(0.1),
                    CallFunc::create([=] () {
                    Application->environment->enemy->setColor(Application->environment->enemy->color);
                    }),
                    nullptr
                  )
                );

                if(probably(20))
                {
                  Application->environment->enemy->plates.current->setType(Plate::DIAMOND, false);
                  for(auto decoration : Application->environment->enemy->plates.current->getDecorations())
                  {
                    decoration->setPosition3D(Application->environment->enemy->getPosition3D());
                    decoration->setPositionZ(decoration->getPositionZ() - 0.75);
                    decoration->runAction(
                      Spawn::create(
                        Sequence::create(
                          EaseSineOut::create(
                            MoveBy::create(0.15, Vec3(0.0, 3.0, -0.0))
                          ),
                          EaseSineIn::create(
                            MoveBy::create(0.1, Vec3(0.0, -1.0, 0.0))
                          ),
                          CallFunc::create([=] () {
                          decoration->onPickup();
                          decoration->_destroy();
                          }),
                          nullptr
                        ),
                        nullptr
                      )
                    );
                  }

                  Application->environment->enemy->plates.current->getDecorations().clear();
                }
              }
              else if(Application->environment->enemy->state != STATE_CRASH)
              {
                this->changeState(STATE_NORMAL);

                return;
              }
            }
          }
        }

        if(this->plates.current->getStage() != next->getStage())
        {
          this->changeState(STATE_NORMAL);
          return;
        }

        Director::getInstance()->getActionManager()->pauseTarget(next);
        Director::getInstance()->getScheduler()->pauseTarget(next);

        Director::getInstance()->getActionManager()->pauseTarget(next->special);
        Director::getInstance()->getScheduler()->pauseTarget(next->special);
      }

      int stage = next ? next->getStage() : 1;

      this->runAction(
        Spawn::create(
          RotateGlobalBy::create(time, Vec3(0, 0, rotation ? -90 : 0)),
          Sequence::create(
            MoveBy::create(time / 2, Vec3(0.75, 0.2, 0)),
            MoveBy::create(time / 2, Vec3(0.75, -0.2 - (this->getPositionY() - 1.3 - (stage * 0.8)), 0)),
            CallFunc::create([=] () {
              this->changeState(STATE_NORMAL);
              this->onTurn(RIGHT);

              if(next)
              {
                Director::getInstance()->getActionManager()->resumeTarget(next);
                Director::getInstance()->getScheduler()->resumeTarget(next);

                Director::getInstance()->getActionManager()->resumeTarget(next->special);
                Director::getInstance()->getScheduler()->resumeTarget(next->special);
              }
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

      this->onMoveRight(time);
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
void Character::onTurnBack(bool action, bool set, bool rotation, float time)
{
  if(action)
  {
    if(this->state == STATE_COPTER)
    {
      this->turns++;

      if(this->turns < STATE_COPTER_TURNS)
      {
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

        this->changeState(STATE_NORMAL);
      }
    }

    this->turns = 0;

    if(this->plates.current->getDirection())
    {
      this->onTurnBackRight(action, set, rotation, time);
    }
    else
    {
      this->onTurnBackLeft(action, set, rotation, time);
    }
  }
  else
  {
    this->onTurnBackLeft(action, set, rotation, time);
    this->onTurnBackRight(action, set, rotation, time);
  }
}

void Character::onTurnBackLeft(bool action, bool set, bool rotation, float time)
{
  if(action)
  {
    auto previous = this->plates.current;

    if(!this->isPlateRightBlocked() && this->onTouch())
    {
      auto next = this->getBackPlateRight(previous);

      if(next)
      {
        if(this->getAutomatecally())
        {
          if(Application->environment->character->state != STATE_NORMAL)
          {
            if(abs(Application->environment->enemy->plates.current->getIndex() - this->plates.current->getIndex()) < 3)
            {
              this->changeState(STATE_NORMAL);
              return;
            }
          }

          if(Application->environment->character->plates.current == next || Application->environment->character->plates.current == previous)
          {
            if(Application->environment->character->state == STATE_NORMAL)
            {
              Application->environment->character->plane->Node::runAction(
                Sequence::create(
                  CallFunc::create([=] () {
                  Sound->play("insane-brick-" + to_string(random(1, 3)));
                  }),
                  CallFunc::create([=] () {
                  Application->environment->character->onTurnBack(true, true, true, 0.1);
                  }),
                  DelayTime::create(0.15),
                  CallFunc::create([=] () {
                  Application->environment->character->onTurnBack(true, true, true, 0.1);
                  }),
                  DelayTime::create(0.15),
                  CallFunc::create([=] () {
                  Application->environment->character->onTurnBack(true, true, true, 0.1);
                  }),
                  DelayTime::create(0.1),
                  nullptr
                ), 7
              );
              Application->environment->enemy->plane->Node::runAction(
                DelayTime::create(0.4), 7
              );
              Application->environment->character->setColor(Color3B::WHITE);
              Application->environment->character->plane->runAction(
                Sequence::create(
                  DelayTime::create(0.1),
                  CallFunc::create([=] () {
                  Application->environment->character->setColor(Application->environment->character->color);
                  }),
                  nullptr
                )
              );
            }
            else
            {
              this->changeState(STATE_NORMAL);

              return;
            }
          }
        }
        else
        {
          this->plates.current->onUncount(true);
        }

        if(this->plates.current->getStage() != next->getStage())
        {
          this->changeState(STATE_NORMAL);
          return;
        }

        Director::getInstance()->getActionManager()->pauseTarget(next);
        Director::getInstance()->getScheduler()->pauseTarget(next);

        Director::getInstance()->getActionManager()->pauseTarget(next->special);
        Director::getInstance()->getScheduler()->pauseTarget(next->special);
      }

      int stage = next ? next->getStage() : 1;

      this->runAction(
        Spawn::create(
          RotateGlobalBy::create(time, Vec3(rotation ? 90 : 0, 0, 0)),
          Sequence::create(
            MoveBy::create(time / 2, Vec3(0.0, rotation ? 0.2 : 0, 0.75)),
            MoveBy::create(time / 2, Vec3(0.0, rotation ? (-0.2 - (this->getPositionY() - 1.3 - (stage * 0.8))) : 0, 0.75)),
            CallFunc::create([=] () {
              this->changeState(STATE_NORMAL);
              this->onTurn(LEFT);

              if(next)
              {
                Director::getInstance()->getActionManager()->resumeTarget(next);
                Director::getInstance()->getScheduler()->resumeTarget(next);

                Director::getInstance()->getActionManager()->resumeTarget(next->special);
                Director::getInstance()->getScheduler()->resumeTarget(next->special);
              }
            }),
            nullptr
          ),
          nullptr
        )
      );

      this->onMoveBackLeft(time);
    }
  }
}

void Character::onTurnBackRight(bool action, bool set, bool rotation, float time)
{
  if(action)
  {
    auto previous = this->plates.current;

    if(!this->isPlateLeftBlocked() && this->onTouch())
    {
      auto next = this->getBackPlateLeft(previous);

      if(next)
      {
        if(this->getAutomatecally())
        {
          if(Application->environment->character->state != STATE_NORMAL)
          {
            if(abs(Application->environment->enemy->plates.current->getIndex() - this->plates.current->getIndex()) < 3)
            {
              this->changeState(STATE_NORMAL);
              return;
            }
          }

          if(Application->environment->character->plates.current == next || Application->environment->character->plates.current == previous)
          {
            if(Application->environment->character->state == STATE_NORMAL)
            {
              Application->environment->character->plane->Node::runAction(
                Sequence::create(
                  CallFunc::create([=] () {
                  Sound->play("insane-brick-" + to_string(random(1, 3)));
                  }),
                  CallFunc::create([=] () {
                  Application->environment->character->onTurnBack(true, true, true, 0.1);
                  }),
                  DelayTime::create(0.15),
                  CallFunc::create([=] () {
                  Application->environment->character->onTurnBack(true, true, true, 0.1);
                  }),
                  DelayTime::create(0.15),
                  CallFunc::create([=] () {
                  Application->environment->character->onTurnBack(true, true, true, 0.1);
                  }),
                  DelayTime::create(0.1),
                  nullptr
                ), 7
              );
              Application->environment->enemy->plane->Node::runAction(
                DelayTime::create(0.4), 7
              );
              Application->environment->character->setColor(Color3B::WHITE);
              Application->environment->character->plane->runAction(
                Sequence::create(
                  DelayTime::create(0.1),
                  CallFunc::create([=] () {
                  Application->environment->character->setColor(Application->environment->character->color);
                  }),
                  nullptr
                )
              );
            }
            else
            {
              this->changeState(STATE_NORMAL);

              return;
            }
          }
        }
        else
        {
          this->plates.current->onUncount(true);
        }

        if(this->plates.current->getStage() != next->getStage())
        {
          this->changeState(STATE_NORMAL);
          return;
        }

        Director::getInstance()->getActionManager()->pauseTarget(next);
        Director::getInstance()->getScheduler()->pauseTarget(next);

        Director::getInstance()->getActionManager()->pauseTarget(next->special);
        Director::getInstance()->getScheduler()->pauseTarget(next->special);
      }

      int stage = next ? next->getStage() : 1;

      this->runAction(
        Spawn::create(
          RotateGlobalBy::create(time, Vec3(0, 0, rotation ? 90 : 0)),
          Sequence::create(
            MoveBy::create(time / 2, Vec3(-0.75, rotation ? 0.2 : 0, 0)),
            MoveBy::create(time / 2, Vec3(-0.75, rotation ? (-0.2 - (this->getPositionY() - 1.3 - (stage * 0.8))) : 0, 0)),
            CallFunc::create([=] () {
              this->changeState(STATE_NORMAL);
              this->onTurn(RIGHT);

              if(next)
              {
                Director::getInstance()->getActionManager()->resumeTarget(next);
                Director::getInstance()->getScheduler()->resumeTarget(next);

                Director::getInstance()->getActionManager()->resumeTarget(next->special);
                Director::getInstance()->getScheduler()->resumeTarget(next->special);
              }
            }),
            nullptr
          ),
          nullptr
        )
      );

      this->onMoveBackRight(time);
    }
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

  if(!this->manual)
  {
    if(Application->environment->insane->state->create && Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget(Application->environment->insane) <= 1)
    {
      Application->environment->insane->onRemove();
    }
  }

  return this->manual;
}

bool Character::getAutomatecally()
{
  return this->automatecally;
}

bool Character::setAutomatecally(bool automatecally)
{
  this->automatecally = manual;

  return this->automatecally;
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

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));

    int px = plate->getPositionX() / 1.5;
    int pz = plate->getPositionZ() / 1.5;

    if(px == x && pz == z && (!plate->moved || plate->blocked))
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
  auto z = this->getPositionZ();

  if(plate->behavior == Plate::DYNAMIC)
  {
    if(Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget(plate) > 1)
    {
      return this->onLandFail(turn, plate);
    }
  }

  auto color = this->color;

  if(!this->getAutomatecally())
  {
    for(Decoration* decoration : plate->getDecorations())
    {
      if(decoration->removable)
      {
        color = decoration->getColor();
      }

      if(proceed)
      {
        decoration->onPickup();

        plate->clearDecorations();
      }
    }
  }

  for(int i = 0; i < 10; i++)
  {
    Application->environment->createParticle(0, x, plate->getPositionY() + 0.4, z)->setColor(color);
  }

  this->onSound();

  if(!this->getAutomatecally())
  {
    if(!plate->counted)
    {
      plate->onCount();

      Application->counter->onCount();

      Application->environment->generator->create(true);
      Application->environment->generator->destroy(true);
    }

    if(plate->type == Plate::FINISH)
    {
      this->changeState(STATE_FINISH);

      /**
       *
       * @Missions
       * Update missions with stages.
       *
       */
      if(Application->environment->generator->bonus)
      {
        if(MissionsFactory::getInstance()->isListenen())
        {
          Application->counter->missionUpdateOnce.special_once_14++;
          Application->counter->missionUpdateProgress.special_progress_14++;

          Events::updateMissions();
        }
      }
    }
    else if(!Generators->isEpisodes())
    {
      if(!Application->environment->insane->state->create)
      {
        if(!Application->environment->generator->bonus && this->getManual())
        {
          if(this->plates.current && (Application->environment->generator->size - this->plates.current->getIndex()) > 10)
          {
            if(this->steps >= 30)
            {
              auto counter = 5;
              auto element = this->plates.current;

              while(true)
              {
                counter--;
                element = this->getPlatesNearWithDefaults(element).next();

                if(!element)
                {
                  break;
                }

                if(!element->started)
                {
                  break;
                }

                if(element->type == Plate::TRAMPOLINE || element->type == Plate::PORTAL)
                {
                  break;
                }

                if(counter < 0 && !element->getDecorations().size() && !element->special)
                {
                  Application->environment->insane->_create();
                  Application->environment->insane->setPlate(element, false);

                  element->getDecorations().push_back(Application->environment->insane);

                  break;
                }
              }
            }
          }
        }
      }
    }

    Generators->checkEpisodes(plate);
  }

  this->shadow->setPosition(this->plates.current->getStage() * 0.8);
}

void Character::onLandFail(Turn turn, Plate* plate)
{
  this->changeState(STATE_FALL);

  switch(turn)
  {
    default:
    break;
    case NONE:
    this->runAction(
      Spawn::create(
        MoveTo::create(0.1, Vec3(this->getPositionX(), 0.0, this->getPositionZ())),
        CallFunc::create([=] () {
          this->changeState(STATE_CRASH, Crash::FAIL);
        }),
        nullptr
      )
    );
    break;
    case LEFT:
    this->runAction(
      Spawn::create(
        MoveTo::create(0.1, Vec3(this->getPositionX(), 0.0, this->getPositionZ())),
        CallFunc::create([=] () {
          this->changeState(STATE_CRASH, Crash::FAIL);
        }),
        nullptr
      )
    );
    break;
    case RIGHT:
    this->runAction(
      Spawn::create(
        MoveTo::create(0.1, Vec3(this->getPositionX(), 0.0, this->getPositionZ())),
        CallFunc::create([=] () {
          this->changeState(STATE_CRASH, Crash::FAIL);
        }),
        nullptr
      )
    );
    break;
  }
}

/**
 *
 *
 *
 */
void Character::onMoveLeft(float time)
{
  if(!this->getAutomatecally())
  {
    Application->environment->plane->runAction(
      MoveBy::create(time, Vec3(0, 0, 1.5))
    );

    this->onEnvironmentMoveLeft(time);
  }
}

void Character::onMoveRight(float time)
{
  if(!this->getAutomatecally())
  {
    Application->environment->plane->runAction(
      MoveBy::create(time, Vec3(-1.5, 0, 0))
    );

    this->onEnvironmentMoveRight(time);
  }
}

/**
 *
 *
 *
 */
void Character::onMoveBackLeft(float time)
{
  if(!this->getAutomatecally())
  {
    Application->environment->plane->runAction(
      MoveBy::create(time, Vec3(0, 0, -1.5))
    );

    this->onEnvironmentMoveBackLeft(time);
  }
}

void Character::onMoveBackRight(float time)
{
  if(!this->getAutomatecally())
  {
    Application->environment->plane->runAction(
      MoveBy::create(time, Vec3(1.5, 0, 0))
    );

    this->onEnvironmentMoveBackRight(time);
  }
}

/**
 *
 *
 *
 */
void Character::onEnvironmentMoveLeft(float time)
{
}

void Character::onEnvironmentMoveRight(float time)
{
}

/**
 *
 *
 *
 */
void Character::onEnvironmentMoveBackLeft(float time)
{
}

void Character::onEnvironmentMoveBackRight(float time)
{
}

/**
 *
 *
 *
 */
void Character::onNormal()
{
  this->shadow->setVisible(true);
}

void Character::onJump()
{
  //this->plates.current = nullptr;
  this->stopAllActions();
}

void Character::onFall()
{
}

void Character::onCrash(Crash crash)
{
  if(!this->getAutomatecally())
  {
    if(this->plates.current)
    {
      this->plates.current->onUncount();
    }

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
  }

  this->plane->stopAllActions();

  switch(crash)
  {
    default:
    break;
    case FAIL:
    this->plane->runAction(
      Spawn::create(
        Sequence::create(
          ScaleTo::create(0.1, 1.0, 0.2, 1.0),
          DelayTime::create(1.0),
          CallFunc::create([=] () {
          if(!this->getAutomatecally())
          {
            Application->changeState(Game::LOSE);
          }
          }),
          nullptr
        ),
        nullptr
      )
    );

    this->shadow->setVisible(false);
    break;
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
          if(!this->getAutomatecally())
          {
            Application->changeState(Game::LOSE);
          }
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
          if(!this->getAutomatecally())
          {
            Application->changeState(Game::LOSE);
          }
        }),
        nullptr
      )
    );
    break;
    case CATCH:
    this->runAction(
      Spawn::create(
        Sequence::create(
          EaseSineIn::create(
            MoveBy::create(0.2, Vec3(this->plates.current->getDirection() ? -10 : 0, 0, this->plates.current->getDirection() ? 0 : 10))
          ),
          CallFunc::create([=] () {
          this->_destroy();
          if(!this->getAutomatecally())
          {
            Application->changeState(Game::LOSE);
          }
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
          if(!this->getAutomatecally())
          {
            Application->changeState(Game::LOSE);
          }
        }),
        nullptr
      )
    );
    break;
    case COPTER:
    if(!this->getAutomatecally())
    {
    this->changeState(STATE_COPTER);
    }
    break;
  }

  switch(crash)
  {
    default:
    break;
    case FAIL:
    case SPIKES:
    Sound->play("character-destroy-smash");
    break;
    case DOWN:
    Sound->play("character-destroy-smash");
    break;
    case CATCH:
    if(!this->getAutomatecally())
    {
      Sound->play("character-destroy-catch");
    }
    break;
    case GATE:
    Sound->play("character-destroy-smash");
    break;
    case COPTER:
    break;
  }

  if(!this->getAutomatecally())
  {
    switch(crash)
    {
      case CATCH:
      Storage::set("application.plates.index." + s(Application->environment->parameters.stage), Application->environment->platesTimeIndex + 1);
      case FAIL:
      case SPIKES:
      case DOWN:
      case GATE:
      Screenshot::save([&] (bool a, string texture)
      {
        Application->runAction(
          Sequence::create(
          DelayTime::create(1.5),
          CallFunc::create([=] () {
          switch(Application->state)
          {
            default:
            break;
            case Game::FINISH:
            case Game::GAME:
            Application->capture->screenshot(texture);
            break;
          }
          }),
          nullptr
          )
        );
      });
      break;
      case COPTER:
      break;
      case UNDEFINED:
      break;
    }
  }
}

void Character::onHit()
{
  this->plates.current->clearDecorations();

  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  //this->setColor(Color3B(255, 0, 0));

  for(int i = 0; i < 10 * 2; i++)
  {
    Application->environment->createParticle(0, x, y, z)->setColor(this->getColor());
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
  int stage = this->plates.current->getStage();

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
        DelayTime::create(0.35),
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
        CallFunc::create([=] () {
          Sound->play("character-finish-1");
        }),
        EaseSineOut::create(
          MoveBy::create(0.25, Vec3(0, 3, 0))
        ),
        EaseSineOut::create(
          MoveBy::create(0.35, Vec3(0, -1, 0))
        ),
        CallFunc::create([=] () {
          Sound->play("character-finish-2");
        }),
        EaseSineOut::create(
          MoveBy::create(0.5, Vec3(0, 18, 0))
        ),
        DelayTime::create(0.5),
        EaseSineIn::create(
          MoveBy::create(0.5, Vec3(0, -20 - (stage * 0.8), 0))
        ),
        CallFunc::create([=] () {
          Application->changeState(Game::GAME);

          Application->environment->runAction(
            Shake::create(0.5, 0.2)
          );

          this->changeState(STATE_NORMAL);
          this->onLandSuccessful(NONE, this->plates.current);

          Sound->play("landing-" + patch::to_string(random(1, 4)));

          if(Application->environment->generator->bonus)
          {
            Music->speed(1.3);
          }
          else
          {
            Music->speed(1.0);
          }
        }),
        nullptr
      ),
      nullptr
    )
  );

  Application->s->runAction(
    Sequence::create(
      DelayTime::create(1.1),
      FadeIn::create(0.5),
      CallFunc::create([=] () {
        Application->environment->reset();
      }),
      FadeOut::create(0.5),
      nullptr
    )
  );
}

void Character::onInsane()
{
  this->onInsaneStart();
}

/**
 *
 *
 *
 */
void Character::onInsaneStart()
{
  auto x = Application->cameras.d->getRotation3D().x;
  auto y = Application->cameras.d->getRotation3D().y;
  auto z = Application->cameras.d->getRotation3D().z;

  auto px = Application->cameras.d->getPosition3D().x;
  auto py = Application->cameras.d->getPosition3D().y;
  auto pz = Application->cameras.d->getPosition3D().z;

  this->stopAllActions();

  this->plane->stopAllActions();
  this->plane->setScale(1.0);

  Application->cameras.d->stopAllActions();
  Application->cameras.d->runAction(
    Spawn::create(
      ScaleTo::create(2.0, 0.6),
      MoveTo::create(2.0, Vec3(px, py - 20, pz)),
      RotateTo::create(2.0, Vec3(x + 15, y - 1.8, z)),
      nullptr
    )
  );

  this->setManual(false);

  this->insaneDirection = this->plates.current->getDirection();
  this->insanePlate = this->plates.current;
  this->insaneData = 1000;
  this->insaneCount = 5;
  this->insaneSpeed = 0.1;

  if(this->insaneDirection)
  {
    if(!this->getPlateLeft())
    {
      this->insaneDirection = !this->insaneDirection;
    }
  }
  else
  {
    if(!this->getPlateRight())
    {
      this->insaneDirection = !this->insaneDirection;
    }
  }

  if(this->insaneDirection)
  {
    this->onMoveLeft();
  }
  else
  {
    this->onMoveRight();
  }

  this->runAction(
    Spawn::create(
      MoveBy::create(0.1, Vec3(this->insaneDirection ? 0 : 1.5, -0.8 * (this->plates.current->getStage() + 1), this->insaneDirection ? -1.5 : 0)),
      RotateGlobalBy::create(0.1, Vec3(this->insaneDirection ? -90.0 : 0, 0, this->insaneDirection ? 0 : -90)),
      nullptr
    )
  );

 this->runAction(
    Sequence::create(
      DelayTime::create(0.1),
      CallFunc::create([=] () {
      this->onInsaneUpdate();
      }),
      nullptr
    )
  );

  Application->i->_create();
  Application->i->setOpacity(0);
  Application->i->setScale(1.5);
  Application->i->runAction(
    Spawn::create(
      FadeTo::create(2.5, 200),
      ScaleTo::create(2.5, 1.0),
      nullptr
    )
  );

  Music->speed(1.3);
}

void Character::onInsaneFinish()
{
  this->stopAllActions();

  auto element = this->getPlatesNear(this->insanePlate).next();

  this->runAction(
    Spawn::create(
      RotateGlobalBy::create(0.1, Vec3(this->insaneDirection ? 0.0 : -90.0, 0, this->insaneDirection ? -90.0 : 0.0)),
      Sequence::create(
        MoveBy::create(0.1, Vec3(this->insaneDirection ? 1.5 : 0.0, (element->getStage() + 1) * 0.8, this->insaneDirection ? 0 : -1.5)),
        CallFunc::create([=] () {
        if(this->plates.current->type != Plate::FINISH)
        {
          this->plates.current = this->getPlatesNear(this->insanePlate).next();
        }

        this->changeState(STATE_NORMAL);
        this->onLandSuccessful(NONE, this->plates.current, true);

        this->setRotation3D(Vec3(0.0, 0.0, 0.0));
        }),
        nullptr
      ),
      nullptr
    )
  );

  Application->cameras.d->stopAllActions();
  Application->cameras.d->runAction(
    Spawn::create(
      ScaleTo::create(0.5, 1.0),
      MoveTo::create(0.5, Vec3(Application->startCameraX, Application->startCameraY, Application->startCameraZ)),
      RotateTo::create(0.5, Vec3(Application->startCameraRotationX, Application->startCameraRotationY, Application->startCameraRotationZ)),
      nullptr
    )
  );

  Application->i->runAction(
    Sequence::create(
      FadeOut::create(0.5),
      CallFunc::create([=] () {
      Application->i->_destroy();
      }),
      nullptr
    )
  );

  this->steps = 0;
  this->sound = 1;

  this->setManual(true);

  Music->speed(1.0);
}

void Character::onInsaneUpdate()
{
  switch(--this->insaneData)
  {
    case 0:
    this->insaneCount--;
    this->insaneDirection = !this->insaneDirection;
    break;
  }

  if(this->insaneDirection)
  {
    this->onInsaneRight();
  }
  else
  {
    this->onInsaneLeft();
  }

  this->insanePlate = this->getPlatesNear(this->insanePlate).next();
  this->insanePlate->onCount();

  this->onSound();

  Application->counter->onCount();

  Application->environment->generator->create(true);

  if(!this->insanePlate->getStage())
  {
    switch(this->insanePlate->type)
    {
      default:
      break;
      case Plate::SAW:
      this->insanePlate->setVisibility(false);

                Sound->play("insane-brick-" + to_string(random(1, 3)));
                /////
                  for(int i = 0; i < 10; i++)
    {
      auto particle = Application->environment->createParticle(1, this->insanePlate->getPositionX(), this->insanePlate->getPositionY() - 0.5, this->insanePlate->getPositionZ());

      particle->setColor(Environment::TEXTURES_COLORS[Application->environment->parameters.texture - 2]);
    }
      break;
    }
  }

  this->insaneSpeed = max(this->insaneSpeed - 0.001, 0.075);
}

void Character::onInsaneRight()
{
  this->runAction(
    Spawn::create(
      RotateGlobalBy::create(this->insaneSpeed, Vec3(0, 0, -90)),
      Sequence::create(
        CallFunc::create([=] () {
        if(auto plate = this->getPlateLeftWithCoordinates())
        {
          if(plate)
          {
            if((this->insaneCount > 0 || plate->type == Plate::SPIKES || plate->type == Plate::TRAP || plate->type == Plate::SAW || plate->type == Plate::DOWN || plate->behavior == Plate::DYNAMIC) && plate->type != Plate::FINISH)
            {
              if(plate->getStage() == 0)
              {
              plate->setVisibility(false);

              Sound->play("insane-brick-" + to_string(random(1, 3)));
              /////
                for(int i = 0; i < 10; i++)
  {
    auto particle = Application->environment->createParticle(1, plate->getPositionX(), plate->getPositionY() - 0.5, plate->getPositionZ());

      particle->setColor(Environment::TEXTURES_COLORS[Application->environment->parameters.texture - 2]);
  }
  }
            }
            else
            {
              this->onInsaneFinish();
            }
          }
        }
        }),
        MoveBy::create(this->insaneSpeed / 2, Vec3(0.75, 0.0, 0)),
        MoveBy::create(this->insaneSpeed / 2, Vec3(0.75, 0.0, 0)),
        CallFunc::create([=] () {
        auto plate = this->getPlateRightWithCoordinates();

        if(plate && plate->type == Plate::FINISH)
        {
        this->insanePlate = this->getPlatesNear(this->insanePlate).next();
  this->insanePlate->onCount();

  this->onSound();

  Application->counter->onCount();


          this->insaneDirection = !this->insaneDirection;
          this->plates.current = plate;
          this->onInsaneFinish();

          

  if(this->insaneDirection)
  {
    this->onInsaneRight();
  }
  else
  {
    this->onInsaneLeft();
  }
        }
        else
        {
          if(this->getPlateRightWithCoordinates())
          {
            this->insaneData = 2;
          }

          this->onInsaneUpdate();
        }
        }),
        nullptr
      ),
      nullptr
    )
  );

  this->onMoveRight(this->insaneSpeed);
}

void Character::onInsaneLeft()
{
  this->runAction(
    Spawn::create(
      RotateGlobalBy::create(this->insaneSpeed, Vec3(-90, 0, 0)),
      Sequence::create(
        CallFunc::create([=] () {
        if(auto plate = this->getPlateRightWithCoordinates())
        {
          if(plate)
          {
            if((this->insaneCount > 0 || plate->type == Plate::SPIKES || plate->type == Plate::TRAP || plate->type == Plate::SAW || plate->type == Plate::DOWN || plate->behavior == Plate::DYNAMIC) && plate->type != Plate::FINISH)
            {
              if(plate->getStage() == 0)
              {
              plate->setVisibility(false);

              Sound->play("insane-brick-" + to_string(random(1, 3)));
              /////
                for(int i = 0; i < 10; i++)
  {
    auto particle = Application->environment->createParticle(1, plate->getPositionX(), plate->getPositionY() - 0.5, plate->getPositionZ());

      particle->setColor(Environment::TEXTURES_COLORS[Application->environment->parameters.texture - 2]);
  }
  }
            }
            else
            {
              this->onInsaneFinish();
            }
          }
        }
        }),
        MoveBy::create(this->insaneSpeed / 2, Vec3(0.0, 0.0, -0.75)),
        MoveBy::create(this->insaneSpeed / 2, Vec3(0.0, 0.0, -0.75)),
        CallFunc::create([=] () {
          auto plate = this->getPlateLeftWithCoordinates();

        if(plate && plate->type == Plate::FINISH)
        {
        this->insanePlate = this->getPlatesNear(this->insanePlate).next();
  this->insanePlate->onCount();

  this->onSound();

  Application->counter->onCount();


          this->insaneDirection = !this->insaneDirection;
          this->plates.current = plate;
          this->onInsaneFinish();
          

  if(this->insaneDirection)
  {
    this->onInsaneRight();
  }
  else
  {
    this->onInsaneLeft();
  }
        }
        else
        {
          if(this->getPlateLeftWithCoordinates())
          {
            this->insaneData = 2;
          }

          this->onInsaneUpdate();
        }
        }),
        nullptr
      ),
      nullptr
    )
  );

  this->onMoveLeft(this->insaneSpeed);
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
  int z = (current ? current->getPositionZ() : this->plates.current->getPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = plate->getPosition3D();

    int px = position.x / 1.5;
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
  int z = (current ? current->getPositionZ() : this->plates.current->getPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = plate->getPosition3D();

    int px = position.x / 1.5;
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

Plate* Character::getBackPlateRight(Plate* current)
{
  if(!this->plates.current)
  {
    if(!current)
    {
      return nullptr;
    }
  }

  int x = (current ? current->getPositionX() : this->plates.current->getPositionX()) / 1.5;
  int z = (current ? current->getPositionZ() : this->plates.current->getPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = plate->getPosition3D();

    int px = position.x / 1.5;
    int pz = position.z / 1.5;

    if(px == x && pz == z + 1 && !(px == x && pz == z))
    {
      plate->position[Plate::LEFT] = true;
      plate->position[Plate::RIGHT] = false;

      return plate;
    }
  }

  return this->getPlateRightWithDefaults(current);
}

Plate* Character::getBackPlateLeft(Plate* current)
{
  if(!this->plates.current)
  {
    if(!current)
    {
      return nullptr;
    }
  }

  int x = (current ? current->getPositionX() : this->plates.current->getPositionX()) / 1.5;
  int z = (current ? current->getPositionZ() : this->plates.current->getPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = plate->getPosition3D();

    int px = position.x / 1.5;
    int pz = position.z / 1.5;

    if(px == x - 1 && pz == z && !(px == x && pz == z))
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
  int z = (current ? current->getStartPositionZ() : this->plates.current->getStartPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
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
  int z = (current ? current->getStartPositionZ() : this->plates.current->getStartPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
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


Plate* Character::getBackPlateRightWithDefaults(Plate* current)
{
  if(!this->plates.current)
  {
    if(!current)
    {
      return nullptr;
    }
  }

  int x = (current ? current->getStartPositionX() : this->plates.current->getStartPositionX()) / 1.5;
  int z = (current ? current->getStartPositionZ() : this->plates.current->getStartPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
    int pz = position.z / 1.5;

    if(px == x && pz == z + 1 && !(px == x && pz == z))
    {
      plate->position[Plate::LEFT] = true;
      plate->position[Plate::RIGHT] = false;

      return plate;
    }
  }

  return nullptr;
}

Plate* Character::getBackPlateLeftWithDefaults(Plate* current)
{
  if(!this->plates.current)
  {
    if(!current)
    {
      return nullptr;
    }
  }

  int x = (current ? current->getStartPositionX() : this->plates.current->getStartPositionX()) / 1.5;
  int z = (current ? current->getStartPositionZ() : this->plates.current->getStartPositionZ()) / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
    int pz = position.z / 1.5;

    if(px == x - 1 && pz == z && !(px == x && pz == z))
    {
      plate->position[Plate::LEFT] = false;
      plate->position[Plate::RIGHT] = true;

      return plate;
    }
  }

  return nullptr;
}

Plate* Character::getPlateWithCoordinates()
{
  int x = this->getPositionX() / 1.5;
  int z = this->getPositionZ() / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
    int pz = position.z / 1.5;

    if(px == x && pz == z)
    {
      plate->position[Plate::LEFT] = true;
      plate->position[Plate::RIGHT] = false;

      return plate;
    }
  }

  return nullptr;
}

Plate* Character::getPlateRightWithCoordinates()
{
  int x = this->getPositionX() / 1.5;
  int z = this->getPositionZ() / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
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

Plate* Character::getPlateLeftWithCoordinates()
{
  int x = this->getPositionX() / 1.5;
  int z = this->getPositionZ() / 1.5;

  for(int i = 0; i < Application->environment->plates.normal->count; i++)
  {
    auto plate = static_cast<Plate*>(Application->environment->plates.normal->element(i));
    auto position = Vec3(plate->getStartPositionX(), plate->getStartPositionY(), plate->getStartPositionZ());

    int px = position.x / 1.5;
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

Character::Nears Character::getBackPlatesNear(Plate* current)
{
  Nears nears;

  nears.plates[Plate::LEFT] = this->getBackPlateLeft(current);
  nears.plates[Plate::RIGHT] = this->getBackPlateRight(current);

  return nears;
}

Character::Nears Character::getBackPlatesNearWithDefaults(Plate* current)
{
  Nears nears;

  nears.plates[Plate::LEFT] = this->getBackPlateLeftWithDefaults(current);
  nears.plates[Plate::RIGHT] = this->getBackPlateRightWithDefaults(current);

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
      this->onCrash(crash);
      break;
      case STATE_HIT:
      this->onHit();
      break;
      case STATE_COPTER:
      this->onCopter();
      break;
      case STATE_FINISH:
      this->onFinish();
      break;
      case STATE_INSANE:
      this->onInsane();
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
  if(!this->getAutomatecally())
  {
    if(Application->environment->enemy && Application->environment->enemy->Node::state->create)
    {
      if(Application->environment->enemy->plates.current == this->plates.current)
      {
        return;
      }
    }
  }

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
          this->changeState(STATE_CRASH, decoration->status());
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

void Character::updateFinish(float time)
{
}

void Character::updateCopter(float time)
{
  this->turns -= 0.01;

  Application->environment->characterAction->setScaleX(min(1.0f, max(0.0f, this->turns / STATE_COPTER_TURNS)));
}

void Character::updateInsane(float time)
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
    case STATE_COPTER:
    this->updateCopter(time);
    break;
    case STATE_FINISH:
    this->updateFinish(time);
    break;
    case STATE_INSANE:
    this->updateInsane(time);
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
  if(this->getManual())
  {
    this->soundTimeElapsed += time;

    if(this->soundTimeElapsed >= this->soundTime)
    {
      this->steps = 0;
      this->sound = 1;

      if(Application->environment->insane->state->create && Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget(Application->environment->insane) <= 1)
      {
        Application->environment->insane->onRemove();
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
