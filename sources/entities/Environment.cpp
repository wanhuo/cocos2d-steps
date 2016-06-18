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
const Color3B Environment::COLORS[] = {
};

const Color3B Environment::TEXTURES_COLORS[] = {
  Color3B(252, 226, 105),
  Color3B(231, 223, 194),
  Color3B(172, 192, 193),
  Color3B(236, 220, 184),
  Color3B(184, 235, 252),
  Color3B(97, 177, 177),
  Color3B(187, 128, 68),
  Color3B(172, 192, 193),
  Color3B(187, 220, 47),
  Color3B(187, 102, 70),
  Color3B(115, 205, 75),
  Color3B(108, 131, 133),
  Color3B(103, 174, 204),
  Color3B(193, 159, 240),
  Color3B(244, 154, 193),
  Color3B(218, 190, 133),
  Color3B(150, 165, 212),
  Color3B(208, 174, 108)
};

/**
 *
 *
 *
 */
Environment::Environment(Node* parent)
: Background(parent)
{
  this->updateData();
}

Environment::~Environment()
{
}

/**
 *
 *
 *
 */
void Environment::onAccelerate(Acceleration* acceleration, Event* e)
{
  this->accelerometerX = acceleration->x * ACCELEROMETER_FACTOR;
  this->accelerometerY = acceleration->y * ACCELEROMETER_FACTOR;
  this->accelerometerZ = acceleration->z * ACCELEROMETER_FACTOR;
}

/**
 *
 *
 *
 */
