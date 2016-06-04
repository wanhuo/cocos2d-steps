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
bool Generator::updateEpisodes()
{
  if(this->updateEpisode(EPISODE_WIPE)) return true;
  if(this->updateEpisode(EPISODE_DUEL)) return true;
  if(this->updateEpisode(EPISODE_TRAMPOLINES)) return true;

  return false;
}

bool Generator::cleanEpisodes()
{
  this->cleanEpisode(EPISODE_WIPE);
  this->cleanEpisode(EPISODE_DUEL);
  this->cleanEpisode(EPISODE_TRAMPOLINES);

  return false;
}

bool Generator::checkEpisodes(Plate* plate)
{
  if(plate->isEpisodeStart(Generator::EPISODE_WIPE))
  {
    this->onEpisodeStart(Generator::EPISODE_WIPE);
  }
  else if(plate->isEpisodeFinish(Generator::EPISODE_WIPE))
  {
    this->onEpisodeFinish(Generator::EPISODE_WIPE);
  }
  else if(plate->isEpisodeStart(Generator::EPISODE_DUEL))
  {
    this->onEpisodeStart(Generator::EPISODE_DUEL);
  }
  else if(plate->isEpisodeFinish(Generator::EPISODE_DUEL))
  {
    this->onEpisodeFinish(Generator::EPISODE_DUEL);
  }

  return false;
}

/**
 *
 *
 *
 */
bool Generator::updateEpisode(int episode)
{
  switch(episode)
  {
    /**
     *
     *
     *
     *
     */
    case EPISODE_WIPE:
    if(--this->episode.wipe.length < 0 && !this->isEpisodes() && this->portal < -1 && this->direction && this->count == 0 && Application->environment->character->state != Character::STATE_INSANE && probably(4.0))
    {
      this->episode.wipe.length = random(10, 20);
      this->episode.wipe.index = 0;
      this->episode.wipe.start = false;
      this->episode.wipe.finish = false;
    }

    if(this->episode.wipe.length > 0)
    {
      this->length++;
      this->episode.wipe.index++;

      this->plate->setType(Plate::WIPE);

      return true;
    }

    if(this->episode.wipe.length == 0)
    {
      this->count = 0;
      this->length = random(this->parameters.current.route.min, this->parameters.current.route.max);
      this->direction = !this->direction;

      return true;
    }
    break;

    /**
     *
     *
     *
     *
     */
    case EPISODE_DUEL:
    if(--this->episode.duel.length < 0 && !this->isEpisodes() && this->portal < -1 && !this->direction && this->count == 0 && Application->environment->character->state != Character::STATE_INSANE && probably(4.0))
    {
      this->episode.duel.length = this->start;
      this->episode.duel.index = 0;
      this->episode.duel.start = false;
      this->episode.duel.finish = false;
    }

    if(this->episode.duel.length > 0)
    {
      this->length++;
      this->episode.duel.index++;

      this->plate->setType(Plate::DUEL);

      return true;
    }

    if(this->episode.duel.length == 0)
    {
      this->count = 0;
      this->length = random(this->parameters.current.route.min, this->parameters.current.route.max);
      this->direction = !this->direction;

      return true;
    }
    break;

    /**
     *
     *
     *
     *
     */
    case EPISODE_TRAMPOLINES:
    if(--this->episode.trampolines.length < 0 && !this->isEpisodes() && this->portal < -1 && Application->environment->character->state != Character::STATE_INSANE && probably(1.0))
    {
      this->episode.trampolines.length = random(5, 20);
      this->episode.trampolines.index = 0;
      this->episode.trampolines.start = false;
      this->episode.trampolines.finish = false;
    }

    if(this->episode.trampolines.length > 0)
    {
      this->episode.trampolines.index++;

      if(this->episode.trampolines.next)
      {
        this->plate->episode.trampolines.index = this->episode.trampolines.index;
        this->plate->setType(Plate::TRAMPOLINE);

        this->plate->conditions(Plate::TRAMPOLINE);
      }

      this->episode.trampolines.next = !this->episode.trampolines.next;

      return true;
    }

    if(this->episode.trampolines.length == 0)
    {
      this->episode.trampolines.index = 0;
    }
    break;
  }

  return false;
}

