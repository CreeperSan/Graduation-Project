function getCookie(name) {  
    var cookieValue = null;  
    if (document.cookie && document.cookie != '') {  
        var cookies = document.cookie.split(';');  
        for (var i = 0; i < cookies.length; i++) {  
            var cookie = jQuery.trim(cookies[i]);  
            // Does this cookie string begin with the name we want?  
            if (cookie.substring(0, name.length + 1) == (name + '=')) {  
                cookieValue = decodeURIComponent(cookie.substring(name.length + 1));  
                break;  
            }  
        }  
    }  
    return cookieValue;  
} 

function csrfSafeMethod(method) {  
    // these HTTP methods do not require CSRF protection  
    return (/^(GET|HEAD|OPTIONS|TRACE)$/.test(method));  
}  

$.ajaxSetup({  
    beforeSend: function(xhr, settings) {  
    var csrftoken = getCookie('csrftoken');       
    if (!csrfSafeMethod(settings.type) && !this.crossDomain) {  
            xhr.setRequestHeader("X-CSRFToken", csrftoken);  
        }  
    }  
});  

function ajaxPost(urlSend,dataSend,onSuccess,onError){
    $.ajax({
        url:urlSend,
        type:'POST',
        async:true,
        data:dataSend,
        timeout:5000,
        beforeSend:function(xhr, settings){
            console.log('发送前');
            var csrftoken = getCookie('csrftoken');
            if (!csrfSafeMethod(settings.type) && !this.crossDomain) {
                xhr.setRequestHeader("X-CSRFToken", csrftoken);
            }
        },
        success:function(data,textStatus,jqXHR){
            console.log(data);
            onSuccess();
        },
        error:function(xhr,textStatus){
            console.log('错误');
            onError();
        },
        complete:function(){
            console.log('结束');
        }
    });
}