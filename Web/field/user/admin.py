from django.contrib import admin
from .models import User

# Register your models here.

class UserAdmin(admin.ModelAdmin):
    list_display = ['username','nickname','email','is_staff','date_joined','is_active','info']

admin.site.register(User,UserAdmin)
