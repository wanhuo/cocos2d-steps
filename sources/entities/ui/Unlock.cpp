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
Unlock::Unlock(Node* parent)
: Button3D("unlock.obj", parent)
{
}

Unlock::~Unlock()
{
}

/**
 *
 *
 *
 */
void Unlock::onCreate()
{
  Button3D::onCreate();

  /**
   *
   *
   *
   */
  static_cast<Sprite3D*>(this->getChildByName("box"))->setTexture("ui/video-texture.png");
  static_cast<Sprite3D*>(this->getChildByName("box"))->setLightMask(this->index);

  static_cast<Sprite3D*>(this->getChildByName("door"))->setTexture("ui/video-texture.png");
  static_cast<Sprite3D*>(this->getChildByName("door"))->setLightMask(this->index);

  static_cast<Sprite3D*>(this->getChildByName("plate"))->setTexture("ui/video-texture.png");
  static_cast<Sprite3D*>(this->getChildByName("plate"))->setLightMask(this->index);

  static_cast<Sprite3D*>(this->getChildByName("box"))->setPosition3D(Vec3(0.0, 0.0, 0.0));
  static_cast<Sprite3D*>(this->getChildByName("box"))->setRotation3D(Vec3(0.0, 0.0, 0.0));

  static_cast<Sprite3D*>(this->getChildByName("door"))->setPosition3D(Vec3(0.0, 0.0, 0.0));
  static_cast<Sprite3D*>(this->getChildByName("door"))->setRotation3D(Vec3(0.0, 0.0, 0.0));

  static_cast<Sprite3D*>(this->getChildByName("plate"))->setPosition3D(Vec3(0.0, 0.0, 0.0));
  static_cast<Sprite3D*>(this->getChildByName("plate"))->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->setScale(0);

  this->setPosition3D(Vec3(0, -1.7, -3.0));
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

  this->setCameraMask(this->index);
}

void Unlock::onDestroy(bool action)
{
  Button3D::onDestroy(action);
}

/**
 *
 *
 *
 */
void Unlock::onTouch(cocos2d::Touch* touch, Event* e)
{
  Button3D::onTouch(touch, e);

  /**
   *
   *
   *
   */
  Store::getInstance()->nextTexture(true);

  /**
   *
   *
   *
   */
  static_cast<Sprite3D*>(this->getChildByName("plate"))->setTexture(Application->environment->getTextureState1());

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
        Open::getInstance()->Finish::onShow();

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
      nullptr
    )
  );

  this->getChildByName("plate")->runAction(
    Sequence::create(
      DelayTime::create(0.7),
      EaseSineIn::create(
        MoveBy::create(0.2, Vec3(0.0, 0.6, 0.0))
      ),
      nullptr
    )
  );

  this->getChildByName("plate")->runAction(
    RepeatForever::create(
      Sequence::create(
        RotateBy::create(0.5, Vec3(0.0, 30.0, 0.0)),
        nullptr
      )
    )
  );

  Sound->play("open");
}
