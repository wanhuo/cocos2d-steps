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

#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "Game.h"

/**
 *
 *
 *
 */
class Plate;

/**
 *
 *
 *
 */
class Generator : public Ref
{
  /**
   *
   *
   *
   */
  public:
  enum {
    EPISODE_WIPE,
    EPISODE_DUEL,
    EPISODE_TRAMPOLINES
  };

  /**
   *
   *
   *
   */
  private:
  struct Element {
    int probability;
    int type;
    int min;
    int max;
  };

  struct Elements {
    int probability;

    vector<Element> elements;
  };

  struct Bonus {
    int size;
  };

  struct Route {
    float max;
    float min;
  };

  struct Parameter {
    int size;
    int save;
    int start;

    Route route;
    Bonus bonus;

    Elements plates;
    Elements pickups;
  };

  struct Parameters {
    Parameter general;
    Parameter current;
  };

  /**
   *
   *
   *
   */
  protected:
  struct Conditions {
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
    int s6;
    int s7;
    int s8;
    int s9;
    int s10;
    int s11;
  };

  struct HeightStruct {
    int counter;
    int length;
  };

  struct Height {
    int stage;
    int max = 2;

    HeightStruct up;
    HeightStruct down;
  };

  struct Wipe {
    bool next = false;

    int index;
    int length;

    bool start;
    bool finish;
  };

  struct Duel {
    bool next = false;

    int index;
    int length;

    bool start;
    bool finish;
  };

  struct Trampolines {
    bool next = false;

    int index;
    int length;

    bool start;
    bool finish;
  };

  struct Episode {
    Wipe wipe;
    Duel duel;
    Trampolines trampolines;
  };

  vector<Parameter> levels;

  /**
   *
   *
   *
   */
  public:
  Parameters parameters;
  Conditions conditions;
  Episode episode;
  Height height;

  Generator();
 ~Generator();

  string word;

  Plate* plate;

  float x;
  float y;
  float z;

  int size;
  int start;
  int save;
  int count;
  int index;
  int length;
  int general;

  bool direction;
  bool bonus;

  int bonusSkip;
  int skip;
  int portal;

  virtual Plate* create(bool animated = false);
  virtual Plate* destroy(bool manual = false);

  virtual void createBonusElement();
  virtual void createGeneralElement();

  virtual bool updateEpisode(int episode);
  virtual bool cleanEpisode(int episode);

  virtual bool updateEpisodes();
  virtual bool checkEpisodes(Plate* plate);
  virtual bool cleanEpisodes();

  virtual bool isEpisode(int episode);
  virtual bool isEpisodes();

  virtual void onEpisodeStart(int episode);
  virtual void onEpisodeFinish(int episode);

  virtual Plate* update(bool post);

  virtual void reset(bool complete = false);
};

#endif
