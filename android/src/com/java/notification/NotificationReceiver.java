package com.java.notification;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.app.PendingIntent;

public class NotificationReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
          String extra = intent.getStringExtra("info");

          if (extra.equals("play")) {
              NativeFunctions.javaPlayButtonClicked();
          } else if (extra.equals("next")) {
              NativeFunctions.javaNextButtonClicked();
          } else if (extra.equals("previous")) {
              NativeFunctions.javaPreviousButtonClicked();
          }
    }
}
