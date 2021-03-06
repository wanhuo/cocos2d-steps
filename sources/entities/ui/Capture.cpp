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
Capture::Capture(Node* parent)
: Entity("capture.png", parent)
{
  this->buttons.back = new Button("back-button.png", 2, 1, Application, std::bind([=] () {
    this->state = STATE_NORMAL;

    this->buttons.back->runAction(
      Sequence::create(
        MoveTo::create(0.2, Vec2(110, Application->getHeight() + 100)),
        CallFunc::create([=] () {
        this->buttons.back->_destroy();
        }),
        nullptr
      )
    );

    this->buttons.share->runAction(
      Sequence::create(
        MoveTo::create(0.2, Vec2(Application->getCenter().x, -100)),
        CallFunc::create([=] () {
        this->buttons.share->_destroy();
        }),
        nullptr
      )
    );

    this->stopAllActions();
    this->runAction(
      Spawn::create(
        ScaleTo::create(0.2, 0.63),
        MoveTo::create(0.2, Vec2(Application->getWidth() / 2, Application->getHeight() / 2 + 70)),
        Sequence::create(
          DelayTime::create(0.2),
          CallFunc::create([=] () {
          }),
          nullptr
        ),
        nullptr
      ), 1
    );
    Application->d->runAction(
      FadeTo::create(0.2, 0)
    );
  }));
  this->buttons.back->setGlobalZOrder(2000);
  this->buttons.back->setLocalZOrder(2000);
  this->buttons.back->setCameraMask(8);

  this->buttons.share = new Button("share-button.png", 3, 1, Application, std::bind([=] () {
  this->onShare(true);
  }));
  this->buttons.share->setGlobalZOrder(2000);
  this->buttons.share->setLocalZOrder(2000);
  this->buttons.share->setCameraMask(8);

  this->element = new Entity(this, true);
  this->element->setGlobalZOrder(1000);
  this->element->setLocalZOrder(-1);

  this->element2 = new Entity(this);
  this->element2->setGlobalZOrder(1000);
  this->element2->setLocalZOrder(-2);

  this->diamond = new Entity("diamond.png", this);
  this->diamond->setGlobalZOrder(1000);
  this->diamond->setLocalZOrder(1);

  this->text = new Text("capture-share", this, true);
  this->text->setPosition(this->getWidth() / 2, 35);
  this->text->setGlobalZOrder(1000);
  this->text->setLocalZOrder(1);

  this->texts.back = new Text("back", this->buttons.back, TextHAlignment::LEFT, true);
  this->texts.back->setPosition(55, this->buttons.back->getHeight() / 2);
  this->texts.back->setGlobalZOrder(2000);
  this->texts.back->setLocalZOrder(2000);
  this->texts.back->setCameraMask(8);

  this->setGlobalZOrder(1000);
  this->setCameraMask(8);

  this->setScheduleUpdate(Screenshot::support());
  this->bind(true);
}

Capture::~Capture()
{
}

/**
 *
 *
 *
 */
void Capture::onCreate()
{
  Entity::onCreate();

  /**
   *
   *
   *
   */
  this->state = STATE_NORMAL;

  this->bind(true);

  this->complete = false;
  this->earn = Screenshot::support() && probably(20);

  /**
   *
   *
   *
   */
  this->setPosition(Application->getWidth() / 2, Application->getHeight() / 2 + 70);
  this->setScale(1.0);

  this->runAction(
    ScaleTo::create(0.2, 0.63)
  );

  if(this->earn)
  {
    this->text->setText("capture-share-and-earn");
    this->text->setPosition(this->getWidth() / 2 - 10, 35);

    this->diamond->_create();
    this->diamond->setScale(1.8);
    this->diamond->setColor(Color3B(71, 132, 164));
    this->diamond->setPosition(this->text->getPositionX() + this->text->getWidth() / 2 + 20, this->text->getPositionY());
  }
  else
  {
    this->text->setText("capture-share");
    this->text->setPosition(this->getWidth() / 2, 35);

    this->diamond->_destroy();
  }

  Finish::getInstance()->missions->_create();

  Sound->play("capture");
}

void Capture::onDestroy(bool action)
{
  Entity::onDestroy(action);
}

/**
 *
 *
 *
 */
