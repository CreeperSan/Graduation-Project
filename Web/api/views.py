import json
import math
import time
from django.shortcuts import render
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.views.decorators.csrf import requires_csrf_token
from django.views.decorators.csrf import ensure_csrf_cookie
import authorization.authorization as token
from django.contrib import auth
from authorization import authorization
import user.models as database
import config.config as config
import state.state as state
from conn import conn
from authorization import authorization

# Create your views here.

HTTP_RESULT_SUCCESS = 1
HTTP_RESULT_FAIL = -100
HTTP_RESULT_PERMISSION_DENIED = 0
HTTP_RESULT_NO_SUCH_API = -1
HTTP_RESULT_PARAMS_ERROR = -2
HTTP_RESULT_LOGIN_REQUIRE = -3
HTTP_RESULT_UNKNOWN_ERROR = -4


JSON_PERMISSION_DENIED = '{"result":0}'
JSON_OPPERATION_SUCCESS = '{"result":1}'
JSON_OPPERATION_FAIL = '{"result":-100}'
JSON_NO_SUCH_API = '{"result":-1}'
JSON_PARAMS_INCORRENCT = '{"result":-2}'
JSON_LOGIN_REQUIRE = '{"result":-3}'
JSON_UNKNOWN_ERROR = '{"result":-4}'
JSON_REQUIRE_POST = '{"request":-5}'

DICT_RESULT_CODE = {
    HTTP_RESULT_PARAMS_ERROR: JSON_PERMISSION_DENIED,
    HTTP_RESULT_NO_SUCH_API: JSON_NO_SUCH_API,
    HTTP_RESULT_PARAMS_ERROR: JSON_PARAMS_INCORRENCT,
    HTTP_RESULT_LOGIN_REQUIRE: JSON_LOGIN_REQUIRE,
    HTTP_RESULT_UNKNOWN_ERROR: JSON_UNKNOWN_ERROR,
}

KEY_RESULT = 'result'
KEY_TYPE = 'type'
KEY_OPERATION_RESULT = 'operation_result'
TYPE_DEVICE = 1
TYPE_LIGHT = 2
TYPE_TEMPERATURE = 3
TYPE_HUMIDITY = 4
TYPE_DIRT_HUMIDITY = 5
TYPE_FERTILIZATION = 6
TYPE_WATER = 7
TYPE_USER = 8


# 处理函数

def __checkUser(request):
    # if request.user.is_authenticated:
    #     return HTTP_RESULT_SUCCESS
    # return HTTP_RESULT_LOGIN_REQUIRE
    return HTTP_RESULT_SUCCESS

def __intToHex( num):
    return ('0' + str(hex(num)[2:]))[-2:]

@csrf_exempt
def device(request):
    request_result = __checkUser(request)
    if request_result == HTTP_RESULT_SUCCESS:
        custom_device_config = config.get_device_config()
        if request.method == 'POST':  # 如果是POST请求
            print(request.POST)
            if config.KEY_DEVICE_STATE_1 in request.POST: # 设备1
                custom_device_config.device1State = int(request.POST.get(config.KEY_DEVICE_STATE_1, config.STATE_OFF))
                print('自定义设备1被设置为 ', custom_device_config.device1State)
                conn.sendCmd('00','0'+str(custom_device_config.device1State))
                state.device_1 = custom_device_config.device1State
            if config.KEY_DEVICE_STATE_2 in request.POST: # 设备2
                custom_device_config.device2State = int(request.POST.get(config.KEY_DEVICE_STATE_2, config.STATE_OFF))
                print('自定义设备2被设置为 ', custom_device_config.device2State)
                conn.sendCmd('01','0'+str(custom_device_config.device2State))
                state.device_2 = custom_device_config.device2State
            if config.KEY_DEVICE_STATE_3 in request.POST: # 设备3
                custom_device_config.device3State = int(request.POST.get(config.KEY_DEVICE_STATE_3, config.STATE_OFF))
                print('自定义设备3被设置为 ', custom_device_config.device3State)
                conn.sendCmd('02','0'+str(custom_device_config.device3State))
                state.device_3 = custom_device_config.device3State
            if config.KEY_DEVICE_STATE_4 in request.POST: # 设备4
                custom_device_config.device4State = int(request.POST.get(config.KEY_DEVICE_STATE_4, config.STATE_OFF))
                print('自定义设备4被设置为 ', custom_device_config.device4State)
                conn.sendCmd('03','0'+str(custom_device_config.device4State))
                state.device_4 = custom_device_config.device4State
            config.set_device_config_obj(custom_device_config)
            time.sleep(0.3)
            conn.sendCmdReset()
        json_obj = {
            KEY_RESULT: HTTP_RESULT_SUCCESS,
            config.KEY_DEVICE_STATE_1: int(custom_device_config.device1State),
            config.KEY_DEVICE_STATE_2: int(custom_device_config.device2State),
            config.KEY_DEVICE_STATE_3: int(custom_device_config.device3State),
            config.KEY_DEVICE_STATE_4: int(custom_device_config.device4State),
        }
        return HttpResponse(json.dumps(json_obj))
    else:
        return HttpResponse(DICT_RESULT_CODE.get(request_result, JSON_UNKNOWN_ERROR))


