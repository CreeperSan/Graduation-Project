from django.db import models
import config.config as config

# Create your models here.

# 传感器数据，主动触发

class Sensor(models.Model):
    year   = models.IntegerField(default=2017)
    month  = models.IntegerField(default=1)
    day    = models.IntegerField(default=1)
    hour   = models.IntegerField(default=0)
    minute = models.IntegerField(default=0)
    second = models.IntegerField(default=0)
    light           = models.FloatField(default=-100)
    air_temperature = models.FloatField(default=-100)
    dirt_temperature= models.FloatField(default=-100)
    air_humidity    = models.FloatField(default=-100)
    dirt_humidity   = models.FloatField(default=-100)
    device_id       = models.IntegerField(default=0)

    def __str__(self):
        return str(self.year)+str(self.month)+str(self.day)+str(self.hour)+str(self.minute)+str(self.second)


# 用户自定义继电器，被动触发

class CustomControl(models.Model):
    year   = models.IntegerField(default=2017)
    month  = models.IntegerField(default=1)
    day    = models.IntegerField(default=1)
    hour   = models.IntegerField(default=0)
    minute = models.IntegerField(default=0)
    second = models.IntegerField(default=0)
    value  = models.FloatField(default=0)
    reason = models.CharField(max_length=100)

    def __str__(self):
        return str(year)+str(month)+str(day)+str(hour)+str(minute)+str(second)


# 报警信息，被动触发

class Alarm(models.Model):
    year   = models.IntegerField(default=2017)
    month  = models.IntegerField(default=1)
    day    = models.IntegerField(default=1)
    hour   = models.IntegerField(default=0)
    minute = models.IntegerField(default=0)
    second = models.IntegerField(default=0)
    level  = models.IntegerField(default=0)
    reason = models.CharField(max_length=200)
    action = models.CharField(max_length=200)

    def __str__(self):
        return str(year)+str(month)+str(day)+str(hour)+str(minute)+str(second)+str(reason)


# 浇水信息，被动触发

class Watering(models.Model):
    year   = models.IntegerField(default=2017)
    month  = models.IntegerField(default=1)
    day    = models.IntegerField(default=1)
    hour   = models.IntegerField(default=0)
    minute = models.IntegerField(default=0)
    second = models.IntegerField(default=0)
    reason = models.CharField(max_length=100)

    def __str__(self):
        return str(year)+str(month)+str(day)+str(hour)+str(minute)+str(second)+str(reason)


# 施肥信息,被动触发

class Fertilization(models.Model):
    year   = models.IntegerField(default=2017)
    month  = models.IntegerField(default=1)
    day    = models.IntegerField(default=1)
    hour   = models.IntegerField(default=0)
    minute = models.IntegerField(default=0)
    second = models.IntegerField(default=0)
    reason = models.CharField(max_length=100)

    def __str__(self):
        return str(year)+str(month)+str(day)+str(hour)+str(minute)+str(second)+str(reason)

# 定时信息的记录

class Schedule(models.Model):
    name = models.CharField(max_length=100)
    isOn = models.IntegerField(default=config.STATE_OFF)
    repeatType = models.IntegerField(default=config.REPEAT_TYPE_NO)
    repeatCircle = models.CharField(default='0',max_length=7)
    hour = models.IntegerField(default='0')
    minute = models.IntegerField(default='0')
    actions = models.CharField(max_length=1024)

    def __str__():
        return str(name)
