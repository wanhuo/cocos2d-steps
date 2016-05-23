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

#ifndef _LETTERS_H_
#define _LETTERS_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Letters : public Entity3D
{
  /**
   *
   *
   *
   */
  private:
  struct Lets {
    Pool* a;
    Pool* b;
    Pool* c;
    Pool* d;
    Pool* e;
    Pool* f;
    Pool* g;
    Pool* h;
    Pool* i;
    Pool* j;
    Pool* k;
    Pool* l;
    Pool* m;
    Pool* n;
    Pool* o;
    Pool* p;
    Pool* q;
    Pool* r;
    Pool* s;
    Pool* t;
    Pool* u;
    Pool* v;
    Pool* w;
    Pool* x;
    Pool* y;
    Pool* z;
  };

  Camera* camera;

  /**
   *
   *
   *
   */
  protected:
  Lets letters;

  /**
   *
   *
   *
   */
  public:
  Letters(Node* parent, bool copy = false);
 ~Letters();

  virtual void onEnter();
  virtual void onExit();

  virtual void create(string word);
  virtual void destroy();
};

#endif