bool Generator::cleanEpisode(int episode)
{
  switch(episode)
  {
    case EPISODE_WIPE:
    this->episode.wipe.index = 0;
    this->episode.wipe.length = 0;
    this->episode.wipe.start = false;
    this->episode.wipe.finish = false;
    break;
    case EPISODE_DUEL:
    this->episode.duel.index = 0;
    this->episode.duel.length = 0;
    this->episode.duel.start = false;
    this->episode.duel.finish = false;
    break;
    case EPISODE_TRAMPOLINES:
    this->episode.trampolines.index = 0;
    this->episode.trampolines.length = 0;
    this->episode.trampolines.start = false;
    this->episode.trampolines.finish = false;
    break;
  }

  return false;
}

/**
 *
 *
 *
 */
bool Generator::isEpisode(int episode)
{
  switch(episode)
  {
    case EPISODE_WIPE:
    if(this->episode.wipe.start) return true;
    break;
    case EPISODE_DUEL:
    if(this->episode.duel.start) return true;
    break;
    case EPISODE_TRAMPOLINES:
    if(this->episode.trampolines.start) return true;
    break;
  }

  return false;
}

bool Generator::isEpisodes()
{
  if(this->isEpisode(EPISODE_WIPE)) return true;
  if(this->isEpisode(EPISODE_DUEL)) return true;
  if(this->isEpisode(EPISODE_TRAMPOLINES)) return true;

  return false;
}

/**
 *
 *
 *
 */
void Generator::onEpisodeStart(int episode)
{
  auto x = Application->cameras.d->getRotation3D().x;
  auto y = Application->cameras.d->getRotation3D().y;
  auto z = Application->cameras.d->getRotation3D().z;

  auto px = Application->cameras.d->getPosition3D().x;
  auto py = Application->cameras.d->getPosition3D().y;
  auto pz = Application->cameras.d->getPosition3D().z;

  switch(episode)
  {
    case EPISODE_WIPE:
    if(this->episode.wipe.start) return;

    this->episode.wipe.start = true;

    Application->cameras.d->stopAllActions();
    Application->cameras.d->runAction(
      Spawn::create(
        ScaleTo::create(0.5, 0.75),
        MoveTo::create(0.5, Vec3(px + 25.0, py - 17, pz)),
        RotateTo::create(0.5, Vec3(x + 5, y + 20.0, z)),
        nullptr
      )
    );
    break;
    case EPISODE_DUEL:
    if(this->episode.duel.start) return;

    this->episode.duel.start = true;

    Music->speed(1.5);

    Application->cameras.d->stopAllActions();
    Application->cameras.d->runAction(
      Spawn::create(
        ScaleTo::create(0.5, 0.75),
        MoveTo::create(0.5, Vec3(px + 23.0, py - 17, pz)),
        RotateTo::create(0.5, Vec3(x + 5, y + 20.0, z)),
        nullptr
      )
    );
    break;
    case EPISODE_TRAMPOLINES:
    if(this->episode.trampolines.start) return;

    this->episode.trampolines.start = true;

    break;
  }
}

void Generator::onEpisodeFinish(int episode)
{
  switch(episode)
  {
    case EPISODE_WIPE:
    if(this->episode.wipe.finish) return;

    this->episode.wipe.finish = true;
    this->episode.wipe.start = false;
    this->episode.wipe.index = 0;

    Application->cameras.d->stopAllActions();
    Application->cameras.d->runAction(
      Spawn::create(
        ScaleTo::create(0.5, 1.0),
        MoveTo::create(0.5, Vec3(Application->startCameraX, Application->startCameraY, Application->startCameraZ)),
        RotateTo::create(0.5, Vec3(Application->startCameraRotationX, Application->startCameraRotationY, Application->startCameraRotationZ)),
        nullptr
      )
    );
    break;
    case EPISODE_DUEL:
    if(this->episode.duel.finish) return;

    this->episode.duel.finish = true;
    this->episode.duel.start = false;
    this->episode.duel.index = 0;

    Application->cameras.d->stopAllActions();
    Application->cameras.d->runAction(
      Spawn::create(
        ScaleTo::create(0.5, 1.0),
        MoveTo::create(0.5, Vec3(Application->startCameraX, Application->startCameraY, Application->startCameraZ)),
        RotateTo::create(0.5, Vec3(Application->startCameraRotationX, Application->startCameraRotationY, Application->startCameraRotationZ)),
        nullptr
      )
    );

    Music->speed(1.0);
    break;
    case EPISODE_TRAMPOLINES:
    if(this->episode.trampolines.finish) return;

    this->episode.trampolines.finish = true;
    this->episode.trampolines.start = false;
    break;
  }
}
