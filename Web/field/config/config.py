import json
import os
import sys
import string
import configparser

EMPTY_ACTION = '[{}]'
REPEAT_TYPE_NO     = 0  # 不重复
REPEAT_TYPE_WEEK   = 1  # 每周几重复
REPEAT_TYPE_DAY    = 2  # 每过X天重复
REPEAT_TYPE_HOUR   = 3  # 每过X小时重复
REPEAT_TYPE_MINUTE = 4  # 每过X分钟重复
STATE_ON  = 1   # 开
STATE_OFF = 0   # 关
COLOR_RED    = 0    # 红色
COLOR_GREEN  = 1    # 绿色
COLOR_BLUE   = 2    # 蓝色
COLOR_YELLOW = 3    # 黄色 红+绿
COLOR_PURPLE = 4    # 紫色 红+蓝
COLOR_CYAN   = 5    # 青色 蓝+绿
COLOR_WHITE  = 6    # 白色 全部
LEVEL_LIGHT_0   = 0   # 亮度 顾名思义
LEVEL_LIGHT_10  = 1   # 亮度 顾名思义
LEVEL_LIGHT_20  = 2   # 亮度 顾名思义
LEVEL_LIGHT_30  = 3   # 亮度 顾名思义
LEVEL_LIGHT_40  = 4   # 亮度 顾名思义
LEVEL_LIGHT_50  = 5   # 亮度 顾名思义
LEVEL_LIGHT_60  = 6   # 亮度 顾名思义
LEVEL_LIGHT_70  = 7   # 亮度 顾名思义
LEVEL_LIGHT_80  = 8   # 亮度 顾名思义
LEVEL_LIGHT_90  = 9   # 亮度 顾名思义
LEVEL_LIGHT_100 = 10  # 亮度 顾名思义
FILE_NAME_CONFIG = "config/config.ini"
SECTIONS_CUSTOM_DEVICE = "custom_device" # 自定义设备配置文件名
SECTIONS_DIRT_HUMIDITY = "dirt_humidity" # 土壤湿度配置文件名
SECTIONS_FERTILIZATION = "fertilization" # 施肥配置文件名
SECTIONS_HUMIDITY = "humidity"           # 空气湿度配置文件名
SECTIONS_LIGHT = "light"                 # 灯光配置文件名
SECTIONS_SCHEDULE = "schedule"           # 定时配置文件名
SECTIONS_TEMPERATURE = "temperature"     # 温度配置文件名
SECTIONS_WATER = "water"                 # 浇水配置文件名
TARGET_NO                           = -1    # 无目标
TARGET_TEMPERATION_AUTO_CONTROL     = 0     # 温度自动控制
TARGET_HUMIDITY_AUTO_CONTROL        = 1     # 空气湿度自动控制
TARGET_DIRT_HUMIDITY_AUTO_CONTROL   = 2     # 土壤湿度自动控制
TARGET_FERTILIZATION_AUTO_CONTROL   = 3     # 自动施肥
TARGET_WATER_AUTO_CONTROL           = 4     # 自动浇水
TARGET_FERTILIZATION                = 5     # 施肥
TARGET_WATER                        = 6     # 浇水
TARGET_FAN                          = 7     # 风扇
TARGET_HEAT                         = 8     # 加热
TARGET_CUSTOM_DEVICE_1              = 9     # 自定义设备1
TARGET_CUSTOM_DEVICE_2              = 10    # 自定义设备2
TARGET_CUSTOM_DEVICE_3              = 11    # 自定义设备3
TARGET_CUSTOM_DEVICE_4              = 12    # 自定义设备4
TARGET_LIGHT                        = 13    # 灯光开关
TARGET_LIGHT_COLOR                  = 14    # 灯光颜色
TARGET_LIGHT_LEVEL                  = 15    # 灯光亮度
OPERATION_NO                        = -1    # 无操作
KEY_TARGET          = 'target'
KEY_OPERATION       = 'operation'
KEY_IS_AUTO_CONTROL = 'is_auto_control'
KEY_UPPER_LIMIT     = 'upper_limit'
KEY_LOWER_LIMIT     = 'lower_limit'
KEY_UPPER_ACTION    = 'upper_action'
KEY_LOWER_ACTION    = 'lower_action'
KEY_REPEAT_TYPE     = 'repeat_type'
KEY_REPEAT_CIRCLE   = 'repeat_circle'
KEY_HOUR            = 'hour'
KEY_MINUTE          = 'minute'
KEY_DEVICE_STATE_1  = 'device1_state'
KEY_DEVICE_STATE_2  = 'device2_state'
KEY_DEVICE_STATE_3  = 'device3_state'
KEY_DEVICE_STATE_4  = 'device4_state'
KEY_IS_LIGHT_ON     = 'is_light_on'
KEY_LIGHT_COLOR     = 'light_color'
KEY_LIGHT_LEVEL     = 'light_level'
KEY_IS_ON           = 'is_on'
KEY_NAME            = 'name'
KEY_ACTIONS         = 'actions'
KEY_PAGE_NUM        = 'page_num'    # 用户
KEY_PAGE_COUNT      = 'page_count'  # 用户
KEY_USERNAME        = 'username'    # 用户
KEY_PASSWORD        = 'password'    # 用户
KEY_IS_STUFF        = 'is_stuff'    # 用户
KEY_IS_ACTIVE       = 'is_active'   # 用户
KEY_NICKNAME        = 'nickname'    # 用户
KEY_INFO            = 'info'        # 用户
KEY_USER_ACTION_TYPE = 'action_type'# 用户
STRING_COLOR = {
    0:'红色',
    1:'绿色',
    2:'蓝色',
    3:'黄色',
    4:'紫色',
    5:'青色',
    6:'白色',
}
DEFAULT_AUTO_CONTROL = STATE_OFF
DEFAULT_TEMPERATURE_UPPER_LIMIT = 30
DEFAULT_TEMPERATURE_LOWER_LIMIT = 0
DEFAULT_ACTIONS = EMPTY_ACTION
DEFAULT_HUMIDITY_UPPER_LIMIT = 60
DEFAULT_HUMIDITY_LOWER_LIMIT = 10
DEFAULT_DIRT_HUMIDITY_UPPER_LIMIT = 70
DEFAULT_DIRT_HUMIDITY_LOWER_LIMIT = 5
DEFAULT_REPEAT_TYPE = REPEAT_TYPE_NO
DEFAULT_REPEAT_CIRCLE = 0
DEFAULT_REPEAT_HOUR = 6
DEFAULT_REPEAT_MINUTE = 30
DEFAULT_DEVICE_STATE = STATE_OFF
DEFAULT_LIGHT_COLOR = COLOR_RED
DEFAULT_LIGHT_LEVEL = LEVEL_LIGHT_100

