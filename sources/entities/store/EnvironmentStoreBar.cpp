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
  this->buttons.play = new Button("play-button.png", 2, 1, this, std::bind([=] () {
    Application->counter->save();

    Application->s->runAction(
      Sequence::create(
        FadeIn::create(0.2),
        CallFunc::create([=] () {
        Application->changeState(Game::MENU);
        }),
        FadeOut::create(0.2),
        nullptr
      )
    );
  }), true);
  this->buttons.facebook = new Button("lock-facebook-button.png", 2, 1, this, std::bind([=] () {
    Application->onLike();

    Application->runAction(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        this->selectedCharacter->position = EnvironmentStoreItem::Position::POSITION_NORMAL;

        this->selectedCharacter->changeState(EnvironmentStoreItem::STATE_UNLOCKED);
        this->onSelectCharacter(this->selectedCharacter->parameters.index - 1);
        }),
        nullptr
      )
    );
  }), true);
  this->buttons.twitter = new Button("lock-twitter-button.png", 2, 1, this, std::bind([=] () {
    Application->onTwitter();

    Application->runAction(
      Sequence::create(
        DelayTime::create(0.5),
        CallFunc::create([=] () {
        this->selectedCharacter->position = EnvironmentStoreItem::Position::POSITION_NORMAL;

        this->selectedCharacter->changeState(EnvironmentStoreItem::STATE_UNLOCKED);
        this->onSelectCharacter(this->selectedCharacter->parameters.index - 1);
        }),
        nullptr
      )
    );
  }), true);
  this->buttons.lock = new Button("lock-button.png", 2, 1, this, std::bind([=] () {
  }), true);

  this->buttons.play->setPosition(0, -700);
  this->buttons.lock->setPosition(0, -700);
  this->buttons.facebook->setPosition(0, -700);
  this->buttons.twitter->setPosition(0, -700);

  this->buttons.play->setCameraMask(4);
  this->buttons.lock->setCameraMask(4);
  this->buttons.facebook->setCameraMask(4);
  this->buttons.twitter->setCameraMask(4);

  this->buttons.play->setVisible(false);
  this->buttons.lock->setVisible(false);
  this->buttons.facebook->setVisible(false);
  this->buttons.twitter->setVisible(false);

  this->backgrounds.missions = new Background(this);
  this->backgrounds.diamonds = new Background(this);
  this->backgrounds.random = new Background(this);
  this->backgrounds.facebook = new Background(this);

  this->texts.missions = new Text("store-state-1", this->backgrounds.missions, true);
  this->texts.diamonds = new Text("store-state-2", this->backgrounds.diamonds, true);
  this->texts.facebook = new Text("store-state-3", this->backgrounds.facebook, true);
  this->texts.random = new Text("store-random", this->backgrounds.random, true);

  this->texts.missions->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);
  this->texts.diamonds->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);
  this->texts.facebook->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);
  this->texts.random->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);

  this->backgrounds.missions->setPosition(0, -100);
  this->backgrounds.diamonds->setPosition(0, -100);
  this->backgrounds.facebook->setPosition(0, -100);
  this->backgrounds.random->setPosition(0, -100);

  this->backgrounds.missions->setCameraMask(4);
  this->backgrounds.diamonds->setCameraMask(4);
  this->backgrounds.facebook->setCameraMask(4);
  this->backgrounds.random->setCameraMask(4);

  this->backgrounds.missions->setVisible(false);
  this->backgrounds.diamonds->setVisible(false);
  this->backgrounds.facebook->setVisible(false);
  this->backgrounds.random->setVisible(false);

  this->texts.diamonds->setPosition(-20, 0);

  this->diamond = new CameraEntity3D("diamond.obj", Application, true,
  {
    Camera::createOrthographic(Application->getFrustumWidth(), Application->getFrustumHeight(), 1, 100),
    Vec3(0, 0, 2),
    Vec3(0, 0, 0),
    Application,
    3
  },
  {
    {DirectionLight::create(Vec3(1.0, -1.0, -1.0), Color3B(200, 200, 200)), Application},
    {AmbientLight::create(Color3B(120, 120, 120)), Application}
  });
  this->diamond->setTexture(Application->environment->getTextureState1());
  this->diamond->setPosition3D(Vec3(Application->getFrustumWidth() / 2 + 0.7, Application->getFrustumHeight() / 2 + 3.4, 0));
  this->diamond->setRotation3D(Vec3(0, 0, 0));
  this->diamond->setColor(Color3B(0.0, 243.0, 120.0));
  this->diamond->setScale(0.7);
  this->diamond->setVisible(false);
  this->diamond->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0, 100, 0))
    )
  );

  Application->environment->store.characters.plane = cocos2d::ui::ListView::create();
  Application->environment->store.characters.plane->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
  Application->environment->store.characters.plane->setBounceEnabled(true);
  Application->environment->store.characters.plane->setScrollBarEnabled(false);
  Application->environment->store.characters.plane->setContentSize(Size(21, 42));
  Application->environment->store.characters.plane->setMagneticType(cocos2d::ui::ListView::MagneticType::CENTER);
  Application->environment->store.characters.plane->ScrollView::addEventListener([this](Ref* ref, cocos2d::ui::ScrollView::EventType eventType) {
    int index = Application->environment->store.characters.plane->getIndex(Application->environment->store.characters.plane->getCenterItemInCurrentView());

    /**
     *
     *
     *
     */
    this->onSelectCharacter(index);
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
    int index = Application->environment->store.textures.plane->getIndex(Application->environment->store.textures.plane->getCenterItemInCurrentView());

    /**
     *
     *
     *
     */
    this->onSelectTexture(index);
  });
  Application->environment->store.textures.plane->_destroy();
  Application->environment->plane->addChild(Application->environment->store.textures.plane);

  this->characters = new EnvironmentStoreBarButtonCharacters(this);
  this->textures = new EnvironmentStoreBarButtonTextures(this);
  this->toogle = new EnvironmentStoreBarButton(this);

  this->toogle->bind(false);
  this->toogle->setColor(Color3B(95.0, 165.0, 196.0));

  this->characters->setColor(Color3B(71.0, 132.0, 164.0));
  this->textures->setColor(Color3B(71.0, 132.0, 164.0));

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
  Application->environment->store.characters.plane->_destroy(action);
  Application->environment->store.textures.plane->_destroy(action);
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

  Application->environment->store.characters.plane->stopAutoScroll();
  Application->environment->store.characters.plane->stopAllActions();
  Application->environment->store.characters.plane->getInnerContainer()->stopAllActions();
  Application->environment->store.characters.plane->getInnerContainer()->setPositionX(20.0);
  Application->environment->store.characters.plane->getInnerContainer()->runAction(
    Sequence::create(
      MoveTo::create(0.5, Vec3(9.0 - 3.0 * (Application->environment->parameters.random.character ? 0 : Application->environment->parameters.character - 1), 0.0, 0.0)),
      CallFunc::create([=] () {
      Application->environment->store.characters.plane->ScrollView::_eventCallback(Application->environment->store.characters.plane, cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED);
      }),
      nullptr
    )
  );

  Application->environment->store.textures.plane->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.5, Vec3(0, 0, 20))
      ),
      CallFunc::create([=] () {
      for(auto element : Application->environment->store.textures.elements) element->_destroy();
      Application->environment->store.textures.plane->_destroy();
      }),
      nullptr
    )
  );

  this->toogle->runAction(
    MoveTo::create(0.2, Vec2(-300.0, 0.0))
  );
}

