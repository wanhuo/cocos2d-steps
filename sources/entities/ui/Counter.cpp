/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2015 by Igor Mats
 * http://www.tooflya.com/development/
 *
 *
 * License: Tooflya Inc. Software License v1.
 *
 * Licensee may not use this software for commercial purposes. For the purpose of this license,
 * commercial purposes means that a 3rd party has to pay in order to access Software or that
 * the Website that runs Software is behind a paywall. In consideration of the License granted
 * under clause 2, Licensee shall pay Licensor a fee, via Credit-Card, PayPal or any other
 * mean which Licensor may deem adequate. Failure to perform payment shall construe as material
 * breach of this Agreement. This software is provided under an AS-IS basis and without any support,
 * updates or maintenance. Nothing in this Agreement shall require Licensor to provide Licensee with
 * support or fixes to any bug, failure, mis-performance or other defect in The Software.
 *
 * @cocos2d
 *
 */

#include "Game.h"

/**
 *
 *
 *
 */
Counter::Counter(Node* parent)
: Background(parent)
{
  this->holder = new BackgroundColor(this, Color4B::RED);
  this->holder->setContentSize(Size(0, 0));
  this->holder->setCascadeOpacityEnabled(true);

  this->starBackground = new Entity("counter-star.png", this->holder);
  this->starBackground->setPosition(0, -80);
  this->starBackground->setPosition(0, 25);
  this->starBackground->setCascadeOpacityEnabled(true);
  this->starBackground->setOpacity(0);
  this->starBackground->setScale(1.5);

  this->bonusBackground = new Entity("counter-bonus.png", this->holder);
  this->bonusBackground->setPosition(0, -80);
  this->bonusBackground->setCascadeOpacityEnabled(true);
  this->bonusBackground->setOpacity(0);
  this->bonusBackground->setScale(1.5);
  //this->bonusBackground->setColor(Color3B(252.0, 225.0, 105.0));

  this->starAction = ProgressTimer::create(new Entity("counter-star.png"));
  this->starAction->setType(ProgressTimer::Type::RADIAL);
  this->starBackground->addChild(this->starAction);
  this->starAction->getSprite()->setOpacity(150);
  this->starAction->getSprite()->setScale(0.8);
  this->starAction->setPosition(this->starBackground->getWidth() / 2, this->starBackground->getHeight() / 2);

  this->icon = new CameraEntity3D("diamond.obj", Application, true,
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
  this->icon->setTexture(Application->environment->getTextureState1());
  this->icon->setPosition3D(Vec3(Application->getFrustumWidth() - 0.4, Application->getFrustumHeight() - 0.7, 0));
  this->icon->setRotation3D(Vec3(0, 0, 0));
  this->icon->setColor(Color3B(0.0, 243.0, 120.0));
  this->icon->runAction(
    RepeatForever::create(
      RotateBy::create(1.0, Vec3(0, 100, 0))
    )
  );

  this->texts.name = new Text("name", this, true);
  this->texts.stage = new Text("stage", this, true);
  this->texts.score = new Text("counter-score", this->holder, true);
  this->texts.coins = new Text("counter-coins", this, true);
  this->texts.best = new Text("counter-best", this, true);
  this->texts.bonus = new Text("counter-bonus", this->bonusBackground, true);

  this->texts.name->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -10), 0);
  this->texts.stage->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);
  this->texts.score->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);
  this->texts.best->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);
  this->texts.coins->enableShadow(Color4B(71.0, 132.0, 164.0, 255.0), Size(0, -3), 0);

  this->texts.best->setPosition(Application->getCenter().x, Application->getHeight() - 300);

  this->holder->setOpacity(0);
  this->texts.stage->setOpacity(0);
  this->texts.best->setOpacity(0);

  this->setCameraMask(4);

  this->holder->setPosition(Application->getCenter().x, Application->getHeight() - 200);
  this->texts.name->setPosition(Application->getCenter().x, Application->getHeight() - 300);
  this->texts.score->setPosition(0, 0);
  this->texts.bonus->setPosition(this->bonusBackground->getWidth() / 2, this->bonusBackground->getHeight() / 2 - 12);

  this->reset(true);

  this->icon->setGlobalZOrder(100);
  this->texts.score->setGlobalZOrder(100);
  this->texts.best->setGlobalZOrder(100);
  this->texts.coins->setGlobalZOrder(100);
  this->texts.stage->setGlobalZOrder(100);
}

Counter::~Counter()
{
}

/**
 *
 *
 *
 */