# 这个是用来读取配置的方法集合
# 将会返回相应的类
def __write_value(config, sections, key, value):
    if not config.has_section(sections):
        config.add_section(sections)
    config.set(sections, key, str(value))

def __read_value(config, sections, key, def_value):
    try:
        return config.get(sections,key,raw=-1)
    except:
        return def_value

# 读取文本资源
def get_color_str(color_int):
    color_int = int(color_int)
    if color_int in STRING_COLOR:
        return STRING_COLOR[color_int]
    return '未设置'

# 读取自定义设备配置
def get_device_config():
    config=configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    deviceConfig = DeviceConfig()
    if config.has_section(SECTIONS_CUSTOM_DEVICE) :
        deviceConfig.device1State = __read_value(config,SECTIONS_CUSTOM_DEVICE,KEY_DEVICE_STATE_1,STATE_OFF)
        deviceConfig.device2State = __read_value(config,SECTIONS_CUSTOM_DEVICE,KEY_DEVICE_STATE_2,STATE_OFF)
        deviceConfig.device3State = __read_value(config,SECTIONS_CUSTOM_DEVICE,KEY_DEVICE_STATE_3,STATE_OFF)
        deviceConfig.device4State = __read_value(config,SECTIONS_CUSTOM_DEVICE,KEY_DEVICE_STATE_4,STATE_OFF)
    return deviceConfig

