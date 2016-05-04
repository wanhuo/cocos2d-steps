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
: Button3D("gift.obj", parent, {
    Camera::createPerspective(60, Application->getWidth() / Application->getHeight(), 1, 100),
    Vec3(0, 0, 2),
    Vec3(0, 0, 0),
    Application,
    5
  },
  {
    {DirectionLight::create(Vec3(1.0, -1.0, -1.0), Color3B(200, 200, 200)), Application},
    {AmbientLight::create(Color3B(120, 120, 120)), Application}
  })
{
  this->elements = new Pool(new Gift::Element, this);
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

  this->texture = this->textures.at(random(0, (int) this->textures.size() - 1));

  for(auto child : this->getChildren())
  {
    static_cast<Sprite3D*>(child)->setTexture(this->texture);
    static_cast<Sprite3D*>(child)->setLightMask(this->index);

    static_cast<Sprite3D*>(child)->setPosition3D(Vec3(0.0, 0.0, 0.0));
    static_cast<Sprite3D*>(child)->setRotation3D(Vec3(0.0, 0.0, 0.0));

    static_cast<Sprite3D*>(child)->getMesh()->getTexture()->setAliasTexParameters();
  }

  this->setCameraMask(this->index);

  /**
   *
   *
   *
   */
  this->setScale(0);

  this->setPosition3D(Vec3(0, -3.0, -5));
  this->setRotation3D(Vec3(0.0, 30.0, 0.0));

  this->camera->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->camera->setRotation3D(Vec3(-20.0, 0.0, 0.0));

  this->runAction(
    Sequence::create(
      ScaleTo::create(0.2, 1.2),
      ScaleTo::create(0.1, 0.8),
      ScaleTo::create(0.1, 1.0),
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
        RotateBy::create(3.0, Vec3(0.0, 30.0, 0.0)),
        RotateBy::create(3.0, Vec3(0.0, -30.0, 0.0)),
        nullptr
      )
    )
  );
}

void Gift::onDestroy(bool action)
{
  Button3D::onDestroy(action);

  /**
   *
   *
   *
   */
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

  this->bind(false);

  this->stopAllActions();

  this->getChildByName("door")->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.1, Vec3(0, -0.1, 0))
      ),
      EaseSineIn::create(
        MoveBy::create(0.5, Vec3(0, 5.0, 0))
      ),
      CallFunc::create([=] () {
      this->runAction(
        Sequence::create(
          EaseSineIn::create(
            ScaleTo::create(0.2, 0.8)
          ),
          EaseSineOut::create(
            ScaleTo::create(0.1    , 1.0)
          ),
          CallFunc::create([=] () {
          for(int i = 0; i < 50; i++)
          {
            auto element = (Entity3D*) this->elements->_create();

            element->setCameraMask(this->index);
            element->setLightMask(this->index);
          }

          Present::getInstance()->texts.claim->stopAllActions();
          Present::getInstance()->texts.claim->runAction(
            Sequence::create(
              FadeOut::create(0.2),
              CallFunc::create([=] () {
              Present::getInstance()->texts.con->runAction(
                Sequence::create(
                  FadeIn::create(0.2),
                  CallFunc::create([=] () {
                  Present::getInstance()->texts.con->runAction(
                    RepeatForever::create(
                      Sequence::create(
                        FadeOut::create(0.5),
                        FadeIn::create(0.5),
                        nullptr
                      )
                    )
                  );
                  }),
                  nullptr
                )
              );
              }),
              nullptr
            )
          );
          }),
          nullptr
        )
      );
      }),
      nullptr
    )
  );
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

Gift::Element::Element()
: Entity3D("diamond.obj", false)
{
  this->setScheduleUpdate(true);
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
  this->setTexture(Application->environment->getTextureState1());

  this->setColor(Color3B(0.0, 231.0, 255.0));

  this->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->setScale(0.3);

  this->direction = Vec3(random(0.5, 1.0) * (probably(50) ? 1 : -1), 1.0, random(0.5, 1.0) * (probably(50) ? 1 : -1));
  this->speed = Vec3(random(0.02, 0.1), random(0.2, 0.3), random(0.02, 0.1));

  this->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0.0, 360.0, 0.0))
    )
  );
}

void Gift::Element::onDestroy(bool action)
{
  Entity3D::onDestroy(action);
}

/**
 *
 *
 *
 */
void Gift::Element::update(float time)
{
  auto x = this->getPositionX();
  auto y = this->getPositionY();
  auto z = this->getPositionZ();

  x += this->direction.x * this->speed.x;
  y += this->direction.y * this->speed.y;
  z += this->direction.z * this->speed.z;

  this->setPosition3D(Vec3(x, y, z));

  this->speed.y -= 0.01;
}

/**
 *
 *
 *
 */
Gift::Element* Gift::Element::deepCopy()
{
  return new Gift::Element;
}
