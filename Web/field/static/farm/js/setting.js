var TYPE_NONE = 0 ;
var TYPE_TEMPERATURE_UPPER_LIMIT = 1;
var TYPE_TEMPERATURE_UPPER_ACTIONS = 2;
var TYPE_TEMPERATURE_LOWER_LIMIT = 3;
var TYPE_TEMPERATURE_LOWER_ACTIONS = 4;
var TYPE_HUMIDITY_UPPER_LIMIT = 5 ;
var TYPE_HUMIDITY_UPPER_ACTIONS = 6 ;
var TYPE_HUMIDITY_LOWER_LIMIT = 7 ;
var TYPE_HUMIDITY_LOWER_ACTIONS = 8 ;
var TYPE_DIRT_HUMIDITY_UPPER_LIMIT = 9 ;
var TYPE_DIRT_HUMIDITY_UPPER_ACTIONS = 10 ;
var TYPE_DIRT_HUMIDITY_LOWER_LIMIT = 11 ;
var TYPE_DIRT_HUMIDITY_LOWER_ACTIONS = 12 ;
var TYPE_FERTILIZATION_CIRCLE = 13 ;
var TYPE_WATER_CIRCLE = 14 ;

var TEMPERATURE_MIN = -10 ;
var TEMPERATURE_MAX = 50 ;
var HUMIDITY_MAX = 100 ;
var HUMIDITY_MIN = 0 ;
var DIRT_HUMIDITY_MAX = 100 ;
var DIRT_HUMIDITY_MIN = 0 ;

var URL_TEMPERATURE = '../../api/temperature/'
var URL_HUMIDITY = '../../api/humidity/'
var URL_DIRT_HUMIDITY = '../../api/dirt_humidity/'
var URL_FERTILIZATION = '../../api/fertilization/'
var URL_WATER = '../../api/water/'

var type = TYPE_NONE;

$(document).ready(function(){

    $.fn.bootstrapSwitch.defaults.onColor = 'success';
    $.fn.bootstrapSwitch.defaults.offColor = 'default';
    $('#test_switch1').bootstrapSwitch();
    $('.switch').bootstrapSwitch();
    $('#ex1').slider({
        formatter: function(value) {
            refreshSeekbarHintText(value);
        }
    });
    $('#auto_fertilization_state').on('switchChange.bootstrapSwitch', function (event,state) {  
        ajaxPost(
            URL_FERTILIZATION,
            {'is_auto_control':Number($(this).bootstrapSwitch('state'))},
            function (){},
            function (){
                showHintDialog('网络错误','设置自动施肥开关失败，请检查您的网络连接后重试。');
            });
    });
    $('#auto_water_state').on('switchChange.bootstrapSwitch', function (event,state) {  
        ajaxPost(
            URL_WATER,
            {'is_auto_control':Number($(this).bootstrapSwitch('state'))},
            function (){},
            function (){
                showHintDialog('网络错误','设置自动浇水开关失败，请检查您的网络连接后重试。');
            });
    });
    $('#topic_water_hint_txt').html(getDisplayCycleStrFromFlag(
        water_cycle['repeat_type'] == CYCLE_WEEKDAY,
        water_cycle['hour'],
        water_cycle['minute'],
        water_cycle['repeat_type'],
        water_cycle['repeat_circle'],
    ));//自动浇水提示文本
    $('#topic_fertilization_hint_txt').html(getDisplayCycleStrFromFlag(
        fertilization_cycle['repeat_type'] == CYCLE_WEEKDAY,
        fertilization_cycle['hour'],
        fertilization_cycle['minute'],
        fertilization_cycle['repeat_type'],
        fertilization_cycle['repeat_circle'],
    ));//自动施肥提示文本
});

