from django.conf.urls import url
from django.contrib.auth import views as auth_views

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^login/$', auth_views.login,
        {'template_name': 'ChitChat/registration/login.html', 'redirect_authenticated_user': True}, name='login'),
    url(r'^logout/$', auth_views.logout_then_login, name='logout'),
    url(r'^userRegistration/$', views.userRegistration, name='userRegistration'),
    url(r'^(?P<user_pk>[0-9]+)/$', views.correspondence, name='correspondence'),
    url(r'^newMessage/(?P<redirect_user_pk>[0-9]+)/$', views.newMessage, name='newMessage'),
]
