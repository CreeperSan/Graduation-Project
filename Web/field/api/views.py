import json
from django.shortcuts import render
from django.http import HttpResponse
import config.config as config
import user.models as database
from django.views.decorators.csrf import csrf_exempt
from django.views.decorators.csrf import requires_csrf_token
from django.views.decorators.csrf import ensure_csrf_cookie

# Create your views here.

HTTP_RESULT_SUCCESS = 1
HTTP_RESULT_PERMISSION_DENIED = 0
HTTP_RESULT_NO_SUCH_API = -1
HTTP_RESULT_PARAMS_ERROR = -2
HTTP_RESULT_LOGIN_REQUIRE = -3
HTTP_RESULT_UNKNOWN_ERROR = -4

JSON_PERMISSION_DENIED = '{"result":0}'
JSON_NO_SUCH_API = '{"result":-1}'
JSON_PARAMS_INCORRENCT = '{"result":-2}'
JSON_LOGIN_REQUIRE = '{"result":-3}'
JSON_UNKNOWN_ERROR = '{"result":-4}'

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
    if request.user.is_authenticated:
        return HTTP_RESULT_SUCCESS
    return HTTP_RESULT_LOGIN_REQUIRE


@csrf_exempt
def device(request):
    request_result = __checkUser(request)
    if request_result == HTTP_RESULT_SUCCESS:
        custom_device_config = config.get_device_config()
        if request.method == 'POST':  # 如果是POST请求
            if config.KEY_DEVICE_STATE_1 in request.POST:
                custom_device_config.device1State = int(request.POST.get(config.KEY_DEVICE_STATE_1, config.STATE_OFF))
                print('自定义设备1被设置为 ', custom_device_config.device1State)
            if config.KEY_DEVICE_STATE_2 in request.POST:
                custom_device_config.device2State = int(request.POST.get(config.KEY_DEVICE_STATE_2, config.STATE_OFF))
                print('自定义设备2被设置为 ', custom_device_config.device2State)
            if config.KEY_DEVICE_STATE_3 in request.POST:
                custom_device_config.device3State = int(request.POST.get(config.KEY_DEVICE_STATE_3, config.STATE_OFF))
                print('自定义设备3被设置为 ', custom_device_config.device3State)
            if config.KEY_DEVICE_STATE_4 in request.POST:
                custom_device_config.device4State = int(request.POST.get(config.KEY_DEVICE_STATE_4, config.STATE_OFF))
                print('自定义设备4被设置为 ', custom_device_config.device4State)
            config.set_device_config_obj(custom_device_config)
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
            if config.KEY_LIGHT_COLOR in request.POST:
                light_config.lightColor = request.POST.get(config.KEY_LIGHT_COLOR, config.STATE_OFF)
                print('环境光颜色设置为', light_config.lightColor)
            if config.KEY_LIGHT_LEVEL in request.POST:
                light_config.lightLevel = request.POST.get(config.KEY_LIGHT_LEVEL, config.STATE_OFF)
                print('环境光亮度设置为', light_config.lightLevel)
            config.set_light_config_obj(light_config)
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
    if request_result == HTTP_RESULT_SUCCESS:
        temperature_config = config.get_temperature_config()
        if request.method == 'POST':
            if config.KEY_IS_AUTO_CONTROL in request.POST:
                temperature_config.isAutoControl = request.POST.get(config.KEY_IS_AUTO_CONTROL, config.STATE_OFF)
                print('自动温度控制被设置为 ' + temperature_config.isAutoControl)
            if config.KEY_UPPER_LIMIT in request.POST:
                temperature_config.upperLimit = request.POST.get(config.KEY_UPPER_LIMIT, 30)
                print('自动温度控制温度上限被设置为 ' + temperature_config.upperLimit)
            if config.KEY_LOWER_LIMIT in request.POST:
                temperature_config.lowerLimit = request.POST.get(config.KEY_LOWER_LIMIT, 0)
                print('自动温度控制温度下限被设置为 ' + temperature_config.lowerLimit)
            if config.KEY_UPPER_ACTION in request.POST:
                temperature_config.upperActions = request.POST.get(config.KEY_UPPER_ACTION, config.EMPTY_ACTION)
                print('自动温度控制温度上限执行动作被设置为 ' + temperature_config.upperActions)
            if config.KEY_LOWER_ACTION in request.POST:
                temperature_config.lowerActions = request.POST.get(config.KEY_LOWER_ACTION, config.EMPTY_ACTION)
                print('自动温度控制温度下限执行动作被设置为 ' + temperature_config.lowerActions)
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
    if request_result == HTTP_RESULT_SUCCESS:
        humidity_config = config.get_humidity_config()
        if request.method == 'POST':
            if config.KEY_IS_AUTO_CONTROL in request.POST:
                humidity_config.isAutoControl = request.POST.get(config.KEY_IS_AUTO_CONTROL, config.STATE_OFF)
                print('自动湿度控制被设置为 ' + humidity_config.isAutoControl)
            if config.KEY_UPPER_LIMIT in request.POST:
                humidity_config.upperLimit = request.POST.get(config.KEY_UPPER_LIMIT,
                                                              config.DEFAULT_HUMIDITY_UPPER_LIMIT)
                print('自动湿度控制温度上限被设置为 ' + humidity_config.upperLimit)
            if config.KEY_LOWER_LIMIT in request.POST:
                humidity_config.lowerLimit = request.POST.get(config.KEY_LOWER_LIMIT,
                                                              config.DEFAULT_HUMIDITY_LOWER_LIMIT)
                print('自动湿度控制湿度下限被设置为 ' + humidity_config.lowerLimit)
            if config.KEY_UPPER_ACTION in request.POST:
                humidity_config.upperActions = request.POST.get(config.KEY_UPPER_ACTION, config.DEFAULT_ACTIONS)
                print('自动湿度动作上限被设置为 ', humidity_config.upperActions)
            if config.KEY_LOWER_ACTION in request.POST:
                humidity_config.lowerActions = request.POST.get(config.KEY_LOWER_ACTION, config.DEFAULT_ACTIONS)
                print('自动湿度动作下限被设置为 ', humidity_config.upperActions)
            config.set_dumidity_config_obj(humidity_config)
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
    if request_result == HTTP_RESULT_SUCCESS:
        dirt_humidity_config = config.get_dirt_humidity_config()
        if request.method == 'POST':
            if config.KEY_IS_AUTO_CONTROL in request.POST:
                dirt_humidity_config.isAutoControl = request.POST.get(config.KEY_IS_AUTO_CONTROL, config.STATE_OFF)
                print('自动土壤湿度控制被设置为 ' + dirt_humidity_config.isAutoControl)
            if config.KEY_UPPER_LIMIT in request.POST:
                dirt_humidity_config.upperLimit = request.POST.get(config.KEY_UPPER_LIMIT,
                                                                   config.DEFAULT_HUMIDITY_UPPER_LIMIT)
                print('自动土壤湿度控制温度上限被设置为 ' + dirt_humidity_config.upperLimit)
            if config.KEY_LOWER_LIMIT in request.POST:
                dirt_humidity_config.lowerLimit = request.POST.get(config.KEY_LOWER_LIMIT,
                                                                   config.DEFAULT_HUMIDITY_LOWER_LIMIT)
                print('自动土壤湿度控制湿度下限被设置为 ' + dirt_humidity_config.lowerLimit)
            if config.KEY_UPPER_ACTION in request.POST:
                dirt_humidity_config.upperActions = request.POST.get(config.KEY_UPPER_ACTION, config.DEFAULT_ACTIONS)
                print('自动土壤湿度动作上限被设置为 ', dirt_humidity_config.upperActions)
            if config.KEY_LOWER_ACTION in request.POST:
                dirt_humidity_config.lowerActions = request.POST.get(config.KEY_LOWER_ACTION, config.DEFAULT_ACTIONS)
                print('自动土壤湿度动作下限被设置为 ', dirt_humidity_config.upperActions)
            config.set_dirt_humidity_config_obj(dirt_humidity_config)
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
JSON_NO_SUCH_USER = '{"result":-5}'
JSON_USER_EXIST = '{"result":-6}'
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


@csrf_exempt
def user(request):
    request_result = __checkUser(request)
    if request_result == HTTP_RESULT_SUCCESS:  # 如果请求成功
        if request.method == 'GET':  # 如果是Get获取数据
            print('Get请求')
            if {config.KEY_PAGE_NUM, config.KEY_PAGE_COUNT}.intersection(request.GET):  # 制定页码
                print('请求参数符合条件')
                user_list = database.User.objects.all()
                return HttpResponse(user_list)  # 未完成
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
                        temp_user = database.User().objects.get(username=user_username)
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


@csrf_exempt
def schedule(request):
    return HttpResponse(JSON_LOGIN_REQUIRE)


@csrf_exempt
def noSuchApi(request):
    return HttpResponse(JSON_NO_SUCH_API)
