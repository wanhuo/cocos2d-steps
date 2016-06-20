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
  this->icon->setScale(0.8);
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
  this->texts.score->setPosition(0, 20);
  this->texts.bonus->setPosition(this->bonusBackground->getWidth() / 2 + 1.0, this->bonusBackground->getHeight() / 2 - 10.0);

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

  this->texts.stage->setText("stage");
  this->texts.stage->data(Application->environment->parameters.stage);

  this->texts.stage->setPosition(Application->getCenter().x, Application->getHeight() - 370);

  this->texts.stage->runAction(
    FadeTo::create(0.2, 255)
  );

  this->texts.stage->runAction(
    RepeatForever::create(
      Sequence::create(
        TintTo::create(0.5, 165.0, 196.0, 255.0),
        TintTo::create(0.5, 255, 255, 255),
        nullptr
      )
    )
  );

  this->texts.best->stopAllActions();
  this->texts.best->setScale(1.0);
  this->texts.best->runAction(
    FadeTo::create(0.2, 255)
  );

  if(this->values.b.best)
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
  this->texts.name->runAction(
    FadeTo::create(0.2, 0)
  );
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
  this->values.start += (Application->environment->star ? 2 : 1);

  if(!Application->environment->generator->bonus)
  {
    this->values.current += (Application->environment->star ? 2 : 1);

    if(Application->environment->star)
    {
      Application->environment->generator->general++;
    }

    if(this->values.current > this->values.best)
    {
      if(!this->values.b.best && this->values.best > 1)
      {
        Sound->play("best");

        /**
         *
         * @Missions
         * Update missions with best.
         *
         */
        if(MissionsFactory::getInstance()->isListenen())
        {
          Application->counter->missionUpdateOnce.points_best++;

          Events::updateMissions();
        }
      }

      this->values.best = this->values.current;
      this->values.b.best = true;
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
  this->texts.best->runAction(
    RepeatForever::create(
      Sequence::create(
        ScaleTo::create(0.25, 1.05),
        ScaleTo::create(0.25, 0.95),
        nullptr
      )
    )
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
  this->values.b.best = false;
  this->values.b.mission = false;
  this->values.b.special = false;
  this->values.b.daily = false;

  this->values.start = 0;
  this->values.current = 1;

  if(init)
  {
    this->values.best = Storage::get("application.score.best");
    this->values.coins = Storage::get("application.coins");

    this->missionUpdateProgress.coins = Storage::get("values.missions.progress.coins");
    this->missionUpdateProgress.points = Storage::get("values.missions.progress.points");
    this->missionUpdateProgress.games = Storage::get("values.missions.progress.games");
    this->missionUpdateProgress.gifts = Storage::get("values.missions.progress.gifts");

    this->missionUpdateProgress.special_progress_1 = Storage::get("values.missions.progress.special_progress_1");
    this->missionUpdateProgress.special_progress_2 = Storage::get("values.missions.progress.special_progress_2");
    this->missionUpdateProgress.special_progress_3 = Storage::get("values.missions.progress.special_progress_3");
    this->missionUpdateProgress.special_progress_4 = Storage::get("values.missions.progress.special_progress_4");
    this->missionUpdateProgress.special_progress_5 = Storage::get("values.missions.progress.special_progress_5");
    this->missionUpdateProgress.special_progress_6 = Storage::get("values.missions.progress.special_progress_6");
    this->missionUpdateProgress.special_progress_7 = Storage::get("values.missions.progress.special_progress_7");
    this->missionUpdateProgress.special_progress_8 = Storage::get("values.missions.progress.special_progress_8");
    this->missionUpdateProgress.special_progress_9 = Storage::get("values.missions.progress.special_progress_9");
    this->missionUpdateProgress.special_progress_10 = Storage::get("values.missions.progress.special_progress_10");
    this->missionUpdateProgress.special_progress_11 = Storage::get("values.missions.progress.special_progress_11");
    this->missionUpdateProgress.special_progress_12 = Storage::get("values.missions.progress.special_progress_12");
    this->missionUpdateProgress.special_progress_13 = Storage::get("values.missions.progress.special_progress_13");
    this->missionUpdateProgress.special_progress_14 = Storage::get("values.missions.progress.special_progress_14");
    this->missionUpdateProgress.special_progress_15 = Storage::get("values.missions.progress.special_progress_15");
  }
  else
  {
    this->resetOnceMissionsUpdate();
  }
}

void Counter::save()
{
  if(Application->environment->generator->bonus)
  {
    Storage::set("generator.bonus.skip." + patch::to_string(Application->environment->parameters.stage), max(Storage::get("generator.bonus.skip." + patch::to_string(Application->environment->parameters.stage)), Application->environment->character->plates.current->getIndex()));
  }

  if(this->values.b.best)
  {
    Sound->play("best");
  }

  Storage::set("application.score.best", this->values.best);
  Storage::set("application.coins", this->values.coins);
  Storage::set("character.color", 1);
  Storage::set("character.color.r", Application->environment->character->color.r);
  Storage::set("character.color.g", Application->environment->character->color.g);
  Storage::set("character.color.b", Application->environment->character->color.b);

  Storage::set("store.character.selected", Application->environment->parameters.character);
  Storage::set("store.texture.selected", Application->environment->parameters.texture);

  Storage::set("store.character.random", Application->environment->parameters.random.character);
  Storage::set("store.texture.random", Application->environment->parameters.random.texture);

  Storage::set("values.missions.progress.coins",  this->missionUpdateProgress.coins);
  Storage::set("values.missions.progress.points", this->missionUpdateProgress.points);
  Storage::set("values.missions.progress.games", this->missionUpdateProgress.points);
  Storage::set("values.missions.progress.gifts", this->missionUpdateProgress.points);

  Storage::set("values.missions.progress.special_progress_1", this->missionUpdateProgress.special_progress_1);
  Storage::set("values.missions.progress.special_progress_2", this->missionUpdateProgress.special_progress_2);
  Storage::set("values.missions.progress.special_progress_3", this->missionUpdateProgress.special_progress_3);
  Storage::set("values.missions.progress.special_progress_4", this->missionUpdateProgress.special_progress_4);
  Storage::set("values.missions.progress.special_progress_5", this->missionUpdateProgress.special_progress_5);
  Storage::set("values.missions.progress.special_progress_6", this->missionUpdateProgress.special_progress_6);
  Storage::set("values.missions.progress.special_progress_7", this->missionUpdateProgress.special_progress_7);
  Storage::set("values.missions.progress.special_progress_8", this->missionUpdateProgress.special_progress_8);
  Storage::set("values.missions.progress.special_progress_9", this->missionUpdateProgress.special_progress_9);
  Storage::set("values.missions.progress.special_progress_10", this->missionUpdateProgress.special_progress_10);
  Storage::set("values.missions.progress.special_progress_11", this->missionUpdateProgress.special_progress_11);
  Storage::set("values.missions.progress.special_progress_12", this->missionUpdateProgress.special_progress_12);
  Storage::set("values.missions.progress.special_progress_13", this->missionUpdateProgress.special_progress_13);
  Storage::set("values.missions.progress.special_progress_14", this->missionUpdateProgress.special_progress_14);
  Storage::set("values.missions.progress.special_progress_15", this->missionUpdateProgress.special_progress_15);

  Services::leaderboards->update(SERVICES_LEADERBOARD_BEST_SCORE, this->values.best);
  Services::leaderboards->update(SERVICES_LEADERBOARD_STAGES_COUNT, Application->environment->parameters.stage - 1);
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
  this->texts.coins->setPosition(Application->getWidth() - this->texts.coins->getWidth() / 2 - 50, Application->getHeight() - 50);

  Application->captures->update();
}

/**
 *
 *
 *
 */
MissionUpdate Counter::getMissionsUpdate() const
{
  MissionUpdate update;

  update.o = this->missionUpdateOnce;
  update.p = this->missionUpdateProgress;

  return update;
}

void Counter::resetMissionsUpdate()
{
  this->resetOnceMissionsUpdate();
  this->resetProgressMissionsUpdate();
}

void Counter::resetOnceMissionsUpdate()
{
  this->missionUpdateOnce.coins = 0;
  this->missionUpdateOnce.points = 0;
  this->missionUpdateOnce.points_best = this->values.best;

  this->missionUpdateOnce.special_once_1 = 0;
  this->missionUpdateOnce.special_once_2 = 0;
  this->missionUpdateOnce.special_once_3 = 0;
  this->missionUpdateOnce.special_once_4 = 0;
  this->missionUpdateOnce.special_once_5 = 0;
  this->missionUpdateOnce.special_once_6 = 0;
  this->missionUpdateOnce.special_once_7 = 0;
  this->missionUpdateOnce.special_once_8 = 0;
  this->missionUpdateOnce.special_once_9 = 0;
  this->missionUpdateOnce.special_once_10 = 0;
  this->missionUpdateOnce.special_once_11 = 0;
  this->missionUpdateOnce.special_once_12 = 0;
  this->missionUpdateOnce.special_once_13 = 0;
  this->missionUpdateOnce.special_once_14 = 0;
  this->missionUpdateOnce.special_once_15 = 0;

  Events::updateMissions();
}

void Counter::resetProgressMissionsUpdate()
{
  this->missionUpdateProgress.coins = 0;
  this->missionUpdateProgress.points = 0;
  this->missionUpdateProgress.games = 0;
  this->missionUpdateProgress.gifts = 0;

  this->missionUpdateProgress.special_progress_1 = 0;
  this->missionUpdateProgress.special_progress_2 = 0;
  this->missionUpdateProgress.special_progress_3 = 0;
  this->missionUpdateProgress.special_progress_4 = 0;
  this->missionUpdateProgress.special_progress_5 = 0;
  this->missionUpdateProgress.special_progress_6 = 0;
  this->missionUpdateProgress.special_progress_7 = 0;
  this->missionUpdateProgress.special_progress_8 = 0;
  this->missionUpdateProgress.special_progress_9 = 0;
  this->missionUpdateProgress.special_progress_10 = 0;
  this->missionUpdateProgress.special_progress_11 = 0;
  this->missionUpdateProgress.special_progress_12 = 0;
  this->missionUpdateProgress.special_progress_13 = 0;
  this->missionUpdateProgress.special_progress_14 = 0;
  this->missionUpdateProgress.special_progress_15 = 0;

  Events::updateMissions();
}

/**
 *
 *
 *
 */
void Counter::onMissionComplete()
{
  this->values.b.mission = true;

  this->resetMissionsUpdate();

  Application->environment->missions.controller->notify->notify(EnvironmentMissionsNotify::NONE);
  Application->environment->missions.missions.elements.erase(Application->environment->missions.missions.elements.begin() + 2);
  Application->environment->missions.missions.plane->removeItem(2);
}
