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
EnvironmentStoreBar::EnvironmentStoreBar()
: Background(Application)
{
  Application->environment->store.characters.plane = cocos2d::ui::ListView::create();
  Application->environment->store.characters.plane->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
  Application->environment->store.characters.plane->setBounceEnabled(true);
  Application->environment->store.characters.plane->setScrollBarEnabled(false);
  Application->environment->store.characters.plane->setContentSize(Size(21, 42));
  Application->environment->store.characters.plane->setMagneticType(cocos2d::ui::ListView::MagneticType::CENTER);
  Application->environment->store.characters.plane->ScrollView::addEventListener([this](Ref* ref, cocos2d::ui::ScrollView::EventType eventType) {
    long index = Application->environment->store.characters.plane->getIndex(Application->environment->store.characters.plane->getCenterItemInCurrentView());

    /**
     *
     *
     *
     */
    for(auto element : Application->environment->store.characters.elements)
    {
      if(index != element->parameters.index - 1)
      {
        element->changePosition(EnvironmentStoreItem::Position::POSITION_NORMAL);
      }
    }

    Application->environment->store.characters.elements.at(index)->changePosition(EnvironmentStoreItem::Position::POSITION_UP);
    Application->environment->parameters.texture = index + 1;
  });
  Application->environment->store.characters.plane->_destroy();
  Application->environment->plane->addChild(Application->environment->store.characters.plane);

  Application->environment->store.textures.plane = cocos2d::ui::ListView::create();
  Application->environment->store.textures.plane->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
  Application->environment->store.textures.plane->setBounceEnabled(true);
  Application->environment->store.textures.plane->setScrollBarEnabled(false);
  Application->environment->store.textures.plane->setContentSize(Size(21, 42));
  Application->environment->store.textures.plane->setMagneticType(cocos2d::ui::ListView::MagneticType::CENTER);
  Application->environment->store.textures.plane->ScrollView::addEventListener([this](Ref* ref, cocos2d::ui::ScrollView::EventType eventType) {
    long index = Application->environment->store.textures.plane->getIndex(Application->environment->store.textures.plane->getCenterItemInCurrentView());

    /**
     *
     *
     *
     */
    for(auto element : Application->environment->store.textures.elements)
    {
      if(index != element->parameters.index - 1)
      {
        element->changePosition(EnvironmentStoreItem::Position::POSITION_NORMAL);
      }
    }

    if(Application->environment->store.textures.elements.at(index)->position == EnvironmentStoreItem::Position::POSITION_NORMAL)
    {
      switch(index)
      {
        case 0:
        Application->environment->parameters.texture = Application->environment->store.controller->randomTexture();
        break;
        default:
        Application->environment->parameters.texture = index + 1;
        break;
      }

      Application->environment->ground->reset();
    }

    Application->environment->store.textures.elements.at(index)->changePosition(EnvironmentStoreItem::Position::POSITION_UP);
  });
  Application->environment->store.textures.plane->_destroy();
  Application->environment->plane->addChild(Application->environment->store.textures.plane);

  this->characters = new EnvironmentStoreBarButtonCharacters(this);
  this->textures = new EnvironmentStoreBarButtonTextures(this);

  this->setPosition(Application->getWidth() / 2, Application->getHeight() - 300);

  this->_destroy();
}

EnvironmentStoreBar::~EnvironmentStoreBar()
{
}

/**
 *
 *
 *
 */
void EnvironmentStoreBar::onCreate()
{
  Background::onCreate();

  this->onChange(0);

  this->characters->_create();
  this->textures->_create();

  Application->environment->character->_destroy();
  Application->environment->plates.normal->clear();

  this->setCameraMask(4);
}

void EnvironmentStoreBar::onDestroy(bool action)
{
  Background::onDestroy(action);

  /**
   *
   *
   *
   */
  this->characters->_destroy();
  this->textures->_destroy();
}

/**
 *
 *
 *
 */
void EnvironmentStoreBar::onCreateCharacters()
{
  for(auto element : Application->environment->store.characters.elements) element->_create()->setPosition3D(Vec3(0.0, 0.75, 0.75));

  Application->environment->store.characters.plane->_create();
  Application->environment->store.characters.plane->setPosition3D(Vec3(-9.75, -12, 0.0));

  Application->environment->store.characters.plane->getInnerContainer()->stopAllActions();
  Application->environment->store.characters.plane->getInnerContainer()->setPositionX(20.0);
  Application->environment->store.characters.plane->getInnerContainer()->runAction(
    Sequence::create(
      MoveTo::create(0.5, Vec3(9.0 - 3.0 * 0, 0.0, 0.0)),
      CallFunc::create([=] () {
      Application->environment->store.characters.plane->ScrollView::_eventCallback(Application->environment->store.characters.plane, cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED);
      }),
      nullptr
    )
  );

  Application->environment->store.textures.plane->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.5, Vec3(0, 0, 10))
      ),
      CallFunc::create([=] () {
      for(auto element : Application->environment->store.textures.elements) element->_destroy();
      Application->environment->store.textures.plane->_destroy();
      }),
      nullptr
    )
  );

  this->characters->setOpacity(255);
  this->textures->setOpacity(155);
}

