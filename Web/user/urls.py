from django.conf.urls import url

from . import views

app_name = 'user'

urlpatterns = [
    url(r'^$', views.index, name='user_index'),
]