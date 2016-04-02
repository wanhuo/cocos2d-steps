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
: Popup()
{
  instance = this;

  this->buttons.restore = new Button("restore-button.png", 2, 1, this, std::bind(&Game::onRate, Application), true);
  this->buttons.back = new Button("back-button.png", 2, 1, this, std::bind([=] () {
    this->hide([=] () {
      Application->changeState(Game::MENU);
    });
  }), true);

  this->buttons.restore->setPosition(Application->getCenter().x + 150, 200);
  this->buttons.back->setPosition(Application->getCenter().x - 150, 200);

  this->background = new BackgroundColor(this, Color4B(235, 255, 255, 255));

  this->scroll = new BackgroundScroll(this->background);
  this->scroll->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
  this->scroll->setBounceEnabled(true);
  this->scroll->setContentSize(Size(Application->getWidth(), Application->getHeight() - 400));
  this->scroll->setPositionY(0);

  int counter = 0;

  /*for(auto m : MissionsFactory::getInstance()->getMissions())
  {
    this->missions.push_back(new Mission(counter));

    counter++;
  }*/

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
  this->updateTextData();

  this->updateListHeight();

  int i = 1;

 /* for(auto mission : this->missions)
  {
    mission->setPositionY(200 + (this->missions.size() - i) * 220);

    i++;
  }*/

  Events::onScreenChanged("Store");
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

  /*for(auto m : this->missions)
  {
    switch(m->mission->state)
    {
      case MissionStruct::STATE_CURRENT:
      this->scroll->setInnerContainerPosition(Vec2(0, max(-this->size + (Application->getHeight() - 400), -m->getPositionY() + (Application->getHeight() - 400) / 2)));
      break;
      case MissionStruct::STATE_FINISHED:
      if(m->state->create)
      {
        m->removeFromParent();

        this->missions.erase(this->missions.begin() + counter);

        for(auto element : this->scroll->getChildren())
        {
          element->setPositionY(element->getPositionY() - 220);
        }

        int c = 0;
        for(auto m : this->missions)
        {
          if(c >= counter)
          {
            m->setPositionY(m->getPositionY() + 220);
          }

          c++;
        }
      }
      else
      {
        this->missions.erase(this->missions.begin() + counter);

        m->release();

        for(auto element : this->scroll->getChildren())
        {
          element->setPositionY(element->getPositionY() - 220);
        }
      }
      break;
    }

    counter++;
  }*/

  int size = 0;//this->missions.size() - 1;

  this->size = 200 * 2 + size * 220;

  this->scroll->setInnerContainerSize(
    Size(
      Application->getWidth(),
      this->size
    )
  );
}

/**
 *
 *
 *
 */
void Store::updateTextData()
{
}
