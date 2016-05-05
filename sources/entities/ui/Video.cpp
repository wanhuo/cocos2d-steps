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
: Button3D("video.obj", parent)
{
  this->element = new Element(this);

  this->setTexture("ui/video-texture.png");
}

Video::~Video()
{
}

/**
 *
 *
 *
 */
void Video::onCreate()
{
  Button3D::onCreate();

  /**
   *
   *
   *
   */
  this->setScale(0);

  this->setPosition3D(Vec3(0, -0.7, -3.0));
  this->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->camera->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->camera->setRotation3D(Vec3(0.0, 0.0, 0.0));

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

  /*this->runAction(
    Sequence::create(
      RotateBy::create(0.4, Vec3(0.0, 90.0, 0.0)),
      CallFunc::create([=] () {
      this->runAction(
        RepeatForever::create(
          Sequence::create(
            RotateBy::create(3.0, Vec3(0.0, 30.0, 0.0)),
            RotateBy::create(3.0, Vec3(0.0, -30.0, 0.0)),
            nullptr
          )
        )
      );
      }),
      nullptr
    )
  );*/

  this->element->_create();

  this->setCameraMask(this->index);
}

void Video::onDestroy(bool action)
{
  Button3D::onDestroy(action);
}

/**
 *
 *
 *
 */
void Video::onTouch(cocos2d::Touch* touch, Event* e)
{
  Button3D::onTouch(touch, e);

  /**
   *
   *
   *
   */
  Heyzap::show(Config::AD_TYPE_VIDEO, [=] (bool state) {
    Application->parameters.elapsed.ad = 0;

    this->element->setAnimation(this->element->animations.click);

    if(state)
    {
      // Add reward.
    }
  });

  Analytics::sendEvent("Application", "application.events.onVideoButtonPressed", "Application onVideoButtonPressed event");
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

Video::Element::Element(Node* parent)
: Spine("video.json", "video.atlas", 1.0, parent)
{
  this->animations.animation = {1, "animation", true};
  this->animations.click = {2, "click", false};

  this->setContentSize(Size(200, 200));
}

Video::Element::~Element()
{
}

/**
 *
 *
 *
 */
void Video::Element::onCreate()
{
  Spine::onCreate();

  /**
   *
   *
   *
   */
  this->setScale(0.003);
  this->setPosition(0, 0.6);

  this->setAnimation(this->animations.animation);
}

void Video::Element::onDestroy(bool action)
{
  Spine::onDestroy(action);
}