def set_device_config_obj(states):
    set_devices_config(states.device1State,states.device2State,states.device3State,states.device4State)

def set_devices_config(state1,state2,state3,state4):
    config=configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    __write_value(config, SECTIONS_CUSTOM_DEVICE, KEY_DEVICE_STATE_1, str(state1))
    __write_value(config, SECTIONS_CUSTOM_DEVICE, KEY_DEVICE_STATE_2, str(state2))
    __write_value(config, SECTIONS_CUSTOM_DEVICE, KEY_DEVICE_STATE_3, str(state3))
    __write_value(config, SECTIONS_CUSTOM_DEVICE, KEY_DEVICE_STATE_4, str(state4))
    config.write(open(FILE_NAME_CONFIG,'w'))

# 自动施肥配置
def get_fertilization_config():
    config = configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    device_config = FertilizationConfig()
    if config.has_section(SECTIONS_CUSTOM_DEVICE):
        device_config.isAutoControl = __read_value(config, SECTIONS_FERTILIZATION, KEY_IS_AUTO_CONTROL, DEFAULT_AUTO_CONTROL)
        device_config.repeatType = __read_value(config, SECTIONS_FERTILIZATION, KEY_REPEAT_TYPE, DEFAULT_REPEAT_TYPE)
        device_config.repeatCircle = __read_value(config, SECTIONS_FERTILIZATION, KEY_REPEAT_CIRCLE, DEFAULT_REPEAT_CIRCLE)
        device_config.hour = __read_value(config, SECTIONS_FERTILIZATION, KEY_HOUR, DEFAULT_REPEAT_HOUR)
        device_config.minute = __read_value(config, SECTIONS_FERTILIZATION, KEY_MINUTE, DEFAULT_REPEAT_MINUTE)
    return device_config

def set_fertilization_config(state,repeat_type,repeat_circle,hour,minute):
    config=configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    __write_value(config, SECTIONS_FERTILIZATION, KEY_IS_AUTO_CONTROL, str(state))
    __write_value(config, SECTIONS_FERTILIZATION, KEY_REPEAT_TYPE, str(repeat_type))
    __write_value(config, SECTIONS_FERTILIZATION, KEY_REPEAT_CIRCLE, str(repeat_circle))
    __write_value(config, SECTIONS_FERTILIZATION, KEY_HOUR, str(hour))
    __write_value(config, SECTIONS_FERTILIZATION, KEY_MINUTE, str(minute))
    config.write(open(FILE_NAME_CONFIG,'w'))

def set_fertilization_config_obj(obj):
    set_fertilization_config(obj.isAutoControl, obj.repeatType, obj.repeatCircle, obj.hour, obj.minute)

# 自动浇水配置
def get_water_config():
    config = configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    device_config = WateringConfig()
    if config.has_section(SECTIONS_CUSTOM_DEVICE):
        device_config.isAutoControl = __read_value(config, SECTIONS_WATER, KEY_IS_AUTO_CONTROL, DEFAULT_AUTO_CONTROL)
        device_config.repeatType = __read_value(config, SECTIONS_WATER, KEY_REPEAT_TYPE, DEFAULT_REPEAT_TYPE)
        device_config.repeatCircle = __read_value(config, SECTIONS_WATER, KEY_REPEAT_CIRCLE, DEFAULT_REPEAT_CIRCLE)
        device_config.hour = __read_value(config, SECTIONS_WATER, KEY_HOUR, DEFAULT_REPEAT_HOUR)
        device_config.minute = __read_value(config, SECTIONS_WATER, KEY_MINUTE, DEFAULT_REPEAT_MINUTE)
    return device_config

