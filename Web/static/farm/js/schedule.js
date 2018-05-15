const CLASS_STATE_CHECKED 	= 'schedule_circle_state_check'
const CLASS_STATE_UNCHECKED = 'schedule_circle_state_uncheck'

const CLASS_NONE_TARGET		= 'value_none_target'
const CLASS_NONE			= 'value_none'
const CLASS_VALUE_STATE		= 'value_state'
const CLASS_VALUE_COLOR		= 'value_color'
const CLASS_VALUE_PERCENT	= 'value_percent'

const ID_REPEAT_TYPE_NO		= 'repeatTypeNo'
const ID_REPEAT_TYPE_DAY	= 'repeatTypeDay'
const ID_REPEAT_TYPE_WEEK	= 'repeatTypeWeek'

const ID_WEEK_SUN			= 'weekdaySun'
const ID_WEEK_MON			= 'weekdayMon'
const ID_WEEK_TUE			= 'weekdayTue'
const ID_WEEK_WEN			= 'weekdayWen'
const ID_WEEK_THU			= 'weekdayThu'
const ID_WEEK_FRI			= 'weekdayFri'
const ID_WEEK_SAT			= 'weekdaySat'

const ID_ITEM_VALUE 		= 'dialog_content_value_select'

const ID_CIRCLE_DIV			= 'dialog_circle_div'
const ID_WEEKDAY_DIV		= 'dialog_weekday_div'

const VALUE_TARGET_NONE		= 'target_none'
const VALUE_TARGET_TEMP_AUTO	= 'target_temp_auto'
const VALUE_TARGET_HUMIDITY_AUTO		= 'target_humidity_auto'
const VALUE_TARGET_DIRT_HUMIDITY_AUTO	= 'target_dirt_humdity_auto'
const VALUE_TARGET_FERTILIZED_AUTO		= 'target_fertilization_auto'
const VALUE_TARGET_WATER_AUTO	= 'target_water_auto'
const VALUE_TARGET_FERTILIZED	= 'target_fertilization'
const VALUE_TARGET_WATER		= 'target_water'
const VALUE_TARGET_FAN			= 'target_fan'
const VALUE_TARGET_DEVICE1		= 'target_device1'
const VALUE_TARGET_DEVICE2		= 'target_device2'
const VALUE_TARGET_DEVICE3		= 'target_device3'
const VALUE_TARGET_DEVICE4		= 'target_device4'
const VALUE_TARGET_LIGHT		= 'target_light'
const VALUE_TARGET_LIGHT_COLOR	= 'target_light_color'
const VALUE_TARGET_LIGHT_LEVEL	= 'target_light_level'

const VALUE_VALUE_NO_TARGET	= 'value_none_target'
const VALUE_VALUE_NONE			= 'value_none'
const VALUE_VALUE_ON			= 'value_on'
const VALUE_VALUE_OFF			= 'value_off'
const VALUE_VALUE_RED			= 'value_red'
const VALUE_VALUE_GREEN		= 'value_green'
const VALUE_VALUE_BLUE			= 'value_blue'
const VALUE_VALUE_YELLOW		= 'value_yellow'
const VALUE_VALUE_PURPLE		= 'value_purple'
const VALUE_VALUE_CYAN			= 'value_cyan'
const VALUE_VALUE_WHITE		= 'value_white'
const VALUE_VALUE_0			= 'value_0'
const VALUE_VALUE_10			= 'value_10'
const VALUE_VALUE_20			= 'value_20'
const VALUE_VALUE_30			= 'value_30'
const VALUE_VALUE_40			= 'value_40'
const VALUE_VALUE_50			= 'value_50'
const VALUE_VALUE_60			= 'value_60'
const VALUE_VALUE_70			= 'value_70'
const VALUE_VALUE_80			= 'value_80'
const VALUE_VALUE_90			= 'value_90'
const VALUE_VALUE_100			= 'value_100'

const REPEAT_TYPE_NO_REPEAT	= 0
const REPEAT_TYPE_DAY		= 1
const REPEAT_TYPE_WEEKDAY	= 2

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

var OPERATION_TYPE_ADD 	= '1'
var OPERATION_TYPE_EDIT = '2'
var OPERATION_TYPE_DEL 	= '3'

