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
Generator::Generator()
{
  auto rootJsonData = Json_create(FileUtils::getInstance()->getStringFromFile("generator.json").c_str());
  auto generalJsonData = Json_getItem(rootJsonData, "general");
  auto levelsJsonData = Json_getItem(rootJsonData, "levels");

  /**
   *
   *
   *
   */
  auto platesJsonData = Json_getItem(generalJsonData, "plates");
  auto pickupsJsonData = Json_getItem(generalJsonData, "pickups");

  /**
   *
   *
   *
   */
  auto bonusJsonData = Json_getItem(generalJsonData, "bonus");
  auto routeJsonData = Json_getItem(generalJsonData, "route");
  auto platesElementsJsonData = Json_getItem(platesJsonData, "elements");
  auto pickupsElementsJsonData = Json_getItem(pickupsJsonData, "elements");

  /**
   *
   *
   *
   */
  this->parameters.general.size = Json_getInt(generalJsonData, "size", 0);
  this->parameters.general.save = Json_getInt(generalJsonData, "save", 0);
  this->parameters.general.start = Json_getInt(generalJsonData, "start", 0);
  this->parameters.general.bonus.size = Json_getInt(bonusJsonData, "size", 0);
  this->parameters.general.route.max = Json_getInt(routeJsonData, "max", 0);
  this->parameters.general.route.min = Json_getInt(routeJsonData, "min", 0);

  /**
   *
   *
   *
   */
  this->parameters.general.plates.probability = Json_getInt(platesJsonData, "probability", 0);
  for(auto plateJsonData = platesElementsJsonData->child; plateJsonData; plateJsonData = plateJsonData->next)
  {
    Element element;

    element.type = Json_getInt(plateJsonData, "type", 0);
    element.probability = Json_getInt(plateJsonData, "probability", 0);

    this->parameters.general.plates.elements.push_back(element);
  }

  /**
   *
   *
   *
   */
  this->parameters.general.pickups.probability = Json_getInt(pickupsJsonData, "probability", 0);
  for(auto pickupJsonData = pickupsElementsJsonData->child; pickupJsonData; pickupJsonData = pickupJsonData->next)
  {
    Element element;

    element.type = Json_getInt(pickupJsonData, "type", 0);
    element.probability = Json_getInt(pickupJsonData, "probability", 0);

    this->parameters.general.pickups.elements.push_back(element);
  }

  /**
   *
   *
   *
   */
  for(auto levelJsonData = levelsJsonData->child; levelJsonData; levelJsonData = levelJsonData->next)
  {
    Parameter parameter;

    /**
     *
     *
     *
     */
    auto platesJsonData = Json_getItem(levelJsonData, "plates");
    auto pickupsJsonData = Json_getItem(levelJsonData, "pickups");

    /**
     *
     *
     *
     */
    auto bonusJsonData = Json_getItem(levelJsonData, "bonus");
    auto routeJsonData = Json_getItem(levelJsonData, "route");
    auto platesElementsJsonData = Json_getItem(platesJsonData, "elements");
    auto pickupsElementsJsonData = Json_getItem(pickupsJsonData, "elements");

    /**
     *
     *
     *
     */
    parameter.size = Json_getInt(levelJsonData, "size", 0);
    parameter.save = Json_getInt(levelJsonData, "save", 0);
    parameter.start = Json_getInt(levelJsonData, "start", 0);
    parameter.bonus.size = Json_getInt(bonusJsonData, "size", 0);
    parameter.route.max = Json_getInt(routeJsonData, "max", 0);
    parameter.route.min = Json_getInt(routeJsonData, "min", 0);

    /**
     *
     *
     *
     */
    parameter.plates.probability = Json_getInt(platesJsonData, "probability", 0);
    for(auto plateJsonData = platesElementsJsonData->child; plateJsonData; plateJsonData = plateJsonData->next)
    {
      Element element;

      element.type = Json_getInt(plateJsonData, "type", 0);
      element.probability = Json_getInt(plateJsonData, "probability", 0);

      parameter.plates.elements.push_back(element);
    }

    /**
     *
     *
     *
     */
    parameter.pickups.probability = Json_getInt(pickupsJsonData, "probability", 0);
    for(auto pickupJsonData = pickupsElementsJsonData->child; pickupJsonData; pickupJsonData = pickupJsonData->next)
    {
      Element element;

      element.type = Json_getInt(pickupJsonData, "type", 0);
      element.probability = Json_getInt(pickupJsonData, "probability", 0);

      parameter.pickups.elements.push_back(element);
    }

    /**
     *
     *
     *
     */
    this->levels.push_back(parameter);
  }
}

Generator::~Generator()
{
}

/**
 *
 *
 *
 */