@csrf_exempt
def light(request):
    request_result = __checkUser(request)
    if request_result == HTTP_RESULT_SUCCESS:
        light_config = config.get_light_config()
        if request.method == 'POST':
            if config.KEY_IS_LIGHT_ON in request.POST:
                light_config.isLightOn = request.POST.get(config.KEY_IS_LIGHT_ON, config.STATE_OFF)
                print('环境光设置为', light_config.isLightOn)
                conn.sendCmd('08','0'+str(light_config.isLightOn))
                state.light = light_config.isLightOn
                time.sleep(0.01)
            if config.KEY_LIGHT_COLOR in request.POST:
                light_config.lightColor = request.POST.get(config.KEY_LIGHT_COLOR, config.STATE_OFF)
                print('环境光颜色设置为', light_config.lightColor)
                conn.sendCmd('09','0'+str(light_config.lightColor))
                state.light_color = light_config.lightColor
                time.sleep(0.01)
            if config.KEY_LIGHT_LEVEL in request.POST:
                light_config.lightLevel = request.POST.get(config.KEY_LIGHT_LEVEL, config.STATE_OFF)
                print('环境光亮度设置为', light_config.lightLevel)
                tempData = light_config.lightLevel
                if(int(tempData) > 9):
                    tempData = 'a'
                conn.sendCmd('0a','0'+str(tempData))
                state.light_level = light_config.lightLevel
                time.sleep(0.01)
            config.set_light_config_obj(light_config)
            time.sleep(0.3)
            conn.sendCmdReset()
        json_obj = {
            KEY_RESULT: HTTP_RESULT_SUCCESS,
            config.KEY_IS_LIGHT_ON: light_config.isLightOn,
            config.KEY_LIGHT_COLOR: light_config.lightColor,
            config.KEY_LIGHT_LEVEL: light_config.lightLevel,
        }
        return HttpResponse(json.dumps(json_obj))
    else:
        return HttpResponse(DICT_RESULT_CODE.get(request_result, JSON_UNKNOWN_ERROR))


@csrf_exempt
def temperature(request):
    request_result = __checkUser(request)
    request_result = HTTP_RESULT_SUCCESS
    if request_result == HTTP_RESULT_SUCCESS:
        temperature_config = config.get_temperature_config()
        if request.method == 'POST':
            if config.KEY_IS_AUTO_CONTROL in request.POST:
                temperature_config.isAutoControl = request.POST.get(config.KEY_IS_AUTO_CONTROL, config.STATE_OFF)
                print('自动温度控制被设置为 ' + temperature_config.isAutoControl)
            if config.KEY_UPPER_LIMIT in request.POST:
                temperature_config.upperLimit = request.POST.get(config.KEY_UPPER_LIMIT, 30)
                state.temperature_upper = temperature_config.upperLimit
                conn.sendCmd('0b',__intToHex(int(temperature_config.upperLimit)))
                print('自动温度控制温度上限被设置为 ' + temperature_config.upperLimit)
            if config.KEY_LOWER_LIMIT in request.POST:
                temperature_config.lowerLimit = request.POST.get(config.KEY_LOWER_LIMIT, 0)
                state.temperature_lower = temperature_config.lowerLimit
                conn.sendCmd('0c',__intToHex(int(temperature_config.lowerLimit)))
                print('自动温度控制温度下限被设置为 ' + temperature_config.lowerLimit)
            if config.KEY_UPPER_ACTION in request.POST:
                temperature_config.upperActions = request.POST.get(config.KEY_UPPER_ACTION, config.EMPTY_ACTION)
                print('自动温度控制温度上限执行动作被设置为 ' + temperature_config.upperActions)
            if config.KEY_LOWER_ACTION in request.POST:
                temperature_config.lowerActions = request.POST.get(config.KEY_LOWER_ACTION, config.EMPTY_ACTION)
                print('自动温度控制温度下限执行动作被设置为 ' + temperature_config.lowerActions)
            time.sleep(0.3)
            conn.sendCmdReset()
            config.set_temperature_config_obj(temperature_config)
        json_obj = {
            KEY_RESULT: HTTP_RESULT_SUCCESS,
            KEY_TYPE: TYPE_TEMPERATURE,
            config.KEY_IS_AUTO_CONTROL: temperature_config.isAutoControl,
            config.KEY_UPPER_LIMIT: temperature_config.upperLimit,
            config.KEY_LOWER_LIMIT: temperature_config.lowerLimit,
            config.KEY_UPPER_ACTION: temperature_config.upperActions,
            config.KEY_LOWER_ACTION: temperature_config.lowerActions,
        }
        return HttpResponse(json.dumps(json_obj))
    else:
        return HttpResponse(DICT_RESULT_CODE.get(request_result, JSON_UNKNOWN_ERROR))


@csrf_exempt
def humidity(request):
    request_result = __checkUser(request)
    request_result = HTTP_RESULT_SUCCESS
    if request_result == HTTP_RESULT_SUCCESS:
        humidity_config = config.get_humidity_config()
        if request.method == 'POST':
            if config.KEY_IS_AUTO_CONTROL in request.POST:
                humidity_config.isAutoControl = request.POST.get(config.KEY_IS_AUTO_CONTROL, config.STATE_OFF)
                print('自动湿度控制被设置为 ' + humidity_config.isAutoControl)
            if config.KEY_UPPER_LIMIT in request.POST:
                humidity_config.upperLimit = request.POST.get(config.KEY_UPPER_LIMIT,config.DEFAULT_HUMIDITY_UPPER_LIMIT)
                state.humidity_air_upper = humidity_config.upperLimit
                conn.sendCmd('0d',__intToHex(int(humidity_config.upperLimit)))
                print('自动湿度控制湿度上限被设置为 ' + humidity_config.upperLimit)
            if config.KEY_LOWER_LIMIT in request.POST:
                humidity_config.lowerLimit = request.POST.get(config.KEY_LOWER_LIMIT,config.DEFAULT_HUMIDITY_LOWER_LIMIT)
                state.humidity_air_lower = humidity_config.lowerLimit
                conn.sendCmd('0e',__intToHex(int(humidity_config.lowerLimit)))
                print('自动湿度控制湿度下限被设置为 ' + humidity_config.lowerLimit)
            if config.KEY_UPPER_ACTION in request.POST:
                humidity_config.upperActions = request.POST.get(config.KEY_UPPER_ACTION, config.DEFAULT_ACTIONS)
                print('自动湿度动作上限被设置为 ', humidity_config.upperActions)
            if config.KEY_LOWER_ACTION in request.POST:
                humidity_config.lowerActions = request.POST.get(config.KEY_LOWER_ACTION, config.DEFAULT_ACTIONS)
                print('自动湿度动作下限被设置为 ', humidity_config.upperActions)
            config.set_dumidity_config_obj(humidity_config)
            time.sleep(0.3)
            conn.sendCmdReset()
        json_obj = {
            KEY_RESULT: HTTP_RESULT_SUCCESS,
            KEY_TYPE: TYPE_HUMIDITY,
            config.KEY_IS_AUTO_CONTROL: humidity_config.isAutoControl,
            config.KEY_UPPER_LIMIT: humidity_config.upperLimit,
            config.KEY_LOWER_LIMIT: humidity_config.lowerLimit,
            config.KEY_UPPER_ACTION: humidity_config.upperActions,
            config.KEY_LOWER_ACTION: humidity_config.lowerActions,
        }
        return HttpResponse(json.dumps(json_obj))
    else:
        return HttpResponse(DICT_RESULT_CODE.get(request_result, JSON_UNKNOWN_ERROR))