def set_water_config_obj(obj):
    set_water_config(obj.isAutoControl, obj.repeatType, obj.repeatCircle, obj.hour, obj.minute)

def set_water_config(state,repeat_type,repeat_circle,hour,minute):
    config=configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    __write_value(config, SECTIONS_WATER, KEY_IS_AUTO_CONTROL, str(state))
    __write_value(config, SECTIONS_WATER, KEY_REPEAT_TYPE, str(repeat_type))
    __write_value(config, SECTIONS_WATER, KEY_REPEAT_CIRCLE, str(repeat_circle))
    __write_value(config, SECTIONS_WATER, KEY_HOUR, str(hour))
    __write_value(config, SECTIONS_WATER, KEY_MINUTE, str(minute))
    config.write(open(FILE_NAME_CONFIG,'w'))

# 读取环境光配置
def get_light_config():
    config=configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    light_config = LightConfig()
    if config.has_section(SECTIONS_LIGHT):
        light_config.isLightOn = __read_value(config,SECTIONS_LIGHT,KEY_IS_LIGHT_ON,DEFAULT_AUTO_CONTROL)
        light_config.lightColor = __read_value(config,SECTIONS_LIGHT,KEY_LIGHT_COLOR,COLOR_WHITE)
        light_config.lightLevel = __read_value(config,SECTIONS_LIGHT,KEY_LIGHT_LEVEL,LEVEL_LIGHT_100)
    return light_config

def set_light_config_obj(obj):
    set_light_config(obj.isLightOn,obj.lightColor,obj.lightLevel)

def set_light_config(state,color,level):
    config=configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    __write_value(config, SECTIONS_LIGHT, KEY_IS_LIGHT_ON, str(state))
    __write_value(config, SECTIONS_LIGHT, KEY_LIGHT_COLOR, str(color))
    __write_value(config, SECTIONS_LIGHT, KEY_LIGHT_LEVEL, str(level))
    config.write(open(FILE_NAME_CONFIG,'w'))

# 读取温度配置
def get_temperature_config():
    config = configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    temperature_config = TemperatureConfig()
    if config.has_section(SECTIONS_TEMPERATURE):
        temperature_config.isAutoControl = __read_value(config, SECTIONS_TEMPERATURE, KEY_IS_AUTO_CONTROL, DEFAULT_AUTO_CONTROL)
        temperature_config.upperLimit = __read_value(config, SECTIONS_TEMPERATURE, KEY_UPPER_LIMIT, DEFAULT_TEMPERATURE_UPPER_LIMIT)
        temperature_config.lowerLimit = __read_value(config, SECTIONS_TEMPERATURE, KEY_LOWER_LIMIT, DEFAULT_TEMPERATURE_LOWER_LIMIT)
        temperature_config.upperActions = __read_value(config, SECTIONS_TEMPERATURE, KEY_UPPER_ACTION, DEFAULT_ACTIONS)
        temperature_config.lowerActions = __read_value(config, SECTIONS_TEMPERATURE, KEY_LOWER_ACTION, DEFAULT_ACTIONS)
    return temperature_config

def set_temperature_config_obj(obj):
    set_temperature_config(obj.isAutoControl, obj.upperLimit, obj.upperActions, obj.lowerLimit, obj.lowerActions)

def set_temperature_config(state, upper_limit, upper_action, lower_limit, lower_action):
    config = configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    __write_value(config, SECTIONS_TEMPERATURE, KEY_IS_AUTO_CONTROL, str(state))
    __write_value(config, SECTIONS_TEMPERATURE, KEY_UPPER_LIMIT, str(upper_limit))
    __write_value(config, SECTIONS_TEMPERATURE, KEY_UPPER_ACTION, str(upper_action))
    __write_value(config, SECTIONS_TEMPERATURE, KEY_LOWER_LIMIT, str(lower_limit))
    __write_value(config, SECTIONS_TEMPERATURE, KEY_LOWER_ACTION, str(lower_action))
    config.write(open(FILE_NAME_CONFIG, 'w'))