void Counter::onMenu()
{
  this->update();

  this->holder->runAction(
    FadeTo::create(0.2, 0)
  );

  this->texts.name->runAction(
    FadeTo::create(0.2, 255)
  );

  this->texts.best->runAction(
    FadeTo::create(0.2, 0)
  );

  this->texts.stage->runAction(
    FadeTo::create(0.2, 0)
  );
}

void Counter::onGame()
{
  this->texts.stage->setOpacity(0);
  this->bonusBackground->setOpacity(0);

  if(!Application->environment->generator->bonus)
  {
    this->texts.stage->setText("stage");
    this->texts.stage->data(Application->environment->parameters.stage);

    this->texts.stage->setPosition(Application->getCenter().x, Application->getHeight() - 370);

    this->runAction(
      Sequence::create(
        CallFunc::create([=] () {
          this->texts.stage->runAction(
            Sequence::create(
              DelayTime::create(1.0),
              FadeOut::create(0.2),
              nullptr
            )
          );
        }),
        nullptr
      )
    );

    this->bonusBackground->stopAllActions();
    this->bonusBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 255),
        Sequence::create(
          CallFunc::create([=] () {
            this->bonusBackground->setVisible(true);
          }),
          MoveTo::create(0.2, Vec2(0, -80)),
          nullptr
        ),
        nullptr
      )
    );

    this->holder->runAction(
      FadeTo::create(0.2, 255)
    );
  }

  this->texts.stage->runAction(
    FadeTo::create(0.2, 255)
  );

  this->update();

  this->texts.name->runAction(
    FadeTo::create(0.2, 0)
  );
}

void Counter::onFinish()
{
  if(Application->state != Game::FINISH)
  {
    this->bonusBackground->stopAllActions();
    this->bonusBackground->setOpacity(0);
    this->holder->stopAllActions();
    this->holder->setOpacity(0);
    this->texts.stage->stopAllActions();
    this->texts.stage->setOpacity(0);

    this->onStarFinish();

    if(!Application->environment->generator->bonus)
    {
      this->onGame();
    }
    else
    {
      this->texts.stage->setText("stage-bonus");
      this->texts.stage->setPosition(Application->getCenter().x, Application->getHeight() - 200);
    }

    this->texts.stage->runAction(
      FadeTo::create(0.2, 255)
    );
  }
}

void Counter::onLose()
{
  this->stopAllActions();

  this->texts.stage->runAction(
    FadeOut::create(0.2)
  );

  this->bonusBackground->stopAllActions();
  this->bonusBackground->runAction(
    Spawn::create(
      FadeTo::create(0.2, 0),
      Sequence::create(
        MoveTo::create(0.2, Vec2(0, 0)),
        CallFunc::create([=] () {
          this->bonusBackground->setVisible(false);
        }),
        nullptr
      ),
      nullptr
    )
  );

  this->update();

  this->holder->runAction(
    FadeTo::create(0.2, 255)
  );

  if(true)
  {
    this->onBest();
  }
  else
  {
    this->onRegular();
  }
}

void Counter::onStore()
{
  this->texts.name->runAction(
    FadeTo::create(0.2, 0)
  );
}

void Counter::onMissions()
{
}

void Counter::onPresent()
{
}

void Counter::onOpen()
{
}

void Counter::onWatch()
{
}

/**
 *
 *
 *
 */
