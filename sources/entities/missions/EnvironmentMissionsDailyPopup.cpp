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
EnvironmentMissionsDailyPopup::EnvironmentMissionsDailyPopup(Node* parent)
: BackgroundColor(parent, Color4B(71.0, 132.0, 164.0, 255.0))
{
  this->setIgnoreAnchorPointForPosition(false);
  this->setScheduleUpdate(true);

  this->setAnchorPoint(Vec2(0.5, 1.0));
  this->setContentSize(Size(650, 400));
  this->setPosition(0, Application->getHeight() - 120 - 1000);

  this->background = new BackgroundColor(this, Color4B(255.0, 170.0, 0.0, 255.0));
  this->background->setIgnoreAnchorPointForPosition(false);
  this->background->setContentSize(Size(400, 80));
  this->background->setAnchorPoint(Vec2(0.5, 0.5));
  this->background->setPosition(this->getContentSize().width / 2, this->getContentSize().height);

  this->texts.background = new Text("missions-daily", this->background, true);
  this->texts.background->setPosition(this->background->getContentSize().width / 2, this->background->getContentSize().height / 2);

  this->texts.text1 = new Text("missions-daily-1", this);
  this->texts.text1->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 100);

  this->texts.text2 = new Text("missions-daily-2", this);
  this->texts.text2->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 150);

  this->texts.text3 = new Text("missions-daily-3", this);
  this->texts.text3->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 100);

  this->texts.text4 = new Text("missions-daily-4", this);
  this->texts.text4->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 220);

  this->_create();

  /**
   *
   *
   *
   */
  auto rootJsonData = Json_create(FileUtils::getInstance()->getStringFromFile("words.json").c_str());
  auto wordsJsonData = Json_getItem(rootJsonData, "words");

  for(auto wordJsonData = wordsJsonData->child; wordJsonData; wordJsonData = wordJsonData->next)
  {
    this->task.words.push_back(wordJsonData->valueString);
  }

  this->reset();
}

EnvironmentMissionsDailyPopup::~EnvironmentMissionsDailyPopup()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsDailyPopup::onCreate()
{
  BackgroundColor::onCreate();
}

void EnvironmentMissionsDailyPopup::onDestroy(bool action)
{
  BackgroundColor::onDestroy(action);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsDailyPopup::onEnter()
{
  BackgroundColor::onEnter();
}

void EnvironmentMissionsDailyPopup::onExit()
{
  BackgroundColor::onExit();
}

/**
 *
 *
 *
 */
string EnvironmentMissionsDailyPopup::getTask()
{
  auto ret = this->task.word;

  for(auto c : this->task.collected)
  {
    ret.erase(ret.find(c), 1);
  }

  return ret;
}

/**
 *
 *
 *
 */
void EnvironmentMissionsDailyPopup::reset()
{
  string time = Storage::get("missions.daily.time", true);
  this->task.time = time.length() > 0 ? stoll(time.c_str()) : 0;
  this->task.active = this->task.time < Times::now();
  this->task.word = Storage::get("missions.daily.word", true);
  this->task.collected = Storage::get("missions.daily.collected", true);

  if(!Storage::get("missions.daily.reset") && this->task.active)
  {
    Storage::set("missions.daily.reset", 1);

    this->task.word = this->task.words.at(random(0, (int) this->task.words.size() - 1));
    this->task.collected = "";

    Storage::set("missions.daily.word", this->task.word);
    Storage::set("missions.daily.collected", this->task.collected);
  }

  this->setVisible(false);
  this->setVisible(true);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsDailyPopup::setVisible(bool visible)
{
  BackgroundColor::setVisible(visible);

  /**
   *
   *
   *
   */
  if(visible)
  {
    if(this->task.active && Application->environment->missions.controller)
    {
      if(Application->environment->missions.controller->isVisible()) Application->environment->letters->create(this->task.word);
      
      this->texts.text1->_create();
      this->texts.text2->_create();

      auto counter = 0;
      auto s = this->task.collected;

      for(auto letter : Application->environment->letters->getChildren())
      {
        auto l = static_cast<Letter*>(letter)->letter;

        if(s.find(l) != string::npos)
        {
          s.erase(s.find(l), 1);

          static_cast<Letter*>(letter)->setOpacity(255);
          static_cast<Letter*>(letter)->setColor(Color3B(255, 170, 0));
          static_cast<Letter*>(letter)->action();
          static_cast<Letter*>(letter)->none->_destroy();
        }
        else
        {
          static_cast<Letter*>(letter)->setOpacity(0);
          static_cast<Letter*>(letter)->none->_create();
        }

        counter++;
      }
    }
    else
    {
      this->texts.text3->_create();
      this->texts.text4->_create();
      this->texts.text4->setScale(1.0);
      this->texts.text4->runAction(
        RepeatForever::create(
          Sequence::create(
            ScaleTo::create(1.0, 1.1),
            ScaleTo::create(1.0, 1.0),
            nullptr
          )
        )
      );
    }
  }
  else
  {
    this->texts.text1->_destroy();
    this->texts.text2->_destroy();
    this->texts.text3->_destroy();
    this->texts.text4->_destroy();

    Application->environment->letters->destroy();
  }

  this->setCameraMask(4);
}

/**
 *
 *
 *
 */
void EnvironmentMissionsDailyPopup::update(char letter)
{
  this->task.collected += letter;

  if(this->task.collected.length() >= this->task.word.length())
  {
    Application->counter->values.b.daily = true;

    Application->environment->missions.controller->notify->notify(EnvironmentMissionsNotify::DAILY);

    this->task.active = false;
    this->task.time = Times::now() + Times::minute() * 60 * 24;

    Storage::set("missions.daily.time", to_string(this->task.time));
    Storage::set("missions.daily.reset", 0);
  }

  Storage::set("missions.daily.word", this->task.word);
  Storage::set("missions.daily.collected", this->task.collected);

  Finish::getInstance()->missions->notificationDaily = true;
}

/**
 *
 *
 *
 */
void EnvironmentMissionsDailyPopup::update(float time)
{
  if(!this->task.active)
  {
    int t = this->task.time - Times::now();

    string h = "" + to_string(Times::hours(t));
    string m = "" + to_string(Times::minutes(t));
    string s = "" + to_string(Times::seconds(t));

    if(Times::hours(t) < 10) h = "0" + h;
    if(Times::minutes(t) < 10) m = "0" + m;
    if(Times::seconds(t) < 10) s = "0" + s;

    this->texts.text4->data(h, m, s);

    if(t <= 0)
    {
      this->reset();
    }
  }
}
