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
  this->decorations = *new vector<Decoration*>();
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
  this->moved = false;
  this->avoid = false;
  this->blocked = false;

  this->behavior = STATIC;

  this->setScale(1.0);

  this->setRotation3D(Vec3(0, 0, 0));
  this->setTexture("plate-texture-state-1.png");

  this->setType(NORMAL);
}

void Plate::onDestroy(bool action)
{
  Cube::onDestroy(action);

  /**
   *
   *
   *
   */
  this->clearDecorations();
  this->clearSpecial();
}

/**
 *
 *
 *
 */
void Plate::onAdd()
{
}

void Plate::onRemove(bool complete)
{
  if(complete)
  {
    auto character = Application->environment->character;

    if(character->plates.current)
    {
      if(character->plates.current->getIndex() == this->getIndex())
      {
        Application->environment->character->changeState(Character::CRASH, Character::Crash::CATCH);
      }
    }
  }

  this->setIndex(10000);

  this->stopAllActions();
}

void Plate::onCount()
{
  switch(this->type)
  {
    default:
    this->setTexture("plate-texture-state-2.png");
    break;
    case BEST:
    this->setTexture("plate-texture-state-2-best.png");
    break;
    case FINISH:
    this->setTexture("plate-texture-state-2-finish.png");
    break;
    case BONUS:
    this->setTexture("plate-texture-state-2-bonus.png");
    break;
  }

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
      case SAW:
      this->special->setTexture("plate-texture-state-2-saw.png");
      break;
      case COPTER:
      this->special->setTexture("plate-texture-state-2-copter.png");
      break;
    }
  }
}

/**
 *
 *
 *
 */
vector<Decoration*> &Plate::getDecorations()
{
  if(this->special)
  {
    if(this->special->getDecorations().size())
    {
      return this->special->getDecorations();
    }
  }

  return this->decorations;
}

int Plate::getIndex()
{
  return this->index;
}

bool Plate::getDirection()
{
  return this->direction;
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

void Plate::setDirection(bool direction)
{
  this->direction = direction;
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
    case START:
    {
      this->setTexture("plate-texture-state-2.png");

      auto decoration = static_cast<Decoration*>(Application->environment->starts->_create());
      decoration->setPlate(this, animated);
      decoration->setRotation3D(Vec3(0, 0, 0));

      this->getDecorations().push_back(decoration);
    }
    break;
    case FINISH:
    {
      this->setTexture("plate-texture-state-1-finish.png");
    }
    break;
    case BEST:
    {
      this->setTexture("plate-texture-state-1-best.png");
    }
    break;
    case SPIKES:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->spikes->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);

      this->setVisible(false);

      this->special = static_cast<Special*>(Application->environment->plates_spikes->_create());
      this->special->setTexture("plate-texture-state-1-spike.png");
    }
    break;
    case UP:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->ups->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);

      this->setVisible(false);

      this->special = static_cast<Special*>(Application->environment->plates_up->_create());
      this->special->setTexture("plate-texture-state-1-up.png");
    }
    break;
    case SAW:
    {
      this->setVisible(false);

      this->special = static_cast<TypeSaw*>(Application->environment->plates_saw->_create());
      this->special->setPlate(this);
    }
    break;
    case GATE:
    {
      this->special = static_cast<TypeGate*>(Application->environment->plates_gate->_create());
      this->special->setPlate(this);
    }
    break;
    case COPTER:
    {
      this->setVisible(false);

      this->special = static_cast<TypeCopter*>(Application->environment->plates_copter->_create());
      this->special->setPlate(this);
    }
    break;
    case DOWN:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->downs->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case CUB:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->cubs->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case COLOR:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->colors->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case DIAMOND:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->diamonds->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case CRYSTAL:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->crystals->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case ENERGY:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->energies->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case STAR:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->stars->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case HEART:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->hearts->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case BONUS:
    {
      this->setTexture("plate-texture-state-1-bonus.png");
      this->setRotation3D(Vec3(0, this->direction ? 180 : -90, 0));
    }
    break;

    /**
     *
     * Complex types.
     *
     */
    case MOVED1:
    //this->stopAllActions();
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

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
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

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
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

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
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

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          nullptr
        )
      )
    );
    break;


    case MOVED2:
    //this->stopAllActions();
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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          CallFunc::create([=] () {
            auto action = EaseSineInOut::create(
              MoveBy::create(0.15, Vec3(1.5, 0, 0))
            );

            this->runAction(action->clone());
            this->moved = true;

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          nullptr
        )
      )
    );
    break;


    case MOVED3:
    //this->stopAllActions();
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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
            }
          }),
          DelayTime::create(0.6),
          nullptr
        )
      )
    );
    break;


    case MOVED4:
    //this->stopAllActions();
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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
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

    auto decoration = new Decoration("plate-up.obj", test);
    decoration->setPlate(this, animated);
    decoration->_create()->setColor(Color3B(255.0, 60.0, 60.0));
    decoration->setPosition3D(Vec3(0, 0, 0));
    decoration->unremovable = true;
    this->getDecorations().push_back(decoration);

    //this->stopAllActions();

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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
              decoration->runAction(
                EaseSineInOut::create(
                  RotateBy::create(0.3, Vec3(0, 0,  90))
                )
              );
            }
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

            if(Application->environment->character->plates.current == this && Application->environment->character->getManual())
            {
              Application->environment->character->runAction(action->clone());
            }

            for(auto decoration : this->getDecorations())
            {
              decoration->runAction(action->clone());
              decoration->runAction(
                EaseSineInOut::create(
                  RotateBy::create(0.3, Vec3(0, 0,  -90))
                )
              );
            }
          }),
          DelayTime::create(0.6),
          nullptr
        )
      )
    );
    break;
  }

  switch(this->type)
  {
    case SAW:
    case GATE:
    if(this->getDirection())
    {
      this->special->setRotation3D(Vec3(0.0f, 0.0f, 0.0f));
    }
    else
    {
      this->special->setRotation3D(Vec3(0.0f, 90.0f, 0.0f));
    }
    break;
  }
}

