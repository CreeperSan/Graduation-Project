package com.creepersan.farm.extend.adapter

import android.content.Intent
import android.util.Log
import com.creepersan.farm.FarmApplication
import com.creepersan.farm.views.activity.WeexActivity
import com.creepersan.farm.broadcast.ExitBroadcastReceiver
import com.taobao.weex.appfram.navigator.IActivityNavBarSetter
import org.json.JSONException
import org.json.JSONObject

class NavigatorAdapter : IActivityNavBarSetter {
    companion object {
        const val DEFAULT_URL = ""
        const val DEFAULT_IS_ANIMATED = true

        const val KEY_JSON_PUSH_ANIMATED = "animated"
        const val KEY_JSON_PUSH_URL = "url"
    }

    override fun clearNavBarLeftItem(param: String?): Boolean {
        log("clearNavBarLeftItem => $param",true)
        return true
    }

    override fun clearNavBarMoreItem(param: String?): Boolean {
        log("clearNavBarMoreItem => $param",true)
        return true
    }

    override fun setNavBarLeftItem(param: String?): Boolean {
        log("setNavBarLeftItem => $param",true)
        return true
    }

    override fun setNavBarRightItem(param: String?): Boolean {
        log("setNavBarRightItem => $param",true)
        return true
    }

    override fun push(param: String?): Boolean {
        log("要跳转的内容 $param")
        try {
//            val jsonObj = JSONObject(param)
//            val isAnimated = jsonObj.optBoolean(KEY_JSON_PUSH_ANIMATED, DEFAULT_IS_ANIMATED)
//            var url = jsonObj.optString(KEY_JSON_PUSH_URL, DEFAULT_URL)
            val intent = Intent(FarmApplication.getApplication(), WeexActivity::class.java)
//            url = url.substring(url.lastIndexOf("/views/") + 1)
            try {
                intent.putExtra(WeexActivity.KEY_INTENT_WEEX_URI, param?.substring(14) ?: "MainView.js")
            }catch (e:Exception){}
//            intent.putExtra(WeexActivity.KEY_INTENT_WEEX_URI, url)
//            intent.flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS
            FarmApplication.getApplication().startActivity(intent)
//            log("push() => $url")
        }catch (e:Exception){
            e.printStackTrace()
            log("push() => JSON解析数据发生问题,"+ e.toString())
            when(e){
                is JSONException -> {
                    log("push() => JSON解析数据发生问题, $param")
                }
                else -> {
                    log("push() => 发生异常, $param\"")
                }
            }
        }

        return true
    }

    override fun clearNavBarRightItem(param: String?): Boolean {
        log("clearNavBarRightItem => $param",true)
        return true
    }

    override fun pop(param: String?): Boolean {
        log("pop => $param")
        val intent = Intent(ExitBroadcastReceiver.ACTION)
        intent.putExtra(ExitBroadcastReceiver.KEY_TYPE,ExitBroadcastReceiver.TYPE_FINISH_TOP)
        FarmApplication.getApplication().sendBroadcast(intent)
        return true
    }

    override fun setNavBarTitle(param: String?): Boolean {
        log("setNavBarTitle => $param",true)
        return true
    }

    override fun setNavBarMoreItem(param: String?): Boolean {
        log("setNavBarMoreItem => $param",true)
        return true
    }

    private fun log(content:String,isError:Boolean = false){
        if (isError){
            Log.e(javaClass.simpleName,content)
        }else{
            Log.i(javaClass.simpleName,content)
        }
    }
}