Plate* Generator::create(bool animated)
{
  if((!this->bonus && this->index <= this->size) || (this->bonus && this->index <= this->size))
  {
    auto plate = this->update(false);

    /**
     *
     * @Generator
     * Bonus generation.
     *
     */
    if(this->bonus)
    {
      this->createBonusElement(plate);
    }

    /**
     *
     * @Generator
     * General generation.
     *
     */
    else
    {
      this->createGeneralElement(plate);
    }

    plate->setPositionX(this->x);
    plate->setPositionY(this->y);
    plate->setPositionZ(this->z);

    plate->setStartPositionX(this->x);
    plate->setStartPositionY(this->y);
    plate->setStartPositionZ(this->z);

    if(animated)
    {
      plate->prepare();
    }
    else
    {
      plate->start();
    }

    this->update(true);

    return plate;
  }

  return nullptr;
}

Plate* Generator::destroy(bool manual)
{
  switch(Application->environment->character->state)
  {
    default:
    switch(Application->state)
    {
      case Game::GAME:
      if(manual)
      {
        if(Application->environment->character->plates.current)
        {
          vector<Plate*> v;
          int counter = 0;

          for(int i = 0; i < Application->environment->plates.normal->count; i++)
          {
            Plate* element = static_cast<Plate*>(Application->environment->plates.normal->element(i));

            if(element->getIndex() < Application->environment->character->plates.current->getIndex() - 5)
            {
              v.push_back(element);
            }
  }
            sort(v.begin(), v.end(),
                []( Plate* a,  Plate* b) -> bool
            { 
                return a->getIndex() < b->getIndex();
            });

            for(auto p : v)
            {
              p->runAction(
                Sequence::create(
                  DelayTime::create(counter * 0.1),
                  CallFunc::create([=] () {
                    p->remove();
                  }),
                  nullptr
                )
              );

              counter++;
            }




        }
      }
      else
      {
        if(Application->counter->values.start >= this->save)
        {
          Plate* plate = nullptr;

          for(int i = 0; i < Application->environment->plates.normal->count; i++)
          {
            Plate* element = static_cast<Plate*>(Application->environment->plates.normal->element(i));

            if(!plate)
            {
              plate = element;
            }
            else
            {
              if(element->getIndex() < plate->getIndex())
              {
                plate = element;
              }
            }
          }

          if(plate)
          {
            plate->remove();
          }
        }
      }
      break;
    }
    break;
    case Character::STATE_INSANE:
    case Character::STATE_FINISH:
    break;
  }

  return nullptr;
}

/**
 *
 *
 *
 */
void Generator::createBonusElement(Plate* plate)
{
  if(this->index >= 1)
  {
    if(this->index >= this->size)
    {
      plate->setType(Plate::FINISH);
    }
    else
    {
      if(this->bonusSkip-- <= 0)
      {
        plate->setType(Plate::DIAMOND);
      }

      plate->setType(Plate::BONUS);

      if(plate->conditions(Plate::CUB))
      {
        plate->setType(Plate::CUB);
      }
    }
  }
}

void Generator::createGeneralElement(Plate* plate)
{
  /**
   *
   * Check if this is a first plate of level.
   *
   */
  if(this->index == 0)
  {
    plate->setType(Plate::START);
  }
  else if(this->index == 3 && !Application->parameters.showPresent && Application->parameters.elapsed.present >= Application->parameters.present)
  {
    plate->setType(Plate::PRESENTION);
  }
  else
  {
    bool action = true;

    /**
     *
     * Check if there is a finish plate.
     *
     */
    if(this->index == this->size)
    {
      plate->setType(Plate::FINISH);
    }
    else if(this->general == Application->counter->values.best + 1)
    {
      if(Application->counter->values.best > 1)
      {
        action = false;

        plate->setType(Plate::BEST);
      }
    }

    /**
     *
     * Check if plates length is more that save plates count.
     *
     */
    if(this->index >= this->save)
    {
      {
        /**
         *
         * Check if there is a finish plate.
         *
         */
        if(this->index == this->size)
        {
        }
        else if(action)
        {
          /**
           *
           * Try to generate some pickup.
           *
           */
          if(this->parameters.current.plates.elements.size()) if(probably(this->parameters.current.plates.probability))
          {
            auto element = this->parameters.current.plates.elements.at(random<int>(0, this->parameters.current.plates.elements.size() - 1));

            if(probably(element.probability) && plate->conditions(element.type))
            {
              plate->setType(element.type);

              return;
            }
          }

          /**
           *
           * Try to generate some enemy plate.
           *
           */
          if(this->parameters.current.pickups.elements.size()) if(probably(this->parameters.current.pickups.probability))
          {
            auto element = this->parameters.current.pickups.elements.at(random<int>(0, this->parameters.current.pickups.elements.size() - 1));

            if(probably(element.probability) && plate->conditions(element.type))
            {
              plate->setType(element.type);

              return;
            }
          }
        }
      }
    }
  }
}

