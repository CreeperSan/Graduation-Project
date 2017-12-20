from django.shortcuts import render
from django.contrib.auth.decorators import login_required
from django.http import HttpResponse
import config.config as config

# Create your views here.

@login_required
def index(request):
    return render(request,'farm/index.html',context={})

@login_required
def monitor(request):
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
    return render(request,'farm/schedule.html',context={})

@login_required
def history(request):
    return render(request,'farm/history.html',context={})

@login_required
def setting(request):
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
    return render(request,'farm/me.html',context={})

@login_required
def logout(request):
    return render(request,'farm/logout.html',context={})
    # return forbidden(request)

def forbidden(request):
    return render(request,'farm/forbidden.html',context={})
