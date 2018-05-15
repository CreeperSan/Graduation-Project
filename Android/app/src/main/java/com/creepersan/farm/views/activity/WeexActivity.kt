package com.creepersan.farm.views.activity

import android.os.Bundle
import android.view.View
import com.taobao.weex.IWXRenderListener
import com.taobao.weex.WXSDKInstance
import com.taobao.weex.common.WXRenderStrategy
import com.taobao.weex.utils.WXFileUtils

class WeexActivity : BaseActivity(), IWXRenderListener {

    companion object {
        const val TEMPLATE_STR = "FARM"

        const val KEY_INTENT_WEEX_URI = "WeexUri"
        const val DEFAULT_INTENT_WEEX_URI = "MainView.js"
    }

    private lateinit var mWXSDKInstance : WXSDKInstance
    private lateinit var mIntentWeexUri: String


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        initIntent()
        initActionBar()
        initWeex()
    }

    private fun initIntent(){
        mIntentWeexUri = intent.getStringExtra(KEY_INTENT_WEEX_URI) ?: DEFAULT_INTENT_WEEX_URI
    }
    private fun initActionBar() {
        supportActionBar?.hide()
    }
    private fun initWeex(){
        mWXSDKInstance = WXSDKInstance(this)
        mWXSDKInstance.registerRenderListener(this)
        mWXSDKInstance.render(TEMPLATE_STR, WXFileUtils.loadAsset(mIntentWeexUri,this),
                null,null, WXRenderStrategy.APPEND_ASYNC)
    }

    /**
     * 往下是生命周期
     */
    override fun onResume() {
        super.onResume()
        mWXSDKInstance.onActivityResume()
    }
    override fun onPause() {
        super.onPause()
        mWXSDKInstance.onActivityPause()
    }
    override fun onStop() {
        super.onStop()
        mWXSDKInstance.onActivityStop()
    }
    override fun onDestroy() {
        super.onDestroy()
        mWXSDKInstance.onActivityDestroy()
    }


    /**
     * 往下是weex的回调函数
     */
    override fun onRefreshSuccess(instance: WXSDKInstance?, width: Int, height: Int) {
        log("onRefreshSuccess")
    }
    override fun onException(instance: WXSDKInstance?, errCode: String?, msg: String?) {
        log("onException")
    }
    override fun onRenderSuccess(instance: WXSDKInstance?, width: Int, height: Int) {
        log("onRenderSuccess")
    }
    override fun onViewCreated(instance: WXSDKInstance?, view: View?) {
        setContentView(view)
        log("onViewCreated")
    }

    override fun onBackPressed() {
        super.onBackPressed()
    }

}