package com.java.notification;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;

public class NotificationReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        String action = intent.getAction();

        if (action.equalsIgnoreCase("com.adjsky.mp3player.PREVIOUS_PLAY")) {
            NativeFunctions.javaPreviousButtonClicked();
        }
        else if (action.equalsIgnoreCase("com.adjsky.mp3player.NEXT_PLAY")) {
            NativeFunctions.javaNextButtonClicked();
        }
        else if (action.equalsIgnoreCase("com.adjsky.mp3player.PLAY_PAUSE")) {
            NativeFunctions.javaPlayButtonClicked();
        }
    }
}
