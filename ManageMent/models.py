from __future__ import unicode_literals

from django.db import models
from django.contrib import admin
from django.contrib.auth.models import User

# Create your models here.
class PushVideo(models.Model):
	title = models.CharField(max_length = 150)
	body = models.TextField()
	timestamp = models.DateTimeField()


admin.site.register(PushVideo)