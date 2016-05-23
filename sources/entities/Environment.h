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

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include "Game.h"

#include "ui/UIListView.h"

/**
 *
 *
 *
 */
class Character;
class Ground;
class Decoration;

class EnvironmentStoreItem;
class EnvironmentStoreCharacter;
class EnvironmentStoreTexture;
class EnvironmentStoreBar;

class EnvironmentMissionsItem;
class EnvironmentMissionsBar;

/**
 *
 *
 *
 */
class Environment : public Background
{
  /**
   *
   *
   *
   */
  private:
  struct Random {
    bool texture;
    bool character;
  };

  struct Parameters {
    int stage;

    int texture;
    int character;

    Random random;
  };

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

  struct Light {
    BaseLight* environment;
    BaseLight* natural;
  };

  struct Plates {
    Pool* normal;
    Pool* finish;
    Pool* best;
    Pool* bonus;
    Pool* spikes;
    Pool* trampolines;
    Pool* saws;
    Pool* gates;
    Pool* traps;
    Pool* copters;
    Pool* moveups;
    Pool* moved1;
    Pool* moved2;
    Pool* moved3;
    Pool* moved4;
  };

  struct Decorations {
    Pool* starts;
    Pool* downs;
    Pool* cubs;
  };

  struct Pickups {
    Pool* diamonds;
    Pool* crystals;
    Pool* energies;
    Pool* stars;
    Pool* hearts;
    Pool* colors;
    Pool* presentions;

    Lets letters;
  };

  struct StoreElement {
    cocos2d::ui::ListView* plane;
    vector<EnvironmentStoreItem*> elements;
  };

  struct MissionsElement {
    cocos2d::ui::ListView* plane;
    vector<EnvironmentMissionsItem*> elements;
  };

  struct Store {
    EnvironmentStoreBar* controller = nullptr;
    StoreElement characters;
    StoreElement textures;
  };

  struct Missions {
    EnvironmentMissionsBar* controller = nullptr;
    MissionsElement missions;

    bool special;
  };

  /**
   *
   *
   *
   */
  private:
  const static int ACCELEROMETER_FACTOR = 10;
  const static int ACCELERATION_FACTOR = 10;

  float accelerometerX = 0;
  float accelerometerY = 0;
  float accelerometerZ = 0;

  float accelerationX = 0;
  float accelerationY = 0;
  float accelerationZ = 0;

  float platesTime;
  float platesTimeElapsed;

  /**
   *
   *
   *
   */
  public:
  const static int STAR_TIME = 5;

  Environment(Node* parent);
 ~Environment();

  Parameters parameters;

  Decorations decorations;
  Pickups pickups;
  Plates plates;

  Store store;
  Missions missions;

  Light light;

  int nextCharacter = 0;
  int nextTexture = 0;

  bool star = false;

  float starTime;
  float starTimeElapsed;

  Character* character;

  Generator* generator = nullptr;
  Letters* letters = nullptr;

  Entity3D* plane;

  Pool* particles;

  Ground* ground;

  Background* characterActionHolder;
  BackgroundColor* characterActionBackground;
  BackgroundColor* characterAction;

  virtual void create();
  virtual void reset();

  virtual Entity3D* createParticle(float x, float y, float z);

  virtual string getTextureState1();
  virtual string getTextureState2();

  virtual void updateData();
  virtual void updateLevel();

  virtual void onAccelerate(Acceleration* acceleration, Event* e);

  virtual void onTurn(bool action = true);

  virtual void onMenu();
  virtual void onGame();
  virtual void onFinish();
  virtual void onLose();
  virtual void onStore();
  virtual void onMissions();
  virtual void onPresent();
  virtual void onOpen();
  virtual void onWatch();
  virtual void onCopter();
  virtual void onMissionComplete();

  virtual void startStar();
  virtual void finishStar();

  virtual void updateStar(float time);

  virtual void updateMenu(float time);
  virtual void updateGame(float time);
  virtual void updateLose(float time);

  virtual void update(float time);
};

#endif
