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
: Popup("store-background-texture.png")
{
  instance = this;

  this->scroll = new BackgroundScroll(this);
  this->scroll->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
  this->scroll->setBounceEnabled(true);
  this->scroll->setContentSize(Size(Application->getWidth(), Application->getHeight() - 400));
  this->scroll->setPositionY(Application->getHeight() - (Application->getHeight() - 400) - 100);
  this->scroll->setScrollBarEnabled(false);

  this->buttons.restore = new Button("restore-button.png", 2, 1, this, std::bind(&Game::onRate, Application), true);
  this->buttons.back = new Button("back-button.png", 2, 1, this, std::bind([=] () {
    this->hide([=] () {
      Application->changeState(Game::MENU);
    });
  }), true);

  this->buttons.restore->setPosition(Application->getCenter().x + 150, 200);
  this->buttons.back->setPosition(Application->getCenter().x - 150, 200);

  auto x = 150.0;
  auto y = 150.0;

  auto index = 0;

  for(int i = 0; i < 5; i++)
  {
    for(int j = 0; j < 2; j++)
    {
      index++;

      auto item = new Item(index, this->scroll);
      item->setPosition(Application->getCenter().x - x * (j == 0 ? 1 : -1), y);

      this->items.push_back(item);
    }

    y += 300;
  }

  this->updateListHeight();
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
  this->updateListHeight();
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
void Store::updateListHeight()
{
  int counter = 0;

  int size = this->items.size() - 1;

  this->size = size * 300 / 2 + 200;

  this->scroll->setInnerContainerSize(
    Size(
      Application->getWidth(),
      this->size
    )
  );
}