function onConfirm(){
    var progress = $('#ex1').data('slider').getValue();
    switch(type){
        case TYPE_TEMPERATURE_UPPER_LIMIT:///////////////////////////////////// 温度上限
            temperature_upper = progress;
            $('#dialog_content_temp_upper_limit_btn').html(progress+'℃');
            ajaxPost(URL_TEMPERATURE,
                {'upper_limit':temperature_upper},
                function(){},
                function(){
                    showHintDialog('网络错误','修改温度上限失败，请检查您的网络连接。');
                });
            break;
        case TYPE_TEMPERATURE_LOWER_LIMIT:////////////////////////////////////  温度下限
            temperature_lower = progress;
            $('#dialog_content_temp_lower_limit_btn').html(progress+'℃');
            ajaxPost(URL_TEMPERATURE,
                {'lower_limit':temperature_lower},
                function(){},
                function(){
                    showHintDialog('网络错误','修改温度下限失败，请检查您的网络连接。');
                });
            break;
        case TYPE_TEMPERATURE_UPPER_ACTIONS://///////////////////////////////// 温度上限事件
            temperature_upper_action = currentEventJson;
            ajaxPost(URL_TEMPERATURE,
                {'upper_action':JSON.stringify(currentEventJson)},
                function(){},
                function(){
                    showHintDialog('网络错误','修改温度上限动作失败，请检查您的网络连接');
                });
            break;
        case TYPE_TEMPERATURE_LOWER_ACTIONS://///////////////////////////////// 温度下限事件
            temperature_lower_action = currentEventJson;
            ajaxPost(URL_TEMPERATURE,
                {'lower_action':JSON.stringify(currentEventJson)},
                function(){},
                function(){
                    showHintDialog('网络错误','修改温度下限动作失败，请检查您的网络连接');
                });
            break;
        case TYPE_HUMIDITY_UPPER_LIMIT://////////////////////////////////////// 湿度上限
            humidity_upper = progress;
            $('#dialog_content_humidity_upper_limit_btn').html(progress+'%');
            ajaxPost(URL_HUMIDITY,
                {'upper_limit':humidity_upper},
                function(){},
                function(){
                    showHintDialog('网络错误','修改湿度上限失败，请检查您的网络连接。');
                });
            break;
        case TYPE_HUMIDITY_LOWER_LIMIT://////////////////////////////////////// 湿度下限
            humidity_lower = progress;
            $('#dialog_content_humidity_lower_limit_btn').html(progress+'%');
            ajaxPost(URL_HUMIDITY,
                {'lower_limit':humidity_lower},
                function(){},
                function(){
                    showHintDialog('网络错误','修改湿度下限失败，请检查您的网络连接。');
                });
            break;
        case TYPE_HUMIDITY_UPPER_ACTIONS:////////////////////////////////////// 湿度上限事件
            humidity_upper_action = currentEventJson;
            ajaxPost(URL_HUMIDITY,
                {'upper_action':JSON.stringify(currentEventJson)},
                function(){},
                function(){
                    showHintDialog('网络错误','修改空气湿度上限动作失败，请检查您的网络连接');
                });
            break;
        case TYPE_HUMIDITY_LOWER_ACTIONS://///////////////////////////////////  湿度下限事件
            humidity_lower_action = currentEventJson;
            ajaxPost(URL_HUMIDITY,
                {'lower_action':JSON.stringify(currentEventJson)},
                function(){},
                function(){
                    showHintDialog('网络错误','修改空气湿度上限动作失败，请检查您的网络连接');
                });
            break;
        case TYPE_DIRT_HUMIDITY_UPPER_LIMIT://////////////////////////////////  土壤湿度上限
            dirt_humidity_upper = progress;
            $('#dialog_content_dirt_humidity_upper_limit_btn').html(progress+'%');
            ajaxPost(URL_DIRT_HUMIDITY,
                {'upper_limit':dirt_humidity_upper},
                function(){},
                function(){
                    showHintDialog('网络错误','修改空气湿度上限失败，请检查您的网络连接。');
                });
            break;
        case TYPE_DIRT_HUMIDITY_LOWER_LIMIT://////////////////////////////////  土壤湿度下限
            dirt_humidity_lower = progress;
            $('#dialog_content_dirt_humidity_lower_limit_btn').html(progress+'%');
            ajaxPost(URL_DIRT_HUMIDITY,
                {'lower_limit':dirt_humidity_lower},
                function(){},
                function(){
                    showHintDialog('网络错误','修改空气湿度下限失败，请检查您的网络连接。');
                });
            break;
        case TYPE_DIRT_HUMIDITY_UPPER_ACTIONS:///////////////////////////////// 土壤湿度上限事件
            dirt_humidity_upper_action = currentEventJson;
            ajaxPost(URL_DIRT_HUMIDITY,
                {'upper_action':JSON.stringify(currentEventJson)},
                function(){},
                function(){
                    showHintDialog('网络错误','修改土壤湿度上限动作失败，请检查您的网络连接');
                });
            break;
        case TYPE_DIRT_HUMIDITY_LOWER_ACTIONS:///////////////////////////////// 土壤湿度下限事件
            dirt_humidity_lower_action = currentEventJson;
            ajaxPost(URL_DIRT_HUMIDITY,
                {'lower_action':JSON.stringify(currentEventJson)},
                function(){},
                function(){
                    showHintDialog('网络错误','修改土壤湿度上限动作失败，请检查您的网络连接');
                });
            break;
        case TYPE_FERTILIZATION_CIRCLE://////////////////////////////////////// 自动施肥
        case TYPE_WATER_CIRCLE://////////////////////////////////////////////// 自动浇水
            if (selectCycleType == CYCLE_NO) {break;}
            var cycleVal = parseInt($('#dialog_content_repeat_cycle').val());
            var hourVal = parseInt($('#dialog_content_hour').val());
            var minVal = parseInt($('#dialog_content_minute').val());
            if (isNaN(hourVal) || Number(hourVal)<0 ||Number(hourVal)>=24) { $('#dialog_content_hour').shake(1, 10, 300);return; }
            if (isNaN(minVal) || Number(minVal)<0 || Number(minVal)>=60) { $('#dialog_content_minute').shake(1, 10, 300);return; }
            switch(selectCycleType){
                case CYCLE_WEEKDAY:
                    cycleVal = getWeekdayStr(isSunday)+getWeekdayStr(isMonday)+getWeekdayStr(isTuesday)+getWeekdayStr(isWensday)+getWeekdayStr(isThusday)+getWeekdayStr(isFriday)+getWeekdayStr(isSatday);
                break;
                case CYCLE_DAY:
                case CYCLE_HOUR:
                case CYCLE_MINUTE:
                    if (isNaN(cycleVal) || Number(cycleVal)<0 || Number(cycleVal)>=999999) { $('#dialog_content_repeat_cycle').shake(1, 10, 300);return; }
                break;
            }
            if (type == TYPE_FERTILIZATION_CIRCLE) {//如果是施肥
                $('#topic_fertilization_hint_txt').html(getDisplayCycleStr(selectCycleType==CYCLE_WEEKDAY,hourVal,minVal,selectCycleType,cycleVal));
                fertilization_cycle['hour'] = hourVal;
                fertilization_cycle['minute'] = minVal;
                fertilization_cycle['repeat_type'] = selectCycleType;
                fertilization_cycle['repeat_circle'] = cycleVal;
                ajaxPost(URL_FERTILIZATION,
                    {'hour':hourVal,'minute':minVal,'repeat_type':selectCycleType,'repeat_circle':cycleVal},
                    function(){
                    },
                    function(){
                        showHintDialog('网络错误','修改自动施肥周期失败，请检查您的网络连接。');
                    })
            }else if (type == TYPE_WATER_CIRCLE) {//如果是浇水
                $('#topic_water_hint_txt').html(getDisplayCycleStr(selectCycleType==CYCLE_WEEKDAY,hourVal,minVal,selectCycleType,cycleVal));
                water_cycle['hour'] = hourVal;
                water_cycle['minute'] = minVal;
                water_cycle['repeat_type'] = selectCycleType;
                water_cycle['repeat_circle'] = cycleVal;
                console.log('浇水循环周期 ' + water_cycle['repeat_circle']);
                ajaxPost(URL_WATER,
                    {'hour':hourVal,'minute':minVal,'repeat_type':selectCycleType,'repeat_circle':cycleVal},
                    function(){},
                    function(){
                        showHintDialog('网络错误','修改自动浇水周期失败，请检查您的网络连接。');
                    })
            }
            break;
    }
    hideDialog();
}


