from django.db import models
from django.contrib import admin

# Create your models here.

class Section(models.Model):
	name = models.CharField(max_length=100)
	def __unicode__(self):
		return self.name


class Author(models.Model):
	name = models.CharField(max_length=100)
	age = models.IntegerField(blank=True, null=True)
	def __unicode__(self):
		return self.name


class New(models.Model):
	title = models.CharField(max_length=100)
	description = models.CharField(max_length=1000)
	author = models.ForeignKey(Author)
	section = models.ForeignKey(Section)

	def __unicode__(self):
		return self.title

admin.site.register(Section)
admin.site.register(Author)
admin.site.register(New)


