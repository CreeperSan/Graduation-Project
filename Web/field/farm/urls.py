from django.conf.urls import url

from . import views

app_name = 'farm'

urlpatterns = [
    url(r'^$', views.index, name='farm_index'),
    url(r'^monitor/',views.monitor,name='farm_monitor'),
    url(r'^schedule/',views.schedule,name='farm_schedule'),
    url(r'^history/',views.history,name='farm_history'),
    url(r'^setting/',views.setting,name='farm_setting'),
    url(r'^me/',views.me,name='farm_me'),
    url(r'^logout/',views.logout,name='farm_logout'),
]