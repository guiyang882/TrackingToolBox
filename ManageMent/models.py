from __future__ import unicode_literals

from django.db import models
from django.contrib import admin
from django.db.models import permalink

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

admin.site.register(Photo)
admin.site.register(Video)