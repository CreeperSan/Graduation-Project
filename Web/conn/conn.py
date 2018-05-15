import threading
import time
import os
import json
from django.apps import AppConfig
import state.state as state
import socket
from farm.models import Sensor as Sensor
from config import config

CONST_INT_TO_BYTE_LIST = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
CONST_IP_ADDR = '255.255.255.255'
CONST_PORT_RECV = 7000
CONST_PORT_SEND = 7001


#
# 		单例模式　&& 类
#

class UdpSocketHolder(object):
    _instance_lock = threading.Lock()

    udpSocket = None
    udpListenThread = None
    isLoad = False
    num = 0

    def __init__(self):
        time.sleep(1)

    @classmethod
    def instance(cls, *args, **kwargs):
        if not hasattr(UdpSocketHolder, '_instance'):
            with UdpSocketHolder._instance_lock:
                if not hasattr(UdpSocketHolder, '_instance'):
                    UdpSocketHolder._instance = UdpSocketHolder()
        return UdpSocketHolder._instance


class SocketListenThread(threading.Thread):
    isRunning = True

    def __intToHex(self, intDat):
        if 16 > intDat >= 0:
            return CONST_INT_TO_BYTE_LIST[intDat]
        else:
            return '[Error]'

    def bytesToHexString(self, bytesData):
        resultStr = ''
        for tempByte in bytesData:
            resultStr += self.__intToHex((int)(tempByte / 16))
            resultStr += self.__intToHex((int)(tempByte % 16))
            resultStr += ' '
        return resultStr

    def run(self):
        print('正在监听局域网的数据包')
        while (self.isRunning):
            data, addr = UdpSocketHolder.instance().udpSocket.recvfrom(1024)
            # print('数据包 => ' + self.bytesToHexString(data))

            # 11 99 FF 01 00 00 00 00 00 01 05 0A 00 16 00 2E 00 14 00 33 00 1F F0 90 10
            if (len(data) == 33 and data[0] == 0x11 and data[1] == 0x99 and data[2] == 0xff and data[30] == 0xf0 and
                    data[31] == 0x90 and data[32] == 0x10):
                # 设备部分
                temp_device1_state = 1 if (data[3] & 0x01) > 0 else 0
                temp_device2_state = 1 if (data[3] & 0x02) > 0 else 0
                temp_device3_state = 1 if (data[3] & 0x04) > 0 else 0
                temp_device4_state = 1 if (data[3] & 0x08) > 0 else 0
                config.set_devices_config(temp_device1_state, temp_device2_state, temp_device3_state,
                                          temp_device4_state)
                state.device_1 = temp_device1_state
                state.device_2 = temp_device2_state
                state.device_3 = temp_device3_state
                state.device_4 = temp_device4_state
                # 其他部分
                temp_fan_state = data[4]
                temp_warm_state = data[5]
                temp_fertilization_state = data[6]
                temp_water_state = data[7]
                temp_buzzer_state = data[8]
                # 灯光部分
                temp_light_state = data[9]
                temp_light_color = data[10]
                temp_light_level = data[11]
                state.light = temp_light_state
                state.light_color = temp_light_color
                state.light_level = temp_light_level
                # 上下限部分
                temp_air_temp = data[13]
                state.temperature_air = temp_air_temp
                temp_air_humidity = data[15]
                state.humidity_air = temp_air_humidity
                temp_dirt_temp = data[17]
                state.temperature_dirt = temp_dirt_temp
                temp_dirt_humidity = data[19]
                state.humidity_dirt = temp_dirt_humidity
                temp_ad_light = data[21]
                air_temp_up = data[22]
                air_temp_low = data[23]
                tempAirTempObj = config.get_temperature_config()
                tempAirTempObj.upperLimit = air_temp_up
                tempAirTempObj.lowerLimit = air_temp_low
                config.set_temperature_config_obj(tempAirTempObj)
                air_humidity_up = data[24]
                air_humidity_low = data[25]
                tempAirHumidityObj = config.get_humidity_config()
                tempAirHumidityObj.upperLimit = air_humidity_up
                tempAirHumidityObj.lowerLimit = air_humidity_low
                config.set_dumidity_config_obj(tempAirHumidityObj)
                dirt_temp_up = data[26] # 没用上
                dirt_temp_low = data[27] # 没用上
                dirt_humidity_up = data[28]
                dirt_humidity_low = data[29]
                tempDirtHumidityObj = config.get_dirt_humidity_config()
                tempDirtHumidityObj.upperLimit = dirt_humidity_up
                tempDirtHumidityObj.lowerLimit = dirt_humidity_low
                config.set_dirt_humidity_config_obj(tempDirtHumidityObj)
                print('设备1 => ' + str(temp_device1_state)
                      + '     设备2 => ' + str(temp_device2_state)
                      + '\n设备3 => ' + str(temp_device3_state)
                      + '     设备4 => ' + str(temp_device4_state)
                      + '\n风扇 => ' + str(temp_fan_state)
                      + '     加热膜 => ' + str(temp_warm_state)
                      + '\n施肥 => ' + str(temp_fertilization_state)
                      + '     浇水 => ' + str(temp_water_state)
                      + '\nBUzzer => ' + str(temp_buzzer_state)
                      + '     灯光 => ' + str(temp_light_state)
                      + '\n颜色 => ' + str(temp_light_color)
                      + '     亮度 => ' + str(temp_light_level)
                      + '\n气温 => ' + str(temp_air_temp)
                      + '     气湿 => ' + str(temp_air_humidity)
                      + '\n土温 => ' + str(temp_dirt_temp)
                      + '     土湿 => ' + str(temp_dirt_humidity)
                      + '     亮度 => ' + str(temp_ad_light)
                      + '\n气温上限 => ' + str(air_temp_up)
                      + '     气温下限 => ' + str(air_temp_low)
                      + '\n气湿上限 => ' + str(air_humidity_up)
                      + '     气湿下限 => ' + str(air_humidity_low)
                      + '\n土温上限 => ' + str(dirt_temp_up)
                      + '     土温下限 => ' + str(dirt_temp_low)
                      + '\n土湿上限 => ' + str(dirt_humidity_up)
                      + '     土湿下限 => ' + str(dirt_humidity_low)
                      )
                localTime = time.localtime()
                localYear = time.strftime('%Y', localTime)
                localMonth = time.strftime('%m', localTime)
                localDay = time.strftime('%d', localTime)
                localHour = time.strftime('%H', localTime)
                localMinute = time.strftime('%M', localTime)
                localSecond = time.strftime('%S', localTime)
                sensorData = Sensor(year=localYear, month=localMonth, day=localDay, hour=localHour, minute=localMinute,
                                    second=localSecond,
                                    light=temp_ad_light, air_temperature=temp_air_temp, dirt_temperature=temp_dirt_temp,
                                    air_humidity=temp_air_humidity,
                                    dirt_humidity=temp_dirt_humidity, device_id='0')
                sensorData.save()
                # 下面就很难看了，不好意思，因为时间紧迫，实在抱歉
                # 发现这里我的CONFIG里面的上下限定义都没用上，一开始没做好规划真的难受
                configTemperature = config.get_temperature_config()
                configHumidityAir = config.get_humidity_config()
                configHumidityDirt = config.get_dirt_humidity_config()
                # 温度上限处理
                flag_is_need_reset = False
                if configTemperature.isAutoControl == str(config.STATE_ON):
                    if temp_air_temp > air_temp_up:  # 温度超过上线
                        self.actionLimit(configTemperature.upperActions)
                        flag_is_need_reset = True
                    if temp_air_temp < air_temp_low:  # 温度低于下线
                        self.actionLimit(configTemperature.upperActions)
                        flag_is_need_reset = True
                if configHumidityAir.isAutoControl == str(config.STATE_ON):
                    if temp_air_humidity > dirt_humidity_up:  # 空气适度超过上线
                        self.actionLimit(configHumidityAir.upperActions)
                        flag_is_need_reset = True
                    if temp_air_humidity < air_humidity_low:  # 空气适度低于下线
                        self.actionLimit(configHumidityAir.lowerActions)
                        flag_is_need_reset = True
                if configHumidityDirt.isAutoControl == str(config.STATE_ON):
                    if temp_dirt_humidity > dirt_humidity_up:  # 土壤适度超过上线
                        self.actionLimit(configHumidityDirt.upperActions)
                        flag_is_need_reset = True
                    if temp_dirt_humidity < dirt_humidity_low:  # 土壤湿度低于下线
                        self.actionLimit(configHumidityDirt.lowerActions)
                        flag_is_need_reset = True
                if flag_is_need_reset :
                    time.sleep(0.3)
                    sendCmdReset()

    def intToHex(self,num):
        return ('0' + str(hex(num)[2:]))[-2:]

    def actionLimit(self, actions):
        # print(actions)
        print('执行任务')
        print(actions)
        for tempAction in json.loads(actions):
            print('循环')
            tempTarget = tempAction['target']
            tempOperation = tempAction['operation']
            if tempTarget == 0: # 温度自动控制
                tempperatureConfig = config.get_temperature_config()
                tempperatureConfig.isAutoControl = int(tempOperation)
                config.set_temperature_config_obj(tempperatureConfig)
            elif tempTarget == 1: # 空气适度自动控制
                humidityConfig = config.get_humidity_config()
                humidityConfig.isAutoControl = int(tempOperation)
                config.set_dumidity_config_obj(humidityConfig)
                pass
            elif tempTarget == 2: # 土壤适度自动控制
                dirtHumidity = config.get_dirt_humidity_config()
                dirtHumidity.isAutoControl = int(tempOperation)
                config.set_dirt_humidity_config_obj(dirtHumidity)
                pass
            elif tempTarget == 3: # 自动施肥
                fertilizationConfig = config.get_fertilization_config()
                config.set_fertilization_config(tempOperation, fertilizationConfig.repeatType, fertilizationConfig.repeatCircle,
                                                fertilizationConfig.hour, fertilizationConfig.minute)
            elif tempTarget == 4: # 自动浇水
                waterConfig = config.get_water_config()
                config.set_water_config(tempOperation, waterConfig.repeatType, waterConfig.repeatCircle,
                                                waterConfig.hour, waterConfig.minute)
            elif tempTarget == 5: # 施肥
                sendCmd('06',self.intToHex(tempOperation))
            elif tempTarget == 6: # 浇水
                sendCmd('07',self.intToHex(tempOperation))
            elif tempTarget == 7: # 风扇
                sendCmd('04',self.intToHex(tempOperation))
            elif tempTarget == 8: # 电热膜
                sendCmd('05',self.intToHex(tempOperation))
            elif tempTarget == 9: # 自定义设备１
                sendCmd('00',self.intToHex(tempOperation))
            elif tempTarget == 10: # 自定义设备2
                sendCmd('01',self.intToHex(tempOperation))
            elif tempTarget == 11: # 自定义设备3
                sendCmd('02',self.intToHex(tempOperation))
            elif tempTarget == 12: # 自定义设备4
                sendCmd('03',self.intToHex(tempOperation))
            elif tempTarget == 13: # 环境光控制
                sendCmd('08',self.intToHex(tempOperation))
            elif tempTarget == 14: # 环境光颜色
                sendCmd('09',self.intToHex(tempOperation))
            elif tempTarget == 15: # 环境光亮度
                sendCmd('0a',self.intToHex(tempOperation))
            print(self.intToHex(tempTarget),'  --  ',self.intToHex(tempOperation))
            # sendCmd(self.intToHex(tempTarget), self.intToHex(tempOperation))
            # sendCmd('00','01')
            # time.sleep(0.05)
            # if tempTarget
            # print('target => ' + str(tempAction['target']) + '      operation => ' + str(tempAction['operation']))
            time.sleep(0.05)
        sendCmdReset()

