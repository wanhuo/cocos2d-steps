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
EnvironmentMissionsFinishDaily::EnvironmentMissionsFinishDaily()
: Layout()
{
  this->init();
  this->autorelease();

  this->setScheduleUpdate(true);
  this->setCascadeOpacityEnabled(true);
  this->setContentSize(Size(Application->getWidth(), 210));

  this->background = new BackgroundColor(this, Color4B(255.0, 170.0, 0.0, 255.0));
  this->background->setIgnoreAnchorPointForPosition(false);
  this->background->setContentSize(Size(430, 60));
  this->background->setAnchorPoint(Vec2(0.5, 0.5));
  this->background->setPosition(this->getContentSize().width / 2, this->getContentSize().height);

  this->text = new Text("missions-daily-progress-1", this->background, true);
  this->text->setPosition(this->background->getContentSize().width / 2, this->background->getContentSize().height / 2);

  this->texts.text3 = new Text("missions-daily-3", this);
  this->texts.text3->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 80);

  this->texts.text4 = new Text("missions-daily-4", this);
  this->texts.text4->setPosition(this->getContentSize().width / 2, this->getContentSize().height - 150);

  this->letters = new Letters(this, true);
  this->letters->setPosition3D(Vec3(this->getContentSize().width / 2, this->getContentSize().height / 2 - 30.0, 0.0));
  this->letters->setScale(1.0 / 0.015);

  this->_create();
}

EnvironmentMissionsFinishDaily::~EnvironmentMissionsFinishDaily()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsFinishDaily::onEnter()
{
  Layout::onEnter();

  /**
   *
   *
   *
   */
  if(Application->environment->missions.controller->popups.daily->task.active || Application->counter->values.b.daily)
  {
    this->letters->create(Application->environment->missions.controller->popups.daily->task.word);

    /**
     *
     *
     *
     */
    auto counter = 0;
    auto s = Application->environment->missions.controller->popups.daily->task.collected;

    for(auto letter : this->letters->getChildren())
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

    this->texts.text3->_destroy();
    this->texts.text4->_destroy();
  }
  else
  {
    this->texts.text3->_create();
    this->texts.text4->_create();
  }

  /**
   *
   *
   *
   */
  if(Application->counter->values.b.daily)
  {
    this->text->stopAllActions();
    this->text->setScale(1.0);
    this->text->setText("missions-daily-complete");
  }
  else
  {
    this->text->setText("missions-daily-progress-1");
    this->text->setScale(1.0);
    this->text->setOpacity(255);
    this->text->runAction(
      RepeatForever::create(
        Sequence::create(
          Repeat::create(
            Sequence::create(
            EaseSineInOut::create(
              ScaleTo::create(0.5, 1.1)
            ),
            EaseSineInOut::create(
              ScaleTo::create(0.5, 1.0)
            ),
            nullptr
            ),
          3),
          EaseSineInOut::create(
            ScaleTo::create(0.5, 1.1)
          ),
          EaseSineInOut::create(
            ScaleTo::create(0.5, 1.0, 0.0)
          ),
          CallFunc::create([=] () {
          this->text->setText("missions-daily-progress-2");
          }),
          EaseSineInOut::create(
            ScaleTo::create(0.5, 1.1)
          ),
          EaseSineInOut::create(
            ScaleTo::create(0.5, 1.0)
          ),
          Repeat::create(
            Sequence::create(
            EaseSineInOut::create(
              ScaleTo::create(0.5, 1.1)
            ),
            EaseSineInOut::create(
              ScaleTo::create(0.5, 1.0)
            ),
            nullptr
            ),
          3),
          EaseSineInOut::create(
            ScaleTo::create(0.5, 1.1)
          ),
          EaseSineInOut::create(
            ScaleTo::create(0.5, 1.0, 0.0)
          ),
          CallFunc::create([=] () {
          this->text->setText("missions-daily-progress-1");
          }),
          EaseSineInOut::create(
            ScaleTo::create(0.5, 1.1)
          ),
          EaseSineInOut::create(
            ScaleTo::create(0.5, 1.0)
          ),
          nullptr
        )
      )
    );
  }
}

void EnvironmentMissionsFinishDaily::onExit()
{
  Layout::onExit();

  /**
   *
   *
   *
   */
  this->letters->destroy();
}

/**
 *
 *
 *
 */
void EnvironmentMissionsFinishDaily::update(float time)
{
  if(!Application->environment->missions.controller->popups.daily->task.active)
  {
    long long t = Application->environment->missions.controller->popups.daily->task.time - Times::now();

    string h = "" + patch::to_string(Times::hours(t));
    string m = "" + patch::to_string(Times::minutes(t));
    string s = "" + patch::to_string(Times::seconds(t));

    if(Times::hours(t) < 10) h = "0" + h;
    if(Times::minutes(t) < 10) m = "0" + m;
    if(Times::seconds(t) < 10) s = "0" + s;

    this->texts.text4->data(h, m, s);

    if(t <= 0)
    {
      Application->environment->missions.controller->popups.daily->reset();
      this->onEnter();
    }
  }
  Application->environment->missions.controller->popups.daily->update(time);
}
