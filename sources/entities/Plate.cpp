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
: Cube("plate.obj")
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
  Cube::onCreate();

  /**
   *
   *
   *
   */
  this->position = true;
  this->moved = false;

  this->setTexture("plate-texture.png");

  this->setType(TYPE_NORMAL);

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
  Cube::onDestroy(action);

  /**
   *
   *
   *
   */
  this->clearDecoration(true);

  if(this->special)
  {
    this->special->_destroy();
    this->special = nullptr;
  }
}

/**
 *
 *
 *
 */
void Plate::onCount()
{
  this->setTexture("plate-texture-2.png");

  if(this->special)
  {
    switch(this->type)
    {
      case TYPE_SPIKES:
      this->special->setTexture("spike-plate-texture-2.png");
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Plate::setOpacity(GLubyte opacity)
{
  Cube::setOpacity(opacity);

  if(this->special)
  {
    this->special->setOpacity(opacity);
  }
}

void Plate::setPositionX(float x)
{
  Cube::setPositionX(x);

  if(this->special)
  {
    this->special->setPositionX(x);
  }
}

void Plate::setPositionY(float y)
{
  Cube::setPositionY(y);

  if(this->special)
  {
    this->special->setPositionY(y);
  }
}

void Plate::setPositionZ(float z)
{
  Cube::setPositionZ(z);

  if(this->special)
  {
    this->special->setPositionZ(z);
  }
}

void Plate::setPosition3D(Vec3 position)
{
  Cube::setPosition3D(position);

  if(this->special)
  {
    this->special->setPosition3D(position);
  }
}

Action* Plate::runAction(Action* action)
{
  Cube::runAction(action);

  if(this->special)
  {
    this->special->runAction(action->clone());
  }
}

/**
 *
 *
 *
 */
void Plate::setType(int type, bool animated)
{
  this->type = type;

  switch(this->type)
  {
    case TYPE_SPIKES:
    this->decoration = static_cast<Decoration*>(Application->environment->spikes->_create());
    this->decoration->setPlate(this, animated);

    this->setVisible(false);

    this->special = static_cast<Entity3D*>(Application->environment->plates_spikes->_create());
    this->special->setTexture("spike-plate-texture.png");
    break;
    case TYPE_DIAMOND:
    this->decoration = static_cast<Decoration*>(Application->environment->diamonds->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_CRYSTAL:
    this->decoration = static_cast<Decoration*>(Application->environment->crystals->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_ENERGY:
    this->decoration = static_cast<Decoration*>(Application->environment->energies->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_STAR:
    this->decoration = static_cast<Decoration*>(Application->environment->stars->_create());
    this->decoration->setPlate(this, animated);
    break;
    case TYPE_HEART:
    this->decoration = static_cast<Decoration*>(Application->environment->hearts->_create());
    this->decoration->setPlate(this, animated);
    break;

    /**
     *
     * Complex types.
     *
     */
    case TYPE_MOVED_1:
    this->setTexture("plate-texture-state-1-moved-1.png");
    this->moved = true;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.05, Vec3(0, 0, -1.5))
            );

            this->runAction(action->clone());this->position=false;

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
              MoveBy::create(0.05, Vec3(0, 0, 1.5))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.05),
                CallFunc::create([=] () {
                  this->position = true;
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
              MoveBy::create(0.05, Vec3(0, 0, 1.5))
            );

            this->runAction(action->clone());this->position = false;

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
              MoveBy::create(0.05, Vec3(0, 0, -1.5))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.05),
                CallFunc::create([=] () {
                  this->position = true;
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


    case TYPE_MOVED_2:
    this->moved = true;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.05, Vec3(-1.5, 0, 0))
            );

            this->runAction(action->clone());this->position = false;

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
              MoveBy::create(0.05, Vec3(1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.05),
                CallFunc::create([=] () {
                  this->position = true;
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
              MoveBy::create(0.05, Vec3(1.5, 0, 0))
            );

            this->runAction(action->clone());this->position=false;

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
              MoveBy::create(0.05, Vec3(-1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.05),
                CallFunc::create([=] () {
                  this->position = true;
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


    case TYPE_MOVED_3:
    this->moved = true;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.05, Vec3(0, 0, 1.5))
            );

            this->runAction(action->clone());this->position = false;

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
              MoveBy::create(0.05, Vec3(0, 0, -1.5))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.05),
                CallFunc::create([=] () {
                  this->position = true;
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


    case TYPE_MOVED_4:
    this->moved = true;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.05, Vec3(-1.5, 0, 0))
            );

            this->runAction(action->clone());this->position=false;

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
              MoveBy::create(0.05, Vec3(1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.05),
                CallFunc::create([=] () {
                  this->position = true;
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
void Plate::update(float time)
{
  Cube::update(time);
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