void Environment::create()
{
  this->plane = new Entity3D(this, true);
  this->plane->setRotation3D(Vec3(0, 0, 0));
  this->plane->setPosition3D(Vec3(0, 0, 0));

  this->ground = new Ground(this);
  this->insane = new Insane;

  this->plates.normal = new Pool(new Plate, this->plane);
  this->plates.simple = new Pool(new TypeSimple, this->plane);
  this->plates.duel = new Pool(new TypeDuel, this->plane);
  this->plates.finish = new Pool(new TypeFinish, this->plane);
  this->plates.best = new Pool(new TypeBest, this->plane);
  this->plates.bonus = new Pool(new TypeBonus, this->plane);
  this->plates.spikes = new Pool(new TypeSpikes, this->plane);
  this->plates.trampolines = new Pool(new TypeTrampoline, this->plane);
  this->plates.saws = new Pool(new TypeSaw, this->plane);
  this->plates.gates = new Pool(new TypeGate, this->plane);
  this->plates.copters = new Pool(new TypeCopter, this->plane);
  this->plates.traps = new Pool(new TypeTrap, this->plane);
  this->plates.portals = new Pool(new TypePortal, this->plane);
  this->plates.moveups = new Pool(new TypeMoveUp, this->plane);
  this->plates.moved1 = new Pool(new TypeMoved1, this->plane);
  this->plates.moved2 = new Pool(new TypeMoved2, this->plane);
  this->plates.moved3 = new Pool(new TypeMoved3, this->plane);
  this->plates.moved4 = new Pool(new TypeMoved4, this->plane);
  this->plates.moved5 = new Pool(new TypeMoved5, this->plane);

  this->pickups.diamonds = new Pool(new Diamond, this->plane);
  this->pickups.crystals = new Pool(new Crystal, this->plane);
  this->pickups.energies = new Pool(new Energy, this->plane);
  this->pickups.stars = new Pool(new Star, this->plane);
  this->pickups.hearts = new Pool(new Heart, this->plane);
  this->pickups.colors = new Pool(new Color, this->plane);
  this->pickups.presentions = new Pool(new Presention, this->plane);

  this->pickups.letters.a = new Pool(new Let('a'), this->plane);
  this->pickups.letters.b = new Pool(new Let('b'), this->plane);
  this->pickups.letters.c = new Pool(new Let('c'), this->plane);
  this->pickups.letters.d = new Pool(new Let('d'), this->plane);
  this->pickups.letters.e = new Pool(new Let('e'), this->plane);
  this->pickups.letters.f = new Pool(new Let('f'), this->plane);
  this->pickups.letters.g = new Pool(new Let('g'), this->plane);
  this->pickups.letters.h = new Pool(new Let('h'), this->plane);
  this->pickups.letters.i = new Pool(new Let('i'), this->plane);
  this->pickups.letters.j = new Pool(new Let('j'), this->plane);
  this->pickups.letters.k = new Pool(new Let('k'), this->plane);
  this->pickups.letters.l = new Pool(new Let('l'), this->plane);
  this->pickups.letters.m = new Pool(new Let('m'), this->plane);
  this->pickups.letters.n = new Pool(new Let('n'), this->plane);
  this->pickups.letters.o = new Pool(new Let('o'), this->plane);
  this->pickups.letters.p = new Pool(new Let('p'), this->plane);
  this->pickups.letters.q = new Pool(new Let('q'), this->plane);
  this->pickups.letters.r = new Pool(new Let('r'), this->plane);
  this->pickups.letters.s = new Pool(new Let('s'), this->plane);
  this->pickups.letters.t = new Pool(new Let('t'), this->plane);
  this->pickups.letters.u = new Pool(new Let('u'), this->plane);
  this->pickups.letters.v = new Pool(new Let('v'), this->plane);
  this->pickups.letters.w = new Pool(new Let('w'), this->plane);
  this->pickups.letters.x = new Pool(new Let('x'), this->plane);
  this->pickups.letters.y = new Pool(new Let('y'), this->plane);
  this->pickups.letters.z = new Pool(new Let('z'), this->plane);

  this->decorations.downs = new Pool(new Down, this->plane);
  this->decorations.starts = new Pool(new Start, this->plane);
  this->decorations.cubs = new Pool(new Cub, this->plane);

  this->particles.s = new Pool(new Particle, this->plane);

  this->character = new Character;
  this->generator = new Generator;
  this->letters = new Letters(Application);

  this->characterActionHolder = new Background(this);
  this->characterActionHolder->setContentSize(Size(Application->getWidth(), 0));
  this->characterActionHolder->setPosition(Vec2(0, 870));
  this->characterActionHolder->setCascadeOpacityEnabled(true);
  this->characterActionHolder->setCameraMask(4);

  this->characterActionBackground = new BackgroundColor(this->characterActionHolder, Color4B(255, 255, 255, 150));
  this->characterActionBackground->setContentSize(Size(Application->getWidth() - 100, 40));
  this->characterActionBackground->setAnchorPoint(Vec2(0, 0));
  this->characterActionBackground->setPosition(Vec2(50, 10));
  this->characterActionBackground->setCameraMask(4);

  this->characterAction = new BackgroundColor(this->characterActionHolder, Color4B(255, 0, 0, 150));
  this->characterAction->setContentSize(Size(Application->getWidth() - 110, 30));
  this->characterAction->setAnchorPoint(Vec2(0, 0));
  this->characterAction->setPosition(Vec2(55, 15));
  this->characterAction->setCameraMask(4);

  this->characterActionHolder->setScale(0);
  this->characterActionHolder->setOpacity(0);

  this->light.natural = AmbientLight::create(Color3B(150, 150, 150));
  this->light.environment = DirectionLight::create(Vec3(0.5, -1.0, 0.0), Color3B(120, 120, 120));

  this->plane->addChild(this->light.environment);
  this->plane->addChild(this->light.natural);

  /**
   *
   *
   *
   */
  this->store.controller = new EnvironmentStoreBar();
  this->missions.controller = new EnvironmentMissionsBar();
  this->missions.special = this->missions.controller->popups.ketchapp->complete < 8;















///
  auto rootJsonData = Json_create(FileUtils::getInstance()->getStringFromFile("store.json").c_str());
  auto charactersJsonData = Json_getItem(rootJsonData, "characters");
  auto texturesJsonData = Json_getItem(rootJsonData, "textures");

  for(auto characterJsonData = charactersJsonData->child; characterJsonData; characterJsonData = characterJsonData->next) this->store.characters.elements.push_back(new EnvironmentStoreCharacter(characterJsonData));
  for(auto textureJsonData = texturesJsonData->child; textureJsonData; textureJsonData = textureJsonData->next) this->store.textures.elements.push_back(new EnvironmentStoreTexture(textureJsonData));

  /**
   *
   *
   *
   */
  if(Application->environment->missions.special) this->missions.missions.elements.push_back(new EnvironmentMissionsItem(-2));
  this->missions.missions.elements.push_back(new EnvironmentMissionsItem(-1));

  int counter = 0;

  for(auto m : MissionsFactory::getInstance()->getMissions())
  {
    switch(m->state)
    {
      case MissionStruct::STATE_CURRENT:
      case MissionStruct::STATE_LOCKED:
      this->missions.missions.elements.push_back(new EnvironmentMissionsItem(counter));
      break;
    }

    counter++;
  }

  //this->missions.missions.elements.push_back(new EnvironmentMissionsItem(0));
}

