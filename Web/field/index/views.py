from django.shortcuts import render
from django.http import HttpResponse
from django.contrib import auth
from django.shortcuts import render_to_response
from django.template import RequestContext

# Create your views here.

def index(request):
    isSuccess = False
    isLoginRequest = False
    if request.POST :
        isLoginRequest = True
        username = password = ''
        username = request.POST.get('username')
        password = request.POST.get('password')
        user = auth.authenticate(username=username,password=password)
        if user is not None and user.is_active:
            isSuccess = True
            auth.login(request,user)
            print('登陆成功',username,password)
        else :
            print('登陆失败',username,password)
    return render(request,'index/index.html',context={
        'isSuccess':isSuccess,
        'isLoginRequest':isLoginRequest,
    })