void Capture::onTouchStart(cocos2d::Touch* touch, Event* e)
{
  if(this->state == STATE_ACTIVE) return;
  if(this->getActionByTag(1)) return;

  this->stopActionByTag(101);
  this->Node::runAction(
    EaseSineIn::create(
      ScaleTo::create(0.1, this->state == STATE_NORMAL ? 0.58 : 1.25)
    ), 101
  );

  /**
   *
   *
   *
   */
  Node::onTouchStart(touch, e);
}

void Capture::onTouchFinish(cocos2d::Touch* touch, Event* e)
{
  if(this->state == STATE_ACTIVE) return;
  if(this->getActionByTag(1)) return;

  this->stopActionByTag(101);
  this->Node::runAction(
    EaseSineIn::create(
      ScaleTo::create(0.1, this->state == STATE_NORMAL ? 0.63 : 1.3)
    ), 101
  );

  /**
   *
   *
   *
   */
  Node::onTouchFinish(touch, e);
}

void Capture::onTouchCancelled(cocos2d::Touch* touch, Event* e)
{
  if(this->state == STATE_ACTIVE) return;

  this->stopActionByTag(101);
  this->Node::runAction(
    EaseSineIn::create(
      ScaleTo::create(0.1, this->state == STATE_NORMAL ? 0.63 : 1.3)
    ), 101
  );

  /**
   *
   *
   *
   */
  Node::onTouchCancelled(touch, e);
}

/**
 *
 *
 *
 */
void Capture::onTouch(cocos2d::Touch* touch, Event* e)
{
  if(this->state == STATE_ACTIVE) return;

  /**
   *
   *
   *
   */
  Entity::onTouch(touch, e);

  /**
   *
   *
   *
   */
  if(!this->Node::state->create) return;

  /**
   *
   *
   *
   */
  switch(this->state)
  {
    case STATE_NORMAL:
    this->state = STATE_ACTIVE;

    this->buttons.share->_create();
    this->buttons.share->bind(false);
    this->buttons.share->setCurrentFrameIndex(0);
    this->buttons.share->setPosition(Application->getCenter().x, -100);
    this->buttons.share->runAction(
      MoveTo::create(0.2, Vec2(Application->getCenter().x, 220))
    );

    this->buttons.back->_create();
    this->buttons.back->bind(true);
    this->buttons.back->setCurrentFrameIndex(0);
    this->buttons.back->setPosition(110, Application->getHeight() + 100);
    this->buttons.back->runAction(
      MoveTo::create(0.2, Vec2(110, Application->getHeight() - 50))
    );

    this->stopAllActions();
    this->runAction(
      Spawn::create(
        ScaleTo::create(0.2, 1.3),
        RotateTo::create(0.2, 0),
        MoveTo::create(0.2, Vec2(Application->getWidth() / 2, Application->getHeight() / 2 + 50)),
        Sequence::create(
          CallFunc::create([=] () {
          if(Screenshot::support())
          {
            if(!this->complete)
            {
              this->text->setText("capture-1");
              this->text->setPosition(this->getWidth() / 2, 35);
              this->text->data(0);

              this->diamond->_destroy();
            }
            else
            {
              this->buttons.share->bind(true);
              this->buttons.share->setCurrentFrameIndex(1);
            }

            this->element->runAction(
              Sequence::create(
                FadeTo::create(0.2, this->complete ? 255.0 : 0.0),
                CallFunc::create([=] () {
                this->onShare();
                }),
                nullptr
              )
            );
          }
          else
          {
            this->buttons.share->bind(true);
            this->buttons.share->setCurrentFrameIndex(1);

            this->runAction(
              Sequence::create(
                DelayTime::create(0.5),
                CallFunc::create([=] () {
                Application->onShare(true, this->complete,
                  [=] (int state) {
                    if(this->state == STATE_ACTIVE) this->onTouch(NULL, NULL);

                    switch(state)
                    {
                      case 0:
                      this->text->setText("capture-failed");
                      break;
                      case 1:
                      this->text->setText("capture-successful");
                      break;
                    }
                  },
                 [=] (int type, int state) {
                 });
                }),
                nullptr
              )
            );
          }
          }),
          nullptr
        ),
        nullptr
      ), 1
    );
    Application->d->runAction(
      FadeTo::create(0.2, 230)
    );
    break;
    case STATE_ACTIVE:
    break;
  }

  /**
   *
   *
   *
   */
  Sound->play("touch");
}

/**
 *
 *
 *
 */
