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
Special::Special(string file, Node* parent)
: Cube(file, parent)
{
  this->decorations = *new vector<Decoration*>();

  this->setLightMask(0);
}

Special::Special()
: Cube()
{
  this->decorations = *new vector<Decoration*>();

  this->setLightMask(0);
}

Special::~Special()
{
}

/**
 *
 *
 *
 */
void Special::onCreate()
{
  Cube::onCreate();

  /**
   *
   *
   *
   */
  this->setRotation3D(Vec3(0, 0, 0));
}

void Special::onDestroy(bool action)
{
  Cube::onDestroy(action);

  /**
   *
   *
   *
   */
  this->clearDecorations();
}

/**
 *
 *
 *
 */
vector<Decoration*> &Special::getDecorations()
{
  return this->Special::decorations;
}

/**
 *
 *
 *
 */
void Special::setPlate(Plate* plate)
{
  this->plate = plate;
}

/**
 *
 *
 *
 */
void Special::start()
{
}

/**
 *
 *
 *
 */
void Special::clearDecorations()
{
  for(auto decoration : this->getDecorations())
  {
    if((decoration->removable && !decoration->unremovable) || !this->state->create)
    {
      decoration->_destroy(true);
    }
  }

  this->getDecorations().erase(
    std::remove_if(
        this->getDecorations().begin(),
        this->getDecorations().end(),
        [](Decoration* element) -> bool {
            return !element->state->create;
        }
    ),
    this->getDecorations().end()
  );
}

/**
 *
 *
 *
 */
Special* Special::deepCopy()
{
  return new Special(this->textureFileName);
}

/**
 *
 *
 *
 */
void Special::setTexture(const std::string& texture)
{
  Cube::setTexture(texture);

  /**
   *
   *
   *
   */
  for(auto decoration : this->getDecorations())
  {
    decoration->setTexture(texture);
  }
}
