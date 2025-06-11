#include <jni.h>
#include "react-native-crosssqlite.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_crosssqlite_CrosssqliteModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return crosssqlite::multiply(a, b);
}