@csrf_exempt
def dirt_humidity(request):
    request_result = __checkUser(request)
    request_result = HTTP_RESULT_SUCCESS
    if request_result == HTTP_RESULT_SUCCESS:
        dirt_humidity_config = config.get_dirt_humidity_config()
        if request.method == 'POST':
            if config.KEY_IS_AUTO_CONTROL in request.POST:
                dirt_humidity_config.isAutoControl = request.POST.get(config.KEY_IS_AUTO_CONTROL, config.STATE_OFF)
                print('自动土壤湿度控制被设置为 ' + dirt_humidity_config.isAutoControl)
            if config.KEY_UPPER_LIMIT in request.POST:
                dirt_humidity_config.upperLimit = request.POST.get(config.KEY_UPPER_LIMIT,config.DEFAULT_HUMIDITY_UPPER_LIMIT)
                state.humidity_dirt_upper = dirt_humidity_config.upperLimit
                print('自动土壤湿度控制温度上限被设置为 ' + dirt_humidity_config.upperLimit)
                conn.sendCmd('12',__intToHex(int(dirt_humidity_config.upperLimit)))
            if config.KEY_LOWER_LIMIT in request.POST:
                dirt_humidity_config.lowerLimit = request.POST.get(config.KEY_LOWER_LIMIT,config.DEFAULT_HUMIDITY_LOWER_LIMIT)
                state.humidity_dirt_lower = dirt_humidity_config.lowerLimit
                print('自动土壤湿度控制湿度下限被设置为 ' + dirt_humidity_config.lowerLimit)
                conn.sendCmd('13',__intToHex(int(dirt_humidity_config.lowerLimit)))
            if config.KEY_UPPER_ACTION in request.POST:
                dirt_humidity_config.upperActions = request.POST.get(config.KEY_UPPER_ACTION, config.DEFAULT_ACTIONS)
                print('自动土壤湿度动作上限被设置为 ', dirt_humidity_config.upperActions)
            if config.KEY_LOWER_ACTION in request.POST:
                dirt_humidity_config.lowerActions = request.POST.get(config.KEY_LOWER_ACTION, config.DEFAULT_ACTIONS)
                print('自动土壤湿度动作下限被设置为 ', dirt_humidity_config.upperActions)
            config.set_dirt_humidity_config_obj(dirt_humidity_config)
            time.sleep(0.3)
            conn.sendCmdReset()
        json_obj = {
            KEY_RESULT: HTTP_RESULT_SUCCESS,
            KEY_TYPE: TYPE_DIRT_HUMIDITY,
            config.KEY_IS_AUTO_CONTROL: dirt_humidity_config.isAutoControl,
            config.KEY_UPPER_LIMIT: dirt_humidity_config.upperLimit,
            config.KEY_LOWER_LIMIT: dirt_humidity_config.lowerLimit,
            config.KEY_UPPER_ACTION: dirt_humidity_config.upperActions,
            config.KEY_LOWER_ACTION: dirt_humidity_config.lowerActions,
        }
        return HttpResponse(json.dumps(json_obj))
    else:
        return HttpResponse(DICT_RESULT_CODE.get(request_result, JSON_UNKNOWN_ERROR))


@csrf_exempt
def fertilization(request):
    request_result = __checkUser(request)
    if request_result == HTTP_RESULT_SUCCESS:
        fertilization_config = config.get_fertilization_config()
        if request.method == 'POST':
            if config.KEY_IS_AUTO_CONTROL in request.POST:
                fertilization_config.isAutoControl = request.POST.get(config.KEY_IS_AUTO_CONTROL,
                                                                      config.DEFAULT_AUTO_CONTROL)
                print('自动施肥被设置为', fertilization_config.isAutoControl)
            if config.KEY_REPEAT_TYPE in request.POST:
                fertilization_config.repeatType = request.POST.get(config.KEY_REPEAT_TYPE, config.DEFAULT_REPEAT_TYPE)
                print('自动施肥重复类型被设置为', fertilization_config.repeatType)
            if config.KEY_REPEAT_CIRCLE in request.POST:
                fertilization_config.repeatCircle = request.POST.get(config.KEY_REPEAT_CIRCLE,
                                                                     config.DEFAULT_REPEAT_CIRCLE)
                print('自动施肥周期被设置为', fertilization_config.repeatCircle)
            if config.KEY_HOUR in request.POST:
                fertilization_config.hour = request.POST.get(config.KEY_HOUR, config.DEFAULT_REPEAT_HOUR)
                print('自动施肥周期小时被设置为', fertilization_config.hour)
            if config.KEY_MINUTE in request.POST:
                fertilization_config.minute = request.POST.get(config.KEY_MINUTE, config.DEFAULT_REPEAT_MINUTE)
                print('自动施肥周期分钟被设置为', fertilization_config.minute)
            config.set_fertilization_config_obj(fertilization_config)
        json_obj = {
            KEY_RESULT: HTTP_RESULT_SUCCESS,
            KEY_TYPE: TYPE_FERTILIZATION,
            config.KEY_IS_AUTO_CONTROL: fertilization_config.isAutoControl,
            config.KEY_REPEAT_TYPE: fertilization_config.repeatType,
            config.KEY_REPEAT_CIRCLE: fertilization_config.repeatCircle,
            config.KEY_HOUR: fertilization_config.hour,
            config.KEY_MINUTE: fertilization_config.minute
        }
        return HttpResponse(json.dumps(json_obj))
    else:
        return HttpResponse(DICT_RESULT_CODE.get(request_result, JSON_UNKNOWN_ERROR))


