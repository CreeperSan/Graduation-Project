import os
import random
import string
import time
from django.contrib import auth

# 常量
KEY_TOKEN = 'token'
KEY_USERNAME = 'username'
KEY_PASSWORD = 'password'

RESULT_SUCCESS = 0
RESULT_TOKEN_NOT_EXIST = 6
RESULT_PASSWORD_ERROR = 2
RESULT_PARAMS_MISSED = 3
RESULT_ACCOUNT_DISABLE = 4
RESULT_LUCKY = 5

OVER_TIME_DELAY_TIME = 1000*60*60*24*7      # 超时时间，1000ms*60s*60m*24h*7d 一周


# 客户端登录验证用的
# 里面储存的简直对类型是　键 : 用户唯一token 　　　值 : ［　激活时间戳, 用户对象, token ］
userDict = {}
userNameSet = set()


# 通过请求获取用户,将会返回１个list,里面包含２个参数,第一个是结果代码,第二个是token,第三个是登录的用户对象(如果没有则为None)
def get_user(request):
    # print('\n\n\n\n\n\n\n\n数据源')
    # print(userDict)
    if request.user.is_authenticated : # 如果已经验证过,session存在(web)
        return [RESULT_SUCCESS, get_token(request.user.username),request.user]
    else: # 如果没有验证过
        if KEY_TOKEN in request.POST : # 如果存在 authorization
            temp_token = request.POST[KEY_TOKEN]
            if temp_token in userDict:
                temp_user_obj = userDict[temp_token]
                current_time_stamp = getTimeStamp()
                if temp_user_obj[0] - current_time_stamp > OVER_TIME_DELAY_TIME:
                    return [RESULT_TOKEN_NOT_EXIST, get_token(temp_user_obj[1]), temp_user_obj[1]]
                temp_user_obj[0] = getTimeStamp()
                userDict[temp_token][0]=getTimeStamp()
                return [RESULT_SUCCESS, get_token(userDict[temp_token][1]), userDict[temp_token][1]]
            else:
                return [RESULT_TOKEN_NOT_EXIST, '',None]
        elif KEY_USERNAME in request.POST and KEY_PASSWORD in request.POST : # 如果存在帐号和密码
            username = request.POST['username']
            password = request.POST['password']
            temp_user = auth.authenticate(request, username=username, password=password) # 验证
            if temp_user is not None:   # 如果用户存在
                if temp_user.is_active : # 如果用户没被停用
                    for i in range(0,10):
                        temp_token = get_random_string(32)
                        if temp_token not in userDict: # 生成的随机验证码可用
                            if temp_user.username in userNameSet :
                                prev_token = ''
                                for temp_user_item in userDict:
                                    if userDict[temp_user_item][1].username == temp_user.username:
                                        prev_token = temp_user_item
                                        break
                                if prev_token != '':
                                    userNameSet.remove(userDict[prev_token][1].username)
                                    userDict.pop(prev_token)
                            userDict[temp_token] = [getTimeStamp(), temp_user, temp_token]
                            userNameSet.add(temp_user.username)
                            return [ RESULT_SUCCESS, get_token(temp_user),temp_user ]
                    return [ RESULT_LUCKY, None ]
                else : # 如果用户被停用
                    return [ RESULT_ACCOUNT_DISABLE, get_token(temp_user),temp_user ]
            else : # 如果用户不存在
                return [RESULT_PASSWORD_ERROR, '', None]
        else :
            return [RESULT_PARAMS_MISSED, '', None]

def get_token(username):
    for tempToken in userDict:
        # print(userDict[tempToken][1])
        if userDict[tempToken][1] == username:
            return tempToken
    return ''

# 获取随机字符串
def get_random_string(length):
    return ''.join(random.sample(string.ascii_letters + string.digits, length))

# 获取时间戳
def getTimeStamp():
    return int(time.time()*1000)