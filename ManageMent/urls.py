from django.conf.urls import url
from ManageMent import views

urlpatterns = [
    url(r'^$', views.index, name="homepage"),
    url(r'^signup/$', views.signup, name='signup'),
    url(r'^login/$', views.login, name='login'),
    url(r'^logout/$', views.logout, name='logout'),
    url(r'^set_password/$', views.set_password, name='set_password'),
    url(r'^upload_videos/$', views.upload_videos, name='upload_videos'),
    url(r'^upload_images/$', views.upload_images, name='upload_images'),
    url(r'^view_videos/$', views.view_videos_list, name='view_videos'),
    url(r'^view_images/$', views.view_images_list, name='view_images'),
]