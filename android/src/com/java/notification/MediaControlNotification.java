package com.java.notification;

import android.app.Notification;
import android.content.Intent;
import android.content.Context;
import android.app.NotificationChannel;
import android.app.PendingIntent;
import android.os.Handler;
import android.widget.Toast;
import android.os.Message;
import android.graphics.Color;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Bundle;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.R;


public class MediaControlNotification
{
    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;

    public MediaControlNotification() {}

    public static void notify(Context context, String string) {
        try {
            m_notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                int importance = NotificationManager.IMPORTANCE_DEFAULT;
                NotificationChannel notificationChannel = new NotificationChannel("Qt", "Qt Notifier", importance);
                m_notificationManager.createNotificationChannel(notificationChannel);
                m_builder = new Notification.Builder(context, notificationChannel.getId());
            } else {
                m_builder = new Notification.Builder(context);
            }

            Intent playIntent = new Intent("com.adjsky.mp3player.PLAY_PAUSE");
            PendingIntent playPendingIntent = PendingIntent.getBroadcast(context, 0, playIntent, 0);

            Intent nextIntent = new Intent("com.adjsky.mp3player.NEXT_PLAY");
            PendingIntent nextPendingIntent = PendingIntent.getBroadcast(context, 0, nextIntent, 0);

            Intent prevIntent = new Intent("com.adjsky.mp3player.PREVIOUS_PLAY");
            PendingIntent previousPendingIntent = PendingIntent.getBroadcast(context, 0, prevIntent, 0);


            m_builder.setSmallIcon(R.drawable.sym_action_chat)
                    .setContentTitle("Playing music")
                    .setContentText(string)
                    .setStyle(new Notification.MediaStyle())
                    .addAction(R.drawable.ic_media_previous, "Previous", previousPendingIntent)
                    .addAction(R.drawable.ic_media_play, "PlayPause", playPendingIntent)
                    .addAction(R.drawable.ic_media_next, "Next", nextPendingIntent);


            m_notificationManager.notify(0, m_builder.build());           

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void removeNotification() {
        m_notificationManager.cancel(0);
    }
}