@csrf_exempt
def water(request):
    request_result = __checkUser(request)
    if request_result == HTTP_RESULT_SUCCESS:
        water_config = config.get_water_config()
        if request.method == 'POST':
            if config.KEY_IS_AUTO_CONTROL in request.POST:
                water_config.isAutoControl = request.POST.get(config.KEY_IS_AUTO_CONTROL, config.DEFAULT_AUTO_CONTROL)
                print('自动浇水被设置为', water_config.isAutoControl)
            if config.KEY_REPEAT_TYPE in request.POST:
                water_config.repeatType = request.POST.get(config.KEY_REPEAT_TYPE, config.DEFAULT_REPEAT_TYPE)
                print('自动浇水重复类型被设置为', water_config.repeatType)
            if config.KEY_REPEAT_CIRCLE in request.POST:
                water_config.repeatCircle = request.POST.get(config.KEY_REPEAT_CIRCLE, config.DEFAULT_REPEAT_CIRCLE)
                print('自动浇水周期被设置为', water_config.repeatCircle)
            if config.KEY_HOUR in request.POST:
                water_config.hour = request.POST.get(config.KEY_HOUR, config.DEFAULT_REPEAT_HOUR)
                print('自动浇水周期小时被设置为', water_config.hour)
            if config.KEY_MINUTE in request.POST:
                water_config.minute = request.POST.get(config.KEY_MINUTE, config.DEFAULT_REPEAT_MINUTE)
                print('自动浇水周期分钟被设置为', water_config.minute)
            config.set_water_config_obj(water_config)
        json_obj = {
            KEY_RESULT: HTTP_RESULT_SUCCESS,
            KEY_TYPE: TYPE_WATER,
            config.KEY_IS_AUTO_CONTROL: water_config.isAutoControl,
            config.KEY_REPEAT_TYPE: water_config.repeatType,
            config.KEY_REPEAT_CIRCLE: water_config.repeatCircle,
            config.KEY_HOUR: water_config.hour,
            config.KEY_MINUTE: water_config.minute
        }
        return HttpResponse(json.dumps(json_obj))
    else:
        return HttpResponse(DICT_RESULT_CODE.get(request_result, JSON_UNKNOWN_ERROR))


TYPE_USER_NO = -1
TYPE_USER_CREATE = 0
TYPE_USER_EDIT = 1
TYPE_USER_DELETE = 2
ACTION_TYPE_NONE = -1
ACTION_TYPE_USER_CREATE = 0
ACTION_TYPE_USER_EDIT = 1
ACTION_TYPE_USER_DEL = 2
VALUE_OPERATION_RESULT_FAIL = 'fail'
VALUE_OPERATION_RESULT_SUCCESS = 'success'
VALUE_OPERATION_RESULT_USER_EXIST = 'user_exist'
VALUE_OPERATION_RESULT_USER_NOT_EXIST = 'user_not_exist'
VALUE_BOOL_TRUE = 1
VALUE_BOOL_FALSE = 0
JSON_NO_SUCH_USER = '{"result":-5}'
JSON_USER_EXIST = '{"result":-6}'


@csrf_exempt
def user(request):
    request_result = __checkUser(request)
    request_result = HTTP_RESULT_SUCCESS # 要删掉
    if request_result == HTTP_RESULT_SUCCESS:  # 如果请求成功
        if request.method == 'GET':  # 如果是Get获取数据
            print('Get请求')
            if {config.KEY_PAGE_NUM, config.KEY_PAGE_COUNT}.intersection(request.GET):  # 制定页码
                print('请求参数符合条件')
                user_list = database.User.objects.all()
                return HttpResponse(user_list) 
        elif request.method == 'POST':
            print('收到的API的关于用户的POST的请求\n'+str(request.POST))
            if {config.KEY_USER_ACTION_TYPE, config.KEY_USERNAME, config.KEY_PASSWORD, config.KEY_IS_STUFF,
                config.KEY_IS_ACTIVE, config.KEY_NICKNAME, config.KEY_INFO}.intersection(request.POST):
                print('用户的参数校验正确')
                user_username = request.POST[config.KEY_USERNAME]
                user_password = request.POST[config.KEY_PASSWORD]
                user_is_stuff = int(request.POST[config.KEY_IS_STUFF]) == VALUE_BOOL_TRUE
                user_is_active = int(request.POST[config.KEY_IS_ACTIVE]) == VALUE_BOOL_TRUE
                user_action_type = int(request.POST[config.KEY_USER_ACTION_TYPE])
                user_info = request.POST[config.KEY_INFO]
                user_nickname = request.POST[config.KEY_NICKNAME]
                if user_nickname == '':
                    user_nickname = user_username
                if user_info == '':
                    user_info = '暂无简介'
                user_operation_result = VALUE_OPERATION_RESULT_FAIL
                if user_action_type == ACTION_TYPE_USER_CREATE:  # 如果是创建用户
                    print('创建用户 是否工作人员 '+str(user_is_stuff)+' 是否活动 '+str(user_is_active))
                    if database.User.objects.filter(username=user_username):  # 如果用户名已被注册
                        user_operation_result = VALUE_OPERATION_RESULT_USER_EXIST
                        print("同户名 %s 已被注册"%user_username)
                    else:  # 如果用户名可用
                        temp_user = database.User()
                        temp_user.username = user_username
                        temp_user.nickname = user_nickname
                        temp_user.set_password(user_password)
                        temp_user.is_staff = user_is_stuff
                        temp_user.is_active = user_is_active
                        temp_user.info = user_info
                        temp_user.save()
                        print("同户名 %s 创建成功"%user_username)
                elif user_action_type == ACTION_TYPE_USER_EDIT:  # 如果是编辑用户,不会改变密码
                    print('编辑用户')
                    if database.User.objects.filter(username=user_username):  # 如果用户的确存在
                        temp_user = database.User.objects.get(username=user_username)
                        temp_user.username = user_username
                        temp_user.nickname = user_nickname
                        temp_user.is_staff = user_is_stuff
                        temp_user.is_active = user_is_active
                        temp_user.info = user_info
                        temp_user.save()
                        print("同户 %s 编辑成功"%user_username)
                    else:  # 如果用户不存在
                        user_operation_result = VALUE_OPERATION_RESULT_USER_EXIST
                        print("同户 %s 不存在，不能编辑"%user_username)
                elif user_action_type == ACTION_TYPE_USER_DEL:  # 如果是删除账户
                    print('删除用户')
                    if database.User.objects.filter(username=user_username):  # 如果用户的确存在
                        temp_user = database.User.objects.get(username=user_username)
                        print("同户 %s 删除成功"%user_username)
                        temp_user.delete()
                    else:  # 如果用户不存在
                        user_operation_result = VALUE_OPERATION_RESULT_USER_EXIST
                        print("同户 %s 不存在，不能删除"%user_username)
                else:
                    print('传递的用户操作类型不正确')
                    user_action_type = ACTION_TYPE_NONE
                json_obj = {
                    KEY_RESULT: HTTP_RESULT_SUCCESS,
                    KEY_TYPE: TYPE_USER,
                    KEY_OPERATION_RESULT: user_operation_result,
                    config.KEY_USERNAME: user_username,
                    config.KEY_NICKNAME: user_nickname,
                    config.KEY_IS_STUFF: user_is_stuff,
                    config.KEY_IS_ACTIVE: user_is_active,
                    config.KEY_INFO: user_info,
                    config.KEY_USER_ACTION_TYPE: user_action_type
                }
                return HttpResponse(json.dumps(json_obj))
        return HttpResponse(JSON_PARAMS_INCORRENCT)
    else:
        return HttpResponse(DICT_RESULT_CODE.get(request_result, JSON_UNKNOWN_ERROR))