function getWeekdayStr(weekdayBoolean){
    if (weekdayBoolean) {
        return '1';
    }
    return '0';
}
function getWeekRepeatStr(){
    return '每周'+ (isSunday?' 日':'') + (isMonday?' 一':'') + (isTuesday?' 二':'') + (isWensday?' 三':'') + (isThusday?' 四':'') + (isFriday?' 五':'') + (isSatday?' 六':'');
}
function getWeekRepeatStrFromString(tempFlagStr){
    var flagArray = tempFlagStr.split('');
    return '每周'+ (flagArray[0]!=0?' 日':'') + (flagArray[1]!=0?' 一':'') + (flagArray[2]!=0?' 二':'') + (flagArray[3]!=0?' 三':'') + (flagArray[4]!=0?' 四':'') + (flagArray[5]!=0?' 五':'') + (flagArray[6]!=0?' 六':'');
}
function getTimeStr(hour,minute){
    return (hour<10?('0'+hour):hour) +':'+(minute<10?('0'+minute):minute);
}
function getRepeatCycleUnitStr(type,unitCount){
    var unitStr = '';
    switch(type){
        case CYCLE_DAY: unitStr = '天';break;
        case CYCLE_HOUR: unitStr = '小时';break;
        case CYCLE_MINUTE: unitStr = '分钟';break;
    }
    return unitCount+' '+unitStr;
}
//获取周期的文本
function getDisplayCycleStr(isWeekday,hour,minute,repeatType,repeatCycle){
    if (isWeekday) {
        return getWeekRepeatStr()+' 的'+getTimeStr(hour,minute)+'重复';
    }else{
        return '从 '+getTimeStr(hour,minute)+' 开始，每隔 '+getRepeatCycleUnitStr(repeatType,repeatCycle)+' 重复';
    }
}

function getDisplayCycleStrFromFlag(isWeekday,hour,minute,repeatType,repeatCycle){
    if (isWeekday) {
        return getWeekRepeatStrFromString(repeatCycle.toString())+' 的'+getTimeStr(hour,minute)+'重复';
    }else{
        return '从 '+getTimeStr(hour,minute)+' 开始，每隔 '+getRepeatCycleUnitStr(repeatType,repeatCycle)+' 重复';
    }
}

/**
 *  往下是选择动作的相关处理时间
 */

var TARGET_NO                           = -1 ;    // 无目标
var TARGET_TEMPERATION_AUTO_CONTROL     = 0 ;     // 温度自动控制
var TARGET_HUMIDITY_AUTO_CONTROL        = 1 ;     // 空气湿度自动控制
var TARGET_DIRT_HUMIDITY_AUTO_CONTROL   = 2 ;     // 土壤湿度自动控制
var TARGET_FERTILIZATION_AUTO_CONTROL   = 3 ;     // 自动施肥
var TARGET_WATER_AUTO_CONTROL           = 4 ;     // 自动浇水
var TARGET_FERTILIZATION                = 5 ;     // 施肥
var TARGET_WATER                        = 6 ;     // 浇水
var TARGET_FAN                          = 7 ;     // 风扇
var TARGET_HEAT                         = 8 ;     // 加热
var TARGET_CUSTOM_DEVICE_1              = 9 ;     // 自定义设备1
var TARGET_CUSTOM_DEVICE_2              = 10 ;    // 自定义设备2
var TARGET_CUSTOM_DEVICE_3              = 11 ;    // 自定义设备3
var TARGET_CUSTOM_DEVICE_4              = 12 ;    // 自定义设备4
var TARGET_LIGHT                        = 13 ;    // 灯光开关
var TARGET_LIGHT_COLOR                  = 14 ;    // 灯光颜色
var TARGET_LIGHT_LEVEL                  = 15 ;    // 灯光亮度
var OPERATION_NO                        = -1 ;    // 无操作
var STATE_ON  = 1 ;   // 开
var STATE_OFF = 0 ;   // 关
var COLOR_RED    = 0 ;    // 红色
var COLOR_GREEN  = 1 ;    // 绿色
var COLOR_BLUE   = 2 ;    // 蓝色
var COLOR_YELLOW = 3 ;    // 黄色 红+绿
var COLOR_PURPLE = 4 ;    // 紫色 红+蓝
var COLOR_CYAN   = 5 ;    // 青色 蓝+绿
var COLOR_WHITE  = 6 ;    // 白色 全部
var LEVEL_LIGHT_0   = 0 ;   // 亮度 顾名思义
var LEVEL_LIGHT_10  = 1 ;   // 亮度 顾名思义
var LEVEL_LIGHT_20  = 2 ;   // 亮度 顾名思义
var LEVEL_LIGHT_30  = 3 ;   // 亮度 顾名思义
var LEVEL_LIGHT_40  = 4 ;   // 亮度 顾名思义
var LEVEL_LIGHT_50  = 5 ;   // 亮度 顾名思义
var LEVEL_LIGHT_60  = 6 ;   // 亮度 顾名思义
var LEVEL_LIGHT_70  = 7 ;   // 亮度 顾名思义
var LEVEL_LIGHT_80  = 8 ;   // 亮度 顾名思义
var LEVEL_LIGHT_90  = 9 ;   // 亮度 顾名思义
var LEVEL_LIGHT_100 = 10 ;  // 亮度 顾名思义
var CYCLE_NO = 0 ;
var CYCLE_WEEKDAY = 1 ;
var CYCLE_DAY = 2 ;
var CYCLE_HOUR = 3 ;
var CYCLE_MINUTE = 4 ;
var ACTION_NO = 0;
var ACTION_TEMPERATURE_UPPER = 1;
var ACTION_TEMPERATURE_LOWER = 2;
var ACTION_HUMIDITY_UPPER = 3;
var ACTION_HUMIDITY_LOWER = 4;
var ACTION_DIRT_HUMIDITY_UPPER = 5;
var ACTOIN_DIRT_HUMIDITY_LOWER = 6;

