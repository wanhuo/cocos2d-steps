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
Color::Color(int index, int r, int g, int b)
{
  this->index = index;

  currentColor[0] = r;
  currentColor[1] = g;
  currentColor[2] = b;

 targetColor   = generateRGB(25, 200);
 distance    = calculateDistance(currentColor, targetColor);
 increment   = calculateIncrement(distance);

}

Color::~Color()
{
}

/**
 *
 *
 *
 */
int* Color::generateRGB(int min, int max)
{
  auto color = new int[3];
  for(int i = 0; i < 3; i++) {
    auto num = floor(random(0.0f, 1.0f) * max);
    while(num < min) {
      num = floor(random(0.0f, 1.0f) * max);
    }

    color[i] = num;
  }

  return color;
}

int* Color::calculateDistance(int* colorArray1, int* colorArray2)
{
  auto distance = new int[3];
  for (int i = 0; i < 3; i++) {
    distance[i] = abs(colorArray1[i] - colorArray2[i]);
  }

  return distance;
}

int* Color::calculateIncrement(int* distanceArray)
{
  auto increment = new int[3];
  for(int i = 0; i < 3; i++) {
    increment[i] = abs(floor(distanceArray[i] / this->index));
    if (increment[i] == 0) {
      increment[i]++;
    }
  }

  return increment;
}

Color3B Color::get()
{
  if (currentColor[0] > targetColor[0]) {
    currentColor[0] -= increment[0];
    if (currentColor[0] <= targetColor[0]) {
      increment[0] = 0;
    }
  } else {
    currentColor[0] += increment[0];
    if (currentColor[0] >= targetColor[0]) {
      increment[0] = 0;
    }
  }
  
  if (currentColor[1] > targetColor[1]) {
    currentColor[1] -= increment[1];
    if (currentColor[1] <= targetColor[1]) {
      increment[1] = 0;
    }
  } else {
    currentColor[1] += increment[1];
    if (currentColor[1] >= targetColor[1]) {
      increment[1] = 0;
    }
  }
  
  if (currentColor[2] > targetColor[2]) {
    currentColor[2] -= increment[2];
    if (currentColor[2] <= targetColor[2]) {
      increment[2] = 0;
    }
  } else {
    currentColor[2] += increment[2];
    if (currentColor[2] >= targetColor[2]) {
      increment[2] = 0;
    }
  }

  if (increment[0] == 0 && increment[1] == 0 && increment[2] == 0) {
    targetColor = generateRGB(25, 200);
    distance  = calculateDistance(currentColor, targetColor);
    increment = calculateIncrement(distance);
    
    return get();
  }

  return Color3B(currentColor[0], currentColor[1], currentColor[2]);

}

/*
function generateRGB(min, max) {
  var min   = min || 0;
  var max   = max || 255;
  var color = [];
  for (var i = 0; i < 3; i++) {
    var num = Math.floor(Math.random() * max);
    while (num < min) {
      num = Math.floor(Math.random() * max);
    }
    color.push(num);
  }
  return color;
}

function calculateDistance(colorArray1, colorArray2) {
  var distance = [];
  for (var i = 0; i < colorArray1.length; i++) {
    distance.push(Math.abs(colorArray1[i] - colorArray2[i]));
  }
  return distance;
}

function calculateIncrement(distanceArray, fps, duration) {
  var fps     = fps || 30;
  var duration  = duration || 1;
  var increment = [];
  for (var i = 0; i < distanceArray.length; i++) {
    increment.push(Math.abs(Math.floor(distanceArray[i] / (fps * duration))));
    if (increment[i] == 0) {
      increment[i]++;
    }
  }
  return increment;
}

function rgb2hex(colorArray) {
  var hex = [];
  for (var i = 0; i < colorArray.length; i++) {
    hex.push(colorArray[i].toString(16));
    if (hex[i].length < 2) { hex[i] = "0" + hex[i]; }
  }
  return "#" + hex.join("");
}*/
