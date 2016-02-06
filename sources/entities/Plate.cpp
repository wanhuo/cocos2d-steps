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
Plate::Plate()
: Replace("plate.obj")
{
}

Plate::~Plate()
{
}

/**
 *
 *
 *
 */
void Plate::onCreate()
{
  Replace::onCreate();

  /**
   *
   *
   *
   */
  //this->position = true;
  this->behavior = STATIC;

  this->setTexture("plate-texture-state-1.png");

  this->setType(NORMAL);

  this->runAction(
    RepeatForever::create(
      Sequence::create(
        DelayTime::create(random(1.0, 5.0)),
        CallFunc::create([=] () {
          Application->environment->createRipple(this->getPositionX(), this->getPositionZ(), 1.25);
        }),
        nullptr
      )
    )
  );
}

void Plate::onDestroy(bool action)
{
  Replace::onDestroy(action);

  /**
   *
   *
   *
   */
  this->clearDecoration(true);
}

/**
 *
 *
 *
 */
void Plate::onCount()
{
  if(this->special)
  {
    switch(this->type)
    {
      case SPIKES:
      this->special->setTexture("spike-plate-texture-2.png");
      break;
    }
  }

  switch(this->type)
  {
    default:
    this->setTexture("plate-texture-state-2.png");
    break;
    case MOVED1:
    this->setTexture("plate-texture-state-2-moved-1.png");
    break;
    case MOVED2:
    this->setTexture("plate-texture-state-2-moved-2.png");
    break;
    case MOVED3:
    this->setTexture("plate-texture-state-2-moved-3.png");
    break;
    case MOVED4:
    this->setTexture("plate-texture-state-2-moved-4.png");
    break;
  }
}

/**
 *
 *
 *
 */
float Plate::getStartPositionX()
{
  return this->startPositionX;
}

float Plate::getStartPositionY()
{
  return this->startPositionY;
}

float Plate::getStartPositionZ()
{
  return this->startPositionZ;
}

void Plate::setStartPositionX(float x)
{
  this->startPositionX = x;
}

void Plate::setStartPositionY(float y)
{
  this->startPositionY = y;
}

void Plate::setStartPositionZ(float z)
{
  this->startPositionZ = z;
}

/**
 *
 *
 *
 */
void Plate::setType(Type type, bool animated)
{
  this->type = type;

  switch(this->type)
  {
    case SPIKES:
    this->decoration = static_cast<Decoration*>(Application->environment->spikes->_create());
    this->decoration->setPlate(this, animated);

    this->setVisible(false);

    this->special = static_cast<Entity3D*>(Application->environment->plates_spikes->_create());
    this->special->setTexture("spike-plate-texture.png");
    break;
    case DIAMOND:
    this->decoration = static_cast<Decoration*>(Application->environment->diamonds->_create());
    this->decoration->setPlate(this, animated);
    break;
    case CRYSTAL:
    this->decoration = static_cast<Decoration*>(Application->environment->crystals->_create());
    this->decoration->setPlate(this, animated);
    break;
    case ENERGY:
    this->decoration = static_cast<Decoration*>(Application->environment->energies->_create());
    this->decoration->setPlate(this, animated);
    break;
    case STAR:
    this->decoration = static_cast<Decoration*>(Application->environment->stars->_create());
    this->decoration->setPlate(this, animated);
    break;
    case HEART:
    this->decoration = static_cast<Decoration*>(Application->environment->hearts->_create());
    this->decoration->setPlate(this, animated);
    break;

    /**
     *
     * Complex types.
     *
     */
    case MOVED1:
    this->stopAllActions();
    this->setTexture("plate-texture-state-1-moved-1.png");
    this->behavior = DYNAMIC;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0, -1.5))
            );

            this->runAction(action->clone());
          //this->position=false;

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0, 1.5))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.15),
                CallFunc::create([=] () {
                  //this->position = true;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0, 1.5))
            );

            this->runAction(action->clone());
          //this->position = false;

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0, -1.5))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.15),
                CallFunc::create([=] () {
                  //this->position = true;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          nullptr
        )
      )
    );
    break;


    case MOVED2:
    this->stopAllActions();
    this->setTexture("plate-texture-state-1-moved-2.png");
    this->behavior = DYNAMIC;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(-1.5, 0, 0))
            );

            this->runAction(action->clone());
          //this->position = false;

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.15),
                CallFunc::create([=] () {
                  //this->position = true;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(1.5, 0, 0))
            );

            this->runAction(action->clone());
          //this->position=false;

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(-1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.15),
                CallFunc::create([=] () {
                  //this->position = true;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          nullptr
        )
      )
    );
    break;


    case MOVED3:
    this->stopAllActions();
    this->setTexture("plate-texture-state-1-moved-3.png");
    this->behavior = DYNAMIC;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0, 1.5))
            );

            this->runAction(action->clone());
          //this->position = false;

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0, -1.5))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.15),
                CallFunc::create([=] () {
                  //this->position = true;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          nullptr
        )
      )
    );
    break;


    case MOVED4:
    this->stopAllActions();
    this->setTexture("plate-texture-state-1-moved-4.png");
    this->behavior = DYNAMIC;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(-1.5, 0, 0))
            );

            this->runAction(action->clone());
          //this->position=false;

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.15),
                CallFunc::create([=] () {
                  //this->position = true;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this && Application->environment->character->numberOfRunningActions() < 1)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          nullptr
        )
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
void Plate::clearDecoration(bool force, bool animated)
{
  if(this->decoration)
  {
    if(this->decoration->removable || force || animated)
    {
      this->decoration->remove(force);
      this->decoration = nullptr;
    }
  }
}

/**
 *
 *
 *
 */
Plate* Plate::deepCopy()
{
  return new Plate;
}
