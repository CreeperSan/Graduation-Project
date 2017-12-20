var TYPE_PICK_LIGHT_COLOR = 0;
var TYPE_PICK_LIGHT_LEVEL = 1;
var TYPE_HINT = 2;
var COLOR_RED = 0;
var COLOR_GREEN = 1;
var COLOR_BLUE = 2;
var COLOR_YELLOW = 3;
var COLOR_PURPLE = 4;
var COLOR_CYAN = 5;
var COLOR_WHITE = 6;
var type = -1;

 
  




 $(document).ready(function(){


    $.fn.bootstrapSwitch.defaults.onColor = 'success';
    $.fn.bootstrapSwitch.defaults.offColor = 'default';
    $.fn.bootstrapSwitch.defaults.onText = '是';
    $.fn.bootstrapSwitch.defaults.offText = '否';
    $('#test_switch1').bootstrapSwitch();
    $('.switch').bootstrapSwitch();
    $('#ex1').slider({
        formatter: function(value) {
            $('#dialog_content_light_level_hint').html('当前亮度 ' + value*10 + '%');
        }
    });
    $('.color_picker_div').click(function(){
        onColorPick($(this));
    });
    //往下为Ajax的请求
    $('#switch_device1_state').on('switchChange.bootstrapSwitch', function (event,state) {  
        ajaxPost(
            '../../api/device/',
            {'device1_state':Number($(this).bootstrapSwitch('state'))},
            function (){},
            function (){
                showHintDialog('网络错误','设置自定义设备1的开关失败，请检查您的网络连接后重试。');
            });
    });  
    $('#switch_device2_state').on('switchChange.bootstrapSwitch', function (event,state) {  
        ajaxPost(
            '../../api/device/',
            {'device2_state':Number($(this).bootstrapSwitch('state'))},
            function (){},
            function (){
                showHintDialog('网络错误','设置自定义设备2的开关失败，请检查您的网络连接后重试。');
            });
    });
    $('#switch_device3_state').on('switchChange.bootstrapSwitch', function (event,state) {  
        ajaxPost(
            '../../api/device/',
            {'device3_state':Number($(this).bootstrapSwitch('state'))},
            function (){},
            function (){
                showHintDialog('网络错误','设置自定义设备3的开关失败，请检查您的网络连接后重试。');
            });
    });
    $('#switch_device4_state').on('switchChange.bootstrapSwitch', function (event,state) {  
        ajaxPost(
            '../../api/device/',
            {'device4_state':Number($(this).bootstrapSwitch('state'))},
            function (){},
            function (){
                showHintDialog('网络错误','设置自定义设备4的开关失败，请检查您的网络连接后重试。');
            });
    });
    $('#switch_light_state').on('switchChange.bootstrapSwitch', function (event,state) {  
        ajaxPost(
            '../../api/light/',
            {'is_light_on':Number($(this).bootstrapSwitch('state'))},
            function (){},
            function (){
                showHintDialog('网络错误','设置环境光的开关失败，请检查您的网络连接后重试。');
            });
    });
});

function showColorPickerDialog(){
    $('#dialog_title').html('设置环境光颜色');
    $('#dialog_content_hint_p').css('display','none');
    $('#dialog_content_light_level_div').css('display','none');
    $('#dialog_content_color_pick_div').css('display','block');
    $('.color_picker_div').css('border-color','#eee');
    $('body').find('.color_picker_div').eq(lightColor).css('border-color','#aaa');
    type = TYPE_PICK_LIGHT_COLOR;
    showDialog();
}

function showLightLevelPicketDialog(){
    $('#dialog_title').html('设置环境光亮度');
    $('#dialog_content_hint_p').css('display','none');
    $('#dialog_content_light_level_div').css('display','block');
    $('#dialog_content_color_pick_div').css('display','none');
    $('#ex1').data('slider').setValue(lightLevel);
    type = TYPE_PICK_LIGHT_LEVEL;
    showDialog();
}

function showHintDialog(titleStr,contentStr){
    $('#dialog_title').html(titleStr);
    $('#dialog_content_hint_p').css('display','block');
    $('#dialog_content_light_level_div').css('display','none');
    $('#dialog_content_color_pick_div').css('display','none');
    $('#ex1').data('slider').setValue(lightLevel);
    $('#dialog_content_hint_p').html(contentStr);
    type = TYPE_HINT;
    showDialog();
}

function onColorPick(item){
    switch(item.attr('id')){
        case 'color_piack_red':lightTempColor = COLOR_RED;break;
        case 'color_piack_green':lightTempColor = COLOR_GREEN;break;
        case 'color_piack_blue':lightTempColor = COLOR_BLUE;break;
        case 'color_piack_yellow':lightTempColor = COLOR_YELLOW;break;
        case 'color_piack_purple':lightTempColor = COLOR_PURPLE;break;
        case 'color_piack_cyan':lightTempColor = COLOR_CYAN;break;
        case 'color_piack_white':lightTempColor = COLOR_WHITE;break;
    }
    $('.color_picker_div').css('border-color','#eee');
    item.css('border-color','#aaa');
}

function onConfirm(){
    switch(type){
        case TYPE_PICK_LIGHT_COLOR : {
            onPickColor();
            break;
        }
        case TYPE_PICK_LIGHT_LEVEL : {
            onPickLightLevel();
            break;
        }
    }
    hideDialog();
}

function onPickColor(){
    lightColor = lightTempColor;
    var colorStr = '';
    switch(lightColor){
        case COLOR_RED : colorStr='红色';break;
        case COLOR_GREEN : colorStr='绿色';break;
        case COLOR_BLUE : colorStr='蓝色';break;
        case COLOR_YELLOW : colorStr='黄色';break;
        case COLOR_PURPLE : colorStr='紫色';break;
        case COLOR_CYAN : colorStr='青色';break;
        case COLOR_WHITE : colorStr='白色';break;
    }
    $('#item_light_color_hint').html('当前颜色：'+colorStr);
    ajaxPost(
            '../../api/light/',
            {'light_color':lightColor},
            function (){},
            function (){
                showHintDialog('网络错误','设置环境光的颜色失败，请检查您的网络连接后重试。');
            });
}

function onPickLightLevel(){
    lightLevel = $('#ex1').data('slider').getValue();
    $('#item_light_level_hint').html('当前亮度：'+lightLevel*10+'%');
    ajaxPost(
            '../../api/light/',
            {'light_level':lightLevel},
            function (){},
            function (){
                showHintDialog('网络错误','设置环境光的亮度失败，请检查您的网络连接后重试。');
            });
}

function onCancel(){
    hideDialog();
}