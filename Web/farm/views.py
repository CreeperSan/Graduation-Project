from django.shortcuts import render
from django.contrib.auth.decorators import login_required
from django.http import HttpResponse
import config.config as config
import state.state as state



lightColorStrDirt = {
                    0 : '红色',
                    1 : '绿色',
                    2 : '蓝色',
                    3 : '黄色',
                    4 : '紫色',
                    5 : '青色',
                    6 : '白色',
                }

@login_required
def index(request):
    # import conn.conn as socket
    # socket.sendData('Hello World From Django')
    # 空气温度显示的文本
    temperatureAirSubTitle = ' ' 
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
        else :
            lightTitle = '其他颜色'
    else :
        lightTitle = '关闭'
        lightSubTitle = '已关闭'
    # 自定义设备的显示文本
    deviceStateTitle = ' '
    deviceStateSubTitle = ' '
    if int(state.device_1) == 1 and int(state.device_2) == 1 and int(state.device_3) == 1 and int(state.device_4) == 1:
        deviceStateTitle = 'ON'
        deviceStateSubTitle = '自定义设备均已打开'
    elif int(state.device_1) != 1 and int(state.device_2) != 1 and int(state.device_3) != 1 and int(state.device_4) != 1:
        deviceStateTitle = 'OFF'
        deviceStateSubTitle = '自定义设备均已关闭'
    else :
        deviceStateTitle = 'ON'
        deviceStateSubTitle = '自定义设备已部分打开'
    return render(request,'farm/index.html',context={
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
        })

@login_required
def monitor(request):
    if not checkHasPermissionModifyConfig(request.user):
        return forbidden(request)
    device_config = config.get_device_config()
    light_config = config.get_light_config()
    return render(request,'farm/farm.html',context={
        'device1_state':device_config.device1State,
        'device2_state':device_config.device2State,
        'device3_state':device_config.device3State,
        'device4_state':device_config.device4State,
        'light_state':light_config.isLightOn,
        'light_color':light_config.lightColor,
        'light_color_str':config.get_color_str(light_config.lightColor),
        'light_level':light_config.lightLevel
        })

@login_required
def schedule(request):
    if not checkHasPermissionModifyConfig(request.user):
        return forbidden(request)
    try:
        scheduleList = config.get_schedule()['data']
        for scheduleItem in scheduleList:
            scheduleItem['repeat_str'] = __getScheduleWeekdayStr(scheduleItem['repeat_value'])
    except Exception as e:
        scheduleList = []
    return render(request,'farm/schedule.html',context={'scheduleList':scheduleList,'scheduleJsonPart':str(scheduleList).replace("'",'"')})

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

@login_required
def history(request):
    return render(request,'farm/history.html',context={})

@login_required
def setting(request):
    if not checkHasPermissionModifyConfig(request.user):
        return forbidden(request)
    temperature_config = config.get_temperature_config()
    humidity_config = config.get_humidity_config()
    dirt_humidity_config = config.get_dirt_humidity_config()
    fertilization_config = config.get_fertilization_config()
    watering_config = config.get_water_config()
    print('获取到的温度上限动作为 : '+str(temperature_config.upperActions))
    return render(request,'farm/setting.html',context={
        'temperature_state':temperature_config.isAutoControl,
        'temperature_upper_limit':temperature_config.upperLimit,
        'temperature_lower_limit':temperature_config.lowerLimit,
        'temperature_upper_actions':temperature_config.upperActions,
        'temperature_lower_actions':temperature_config.lowerActions,
        'himidity_state':humidity_config.isAutoControl,
        'himidity_upper_limit':humidity_config.upperLimit,
        'himidity_lower_limit':humidity_config.lowerLimit,
        'himidity_upper_actions':humidity_config.upperActions,
        'himidity_lower_actions':humidity_config.lowerActions,
        'dirt_himidity_state':dirt_humidity_config.isAutoControl,
        'dirt_himidity_upper_limit':dirt_humidity_config.upperLimit,
        'dirt_himidity_lower_limit':dirt_humidity_config.lowerLimit,
        'dirt_himidity_upper_actions':dirt_humidity_config.upperActions,
        'dirt_himidity_lower_actions':dirt_humidity_config.lowerActions,
        'fertilization_state':fertilization_config.isAutoControl,
        'fertilization_repeat_type':fertilization_config.repeatType,
        'fertilization_hour':fertilization_config.hour,
        'fertilization_minute':fertilization_config.minute,
        'fertilization_repeat_circle':fertilization_config.repeatCircle,
        'fertilization_hint_text':'自动施肥周期',
        'watering_state':watering_config.isAutoControl,
        'watering_repeat_type':watering_config.repeatType,
        'watering_hour':watering_config.hour,
        'watering_minute':watering_config.minute,
        'watering_repeat_circle':watering_config.repeatCircle,
        'watering_hint_text':'自动浇水周期',
        })

@login_required
def me(request):
    level_img_str = getUserLevelImg(request.user)
    level_str = getUserLevelStr(request.user)
    nickname = getNicknameStr(request.user)
    username = request.user.username
    is_staff = request.user.is_staff
    is_available = not request.user.is_active
    register_time = str(request.user.date_joined)
    info = request.user.info
    return render(request,'farm/me.html',context={
        'level_img_str':level_img_str,
        'level_str':level_str,
        'nickname':nickname,
        'username':username,
        'is_staff':bool_to_chs_str_lambda(is_staff),
        'is_available':bool_to_chs_str_lambda(is_available),
        'register_time':register_time[0:len(register_time)-13],
        'info':info,
        })

@login_required
def logout(request):
    return render(request,'farm/logout.html',context={})

@login_required
def forbidden(request):
    return render(request,'farm/forbidden.html',context={})

bool_to_chs_str_lambda = lambda temp : '是' if temp else '否' 

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

def checkHasPermissionModifyConfig(user):
    return user.is_active and user.is_staff 