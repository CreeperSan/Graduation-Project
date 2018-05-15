package com.creepersan.farm.broadcast

import android.app.Activity
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.util.Log
import java.lang.ref.WeakReference
import java.util.*

class ExitBroadcastReceiver(var activityList: LinkedList<WeakReference<Activity>>) : BroadcastReceiver() {
    companion object {
        const val ACTION = "com.creepersan.farm.ExitBroadcastReceiver.action_exit"

        const val KEY_TYPE = "Type"
        const val TYPE_FINISH_TOP = 1
        const val TYPE_FINISH_ALL = 0
        const val TYPE_NONE       = -1
    }

    override fun onReceive(context: Context?, intent: Intent?) {
        intent?.let {
            val intentType = intent.getIntExtra(KEY_TYPE, TYPE_NONE)
            when(intentType){
                TYPE_FINISH_TOP -> {//结束栈顶Activity
                    log("结束栈顶Activity")
                    activityList.firstOrNull()?.get()?.finish()
                }
                TYPE_FINISH_ALL -> {//结束所有Activity
                    log("结束所有Activity")
                    activityList.forEach {
                        it.get()?.finish()
                    }
                }
                else -> {//没有匹配到处理动作
                    Log.w(javaClass.simpleName,"收到了广播，类型未知 $intentType")
                }
            }
        }
    }

    private fun log(content:String){
        Log.i("ExitBroadcastReceiver",content)
    }
}