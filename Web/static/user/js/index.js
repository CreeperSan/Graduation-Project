$(document).ready(function(){
    $.fn.bootstrapSwitch.defaults.onColor = 'success';
    $.fn.bootstrapSwitch.defaults.offColor = 'default';
    $('.switch').bootstrapSwitch({
        onText:'是',
        offText:'否'
    });

});

/**
 *  定义一些常量
 */

/**
 *  对话框部分
 */
var TYPE_NONE = 0;
var TYPE_CREATE_USER = 1;
var TYPE_EDIT_USER = 2;
var TYPE_DEL_USER = 3;
var ACTION_TYPE_USER_CREATE = 0;
var ACTION_TYPE_USER_EDIT = 1;
var ACTION_TYPE_USER_DEL = 2;
var VALUE_BOOL_TRUE = 1;
var VALUE_BOOL_FALSE = 0;

var type = TYPE_NONE;   //当前操作
var sendJson = {};
var selectUserName = '';    //当前操作的用户名

function showAsCreateUserDialog(){
    type = TYPE_CREATE_USER;
    $('#dialog_username_input').val('');
    $('#dialog_nickname_input').val('');
    $('#dialog_password_input').val('');
    $('#dialog_password_confirm_input').val('');
    $('#dialog_info').val('');
    setSwitchState('dialog_is_stuff_switch',false);
    setSwitchState('dialog_is_active_switch',true);
    showCreateUserDialog('创建用户','使用此引导来创建一个用户');
}

function onConfirm(){
        var userName = $('#dialog_username_input').val();
        var nickName = $('#dialog_nickname_input').val();
        var password = $('#dialog_password_input').val();
        var passwordConfirm = $('#dialog_password_confirm_input').val();
        var isStuff = VALUE_BOOL_FALSE;
        var isActive = VALUE_BOOL_FALSE;
        if ($('#dialog_is_stuff_switch').is(':checked')) {
            isStuff = VALUE_BOOL_TRUE;
        }
        if ($('#dialog_is_active_switch').is(':checked')) {
            isActive = VALUE_BOOL_TRUE;
        }
        var info = $('#dialog_info').val();
    if (type == TYPE_CREATE_USER) {//创建用户打开的对话框
        //校验数据合法性
        if (userName == '') {$('#dialog_username_div').shake(1,10,300);return;}//检查用户名是否合法
        if (password.length < 6) {$('#dialog_password_div').shake(1,10,300);return;}//检查密码是否合法
        if (passwordConfirm != password) {$('#dialog_password_div').shake(1,10,300);$('#dialog_password_confirm_div').shake(1,10,300);return;}//检查重复密码是否和发
        //发送请求
        sendJson = {'username':userName,'nickname':nickName,'password':password,'is_stuff':isStuff,'is_active':isActive,'info':info};
        sendJson['action_type'] = ACTION_TYPE_USER_CREATE;
        ajaxPost(API_USER,
            sendJson,
            function(){
                location.reload();
            },
            function(){
                showSimpleDialog('网络错误','创建用户失败，请检查您的网络连接后重试');
            }
        )
    }else if (type == TYPE_EDIT_USER) {//编辑用户打开的对话框
        sendJson = {'username':userName,'nickname':nickName,'password':password,'is_stuff':isStuff,'is_active':isActive,'info':info};
        sendJson['action_type'] = ACTION_TYPE_USER_EDIT;
        ajaxPost(API_USER,
            sendJson,
            function(){
                location.reload();
            },
            function(){
                showSimpleDialog('网络错误','创建用户失败，请检查您的网络连接后重试');
            }
        )
    }else{
        alert('未知的操作类型!');
    }
    //关闭对话框
    hideDialog();
    type = TYPE_NONE;
}

function onCancel(){
    hideDialog();
    type = TYPE_NONE;
}

function onEdit(self){
    var username = $(self).attr('id').substring(5);
    selectUserName = username;
    type = TYPE_EDIT_USER;
    var userJsonObject = getJsonObjectFromUsername(username)
    if (userJsonObject) {
        showEditUserDialog(userJsonObject);
    }else{
        console.log("要编辑的用户为空");
    }
}

