from django.conf.urls import url
from ManageMent import views

urlpatterns = [
    url(r'^$', views.index, name="homepage"),
]