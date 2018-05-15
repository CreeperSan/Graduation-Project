from django.conf.urls import url

from . import views

app_name = 'api'

urlpatterns = [
    # 下面是正产的请求
    url(r'^device/',views.device,name='api_device'),
    url(r'^light/',views.light,name='api_light'),
    url(r'^temperature/',views.temperature,name='api_temperature'),
    url(r'^humidity/',views.humidity,name='api_humidity'),
    url(r'^dirt_humidity/',views.dirt_humidity,name='api_dirt_humidity'),
    url(r'^fertilization/',views.fertilization,name='api_fertilization'),
    url(r'^water/',views.water,name='api_water'),
    url(r'^schedule/',views.schedule,name='api_schedule'),
    url(r'^user/',views.user,name='api_user'),
    url(r'^logout/',views.logout,name='api_logout'),
    url(r'^history/',views.history,name='api_history'),

    # 下面是手机初始化界面的请求
    url(r'^mobile_index', views.mobile_index, name='api_mobile_index'),
    url(r'^mobile_manage', views.mobile_manage, name='api_mobile_manage'),
    url(r'^mobile_schedule', views.mobile_schedule, name='api_mobile_schedule'),
    url(r'^mobile_me', views.mobile_me, name='api_mobile_me'),
    url(r'^mobile_login', views.mobile_login, name='api_mobile_login'),
    url(r'^mobile_setting', views.mobile_setting, name='api_mobile_setting'),
    url(r'^mobile_user', views.mobile_user, name='api_mobile_user'),

    # 下面是其他的请求
    url(r'^.*', views.noSuchApi, name='api_no_such_api'),
]