void Environment::reset()
{
  this->generator->reset();

  this->platesTime = 1.0;
  this->platesTimeElapsed = 0;

  Application->counter->onFinish();
}

/**
 *
 *
 *
 */
Entity3D* Environment::createParticle(int type, float x, float y, float z)
{
  auto particle = static_cast<Entity3D*>(this->particles.s->_create());

  switch(type)
  {
    case 0:
    particle->setScaleX(random(0.5, 1.5));
    particle->setScaleY(0.0);
    particle->setScaleZ(random(0.5, 1.5));

    particle->setPositionX(x);
    particle->setPositionY(y);
    particle->setPositionZ(z);

    particle->runAction(
      Spawn::create(
        Sequence::create(
          EaseSineOut::create(
            ScaleTo::create(random(0.2, 0.5), particle->getScaleX(), 1.0, particle->getScaleZ())
          ),
          EaseSineOut::create(
            ScaleTo::create(random(0.2, 0.5), 0.0)
          ),
          CallFunc::create([=] () {
            particle->_destroy(true);
          }),
          nullptr
        ),
        Sequence::create(
          EaseSineOut::create(
            MoveBy::create(random(0.2, 0.5), Vec3(random(0.5, 1.2) * (probably(50) ? 1 : -1), 0.0, random(0.5, 1.2) * (probably(50) ? 1 : -1)))
          ),
          nullptr
        ),
        nullptr
      )
    );
    break;
    case 1:
    auto s = random(1.0, 1.5);

    particle->setScaleX(s);
    particle->setScaleY(s);
    particle->setScaleZ(s);

    particle->setPositionX(x);
    particle->setPositionY(y);
    particle->setPositionZ(z);

    particle->runAction(
      Spawn::create(
        Sequence::create(
          EaseSineOut::create(
            ScaleTo::create(random(0.2, 0.5), s * 1.2)
          ),
          EaseSineOut::create(
            ScaleTo::create(random(1.0, 2.5), 0.0)
          ),
          CallFunc::create([=] () {
            particle->_destroy(true);
          }),
          nullptr
        ),
        Sequence::create(
          EaseSineOut::create(
            MoveBy::create(random(0.2, 0.5), Vec3(random(0.5, 1.5) * (probably(50) ? 1 : -1), random(0.5, 1.5), random(0.5, 1.5) * (probably(50) ? 1 : -1)))
          ),
          nullptr
        ),
        nullptr
      )
    );
    break;
  }

  return particle;
}

/**
 *
 *
 *
 */
string Environment::getTextureState1()
{
  return "textures/" + patch::to_string(this->parameters.texture) + "/textures-state-1.png";
}

string Environment::getTextureState2()
{
  return "textures/" + patch::to_string(this->parameters.texture) + "/textures-state-2.png";
}

/**
 *
 *
 *
 */
void Environment::updateData()
{
  this->parameters.stage = max(1, Storage::get("application.current.level"));

  this->parameters.character = max(2, Storage::get("store.character.selected"));
  this->parameters.texture = max(2, Storage::get("store.texture.selected"));

  this->parameters.random.character = Storage::get("store.character.random");
  this->parameters.random.texture = Storage::get("store.texture.random");

  /**
   *
   * Check is random choose of character and texture are enabled.
   *
   */
  if(this->store.controller)
  {
    if(this->parameters.random.character) this->parameters.character = this->store.controller->randomCharacter();
    if(this->parameters.random.texture) this->parameters.texture = this->store.controller->randomTexture();
  }

  /**
   *
   * Check is next character is setted up manually.
   *
   */
  if(this->nextCharacter)
  {
    this->parameters.character = this->nextCharacter;
    this->nextCharacter = 0;
  }

  /**
   *
   * Check is next texture is setted up manually.
   *
   */
  if(this->nextTexture)
  {
    this->parameters.texture = this->nextTexture;
    this->nextTexture = 0;
  }

  Director::getInstance()->getTextureCache()->addImageAsync(this->getTextureState1(), nullptr);
  Director::getInstance()->getTextureCache()->addImageAsync(this->getTextureState2(), nullptr);
}

void Environment::updateLevel()
{
  Analytics::sendEvent("Application", "application.events.onStagePassed", ("Stage passed: " + patch::to_string(this->parameters.stage)).c_str());

  Storage::set("application.current.level", ++this->parameters.stage);
}

