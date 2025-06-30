#include <jni.h>
#include "sqlite_bridge.h"
#include "react-native-crosssqlite.h"

// ✅ EXACT class path: com.crosssqlite.CrosssqliteModule
extern "C"
JNIEXPORT jdouble JNICALL
Java_com_crosssqlite_CrosssqliteModule_nativeMultiply(JNIEnv* env, jclass, jdouble a, jdouble b) {
  return crosssqlite::multiply(a, b);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_crosssqlite_CrosssqliteModule_nativeOpen(JNIEnv* env, jclass, jstring path) {
  const char* nativePath = env->GetStringUTFChars(path, nullptr);
  int rc = open_db(nativePath);
  env->ReleaseStringUTFChars(path, nativePath);
  return rc;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_crosssqlite_CrosssqliteModule_nativeExec(JNIEnv* env, jclass, jstring sql) {
  const char* nativeSql = env->GetStringUTFChars(sql, nullptr);
  int rc = exec_sql(nativeSql);
  env->ReleaseStringUTFChars(sql, nativeSql);
  return rc;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_crosssqlite_CrosssqliteModule_nativeClose(JNIEnv* env, jclass) {
  close_db();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_crosssqlite_CrosssqliteModule_nativeSelect(JNIEnv* env, jclass, jstring sql) {
  const char* nativeSql = env->GetStringUTFChars(sql, nullptr);
  const char* result = select_json(nativeSql);
  env->ReleaseStringUTFChars(sql, nativeSql);
  return env->NewStringUTF(result);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_crosssqlite_CrosssqliteModule_nativeGetJournalMode(JNIEnv* env, jclass) {
  const char* mode = get_journal_mode();
  return env->NewStringUTF(mode);
}
