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
Video::Video(Node* parent)
: Button("video-button.png", 4, 1, parent, std::bind(&Video::onAction, this))
{
  this->texts.time = new Text("time", this, true);
  this->texts.action = new Text("action", this, true);

  this->texts.time->setPosition(this->getWidth() / 2 + 4.5, 32);
  this->texts.action->setPosition(this->getWidth() / 2, 32);

  this->setCameraMask(4);

  this->setScheduleUpdate(true);
}

Video::~Video()
{
}

/**
 *
 *
 *
 */
void Video::onEnter()
{
  Button::onEnter();

  /**
   *
   *
   *
   */
  this->changeState(NONE);
}

void Video::onExit()
{
  Button::onExit();
}

/**
 *
 *
 *
 */
void Video::onAction()
{
  switch(this->state)
  {
    default:
    break;
    case NORMAL:
    Heyzap::show(Config::AD_TYPE_VIDEO, [=] (bool state) {
    if(state)
    {
      Application->parameters.elapsed.ad = -2;

      this->setCurrentFrameIndex(2);
      this->stopAllActions();
      this->setScale(1.0);
      this->bind(false);

      this->texts.action->data("100");
      this->texts.action->_create();
      this->texts.action->setOpacity(0);
      this->texts.action->runAction(
        Sequence::create(
          FadeIn::create(0.1),
          CallFunc::create([=] () {
          for(int i = 0; i < 20; i++)
          {
            auto time1 = random(0.75, 1.75);
            auto time2 = random(0.0, 0.5);

            auto element = static_cast<R*>(Application->environment->r->_create());
            element->setScale(0.3);
            element->setPosition3D(Vec3(Application->getFrustumWidth() / 2 - 3.1, Application->getFrustumHeight() / 2 + 1.6, 0));

            ccBezierConfig conf;
            conf.controlPoint_1 = Vec2(element->getPosition3D().x + random(-5.0, 0.0), element->getPosition3D().y + random(-5.0, 5.0));
            conf.controlPoint_2 = Vec2(element->getPosition3D().x + random(1.0, 5.0), element->getPosition3D().y + random(-5.0, 5.0));
            conf.endPosition = Vec2(Application->getFrustumWidth() - 0.4, Application->getFrustumHeight() - 0.7);

            element->runAction(
              Spawn::create(
                Sequence::create(
                  DelayTime::create(time2),
                  CallFunc::create([=] () {
                  Sound->play("pickup-diamond");
                  }),
                  ScaleTo::create(time1 - time2, 1.0),
                  nullptr
                ),
                Sequence::create(
                  EaseQuarticActionIn::create(
                    BezierTo::create(time1, conf)
                  ),
                  CallFunc::create([=] () {
                  element->_destroy();

                  Application->counter->icon->setScale(1.0);
                  Application->counter->icon->runAction(
                    Sequence::create(
                      ScaleTo::create(0.1, 0.9),
                      ScaleTo::create(0.5, 0.8),
                      nullptr
                    )
                  );
                  Application->counter->add(5);
                  }),
                  CallFunc::create([=] () {
                  Sound->play("pickup-diamond");
                  }),
                  nullptr
                ),
                nullptr
              )
            );
          }
          }),
          DelayTime::create(2.0),
          FadeOut::create(0.5),
          CallFunc::create([=] () {
          this->changeState(WAIT);
          }),
          nullptr
        )
      );
    }
    });
    break;
    case WAIT:
    break;
  }
}

/**
 *
 *
 *
 */
void Video::onNormal()
{
  this->setCurrentFrameIndex(0);
  this->stopAllActions();
  this->bind(true);
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        Repeat::create(
          Sequence::create(
            ScaleTo::create(0.07, 1.05),
            ScaleTo::create(0.07, 0.97),
            nullptr
          ),
          3
        ),
        DelayTime::create(0.5),
        nullptr
      )
    )
  );

  this->texts.time->_destroy();
  this->texts.action->_destroy();
}

void Video::onWait()
{
  if(this->time - Times::now() < 0)
  {
    this->time = Times::now() + Times::minute() * 15;
    Storage::set(this->id, s(this->time));
  }

  this->setCurrentFrameIndex(2);
  this->stopAllActions();
  this->bind(false);

  this->texts.time->_create();
  this->texts.action->_destroy();
}

/**
 *
 *
 *
 */
void Video::changeState(State state)
{
  if(state == NONE)
  {
    this->time = Times::parse(Storage::get(this->id, true));

    if(this->time - Times::now() < 0)
    {
      this->changeState(NORMAL);
    }
    else
    {
      this->changeState(WAIT);
    }
  }
  else
  {
    if(this->state != state)
    {
      this->state = state;

      switch(this->state)
      {
        default:
        break;
        case NORMAL:
        this->onNormal();
        break;
        case WAIT:
        this->onWait();
        break;
      }
    }
  }
}

/**
 *
 *
 *
 */
void Video::updateNormal(float time)
{
}

void Video::updateWait(float time)
{
  if(this->time - Times::now() > 0)
  {
    this->updateText(time);
  }
  else
  {
    this->changeState(NORMAL);
  }
}

/**
 *
 *
 *
 */
void Video::updateText(float time)
{
  auto data = Times::format(this->time - Times::now());
  this->texts.time->data(data.h, data.m, data.s);
}

/**
 *
 *
 *
 */
void Video::updateStates(float time)
{
  switch(this->state)
  {
    default:
    break;
    case NORMAL:
    this->updateNormal(time);
    break;
    case WAIT:
    this->updateWait(time);
    break;
  }
}

/**
 *
 *
 *
 */
void Video::update(float time)
{
  this->updateStates(time);
}
