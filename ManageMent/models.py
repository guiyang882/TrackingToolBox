from __future__ import unicode_literals

from django.db import models
from django.contrib import admin
from django.db.models import permalink
from django.contrib.auth.models import User
from django.contrib.auth.admin import UserAdmin as BaseUserAdmin

class Photo(models.Model):
    caption = models.CharField(max_length=150)
    image = models.ImageField(upload_to="photos")
    description = models.TextField()
    timestamp = models.DateTimeField()

    class Meta:
        ordering = ['caption']

    def __unicode__(self):
        return self.caption

    @permalink
    def get_absolute_url(self):
        return ("photo_detail", None, {"object_id" : self.id})

class Video(models.Model):
    caption = models.CharField(max_length=150)
    content = models.ImageField(upload_to="videos")
    description = models.TextField()
    timestamp = models.DateTimeField()

    class Meta:
        ordering = ["caption"]

    def __unicode__(self):
        return self.caption

    @permalink
    def get_absolute_url(self):
        return ("video_detail", None, {"object_id" : self.id})

class MyUser(models.Model):
    user = models.OneToOneField(User)
    nickname = models.CharField(max_length=16)
    permission = models.IntegerField(default=1)

    def __unicode__(self):
        return self.user.username

class MyUserInline(admin.StackedInline):
    model = MyUser
    can_delete = False

class UserAdmin(BaseUserAdmin):
    inlines = (MyUserInline,)

admin.site.unregister(User)
admin.site.register(User, UserAdmin)
admin.site.register(Photo)
admin.site.register(Video)