package com.java.notification;

import android.app.Notification;
import android.content.Intent;
import android.content.Context;
import android.app.NotificationChannel;
import android.app.PendingIntent;
import android.os.Handler;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.R;


public class MediaControlNotification
{
    public static NotificationManager m_notificationManager;
    public static Notification.Builder m_builder;

    public MediaControlNotification() {}

    public static void notify(Context context, String string, boolean paused) {
        try {          
            int icon;
            if (paused) {
                icon = R.drawable.ic_media_play;
            } else {
                icon = R.drawable.ic_media_pause;
            }
            m_notificationManager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                int importance = NotificationManager.IMPORTANCE_LOW;
                NotificationChannel notificationChannel = new NotificationChannel("Qt", "Qt Notifier", importance);
                m_notificationManager.createNotificationChannel(notificationChannel);
                m_builder = new Notification.Builder(context, notificationChannel.getId());
            } else {
                m_builder = new Notification.Builder(context);
            }

            Intent playIntent = new Intent(context, NotificationReceiver.class);
            playIntent.putExtra("info", "play");
            PendingIntent playPendingIntent = PendingIntent.getBroadcast(context, 1, playIntent, 0);

            Intent nextIntent = new Intent(context, NotificationReceiver.class);
            nextIntent.putExtra("info", "next");
            PendingIntent nextPendingIntent = PendingIntent.getBroadcast(context, 2, nextIntent, 0);

            Intent prevIntent = new Intent(context, NotificationReceiver.class);
            prevIntent.putExtra("info", "previous");
            PendingIntent previousPendingIntent = PendingIntent.getBroadcast(context, 3, prevIntent, 0);


            m_builder.setSmallIcon(icon)
                    .setContentTitle("Playing music")
                    .setContentText(string)
                    .setStyle(new Notification.MediaStyle()
                                    .setShowActionsInCompactView(1)
                    )
                    .addAction(R.drawable.ic_media_previous, "Previous", previousPendingIntent)
                    .addAction(icon, "PlayPause", playPendingIntent)
                    .addAction(R.drawable.ic_media_next, "Next", nextPendingIntent)
                    .setSound(null)
                    .setVibrate(null);

            m_notificationManager.notify(0, m_builder.build());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}


