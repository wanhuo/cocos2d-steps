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
  this->clearSpecial();
  this->clearDecorations();
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

    if(character->plates.current && character->state == Character::STATE_NORMAL)
    {
      if(character->plates.current->getIndex() == this->getIndex())
      {
        Application->environment->character->changeState(Character::STATE_CRASH, Character::Crash::CATCH);
      }
    }
  }

  this->setIndex(10000);

  this->stopAllActions();
}

void Plate::onCount()
{
  if(MissionsFactory::getInstance()->isListenen())
  {
    Application->counter->missionUpdateOnce.points++;
    Application->counter->missionUpdateProgress.points++;

    switch(this->type)
    {
      default:
      break;
      case SPIKES:
      Application->counter->missionUpdateOnce.special_once_5++;
      Application->counter->missionUpdateProgress.special_progress_5++;
      break;
      case TRAMPOLINE:
      Application->counter->missionUpdateOnce.special_once_6++;
      Application->counter->missionUpdateProgress.special_progress_6++;
      break;
      case DOWN:
      Application->counter->missionUpdateOnce.special_once_7++;
      Application->counter->missionUpdateProgress.special_progress_7++;
      break;
      case CUB:
      Application->counter->missionUpdateOnce.special_once_8++;
      Application->counter->missionUpdateProgress.special_progress_8++;
      break;
      case SAW:
      Application->counter->missionUpdateOnce.special_once_9++;
      Application->counter->missionUpdateProgress.special_progress_9++;
      break;
      case GATE:
      Application->counter->missionUpdateOnce.special_once_10++;
      Application->counter->missionUpdateProgress.special_progress_10++;
      break;
      case COPTER:
      Application->counter->missionUpdateOnce.special_once_11++;
      Application->counter->missionUpdateProgress.special_progress_11++;
      break;
      case TRAP:
      Application->counter->missionUpdateOnce.special_once_12++;
      Application->counter->missionUpdateProgress.special_progress_12++;
      break;
      case MOVE_UP:
      Application->counter->missionUpdateOnce.special_once_13++;
      Application->counter->missionUpdateProgress.special_progress_13++;
      break;
      case MOVED1:
      case MOVED2:
      case MOVED3:
      case MOVED4:
      Application->counter->missionUpdateOnce.special_once_15++;
      Application->counter->missionUpdateProgress.special_progress_15++;
      break;
    }

    Events::updateMissions();

    /**
     *
     *
     *
     */
    if(Application->environment->character->getManual())
    {
      if(!Application->environment->generator->bonus)
      {
        Music->speed(1.0 + (0.3 / max(200, Application->environment->generator->size)) * this->index);
      }
    }
  }

  /**
   *
   *
   *
   */
  this->setTexture(Application->environment->getTextureState2());
}

