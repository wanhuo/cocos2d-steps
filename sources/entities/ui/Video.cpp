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
  this->setRotation3D(Vec3(0.0, -15.0, 0.0));

  this->camera->setPosition3D(Vec3(0.0, 0.0, 0.0));
  this->camera->setRotation3D(Vec3(0.0, 0.0, 0.0));

  this->runAction(
    Sequence::create(
      ScaleTo::create(0.4, 1.0),
      nullptr
    )
  );

  this->runAction(
    Sequence::create(
      DelayTime::create(0.4),
      CallFunc::create([=] () {
      this->runAction(
        RepeatForever::create(
          Sequence::create(
            RotateBy::create(2.0, Vec3(0.0, 30.0, 0.0)),
            RotateBy::create(2.0, Vec3(0.0, -30.0, 0.0)),
            nullptr
          )
        )
      );
      }),
      nullptr
    )
  );

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
    Application->counter->add(30);

    this->_destroy();
    Watch::getInstance()->background->setOpacity(0);
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
: Spine("video.json", "video.atlas", 1.0)
{
  this->plane = new Entity3D(parent, true);
  this->plane->setPosition3D(Vec3(0.0, 0.0, 0.25));

  this->animations.animation = {1, "animation", true};

  this->plane->addChild(this);
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
  this->setScale(0.0025);
  this->setPosition(0, 0.643567);

  this->setAnimation(this->animations.animation);
}

void Video::Element::onDestroy(bool action)
{
  Spine::onDestroy(action);
}
