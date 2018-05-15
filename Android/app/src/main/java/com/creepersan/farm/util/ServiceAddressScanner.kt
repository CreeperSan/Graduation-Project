package com.creepersan.farm.util

import android.content.Context
import android.net.wifi.WifiManager
import android.util.Log
import com.creepersan.farm.FarmApplication
import com.creepersan.farm.extend.module.LogModule
import org.json.JSONObject
import java.net.DatagramPacket
import java.net.DatagramSocket
import java.net.InetAddress
import java.net.SocketAddress

class ServiceAddressScanner private constructor(){
    // 单例实现
    companion object {
        private const val PORT_SEND = 20000
        private const val PORT_RECV = 20001


        private const val COUNT_MAX = 3

        private const val KEY_IP_ADDRESS = "ipaddress"

        private var sInstance : ServiceAddressScanner? = null

        fun getInstance():ServiceAddressScanner{
            if (sInstance == null){
                sInstance = ServiceAddressScanner()
            }
            return sInstance!!
        }

    }




    //　属性
    var isLocal : Boolean = false
        private set(value){ field = value }

    private var localAddress = ""
    private val remoteAddress = "http://me.farm.creepersan.com/"
    private var isRunning = false // 是否运行扫描
    private var scanSnap = 1000L // 扫描时间间隔
    private var recThread : RecThread? = null
    private var sendThread : SendThread? = null
    private var udpSocket : DatagramSocket? = null

    private var count = 0
    private val countLock = Any()

    fun getAddress():String{
        return if (isLocal) {
            localAddress
        }else{
            remoteAddress
        }
    }

    fun start(){
        if (!isRunning){
            isRunning = true
            udpSocket = DatagramSocket(PORT_RECV)
//            udpSocket = DatagramSocket()
            recThread = RecThread()
            recThread?.start()
            sendThread = SendThread()
            sendThread?.start()
        }
    }

    fun stop(){
        if (isRunning){
            isRunning = false
            recThread?.interrupt()
            sendThread?.interrupt()
            recThread = null
            sendThread = null
            udpSocket?.close()
            udpSocket = null
        }
    }

    private inner class RecThread : Thread(){
        override fun run() {
            super.run()
            val multicastLock = (FarmApplication.getApplication().getApplicationContext().getSystemService(Context.WIFI_SERVICE) as WifiManager).createMulticastLock("tag")
            multicastLock.acquire()
            val buffer = ByteArray(1024,{0})
            val recPacket = DatagramPacket(buffer,buffer.size)
            log("接受运行中")
            while(isRunning && udpSocket!=null){
                udpSocket?.receive(recPacket)
                val recData = String(recPacket.data,0,recPacket.length)
                log("接受到数据 => ${recData}")
                val tempJson = JSONObject(recData)
                if (tempJson.has(KEY_IP_ADDRESS)){
                    localAddress = "http://${tempJson.getString(KEY_IP_ADDRESS)}:8000/"
                    clearCount()
                    countAction()
                    log("更新服务器地址 => ${localAddress}")
                }
            }

            log("接受运行完毕")
            multicastLock.release()
        }
    }
    private inner class SendThread : Thread(){

        override fun run() {
            super.run()
            while(isRunning){
                val msg= "{\"timestamp\":${System.currentTimeMillis()}}".toByteArray()
                udpSocket?.send(DatagramPacket(msg,0,msg.size, InetAddress.getByName("255.255.255.255"), PORT_SEND))
                addCount()
                countAction()
                log("发送 => ${String(msg)}")
                Thread.sleep(scanSnap)
            }
        }
    }

    /**
     * 计数值相关的同步方法
     */
    private fun addCount(){
        synchronized(countLock,{
            count+=1
        })
    }
    private fun clearCount(){
        synchronized(countLock,{
            count = 0
        })
    }
    private fun countAction(){
        var tempCount = 0;
        synchronized(countLock,{
            tempCount = count
        })
        isLocal = tempCount < COUNT_MAX
    }


    /**
     * 调试方法
     */
    private fun log(content:String){
        Log.i(javaClass.simpleName, content)
    }
}