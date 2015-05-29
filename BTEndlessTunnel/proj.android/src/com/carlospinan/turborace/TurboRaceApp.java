package com.carlospinan.turborace;

import com.lootsie.sdk.lootsiehybrid.Lootsie;
import com.lootsie.sdk.lootsiehybrid.LOOTSIE_CONFIGURATION;
import com.lootsie.sdk.lootsiehybrid.LOOTSIE_NOTIFICATION_CONFIGURATION;
import com.lootsie.sdk.utils.Logs;
import com.lootsie.sdk.utils.LootsieGlobals;
import com.lootsie.sdk.utils.LootsieGlobals.LOOTSIE_LOGGING_LEVEL;

import android.app.Application;

public class TurboRaceApp extends Application {

	 private static final String TAG = TurboRaceApp.class.getName();
	 
    @Override
    public void onCreate() {
        super.onCreate();

        Logs.v(TAG,"LootsieApp: App init");	 
        
        Lootsie.setLogLevel(LootsieGlobals.LOOTSIE_LOGGING_LEVEL.VERBOSE);
        
        // turbo race android - on live AC254671B2752EF9BF4F8ACA24F9F717B17B5BC900A233C4AE49DE215B6E8FE3
        Lootsie.init(this, "AC254671B2752EF9BF4F8ACA24F9F717B17B5BC900A233C4AE49DE215B6E8FE3", null);
 
    }
}
