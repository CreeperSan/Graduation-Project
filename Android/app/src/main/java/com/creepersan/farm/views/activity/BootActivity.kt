package com.creepersan.farm.views.activity

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import com.creepersan.farm.R

class BootActivity : AppCompatActivity() {
    companion object {
        private const val DELAY_TIME = 1000L
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        initActionBar()
        initTimeTask()
    }

    private fun initActionBar() {
        supportActionBar?.hide()
    }
    private fun initTimeTask(){
        Handler().postDelayed({
            startActivity(Intent(this, WeexActivity::class.java))
            finish()
        }, DELAY_TIME)
    }
}
