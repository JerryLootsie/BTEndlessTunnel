package com.carlospinan.utils;

import java.util.ArrayList;

import android.app.AlertDialog;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.util.Log;


//import com.carlospinan.turborace.R;
import com.lootsie.turborace.R;
//import com.google.android.gms.games.Games;
import com.lootsie.sdk.callbacks.IAchievementReached;
import com.lootsie.sdk.callbacks.IRedeemReward;
import com.lootsie.sdk.lootsiehybrid.Lootsie;
import com.lootsie.sdk.lootsiehybrid.LootsieEngine;
import com.lootsie.sdk.model.Achievement;
import com.lootsie.sdk.model.Reward;
import com.lootsie.sdk.utils.Logs;

/**
 * 
 * @author Carlos Eduardo Pi�an Indacochea
 * @version 1.0.0
 * @date 2014/02/25
 * @update 2014/02/25
 * @reference http://www.cocos2d-x.org/forums/6/topics/28296?r=28417
 * @description Class to support Google Play Game Services and Ouya cocos2d-x
 *              integration.
 */
public class NativeUtils {

	// Important variables
	private static Context context = null;
	private static UtilActivity app = null;
	private static NativeUtils instance = null;

	private static String TAG = "NativeUtils";
	
	// ID's
	private static final int REQUEST_ACHIEVEMENTS = 10000;
	private static final int REQUEST_LEADERBOARDS = 10001;
	private static final int REQUEST_LEADERBOARD = 10002;

    class RedeemRewardCallback implements IRedeemReward {

		@Override
		public void onRedeemFailed(String arg0) {
			Logs.v(TAG, "NativeUtils: onRedeemFailed: " + arg0);
			
			// be careful we don't return null, or JNI runtime check will barf			
			String returnMesg = arg0 == null ? "" : arg0;
			nativeRedeemRewardResponse(false, returnMesg);
		}

		@Override
		public void onRedeemSuccess(String arg0) {
			Logs.v(TAG, "NativeUtils: onRedeemSuccess: " + arg0);
			
			// be careful we don't return null, or JNI runtime check will barf
			String returnMesg = arg0 == null ? "" : arg0;
			nativeRedeemRewardResponse(true, returnMesg);
		}
    	
    }
    
    RedeemRewardCallback redeemRewardCallback = new RedeemRewardCallback();
    
	class AchievementReachedCallback implements IAchievementReached {

		public AchievementReachedCallback() {
			Log.v(TAG,"AchievmentReachedCallback: constructor");			
		}
		
        @Override
        public void onLootsieBarClosed() {
            Log.v(TAG, "NativeUtils: onLootsieBarClosed");
            
            // if we let Lootsie handle the rewards page, we need to suspend and then resume cocos2d
            //app.onResume();
        }

        @Override
        public void onLootsieBarExpanded() {
            Log.v(TAG, "NativeUtils: onLootsieBarExpanded");
            
            // if we let Lootsie handle the rewards page, we need to suspend and then resume cocos2d
            //app.onPause();
            
            nativeAchievementReachedIANClicked("test from Android");
        }

        @Override
        public void onLootsieFailed(String mesg) {
            Log.v(TAG, "NativeUtils: onLootsieFailed: " + mesg);
            
            nativeAchievementReachedFailed("achievement failed");
        }

        @Override
        public void onLootsieSuccess() {
            Log.v(TAG, "NativeUtils: onLootsieSuccess");
            
            nativeAchievementReachedSuccess("achievement reached");
        }

        @Override
        public void onNotificationData(String json) {
            Log.v(TAG, "NativeUtils: onNotificationData: " + json);
            
            nativeAchievementReachedNotificationData(json);
            
//            String jsonCopy = new String(json);
//            nativeAchievementReachedNotificationData(jsonCopy);
            
            //nativeAchievementReachedNotificationData("{}");
        }
    }

	public AchievementReachedCallback achievementReachedCallback = null;
  	
	
	/**
	 * Singleton
	 */
	public static NativeUtils sharedInstance() {
		if (instance == null) {
			instance = new NativeUtils();
		}
		return instance;
	}
	
	public NativeUtils() {
		Log.v(TAG, "NativeUtils: constructor");
		
		achievementReachedCallback = new AchievementReachedCallback();		
	}

	
	/**
	 * Configura los datos iniciales para comunicar los eventos de aqu� a
	 * cocos2d-x.
	 */
	public static void configure(Context context) {
		NativeUtils.context = context;
		NativeUtils.app = (UtilActivity) NativeUtils.context;

	}

	/**
	 * 
	 * @param message
	 */
	public static void displayAlert(final String message) {
		Log.d(UtilActivity.TAG, "NativeUtils: displayAlert: " + message);
		/*
		 * AlertDialog.Builder builder = new AlertDialog.Builder(context);
		 * builder.setMessage(message); builder.setNeutralButton(
		 * context.getResources().getString(android.R.string.ok), null);
		 * builder.create().show();
		 */
	}

	/*
	 * Google play games services methods. Requirements:
	 * google-play-services_lib as library.
	 */

	/**
	 * Check if user is Signed In.
	 */
	public static boolean isSignedIn() {
		return app.getSignedIn();
	}

	/**
	 * Google Play Games Services Sign In
	 */
	public static void gameServicesSignIn() {
		Log.d(TAG, "NativeUtils: gameServicesSignIn");
	}

	/**
	 * Google Play Games Services Sign Out
	 */
	public static void gameServicesSignOut() {
		Log.d(TAG, "NativeUtils: gameServicesSignOut");
	}