var selectTarget = TARGET_NO;
var selectValue = OPERATION_NO;
var selectCycleType = CYCLE_NO;
var selectCycle = 0;

function onTypeItemSelected(selectObj){
    value = selectObj.value;//选中的值
    $('#dialog_content_value_select').val('value_none');
    //往下是设置数值的
    switch(value){
        case 'target_none':selectActionTarget = TARGET_NO; break;
        case 'target_none':selectActionTarget = TARGET_NO; break;
        case 'target_temp_auto':selectActionTarget = TARGET_TEMPERATION_AUTO_CONTROL; break;
        case 'target_humidity_auto':selectActionTarget = TARGET_HUMIDITY_AUTO_CONTROL; break;
        case 'target_dirt_humdity_auto':selectActionTarget = TARGET_DIRT_HUMIDITY_AUTO_CONTROL; break;
        case 'target_fertilization_auto':selectActionTarget = TARGET_FERTILIZATION_AUTO_CONTROL; break;
        case 'target_water_auto':selectActionTarget = TARGET_WATER_AUTO_CONTROL; break;
        case 'target_fertilization':selectActionTarget = TARGET_FERTILIZATION; break;
        case 'target_water':selectActionTarget = TARGET_WATER; break;
        case 'target_fan':selectActionTarget = TARGET_FAN; break;
        case 'target_heat':selectActionTarget = TARGET_HEAT; break;
        case 'target_device1':selectActionTarget = TARGET_CUSTOM_DEVICE_1; break;
        case 'target_device2':selectActionTarget = TARGET_CUSTOM_DEVICE_2; break;
        case 'target_device3':selectActionTarget = TARGET_CUSTOM_DEVICE_3; break;
        case 'target_device4':selectActionTarget = TARGET_CUSTOM_DEVICE_4; break;
        case 'target_light':selectActionTarget = TARGET_LIGHT; break;
        case 'target_light_color':selectActionTarget = TARGET_LIGHT_COLOR; break;
        case 'target_light_level':selectActionTarget = TARGET_LIGHT_LEVEL; break;
        default: break;
    }
    selectActionValue = OPERATION_NO;
    //往下是设置界面的
    switch(value){
        //往下是连类型都没选的
        case 'target_none':
            $('.value_none_target').css('display','block');
            $('.value_none').css('display','none');
            $('.value_state').css('display','none');
            $('.value_color').css('display','none');
            $('.value_percent').css('display','none');
            $('#dialog_content_value_select').val('value_none_target');
        break;
        //往下是什么都没选的
        case 'target_none':
            $('.value_none_target').css('display','none');
            $('.value_none').css('display','block');
            $('.value_state').css('display','none');
            $('.value_color').css('display','none');
            $('.value_percent').css('display','none');
        break;
        //往下是只有开关的
        case 'target_temp_auto':
        case 'target_humidity_auto':
        case 'target_dirt_humdity_auto':
        case 'target_fertilization_auto':
        case 'target_water_auto':
        case 'target_fertilization':
        case 'target_water':
        case 'target_fan':
        case 'target_heat':
        case 'target_device1':
        case 'target_device2':
        case 'target_device3':
        case 'target_device4':
        case 'target_light':
            $('.value_none_target').css('display','none');
            $('.value_none').css('display','block');
            $('.value_state').css('display','block');
            $('.value_color').css('display','none');
            $('.value_percent').css('display','none');
        break;
        //往下是有亮度的
        case 'target_light_color':
            $('.value_none_target').css('display','none');
            $('.value_none').css('display','block');
            $('.value_state').css('display','none');
            $('.value_color').css('display','block');
            $('.value_percent').css('display','none');
        break;
        //往下是有颜色的
        case 'target_light_level':
            $('.value_none_target').css('display','none');
            $('.value_none').css('display','block');
            $('.value_state').css('display','none');
            $('.value_color').css('display','none');
            $('.value_percent').css('display','block');
        break;
        //往下是出bug的时候的
        default: 
            $('.value_none_target').css('display','block');
            $('.value_none').css('display','block');
            $('.value_state').css('display','none');
            $('.value_color').css('display','none');
            $('.value_percent').css('display','none');
        break;
    }
}

