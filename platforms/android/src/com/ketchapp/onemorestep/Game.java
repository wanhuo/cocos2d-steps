/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2014 by Igor Mats
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
 * @version of cocos2d is 3.4
 *
 */

package com.ketchapp.onemorestep;

import android.content.Intent;
import android.os.Bundle;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxJavascriptJavaBridge;

import com.tooflya.android.cocos2d.library.Application;

/**
 *
 *
 *
 */
public class Game extends Application {

  /**
   *
   *
   *
   */
  @Override
  public Cocos2dxGLSurfaceView onCreateView() {
    Cocos2dxGLSurfaceView glSurfaceView = super.onCreateView();

    return glSurfaceView;
  }

  /**
   *
   *
   *
   */
  @Override
  protected void onActivityResult(int request, int response, Intent data) {
    super.onActivityResult(request, response, data);
  }

  /**
   *
   *
   *
   */
  @Override
  public void onSaveInstanceState(Bundle outState) {
    super.onSaveInstanceState(outState);
  }

  /**
   *
   *
   *
   */
  @Override
  public String getGoogleServicesID() {
    return Application.sharedInstance().getResources().getString(R.string.google);
  }

  /**
   *
   *
   *
   */
  @Override
  public int getGoogleServicesIconID() {
    return R.drawable.icon;
  }

  /**
   *
   *
   *
   */
  @Override
  public void nativeCall(final String instructions) {

    /**
     *
     *
     *
     */
    Cocos2dxJavascriptJavaBridge.evalString(instructions);
  }
}