KEY_SCHEDULE_ACTION = 'action'
VAL_SCHEDULE_ACTION_ADD = '1'
VAL_SCHEDULE_ACTION_EDIT = '2'
VAL_SCHEDULE_ACTION_DEL = '3'
KEY_SCHEDULE_NAME = 'name'
KEY_SCHEDULE_IS_ACTIVE = 'is_active'
KEY_SCHEDULE_REPEAT_TYPE = 'repeat_type'
KEY_SCHEDULE_REPEAT_VALUE = 'repeat_value'
KEY_SCHEDULE_HOUR = 'hour'
KEY_SCHEDULE_MINUTE = 'minute'
KEY_SHCEDULE_TARGET = 'target'
KEY_SCHEDULE_VALUE = 'value'
KEY_SCHEDULE_OLD_NAME = 'old_name'

JSON_PARAMS_NOT_DEFINE = '{"result":-7}'    # 结果 参数没定义

# 操作类型 


@csrf_exempt
def schedule(request):
    request_result = __checkUser(request)
    if request.method == 'GET':
        return HttpResponse('应该返回所有的定时，现在还没有完成')
    elif request.method == 'POST':
        if request_result == HTTP_RESULT_SUCCESS:
            if {KEY_SCHEDULE_ACTION,KEY_SCHEDULE_NAME,KEY_SCHEDULE_REPEAT_TYPE,KEY_SCHEDULE_REPEAT_VALUE,KEY_SCHEDULE_HOUR,
                KEY_SCHEDULE_MINUTE,KEY_SHCEDULE_TARGET,KEY_SCHEDULE_VALUE,KEY_SCHEDULE_IS_ACTIVE}.intersection(request.POST):
                scheduleObject = config.Schedule()
                scheduleObject.name = request.POST.get(KEY_SCHEDULE_NAME,'undefine')
                scheduleObject.repeat_type = request.POST.get(KEY_SCHEDULE_REPEAT_TYPE,'0')
                scheduleObject.repeat_circle = request.POST.get(KEY_SCHEDULE_REPEAT_VALUE,'0')
                scheduleObject.hour = request.POST.get(KEY_SCHEDULE_HOUR,'0')
                scheduleObject.minute = request.POST.get(KEY_SCHEDULE_MINUTE,'0')
                scheduleObject.target = request.POST.get(KEY_SHCEDULE_TARGET,'0')
                scheduleObject.value = request.POST.get(KEY_SCHEDULE_VALUE,'0')
                scheduleObject.is_active = request.POST.get(KEY_SCHEDULE_IS_ACTIVE,'false')
                scheduleObject.start_time = config.get_time_stamp()
                scheduleOldName = request.POST.get(KEY_SCHEDULE_OLD_NAME,' ')
                if request.POST[KEY_SCHEDULE_ACTION] == VAL_SCHEDULE_ACTION_ADD:
                    config.add_schedule(scheduleObject)
                elif request.POST[KEY_SCHEDULE_ACTION] == VAL_SCHEDULE_ACTION_DEL:
                    config.del_schedule(scheduleObject.name)
                elif request.POST[KEY_SCHEDULE_ACTION] == VAL_SCHEDULE_ACTION_EDIT:
                    config.edit_schedule(scheduleObject,scheduleOldName)
                print('定时请求参数完整')
                return HttpResponse(JSON_OPPERATION_SUCCESS)
            else :
                return HttpResponse(JSON_PARAMS_NOT_DEFINE)
        else :
            return HttpResponse(JSON_LOGIN_REQUIRE)


@csrf_exempt
def noSuchApi(request):
    return HttpResponse(JSON_NO_SUCH_API)


