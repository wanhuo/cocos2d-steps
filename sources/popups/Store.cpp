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
Store* Store::instance;

/**
 *
 *
 *
 */
Store* Store::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Store::Store()
: Popup("ui/store-background-texture.png")
{
  instance = this;

  this->scroll = new BackgroundScroll(this);
  this->scroll->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
  this->scroll->setBounceEnabled(true);
  this->scroll->setContentSize(Size(Application->getWidth(), Application->getHeight() - 100));
  this->scroll->setPositionY(Application->getHeight() - (Application->getHeight()));
  this->scroll->setScrollBarEnabled(false);

  this->buttons.back = new Button("back-button.png", 2, 1, this, std::bind([=] () {
    this->hide([=] () {
      Application->changeState(Game::MENU);
    });
  }), true);

  this->buttons.back->setPosition(51, Application->getHeight() - 51);

  /**
   *
   *
   *
   */
  auto rootJsonData = Json_create(FileUtils::getInstance()->getStringFromFile("items.json").c_str());
  auto texturesJsonData = Json_getItem(rootJsonData, "textures");

  /**
   *
   *
   *
   */
  for(auto textureJsonData = texturesJsonData->child; textureJsonData; textureJsonData = textureJsonData->next)
  {
    this->positions.push_back(new Position(this->scroll, textureJsonData));
  }
}

Store::~Store()
{
}

/**
 *
 *
 *
 */
void Store::onShow()
{
  Popup::onShow();
}

void Store::onHide(Callback callback)
{
  Popup::onHide(callback);
}

/**
 *
 *
 *
 */
void Store::show()
{
  Popup::show();
}

void Store::hide(Callback callback)
{
  Popup::hide(callback);
}

/**
 *
 *
 *
 */
void Store::onEnter()
{
  Popup::onEnter();

  /**
   *
   *
   *
   */
  this->update();
}

void Store::onExit()
{
  Popup::onExit();
}

/**
 *
 *
 *
 */
void Store::update()
{
  /**
   *
   *
   *
   */
  this->scroll->setInnerContainerSize(
    Size(
      Application->getWidth(),
      (this->positions.size() / ROW + 1) * Store::Position::HEIGHT + (this->positions.size() / ROW + 1) * Store::Position::PY
    )
  );

  /**
   *
   *
   *
   */
  auto x = 0;
  auto y = this->scroll->getInnerContainer()->getContentSize().height - Store::Position::HEIGHT;

  for(int i = 0; i < this->positions.size();)
  {
    x = Store::Position::PX;

    for(int j = 0; j < ROW && i < this->positions.size(); j++)
    {
      auto position = this->positions.at(i);

      position->setPosition(x, y);

      x += Store::Position::WIDTH + Store::Position::PX;
      y += 0;

      i++;
    }
    y -= Store::Position::HEIGHT + Store::Position::PY;
  }
}

/**
 *
 *
 *
 */
int Store::nextTexture(bool action)
{
  Position* position = nullptr;
  vector<Position*> positions;

  /**
   *
   *
   *
   */
  for(auto p : this->positions)
  {
    if(p->state == Position::DIAMONDS)
    {
       if(Application->counter->values.coins >= p->parameters.diamonds)
       {
        positions.push_back(p);
      }
    }
  }

  /**
   *
   *
   *
   */
  if(positions.size())
  {
    position = positions.at(random(0, (int) positions.size() - 1));

    if(action)
    {
      position->onSelect();
    }

    return position->parameters.index;
  }

  return 0;
}

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

Store::Position::Position(Node* parent, Json* parameters)
: BackgroundColor(parent, Color4B(132, 209, 223, 255))
{
  this->setContentSize(Size(WIDTH, HEIGHT));

  this->parameters.id = Json_getString(parameters, "id", "");
  this->parameters.index = Json_getInt(parameters, "index", 0);
  this->parameters.missions = Json_getInt(parameters, "missions", 0);
  this->parameters.diamonds = Json_getInt(parameters, "diamonds", 0);

  this->texts.missions = new Text("store-position-missions", this);
  this->texts.diamonds = new Text("store-position-diamonds", this);

  this->texture = new TiledEntity("textures/textures.png", 5, 1, this);

  this->lock = new Entity("store-position-lock.png", this);
  this->diamond = new Entity("diamond.png", this);

  this->lock->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 + 10);
  this->texture->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
  this->texture->setCurrentFrameIndex(this->parameters.index - 1);

  this->bind(true, false);
}

Store::Position::~Position()
{
}

/**
 *
 *
 *
 */
void Store::Position::setState(State state)
{
  this->state = state;

  this->saveState();
  this->updateState();
}

void Store::Position::saveState()
{
  Storage::set(this->parameters.id, this->state);
}

