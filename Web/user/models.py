from django.db import models
from django.contrib.auth.models import AbstractUser
from django.utils.translation import ugettext_lazy as _
from django.contrib.auth.base_user import BaseUserManager

# Create your models here.

class User(AbstractUser):
    nickname    = models.CharField(_('昵称'),max_length=50,blank=True)
    info        = models.CharField(_('备注'),max_length=200,blank=True)

    class Meta(AbstractUser.Meta):
        pass


