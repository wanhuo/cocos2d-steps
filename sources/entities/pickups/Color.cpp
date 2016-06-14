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
Color::Color()
: Pickup("color.obj")
{
  this->setScale(1.5);
  this->glow->setVisible(false);
}

Color::~Color()
{
}

/**
 *
 *
 *
 */
void Color::onCreate()
{
  Pickup::onCreate();

  /**
   *
   *
   *
   */
  this->runAction(
    RepeatForever::create(
      Sequence::create(
        CallFunc::create([=] () {
        
  float r = 0;
  float g = 0;
  float b = 0;

  while(true)
  {
  float h = random(0.0, 1.0);
  float s = 0.5;
  float v = 0.95;

  int hi = floor(h*6);
  float f = h*6 - hi;
  float p = v * (1 - s);
  float q = v * (1 - f*s);
  float t = v * (1 - (1 - f) * s);
	
	switch (hi) {
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		case 5:
			r = v;
			g = p;
			b = q;
			break;
	}

  r *= 256;
  g *= 256;
  b *= 256;

  r = floor(min(r, 255.0f));
  g = floor(min(g, 255.0f));
  b = floor(min(b, 255.0f));

if(r == Application->environment->character->getColor().r && g == Application->environment->character->getColor().g && b == Application->environment->character->getColor().b)
{
}
else
{
  break;
}

}




          this->setColor(Color3B(r, g, b));
        }),
        DelayTime::create(0.25),
        nullptr
      )
    )
  );
}

void Color::onDestroy(bool action)
{
  Pickup::onDestroy(action);
}

/**
 *
 *
 *
 */
void Color::onPickup()
{
  Pickup::onPickup();

  /**
   *
   * @Missions
   * Update missions with color.
   *
   */
  if(MissionsFactory::getInstance()->isListenen())
  {
    Application->counter->missionUpdateOnce.special_once_4++;
    Application->counter->missionUpdateProgress.special_progress_4++;

    Events::updateMissions();
  }

  /**
   *
   *
   *
   */
  Application->environment->character->color = this->getColor();
  Application->environment->character->setColor(this->getColor());

  Sound->play("pickup-color");
}

/**
 *
 *
 *
 */
void Color::setPlate(Plate* plate, bool animated)
{
  Pickup::setPlate(plate, animated);

  /**
   *
   *
   *
   */
  this->setPositionY(this->getPositionY() + 0.2);
}

/**
 *
 *
 *
 */
Color* Color::deepCopy()
{
  return new Color;
}
