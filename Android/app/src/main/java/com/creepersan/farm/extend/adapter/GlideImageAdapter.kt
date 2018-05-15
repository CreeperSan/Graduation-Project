package com.creepersan.farm.extend.adapter

import android.widget.ImageView
import com.bumptech.glide.Glide
import com.taobao.weex.adapter.IWXImgLoaderAdapter
import com.taobao.weex.common.WXImageStrategy
import com.taobao.weex.dom.WXImageQuality

class GlideImageAdapter : IWXImgLoaderAdapter{

    override fun setImage(url: String?, view: ImageView?, quality: WXImageQuality?, strategy: WXImageStrategy?) {
//        view?.apply {
//            Glide.with(this).load(url).into(this)
//        }

        var urls = ""
        url?.let {
            if (url.startsWith("assets://")){
                urls = url.replace("assets://","file:///android_asset/")
            }else{
                urls = url
            }
        }
        view?.let { Glide.with(it).load(urls).into(it) }
    }

}