function onValueItemSelected(selectObj){
    value = selectObj.value;//选中的值
    switch(value){
        case 'value_none_target':
        case 'value_none':
            selectActionValue = OPERATION_NO;
            break;
        case 'value_on':
            selectActionValue = STATE_ON;
            break;
        case 'value_off':
            selectActionValue = STATE_OFF;
            break;
        case 'value_red':
            selectActionValue = COLOR_RED;
            break;
        case 'value_green':
            selectActionValue = COLOR_GREEN;
            break;
        case 'value_blue':
            selectActionValue = COLOR_BLUE;
            break;
        case 'value_yellow':
            selectActionValue = COLOR_YELLOW;
            break;
        case 'value_purple':
            selectActionValue = COLOR_PURPLE;
            break;
        case 'value_cyan':
            selectActionValue = COLOR_CYAN;
            break;
        case 'value_white':
            selectActionValue = COLOR_WHITE;
            break;
        case 'value_0':
            selectActionValue = LEVEL_LIGHT_0;
            break;
        case 'value_10':
            selectActionValue = LEVEL_LIGHT_10;
            break;
        case 'value_20':
            selectActionValue = LEVEL_LIGHT_20;
            break;
        case 'value_30':
            selectActionValue = LEVEL_LIGHT_30;
            break;
        case 'value_40':
            selectActionValue = LEVEL_LIGHT_40;
            break;
        case 'value_50':
            selectActionValue = LEVEL_LIGHT_50;
            break;
        case 'value_60':
            selectActionValue = LEVEL_LIGHT_60;
            break;
        case 'value_70':
            selectActionValue = LEVEL_LIGHT_70;
            break;
        case 'value_80':
            selectActionValue = LEVEL_LIGHT_80;
            break;
        case 'value_90':
            selectActionValue = LEVEL_LIGHT_90;
            break;
        case 'value_100':
            selectActionValue = LEVEL_LIGHT_100;
            break;
        default:
            selectActionValue = OPERATION_NO;
            break;
    }
}



var isSunday = false;
var isMonday = false;
var isTuesday = false;
var isWensday = false;
var isThusday = false;
var isFriday = false;
var isSatday = false;

function onRepeatCircleItemSelected(selectObj){
    value = selectObj.value;//选中的值
    switch(value){
        case 'target_none':
            selectCycleType = CYCLE_NO;
            $('#dialog_content_weekday').css('display','none');
            $('#dialog_content_repeat_cycle').css('display','none');
            $('#dialog_content_hour').css('display','none');
            $('#dialog_content_minute').css('display','none');
        break;
        case 'target_week':
            selectCycleType = CYCLE_WEEKDAY;
            $('#dialog_content_weekday').css('display','block');
            $('#dialog_content_repeat_cycle').css('display','none');
            $('#dialog_content_hour').css('display','inline');
            $('#dialog_content_minute').css('display','inline');
        break;
        case 'target_day':
        case 'target_hour':
        case 'target_minute':
            if (value == 'target_day') {
                selectCycleType = CYCLE_DAY;
            }else if (value == 'target_hour') {
                selectCycleType = CYCLE_HOUR;
            }else{
                selectCycleType = CYCLE_MINUTE;
            }
            $('#dialog_content_weekday').css('display','none');
            $('#dialog_content_repeat_cycle').css('display','inline');
            $('#dialog_content_hour').css('display','inline');
            $('#dialog_content_minute').css('display','inline');
        break;
        default:
            selectCycleType = CYCLE_NO;
            $('#dialog_content_weekday').css('display','none');
            $('#dialog_content_repeat_cycle').css('display','none');
            $('#dialog_content_hour').css('display','none');
            $('#dialog_content_minute').css('display','none');
        break;
    }
}

function onWeekdaysClick(self){
    var self_state = false;
    switch($(self).attr('id')){
        case 'dialog_weekday_sun':
            isSunday = !isSunday;
            self_state = isSunday;
        break;
        case 'dialog_weekday_mon':
            isMonday = !isMonday;
            self_state = isMonday;
        break;
        case 'dialog_weekday_tue':
            isTuesday = !isTuesday;
            self_state = isTuesday;
        break;
        case 'dialog_weekday_wen':
            isWensday = !isWensday;
            self_state = isWensday;
        break;
        case 'dialog_weekday_thus':
            isThusday = !isThusday;
            self_state = isThusday;
        break;
        case 'dialog_weekday_fri':
            isFriday = !isFriday;
            self_state = isFriday;
        break;
        case 'dialog_weekday_sat':
            isSatday = !isSatday;
            self_state = isSatday;
        break
        default :
            self_state = false;
        break;
    }
    if (self_state) {
        $(self).css('background-color','#5ab75d');
        $(self).css('color','#fff');
    }else{
        $(self).css('background-color','#fff');
        $(self).css('color','#000');
    }

}

/**
 *  往下是对话框的相关处理事件
 */
function onCancel(){
    // type = TYPE_NONE;
    hideDialog();
}

function showAsTempUpper(){
    type = TYPE_TEMPERATURE_UPPER_LIMIT;
    showSeekbarDialog('设置温度上限','请输入要设置的温度上限',TEMPERATURE_MAX,TEMPERATURE_MIN,temperature_upper);
}

function showAsTempLower(){
    type = TYPE_TEMPERATURE_LOWER_LIMIT;
    showSeekbarDialog('设置温度下限','请输入要设置的温度下限',TEMPERATURE_MAX,TEMPERATURE_MIN,temperature_lower);
}

function showAsTempUpperAction(){
    type = TYPE_TEMPERATURE_UPPER_ACTIONS;
    initEventDialogView(temperature_upper_action);
    currntAction = ACTION_TEMPERATURE_UPPER;
    type = TYPE_TEMPERATURE_UPPER_ACTIONS;
    showActionPickerDialog('设置温度上限执行动作','当监控的温度高于上限的时候，将会执行...');
}

function showAsTempLowerAction(){
    type = TYPE_TEMPERATURE_UPPER_ACTIONS;
    initEventDialogView(temperature_lower_action);
    currntAction = ACTION_TEMPERATURE_LOWER;
    type = TYPE_TEMPERATURE_LOWER_ACTIONS;
    showActionPickerDialog('设置温度下限执行动作','当监控的温度低于下限的时候，将会执行...');
}

function showAsHumidityUpper(){
    type = TYPE_HUMIDITY_UPPER_LIMIT;
    showSeekbarDialog('设置湿度上限','请输入要设置的湿度上限',HUMIDITY_MAX,HUMIDITY_MIN,humidity_upper);
}

