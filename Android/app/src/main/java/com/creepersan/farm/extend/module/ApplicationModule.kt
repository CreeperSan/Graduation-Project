package com.creepersan.farm.extend.module

import com.creepersan.farm.util.ServiceAddressScanner
import com.taobao.weex.annotation.JSMethod
import com.taobao.weex.bridge.JSCallback
import com.taobao.weex.common.WXModule

class ApplicationModule : WXModule() {
    private companion object {
        const val KEY_ADDRESS = "address"
        const val KEY_TOKEN = "token"
    }

    @JSMethod(uiThread = false)
    fun getDataBundle(jsCallback: JSCallback){
        jsCallback.invoke(HashMap<String,Any>().apply {
            put(KEY_ADDRESS, ServiceAddressScanner.getInstance().getAddress())
            put(KEY_TOKEN, "")
        })
    }

    @JSMethod(uiThread = true)
    fun getApplicationVersion(jsCallback: JSCallback){
        val context = mWXSDKInstance.context
        jsCallback.invoke(context.packageManager.getPackageInfo(context.packageName,0).versionName)
    }
}