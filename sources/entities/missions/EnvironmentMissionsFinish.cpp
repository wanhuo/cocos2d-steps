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
EnvironmentMissionsFinish::EnvironmentMissionsFinish(Node* parent)
: BackgroundColor(parent, Color4B(71.0, 132.0, 164.0, 255.0))
{
  this->setIgnoreAnchorPointForPosition(false);

  this->setAnchorPoint(Vec2(0.5, 0.5));
  this->setContentSize(Size(Application->getWidth(), 210));

  for(int i = 0; i < 3; i++)
  {
    this->missions.push_back(new EnvironmentMissionsPopup::MissionTask(this));
  }

  this->background = new BackgroundColor(this, Color4B(95.0, 165.0, 196.0, 255.0));
  this->background->setIgnoreAnchorPointForPosition(false);
  this->background->setContentSize(Size(400, 60));
  this->background->setAnchorPoint(Vec2(0.5, 0.5));
  this->background->setPosition(this->getContentSize().width / 2, this->getContentSize().height);

  this->text = new Text("missions-finish", this->background, true);
  this->text->setPosition(this->background->getContentSize().width / 2, this->background->getContentSize().height / 2);

  this->_destroy();
}

EnvironmentMissionsFinish::~EnvironmentMissionsFinish()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsFinish::onCreate()
{
  BackgroundColor::onCreate();

  /**
   *
   *
   *
   */
  auto structure = MissionsFactory::getInstance()->getCurrentMission();

  if(Application->counter->values.b.mission)
  {
    structure = MissionsFactory::getInstance()->getPreviousMission();
  }

  if(structure)
  {
    for(int i = 0; i < structure->complete.size(); i++)
    {
      auto mission = this->missions.at(i);

      mission->_create();
      mission->setScale(0.4);

      static_cast<EnvironmentMissionsPopup::MissionTask*>(mission)->updateData(i, structure);
    }

    /**
     *
     *
     *
     */
    switch(structure->complete.size())
    {
      case 1:
      this->missions.at(0)->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 - 15);
      break;
      case 2:
      this->missions.at(0)->setPosition(this->getContentSize().width / 2 - 80, this->getContentSize().height / 2 - 15);
      this->missions.at(1)->setPosition(this->getContentSize().width / 2 + 80, this->getContentSize().height / 2 - 15);
      break;
      case 3:
      this->missions.at(0)->setPosition(this->getContentSize().width / 2 - 160, this->getContentSize().height / 2 - 15);
      this->missions.at(1)->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 - 15);
      this->missions.at(2)->setPosition(this->getContentSize().width / 2 + 160, this->getContentSize().height / 2 - 15);
      break;
    }

    this->text->setText("missions-finish");
    this->text->data(structure->id);

    /**
     *
     *
     *
     */
    this->setCameraMask(4);
    this->setPosition(Application->getWidth() / 2, Application->getHeight() / 2 - 230);
  }
  else
  {
    this->_destroy();
  }
}

void EnvironmentMissionsFinish::onDestroy(bool action)
{
  BackgroundColor::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsFinish::onEnter()
{
  BackgroundColor::onEnter();
}

void EnvironmentMissionsFinish::onExit()
{
  BackgroundColor::onExit();

  /**
   *
   *
   *
   */
  this->_destroy();

  for(int i = 0; i < 3; i++)
  {
    this->missions.at(i)->_destroy();
  }
}
