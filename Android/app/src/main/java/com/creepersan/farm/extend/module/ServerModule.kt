package com.creepersan.farm.extend.module

import android.content.Context
import android.content.SharedPreferences
import com.taobao.weex.annotation.JSMethod
import com.taobao.weex.bridge.JSCallback
import com.taobao.weex.common.WXModule

/**
 * 用于记录和服务器的交互
 */
class ServerModule : WXModule() {
    companion object {
        private var sServerPref : SharedPreferences? = null
        private val PREF_NAME = "Server"
        private val PREF_KEY_SERVE_ADDRESS = "ServerAddress"
        private val PREF_KEY_TOKEN = "Token"

        private val VAL_KEY_ADDRESS = "address"
        private val VAL_TOKEN = "token"

        fun getPref(context:Context):SharedPreferences{
            return sServerPref ?: context.getSharedPreferences(PREF_NAME, Context.MODE_PRIVATE)
        }
    }

    @JSMethod(uiThread = true)
    fun getServerAddressAndToken(jsCallback: JSCallback){
        jsCallback.invoke(HashMap<String,String>().apply {
            val prefs = getPref(mWXSDKInstance.context)
            put(PREF_KEY_SERVE_ADDRESS, prefs.getString(PREF_KEY_SERVE_ADDRESS, ""))
            put(PREF_KEY_TOKEN, prefs.getString(PREF_KEY_TOKEN, ""))
        })
    }

    @JSMethod(uiThread = true)
    fun setServerAddress(serverAddress:String){
        getPref(mWXSDKInstance.context).edit()
                .putString(PREF_KEY_SERVE_ADDRESS, serverAddress)
                .apply()
    }

    @JSMethod(uiThread = true)
    fun setToken(token:String){
        getPref(mWXSDKInstance.context).edit()
                .putString(PREF_KEY_SERVE_ADDRESS, token)
                .apply()
    }



    @JSMethod(uiThread = false)
    fun getDataBundle(jsCallback: JSCallback){
        jsCallback.invoke(HashMap<String,String>().apply {

        })
    }


}