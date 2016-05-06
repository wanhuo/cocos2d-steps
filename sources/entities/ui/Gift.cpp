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
  this->elements = new Pool(new Gift::Diamond, this);
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
  this->elements->clear();
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
  this->runAction(
    Spawn::create(
      Repeat::create(
        Sequence::create(
          ScaleBy::create(0.05, 1.1),
          ScaleBy::create(0.05, 0.9),
          nullptr
        ), 6),
      Sequence::create(
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
        nullptr
      ),
      Sequence::create(
        DelayTime::create(0.65),
        CallFunc::create([=] () {
        Application->counter->add(50);

        Present::getInstance()->time = 1.0;

        for(int i = 0; i < 40; i++)
        {
          auto element = (Entity3D*) this->elements->_create();

          element->setCameraMask(this->index);
          element->setLightMask(this->index);
        }
        }),
        DelayTime::create(0.4),
        CallFunc::create([=] () {
        Present::getInstance()->time = 0.4;
        }),
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        Present::getInstance()->time = 1.0;
        Present::getInstance()->Finish::onShow();
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

Gift::Diamond::Diamond()
: Entity3D("diamond.obj", false)
{
  this->setScheduleUpdate(true);
}

Gift::Diamond::~Diamond()
{
}

/**
 *
 *
 *
 */
void Gift::Diamond::onCreate()
{
  Entity3D::onCreate();

  /**
   *
   *
   *
   */
  this->setTexture(Application->environment->getTextureState1());

  this->setColor(Color3B(0.0, 243.0, 120.0));

  this->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->setScale(0.2);

  this->direction = Vec3(random(0.2, 0.5) * (probably(50) ? 1 : -1), 1.0, random(0.2, 0.5) * (probably(50) ? 1 : -1));
  this->speed = Vec3(random(0.02, 0.1), random(0.1, 0.2), random(0.02, 0.1));

  this->runAction(
    RepeatForever::create(
      RotateBy::create(random(1.0, 2.0), Vec3(360.0, 360.0, 360.0))
    )
  );
}

void Gift::Diamond::onDestroy(bool action)
{
  Entity3D::onDestroy(action);
}

/**
 *
 *
 *
 */
void Gift::Diamond::update(float time)
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  x += this->direction.x * this->speed.x * Present::getInstance()->time;
  y += this->direction.y * this->speed.y * Present::getInstance()->time;
  z += this->direction.z * this->speed.z * Present::getInstance()->time;

  this->setPosition3D(Vec3(x, y, z));

  this->speed.y -= 0.008 * Present::getInstance()->time;
}

/**
 *
 *
 *
 */
Gift::Diamond* Gift::Diamond::deepCopy()
{
  return new Gift::Diamond;
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

  this->text = new Text("present", this->window, true);
  this->text->setScale(0.008);
  this->text->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(-10, 0.0), 0);
  this->text->setPosition(-this->text->getWidthScaled() / 2 + 0.2, 0);

  this->diamond = new Entity3D("diamond.obj", this->window, true);
  this->diamond->setTexture(Application->environment->getTextureState1());
  this->diamond->setColor(Color3B(0.0, 243.0, 120.0));
  this->diamond->setScale(0.5);
  this->diamond->setPosition(this->text->getWidthScaled()  / 2, 0.1);
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
