from django.db import models
from django.contrib import admin

# Create your models here.

class Section(models.Model):
	name = models.CharField(max_lenght=100)


class Author(models.Model):
	name = models.CharField(max_lenght=100)
	age = models.IntegerField(blank=True, null=True)


class New(models.Model):
	title = models.CharField(max_lenght=100)
	description = models.CharField(max_lenght=1000)
	author = models.ForeignKey(Author)
	section = models.ForeignKey(Section)

	def __unicode__(self):
		return self.title

admin.site.register(Section)
admin.site.register(Author)
admin.site.register(New)