	/**
	 * Submit a score in a leaderboard.
	 * 
	 * @param leaderboardID
	 * @param score
	 */
	public static void submitScore(final String leaderboardID, final long score) {
		Log.d(TAG, "NativeUtils: submitScore: " + score );
	}

	/**
	 * Unlock an achievement.
	 * 
	 * @param achievementId
	 */
	public static void unlockAchievement(final String achievementID) {		
		Log.d(TAG, "NativeUtils: unlockAchievement: " + achievementID );
				
		NativeUtils utils = NativeUtils.sharedInstance();
		Lootsie.AchievementReached(app,achievementID, LootsieEngine.DEFAULT_POSITION, utils.achievementReachedCallback);		
	}
	
	public static void redeemReward(final String emailStr, final String rewardIdStr) {
		Log.d(TAG, "NativeUtils: redeemReward: email: " + emailStr + " rewardId: " + rewardIdStr );
		
		//Lootsie.redeemReward(emailStr, rewardIdStr);
		
		NativeUtils utils = NativeUtils.sharedInstance();
		Lootsie.redeemReward(emailStr, rewardIdStr, utils.redeemRewardCallback);
	}
	

	/**
	 * Increment the achievement in numSteps.
	 * 
	 * @param achievementId
	 * @param numSteps
	 */
	public static void incrementAchievement(final String achievementID,
			final int numSteps) {		
		Log.d(TAG, "NativeUtils: incrementAchievement: " + achievementID + " : " + numSteps);
	}

	/**
	 * Show all achievements.
	 */
	public static void showAchievements() {
		Log.v(TAG,"NativeUtils: showAchievements");
		
		app.runOnUiThread(new Runnable() {

			@Override
			public void run() {		
				Lootsie.showAchievementsPage(app);
			}
		});
	}

	/**
	 * Show all achievements.
	 */
	public static void getAchievements() {
		Log.v(TAG,"NativeUtils: getAchievements 9/10/2015");
		
//		app.runOnUiThread(new Runnable() {
//
//			@Override
//			public void run() {		
//				Lootsie.showAchievementsPage(app);
//			}
//		});
		
		//ArrayList<Achievement> testAchievments = new ArrayList<Achievement>();
		
		ArrayList<Achievement> testAchievments = Lootsie.getAppAchievements();
		if (testAchievments != null) {
			Log.v(TAG,"NativeUtils: getAchievements: " + testAchievments.size());
		}
		
		nativeMono("test from Android", testAchievments);
		//nativeMono("test from Android");
		
	}	
	
	public static void getRewards() {
		Log.v(TAG, "NativeUtils: getRewards");
		
		ArrayList<Reward> testRewards = Lootsie.getUserRewards();
		if (testRewards != null) {
			Log.v(TAG,"NativeUtils: getRewards: " + testRewards.size());
		}
		
		nativeGetRewards("test from Android", testRewards);
	}
	
	/**
	 * Show all leaderboard.
	 */
	public static void showLeaderboards() {
		Log.v(TAG,"NativeUtils: showLeaderboards");
		
		// just kick off an achievment instead
		//NativeUtils utils = NativeUtils.sharedInstance();
		//Lootsie.AchievementReached(app,"ACH_AVOID_3_OBSTACLES_IN_EASY_MODE", LootsieEngine.DEFAULT_POSITION, utils.achievementReachedCallback);
	}

	/**
	 * Show single leaderboard.
	 */
	public static void showLeaderboard(final String leaderboardID) {
		Log.v(TAG,"NativeUtils: showLeaderboard: " + leaderboardID);
		
		Lootsie.showAchievementsPage(app);
	}

	/**
	 * 
	 * @param key
	 * @param app_state
	 */
	public static void inCloudSaveOrUpdate(final int key, final byte[] app_state) {
		Log.v(TAG,"NativeUtils: inCloudSaveOrUpdate");
		return;
	}

	/**
	 * 
	 * @param key
	 */
	public static void inCloudLoad(final int key) {
		Log.v(TAG,"NativeUtils: inCloudLoad");
		return;
	}

	/*
	 * Show and Hide AdView
	 */

	public static void showAd() {
		Log.v(TAG,"NativeUtils: showAd");
	}

	public static void hideAd() {
		Log.v(TAG,"NativeUtils: hideAd");
	}

	public static void rateApp() {		
		Log.v(TAG,"NativeUtils: rateApp");		
	}

	public static void shareOnFacebook(final int level, final long score,
			final int obstacles) {
		Log.v(TAG,"NativeUtils: shareOnFacebook");
	}

	public static void showAdBuddiz() {
		Log.v(TAG,"NativeUtils: showAdBuddiz");
	}

	public static void sendAnalytics(final String screen) {
		Log.v(TAG,"NativeUtils: sendAnalytics");
	}

	public static void killApp() {
		app.killApp();
	}

	/*
	 * Ouya support Note: For Ouya support need uncomment the <category
	 * android:name="tv.ouya.intent.category.GAME" /> in the AndroidManifest.xml
	 */

	/*
	 * Native call
	 */

	public static native void notifyInCloudSavingOrUpdate();

	public static native void notifyInCloudLoad();

	static native void nativeMono(String testStr, ArrayList<Achievement> lootsieAchievements);
	static native void nativeGetRewards(String testStr, ArrayList<Reward> lootsieRewards);
	static native void nativeRedeemRewardResponse(boolean result, String testStr);
	static native void nativeAchievementReachedIANClicked(String testStr);
	
	static native void nativeAchievementReachedSuccess(String testStr);
	static native void nativeAchievementReachedFailed(String testStr);
	static native void nativeAchievementReachedNotificationData(String testStr);	
	
}
