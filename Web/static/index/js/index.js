function initLoginBlockPosition(){
    var screenHeight = $(window).height();
    var loginBlockHeight = $('#login_content').height();
    $('#login_content').css('top',(screenHeight-loginBlockHeight)/2*0.4);
}


var LENGTH_PASSWORD_LENTH_MIN = 6;
var LENGTH_USERNAME_LENTH_MIN = 4;
function submitLogin(){
    var usernameStr = $('#login_input_account').val();
    var passwordStr = $('#login_input_password').val();
    if (usernameStr.length < LENGTH_USERNAME_LENTH_MIN) {   //用户名太短
        $('#login_block_username').shake(1, 10, 300);
        return false;
    }else if (passwordStr.length < LENGTH_PASSWORD_LENTH_MIN) {     //密码太短
        $('#login_block_password').shake(1, 10, 300);
        return false;
    }
    return true;
}

$(document).ready(function(){
    initLoginBlockPosition();
    $('#text_forget_password').click(function(){
        showDialogWithContent('忘记密码了？','你可以询问管理员已以重置密码。')
    })
});

$(window).resize(initLoginBlockPosition);