void EnvironmentStoreBar::onCreateTextures()
{
  for(auto element : Application->environment->store.textures.elements) element->_create()->setPosition3D(Vec3(0.0, 0.75, 0.75));

  Application->environment->store.textures.plane->_create();
  Application->environment->store.textures.plane->setPosition3D(Vec3(-9.75, -12, 0.0));

  Application->environment->store.textures.plane->getInnerContainer()->stopAllActions();
  Application->environment->store.textures.plane->getInnerContainer()->setPositionX(20.0);
  Application->environment->store.textures.plane->getInnerContainer()->runAction(
    Sequence::create(
      MoveTo::create(0.5, Vec3(9.0 - 3.0 * 0, 0.0, 0.0)),
      CallFunc::create([=] () {
      Application->environment->store.textures.plane->ScrollView::_eventCallback(Application->environment->store.textures.plane, cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED);
      }),
      nullptr
    )
  );

  Application->environment->store.characters.plane->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.5, Vec3(0, 0, 10))
      ),
      CallFunc::create([=] () {
      for(auto element : Application->environment->store.characters.elements) element->_destroy();
      Application->environment->store.characters.plane->_destroy();
      }),
      nullptr
    )
  );

  this->characters->setOpacity(155);
  this->textures->setOpacity(255);

  for(auto element : Application->environment->store.textures.elements) element->_create()->setPosition3D(Vec3(0.0, 0.4, 0.75));
}

/**
 *
 *
 *
 */
void EnvironmentStoreBar::onChange(int index)
{
  this->index = index;

  switch(this->index)
  {
    case 0:
    this->onCreateCharacters();
    break;
    case 1:
    this->onCreateTextures();
    break;
  }
}

/**
 *
 *
 *
 */
int EnvironmentStoreBar::randomCharacter()
{
  vector<EnvironmentStoreItem*> candidates;

  for(auto element : Application->environment->store.characters.elements)
  {
    if(element->parameters.index > 1)
    {
      if(element->state == EnvironmentStoreItem::STATE_UNLOCKED || element->state == EnvironmentStoreItem::STATE_SELECTED)
      {
        candidates.push_back(element);
      }
    }
  }

  if(candidates.size())
  {
    return candidates.at(random(0, (int) candidates.size() - 1))->parameters.index;
  }

  return 0;
}

int EnvironmentStoreBar::randomTexture()
{
  vector<EnvironmentStoreItem*> candidates;

  for(auto element : Application->environment->store.textures.elements)
  {
    if(element->parameters.index > 1)
    {
      if(element->state == EnvironmentStoreItem::STATE_UNLOCKED || element->state == EnvironmentStoreItem::STATE_SELECTED)
      {
        candidates.push_back(element);
      }
    }
  }

  if(candidates.size())
  {
    return candidates.at(random(0, (int) candidates.size() - 1))->parameters.index;
  }

  return 0;
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

EnvironmentStoreBar::EnvironmentStoreBarButton::EnvironmentStoreBarButton(Node* parent)
: BackgroundColor(parent, Color4B(255.0, 255.0, 255.0, 255.0))
{
  this->setContentSize(Size(300, 50));
  this->setCascadeOpacityEnabled(false);

  this->bind(true);

  this->_destroy();
}

EnvironmentStoreBar::EnvironmentStoreBarButton::~EnvironmentStoreBarButton()
{
}

/**
 *
 *
 *
 */
void EnvironmentStoreBar::EnvironmentStoreBarButton::onEnter()
{
  BackgroundColor::onEnter();
}

void EnvironmentStoreBar::EnvironmentStoreBarButton::onExit()
{
  BackgroundColor::onExit();
}

/**
 *
 *
 *
 */
void EnvironmentStoreBar::EnvironmentStoreBarButton::onTouchStart(cocos2d::Touch* touch, Event* e)
{
  BackgroundColor::onTouchStart(touch, e);
}

void EnvironmentStoreBar::EnvironmentStoreBarButton::onTouchFinish(cocos2d::Touch* touch, Event* e)
{
  BackgroundColor::onTouchFinish(touch, e);
}

void EnvironmentStoreBar::EnvironmentStoreBarButton::onTouchCancelled(cocos2d::Touch* touch, Event* e)
{
  BackgroundColor::onTouchCancelled(touch, e);
}

/**
 *
 *
 *
 */
void EnvironmentStoreBar::EnvironmentStoreBarButton::onTouch(cocos2d::Touch* touch, Event* e)
{
  if(!Application->environment->store.characters.plane->numberOfRunningActions() && !Application->environment->store.textures.plane->numberOfRunningActions())
  {
    if(Application->environment->store.controller->index != this->index)
    {
      Sound->play("touch");

      /**
       *
       *
       *
       */
      Application->environment->store.controller->onChange(this->index);
    }
  }
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

EnvironmentStoreBar::EnvironmentStoreBarButtonCharacters::EnvironmentStoreBarButtonCharacters(Node* parent)
: EnvironmentStoreBarButton(parent)
{
  this->text = new Text("store-characters", this, true);
  this->text->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
  this->text->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);

  this->setPosition(-300, 0);

  this->index = 0;
}

EnvironmentStoreBar::EnvironmentStoreBarButtonCharacters::~EnvironmentStoreBarButtonCharacters()
{
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

EnvironmentStoreBar::EnvironmentStoreBarButtonTextures::EnvironmentStoreBarButtonTextures(Node* parent)
: EnvironmentStoreBarButton(parent)
{
  this->text = new Text("store-textures", this, true);
  this->text->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
  this->text->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);

  this->setPosition(0, 0);

  this->index = 1;
}

EnvironmentStoreBar::EnvironmentStoreBarButtonTextures::~EnvironmentStoreBarButtonTextures()
{
}
