package com.creepersan.farm

import android.app.Activity
import android.app.Application
import android.content.IntentFilter
import android.os.Bundle
import android.os.StrictMode
import com.creepersan.farm.broadcast.ExitBroadcastReceiver
import com.creepersan.farm.extend.adapter.GlideImageAdapter
import com.creepersan.farm.extend.adapter.NavigatorAdapter
import com.creepersan.farm.extend.module.ApplicationModule
import com.creepersan.farm.extend.module.LogModule
import com.creepersan.farm.extend.module.ServerModule
import com.creepersan.farm.util.ServiceAddressScanner
import com.taobao.weex.InitConfig
import com.taobao.weex.WXSDKEngine
import com.taobao.weex.WXSDKInstance
import java.lang.ref.WeakReference
import java.util.*

class FarmApplication : Application(),Application.ActivityLifecycleCallbacks{
    private val mActivityList = LinkedList<WeakReference<Activity>>()
    private lateinit var mExitBroadcastReceiver : ExitBroadcastReceiver

    companion object {
        private var sInstance : FarmApplication? = null

        fun getApplication():FarmApplication{
            return sInstance ?: FarmApplication()
        }
    }

    init {
        sInstance = this
    }

    override fun onCreate() {
        super.onCreate()

        initUri()
        initBroadcastReceiver()
        initActivityLifeRecycler()
        initWeex()
        initAddressService()

    }

    /**
     *  初始化
     */
    private fun initUri(){
        //API18 以上才能运行
        val builder = StrictMode.VmPolicy.Builder()
        StrictMode.setVmPolicy(builder.build())
        builder.detectFileUriExposure()
    }
    private fun initBroadcastReceiver(){
        mExitBroadcastReceiver = ExitBroadcastReceiver(mActivityList)
        registerReceiver(mExitBroadcastReceiver, IntentFilter(ExitBroadcastReceiver.ACTION))
    }
    private fun initActivityLifeRecycler(){
        registerActivityLifecycleCallbacks(this)
    }
    private fun initWeex(){
        WXSDKEngine.initialize(this,InitConfig.Builder()
                .setImgAdapter(GlideImageAdapter())
                .build())

        WXSDKEngine.registerModule("server",ServerModule::class.java)
        WXSDKEngine.registerModule("log",LogModule::class.java)
        WXSDKEngine.registerModule("application",ApplicationModule::class.java)

        WXSDKEngine.setActivityNavBarSetter(NavigatorAdapter())
    }
    private fun initAddressService(){
        ServiceAddressScanner.getInstance().start()
    }

    fun exitApplication(){
        ServiceAddressScanner.getInstance().stop()
    }

    /**
     *  Activity生命周期
     */
    override fun onActivityPaused(activity: Activity?) {}
    override fun onActivityResumed(activity: Activity?) {}
    override fun onActivityStarted(activity: Activity?) {}
    override fun onActivityStopped(activity: Activity?) {}
    override fun onActivityDestroyed(activity: Activity?) {
        val iterator = mActivityList.iterator()
        iterator.forEach { tempActivity ->
            if (tempActivity.get() == activity){
                iterator.remove()
                return@forEach
            }
        }
    }
    override fun onActivityCreated(activity: Activity?, savedInstanceState: Bundle?) {
        activity?.let { mActivityList.addFirst(WeakReference(activity)) }
    }
    override fun onActivitySaveInstanceState(activity: Activity?, outState: Bundle?) {}
}