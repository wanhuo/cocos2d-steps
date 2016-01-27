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
Generator::Generator(Environment* environment)
{
  this->environment = environment;
}

Generator::~Generator()
{
}

/**
 *
 *
 *
 */
void Generator::spawn()
{
  if(this->routes.size() < 1)
  {
    this->onCreateRoute();
  }
  else
  {
    for(auto route : this->routes)
    {
      route->spawn();
    }

    if(this->temp.size() > 0)
    {
      this->routes.push_back(this->temp.at(0));
    }

    this->temp.clear();

    for(int i = 0; i < this->environment->plates->count; i++)
    {
      auto plate = static_cast<Plate*>(this->environment->plates->element(i));

      if(plate->getPositionZ() - this->environment->character->getPositionZ() > MAX_FREE_PLATES || this->environment->character->getPositionX() - plate->getPositionX() > MAX_FREE_PLATES)
      {
        plate->runAction(
          Spawn::create(
            Sequence::create(
              EaseSineInOut::create(
                MoveBy::create(0.2, Vec3(0, 1.0, 0))
              ),
              EaseSineInOut::create(
                MoveBy::create(0.4, Vec3(0, -6.0, 0))
              ),
              CallFunc::create([=] () {
                plate->_destroy(true);
              }),
              nullptr
            ),
            Sequence::create(
              DelayTime::create(0.3),
              FadeOut::create(0.1),
              nullptr
            ),
            nullptr
          )
        );

        plate->clearDecoration(false, true);
      }
    }
  }
}

/**
 *
 *
 *
 */
void Generator::onCreateRoute(Route* route)
{
  if(route)
  {
    if(probably(ROUTE_PROBABILITY))
    {
      if(this->routes.size() < MAX_ROUTES_COUNT)
      {
        auto next = new Route(this->environment, this);

        next->spawn(route);
        this->temp.push_back(next);
      }
    }
  }
  else
  {
    this->routes.push_back(new Route(this->environment, this));
  }
}

void Generator::onDestroyRoute(Route* route)
{
}
