#include "mediacontrolnotification.h"
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QGuiApplication>

//java function definitions
static void javaPlayButtonClicked(JNIEnv * /*env*/, jobject /*obj*/)
{
    emit MediaControlNotification::instance()->playButtonClicked();
}

static void javaNextButtonClicked(JNIEnv * /*env*/, jobject /*obj*/)
{
    emit MediaControlNotification::instance()->nextButtonClicked();
}

static void javaPreviousButtonClicked(JNIEnv * /*env*/, jobject /*obj*/)
{

    emit MediaControlNotification::instance()->previousButtonClicked();
}

MediaControlNotification *MediaControlNotification::m_instance = nullptr;

MediaControlNotification::MediaControlNotification(QObject *parent) : QObject(parent)
{
    m_instance = this;

    connect(this, &MediaControlNotification::onNotificationUpdate, this, &MediaControlNotification::showNotification);

    //register functions in JM env
    JNINativeMethod methods[] {{"javaPlayButtonClicked", "()V", (void *)javaPlayButtonClicked},
                               {"javaPreviousButtonClicked", "()V", (void *)javaPreviousButtonClicked},
                               {"javaNextButtonClicked", "()V", (void *)javaNextButtonClicked}};
    QAndroidJniObject javaClass("com/java/notification/NativeFunctions");

    QAndroidJniEnvironment env;
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
}

void MediaControlNotification::showNotification(QString string, bool paused) {
    QAndroidJniObject name = QAndroidJniObject::fromString(string);
    jboolean state = paused;
    QAndroidJniObject::callStaticMethod<void>("com/java/notification/MediaControlNotification",
                                              "notify",
                                              "(Landroid/content/Context;Ljava/lang/String;Z)V",
                                              QtAndroid::androidContext().object(),
                                              name.object<jstring>(),
                                              state);
}

void MediaControlNotification::notificate(QString string, bool paused) {
    emit onNotificationUpdate(string, paused);
}