/**
 *
 *
 *
 */
void Plate::add()
{
  this->onAdd();

  auto action = Sequence::create(
    EaseSineIn::create(
      MoveBy::create(0.5, Vec3(this->direction ? -10.0 : 0.0, 0.0, this->direction ? 0.0 : 10.0))
    ),
    nullptr
  );

  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  this->setPosition3D(Vec3(x + (this->direction ? 10.0 : 0.0), y, z - (this->direction ? 0.0 : 10.0)));
  this->runAction(action);

  for(auto decoration : this->getDecorations())
  {
    auto x = decoration->getPositionX();
    auto y = decoration->getPositionY();
    auto z = decoration->getPositionZ();

    decoration->setPosition3D(Vec3(x + (this->direction ? 10.0 : 0.0), y, z - (this->direction ? 0.0 : 10.0)));
    decoration->runAction(action->clone());
  }
}

void Plate::remove(bool complete)
{
  this->onRemove(complete);

  this->runAction(
    Spawn::create(
      Sequence::create(
        EaseSineIn::create(
          MoveBy::create(0.2, Vec3(this->direction ? -10 : 0, 0, this->direction ? 0 : 10))
        ),
        CallFunc::create([=] () {
          this->_destroy(true);
        }),
        nullptr
      ),
      nullptr
    )
  );

  for(auto decoration : this->getDecorations())
  {
    if(decoration->shadow)
    {
      decoration->shadow->_destroy();
    }

    decoration->runAction(
      Spawn::create(
        Sequence::create(
          EaseSineIn::create(
            MoveBy::create(0.2, Vec3(this->direction ? -10 : 0, 0, this->direction ? 0 : 10))
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
void Plate::clearDecorations()
{
  if(this->special)
  {
    this->special->clearDecorations();
  }

  for(auto decoration : this->getDecorations())
  {
    if((decoration->removable && !decoration->unremovable) || !this->state->create)
    {
      decoration->_destroy(true);
    }
  }

  this->getDecorations().erase(
    std::remove_if(
        this->getDecorations().begin(),
        this->getDecorations().end(),
        [](Decoration* element) -> bool {
            return !element->state->create;
        }
    ),
    this->getDecorations().end()
  );
}

void Plate::clearSpecial()
{
  if(this->special)
  {
    this->special->_destroy(true);
    this->special = nullptr;
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

/**
 *
 *
 *
 */
void Plate::setOpacity(GLubyte opacity)
{
  Cube::setOpacity(opacity);

  /**
   *
   *
   *
   */
  if(this->special)
  {
    this->special->setOpacity(opacity);
  }
}

/**
 *
 *
 *
 */
void Plate::setPositionX(float x)
{
  Cube::setPositionX(x);

  /**
   *
   *
   *
   */
  if(this->special)
  {
    this->special->setPositionX(x);
  }
}

/**
 *
 *
 *
 */
void Plate::setPositionY(float y)
{
  Cube::setPositionY(y);

  /**
   *
   *
   *
   */
  if(this->special)
  {
    this->special->setPositionY(y);
  }
}

void Plate::setPositionZ(float z)
{
  Cube::setPositionZ(z);

  /**
   *
   *
   *
   */
  if(this->special)
  {
    this->special->setPositionZ(z);
  }
}

void Plate::setPosition3D(Vec3 position)
{
  Cube::setPosition3D(position);

  /**
   *
   *
   *
   */
  if(this->special)
  {
    this->special->setPosition3D(position);
  }
}

/**
 *
 *
 *
 */
Action* Plate::runAction(Action* action)
{
  Cube::runAction(action);

  /**
   *
   *
   *
   */
  if(this->special)
  {
    this->special->runAction(action->clone());
  }
}
