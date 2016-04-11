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
  this->behavior = STATIC;
  this->moved = false;
  this->avoid = false;
  this->blocked = false;

  this->setRotation3D(Vec3(0, 0, 0));
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
void Plate::onRemove()
{
  auto character = Application->environment->character;

  if(character->plates.current)
  {
    if(character->plates.current->getIndex() == this->getIndex())
    {
      Application->environment->character->changeState(Character::CRASH, Character::Crash::CATCH);
    }
  }

  this->setIndex(10000);
  this->stopAllActions();
}

void Plate::onCount()
{
  if(this->special)
  {
    switch(this->type)
    {
      case SPIKES:
      this->special->setTexture("plate-texture-state-2-spike.png");
      break;
      case UP:
      this->special->setTexture("plate-texture-state-2-up.png");
      break;
    }
  }

  switch(this->type)
  {
    default:
    this->setTexture("plate-texture-state-2.png");
    break;
    case BEST:
    this->setTexture("plate-texture-state-2-best.png");
    break;
    /*case MOVED1:
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
    break;*/
  }
}

/**
 *
 *
 *
 */
int Plate::getIndex()
{
  return this->index;
}

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

void Plate::setIndex(int index)
{
  this->index = index;
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
    case BEST:
    this->setTexture("plate-texture-state-1-best.png");
    break;
    case SPIKES:
    this->decoration = static_cast<Decoration*>(Application->environment->spikes->_create());
    this->decoration->setPlate(this, animated);

    this->setVisible(false);

    this->special = static_cast<Entity3D*>(Application->environment->plates_spikes->_create());
    this->special->setTexture("plate-texture-state-1-spike.png");
    break;
    case UP:
    this->decoration = static_cast<Decoration*>(Application->environment->ups->_create());
    this->decoration->setPlate(this, animated);

    this->setVisible(false);

    this->special = static_cast<Entity3D*>(Application->environment->plates_up->_create());
    this->special->setTexture("plate-texture-state-1-up.png");
    break;
    case DOWN:
    this->decoration = static_cast<Decoration*>(Application->environment->downs->_create());
    this->decoration->setPlate(this, animated);
    break;
    case CANNON:
    this->decoration = static_cast<Decoration*>(Application->environment->cannons->_create());
    this->decoration->setPlate(this, animated);
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
    //this->setTexture("plate-texture-state-1-moved-1.png");
    this->behavior = DYNAMIC;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0, -1.5))
            );

            this->runAction(action->clone());
            this->moved = true;

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
                  this->moved = false;
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
            this->moved = true;

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
                  this->moved = false;
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
    //this->setTexture("plate-texture-state-1-moved-2.png");
    this->behavior = DYNAMIC;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(-1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->moved = true;

            if(Application->environment->character->plates.current == this)
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
                  this->moved = false;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this)
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
            this->moved = true;

            if(Application->environment->character->plates.current == this)
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
                  this->moved = false;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this)
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
    //this->setTexture("plate-texture-state-1-moved-3.png");
    this->behavior = DYNAMIC;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0, 1.5))
            );

            this->runAction(action->clone());
            this->moved = true;

            if(Application->environment->character->plates.current == this)
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
                  this->moved = false;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this)
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
    //this->setTexture("plate-texture-state-1-moved-4.png");
    this->behavior = DYNAMIC;
    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(-1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->moved = true;

            if(Application->environment->character->plates.current == this)
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
                  this->moved = false;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this)
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


    case MOVED5:
    auto test = new Entity3D(this->getParent(), true);
    test->setRotation3D(Vec3(0, (this->direction ? 2 : 90), 0));
    test->setPosition3D(this->getPosition3D());

    this->decoration = new Decoration("plate-up.obj", test);
    this->decoration->setPlate(this, animated);
    this->decoration->_create()->setColor(Color3B(255.0, 60.0, 60.0));
    this->decoration->setPosition3D(Vec3(0, 0, 0));

    this->stopAllActions();

    this->behavior = DYNAMIC;
    this->avoid = true;

    this->runAction(
      RepeatForever::create(
        Sequence::create(
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, 0.8, 0))
            );

            this->runAction(action->clone());
            this->moved = true;
            this->blocked = true;

            if(Application->environment->character->plates.current == this)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }

            this->decoration->runAction(
              EaseSineInOut::create(
                RotateBy::create(0.3, Vec3(0, 0,  90))
              )
            );
          }),
          DelayTime::create(0.2),
          CallFunc::create([=] () {
            this->moved = false;
          }),
          DelayTime::create(0.4),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(0, -0.8, 0))
            );

            this->moved = true;

            this->runAction(action->clone());
            this->runAction(
              Sequence::create(
                DelayTime::create(0.15),
                CallFunc::create([=] () {
                  this->moved = false;
                  this->blocked = false;
                }),
                nullptr
              )
            );

            if(Application->environment->character->plates.current == this)
            {
              Application->environment->character->runAction(action->clone());
            }

            if(this->decoration)
            {
              this->decoration->runAction(action->clone());
            }

            this->decoration->runAction(
              EaseSineInOut::create(
                RotateBy::create(0.3, Vec3(0, 0,  -90))
              )
            );
          }),
          DelayTime::create(0.6),
          nullptr
        )
      )
    );
    break;
  }

  if(this->decoration)
  {
    this->decoration->setRotation3D(Vec3(0, 0, 0));
  }

  if(this->special)
  {
    this->special->setRotation3D(Vec3(0, 0, 0));
  }
}

/**
 *
 *
 *
 */
void Plate::remove()
{
  this->onRemove();

  this->runAction(
    Spawn::create(
      RotateBy::create(0.3, Vec3((this->direction ? 0 : 20), 0, (this->direction ? -20 : 0))),
      Sequence::create(
        EaseSineOut::create(
          MoveBy::create(0.5, Vec3(0, -1, 0))
        ),
        CallFunc::create(CC_CALLBACK_0(Node::_destroy, this, true)),
        nullptr
      ),
      nullptr
    )
  );

  if(this->decoration)
  {
    if(this->decoration->shadow)
    {
      this->decoration->shadow->_destroy();
    }

    this->decoration->runAction(
    Spawn::create(
      RotateBy::create(0.3, Vec3((this->direction ? 0 : 20), 0, (this->direction ? -20 : 0))),
      Sequence::create(
        EaseSineOut::create(
          MoveBy::create(0.5, Vec3(0, -1, 0))
        ),
        nullptr
      ),
      nullptr
      )
    );
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
