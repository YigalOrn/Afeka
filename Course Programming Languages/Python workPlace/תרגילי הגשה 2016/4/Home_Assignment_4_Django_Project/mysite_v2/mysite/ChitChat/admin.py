from django.contrib import admin
from .models import Message
from django.contrib.auth.models import User


# Register your models here.

class MessageAdmin(admin.ModelAdmin):
    list_display = ('pk', 'sender', 'recipient', 'pub_date', 'message')
    list_filter = ['pub_date', 'sender', 'recipient']


class UserAdmin(admin.ModelAdmin):
    list_display = ('username', 'date_joined', 'last_login', 'is_superuser', 'pk')


admin.site.unregister(User)
admin.site.register(User, UserAdmin)
admin.site.register(Message, MessageAdmin)