# 读取空气湿度配置
def get_humidity_config():
    config = configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    temperature_config = TemperatureConfig()
    if config.has_section(SECTIONS_HUMIDITY):
        temperature_config.isAutoControl = __read_value(config, SECTIONS_HUMIDITY, KEY_IS_AUTO_CONTROL, DEFAULT_AUTO_CONTROL)
        temperature_config.upperLimit = __read_value(config, SECTIONS_HUMIDITY, KEY_UPPER_LIMIT, DEFAULT_HUMIDITY_UPPER_LIMIT)
        temperature_config.lowerLimit = __read_value(config, SECTIONS_HUMIDITY, KEY_LOWER_LIMIT, DEFAULT_HUMIDITY_LOWER_LIMIT)
        temperature_config.upperActions = __read_value(config, SECTIONS_HUMIDITY, KEY_UPPER_ACTION, DEFAULT_ACTIONS)
        temperature_config.lowerActions = __read_value(config, SECTIONS_HUMIDITY, KEY_LOWER_ACTION, DEFAULT_ACTIONS)
    return temperature_config

def set_dumidity_config_obj(obj):
    set_humidity_config(obj.isAutoControl, obj.upperLimit, obj.upperActions, obj.lowerLimit, obj.lowerActions)

def set_humidity_config(state, upper_limit, upper_action, lower_limit, lower_action):
    config = configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    __write_value(config, SECTIONS_HUMIDITY, KEY_IS_AUTO_CONTROL, str(state))
    __write_value(config, SECTIONS_HUMIDITY, KEY_UPPER_LIMIT, str(upper_limit))
    __write_value(config, SECTIONS_HUMIDITY, KEY_UPPER_ACTION, str(upper_action))
    __write_value(config, SECTIONS_HUMIDITY, KEY_LOWER_LIMIT, str(lower_limit))
    __write_value(config, SECTIONS_HUMIDITY, KEY_LOWER_ACTION, str(lower_action))
    config.write(open(FILE_NAME_CONFIG, 'w'))

# 读取土壤湿度配置
def get_dirt_humidity_config():
    config = configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    temperature_config = TemperatureConfig()
    if config.has_section(SECTIONS_DIRT_HUMIDITY):
        temperature_config.isAutoControl = __read_value(config, SECTIONS_DIRT_HUMIDITY, KEY_IS_AUTO_CONTROL, DEFAULT_AUTO_CONTROL)
        temperature_config.upperLimit = __read_value(config, SECTIONS_DIRT_HUMIDITY, KEY_UPPER_LIMIT, DEFAULT_DIRT_HUMIDITY_UPPER_LIMIT)
        temperature_config.lowerLimit = __read_value(config, SECTIONS_DIRT_HUMIDITY, KEY_LOWER_LIMIT, DEFAULT_DIRT_HUMIDITY_LOWER_LIMIT)
        temperature_config.upperActions = __read_value(config, SECTIONS_DIRT_HUMIDITY, KEY_UPPER_ACTION, DEFAULT_ACTIONS)
        temperature_config.lowerActions = __read_value(config, SECTIONS_DIRT_HUMIDITY, KEY_LOWER_ACTION, DEFAULT_ACTIONS)
    return temperature_config

def set_dirt_humidity_config_obj(obj):
    set_dirt_humidity_config(obj.isAutoControl, obj.upperLimit, obj.upperActions, obj.lowerLimit, obj.lowerActions)