'''
传过来的参数说明
    year : 年
    month : 月
    day : 日
    hour : 时
    minute : 分
    second : 秒
    air_temp : 气温
    air_humidity :　空气湿度
    dirt_temp : 土壤温度
    dirt_humiity :　土壤湿度
    light : 亮度
    count : 将要返回的条目数
    page : 将要返回的页数
'''
from farm.models import Sensor as Sensor
from django.forms.models import model_to_dict
@csrf_exempt
def history(request):
    if request.method == 'GET':
        return HttpResponse(JSON_REQUIRE_POST)
    qYear = request.POST.get('year',None)
    qMonth = request.POST.get('month',None)
    qDay = request.POST.get('day',None)
    qHour = request.POST.get('hour',None)
    qMinute = request.POST.get('minute',None)
    qSecond = request.POST.get('second',None)
    qAirTemp = request.POST.get('air_temp',None)
    qAirHumidity = request.POST.get('air_humidity',None)
    qDirtTemp = request.POST.get('dirt_temp',None)
    qDirtHumidity = request.POST.get('dirt_humiity',None)
    qLight = request.POST.get('light',None)
    qCount = int(request.POST.get('count',8))
    qPage = int(request.POST.get('page',0))

    queryDict = {}
    if qYear != None:
        queryDict['year'] = int(qYear)
    if qMonth != None:
        queryDict['month'] = int(qMonth)
    if qDay != None:
        queryDict['day'] = int(qDay)
    if qHour != None:
        queryDict['hour'] = int(qHour)
    if qMinute != None:
        queryDict['minute'] = int(qMinute)
    if qSecond != None:
        queryDict['second'] = int(qSecond)
    if qAirTemp != None:
        queryDict['air_temperature'] = int(qAirTemp)
    if qAirHumidity != None:
        queryDict['air_humidity'] = int(qAirHumidity)
    if qDirtTemp != None:
        queryDict['dirt_temperature'] = int(qDirtTemp)
    if qDirtHumidity != None:
        queryDict['dirt_humidity'] = int(qDirtHumidity)
    if qLight != None:
        queryDict['light'] = int(qLight)

    # print('queryDict   ,qCount '+str(qCount)+'   qPage '+str(qPage))
    print(queryDict)

    dataAllSet = Sensor.objects.filter(**queryDict)
    dataAllSet = dataAllSet[::-1]
    dataSize = len(dataAllSet)
    dataList = dataAllSet[qPage*qCount:(qPage+1)*qCount] # 这里报错 onordered

    dataDatabase = []
    for tempData in dataList:
        tempData = model_to_dict(tempData)
        # print(tempData)
        tempDataDict =  {
                            'year'          : tempData['year'],
                            'month'         : tempData['month'],
                            'day'           : tempData['day'],
                            'hour'          : tempData['hour'],
                            'minute'        : tempData['minute'],
                            'second'        : tempData['second'],
                            'air_temp'      : tempData['air_temperature'],
                            'air_humidity'  : tempData['air_humidity'],
                            'dirt_temp'     : tempData['dirt_temperature'],
                            'dirt_humiity'  : tempData['dirt_humidity'],
                            'light'         : tempData['light']
                        }
        dataDatabase.append(tempData)


    dataBack = {}
    dataBack['length'] = len(dataAllSet)
    dataBack['data'] = dataDatabase
    dataBack['startPos'] = qPage*qCount
    dataBack['startPage'] = qPage
    dataBack['pageMax'] = math.ceil(dataSize/qCount)

    jsonData = json.dumps(dataBack)
    return HttpResponse(jsonData)

    # if request.user.is_authenticated:
    #     return HttpResponse(JSON_OPPERATION_SUCCESS)
    # else :
    #     return HttpResponse(JSON_LOGIN_REQUIRE)


@csrf_exempt
def logout(request):
    if request.user.is_authenticated:
        auth.logout(request)
        return HttpResponse(JSON_OPPERATION_SUCCESS)
    else :
        return HttpResponse(JSON_OPPERATION_FAIL)



    ############################################################
    #
    #
    #   往下是移动端的请求
    #
    #
    ############################################################

# 主页信息功能
# 如果返回result = 1 代表权限不足
# 如果返回result = 2 代表用户没有登录