void Plate::onUncount()
{
  if(MissionsFactory::getInstance()->isListenen())
  {
    switch(this->type)
    {
      default:
      break;
      case SPIKES:
      Application->counter->missionUpdateOnce.special_once_5--;
      Application->counter->missionUpdateProgress.special_progress_5--;
      break;
      case TRAMPOLINE:
      Application->counter->missionUpdateOnce.special_once_6--;
      Application->counter->missionUpdateProgress.special_progress_6--;
      break;
      case DOWN:
      Application->counter->missionUpdateOnce.special_once_7--;
      Application->counter->missionUpdateProgress.special_progress_7--;
      break;
      case CUB:
      Application->counter->missionUpdateOnce.special_once_8--;
      Application->counter->missionUpdateProgress.special_progress_8--;
      break;
      case SAW:
      Application->counter->missionUpdateOnce.special_once_9--;
      Application->counter->missionUpdateProgress.special_progress_9--;
      break;
      case GATE:
      Application->counter->missionUpdateOnce.special_once_10--;
      Application->counter->missionUpdateProgress.special_progress_10--;
      break;
      case COPTER:
      Application->counter->missionUpdateOnce.special_once_11--;
      Application->counter->missionUpdateProgress.special_progress_11--;
      break;
      case TRAP:
      Application->counter->missionUpdateOnce.special_once_12--;
      Application->counter->missionUpdateProgress.special_progress_12--;
      break;
      case MOVE_UP:
      Application->counter->missionUpdateOnce.special_once_13--;
      Application->counter->missionUpdateProgress.special_progress_13--;
      break;
      case MOVED1:
      case MOVED2:
      case MOVED3:
      case MOVED4:
      Application->counter->missionUpdateOnce.special_once_15--;
      Application->counter->missionUpdateProgress.special_progress_15--;
      break;
    }

    Events::updateMissions();
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

int Plate::getStage()
{
  return this->stage;
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

void Plate::setStage(int stage)
{
  this->stage = stage;
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
void Plate::setType(int type, bool animated, char data)
{
  this->type = static_cast<Type>(type);

  switch(this->type)
  {
    default:
    break;
    case START:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->decorations.starts->_create());
      decoration->setPlate(this, animated);
      decoration->setRotation3D(Vec3(0, 0, 0));

      this->getDecorations().push_back(decoration);
    }
    break;
    case FINISH:
    {
      this->setVisible(false);

      this->special = static_cast<Special*>(Application->environment->plates.finish->_create());
      this->special->setPlate(this);
    }
    break;
    case BEST:
    {
      this->setVisible(false);

      this->special = static_cast<Special*>(Application->environment->plates.best->_create());
      this->special->setPlate(this);
    }
    break;
    case BONUS:
    {
      this->setVisible(false);

      this->special = static_cast<Special*>(Application->environment->plates.bonus->_create());
      this->special->setPlate(this);

      this->special->setRotation3D(Vec3(0, this->direction ? 180 : -90, 0));
    }
    break;
    case PRESENTION:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->pickups.presentions->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
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
      auto decoration = static_cast<Decoration*>(Application->environment->decorations.downs->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case CUB:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->decorations.cubs->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case COLOR:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->pickups.colors->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case DIAMOND:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->pickups.diamonds->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case CRYSTAL:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->pickups.crystals->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case ENERGY:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->pickups.energies->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case STAR:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->pickups.stars->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case HEART:
    {
      auto decoration = static_cast<Decoration*>(Application->environment->pickups.hearts->_create());
      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
    case PORTAL:
    {
      this->setVisible(false);

      this->special = static_cast<TypePortal*>(Application->environment->plates.portals->_create());
      this->special->setPlate(this);
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
    case LETTER:
    {
      Decoration* decoration;

      switch(data)
      {
        case 'a':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.a->_create());
        break;
        case 'b':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.b->_create());
        break;
        case 'c':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.c->_create());
        break;
        case 'd':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.d->_create());
        break;
        case 'e':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.e->_create());
        break;
        case 'f':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.f->_create());
        break;
        case 'g':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.g->_create());
        break;
        case 'h':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.h->_create());
        break;
        case 'i':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.i->_create());
        break;
        case 'j':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.j->_create());
        break;
        case 'k':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.k->_create());
        break;
        case 'l':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.l->_create());
        break;
        case 'm':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.m->_create());
        break;
        case 'n':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.n->_create());
        break;
        case 'o':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.o->_create());
        break;
        case 'p':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.p->_create());
        break;
        case 'q':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.q->_create());
        break;
        case 'r':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.r->_create());
        break;
        case 's':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.s->_create());
        break;
        case 't':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.t->_create());
        break;
        case 'u':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.u->_create());
        break;
        case 'v':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.v->_create());
        break;
        case 'w':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.w->_create());
        break;
        case 'x':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.x->_create());
        break;
        case 'y':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.y->_create());
        break;
        case 'z':
        decoration = static_cast<Decoration*>(Application->environment->pickups.letters.z->_create());
        break;
      }

      decoration->setPlate(this, animated);

      this->getDecorations().push_back(decoration);
    }
    break;
  }

  switch(this->type)
  {
    default:
    break;
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

  switch(this->type)
  {
    default:
    this->setTexture(Application->environment->getTextureState1());
    break;
    case START:
    this->setTexture(Application->environment->getTextureState2());
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
  if(this->special) this->special->runAction(action->clone());
  this->runAction(action->clone());

  for(auto decoration : this->getDecorations())
  {
    if(decoration->getParent() == Application->environment->plane)
    {
      decoration->setPosition3D(Vec3(decoration->getPositionX() + (this->direction ? 10.0 : 0.0), decoration->getPositionY(), decoration->getPositionZ() - (this->direction ? 0.0 : 10.0)));
      decoration->runAction(action->clone());
    }
  }

  this->runAction(
    Sequence::create(
      DelayTime::create(0.6),
      CallFunc::create([=] () {
      this->start();
      }),
      nullptr
    )
  );
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

  if(this->special)
  {
    this->special->runAction(
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

  for(auto decoration : this->getDecorations())
  {
    if(decoration->getParent() == Application->environment->plane)
    {
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

  for(auto decoration : this->getDecorations())
  {
    decoration->start();
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

  auto direction = Application->environment->generator->direction;
  auto length = Application->environment->generator->length;
  auto count = Application->environment->generator->count;
  auto index = Application->environment->generator->index;
  auto size = Application->environment->generator->size;

  auto conditions = &Application->environment->generator->conditions;

  switch(type)
  {
    case DIAMOND:
    result = conditions->s10 < 1;
    break;
    case CRYSTAL:
    result = true;
    break;
    case ENERGY:
    result = conditions->s8 < 1 && conditions->s9 < 1 && (size - index) > 10;
    break;
    case STAR:
    result = conditions->s4 < 0 && (size - index) > 10;
    break;
    case HEART:
    result = false;
    break;
    case COLOR:
    result = conditions->s11 < 1 && Application->environment->parameters.character != 3;
    break;

    case SPIKES:
    result = conditions->s2 < 1;
    break;
    case TRAMPOLINE:
    result = conditions->s8 < 1 && (size - index) > 5;
    break;
    case DOWN:
    result = conditions->s2 < 1 && conditions->s7 < 1;
    break;
    case CUB:
    result = Application->environment->generator->bonus && conditions->s1 < 1 && count > 2;
    break;
    case SAW:
    result = count > 0 && conditions->s1 < 1 && conditions->s2 < 1 && (size - index) > 5;
    break;
    case GATE:
    result = count > 0 && conditions->s1 < 1 && conditions->s2 < 1 && conditions->s7 < 1;
    break;
    case COPTER:
    result = conditions->s2 < 1 && conditions->s5 < 1;
    break;
    case TRAP:
    result = conditions->s2 < 1;
    break;
    case PORTAL:
    result = (size - index) > 20 && conditions->s8 < 1 && Application->environment->generator->portal <= -10;
    break;

    case MOVE_UP:
    result = (count < length) && count > 0 && direction && conditions->s1 < 1 && conditions->s2 < 0 && conditions->s7 < 1;
    break;
    case MOVED1:
    result = (length - count) > 1 && direction && conditions->s2 < 0 && conditions->s7 < 1 && (size - index) > 2;
    break;
    case MOVED2:
    result = (length - count) > 1 && !direction && conditions->s2 < 0 && conditions->s7 < 1 && (size - index) > 2;
    break;
    case MOVED3:
    result = (count >= length) && direction && conditions->s2 < 0 && conditions->s7 < 1 && (size - index) > 2;
    break;
    case MOVED4:
    result = (count >= length) && !direction && conditions->s2 < 0 && conditions->s7 < 1 && (size - index) > 2;
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
      conditions->s7 = 20;
      conditions->s9 = 15;
      conditions->s10 = 7;
      break;
      case STAR:
      conditions->s4 = 20;
      break;
      case HEART:
      break;
      case COLOR:
      conditions->s11 = 50;
      break;

      case SPIKES:
      conditions->s1 = 2;
      conditions->s2 = 2;
      break;
      case TRAMPOLINE:
      conditions->s1 = 2;
      conditions->s2 = 2;
      conditions->s6 = 15;
      conditions->s8 = 5;
      break;
      case DOWN:
      conditions->s1 = 2;
      conditions->s2 = 2;
      break;
      case CUB:
      conditions->s1 = random(2, 4);
      break;
      case SAW:
      conditions->s1 = 2;
      conditions->s2 = 2;

      Application->environment->generator->length++;
      Application->environment->generator->length++;
      break;
      case GATE:
      conditions->s1 = 2;
      conditions->s2 = 2;

      Application->environment->generator->length++;
      Application->environment->generator->length++;
      break;
      case COPTER:
      conditions->s1 = 2;
      conditions->s2 = 2;
      conditions->s5 = 10;
      break;
      case TRAP:
      conditions->s1 = 2;
      conditions->s2 = 2;
      break;
      case PORTAL:
      Application->environment->generator->portal = 10;
      break;

      case MOVE_UP:
      conditions->s2 = 2;
      break;
      case MOVED1:
      conditions->s2 = 2;

      Application->environment->generator->length++;
      break;
      case MOVED2:
      conditions->s2 = 2;

      Application->environment->generator->length++;
      break;
      case MOVED3:
      conditions->s2 = 2;
      break;
      case MOVED4:
      conditions->s2 = 2;
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
void Plate::setVisibility(bool visible)
{
  Cube::setVisible(visible);

  this->shadow->setVisible(visible);

  if(this->special)
  {
    this->special->setVisible(visible);

    /**
     *
     *
     *
     */
    for(auto decoration : this->special->getDecorations())
    {
      decoration->setVisible(visible);
    }
  }

  /**
   *
   *
   *
   */
  for(auto decoration : this->getDecorations())
  {
    decoration->setVisible(visible);
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
  if(this->special && Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget(this->special) == 0)
  {
    this->special->setPosition3D(position);
  }
}

/**
 *
 *
 *
 */
void Plate::setTexture(const std::string& texture)
{
  Cube::setTexture(texture);

  /**
   *
   *
   *
   */
  for(auto decoration : this->getDecorations())
  {
    decoration->setTexture(texture);
  }

  /**
   *
   *
   *
   */
  if(this->special)
  {
    this->special->setTexture(texture);
  }
}
