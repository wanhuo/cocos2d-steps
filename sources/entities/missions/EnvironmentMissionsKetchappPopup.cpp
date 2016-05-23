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
EnvironmentMissionsKetchappPopup::EnvironmentMissionsKetchappPopup(Node* parent)
: BackgroundColor(parent, Color4B(71.0, 132.0, 164.0, 255.0))
{
  this->setIgnoreAnchorPointForPosition(false);

  this->setAnchorPoint(Vec2(0.5, 1.0));
  this->setContentSize(Size(650, 400));
  this->setPosition(0, Application->getHeight() - 120 - 1000);

  this->background = new BackgroundColor(this, Color4B(255.0, 0.0, 0.0, 255.0));
  this->background->setIgnoreAnchorPointForPosition(false);
  this->background->setContentSize(Size(400, 80));
  this->background->setAnchorPoint(Vec2(0.5, 0.5));
  this->background->setPosition(this->getContentSize().width / 2, this->getContentSize().height);

  this->text = new Entity("ketchapp.png", this->background, true);
  this->text->setPosition(this->background->getContentSize().width / 2, this->background->getContentSize().height / 2);

  this->texts.text1 = new Text("missions-ketchapp-1", this, true);
  this->texts.text1->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 100);

  this->texts.text2 = new Text("missions-ketchapp-2", this, true);
  this->texts.text2->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 150);

  this->complete = Storage::get("missions.ketchapp.complete");

  this->setVisible(false);
}

EnvironmentMissionsKetchappPopup::~EnvironmentMissionsKetchappPopup()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsKetchappPopup::onCreate()
{
  BackgroundColor::onCreate();
}

void EnvironmentMissionsKetchappPopup::onDestroy(bool action)
{
  BackgroundColor::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsKetchappPopup::onEnter()
{
  BackgroundColor::onEnter();
}

void EnvironmentMissionsKetchappPopup::onExit()
{
  BackgroundColor::onExit();
}

/**
 *
 *
 *
 */
void EnvironmentMissionsKetchappPopup::setVisible(bool visible)
{
  BackgroundColor::setVisible(visible);

  /**
   *
   *
   *
   */
  if(visible)
  {
    Application->environment->letters->create("ketchapp");

    /**
     *
     *
     *
     */
    int counter = 0;

    for(auto letter : Application->environment->letters->getChildren())
    {
      if(this->complete > counter++)
      {
        static_cast<Letter*>(letter)->setColor(Color3B(255, 255, 255));
        static_cast<Letter*>(letter)->action();
      }
      else
      {
        static_cast<Letter*>(letter)->setColor(Color3B(0, 0, 0));
      }
    }
  }
  else
  {
    Application->environment->letters->destroy();
  }
}

/**
 *
 *
 *
 */
void EnvironmentMissionsKetchappPopup::update(char letter)
{
  Storage::set("missions.letchapp.complete", ++this->complete);

  if(this->complete >= 0)
  {
    Application->environment->missions.controller->notify->_create();
    Application->environment->missions.missions.elements.erase(Application->environment->missions.missions.elements.begin());
    Application->environment->missions.missions.plane->removeItem(0);
  }

  Finish::getInstance()->missions->notificationKetchapp = true;
}
