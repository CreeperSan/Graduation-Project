import threading
import json
import time
import datetime
import config.config as config

isRunning = False
schedule_list = []
# today_active_schedule = set() # 定时执行记录
# prev_day = 0

class ScheduleThread(threading.Thread):

    def run(self):
        global isRunning
        global schedule_list

        while isRunning:
            refresh_schedule_list()
            flag_is_need_reset = False
            for tempSchedule in schedule_list: # 单个循环
                # print('循环到定时')
                # print(tempSchedule)
                if tempSchedule['is_active'] != 'true': # 如果没开，就下一个
                    continue
                timestampNow = config.get_time_stamp()
                timeNow = datetime.datetime.fromtimestamp(timestampNow / 1000)
                if str(timeNow.hour)==tempSchedule['hour'] and str(timeNow.minute)==tempSchedule['minute']:
                    # print('时间到!!!!!!')
                    if tempSchedule['repeat_type'] == '0':  # 不重复
                        tempSchedule['is_active'] = 'false'
                        tempSchedule['prev_time'] = str(config.get_time_stamp())
                        old_name = tempSchedule['name']
                        config.edit_schedule_inner(tempSchedule,old_name)
                        operation(tempSchedule)
                        flag_is_need_reset = True
                    elif tempSchedule['repeat_type'] == '1':  # 按日期重复
                        startTimeStamp = int(tempSchedule['start_time'])
                        startDate = datetime.datetime.fromtimestamp(startTimeStamp/1000)
                        tempRepeatDay = int(tempSchedule['repeat_value'])
                        if tempRepeatDay <= 1:
                            tempRepeatDay = 1
                        deltaDay = (timeNow-startDate).days
                        if(deltaDay % tempRepeatDay == 0):
                            prevTime = 0
                            try:
                                prevTime = int(tempSchedule['prev_time'])
                            except:
                                prevTime = 0
                            prevDate = datetime.datetime.fromtimestamp(prevTime/1000)
                            # print('PrevTime',prevDate)
                            # print('NowTime',timeNow)
                            if str(prevDate.hour)!=str(timeNow.hour) or str(prevDate.minute)!=str(timeNow.minute):
                                tempSchedule['prev_time'] = str(config.get_time_stamp())
                                old_name = tempSchedule['name']
                                config.edit_schedule_inner(tempSchedule, old_name)
                                operation(tempSchedule)
                                flag_is_need_reset = True
                    elif tempSchedule['repeat_type'] == '2':  # 按星期重复
                        tempRepeatValue = tempSchedule['repeat_value'][1:7]+tempSchedule['repeat_value'][0]
                        if tempRepeatValue[timeNow.weekday()] != '0':
                            prevTime = 0
                            try:
                                prevTime = int(tempSchedule['prev_time'])
                            except:
                                prevTime = 0
                            prevDate = datetime.datetime.fromtimestamp(prevTime/1000)
                            # print('PrevTime',prevDate)
                            # print('NowTime',timeNow)
                            if str(prevDate.hour)!=str(timeNow.hour) or str(prevDate.minute)!=str(timeNow.minute):
                                tempSchedule['prev_time'] = str(config.get_time_stamp())
                                old_name = tempSchedule['name']
                                config.edit_schedule_inner(tempSchedule, old_name)
                                operation(tempSchedule)
                                flag_is_need_reset = True
                            # print(tempRepeatValue[timeNow.weekday()])
            if flag_is_need_reset :
                time.sleep(0.3)
                conn.sendCmdReset()
                time.sleep(0.7)
            else :
                time.sleep(1)





def init():
    global isRunning
    refresh_schedule_list()
    tempThread = ScheduleThread()
    isRunning = True
    tempThread.start()

def stop():
    global isRunning
    isRunning = False

def refresh_schedule_list():
    global schedule_list
    # global today_active_schedule
    schedule_list = config.get_schedule()['data']
    # today_active_schedule.clear()

from conn import conn
# 此处执行操作
def operation(schedule):
    tempTarget = int(schedule['target'])
    tempOperation = int(schedule['value'])
    print('命令',tempTarget,'值',tempOperation)
    if tempTarget == 0:  # 温度自动控制
        tempperatureConfig = config.get_temperature_config()
        tempperatureConfig.isAutoControl = int(tempOperation)
        config.set_temperature_config_obj(tempperatureConfig)
    elif tempTarget == 1:  # 空气适度自动控制
        humidityConfig = config.get_humidity_config()
        humidityConfig.isAutoControl = int(tempOperation)
        config.set_dumidity_config_obj(humidityConfig)
    elif tempTarget == 2:  # 土壤适度自动控制
        dirtHumidity = config.get_dirt_humidity_config()
        dirtHumidity.isAutoControl = int(tempOperation)
        config.set_dirt_humidity_config_obj(dirtHumidity)
    elif tempTarget == 3:  # 自动施肥
        fertilizationConfig = config.get_fertilization_config()
        config.set_fertilization_config(tempOperation, fertilizationConfig.repeatType, fertilizationConfig.repeatCircle,
                                        fertilizationConfig.hour, fertilizationConfig.minute)
    elif tempTarget == 4:  # 自动浇水
        waterConfig = config.get_water_config()
        config.set_water_config(tempOperation, waterConfig.repeatType, waterConfig.repeatCircle,
                                waterConfig.hour, waterConfig.minute)
    elif tempTarget == 5:  # 施肥
        conn.sendCmd('06', intToHex(tempOperation))
    elif tempTarget == 6:  # 浇水
        conn.sendCmd('07', intToHex(tempOperation))
    elif tempTarget == 7:  # 风扇
        conn.sendCmd('04', intToHex(tempOperation))
    elif tempTarget == 8:  # 电热膜
        conn.sendCmd('05', intToHex(tempOperation))
    elif tempTarget == 9:  # 自定义设备１
        conn.sendCmd('00', intToHex(tempOperation))
    elif tempTarget == 10:  # 自定义设备2
        conn.sendCmd('01', intToHex(tempOperation))
    elif tempTarget == 11:  # 自定义设备3
        conn.sendCmd('02', intToHex(tempOperation))
    elif tempTarget == 12:  # 自定义设备4
        conn.sendCmd('03', intToHex(tempOperation))
    elif tempTarget == 13:  # 环境光控制
        conn.sendCmd('08', intToHex(tempOperation))
    elif tempTarget == 14:  # 环境光颜色
        conn.sendCmd('09', intToHex(tempOperation))
    elif tempTarget == 15:  # 环境光亮度
        conn.sendCmd('0a', intToHex(tempOperation))
    print('真的执行定时操作 ')

def intToHex(num):
    return ('0' + str(hex(num)[2:]))[-2:]
