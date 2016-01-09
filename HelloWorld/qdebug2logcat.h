#ifndef QDEBUG2LOGCAT
#define QDEBUG2LOGCAT

#ifdef ANDROID
void installLogcatMessageHandler(const char *TAG);
#else
#define installLogcatHandler(TAG)
#endif

#endif // QDEBUG2LOGCAT