void EnvironmentStoreBar::onCreateTextures()
{
  for(auto element : Application->environment->store.textures.elements) element->_create()->setPosition3D(Vec3(0.0, 0.75, 0.75));

  Application->environment->store.textures.plane->_create();
  Application->environment->store.textures.plane->setPosition3D(Vec3(-9.75, -12, 0.0));

  Application->environment->store.textures.plane->stopAutoScroll();
  Application->environment->store.textures.plane->stopAllActions();
  Application->environment->store.textures.plane->getInnerContainer()->stopAllActions();
  Application->environment->store.textures.plane->getInnerContainer()->setPositionX(20.0);
  Application->environment->store.textures.plane->getInnerContainer()->runAction(
    Sequence::create(
      MoveTo::create(0.5, Vec3(9.0 - 3.0 * (Application->environment->parameters.random.texture ? 0 : Application->environment->parameters.texture - 1), 0.0, 0.0)),
      CallFunc::create([=] () {
      Application->environment->store.textures.plane->ScrollView::_eventCallback(Application->environment->store.textures.plane, cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED);
      }),
      nullptr
    )
  );

  Application->environment->store.characters.plane->runAction(
    Sequence::create(
      EaseSineOut::create(
        MoveBy::create(0.5, Vec3(0, 0, 20))
      ),
      CallFunc::create([=] () {
      for(auto element : Application->environment->store.characters.elements) element->_destroy();
      Application->environment->store.characters.plane->_destroy();
      }),
      nullptr
    )
  );

  this->toogle->runAction(
    MoveTo::create(0.2, Vec2(0.0, 0.0))
  );

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
void EnvironmentStoreBar::onSelect(EnvironmentStoreItem* element)
{
  this->buttons.play->setVisible(false);
  this->buttons.lock->setVisible(false);
  this->buttons.facebook->setVisible(false);
  this->buttons.twitter->setVisible(false);

  switch(element->state)
  {
    case EnvironmentStoreItem::STATE_UNLOCKED:
    this->buttons.play->setVisible(true);
    break;
    case EnvironmentStoreItem::STATE_MISSIONS:
    this->buttons.lock->setVisible(true);
    break;
    case EnvironmentStoreItem::STATE_DIAMONDS:
    this->buttons.lock->setVisible(true);
    break;
    case EnvironmentStoreItem::STATE_FACEBOOK:
    this->buttons.facebook->setVisible(true);
    break;
    case EnvironmentStoreItem::STATE_TWITTER:
    this->buttons.twitter->setVisible(true);
    break;
  }

  this->backgrounds.missions->setVisible(false);
  this->backgrounds.diamonds->setVisible(false);
  this->backgrounds.facebook->setVisible(false);
  this->backgrounds.random->setVisible(false);

  this->diamond->setVisible(false);

  switch(element->state)
  {
    case EnvironmentStoreItem::STATE_UNLOCKED:
    break;
    case EnvironmentStoreItem::STATE_MISSIONS:
    this->backgrounds.missions->setVisible(true);
    this->texts.missions->data(element->parameters.missions);
    break;
    case EnvironmentStoreItem::STATE_DIAMONDS:
    this->diamond->setVisible(true);

    this->backgrounds.diamonds->setVisible(true);
    this->texts.diamonds->data(element->parameters.diamonds);
    break;
    case EnvironmentStoreItem::STATE_FACEBOOK:
    this->backgrounds.facebook->setVisible(true);
    break;
  }

  if(element->parameters.index == 1)
  {
    this->backgrounds.random->setVisible(true);
  }

  element->changePosition(EnvironmentStoreItem::Position::POSITION_UP);
}

void EnvironmentStoreBar::onSelectCharacter(int index)
{
  auto element = Application->environment->store.characters.elements.at(index);

  for(auto element : Application->environment->store.characters.elements)
  {
    if(index != element->parameters.index - 1)
    {
      element->changePosition(EnvironmentStoreItem::Position::POSITION_NORMAL);
    }
  }

  if(element->position == EnvironmentStoreItem::Position::POSITION_NORMAL && element->state == EnvironmentStoreItem::STATE_UNLOCKED)
  {
    Application->environment->parameters.character = index + 1;
    Application->environment->parameters.random.character = index == 0;
  }

  this->onSelect(element);

  this->selectedCharacter = element;
}

void EnvironmentStoreBar::onSelectTexture(int index)
{
  auto element = Application->environment->store.textures.elements.at(index);

  for(auto element : Application->environment->store.textures.elements)
  {
    if(index != element->parameters.index - 1)
    {
      element->changePosition(EnvironmentStoreItem::Position::POSITION_NORMAL);
    }
  }

  if(element->position == EnvironmentStoreItem::Position::POSITION_NORMAL && element->state == EnvironmentStoreItem::STATE_UNLOCKED)
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
    Application->environment->parameters.random.texture = index == 0;
    Application->environment->ground->reset();
  }

  this->onSelect(element);

  this->selectedTexture = element;
}