void Store::Position::updateState()
{
  this->texts.missions->_destroy();
  this->texts.diamonds->_destroy();

  this->lock->_destroy();
  this->diamond->_destroy();
  this->texture->_destroy();

  switch(this->state)
  {
    case MISSIONS:
    this->lock->_create();

    this->texts.missions->_create();
    this->texts.missions->setPosition(this->getContentSize().width / 2, 15);
    this->texts.missions->data(this->parameters.missions);
    break;
    case DIAMONDS:
    this->lock->_create();
    this->diamond->_create();

    this->texts.diamonds->_create();
    this->texts.diamonds->setPosition(this->getContentSize().width / 2 + this->diamond->getWidth() / 2, 15);
    this->texts.diamonds->data(this->parameters.diamonds);

    this->diamond->setPosition(this->getContentSize().width / 2 - this->diamond->getContentSize().width / 2 - 15, 18);
    break;
    case UNLOCKED:
    this->texture->_create();
    break;
    case SELECTED:
    this->texture->_create();
    break;
  }

  switch(this->state)
  {
    default:
    this->setColor(Color3B(132, 209, 223));
    break;
    case SELECTED:
    this->setColor(Color3B(237, 115, 113));
    break;
  }

  this->setCameraMask(4);
}

/**
 *
 *
 *
 */
void Store::Position::onEnter()
{
  BackgroundColor::onEnter();

  /**
   *
   *
   *
   */
  this->stopAllActions();
  this->setScale(1.0);

  this->Node::state->create = true;

  this->state = Storage::get(this->parameters.id);

  if(!this->state)
  {
    if(this->parameters.index == 1)
    {
      this->state = SELECTED;
    }
    else
    {
      if(MissionsFactory::getInstance()->getCompletedMissionsCount() < this->parameters.missions)
      {
        this->state = MISSIONS;
      }
      else
      {
        this->state = DIAMONDS;
      }
    }
  }

  this->updateState();
}

void Store::Position::onExit()
{
  BackgroundColor::onExit();

  /**
   *
   *
   *
   */
  this->Node::state->create = false;
}

/**
 *
 *
 *
 */
void Store::Position::onTouchStart(cocos2d::Touch* touch, Event* e)
{
  BackgroundColor::onTouchStart(touch, e);

  /**
   *
   *
   *
   */
  Color3B color;

  switch(this->state)
  {
    default:
    color = Color3B(100, 204, 223);
    break;
    case SELECTED:
    color = Color3B(237, 101, 100);
    break;
  }

  this->runAction(EaseSineInOut::create(TintTo::create(0.2, color)), 1);
}

void Store::Position::onTouchFinish(cocos2d::Touch* touch, Event* e)
{
  this->stopActionByTag(1);

  switch(this->state)
  {
    default:
    this->setColor(Color3B(132, 209, 223));
    break;
    case SELECTED:
    this->setColor(Color3B(237, 115, 113));
    break;
  }

  Node::onTouchFinish(touch, e);
}

void Store::Position::onTouchCancelled(cocos2d::Touch* touch, Event* e)
{
  Node::onTouchCancelled(touch, e);

  /**
   *
   *
   *
   */
  this->stopActionByTag(1);

  switch(this->state)
  {
    default:
    this->setColor(Color3B(132, 209, 223));
    break;
    case SELECTED:
    this->setColor(Color3B(237, 115, 113));
    break;
  }
}

/**
 *
 *
 *
 */
void Store::Position::onTouch(cocos2d::Touch* touch, Event* e)
{
  switch(this->state)
  {
    case MISSIONS:
    Missions::getInstance()->show();
    break;
    case DIAMONDS:
    this->onPurchase();
    break;
    case UNLOCKED:
    this->onSelect(true);
    break;
    case SELECTED:
    break;
  }
}

/**
 *
 *
 *
 */
void Store::Position::onSelect(bool sound)
{
  for(auto position : Store::getInstance()->positions)
  {
    if(position->state == SELECTED)
    {
      position->setState(UNLOCKED);
    }
  }

  this->runAction(
    Sequence::create(
      EaseSineInOut::create(
        ScaleTo::create(0.2, 0.9)
      ),
      EaseSineInOut::create(
        ScaleTo::create(0.2, 1.1)
      ),
      EaseSineInOut::create(
        ScaleTo::create(0.2, 1.0)
      ),
      nullptr
    )
  );

  if(this->state == DIAMONDS)
  {
    Application->counter->remove(this->parameters.diamonds);
  }

  this->setState(SELECTED);

  Storage::set("store.texture.selected", this->parameters.index);

  Application->environment->updateData();

  if(sound)
  {
    Sound->play("select");
  }
}

void Store::Position::onPurchase()
{
  if(Application->counter->values.coins >= this->parameters.diamonds)
  {
    this->runAction(
      Sequence::create(
        CallFunc::create([=] ()
        {
          Modal::block();
        }),
        Repeat::create(
          Sequence::create(
            ScaleTo::create(0.05, 0.95),
            ScaleTo::create(0.05, 1.05),
            nullptr
          ),
          6
        ),
        ScaleTo::create(0.05, 1.0),
        CallFunc::create([=] () {
        this->onSelect();
        }),
        DelayTime::create(1.0),
        CallFunc::create([=] ()
        {
          Modal::hide();
        }),
        nullptr
      )
    );

    Sound->play("open");
  }
  else
  {
    Sound->play("character-hit");
  }
}
