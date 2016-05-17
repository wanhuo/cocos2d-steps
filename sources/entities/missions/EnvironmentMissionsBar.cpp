/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @version of cocos2d is 3.5
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
EnvironmentMissionsBar::EnvironmentMissionsBar()
: Background(Application)
{
  this->buttons.play = new Button("play-button.png", 2, 1, this, std::bind([=] () {
    Application->counter->save();

    Application->s->runAction(
      Sequence::create(
        FadeIn::create(0.2),
        CallFunc::create([=] () {
        Application->changeState(Game::MENU);
        }),
        FadeOut::create(0.2),
        nullptr
      )
    );
  }), true);
  this->buttons.lock = new Button("lock-button.png", 2, 1, this, std::bind([=] () {
  }), true);

  this->buttons.play->setPosition(0, -700);
  this->buttons.lock->setPosition(0, -700);

  this->buttons.play->setCameraMask(4);
  this->buttons.lock->setCameraMask(4);

  this->buttons.play->setVisible(false);
  this->buttons.lock->setVisible(false);

  this->popup = new EnvironmentMissionsPopup(this);
  this->notify = new EnvironmentMissionsNotify();

  Application->environment->missions.missions.plane = cocos2d::ui::ListView::create();
  Application->environment->missions.missions.plane->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
  Application->environment->missions.missions.plane->setBounceEnabled(true);
  Application->environment->missions.missions.plane->setScrollBarEnabled(false);
  Application->environment->missions.missions.plane->setContentSize(Size(22, 42));
  Application->environment->missions.missions.plane->setMagneticType(cocos2d::ui::ListView::MagneticType::CENTER);
  Application->environment->missions.missions.plane->ScrollView::addEventListener([this] (Ref* ref, cocos2d::ui::ScrollView::EventType eventType) {
    long index = Application->environment->missions.missions.plane->getIndex(Application->environment->missions.missions.plane->getCenterItemInCurrentView());

    /**
     *
     *
     *
     */
    this->onSelectMission(index);
  });
  Application->environment->missions.missions.plane->_destroy();
  Application->environment->plane->addChild(Application->environment->missions.missions.plane);

  this->setPosition(Application->getWidth() / 2, Application->getHeight() - 300);

  this->_destroy();
}

EnvironmentMissionsBar::~EnvironmentMissionsBar()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsBar::onCreate()
{
  Background::onCreate();

  /**
   *
   *
   *
   */
  this->onCreateMissions();

  Application->environment->character->_destroy();
  Application->environment->plates.normal->clear();

  this->setCameraMask(4);
}

void EnvironmentMissionsBar::onDestroy(bool action)
{
  Background::onDestroy(action);

  /**
   *
   *
   *
   */
  Application->environment->missions.missions.plane->_destroy(action);
  Application->environment->missions.missions.plane->_destroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsBar::onCreateMissions()
{
  for(auto element : Application->environment->missions.missions.elements) element->_create()->setPosition3D(Vec3(0.0, 0.75, 0.75));

  Application->environment->missions.missions.plane->_create();
  Application->environment->missions.missions.plane->setPosition3D(Vec3(-9.75, -12, 0.0));

  Application->environment->missions.missions.plane->getInnerContainer()->setPositionX(20.0);
  Application->environment->missions.missions.plane->stopAutoScroll();
  Application->environment->missions.missions.plane->stopAllActions();
  Application->environment->missions.missions.plane->getInnerContainer()->stopAllActions();
  Application->environment->missions.missions.plane->getInnerContainer()->runAction(
    Sequence::create(
      MoveTo::create(0.5, Vec3(9.5, 0.0, 0.0)),
      CallFunc::create([=] () {
      Application->environment->missions.missions.plane->ScrollView::_eventCallback(Application->environment->missions.missions.plane, cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED);
      }),
      nullptr
    )
  );

  this->selectedMission = nullptr;
}

/**
 *
 *
 *
 */
void EnvironmentMissionsBar::onSelect(EnvironmentMissionsItem* element)
{
  if(this->selectedMission && this->selectedMission->parameters.index == element->parameters.index) return;

  this->selectedMission = element;

  this->buttons.play->setVisible(false);
  this->buttons.lock->setVisible(false);

  switch(element->mission->state)
  {
    case MissionStruct::STATE_CURRENT:
    this->buttons.play->setVisible(true);
    break;
    case MissionStruct::STATE_LOCKED:
    this->buttons.lock->setVisible(true);
    break;
    case MissionStruct::STATE_CLAIM:
    break;
  }

  this->popup->updateData(element->parameters.index);

  element->changePosition(EnvironmentMissionsItem::Position::POSITION_UP);
}

void EnvironmentMissionsBar::onSelectMission(int index)
{
  auto element = Application->environment->missions.missions.elements.at(index);

  for(auto element : Application->environment->missions.missions.elements)
  {
    if(index != element->parameters.index - 1)
    {
      element->changePosition(EnvironmentMissionsItem::Position::POSITION_NORMAL);
    }
  }

  /*if(element->position == EnvironmentMissionsItem::Position::POSITION_NORMAL && element->state == EnvironmentMissionsItem::STATE_UNLOCKED)
  {
    Application->environment->parameters.character = index + 1;
    Application->environment->parameters.random.character = index == 0;
  }*/

  this->onSelect(element);
}
