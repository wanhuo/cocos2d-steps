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
Letters::Letters(Node* parent, bool copy)
: Entity3D("", parent)
{
  if(!copy)
  {
    this->camera = Camera::createOrthographic(Application->getFrustumWidth(), Application->getFrustumHeight(), 1, 100);
    this->camera->setPosition3D(Vec3(0, 0, 2));
    this->camera->setRotation3D(Vec3(0, 0, 0));
    this->camera->setDepth(3);
    this->camera->setCameraFlag(32);

    Application->addChild(this->camera);

    auto l1 = DirectionLight::create(Vec3(1.0, -1.0, -1.0), Color3B(255, 255, 255));
    auto l2 = AmbientLight::create(Color3B(120, 120, 120));

    l1->setLightFlag(32);
    l2->setLightFlag(32);

    Application->addChild(l1);
    Application->addChild(l2);
  }

  this->letters.a = new Pool(new Letter("a"), this);
  this->letters.b = new Pool(new Letter("b"), this);
  this->letters.c = new Pool(new Letter("c"), this);
  this->letters.d = new Pool(new Letter("d"), this);
  this->letters.e = new Pool(new Letter("e"), this);
  this->letters.f = new Pool(new Letter("f"), this);
  this->letters.g = new Pool(new Letter("g"), this);
  this->letters.h = new Pool(new Letter("h"), this);
  this->letters.i = new Pool(new Letter("i"), this);
  this->letters.j = new Pool(new Letter("j"), this);
  this->letters.k = new Pool(new Letter("k"), this);
  this->letters.l = new Pool(new Letter("l"), this);
  this->letters.m = new Pool(new Letter("m"), this);
  this->letters.n = new Pool(new Letter("n"), this);
  this->letters.o = new Pool(new Letter("o"), this);
  this->letters.p = new Pool(new Letter("p"), this);
  this->letters.q = new Pool(new Letter("q"), this);
  this->letters.r = new Pool(new Letter("r"), this);
  this->letters.s = new Pool(new Letter("s"), this);
  this->letters.t = new Pool(new Letter("t"), this);
  this->letters.u = new Pool(new Letter("u"), this);
  this->letters.v = new Pool(new Letter("v"), this);
  this->letters.w = new Pool(new Letter("w"), this);
  this->letters.x = new Pool(new Letter("x"), this);
  this->letters.y = new Pool(new Letter("y"), this);
  this->letters.z = new Pool(new Letter("z"), this);

  this->setPosition3D(Vec3(Application->getFrustumWidth() / 2, Application->getFrustumHeight() / 2 + 3.0, 0));
}

Letters::~Letters()
{
}

/**
 *
 *
 *
 */
void Letters::onEnter()
{
  Entity3D::onEnter();
}

void Letters::onExit()
{
  Entity3D::onExit();
}

/**
 *
 *
 *
 */
void Letters::create(string word)
{
  vector<Node*> w;

  for(char letter : word)
  {
    switch(letter)
    {
      case 'a':
      w.push_back(this->letters.a->_create());
      break;
      case 'b':
      w.push_back(this->letters.b->_create());
      break;
      case 'c':
      w.push_back(this->letters.c->_create());
      break;
      case 'd':
      w.push_back(this->letters.d->_create());
      break;
      case 'e':
      w.push_back(this->letters.e->_create());
      break;
      case 'f':
      w.push_back(this->letters.f->_create());
      break;
      case 'g':
      w.push_back(this->letters.g->_create());
      break;
      case 'h':
      w.push_back(this->letters.h->_create());
      break;
      case 'i':
      w.push_back(this->letters.i->_create());
      break;
      case 'k':
      w.push_back(this->letters.k->_create());
      break;
      case 'l':
      w.push_back(this->letters.l->_create());
      break;
      case 'm':
      w.push_back(this->letters.m->_create());
      break;
      case 'n':
      w.push_back(this->letters.n->_create());
      break;
      case 'o':
      w.push_back(this->letters.o->_create());
      break;
      case 'p':
      w.push_back(this->letters.p->_create());
      break;
      case 'q':
      w.push_back(this->letters.q->_create());
      break;
      case 'r':
      w.push_back(this->letters.r->_create());
      break;
      case 's':
      w.push_back(this->letters.s->_create());
      break;
      case 't':
      w.push_back(this->letters.t->_create());
      break;
      case 'u':
      w.push_back(this->letters.u->_create());
      break;
      case 'v':
      w.push_back(this->letters.v->_create());
      break;
      case 'w':
      w.push_back(this->letters.w->_create());
      break;
      case 'x':
      w.push_back(this->letters.x->_create());
      break;
      case 'y':
      w.push_back(this->letters.y->_create());
      break;
      case 'z':
      w.push_back(this->letters.z->_create());
      break;
    }
  }

  /**
   *
   *
   *
   */
  auto x = -((w.size() - 1) * 1.0) / 2;
  auto y = 0.0;

  auto counter = 0;

  for(auto letter : w)
  {
    static_cast<Entity3D*>(letter)->setPosition3D(Vec3(x, y, 0));
    static_cast<Entity3D*>(letter)->setRotation3D(Vec3(0.0, 0.0, 0.0));
    static_cast<Entity3D*>(letter)->setCameraMask(32);
    static_cast<Entity3D*>(letter)->setLightMask(32);

    x += 1.0;
    counter++;
  }

  this->_create();

  this->setCameraMask(32);
  this->setLightMask(32);
}

void Letters::destroy()
{
  this->letters.a->clear();
  this->letters.b->clear();
  this->letters.c->clear();
  this->letters.d->clear();
  this->letters.e->clear();
  this->letters.f->clear();
  this->letters.g->clear();
  this->letters.h->clear();
  this->letters.i->clear();
  this->letters.j->clear();
  this->letters.k->clear();
  this->letters.l->clear();
  this->letters.m->clear();
  this->letters.n->clear();
  this->letters.o->clear();
  this->letters.p->clear();
  this->letters.q->clear();
  this->letters.r->clear();
  this->letters.s->clear();
  this->letters.t->clear();
  this->letters.u->clear();
  this->letters.v->clear();
  this->letters.w->clear();
  this->letters.x->clear();
  this->letters.y->clear();
  this->letters.z->clear();

  this->_destroy();
}
