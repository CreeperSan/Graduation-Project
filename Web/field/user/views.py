import json
from django.shortcuts import render
from django.http import HttpResponse
from user.models import User


# Create your views here.

def index(request):
    userList = User.objects.all()
    userListJson = []
    for userItem in userList:
        tempUserJson = {}
        tempUserJson['username'] = userItem.username
        tempUserJson['nickname'] = userItem.nickname
        tempUserJson['is_staff'] = userItem.is_staff
        tempUserJson['is_active'] = userItem.is_active
        tempUserJson['is_admin'] = userItem.is_superuser
        tempUserJson['info'] = userItem.info
        userListJson.append(tempUserJson)
    return render(request,'user/index.html',context={'userList':userList,'jsonData':json.dumps(userListJson)})