function showAsHumidityLower(){
    type = TYPE_HUMIDITY_LOWER_LIMIT;
    showSeekbarDialog('设置湿度下限','请输入要设置的湿度下限',HUMIDITY_MAX,HUMIDITY_MIN,humidity_lower);
}

function showAsHumidityUpperAction(){
    type = TYPE_HUMIDITY_UPPER_ACTIONS;
    initEventDialogView(humidity_upper_action);
    currntAction = ACTION_HUMIDITY_UPPER;
    type = TYPE_HUMIDITY_UPPER_ACTIONS;
    showActionPickerDialog('设置湿度上限执行动作','当监控的湿度高于上限的时候，将会执行...');
}

function showAsHumidityLowerAction(){
    type = TYPE_HUMIDITY_LOWER_ACTIONS;
    initEventDialogView(humidity_lower_action);
    currntAction = ACTION_HUMIDITY_LOWER;
    type = TYPE_HUMIDITY_LOWER_ACTIONS;
    showActionPickerDialog('设置湿度下限执行动作','当监控的湿度低于下限的时候，将会执行...');
}

function showAsDirtHumidityUpper(){
    type = TYPE_DIRT_HUMIDITY_UPPER_LIMIT;
    showSeekbarDialog('设置土壤湿度上限','请输入要设置的土壤湿度上限',DIRT_HUMIDITY_MAX,DIRT_HUMIDITY_MIN,dirt_humidity_upper);
}

function showAsDirtHumidityLower(){
    type = TYPE_DIRT_HUMIDITY_LOWER_LIMIT;
    showSeekbarDialog('设置土壤湿度下限','请输入要设置的土壤湿度下限',DIRT_HUMIDITY_MAX,DIRT_HUMIDITY_MIN,dirt_humidity_lower);
}

function showAsDirtHumidityUpperAction(){
    type = TYPE_DIRT_HUMIDITY_UPPER_ACTIONS;
    initEventDialogView(dirt_humidity_upper_action);
    currntAction = ACTION_DIRT_HUMIDITY_UPPER;
    type = TYPE_DIRT_HUMIDITY_UPPER_ACTIONS;
    showActionPickerDialog('设置土壤湿度上限执行动作','当监控的土壤湿度高于上限的时候，将会执行...');
}

function showAsDirtHumidityLowerAction(){
    type = TYPE_DIRT_HUMIDITY_UPPER_ACTIONS;
    initEventDialogView(dirt_humidity_lower_action);
    currntAction = ACTOIN_DIRT_HUMIDITY_LOWER;
    type = TYPE_DIRT_HUMIDITY_LOWER_ACTIONS;
    showActionPickerDialog('设置土壤湿度下限执行动作','当监控的土壤湿度低于下限的时候，将会执行...');
}


/**
 *  往下是显示选择事件按钮的弹窗的逻辑
 */
var isActionCanAdd = true;  //表明添加按钮点击是否起作用
var currntAction = ACTION_NO;
var selectActionTarget = TARGET_NO; //选择的对象
var selectActionValue = OPERATION_NO;   //对象的操作
var currentEventJson = [];

function onActionAddClick(){
    if (!isActionCanAdd) {//如果数量已超出上限，则shake提示文本
        $('#dialog_content_action_pick_hint').shake(1,10,300);
        return
    }
    if (selectActionTarget == TARGET_NO) {  //如果没有选择目标
        $('#dialog_content_target_select').shake(1,10,300);
        return;
    }
    if (selectActionValue == OPERATION_NO) {    //如果没有选择值
        $('#dialog_content_value_select').shake(1,10,300);
        return;
    }
    //添加数值到JSON对象
    var tempItemJson = {'target':selectActionTarget,'operation':selectActionValue};
    currentEventJson.push(tempItemJson);
    //如果是有选择了数值的话，就添加并且清零
    selectActionTarget = TARGET_NO;
    selectActionValue = OPERATION_NO;
    $('#dialog_content_target_select').val('target_none');
    $('#dialog_content_value_select').val('value_none_target');
    initEventDialogView(currentEventJson);//添加完一条数据后刷新一遍界面
}

function initEventDialogView(eventJson){
    currentEventJson = eventJson;
    if (eventJson.length >= 5) {
        $('#dialog_content_action_pick_hint').css('display','inline');
        $('#dialog_content_action_add_btn').css('opacity','0.5');
        isActionCanAdd = false;
    }else{
        $('#dialog_content_action_pick_hint').css('display','none');
        $('#dialog_content_action_add_btn').css('opacity','1');
        isActionCanAdd = true;
    }
    var eventJsonSize = eventJson.length;
    for(var i=0;i<5;i++){
        if (i<eventJsonSize) {//如果JSON存在这个对象
            $('#dialog_list_item'+i.toString()).css('display','block');
            $('#dialog_list_text'+i.toString()).html(__getStringFromTempJson(eventJson[i]));
        }else{//如果JSON不存在这个对象
            $('#dialog_list_item'+i.toString()).css('display','none');
        }
    }
}

function actionItem1Delete(){
    currentEventJson.splice(0,1);
    initEventDialogView(currentEventJson);
}
function actionItem2Delete(){
    currentEventJson.splice(1,1);
    initEventDialogView(currentEventJson);
}
function actionItem3Delete(){
    currentEventJson.splice(2,1);
    initEventDialogView(currentEventJson);
}
function actionItem4Delete(){
    currentEventJson.splice(3,1);
    initEventDialogView(currentEventJson);
}
function actionItem5Delete(){
    currentEventJson.splice(4,1);
    initEventDialogView(currentEventJson);
}