void Counter::onStarStart()
{
  if(this->bonusBackground->isVisible())
  {
    this->bonusBackground->stopAllActions();
    this->bonusBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 0),
        Sequence::create(
          MoveTo::create(0.2, Vec2(0, 0)),
          CallFunc::create([=] () {
            this->bonusBackground->setVisible(false);

            this->starBackground->stopAllActions();
            this->starBackground->runAction(
              Spawn::create(
                FadeTo::create(0.2, 150),
                Sequence::create(
                  CallFunc::create([=] () {
                    this->starBackground->setVisible(true);
                  }),
                  MoveTo::create(0.2, Vec2(0, -80)),
                  nullptr
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
  }
  else
  {
  }
}

void Counter::onStarFinish()
{
  if(Application->environment->generator->bonus)
  {
    this->starBackground->stopAllActions();
    this->starBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 0),
        Sequence::create(
          CallFunc::create([=] () {
            this->starBackground->setVisible(false);
          }),
          MoveTo::create(0.2, Vec2(0, 0)),
          nullptr
        ),
        nullptr
      )
    );
  }
  else
  {
    this->starBackground->stopAllActions();
    this->starBackground->runAction(
      Spawn::create(
        FadeTo::create(0.2, 0),
        Sequence::create(
          MoveTo::create(0.2, Vec2(0, 0)),
          CallFunc::create([=] () {
            this->starBackground->setVisible(false);

            if(Application->state == Game::GAME)
            {
              this->bonusBackground->stopAllActions();
              this->bonusBackground->runAction(
                Spawn::create(
                  FadeTo::create(0.2, 255),
                  Sequence::create(
                    CallFunc::create([=] () {
                      this->bonusBackground->setVisible(true);
                    }),
                    MoveTo::create(0.2, Vec2(0, -80)),
                    nullptr
                  ),
                  nullptr
                )
              );
            }
          }),
          nullptr
        ),
        nullptr
      )
    );
  }
}

void Counter::onStarUpdate()
{
  this->starAction->setPercentage(Application->environment->starTimeElapsed / Application->environment->starTime * 100);
}

/**
 *
 *
 *
 */
void Counter::onCount()
{
  if(!Application->environment->generator->bonus)
  {
    this->values.start += (Application->environment->star ? 2 : 1);
    this->values.current += (Application->environment->star ? 2 : 1);

    if(Application->environment->star)
    {
      Application->environment->generator->general++;
    }

    if(this->values.current > this->values.best)
    {
      if(!this->values.newBest && this->values.best > 1)
      {
        Sound->play("best");
      }

      this->values.best = this->values.current;
      this->values.newBest = true;
    }

    this->update();
  }
}

void Counter::onCoins()
{
  this->values.coins++;

  this->update();
}

/**
 *
 *
 *
 */
void Counter::onBest()
{
  this->texts.stage->setText("stage");
  this->texts.stage->data(Application->environment->parameters.stage);

 this->texts.stage->setPosition(Application->getCenter().x, Application->getHeight() - 370);

  this->texts.stage->runAction(
    FadeTo::create(0.2, 255)
  );

  this->texts.best->runAction(
    FadeTo::create(0.2, 255)
  );
}

void Counter::onRegular()
{
}

/**
 *
 *
 *
 */
void Counter::reset(bool init)
{
  this->values.newBest = false;

  this->values.start = 0;
  this->values.current = 1;

  if(init)
  {
    this->values.best = Storage::get("application.score.best");
    this->values.coins = Storage::get("application.coins");
  }
}

void Counter::save()
{
  if(Application->environment->generator->bonus)
  {
    Storage::set("generator.bonus.skip." + to_string(Application->environment->parameters.stage), max(Storage::get("generator.bonus.skip." + to_string(Application->environment->parameters.stage)), Application->environment->character->plates.current->getIndex()));
  }

  if(this->values.newBest)
  {
    Sound->play("best");
  }

  Storage::set("application.score.best", this->values.best);
  Storage::set("application.coins", this->values.coins);
  Storage::set("character.color", 1);
  Storage::set("character.color.r", Application->environment->character->getColor().r);
  Storage::set("character.color.g", Application->environment->character->getColor().g);
  Storage::set("character.color.b", Application->environment->character->getColor().b);

  Analytics::sendEvent("Application", "application.events.onLose", ("User is lost: (" + patch::to_string(this->values.current) + "/" + patch::to_string(this->values.best) + ")").c_str());
}

/**
 *
 *
 *
 */
void Counter::add(int count)
{
  this->values.coins += count;
  this->count.add += count;

  this->runAction(
    Repeat::create(
      Sequence::create(
        CallFunc::create([=] () {
          this->count.add--;

          this->update();
        }),
        DelayTime::create(0.01),
        nullptr
      ),
      count
    )
  );
}

void Counter::remove(int count)
{
  this->values.coins -= count;
  this->count.remove += count;

  this->runAction(
    Repeat::create(
      Sequence::create(
        CallFunc::create([=] () {
          this->count.remove--;

          this->update();
        }),
        DelayTime::create(0.01),
        nullptr
      ),
      count
    )
  );
}

/**
 *
 *
 *
 */
void Counter::update()
{
  this->texts.bonus->data(Application->environment->generator->size - (Application->environment->character->plates.current ? Application->environment->character->plates.current->getIndex() : 0));
  this->texts.score->data(this->values.current);
  this->texts.best->data(this->values.best);
  this->texts.coins->data(this->values.coins - this->count.add + this->count.remove);
  this->texts.coins->setPosition(Application->getWidth() - this->texts.coins->getWidth() / 2 - 60, Application->getHeight() - 60);
}