lightColorStrDirt = {
    0: '红色',
    1: '绿色',
    2: '蓝色',
    3: '黄色',
    4: '紫色',
    5: '青色',
    6: '白色',
}
@csrf_exempt
def mobile_index(request):
    getUserList = authorization.get_user(request)
    if getUserList[0] == authorization.RESULT_SUCCESS:
        if int(state.temperature_air) > int(state.temperature_upper):
            temperatureAirSubTitle = '空气温度过高，请采取措施'
        elif int(state.temperature_air) < int(state.temperature_lower):
            temperatureAirSubTitle = '空气温度过低，请采取措施'
        else :
            temperatureAirSubTitle = '空气温度正常'
        # 土壤温度显示的文本
        temperatureDirtSubTitle = ' '
        if int(state.temperature_dirt) > int(state.temperature_upper):
            temperatureDirtSubTitle = '土壤温度过高，请采取措施'
        elif int(state.temperature_dirt) < int(state.temperature_lower):
            temperatureDirtSubTitle = '土壤温度过低，请采取措施'
        else :
            temperatureDirtSubTitle = '土壤温度正常'
        # 空气湿度显示的文本
        humidityAirText = ' '
        if int(state.humidity_air) > int(state.humidity_air_upper):
            humidityAirText = '空气湿度过高，请采取措施'
        elif int(state.humidity_air) < int(state.humidity_air_lower):
            humidityAirText = '空气湿度过低，请采取措施'
        else :
            humidityAirText = '空气湿度正常'
        # 土壤湿度显示的文本
        humidityDirtText = ' '
        if int(state.humidity_dirt) > int(state.humidity_dirt_upper):
            humidityDirtText = '土壤湿度过高，请采取措施'
        elif int(state.humidity_dirt) < int(state.humidity_dirt_lower):
            humidityDirtText = '土壤湿度过低，请采取措施'
        else :
            humidityDirtText = '土壤湿度正常'
        # 灯光的显示文本
        lightTitle = ' '
        lightSubTitle = '亮度'+str(state.light_level*10)+'%'
        if state.light == 1:
            if state.light_color == 0:
                lightTitle = '红色'
            elif state.light_color == 1:
                lightTitle = '绿色'
            elif state.light_color == 2:
                lightTitle = '蓝色'
            elif state.light_color == 3:
                lightTitle = '黄色'
            elif state.light_color == 4:
                lightTitle = '紫色'
            elif state.light_color == 5:
                lightTitle = '青色'
            elif state.light_color == 6:
                lightTitle = '白色'
            else:
                lightTitle = '其他颜色'
        else :
            lightTitle = '关闭'
            lightSubTitle = '已关闭'
        # 自定义设备的显示文本
        deviceStateTitle = ' '
        deviceStateSubTitle = ' '
        if state.device_1 == 1 and state.device_2 == 1 and state.device_3 == 1 and state.device_4 == 1:
            deviceStateTitle = 'ON'
            deviceStateSubTitle = '自定义设备均已打开'
        elif state.device_1 != 1 and state.device_2 != 1 and state.device_3 != 1 and state.device_4 != 1:
            deviceStateTitle = 'OFF'
            deviceStateSubTitle = '自定义设备均已关闭'
        else :
            deviceStateTitle = 'ON'
            deviceStateSubTitle = '自定义设备已部分打开'
        return HttpResponse(json.dumps({
            'temperature_air' : state.temperature_air ,
            'temperature_air_text' : temperatureAirSubTitle ,
            'temperature_dirt' : state.temperature_dirt ,
            'temperature_dirt_text' : temperatureDirtSubTitle ,
            'humidity_air' : state.humidity_air ,
            'humidity_air_text' : humidityAirText ,
            'humidity_dirt' : state.humidity_dirt,
            'humidity_dirt_text' : humidityDirtText,
            'light' : lightTitle,
            'light_text' : lightSubTitle,
            'device_title' : deviceStateTitle,
            'device_subtitle' : deviceStateSubTitle,
            'tempUpper':state.temperature_upper,
            'tempLower':state.temperature_lower,
            'humidityAirUpper':state.humidity_air_upper,
            'humidityAirLower':state.humidity_air_lower,
            'humidityDirtUpper':state.humidity_dirt_upper,
            'humidityDirtLower':state.humidity_dirt_lower
            },ensure_ascii=False))
    elif getUserList[0] == authorization.RESULT_TOKEN_NOT_EXIST:
        return HttpResponse(JSON_LOGIN_REQUIRE)
    return HttpResponse(JSON_OPPERATION_FAIL)

# 管理功能
@csrf_exempt
def mobile_manage(request):
    getUserList = authorization.get_user(request)
    if getUserList[0] == authorization.RESULT_SUCCESS:
        if (getUserList[2].is_staff and getUserList[2].is_active) or getUserList[2].is_superuser:
            device_config = config.get_device_config()
            light_config = config.get_light_config()
            return HttpResponse(json.dumps({
                'device1_state': device_config.device1State,
                'device2_state': device_config.device2State,
                'device3_state': device_config.device3State,
                'device4_state': device_config.device4State,
                'light_state': light_config.isLightOn,
                'light_color': light_config.lightColor,
                'light_color_str': config.get_color_str(light_config.lightColor),
                'light_level': light_config.lightLevel
            },ensure_ascii=False))
        else:
            return HttpResponse(JSON_PERMISSION_DENIED)
    elif getUserList[0] == authorization.RESULT_TOKEN_NOT_EXIST:
        return HttpResponse(JSON_LOGIN_REQUIRE)
    else:
        return HttpResponse(JSON_OPPERATION_FAIL)

# 获取定时地信息
def __getScheduleWeekdayStr(weekdayStr):
    if len(weekdayStr) >= 7:
        if weekdayStr == 0:
            weekdatStrBuilder = '还没设定重复的星期'
        else :
            weekdatStrBuilder = '每周'
            if weekdayStr[0] == '1':
                weekdatStrBuilder+='日'
            if weekdayStr[1] == '1':
                weekdatStrBuilder+='一'
            if weekdayStr[2] == '1':
                weekdatStrBuilder+='二'
            if weekdayStr[3] == '1':
                weekdatStrBuilder+='三'
            if weekdayStr[4] == '1':
                weekdatStrBuilder+='四'
            if weekdayStr[5] == '1':
                weekdatStrBuilder+='五'
            if weekdayStr[6] == '1':
                weekdatStrBuilder+='六'
            weekdatStrBuilder+='重复'
        return weekdatStrBuilder
    else :
        return 'undefine'
@csrf_exempt
def mobile_schedule(request):
    getUserList = authorization.get_user(request)
    if getUserList[0] == authorization.RESULT_SUCCESS:
        if (getUserList[2].is_staff and getUserList[2].is_active) or getUserList[2].is_superuser:
            try:
                scheduleList = config.get_schedule()['data']
                for scheduleItem in scheduleList:
                    scheduleItem['repeat_str'] = __getScheduleWeekdayStr(scheduleItem['repeat_value'])
            except Exception as e:
                scheduleList = []
            return HttpResponse(json.dumps({
                'scheduleList': scheduleList,
            },ensure_ascii=False))
        else:
            return HttpResponse(JSON_PERMISSION_DENIED)
    elif getUserList[0] == authorization.RESULT_TOKEN_NOT_EXIST:
        return HttpResponse(JSON_LOGIN_REQUIRE)
    else:
        return HttpResponse(JSON_OPPERATION_FAIL)


# 获取我信息
def getNicknameStr(user):
    if user.nickname == '':
        return user.username
    else :
        return user.nickname
def getUserLevelStr(user):
    if user.is_superuser :
        return '管理员'
    elif user.is_active:
        if user.is_staff :
            return '工作人员'
        else :
            return '访客'
    else :
        return '停用的用户'