/**
  *	往下定义的是对话框的信息
  */

var selectedWeekday = '0000000';	//
var selectedRepeatType = REPEAT_TYPE_NO_REPEAT;
var selectedTarget = TARGET_NO; 
var selectedAction = OPERATION_NO;
var selectedOpeartion = OPERATION_TYPE_ADD;

var editScheduleName = 'undefine'

/**
 *	往下是事件回调函数
 */

 function onSwitchChange(scheduleName,self,scheduleList){
 	var editSchedule = null;
 	var scheduleJsonObj = $.parseJSON(scheduleList)
 	for(var i = 0;i<scheduleJsonObj.data.length;i++){
		if (scheduleJsonObj.data[i].name == scheduleName) {
			editSchedule = scheduleJsonObj.data[i]
			break;
		}
	}
	if (editSchedule == null) {
		alert('找不到对应的定时数据，请刷新重试')
		return;
	}
 	var sendJson = {
			'action':OPERATION_TYPE_EDIT,
			'name':editSchedule.name,
			'repeat_type':editSchedule.repeat_type,
			'repeat_value':editSchedule.repeat_value,
			'hour':editSchedule.hour,
			'minute':editSchedule.minute,
			'target':editSchedule.target,
			'value':editSchedule.value,
			'is_active':$(self).prop('checked')
		}
	log(sendJson)
	//如果是编辑的话，还得把旧的定时的名称也一起发送过去
	sendJson['old_name'] = scheduleName;
	//发送请求
	ajaxPost(URL_SCHEDULE,
		sendJson,
		function(){
			location.reload();
		},
		function(){
			alert('添加定时失败，请检查您的网络连接')
		})
 }

function onRepeatTypeClick(self){
	switch(self.id){
		case ID_REPEAT_TYPE_DAY : {
			selectedRepeatType = REPEAT_TYPE_DAY;
			selectedWeekday = '0'
			break;
		}
		case ID_REPEAT_TYPE_WEEK : {
			selectedRepeatType = REPEAT_TYPE_WEEKDAY
			selectedWeekday = '0000000'
			break;
		}
		case ID_REPEAT_TYPE_NO :
		default : {
			selectedRepeatType = REPEAT_TYPE_NO_REPEAT;
			selectedWeekday = '0'
			break;
		}
	}
	$('#dialog_circle_input').val(0)
	refreshRepeatType();
	refreshSelectWeekday()
}

function onWeekdayClick(self){	//写到这里了！！！！！！！！！！！！！！！！！！！
	if (selectedWeekday.length < 7) {
		selectedWeekday = '0000000'
	}
	switch(self.id){
		case ID_WEEK_MON : {
			toggleStateStr(1);
			break;
		}
		case ID_WEEK_TUE : {
			toggleStateStr(2);
			break;
		}
		case ID_WEEK_WEN : {
			toggleStateStr(3);
			break;
		}
		case ID_WEEK_THU : {
			toggleStateStr(4);
			break;
		}
		case ID_WEEK_FRI : {
			toggleStateStr(5);
			break;
		}
		case ID_WEEK_SAT : {
			toggleStateStr(6);
			break;
		}
		case ID_WEEK_SUN : 
		default :{
			toggleStateStr(0);
			break;
		}
	}
	refreshSelectWeekday()
}

