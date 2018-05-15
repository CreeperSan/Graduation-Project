"""field URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.10/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url,include
from django.contrib import admin
import conn.conn as socket
import address.address as address
import schedule.schedule as schedule

urlpatterns = [
    url(r'^api/',include('api.urls')),
    url(r'^farm/',include('farm.urls')),
    url(r'^user/',include('user.urls')),
    url(r'^admin/', admin.site.urls),
    url(r'',include('index.urls')),
]

# 初始化局域网UDP接受线程
socket.init()
# 初始化局域网地址获取服务
address.init()
# 初始化定时消息循环
schedule.init()