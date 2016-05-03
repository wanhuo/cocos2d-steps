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
Missions* Missions::instance;

/**
 *
 *
 *
 */
Missions* Missions::getInstance()
{
  return instance;
}

/**
 *
 *
 *
 */
Missions::Missions()
: Popup("missions-background-texture.png")
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
  for(auto mission : MissionsFactory::getInstance()->getMissions())
  {
    this->positions.push_back(new Missions::Position(this->scroll, mission));
  }
}

Missions::~Missions()
{
}

/**
 *
 *
 *
 */
void Missions::onShow()
{
  Popup::onShow();
}

void Missions::onHide(Callback callback)
{
  Popup::onHide(callback);
}

/**
 *
 *
 *
 */
void Missions::show()
{
  Popup::show();
}

void Missions::hide(Callback callback)
{
  Popup::hide(callback);
}

/**
 *
 *
 *
 */
void Missions::onEnter()
{
  Popup::onEnter();

  /**
   *
   *
   *
   */
  this->update();
}

void Missions::onExit()
{
  Popup::onExit();
}

/**
 *
 *
 *
 */
void Missions::update()
{
  /**
   *
   *
   *
   */
  this->scroll->setInnerContainerSize(
    Size(
      Application->getWidth(),
      (this->positions.size() + 1) * Missions::Position::HEIGHT + (this->positions.size() + 1) * Missions::Position::PY
    )
  );

  /**
   *
   *
   *
   */
  auto x = Missions::Position::PX;
  auto y = this->scroll->getInnerContainer()->getContentSize().height - Missions::Position::HEIGHT;

  for(int i = 0; i < this->positions.size(); i++)
  {
    auto position = this->positions.at(i);

    position->setPosition(x, y);

    y -= Missions::Position::HEIGHT + Missions::Position::PY;
  }
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

Missions::Position::Position(Node* parent, MissionStruct* mission)
: BackgroundColor(parent, Color4B(132, 209, 223, 255))
{
  this->setContentSize(Size(WIDTH, HEIGHT));

  this->mission = mission;

  this->bind(true, false);
}

Missions::Position::~Position()
{
}

/**
 *
 *
 *
 */
void Missions::Position::onEnter()
{
  BackgroundColor::onEnter();

  /**
   *
   *
   *
   */
  this->Node::state->create = true;
}

void Missions::Position::onExit()
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
void Missions::Position::onTouchStart(cocos2d::Touch* touch, Event* e)
{
  BackgroundColor::onTouchStart(touch, e);

  /**
   *
   *
   *
   */
  Color3B color;

  switch(this->mission->state)
  {
    case MissionStruct::STATE_LOCKED:
    case MissionStruct::STATE_CURRENT:
    color = Color3B(100, 204, 223);
    break;
    case MissionStruct::STATE_CLAIM:
    color = Color3B(237, 101, 100);
    break;
  }

  this->runAction(EaseSineInOut::create(TintTo::create(0.2, color)), 1);
}

void Missions::Position::onTouchFinish(cocos2d::Touch* touch, Event* e)
{
  this->stopActionByTag(1);

  switch(this->mission->state)
  {
    case MissionStruct::STATE_LOCKED:
    case MissionStruct::STATE_CURRENT:
    this->setColor(Color3B(132, 209, 223));
    break;
    case MissionStruct::STATE_CLAIM:
    this->setColor(Color3B(237, 115, 113));
    break;
  }

  Node::onTouchFinish(touch, e);
}

void Missions::Position::onTouchCancelled(cocos2d::Touch* touch, Event* e)
{
  Node::onTouchCancelled(touch, e);

  /**
   *
   *
   *
   */
  this->stopActionByTag(1);

  switch(this->mission->state)
  {
    case MissionStruct::STATE_LOCKED:
    case MissionStruct::STATE_CURRENT:
    this->setColor(Color3B(132, 209, 223));
    break;
    case MissionStruct::STATE_CLAIM:
    this->setColor(Color3B(237, 115, 113));
    break;
  }
}

/**
 *
 *
 *
 */
void Missions::Position::onTouch(cocos2d::Touch* touch, Event* e)
{
}