function onTypeItemSelected(self){
	switch(self.value){
		case VALUE_TARGET_TEMP_AUTO : {
			showActionTypeAsState();
			selectedTarget = TARGET_TEMPERATION_AUTO_CONTROL;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_HUMIDITY_AUTO : {
			showActionTypeAsState();
			selectedTarget = TARGET_HUMIDITY_AUTO_CONTROL;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_DIRT_HUMIDITY_AUTO : {
			showActionTypeAsState();
			selectedTarget = TARGET_DIRT_HUMIDITY_AUTO_CONTROL;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_FERTILIZED_AUTO : {
			showActionTypeAsState();
			selectedTarget = TARGET_FERTILIZATION_AUTO_CONTROL;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_WATER_AUTO : {
			showActionTypeAsState();
			selectedTarget = TARGET_WATER_AUTO_CONTROL;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_FERTILIZED : {
			showActionTypeAsState();
			selectedTarget = TARGET_FERTILIZATION;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_WATER : {
			showActionTypeAsState();
			selectedTarget = TARGET_WATER;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_FAN : {
			showActionTypeAsState();
			selectedTarget = TARGET_FAN;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_DEVICE1 : {
			showActionTypeAsState();
			selectedTarget = TARGET_CUSTOM_DEVICE_1;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_DEVICE2 : {
			showActionTypeAsState();
			selectedTarget = TARGET_CUSTOM_DEVICE_2;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_DEVICE3 : {
			showActionTypeAsState();
			selectedTarget = TARGET_CUSTOM_DEVICE_3;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_DEVICE4 : {
			showActionTypeAsState();
			selectedTarget = TARGET_CUSTOM_DEVICE_4;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_LIGHT : {
			showActionTypeAsState();
			selectedTarget = TARGET_LIGHT;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_LIGHT_COLOR : {
			showActionTypeAsColor();
			selectedTarget = TARGET_LIGHT_COLOR;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_LIGHT_LEVEL : {
			showActionTypeAsPercent();
			selectedTarget = TARGET_LIGHT_LEVEL;
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_TARGET_NONE : 
		default : {
			showActionTypeAsSelectTarget();
			selectedTarget = TARGET_NO;
			selectedAction = OPERATION_NO;
			break;
		}
	}
}

function onValueItemSelected(self){
	switch(self.value){
		case VALUE_VALUE_NONE : {
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_VALUE_NO_TARGET : {
			selectedAction = OPERATION_NO;
			break;
		}
		case VALUE_VALUE_ON : {
			selectedAction = STATE_ON;
			break;
		}
		case VALUE_VALUE_OFF : {
			selectedAction = STATE_OFF;
			break;
		}
		case VALUE_VALUE_RED : {
			selectedAction = COLOR_RED;
			break;
		}
		case VALUE_VALUE_GREEN : {
			selectedAction = VALUE_VALUE_GREEN;
			break;
		}
		case VALUE_VALUE_BLUE : {
			selectedAction = COLOR_BLUE;
			break;
		}
		case VALUE_VALUE_YELLOW : {
			selectedAction = COLOR_YELLOW;
			break;
		}
		case VALUE_VALUE_PURPLE	: {
			selectedAction = COLOR_PURPLE;
			break;
		}
		case VALUE_VALUE_CYAN : {
			selectedAction = COLOR_CYAN;
			break;
		}
		case VALUE_VALUE_WHITE : {
			selectedAction = COLOR_WHITE;
			break;
		}
		case VALUE_VALUE_0 : {
			selectedAction = LEVEL_LIGHT_0;
			break;
		}
		case VALUE_VALUE_10 : {
			selectedAction = LEVEL_LIGHT_10;
			break;
		}
		case VALUE_VALUE_20 : {
			selectedAction = LEVEL_LIGHT_20;
			break;
		}
		case VALUE_VALUE_30 : {
			selectedAction = LEVEL_LIGHT_30;
			break;
		}
		case VALUE_VALUE_40	 : {
			selectedAction = LEVEL_LIGHT_40;
			break;
		}
		case VALUE_VALUE_50 : {
			selectedAction = LEVEL_LIGHT_50;
			break;
		}
		case VALUE_VALUE_60 : {
			selectedAction = LEVEL_LIGHT_60;
			break;
		}
		case VALUE_VALUE_70 : {
			selectedAction = LEVEL_LIGHT_70;
			break;
		}
		case VALUE_VALUE_80 : {
			selectedAction = LEVEL_LIGHT_80;
			break;
		}
		case VALUE_VALUE_90	 : {
			selectedAction = LEVEL_LIGHT_90;
			break;
		}
		case VALUE_VALUE_100 : {
			selectedAction = LEVEL_LIGHT_100;
			break;
		}
	}
}

URL_SCHEDULE = '../../api/schedule/'
function onConfirm(){
	var scheduleName = $('#dialog_username_input').val();	//定时名称
	var scheduleRepeatType = selectedRepeatType;
	var scheduleRepeatValue = '0'
	var scheduleHour = $('#dialog_hour_input').val();
	var scheduleMinute = $('#dialog_minute_input').val();
	var scheduleCircle = $('#dialog_circle_input').val();
	var scheduleTarget = selectedTarget;
	var scheduleValue = selectedAction;
	var scheduleIsActive = $('#dialog_is_active').is(':checked')
	//下面是数值检查
	if (scheduleName == '') {
		$('#dialog_username_div').shake(1,10,300);
		return;
	}
	if (!isRealNum(scheduleHour) || scheduleHour < 0 || scheduleHour > 23) {
		$('#dialog_hour_div').shake(1,10,300);
		return;
	}
	if (!isRealNum(scheduleMinute) || scheduleMinute < 0 || scheduleMinute >  59) {
		$('#dialog_minute_div').shake(1,10,300);
		return;
	}
	if (scheduleTarget == TARGET_NO) {
		$('#dialog_content_action_pick_div').shake(1,10,300);
		return;
	}
	if (scheduleValue == VALUE_TARGET_NONE || scheduleValue == VALUE_VALUE_NONE) {
		$('#dialog_content_value_select').shake(1,10,300);
		return;
	}
	//判断重复类型
	switch(scheduleRepeatType){
		case REPEAT_TYPE_WEEKDAY : {
			scheduleRepeatValue = selectedWeekday;
			break;
		}
		case REPEAT_TYPE_DAY : {
			if (!isRealNum(scheduleCircle) || scheduleCircle < 0 || scheduleCircle > 99999) {
				$('#dialog_circle_div').shake(1,10,300);
				return;
			}
			scheduleRepeatValue = scheduleCircle
			break;
		}
		case REPEAT_TYPE_NO_REPEAT : {
			scheduleRepeatValue = '0'
			break;
		}
		default : {
			location.reload();
			return;
		}
	}
	//发送请求
	var sendJson = {
			'action':selectedOpeartion,
			'name':scheduleName,
			'repeat_type':scheduleRepeatType,
			'repeat_value':scheduleRepeatValue,
			'hour':scheduleHour,
			'minute':scheduleMinute,
			'target':scheduleTarget,
			'value':scheduleValue,
			'is_active':scheduleIsActive
		}
	//如果是编辑的话，还得把旧的定时的名称也一起发送过去
	sendJson['old_name'] = editScheduleName;
	//发送请求
	ajaxPost(URL_SCHEDULE,
		sendJson,
		function(){
			location.reload();
		},
		function(){
			alert('添加定时失败，请检查您的网络连接')
		})
	//隐藏对话
	hideDialog();
}

function onCancel(){
	hideDialog();
}

function onDelete(){
	selectedOpeartion = OPERATION_TYPE_DEL;
	var sendJson = {
		'action' : selectedOpeartion,
		'name' : editScheduleName
	}
	ajaxPost(URL_SCHEDULE,
		sendJson,
		function(){
			location.reload();
		},
		function(){
			alert('删除定时失败，请检查您的网络连接')
		})
	hideDialog();
}

/**
 *	往下是界面的操作
 */

function showEditDialog(scheduleList,scheduleName){
	$('#dialog_title').html('编辑定时');
	$('#dialog_content_delete').css('display','block');
	selectedOpeartion = OPERATION_TYPE_EDIT;
	//获取对象
	var editSchedule = null
	scheduleJsonObj = $.parseJSON(scheduleList)
	for(var i = 0;i<scheduleJsonObj.data.length;i++){
		if (scheduleJsonObj.data[i].name == scheduleName) {
			editSchedule = scheduleJsonObj.data[i]
			editScheduleName = scheduleName
			break;
		}
	}
	if (editSchedule == null) {
		showAddDialog();
		return
	}
	//装载数据
	$('#dialog_username_input').val(editSchedule.name);//名称
	selectedRepeatType = editSchedule.repeat_type;
	selectedWeekday = editSchedule.repeat_value;
	log('selectedWeekday => '+selectedWeekday+'\nselectedRepeatType => '+selectedRepeatType)
	$('#dialog_circle_input').val(editSchedule.repeat_value);
	$('#dialog_hour_input').val(editSchedule.hour);
	$('#dialog_minute_input').val(editSchedule.minute);
	$('#dialog_is_active').bootstrapSwitch('state',editSchedule.is_active == 'true');
	switch(editSchedule.repeat_type){
		case '1' : {
			selectedRepeatType = REPEAT_TYPE_DAY;
			break;
		}
		case '2' : {
			selectedRepeatType = REPEAT_TYPE_WEEKDAY;
			break;
		}
		case '0' : 
		default : {
			selectedRepeatType = REPEAT_TYPE_NO_REPEAT;
			break;
		}
	}
	switch(parseInt(editSchedule.target)){
		case TARGET_NO:{
			$('#dialog_content_target_select').val('target_none');
			break;
		}
		case TARGET_TEMPERATION_AUTO_CONTROL:{
			$('#dialog_content_target_select').val('target_temp_auto');
			break;
		}
		case TARGET_HUMIDITY_AUTO_CONTROL:{
			$('#dialog_content_target_select').val('target_humidity_auto');
			break;
		}
		case TARGET_DIRT_HUMIDITY_AUTO_CONTROL:{
			$('#dialog_content_target_select').val('target_dirt_humdity_auto');
			break;
		}
		case TARGET_FERTILIZATION_AUTO_CONTROL:{
			$('#dialog_content_target_select').val('target_fertilization_auto');
			break;
		}
		case TARGET_WATER_AUTO_CONTROL:{
			$('#dialog_content_target_select').val('target_water_auto');
			break;
		}
		case TARGET_FERTILIZATION:{
			$('#dialog_content_target_select').val('target_fertilization');
			break;
		}
		case TARGET_WATER:{
			$('#dialog_content_target_select').val('target_water');
			break;
		}
		case TARGET_FAN:{
			$('#dialog_content_target_select').val('target_fan');
			break;
		}
		case TARGET_HEAT:{
			$('#dialog_content_target_select').val('target_heat');
			break;
		}
		case TARGET_CUSTOM_DEVICE_1:{
			$('#dialog_content_target_select').val('target_device1');
			break;
		}
		case TARGET_CUSTOM_DEVICE_2:{
			$('#dialog_content_target_select').val('target_device2');
			break;
		}
		case TARGET_CUSTOM_DEVICE_3:{
			$('#dialog_content_target_select').val('target_device3');
			break;
		}
		case TARGET_CUSTOM_DEVICE_4:{
			$('#dialog_content_target_select').val('target_device4');
			break;
		}
		case TARGET_LIGHT:{
			$('#dialog_content_target_select').val('target_light');
			break;
		}
		case TARGET_LIGHT_COLOR:{
			$('#dialog_content_target_select').val('target_light_color');
			break;
		}
		case TARGET_LIGHT_LEVEL:{
			$('#dialog_content_target_select').val('target_light_level');
			break;
		}
		default : {
			alert('定时的目标配置异常 => '+editSchedule.target)
			break;
		}
	}
	onTypeItemSelected(document.getElementById('dialog_content_target_select'));
	switch(parseInt(editSchedule.target)){
		case TARGET_NO:
		case TARGET_TEMPERATION_AUTO_CONTROL:
		case TARGET_HUMIDITY_AUTO_CONTROL:
		case TARGET_DIRT_HUMIDITY_AUTO_CONTROL:
		case TARGET_FERTILIZATION_AUTO_CONTROL:
		case TARGET_WATER_AUTO_CONTROL:
		case TARGET_FERTILIZATION:
		case TARGET_WATER:
		case TARGET_FAN:
		case TARGET_HEAT:
		case TARGET_CUSTOM_DEVICE_1:
		case TARGET_CUSTOM_DEVICE_2:
		case TARGET_CUSTOM_DEVICE_3:
		case TARGET_CUSTOM_DEVICE_4:
		case TARGET_LIGHT:{
			switch(parseInt(editSchedule.value)){
				case STATE_ON:  	{$('#dialog_content_value_select').val('value_on');break;}
				case STATE_OFF: 	{$('#dialog_content_value_select').val('value_off');break;}
				default :{
					$('#dialog_content_value_select').val('value_none');
					alert('定时的目标值配置异常 => '+editSchedule.value);break;
				}
			}
			break;
		}
		case TARGET_LIGHT_COLOR:{
			switch(parseInt(editSchedule.value)){
				case COLOR_RED: 	{$('#dialog_content_value_select').val('value_red');break;}
				case COLOR_GREEN: 	{$('#dialog_content_value_select').val('value_green');break;}
				case COLOR_BLUE: 	{$('#dialog_content_value_select').val('value_blue');break;}
				case COLOR_YELLOW: 	{$('#dialog_content_value_select').val('value_yellow');break;}
				case COLOR_PURPLE: 	{$('#dialog_content_value_select').val('value_purple');break;}
				case COLOR_CYAN: 	{$('#dialog_content_value_select').val('value_cyan');break;}
				case COLOR_WHITE: 	{$('#dialog_content_value_select').val('value_white');break;}
				default :{
					$('#dialog_content_value_select').val('value_none');
					alert('定时的目标值配置异常 => '+editSchedule.value);break;
				}
			}
			break;
		}
		case TARGET_LIGHT_LEVEL:{
			switch(parseInt(editSchedule.value)){
				case LEVEL_LIGHT_0: 	{$('#dialog_content_value_select').val('value_0');break;}
				case LEVEL_LIGHT_10:	{$('#dialog_content_value_select').val('value_10');break;}
				case LEVEL_LIGHT_20:	{$('#dialog_content_value_select').val('value_20');break;}
				case LEVEL_LIGHT_30:	{$('#dialog_content_value_select').val('value_30');break;}
				case LEVEL_LIGHT_40:	{$('#dialog_content_value_select').val('value_40');break;}
				case LEVEL_LIGHT_50:	{$('#dialog_content_value_select').val('value_50');break;}
				case LEVEL_LIGHT_60:	{$('#dialog_content_value_select').val('value_60');break;}
				case LEVEL_LIGHT_70:	{$('#dialog_content_value_select').val('value_70');break;}
				case LEVEL_LIGHT_80:	{$('#dialog_content_value_select').val('value_80');break;}
				case LEVEL_LIGHT_90:	{$('#dialog_content_value_select').val('value_90');break;}
				case LEVEL_LIGHT_100: 	{$('#dialog_content_value_select').val('value_100');break;}
				default :{
					$('#dialog_content_value_select').val('value_none');
					alert('定时的目标值配置异常 => '+editSchedule.value);break;
				}
			}
			break;
		}
		default : {
			$('#dialog_content_target_select').val('target_none');
			alert('定时的目标配置异常 => '+editSchedule.target)
			break;
		}
	}
	selectedAction = editSchedule.value
	//刷新
	refreshRepeatType();
	refreshSelectWeekday();
	showDialog();
}

function showAddDialog(){
	$('#dialog_title').html('添加定时');
	$('#dialog_content_delete').css('display','none');
	selectedTarget = TARGET_NO;
	selectedAction = VALUE_VALUE_NO_TARGET;
	selectedOpeartion = OPERATION_TYPE_ADD;
	//装载数据
	$('#dialog_username_input').val('');//名称
	selectedRepeatType = REPEAT_TYPE_NO_REPEAT;
	selectedWeekday = '0'
	$('#dialog_circle_input').val('')
	$('#dialog_hour_input').val('')
	$('#dialog_minute_input').val('')
	$('#dialog_content_target_select').val('target_none');
	$('#dialog_content_value_select').val(VALUE_VALUE_NO_TARGET);
	//刷新
	refreshRepeatType();
	refreshSelectWeekday();
	showActionTypeAsNone();
	showDialog();
}

function refreshRepeatType(){
	switch(selectedRepeatType){
		case REPEAT_TYPE_WEEKDAY : {
			setElementCheckState(ID_REPEAT_TYPE_WEEK,true);
			setElementCheckState(ID_REPEAT_TYPE_DAY,false);
			setElementCheckState(ID_REPEAT_TYPE_NO,false);
			$('#'+ID_CIRCLE_DIV).css('display','none');
			$('#'+ID_WEEKDAY_DIV).css('display','block');
			break;
		}
		case REPEAT_TYPE_DAY : {
			setElementCheckState(ID_REPEAT_TYPE_WEEK,false);
			setElementCheckState(ID_REPEAT_TYPE_DAY,true);
			setElementCheckState(ID_REPEAT_TYPE_NO,false);
			$('#'+ID_CIRCLE_DIV).css('display','block');
			$('#'+ID_WEEKDAY_DIV).css('display','none');
			break;
		}
		case REPEAT_TYPE_NO_REPEAT : 
		default : {
			setElementCheckState(ID_REPEAT_TYPE_WEEK,false);
			setElementCheckState(ID_REPEAT_TYPE_DAY,false);
			setElementCheckState(ID_REPEAT_TYPE_NO,true);
			$('#'+ID_CIRCLE_DIV).css('display','none');
			$('#'+ID_WEEKDAY_DIV).css('display','none');
		}
	}
}

const LIST_ID_WEEKDAY = new Array(ID_WEEK_SUN,ID_WEEK_MON,ID_WEEK_TUE,ID_WEEK_WEN,ID_WEEK_THU,ID_WEEK_FRI,ID_WEEK_SAT);
function refreshSelectWeekday(){
	for(var i=0;i<selectedWeekday.length;i++){
		setElementCheckState(LIST_ID_WEEKDAY[i],selectedWeekday[i] != '0')
	}
}

function showActionTypeAsSelectTarget(){
	$('.'+CLASS_NONE_TARGET).css('display','block');
	$('.'+CLASS_NONE).css('display','none');
	$('.'+CLASS_VALUE_STATE).css('display','none');
	$('.'+CLASS_VALUE_COLOR).css('display','none');
	$('.'+CLASS_VALUE_PERCENT).css('display','none');
	$('#'+ID_ITEM_VALUE).val(VALUE_VALUE_NO_TARGET);
}

function showActionTypeAsNone(){
	$('.'+CLASS_NONE_TARGET).css('display','none');
	$('.'+CLASS_NONE).css('display','block');
	$('.'+CLASS_VALUE_STATE).css('display','none');
	$('.'+CLASS_VALUE_COLOR).css('display','none');
	$('.'+CLASS_VALUE_PERCENT).css('display','none');
	$('#'+ID_ITEM_VALUE).val(VALUE_VALUE_NONE);
}

function showActionTypeAsState(){
	$('.'+CLASS_NONE_TARGET).css('display','none');
	$('.'+CLASS_NONE).css('display','block');
	$('.'+CLASS_VALUE_STATE).css('display','block');
	$('.'+CLASS_VALUE_COLOR).css('display','none');
	$('.'+CLASS_VALUE_PERCENT).css('display','none');
	$('#'+ID_ITEM_VALUE).val(VALUE_VALUE_NONE);
}

function showActionTypeAsColor(){
	$('.'+CLASS_NONE_TARGET).css('display','none');
	$('.'+CLASS_NONE).css('display','block');
	$('.'+CLASS_VALUE_STATE).css('display','none');
	$('.'+CLASS_VALUE_COLOR).css('display','block');
	$('.'+CLASS_VALUE_PERCENT).css('display','none');
	$('#'+ID_ITEM_VALUE).val(VALUE_VALUE_NONE);
}

function showActionTypeAsPercent(){
	$('.'+CLASS_NONE_TARGET).css('display','none');
	$('.'+CLASS_NONE).css('display','block');
	$('.'+CLASS_VALUE_STATE).css('display','none');
	$('.'+CLASS_VALUE_COLOR).css('display','none');
	$('.'+CLASS_VALUE_PERCENT).css('display','block');
	$('#'+ID_ITEM_VALUE).val(VALUE_VALUE_NONE);
}

/**
 *	快捷操作
 */
function setElementCheckState(elementID,state){
	var tempJQueryName = '#'+elementID;
	if (state) {
		$(tempJQueryName).removeClass(CLASS_STATE_UNCHECKED)
		$(tempJQueryName).addClass(CLASS_STATE_CHECKED)
	}else{
		$(tempJQueryName).removeClass(CLASS_STATE_CHECKED)
		$(tempJQueryName).addClass(CLASS_STATE_UNCHECKED)
	}
}

function toggleStateStr(pos){
	var selectPos = selectedWeekday[pos];
	if (selectPos == '0') {
		selectPos = '1';
	}else{
		selectPos = '0';
	}
	var startStr = selectedWeekday.slice(0,pos);
	var endStr = selectedWeekday.slice(pos+1,selectedWeekday.length);
	selectedWeekday = startStr+selectPos+endStr;
}

function isRealNum(val){
    // isNaN()函数 把空串 空格 以及NUll 按照0来处理 所以先去除
    if(val === "" || val ==null){
        return false;
    }
    if(!isNaN(val)){
        return true;
    }else{
        return false;
    }
} 

function log(str){
	console.log(str);
}