def getUserLevelImg(user):
    if user.is_superuser :
        return '/static/common/icon/ic_admin.png'
    elif user.is_active:
        if user.is_staff :
            return '/static/common/icon/ic_stuff.png'
        else :
            return '/static/common/icon/ic_guest.png'
    else :
        return '/static/common/icon/ic_guest.png'
bool_to_chs_str_lambda = lambda temp : '是' if temp else '否'
@csrf_exempt
def mobile_me(request):
    getUserList = authorization.get_user(request)
    if getUserList[0] == authorization.RESULT_SUCCESS:
        temp_user_list = token.get_user(request)
        if temp_user_list[0] != token.RESULT_SUCCESS :
            return HttpResponse('{"result":'+str(temp_user_list[0])+'}')
        temp_user = temp_user_list[2]
        level_img_str = getUserLevelImg(temp_user)
        level_str = getUserLevelStr(temp_user)
        nickname = getNicknameStr(temp_user)
        username = temp_user.username
        is_staff = temp_user.is_staff
        is_available = not temp_user.is_active
        register_time = str(temp_user.date_joined)
        info = temp_user.info
        return HttpResponse(json.dumps({
            'level_img_str': level_img_str,
            'level_str': level_str,
            'nickname': nickname,
            'username': username,
            'is_staff': bool_to_chs_str_lambda(is_staff),
            'is_available': bool_to_chs_str_lambda(is_available),
            'register_time': register_time[0:len(register_time) - 13],
            'info': info,
        },ensure_ascii=False))
    elif getUserList[0] == authorization.RESULT_TOKEN_NOT_EXIST:
        return HttpResponse(JSON_LOGIN_REQUIRE)
    else:
        return HttpResponse(JSON_OPPERATION_FAIL)

@csrf_exempt
def mobile_login(request):
    if request.POST:
        print(request.POST)
        resultCode, tokenStr, tempUser = authorization.get_user(request)
        print('登录结果',resultCode, tokenStr, tempUser)
        if resultCode == authorization.RESULT_SUCCESS :
            tokenObj = {}
            tokenObj['token'] = tokenStr
            tokenObj['result'] = authorization.RESULT_SUCCESS
        else :
            tokenObj = {}
            tokenObj['token'] = '?'
            tokenObj['result'] = resultCode
        return HttpResponse(json.dumps(tokenObj))
    return HttpResponse(JSON_REQUIRE_POST)

@csrf_exempt
def mobile_setting(request):
    getUserList = authorization.get_user(request)
    if getUserList[0] == authorization.RESULT_SUCCESS:
        if (getUserList[2].is_staff and getUserList[2].is_active) or getUserList[2].is_superuser:
            temperature_config = config.get_temperature_config()
            humidity_config = config.get_humidity_config()
            dirt_humidity_config = config.get_dirt_humidity_config()
            fertilization_config = config.get_fertilization_config()
            watering_config = config.get_water_config()
            return HttpResponse(json.dumps({
                'temperature_state': temperature_config.isAutoControl,
                'temperature_upper_limit': temperature_config.upperLimit,
                'temperature_lower_limit': temperature_config.lowerLimit,
                'temperature_upper_actions': temperature_config.upperActions,
                'temperature_lower_actions': temperature_config.lowerActions,
                'himidity_state': humidity_config.isAutoControl,
                'himidity_upper_limit': humidity_config.upperLimit,
                'himidity_lower_limit': humidity_config.lowerLimit,
                'himidity_upper_actions': humidity_config.upperActions,
                'himidity_lower_actions': humidity_config.lowerActions,
                'dirt_himidity_state': dirt_humidity_config.isAutoControl,
                'dirt_himidity_upper_limit': dirt_humidity_config.upperLimit,
                'dirt_himidity_lower_limit': dirt_humidity_config.lowerLimit,
                'dirt_himidity_upper_actions': dirt_humidity_config.upperActions,
                'dirt_himidity_lower_actions': dirt_humidity_config.lowerActions,
                'fertilization_state': fertilization_config.isAutoControl,
                'fertilization_repeat_type': fertilization_config.repeatType,
                'fertilization_hour': fertilization_config.hour,
                'fertilization_minute': fertilization_config.minute,
                'fertilization_repeat_circle': fertilization_config.repeatCircle,
                'fertilization_hint_text': '自动施肥周期',
                'watering_state': watering_config.isAutoControl,
                'watering_repeat_type': watering_config.repeatType,
                'watering_hour': watering_config.hour,
                'watering_minute': watering_config.minute,
                'watering_repeat_circle': watering_config.repeatCircle,
                'watering_hint_text': '自动浇水周期',
            },ensure_ascii=False))
        return HttpResponse(JSON_PERMISSION_DENIED)
    elif getUserList[0] == authorization.RESULT_TOKEN_NOT_EXIST:
        return HttpResponse(JSON_LOGIN_REQUIRE)
    else:
        return HttpResponse(JSON_OPPERATION_FAIL)


# 用户功能
from user.models import User
@csrf_exempt
def mobile_user(request):
    getUserList = authorization.get_user(request)
    if getUserList[0] == authorization.RESULT_SUCCESS:
        if getUserList[2].is_superuser:
            userList = User.objects.all()
            userListJson = []
            for userItem in userList:
                tempUserJson = {}
                tempUserJson['username'] = userItem.username
                tempUserJson['nickname'] = userItem.nickname
                tempUserJson['is_staff'] = userItem.is_staff
                tempUserJson['is_active'] = userItem.is_active
                tempUserJson['is_admin'] = userItem.is_superuser
                tempUserJson['info'] = userItem.info
                userListJson.append(tempUserJson)
            return HttpResponse(json.dumps(userListJson,ensure_ascii=False))
        return HttpResponse(JSON_PERMISSION_DENIED)
    elif getUserList[0] == authorization.RESULT_TOKEN_NOT_EXIST:
        return HttpResponse(JSON_LOGIN_REQUIRE)
    else:
        return HttpResponse(JSON_OPPERATION_FAIL)




