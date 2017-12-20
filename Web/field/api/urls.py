from django.conf.urls import url

from . import views

app_name = 'api'

urlpatterns = [
    url(r'^device/',views.device,name='api_device'),
    url(r'^light/',views.light,name='api_light'),
    url(r'^temperature/',views.temperature,name='api_temperature'),
    url(r'^humidity/',views.humidity,name='api_humidity'),
    url(r'^dirt_humidity/',views.dirt_humidity,name='api_dirt_humidity'),
    url(r'^fertilization/',views.fertilization,name='api_fertilization'),
    url(r'^water/',views.water,name='api_water'),
    url(r'^schedule/',views.schedule,name='api_schedule'),
    url(r'^user/',views.user,name='api_user'),
    url(r'^.*', views.noSuchApi, name='api_no_such_api'),
]