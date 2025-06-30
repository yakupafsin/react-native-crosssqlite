package com.crosssqlite

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.module.annotations.ReactModule

@ReactModule(name = CrosssqliteModule.NAME)
class CrosssqliteModule(reactContext: ReactApplicationContext) :
  NativeCrosssqliteSpec(reactContext) {

  override fun getName(): String = NAME

  override fun multiply(a: Double, b: Double): Double {
    return nativeMultiply(a, b)
  }

  override fun open(path: String): Double {
    return nativeOpen(path).toDouble() // 🔥 FIXED: return type matches TurboModule definition
  }

  override fun exec(sql: String): Double {
    return nativeExec(sql).toDouble() // 🔥 FIXED
  }

  override fun close() {
    nativeClose()
  }

  override fun select(sql: String): String {
    return nativeSelect(sql)
  }

  override fun getJournalMode(): String {
    return nativeGetJournalMode()
  }

  companion object {
    const val NAME = "Crosssqlite"

    @JvmStatic external fun nativeMultiply(a: Double, b: Double): Double
    @JvmStatic external fun nativeOpen(path: String): Int
    @JvmStatic external fun nativeExec(sql: String): Int
    @JvmStatic external fun nativeClose()
    @JvmStatic external fun nativeSelect(sql: String): String
    @JvmStatic external fun nativeGetJournalMode(): String
  }

  init {
    System.loadLibrary("react-native-crosssqlite")
  }
}