function onDelete(self){
    var userJson =getJsonObjectFromUsername(selectUserName);
    sendJson = {'username':userJson['username'],'nickname':userJson['nickname'],'password':'','is_stuff':VALUE_BOOL_FALSE,'is_active':VALUE_BOOL_FALSE,'info':userJson['info']};
    sendJson['action_type'] = ACTION_TYPE_USER_DEL;
    ajaxPost(API_USER,
        sendJson,
        function(){
            showSimpleDialog('删除成功','删除用户 '+sendJson.username+' 成功')
            refreshWebsite();
        },
        function(){
            showSimpleDialog('网络错误','删除用户 '+sendJson.username+' 失败，请检查你的网络连接后重试');
        }
    )
}

function refreshUserList(){

}

function getJsonObjectFromUsername(username){
    for(var i=0;i<userJson.length;i++){
        var tempJsonObject = userJson[i];
        if ('username' in tempJsonObject) {
            if (tempJsonObject['username'] == username) {
                return tempJsonObject
            }
        }
    }
    return none
}

function showSimpleDialog(title,content){
    //显示元素
    setVisiable('dialog_hint_p',true);
    setVisiable('dialog_username_div',false);
    setVisiable('dialog_nickname_div',false);
    setVisiable('dialog_password_div',false);
    setVisiable('dialog_password_confirm_div',false);
    setVisiable('dialog_info_div',false);
    setVisiable('dialog_switch_div',false);
    setVisiable('dialog_content_delete',false);
    //设置文本
    $('#dialog_title').html(title);
    $('#dialog_hint_p').html(content);
    //显示对话框
    showDialog();
}

function showCreateUserDialog(title,content){
    //显示元素
    setVisiable('dialog_hint_p',true);
    setVisiable('dialog_username_div',true);
    setVisiable('dialog_nickname_div',true);
    setVisiable('dialog_password_div',true);
    setVisiable('dialog_password_confirm_div',true);
    setVisiable('dialog_info_div',true);
    setVisiable('dialog_switch_div',true);
    setVisiable('dialog_content_delete',false);
    //设置文本
    $('#dialog_title').html(title);
    $('#dialog_hint_p').html(content);
    setInputReadOnly('dialog_username_input',false);
    //显示对话框
    showDialog();
}

function showEditUserDialog(userJsonObj){
    //显示元素
    setVisiable('dialog_hint_p',true);
    setVisiable('dialog_username_div',true);
    setVisiable('dialog_nickname_div',true);
    setVisiable('dialog_password_div',false);
    setVisiable('dialog_password_confirm_div',false);
    setVisiable('dialog_info_div',true);
    setVisiable('dialog_switch_div',true);
    setVisiable('dialog_content_delete',true);
    //设置文本
    $('#dialog_title').html('编辑用户');
    $('#dialog_hint_p').html('正在通过向导编辑用户'+userJsonObj['username']);
    $('#dialog_username_input').val(userJsonObj['username']);
    setInputReadOnly('dialog_username_input',true);
    $('#dialog_nickname_input').val(userJsonObj['nickname']);
    setSwitchState('dialog_is_stuff_switch',userJsonObj['is_staff']);
    setSwitchState('dialog_is_active_switch',userJsonObj['is_active']);
    $('#dialog_info').val(userJsonObj['info']);
    //显示对话框
    showDialog();
}

function getIdentityStr(isStaff,isAdmin){
    if (isAdmin) {
        return '管理员';
        if (isStaff) {
            return '工作人员';
        }else{
            return '访客';
        }
    }
}

function getIsActiveStr(isActive){
    if (isActive) {
        return '正在活动';
    }else{
        return '已停用';
    }
}

/**
 *  简单的方法
 */
function setVisiable(id,isVisible){
    if (isVisible) {
        $('#'+id).css('display','block');
    }else{
        $('#'+id).css('display','none');
    }
}
function setSwitchState(id,isActive){
    $('#'+id).bootstrapSwitch('state',isActive);
}
function setInputReadOnly(id,isReadOnly){
    $('#'+id).attr('readOnly',isReadOnly);
}

/**
 *  浏览器操作
 */
 function refreshWebsite(){
    window.location.reload();
 }