function __getStringFromTempJson(tempJson){
    var targetStr = '';
    var oppeartionStr = '';
    switch(tempJson['target']){
        case TARGET_NO : targetStr='尚未选择目标';break;
        case TARGET_TEMPERATION_AUTO_CONTROL : targetStr='空气温度自动控制';break;
        case TARGET_HUMIDITY_AUTO_CONTROL : targetStr='空气湿度自动控制';break;
        case TARGET_DIRT_HUMIDITY_AUTO_CONTROL : targetStr='土壤湿度自动控制';break;
        case TARGET_FERTILIZATION_AUTO_CONTROL : targetStr='自动施肥开关';break;
        case TARGET_WATER_AUTO_CONTROL : targetStr='自动浇水开关';break;
        case TARGET_FERTILIZATION : targetStr='施肥';break;
        case TARGET_WATER : targetStr='浇水';break;
        case TARGET_FAN : targetStr='风扇';break;
        case TARGET_HEAT : targetStr='加热';break;
        case TARGET_CUSTOM_DEVICE_1 : targetStr='自定义设备1';break;
        case TARGET_CUSTOM_DEVICE_2 : targetStr='自定义设备2';break;
        case TARGET_CUSTOM_DEVICE_3 : targetStr='自定义设备3';break;
        case TARGET_CUSTOM_DEVICE_4 : targetStr='自定义设备4';break;
        case TARGET_LIGHT : targetStr='环境灯光开关';break;
        case TARGET_LIGHT_COLOR : targetStr='环境灯光颜色';break;
        case TARGET_LIGHT_LEVEL : targetStr='环境灯光亮度';break;
    }
    if (tempJson['target'] == TARGET_LIGHT_COLOR) {
        switch(tempJson['operation']){
            case COLOR_RED : oppeartionStr='红色';break;
            case COLOR_GREEN : oppeartionStr='绿色';break;
            case COLOR_BLUE : oppeartionStr='蓝色';break;
            case COLOR_YELLOW : oppeartionStr='黄色';break;
            case COLOR_PURPLE : oppeartionStr='紫色';break;
            case COLOR_CYAN : oppeartionStr='青色';break;
            case COLOR_WHITE : oppeartionStr='白色';break;
        }
    }else if (tempJson['target'] == TARGET_LIGHT_LEVEL) {
        switch(tempJson['operation']){
            case LEVEL_LIGHT_0 : oppeartionStr='亮度0%';break;
            case LEVEL_LIGHT_10 : oppeartionStr='亮度10%';break;
            case LEVEL_LIGHT_20 : oppeartionStr='亮度20%';break;
            case LEVEL_LIGHT_30 : oppeartionStr='亮度30%';break;
            case LEVEL_LIGHT_40 : oppeartionStr='亮度40%';break;
            case LEVEL_LIGHT_50 : oppeartionStr='亮度50%';break;
            case LEVEL_LIGHT_60 : oppeartionStr='亮度60%';break;
            case LEVEL_LIGHT_70 : oppeartionStr='亮度70%';break;
            case LEVEL_LIGHT_80 : oppeartionStr='亮度80%';break;
            case LEVEL_LIGHT_90 : oppeartionStr='亮度90%';break;
            case LEVEL_LIGHT_100 : oppeartionStr='亮度100%';break;
        }
    }else{
        switch(tempJson['operation']){
            case OPERATION_NO : oppeartionStr='无操作';break;
            case STATE_ON : oppeartionStr='打开';break;
            case STATE_OFF : oppeartionStr='关闭';break;
        }
    }
    return targetStr + '  ->  ' + oppeartionStr;
}


/**
 *  往下是其他，还没整理
 */

function showAsAutoFertilizationDialog(){
    type = TYPE_FERTILIZATION_CIRCLE;
    initDialogCircle(fertilization_cycle);
    showCirclePickerDialog('自动施肥周期','设置自动施肥周期');
}

function showAsAutoWaterDialog(){
    type = TYPE_WATER_CIRCLE;
    initDialogCircle(water_cycle);
    //显示对话框
    showCirclePickerDialog('自动浇水周期','设置自动浇水周期');
}

function initDialogCircle(jsonObject){
    var weekdayArray = new Array();
    //初始化显示内容
    switch(jsonObject['repeat_type']){
        case CYCLE_NO : 
            $('#dialog_content_cycle_select').val('target_none');
            $('#dialog_content_weekday').css('display','none');
            $('#dialog_content_repeat_cycle').css('display','none');
            $('#dialog_content_hour').css('display','none');
            $('#dialog_content_minute').css('display','none');
            break;
        case CYCLE_WEEKDAY : 
            $('#dialog_content_cycle_select').val('target_week');
            $('#dialog_content_weekday').css('display','inline');
            $('#dialog_content_repeat_cycle').css('display','none');
            $('#dialog_content_hour').css('display','inline');
            $('#dialog_content_minute').css('display','inline');
            break;
        case CYCLE_DAY:
        case CYCLE_HOUR:
        case CYCLE_MINUTE:
            if (jsonObject['repeat_type'] == CYCLE_DAY) {
                $('#dialog_content_cycle_select').val('target_day');
            }else if (jsonObject['repeat_type'] == CYCLE_HOUR) {
                $('#dialog_content_cycle_select').val('target_hour');
            }else if (jsonObject['repeat_type'] == CYCLE_MINUTE) {
                $('#dialog_content_cycle_select').val('target_minute');
            }
            $('#dialog_content_weekday').css('display','none');
            $('#dialog_content_repeat_cycle').css('display','inline');
            $('#dialog_content_hour').css('display','inline');
            $('#dialog_content_minute').css('display','inline');
            break;
    }
    //初始化参数
    if (parseInt(jsonObject['repeat_type']) == CYCLE_WEEKDAY) {    //是星期的处理结果
        weekdayArray = jsonObject['repeat_circle'].split('');
        isSunday  = ( parseInt(weekdayArray[0]) != 0 );
        isMonday  = ( parseInt(weekdayArray[1]) != 0 );
        isTuesday = ( parseInt(weekdayArray[2]) != 0 );
        isWensday = ( parseInt(weekdayArray[3]) != 0 );
        isThusday = ( parseInt(weekdayArray[4]) != 0 );
        isFriday  = ( parseInt(weekdayArray[5]) != 0 );
        isSatday  = ( parseInt(weekdayArray[6]) != 0 );
    }else{  //不是星期的处理结果
        $('#dialog_content_repeat_cycle').val(jsonObject['repeat_circle']);
        isSunday = isMonday = isTuesday = isWensday = isThusday = isFriday = isSatday = false;
    }
    console.log('weekday circle : ' + jsonObject['repeat_circle']);
    console.log('weekday array : ' + weekdayArray);
    console.log('标志位 '+isSunday+'  '+isMonday+'  '+isThusday+'  '+isWensday+'  '+isThusday+'  '+isFriday+'  '+isSatday)
    var idArray = new Array(
        '#dialog_weekday_sun',
        '#dialog_weekday_mon',
        '#dialog_weekday_tue',
        '#dialog_weekday_wen',
        '#dialog_weekday_thus',
        '#dialog_weekday_fri',
        '#dialog_weekday_sat',
    );
    var isActiveFlagArray = new Array(isSunday,isMonday,isTuesday,isWensday,isThusday,isFriday,isSatday);
    for (var i = isActiveFlagArray.length - 1; i >= 0; i--) {
        if (isActiveFlagArray[i]) {
            $(idArray[i]).css('color','#fff');
            $(idArray[i]).css('background-color','#5ab75d');
        }else{
            $(idArray[i]).css('color','#000');
            $(idArray[i]).css('background-color','#fff');
        }
    }
    $('#dialog_content_hour').val(jsonObject['hour']);
    $('#dialog_content_minute').val(jsonObject['minute']);
}