def set_dirt_humidity_config(state, upper_limit, upper_action, lower_limit, lower_action):
    config = configparser.ConfigParser()
    config.read(FILE_NAME_CONFIG)
    __write_value(config, SECTIONS_DIRT_HUMIDITY, KEY_IS_AUTO_CONTROL, str(state))
    __write_value(config, SECTIONS_DIRT_HUMIDITY, KEY_UPPER_LIMIT, str(upper_limit))
    __write_value(config, SECTIONS_DIRT_HUMIDITY, KEY_UPPER_ACTION, str(upper_action))
    __write_value(config, SECTIONS_DIRT_HUMIDITY, KEY_LOWER_LIMIT, str(lower_limit))
    __write_value(config, SECTIONS_DIRT_HUMIDITY, KEY_LOWER_ACTION, str(lower_action))
    config.write(open(FILE_NAME_CONFIG, 'w'))

# 要执行的状态
class Action:
    target = TARGET_NO
    operation = OPERATION_NO

def __parse_action_list_from_str(json_str):
    json_str = json_str.replace('\\','')
    action_list = []
    json_object_list = json.loads(json_str)
    # for temp_json_obj in json_object_list:
    #     temp_action = Action()
    #     temp_action.target = temp_json_obj[KEY_TARGET]
    #     temp_action.operation = temp_json_obj[KEY_OPERATION]
    #     action_list.append(temp_action)
    return action_list

# 描述温度设置的类
class TemperatureConfig:
    isAutoControl = DEFAULT_AUTO_CONTROL
    upperLimit = DEFAULT_TEMPERATURE_UPPER_LIMIT
    lowerLimit = DEFAULT_TEMPERATURE_LOWER_LIMIT
    upperActions = DEFAULT_ACTIONS
    lowerActions = DEFAULT_ACTIONS

# 描述空气湿度设置的类
class HumidityConfig:
    isAutoControl = DEFAULT_AUTO_CONTROL
    upperLimit = DEFAULT_HUMIDITY_UPPER_LIMIT
    lowerLimit = DEFAULT_HUMIDITY_LOWER_LIMIT
    upperActions = DEFAULT_ACTIONS
    lowerActions = DEFAULT_ACTIONS

# 描述土壤湿度设置的类
class DirtHumidityConfig:
    isAutoControl = DEFAULT_AUTO_CONTROL
    upperLimit = DEFAULT_DIRT_HUMIDITY_UPPER_LIMIT
    lowerLimit = DEFAULT_DIRT_HUMIDITY_LOWER_LIMIT
    upperActions = DEFAULT_ACTIONS
    lowerActions = DEFAULT_ACTIONS

# 描述施肥设置的类
class FertilizationConfig:
    isAutoControl = DEFAULT_AUTO_CONTROL
    repeatType = REPEAT_TYPE_NO
    hour = DEFAULT_REPEAT_HOUR
    minute = DEFAULT_REPEAT_MINUTE
    repeatCircle = ''  # 如果是按日期，则为对应数字，如果是按星期，则为日一二三四五六，例1010010

# 描述浇水设置的类
class WateringConfig:
    isAutoControl = DEFAULT_AUTO_CONTROL
    repeatType = REPEAT_TYPE_NO
    hour = DEFAULT_REPEAT_HOUR
    minute = DEFAULT_REPEAT_MINUTE
    repeatCircle = ''  # 如果是按日期，则为对应数字，如果是按星期，则为日一二三四五六，例1010010

# 描述自定义设备设置的类
class DeviceConfig:
    device1State = DEFAULT_DEVICE_STATE
    device2State = DEFAULT_DEVICE_STATE
    device3State = DEFAULT_DEVICE_STATE
    device4State = DEFAULT_DEVICE_STATE

# 描述光照设置的类
class LightConfig:
    isLightOn = DEFAULT_AUTO_CONTROL
    lightColor = DEFAULT_LIGHT_COLOR
    lightLevel = DEFAULT_LIGHT_LEVEL
