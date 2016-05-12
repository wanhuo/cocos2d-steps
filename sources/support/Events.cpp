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

#include "Events.h"

#include "Game.h"

/**
 *
 *
 *
 */
void Events::onStart()
{
  new Game;
  new Menu;
  new Finish;

  new Present;
  new Watch;
  new Open;

  Director::getInstance()->runWithScene(Application);

  Analytics::sendEvent("Application", "application.events.onStart", "Application onStart event");
}

/**
 *
 *
 *
 */
void Events::onStop()
{
  Analytics::sendEvent("Application", "application.events.onStop", "Application onStop event");
}

/**
 *
 *
 *
 */
void Events::onPause()
{
  Analytics::sendEvent("Application", "application.events.onPause", "Application onPause event");
}

/**
 *
 *
 *
 */
void Events::onResume()
{
  Analytics::sendEvent("Application", "application.events.onResume", "Application onResume event");
}

/**
 *
 *
 *
 */
void Events::onLeaderboards()
{
  Analytics::sendEvent("Application", "application.events.onLeaderboards", "Application onLeaderboards event");

  Modal::show();
  Services::showLeaderboards();
}

/**
 *
 *
 *
 */
void Events::onAchievements()
{
  Analytics::sendEvent("Application", "application.events.onAchievements", "Application onAchievements event");

  Modal::show();
  Services::showAchievements();
}

/**
 *
 *
 *
 */
void Events::onServices()
{
  Modal::hide();
  
  /*Game::getInstance()->buttons.leaderboards->bind(true);
  Game::getInstance()->buttons.achievements->bind(true);
  Finish::getInstance()->buttons.leaderboards->bind(true);
  Finish::getInstance()->buttons.achievements->bind(true);

  Game::getInstance()->buttons.leaderboards->setCurrentFrameIndex(0);
  Game::getInstance()->buttons.achievements->setCurrentFrameIndex(0);
  Finish::getInstance()->buttons.leaderboards->setCurrentFrameIndex(0);
  Finish::getInstance()->buttons.achievements->setCurrentFrameIndex(0);*/
}

/**
 *
 *
 *
 */
void Events::onRate()
{
  Analytics::sendEvent("Application", "application.events.onRate", "Application onRate event");

  Media::openStore();
}

/**
 *
 *
 *
 */
void Events::onLike()
{
  Analytics::sendEvent("Application", "application.events.onLike", "Application onLike event");
  Analytics::sendSocial("Twitter", "Open publisher view from application", "503287153144438");

  Media::openFacebook("503287153144438");
}

/**
 *
 *
 *
 */
void Events::onShare()
{
  Analytics::sendEvent("Application", "application.events.onShare", "Application onShare event");

  Modal::show();
  Screenshot::save([&] (bool a, string b)
  {
    auto text = new Text("share-message");
    auto size = Director::getInstance()->getOpenGLView()->getFrameSize();

    Social::share(size.width, size.width, 0, 0, text->data(0), Config::link);
    Modal::hide();
  });
}

/**
 *
 *
 *
 */
void Events::onSound()
{
  Analytics::sendEvent("Application", "application.events.onSound", "Application onSound event");

  if(!Music->enabled || !Sound->enabled)
  {
    Music->changeState(true);
    Sound->changeState(true);
  }
  else
  {
    Music->changeState(false);
    Sound->changeState(false);
  }
}

/**
 *
 *
 *
 */
void Events::onTwitter()
{
  Analytics::sendEvent("Application", "application.events.onTwitter", "Application onTwitter event");
  Analytics::sendSocial("Twitter", "Open developer view from application", "");

  Media::openTwitter();
}

void Events::onFacebook()
{
  Analytics::sendEvent("Application", "application.events.onFacebook", "Application onFacebook event");
  Analytics::sendSocial("Facebook", "Open developer view from application", "386292514777918");

  Media::openFacebook();
}

void Events::onMail()
{
  Analytics::sendEvent("Application", "application.events.onMail", "Application onMail event");

  Media::openMail();
}

/**
 *
 *
 *
 */
void Events::onScreenChanged(const char* name)
{
  Analytics::sendScreen(name);
}

/**
 *
 *
 *
 */
void Events::onRestorePurchases()
{
  Analytics::sendEvent("Application", "application.events.onRestorePurchases", "Application onRestorePurchases event");

  Purchase::restorePurchases();
}

/**
 *
 *
 *
 */
void Events::onPurchaseSuccess(const char* id, const char* name, float revenue)
{
  Modal::hide();

  Analytics::sendEvent("Application", "application.events.onPurchaseSuccess", "Application onPurchaseSuccess event");
  Analytics::sendTransaction(id, name, revenue);
}

/**
 *
 *
 *
 */
void Events::onPurchaseRestored(const char* id)
{
  if(strncmp(id, "com.ketchapp.exodus.remove.ads", 100) == 0)
  {
    //Application->onNoadAction();
  }
}

/*
 *
 *
 *
 */
void Events::updateMissions()
{
  /*if(MissionsFactory::getInstance()->updateCurrentMission(Application->counter->getMissionsUpdate()))
  {
    Events::onMissionComplete(MissionsFactory::getInstance()->getCurrentMission()->id);
  }*/
}

void Events::onMissionComplete(int id)
{
  Analytics::sendEvent("Missions", "missions.events.onMissionComplete", "Mission has been completed", id);

  //Application->counter->onMissionComplete();
}