/**
 *
 *
 *
 */
void Environment::onTurn(bool action)
{
  this->setPosition3D(Vec3(0, 0, 0));

  if(!Director::getInstance()->getActionManager()->getActionByTag(7, this->character->plane))
  {
    this->character->onTurn(action);
  }
}

/**
 *
 *
 *
 */
void Environment::onMenu()
{
  this->store.controller->_destroy();
  this->missions.controller->_destroy();

  this->updateData();

  this->finishStar();

  this->platesTime = 1.0;
  this->platesTimeElapsed = 0;
  this->platesTimeIndex = Storage::get("application.plates.index." + s(this->parameters.stage));

  if(this->enemy)
  {
    this->enemy->removeFromParent();
    this->enemy = nullptr;
  }

  this->character->_destroy();
  this->character->removeFromParent();
  //this->character->release();
  this->character = new Character;
  this->character->_create();

  this->ground->reset();
  this->generator->reset(true);

  this->setPosition3D(Vec3(0, 0, 0));
  this->plane->setPosition3D(Vec3(0, 0, 0));
}

void Environment::onGame()
{
  MissionsFactory::getInstance()->startListen();

  this->onTurn();
}

void Environment::onFinish()
{
}

void Environment::onLose()
{
  this->finishStar();
}

void Environment::onStore()
{
  Application->s->runAction(
    Sequence::create(
      FadeIn::create(0.2),
      CallFunc::create([=] () {

      Application->cameras.d->setScale(1.0);
      Application->cameras.d->setPosition3D(Vec3(Application->startCameraX, Application->startCameraY, Application->startCameraZ));
      Application->cameras.d->setRotation3D(Vec3(Application->startCameraRotationX, Application->startCameraRotationY, Application->startCameraRotationZ));

      this->store.controller->_create();
      }),
      FadeOut::create(0.2),
      nullptr
    )
  );
}

void Environment::onMissions()
{
  Application->s->runAction(
    Sequence::create(
      FadeIn::create(0.2),
      CallFunc::create([=] () {

      Application->cameras.d->setScale(1.0);
      Application->cameras.d->setPosition3D(Vec3(Application->startCameraX, Application->startCameraY, Application->startCameraZ));
      Application->cameras.d->setRotation3D(Vec3(Application->startCameraRotationX, Application->startCameraRotationY, Application->startCameraRotationZ));

      this->missions.controller->_create();
      }),
      FadeOut::create(0.2),
      nullptr
    )
  );
}

void Environment::onPresent()
{
}

void Environment::onOpen()
{
}

void Environment::onWatch()
{
}

void Environment::onCopter()
{
}

void Environment::onMissionComplete()
{
}

/**
 *
 *
 *
 */
void Environment::startStar()
{
  this->star = true;

  this->starTime = STAR_TIME;
  this->starTimeElapsed = 0;

  Application->counter->onStarStart();
}

void Environment::finishStar()
{
  this->star = false;

  Application->counter->onStarFinish();
}

/**
 *
 *
 *
 */
void Environment::updateMenu(float time)
{
}

void Environment::updateLose(float time)
{
}

void Environment::updateGame(float time)
{
  if(this->character->getManual())
  {
    switch(this->character->state)
    {
      case Character::STATE_CRASH:
      case Character::STATE_INSANE:
      break;
      default:
      this->platesTimeElapsed += time;

      if(this->platesTimeElapsed >= this->platesTime)
      {
        this->platesTime = max(0.3 + this->platesTimeIndex * 0.05 + max(0.0, (0.5 - 0.1 * this->parameters.stage)), this->platesTime - 0.01);
        this->platesTimeElapsed = 0;

        this->generator->destroy();
      }
      break;
    }
  }
}

/**
 *
 *
 *
 */
void Environment::updateStar(float time)
{
  if(this->star)
  {
    Application->counter->onStarUpdate();

    this->starTimeElapsed += time;

    if(this->starTimeElapsed >= this->starTime)
    {
      this->finishStar();
    }
  }
}

/**
 *
 *
 *
 */
void Environment::update(float time)
{
  switch(Application->state)
  {
    default:
    break;
    case Game::MENU:
    this->updateMenu(time);
    break;
    case Game::GAME:
    this->updateGame(time);
    break;
    case Game::LOSE:
    this->updateLose(time);
    break;
  }

  this->updateStar(time);
}
