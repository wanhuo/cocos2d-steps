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
Gift::Gift(Node* parent)
: Button3D("gift.obj", parent)
{
  this->element = new Gift::Element(this);
}

Gift::~Gift()
{
}

/**
 *
 *
 *
 */
void Gift::onCreate()
{
  Button3D::onCreate();

  this->texture = Application->parameters.presentTexture;

  static_cast<Sprite3D*>(this->getChildByName("box"))->setTexture(this->texture);
  static_cast<Sprite3D*>(this->getChildByName("box"))->setLightMask(this->index);

  static_cast<Sprite3D*>(this->getChildByName("door"))->setTexture(this->texture);
  static_cast<Sprite3D*>(this->getChildByName("door"))->setLightMask(this->index);

  static_cast<Sprite3D*>(this->getChildByName("box"))->setPosition3D(Vec3(0.0, 0.0, 0.0));
  static_cast<Sprite3D*>(this->getChildByName("box"))->setRotation3D(Vec3(0.0, 0.0, 0.0));

  static_cast<Sprite3D*>(this->getChildByName("door"))->setPosition3D(Vec3(0.0, 0.0, 0.0));
  static_cast<Sprite3D*>(this->getChildByName("door"))->setRotation3D(Vec3(0.0, 0.0, 0.0));

  /**
   *
   *
   *
   */
  this->setScale(0);

  this->setPosition3D(Vec3(0, -1.5, -3.0));
  this->setRotation3D(Vec3(0.0, 30.0, 0.0));

  this->camera->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->camera->setRotation3D(Vec3(-20.0, 0.0, 0.0));

  this->runAction(
    Sequence::create(
      ScaleTo::create(0.4, 1.0),
      CallFunc::create([=] () {
        this->runAction(
          RepeatForever::create(
            Sequence::create(
              ScaleTo::create(0.3, 1.05),
              ScaleTo::create(0.3, 1.0),
              nullptr
            )
          )
        );
      }),
      nullptr
    )
  );

  this->runAction(
    RepeatForever::create(
      Sequence::create(
        RotateBy::create(0.5, Vec3(0.0, 30.0, 0.0)),
        nullptr
      )
    )
  );

  this->element->_create();

  this->setCameraMask(this->index);
}

void Gift::onDestroy(bool action)
{
  Button3D::onDestroy(action);

  /**
   *
   *
   *
   */
  this->element->_destroy();
}

/**
 *
 *
 *
 */
void Gift::onTouch(cocos2d::Touch* touch, Event* e)
{
  Button3D::onTouch(touch, e);

  /**
   *
   *
   *
   */
  int count = 10;

  /**
   *
   *
   *
   */
  switch(Application->state)
  {
    case Game::NONE:
    break;
    case Game::MENU:
    break;
    case Game::GAME:
    break;
    case Game::STORE:
    break;
    case Game::MISSIONS:
    break;
    case Game::FINISH:
    break;
    case Game::LOSE:
    break;
    case Game::OPEN:
    break;
    case Game::WATCH:
    break;
    case Game::PRESENT:
    count *= random(1, 5);
    break;
    case Game::MISSION_COMPLETE:
    if(Application->counter->values.b.special)
    {
      count = 100;
    }
    else if(Application->counter->values.b.daily)
    {
      count = 100;
    }
    else
    {
      count = MissionsFactory::getInstance()->getPreviousMission()->coins;
    }
    break;
  }

  /**
   *
   *
   *
   */
  this->element->text->data(count);

  /**
   *
   *
   *
   */
  this->runAction(
    Spawn::create(
      Repeat::create(
        Sequence::create(
          ScaleBy::create(0.05, 1.1),
          ScaleBy::create(0.05, 0.9),
          nullptr
        ), 6),
      Sequence::create(
        CallFunc::create([=] () {
        Modal::block();
        }),
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        this->getChildByName("door")->runAction(
          Sequence::create(
            EaseSineIn::create(
              MoveBy::create(0.35, Vec3(0, 5.0, 0))
            ),
            nullptr
          )
        );
        }),
        DelayTime::create(1.0),
        CallFunc::create([=] () {
        Modal::hide();
        }),
        nullptr
      ),
      Sequence::create(
        DelayTime::create(0.65),
        CallFunc::create([=] () {
        Application->counter->add(count);

        Present::getInstance()->time = 1.0;

        for(int i = 0; i < 40; i++)
        {
          auto element = (R*) Application->environment->r->_create();

          element->setCameraMask(this->index);
          element->setLightMask(this->index);
          element->setPosition3D(this->getPosition3D());
          element->animation1();
        }
        }),
        DelayTime::create(0.4),
        CallFunc::create([=] () {
        Present::getInstance()->time = 0.4;
        }),
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        switch(Application->state)
        {
          default:
          break;
          case Game::PRESENT:
          Present::getInstance()->time = 1.0;
          Present::getInstance()->Finish::onShow();
          break;
          case Game::MISSION_COMPLETE:
          Present::getInstance()->missions->runAction(
            Sequence::create(
              EaseSineOut::create(
                MoveBy::create(0.5, Vec2(0, -15))
              ),
              CallFunc::create([=] () {
              Present::getInstance()->time = 1.0;
              Present::getInstance()->Finish::onShow();
              }),
              nullptr
            )
          );
          break;
        }
        }),
        nullptr
      ),
      nullptr
    )
  );

  this->element->runAction(
    Sequence::create(
      DelayTime::create(0.7),
      EaseSineIn::create(
        MoveBy::create(0.2, Vec3(0.0, 0.8, 0.0))
      ),
      nullptr
    )
  );

  Sound->play("open");
}

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

Gift::Element::Element(Node* parent)
: Entity3D(parent)
{
  this->window = BillBoard::create();
  this->addChild(this->window);

  this->text = new Text("present", this->window, TextHAlignment::RIGHT, true);
  this->text->setScale(0.008);
  this->text->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(-10, 0.0), 0);
  this->text->setPosition(0.1, 0);

  this->diamond = new Entity3D("diamond.obj", this->window, true);
  this->diamond->setTexture(Application->environment->getTextureState1());
  this->diamond->setColor(Color3B(0.0, 243.0, 120.0));
  this->diamond->setScale(0.4);
  this->diamond->setPosition(this->text->getWidthScaled()  / 2, 0.0);
}

Gift::Element::~Element()
{
}

/**
 *
 *
 *
 */
void Gift::Element::onCreate()
{
  Entity3D::onCreate();

  /**
   *
   *
   *
   */
  this->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->setScale(0.5);
  this->setVisible(false);

  this->runAction(
    Sequence::create(
      DelayTime::create(0.4),
      CallFunc::create([=] () {
        this->setVisible(true);
      }),
      nullptr
    )
  );

  this->diamond->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0, 100, 0))
    )
  );
}

void Gift::Element::onDestroy(bool action)
{
  Entity3D::onDestroy(action);
}