function refreshSeekbarHintText(progress){
    var str_hint = '';
    // var progress = $('#ex1').data('slider').getValue();
    switch(type){
        case TYPE_TEMPERATURE_UPPER_LIMIT : {str_hint='温度上限'+progress+'℃';break;}
        case TYPE_TEMPERATURE_LOWER_LIMIT : {str_hint='温度下限'+progress+'℃';break;}
        case TYPE_HUMIDITY_UPPER_LIMIT : {str_hint='空气湿度上限'+progress+'%';break;}
        case TYPE_HUMIDITY_LOWER_LIMIT : {str_hint='空气湿度下限'+progress+'%';break;}
        case TYPE_DIRT_HUMIDITY_UPPER_LIMIT : {str_hint='土壤湿度上限'+progress+'%';break;}
        case TYPE_DIRT_HUMIDITY_LOWER_LIMIT : {str_hint='土壤湿度下限'+progress+'%';break;}
    }
    $('#dialog_content_seekbar_hint').html(str_hint);
}

function showSimpleDialog(){
    showDialog();
}

function showHintDialog(title,hint){
    $('#dialog_title').css('display','block');
    $('#dialog_content_hint_p').css('display','block');
    $('#dialog_content_hint').css('display','none');
    $('#dialog_content_cycle_pick').css('display','none');
    $('#dialog_content_seekbar_div').css('display','block')
    $('#dialog_content_action').css('display','none');
    $('#dialog_content_action_pick_div').css('display','none');
    $('#dialog_content_button_hr').css('display','none');
    $('#dialog_content_button').css('display','none');
    $('#dialog_title').html(title);
    $('#dialog_content_hint_p').html(hint);
}

function showSeekbarDialog(title,hint,seekarMax,seekbarMin,seekbarProgress){
    $('#dialog_title').css('display','block');
    $('#dialog_content_hint_p').css('display','none');
    $('#dialog_content_hint').css('display','none');
    $('#dialog_content_cycle_pick').css('display','none');
    $('#dialog_content_seekbar_div').css('display','block')
    $('#dialog_content_action').css('display','none');
    $('#dialog_content_action_pick_div').css('display','none');
    $('#dialog_content_button_hr').css('display','block');
    $('#dialog_content_button').css('display','block');
    $('#dialog_title').html(title);
    $('#ex1').data('slider').setAttribute('max',seekarMax);
    $('#ex1').data('slider').setAttribute('min',seekbarMin);
    $('#ex1').data('slider').setValue(seekbarProgress);
    showDialog();
}

function showActionPickerDialog(title,hint){
    if (!hint) {hint=''}
    $('#dialog_content_hint').css('display','block');
    $('#dialog_title').css('display','block');
    $('#dialog_content_hint').css('display','none');
    $('#dialog_content_seekbar_div').css('display','none')
    $('#dialog_content_cycle_pick').css('display','none');
    $('#dialog_content_action').css('display','none');
    $('#dialog_content_action_pick_div').css('display','block');
    $('#dialog_content_button_hr').css('display','block');
    $('#dialog_content_button').css('display','block');
    if(hint==''){
        $('#dialog_content_hint').css('display','none');
    }else{
        $('#dialog_content_hint_p').css('display','block');
        $('#dialog_content_hint_p').html(hint);
    }
    $('#dialog_title').html(title);
    showDialog();
}

function showCirclePickerDialog(title,hint){
    if (!hint) {hint=''}
    $('#dialog_content_hint').css('display','block');
    $('#dialog_title').css('display','block');
    $('#dialog_content_hint').css('display','none');
    $('#dialog_content_seekbar_div').css('display','none')
    $('#dialog_content_cycle_pick').css('display','block');
    $('#dialog_content_action').css('display','none');
    $('#dialog_content_action_pick_div').css('display','none');
    $('#dialog_content_button_hr').css('display','block');
    $('#dialog_content_button').css('display','block');
    if(hint==''){
        $('#dialog_content_hint').css('display','none');
    }else{
        $('#dialog_content_hint_p').css('display','block');
        $('#dialog_content_hint_p').html(hint);
    }
    $('#dialog_title').html(title);
    showDialog();
}