#
#	初始化
#
def killPortProcess(port):
    print('！！！　　杀死对应端口的进程未完成！')


def checkPortUsed(port):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(('127.0.0.1', port))
        s.shutdown(2)
        return True
    except Exception as e:
        return False


def init():
    if not UdpSocketHolder.instance().isLoad:
        UdpSocketHolder.instance().isLoad = True
        # 　端口占用检查
        if checkPortUsed(CONST_PORT_RECV):
            print('检测到本机局域网接受端口 ( ' + str(CONST_PORT_RECV) + ' ) 已被占用')
            killPortProcess(CONST_PORT_RECV)
            print('杀死对应端口进程 ( ' + str(CONST_PORT_RECV) + ' )')
        else:
            print('端口空闲')
        # 启动局域网监听线程
        UdpSocketHolder.instance().udpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        UdpSocketHolder.instance().udpSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        try:
            UdpSocketHolder.instance().udpSocket.bind((CONST_IP_ADDR, CONST_PORT_RECV))
            if not UdpSocketHolder.instance().udpListenThread == None:
                UdpSocketHolder.instance().udpListenThread.isRunning = False
                time.sleep(0.05)
            UdpSocketHolder.instance().udpListenThread = SocketListenThread()
            UdpSocketHolder.instance().udpListenThread.start()
        except Exception as e:
            print('初始化监听线程失败，可能已经运行')
        print('初始化')


def sendData(data):
    UdpSocketHolder.instance().udpSocket.sendto(bytes.fromhex(data), ('255.255.255.255', 7001))
    # UdpSocketHolder.instance().udpSocket.sendto(bytes([00,170,238,00,00,1,239,171,1]), ('255.255.255.255', 7001))

def sendCmdReset():
    sendCmd('14','00')

def sendCmd(target, value):
    sendData('00 AA EE ' + target + ' 00 ' + value + ' EF AB 01')
    print('发送了数据 => '+'00 AA EE ' + target + ' 00 ' + value + ' EF AB 01')
