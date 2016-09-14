from django.conf.urls import url
from ManageMent import views

urlpatterns = [
    url(r'^$', views.index, name="homepage"),
    url(r'^signup/$', views.signup, name='signup'),
    url(r'^login/$', views.login, name='login'),
    url(r'^logout/$', views.logout, name='logout'),
    url(r'^set_password/$', views.set_password, name='set_password'),
]