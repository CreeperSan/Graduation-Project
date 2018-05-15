package com.creepersan.farm.extend.module

import android.util.Log
import com.taobao.weex.annotation.JSMethod
import com.taobao.weex.common.WXModule

class LogModule : WXModule() {

    @JSMethod(uiThread = false)
    fun log(content:String){
        Log.i("JS的打印", content)
    }

}