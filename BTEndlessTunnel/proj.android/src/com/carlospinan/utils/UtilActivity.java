package com.carlospinan.utils;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.Toast;

//import com.carlospinan.turborace.R;
//import com.lootsie.turborace.R;
import com.lootsie.turboracewhitelabel.R;



import com.google.basegameutils.BaseGameActivity;


/**
 * 
 * @author Carlos Eduardo Pi�an Indacochea
 * @version 1.0.0
 * @date 2014/02/25
 * @update 2014/02/25
 * 
 */
public class UtilActivity extends BaseGameActivity {

	private FrameLayout adViewLayout = null;
	public static final String TAG = "UtilActivity";

	private static final String HIT_TYPE = "Turbo Race Android";

	/**
	 * 
	 */
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Log.d(TAG, "UtilActivity: onCreate");
//		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

		_init();

//		uiHelper = new UiLifecycleHelper(this, statusCallback);
//		uiHelper.onCreate(savedInstanceState);
	}

	/**
	 * 
	 */
	private void _init() {
		
		Log.d(TAG, "UtilActivity: _init");
		
		NativeUtils.configure(this);
		

	}

	public void sendAnalyticData(String screen_name) {
		Log.d(TAG, "UtilActivity: sendAnalyticData");		
	}


	@Override
	public void onSignInFailed() {
		// Override in child class
		Log.d(TAG, "UtilActivity: onSignInFailed");		
	}

	@Override
	public void onSignInSucceeded() {
		// Override in child class
		Log.d(TAG, "UtilActivity: onSignInSucceeded");		
	}

	/**
	 * Get boolean to identify if user is signed in
	 * 
	 * @return
	 */
	public boolean getSignedIn() {
		return isSignedIn();
//		return false;
	}





	public void showAd() {
	}

	public void hideAd() {
	}

	@Override
	protected void onPause() {
		super.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
	}

	@Override
	protected void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		
		Log.d(TAG, "UtilActivity: onDestroy");		
	}

	@Override
	public void onStart() {
		super.onStart();
		
		Log.d(TAG, "UtilActivity: onStart");
	}

	@Override
	public void onStop() {
		super.onStop();
		
		Log.d(TAG, "UtilActivity: onStop");
		
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);

	}

	public void killApp() {
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	public void shareOnFacebook(int level, long score, int obstacles) {

		Log.d(TAG, "UtilActivity: shareOnFacebook");

		String name = "Turbo Race";
		String picture = "http://carlospinan.com/icon/turbo_race.png";
		String link = "https://play.google.com/store/apps/details?id=com.carlospinan.turborace";

	}

	public void publishFeedDialog(String name, String caption,
			String description, String link, String picture) {

		Log.d(TAG, "UtilActivity: publishFeedDialog");
		
		final Context context = null;


		AlertDialog.Builder builder = new AlertDialog.Builder(context);
		builder.setMessage("Facebook app not available.");
		builder.setNeutralButton(
				context.getResources().getString(android.R.string.ok), null);
		builder.create().show();

	}



	/*
	 * Cocos2d-x Library
	 */
	static {
		System.loadLibrary("game");
	}

}