/**
 *
 *
 *
 */
Plate* Generator::update(bool post)
{
  /**
   *
   *
   *
   */
  if(post)
  {
    if(!this->bonus)
    {
      this->general++;
    }

    this->index++;

    this->conditions.s1--;
    this->conditions.s2--;
    this->conditions.s3--;
    this->conditions.s4--;
    this->conditions.s5--;
    this->conditions.s6--;
    this->conditions.s7--;
    this->conditions.s8--;
    this->conditions.s9--;
    this->conditions.s10--;
    this->conditions.s11--;

    if(this->direction)
    {
      this->x += 1.5f;
    }
    else
    {
      this->z -= 1.5f;
    }

    this->destroy(true);
  }

  /**
   *
   *
   *
   */
  else
  {
    if(++this->count > this->length)
    {
      this->count = 0;
      this->length = random(this->parameters.current.route.min, this->parameters.current.route.max);

      this->direction = !this->direction;

      if(this->direction)
      {
        this->x += 1.5f;
        this->z += 1.5f;
      }
      else
      {
        this->x -= 1.5f;
        this->z -= 1.5f;
      }
    }

    auto plate = static_cast<Plate*>(Application->environment->plates.normal->_create());

    plate->setDirection(this->direction);

    plate->setPositionX(this->x);
    plate->setPositionY(this->y);
    plate->setPositionZ(this->z);

    plate->setIndex(this->index);

    return plate;
  }

  return nullptr;
}

/**
 *
 *
 *
 */
void Generator::reset(bool complete)
{
  Application->environment->plates.normal->clear(true);

  Application->counter->values.start = 0;

  if(Application->environment->character->plates.current)
  {
    this->x = Application->environment->character->plates.current->getPositionX();
    this->y = 0.4;
    this->z = Application->environment->character->plates.current->getPositionZ();
  }
  else
  {
    this->x = 0.0;
    this->y = 0.4;
    this->z = 0.0;
  }

  /**
   *
   *
   *
   */
  if(Application->environment->character->plates.current && Application->environment->character->plates.current->type == Plate::FINISH && !this->bonus)
  {
    this->index = 0;
    this->count = 0;
    this->start = this->parameters.current.start;
    this->save = this->parameters.current.save;
    this->size = this->parameters.current.bonus.size;
    this->length = random(this->parameters.current.route.min, this->parameters.current.route.max);

    this->direction = true;
    this->bonus = true;

    this->bonusSkip =  Storage::get("generator.bonus.skip." + to_string(Application->environment->parameters.stage));
  }

  /**
   *
   *
   *
   */
  else
  {
    /**
     *
     * Update level if character`s current plate type is finish and bonus generation is enabled. 
     *
     */
    if(Application->environment->character->plates.current && Application->environment->character->plates.current->type == Plate::FINISH && this->bonus)
    {
      Application->environment->updateLevel();
    }
    /**
     *
     * Get parameters of current level.
     *
     */
    if(this->levels.size() >= Application->environment->parameters.stage)
    {
      this->parameters.current = this->levels.at(Application->environment->parameters.stage - 1);
    }
    else
    {
      this->parameters.current = this->parameters.general;
      this->parameters.current.size = Application->environment->parameters.stage * 50;
    }

    this->index = 0;
    this->count = 0;
    this->start = this->parameters.current.start;
    this->save = this->parameters.current.save;
    this->size = this->parameters.current.size;
    this->length = random(this->parameters.current.route.min, this->parameters.current.route.max);

    this->direction = true;
    this->bonus = false;
  }

  if(complete)
  {
    this->general= 1;
  }

  Application->environment->character->plates.current = nullptr;

  Application->environment->stopAllActions();
  Application->environment->runAction(
    Repeat::create(
      CallFunc::create([=] () {
        if(!Application->environment->character->plates.current)
        {
          Application->environment->character->plates.current = this->create();
        }
        else
        {
          this->create();
        }
      }), this->start
    )
  );

  this->conditions.s1 = 0;
  this->conditions.s2 = 0;
  this->conditions.s3 = 0;
  this->conditions.s4 = 0;
  this->conditions.s5 = 0;
  this->conditions.s6 = 0;
  this->conditions.s7 = 0;
  this->conditions.s8 = 0;
  this->conditions.s9 = 0;
  this->conditions.s10 = 0;
  this->conditions.s11 = 0;

  Application->environment->ground->reset();
}
