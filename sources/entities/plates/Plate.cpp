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

  this->shadow = new Shadow("plate-bottom-shadow.obj");
  this->shadow->setMinScale(Vec3(1.0, 1.0, 1.0));
  this->shadow->setMaxScale(Vec3(1.0, 1.0, 1.0));
  this->shadow->setOffset(Vec3(0.4, 0.0, 0.4));

  this->setScheduleUpdate(true);
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
void Plate::onPrepare()
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
      default:
      this->special->setTexture("plate-texture-state-2.png");
      break;
      case SPIKES:
      this->special->setTexture("plate-texture-state-2-spikes.png");
      break;
      case TRAP:
      this->special->setTexture("plate-texture-state-2-trap.png");
      break;
      case TRAMPOLINE:
      this->special->setTexture("plate-texture-state-2-trampoline.png");
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
void Plate::setType(int type, bool animated)
{
  this->type = static_cast<Type>(type);

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
      this->setVisible(false);

      this->special = static_cast<Special*>(Application->environment->plates.spikes->_create());
      this->special->setPlate(this);
    }
    break;
    case TRAP:
    {
      this->setVisible(false);

      this->special = static_cast<Special*>(Application->environment->plates.traps->_create());
      this->special->setPlate(this);
    }
    break;
    case TRAMPOLINE:
    {
      this->setVisible(false);

      this->special = static_cast<Special*>(Application->environment->plates.trampolines->_create());
      this->special->setPlate(this);
    }
    break;
    case SAW:
    {
      this->setVisible(false);

      this->special = static_cast<TypeSaw*>(Application->environment->plates.saws->_create());
      this->special->setPlate(this);
    }
    break;
    case GATE:
    {
      this->special = static_cast<TypeGate*>(Application->environment->plates.gates->_create());
      this->special->setPlate(this);
    }
    break;
    case COPTER:
    {
      this->setVisible(false);

      this->special = static_cast<TypeCopter*>(Application->environment->plates.copters->_create());
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
    {
      this->setVisible(false);
      this->shadow->setVisible(false);

      this->special = static_cast<TypeMoved1*>(Application->environment->plates.moved1->_create());
      this->special->setPlate(this);
    }
    break;


    case MOVED2:
    {
      this->setVisible(false);
      this->shadow->setVisible(false);

      this->special = static_cast<TypeMoved2*>(Application->environment->plates.moved2->_create());
      this->special->setPlate(this);
    }
    break;


    case MOVED3:
    {
      this->setVisible(false);
      this->shadow->setVisible(false);

      this->special = static_cast<TypeMoved3*>(Application->environment->plates.moved3->_create());
      this->special->setPlate(this);
    }
    break;


    case MOVED4:
    {
      this->setVisible(false);
      this->shadow->setVisible(false);

      this->special = static_cast<TypeMoved4*>(Application->environment->plates.moved4->_create());
      this->special->setPlate(this);
    }
    break;

    case MOVE_UP:
    this->setVisible(false);

    this->special = static_cast<Special*>(Application->environment->plates.moveups->_create());
    this->special->setPlate(this);
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
void Plate::prepare()
{
  this->onPrepare();

  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  auto action = Sequence::create(
    EaseSineIn::create(
      MoveBy::create(0.5, Vec3(this->direction ? -10.0 : 0.0, 0.0, this->direction ? 0.0 : 10.0))
    ),
    nullptr
  );

  this->setPosition3D(Vec3(x + (this->direction ? 10.0 : 0.0), y, z - (this->direction ? 0.0 : 10.0)));
  this->runAction(action);

  this->getActionManager()->addAction(Sequence::create(
    DelayTime::create(0.6),
    CallFunc::create([=] () {
      this->setPosition3D(Vec3(x, y, z));
      this->start();
    }),
    nullptr
  ), this, false);

  for(auto decoration : this->getDecorations())
  {
    decoration->setPosition3D(Vec3(decoration->getPositionX() + (this->direction ? 10.0 : 0.0), decoration->getPositionY(), decoration->getPositionZ() - (this->direction ? 0.0 : 10.0)));
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
void Plate::start()
{
  if(this->special)
  {
    this->special->start();
  }
}

/**
 *
 *
 *
 */
bool Plate::conditions(int type)
{
  auto result = false;

  auto length = &Application->environment->generator->length;
  auto conditions = &Application->environment->generator->conditions;

  switch(type)
  {
    case DIAMOND:
    result = true;
    break;
    case CRYSTAL:
    result = true;
    break;
    case ENERGY:
    result = true;
    break;
    case STAR:
    break;
    case HEART:
    break;
    case COLOR:
    result = true;
    break;

    case SPIKES:
    result = conditions.s2 < 1;
    break;
    case TRAMPOLINE:
    result = conditions.s2 < 1;
    break;
    case DOWN:
    result = conditions.s2 < 1;
    break;
    case CUB:
    result = conditions->s1 < 1;
    break;
    case SAW:
    break;
    case GATE:
    break;
    case COPTER:
    break;
    case TRAP:
    result = conditions.s2 < 1;
    break;

    case MOVE_UP:
    break;
    case MOVED1:
    break;
    case MOVED2:
    break;
    case MOVED3:
    break;
    case MOVED4:
    break;
  }

  if(result)
  {
    switch(type)
    {
      case DIAMOND:
      break;
      case CRYSTAL:
      break;
      case ENERGY:
      break;
      case STAR:
      break;
      case HEART:
      break;
      case COLOR:
      break;

      case SPIKES:
      conditions->s1 = 2;
      conditions->s2 = 2;
      break;
      case TRAMPOLINE:
      conditions->s1 = 2;
      conditions->s2 = 2;
      conditions->s6 = 15;
      break;
      case DOWN:
      conditions->s1 = 2;
      conditions->s2 = 2;
      break;
      case CUB:
      conditions->s1 = random(2, 6);
      break;
      case SAW:
      break;
      case GATE:
      break;
      case COPTER:
      break;
      case TRAP:
      conditions->s1 = 2;
      conditions->s2 = 2;
      break;

      case MOVE_UP:
      break;
      case MOVED1:
      break;
      case MOVED2:
      break;
      case MOVED3:
      break;
      case MOVED4:
      break;
    }
  }

  return result;
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
