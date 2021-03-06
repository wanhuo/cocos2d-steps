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
EnvironmentMissionsFinishKetchapp::EnvironmentMissionsFinishKetchapp()
: Layout()
{
  this->init();
  this->autorelease();

  this->setCascadeOpacityEnabled(true);
  this->setContentSize(Size(Application->getWidth(), 210));

  this->background = new BackgroundColor(this, Color4B(255.0, 0.0, 0.0, 255.0));
  this->background->setIgnoreAnchorPointForPosition(false);
  this->background->setContentSize(Size(500, 60));
  this->background->setAnchorPoint(Vec2(0.5, 0.5));
  this->background->setPosition(this->getContentSize().width / 2, this->getContentSize().height);

  this->text = new Text("missions-ketchapp-progress-1", this->background, true);
  this->text->setPosition(this->background->getContentSize().width / 2, this->background->getContentSize().height / 2);

  this->letters = new Letters(this, true);
  this->letters->setPosition3D(Vec3(this->getContentSize().width / 2, this->getContentSize().height / 2 - 30.0, 0.0));
  this->letters->setScale(1.0 / 0.015);
}

EnvironmentMissionsFinishKetchapp::~EnvironmentMissionsFinishKetchapp()
{
}

/**
 *
 *
 *
 */
void EnvironmentMissionsFinishKetchapp::onEnter()
{
  Layout::onEnter();

  /**
   *
   *
   *
   */
  this->letters->create("ketchapp");

  /**
   *
   *
   *
   */
  int counter = 0;

  for(auto letter : this->letters->getChildren())
  {
    if(Application->environment->missions.controller->popups.ketchapp->complete > counter++)
    {
      static_cast<Letter*>(letter)->setColor(Color3B(255, 255, 255));
      static_cast<Letter*>(letter)->action();
    }
    else
    {
      static_cast<Letter*>(letter)->setColor(Color3B(95, 165, 200));
    }
  }

  /**
   *
   *
   *
   */
  if(Application->counter->values.b.special)
  {
    this->text->stopAllActions();
    this->text->setScale(1.0);
    this->text->setText("missions-ketchapp-complete");
  }
  else
  {
    this->text->setText("missions-ketchapp-progress-1");
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
          this->text->setText("missions-ketchapp-progress-2");
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
          this->text->setText("missions-ketchapp-progress-1");
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

void EnvironmentMissionsFinishKetchapp::onExit()
{
  Layout::onExit();

  /**
   *
   *
   *
   */
  this->letters->destroy();
}