void Capture::onShare(bool action)
{
  Application->onShare(action, this->complete,
    [=] (int state) {
    if(this->state == STATE_ACTIVE) this->onTouch(NULL, NULL);

    switch(state)
    {
      case 0:
      this->text->setText("capture-failed");
      break;
      case 1:
      this->text->setText("capture-successful");

      if(this->earn)
      {
        this->earn = false;

        for(int i = 0; i < 25; i++)
        {
          auto element = (R*) Application->environment->r->_create();

          element->setCameraMask(Application->counter->icon->getCameraMask());
          element->setLightMask(Application->counter->icon->getLightMask());
          element->animation2();
        }
      }
      break;
      case 2:
      this->text->setText("capture-canceled");
      break;
    }
    },
    [=] (int type, int state) {
      this->element->setOpacity(255);

      switch(type)
      {
        case 1:
        this->element->setTextureRect(
          Rect(
            0,
            0,
            this->element->getTextureRect().size.width,
            this->element2->getTextureRect().size.height * state / 100
          )
        );

        this->text->data(state);

        if(state >= 100)
        {
          Application->runAction(
            Sequence::create(
              DelayTime::create(1.0),
              CallFunc::create([=] () {
              this->complete = true;

              this->buttons.share->bind(true);
              this->buttons.share->setCurrentFrameIndex(1);
              }),
              nullptr
            )
          );

          this->text->setText("capture-ready");
        }
        break;
        case 2:
        Application->giphy->_create();
        Application->giphy->update(state);

        this->text->setText("capture-2");
        this->text->data(state);

        if(state >= 100)
        {
          Application->giphy->runAction(
            Sequence::create(
              MoveBy::create(0.2, Vec2(0, 100)),
              CallFunc::create([=] () {
              Application->giphy->_destroy();
              }),
              nullptr
            )
          );
        }
        break;
      }
  });
}

/**
 *
 *
 *
 */
void Capture::screenshot(string texture)
{
  this->_create();

  /**
   *
   *
   *
   */
  this->text->setText("capture");

  /**
   *
   *
   *
   */
  Director::getInstance()->getTextureCache()->removeUnusedTextures();
  Director::getInstance()->getTextureCache()->removeTextureForKey(texture.c_str());

  /**
   *
   *
   *
   */
  this->element->setTexture(texture.c_str());
  this->element->setScale(407/ this->element->getTextureRect().size.width);
  this->element->setPosition(this->getWidth() / 2, 71);
  this->element->setAnchorPoint(Vec2(0.5, 0.0));
}

/**
 *
 *
 *
 */
void Capture::animation()
{
  this->_create();

  /**
   *
   *
   *
   */
  this->element->_create();
  this->element->initWithTexture(Application->capturing.textures.at(0)->getSprite()->getTexture());
  this->element->setScale(407 / this->element->getWidth());
  this->element->setScaleY(this->element->getScaleY() * -1);
  this->element->setPosition(this->getWidth() / 2, 71);
  this->element->setAnchorPoint(Vec2(0.5, 1.0));

  /**
   *
   *
   *
   */
  this->element2->_create();
  this->element2->initWithTexture(Application->capturing.textures.at(0)->getSprite()->getTexture());
  this->element2->setScale(407 / this->element->getWidth());
  this->element2->setScaleY(this->element2->getScaleY() * -1);
  this->element2->setPosition(this->getWidth() / 2, 71);
  this->element2->setAnchorPoint(Vec2(0.5, 1.0));

  /**
   *
   *
   *
   */
   GLProgram *shader = new GLProgram();
   shader->initWithFilenames("Shaders/grayscale.vsh", "Shaders/grayscale.fsh");
   shader->link();
   shader->updateUniforms();

   auto state = GLProgramState::getOrCreateWithGLProgram(shader);
   this->element2->setGLProgramState(state);
}

/**
 *
 *
 *
 */
bool Capture::containsTouchLocation(cocos2d::Touch* touch)
{
  switch(this->state)
  {
    case STATE_NORMAL:
    return Entity::containsTouchLocation(touch);
    break;
    case STATE_ACTIVE:
    return true;
    break;
  }

  return false;
}

/**
 *
 *
 *
 */
void Capture::update(float time)
{
  if(Application->capturing.frame <= 0)
  {
    Application->capturing.frame = Application->capturing.frames;
  }

  Application->capturing.frame--;

  this->element->Sprite::setTexture(Application->capturing.textures.at(Application->capturing.frame)->getSprite()->getTexture());
  this->element2->Sprite::setTexture(Application->capturing.textures.at(Application->capturing.frame)->getSprite()->getTexture());
}
