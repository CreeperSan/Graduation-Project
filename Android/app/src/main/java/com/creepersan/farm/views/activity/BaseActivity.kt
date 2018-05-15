package com.creepersan.farm.views.activity

import android.support.v7.app.AppCompatActivity
import android.util.Log

open class BaseActivity : AppCompatActivity() {

    fun log(content:String, tag:String = javaClass.simpleName,level : Int = 2){
        when(level){
            0 -> { Log.v(tag,content) }
            1 -> { Log.d(tag,content) }
            2 -> { Log.i(tag,content) }
            3 -> { Log.w(tag,content) }
            4 -> { Log.e(tag,content) }
        }
    }

}