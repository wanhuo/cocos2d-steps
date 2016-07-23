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
  this->task.time = time.length() > 0 ? std::stoll(time.c_str()) : 0;
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
void EnvironmentMissionsDailyPopup::update(char letter)
{
  this->task.collected += letter;

  if(this->task.collected.length() >= this->task.word.length())
  {
    Application->counter->values.b.daily = true;

    Application->environment->missions.controller->notify->notify(EnvironmentMissionsNotify::DAILY);

    this->task.active = false;
    this->task.time = Times::now() + Times::minute() * 60 * 24;

    Storage::set("missions.daily.time", patch::to_string(this->task.time));
    Storage::set("missions.daily.reset", 0);
  }

  Storage::set("missions.daily.word", this->task.word);
  Storage::set("missions.daily.collected", this->task.collected);

  Finish::getInstance()->missions->notificationDaily = true;
}