/**
 *
 *
 *
 */
int EnvironmentStoreBar::randomCharacter(bool locked)
{
  vector<EnvironmentStoreItem*> candidates;

  for(auto element : Application->environment->store.characters.elements)
  {
    if(element->parameters.index > 1)
    {
      if(locked)
      {
        if(element->state == EnvironmentStoreItem::STATE_DIAMONDS && Application->counter->values.coins >= element->parameters.diamonds)
        {
          candidates.push_back(element);
        }
      }
      else
      {
        if(element->state == EnvironmentStoreItem::STATE_UNLOCKED)
        {
          candidates.push_back(element);
        }
      }
    }
  }

  if(candidates.size())
  {
    return candidates.at(random(0, (int) candidates.size() - 1))->parameters.index;
  }

  return 0;
}

int EnvironmentStoreBar::randomTexture(bool locked)
{
  vector<EnvironmentStoreItem*> candidates;

  for(auto element : Application->environment->store.textures.elements)
  {
    if(element->parameters.index > 1)
    {
      if(locked)
      {
        if(element->state == EnvironmentStoreItem::STATE_DIAMONDS && Application->counter->values.coins >= element->parameters.diamonds)
        {
          candidates.push_back(element);
        }
      }
      else
      {
        if(element->state == EnvironmentStoreItem::STATE_UNLOCKED)
        {
          candidates.push_back(element);
        }
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
 *
 *
 *
 */
EnvironmentStoreBar::Element EnvironmentStoreBar::nextElement()
{
  auto character = this->randomCharacter(true);
  auto texture = this->randomTexture(true);

  if(character && texture)
  {
    if(probably(20))
    {
      return {1, character - 1};
    }
    else
    {
      return {2, texture - 1};
    }
  }
  else
  {
    if(character) return {1, character - 1};
    if(texture) return  {2, texture - 1};
  }

  return {
    0,
    0
  };
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
  this->setContentSize(Size(300, 100));
  this->setCascadeOpacityEnabled(false);

  this->bind(true);

  this->state->create = true;
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
  if(!Director::getInstance()->getActionManager()->getNumberOfRunningActionsInTarget(Application->environment->store.controller->toogle))
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
  this->text->setGlobalZOrder(10);
  this->text->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 - 5.0);
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
  this->text->setGlobalZOrder(10);
  this->text->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2 - 5.0);
  this->text->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);

  this->setPosition(0, 0);

  this->index = 1;
}

EnvironmentStoreBar::EnvironmentStoreBarButtonTextures::~EnvironmentStoreBarButtonTextures()
{
}
