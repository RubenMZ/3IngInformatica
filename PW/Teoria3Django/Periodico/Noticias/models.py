from django.db import models
from django.contrib import admin
from django.template.defaultfilters import slugify

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
	author = models.ManyToManyField(Author, blank=True)
	section = models.ForeignKey(Section)
	slug = models.SlugField(max_length=100)

	def __unicode__(self):
		return self.title

	def save(self, *args, **kwargs):
		self.slug =  slugify(self.title)
		super(New, self).save(*args, **kwargs)


admin.site.register(Section)
admin.site.register(Author)
admin.site.register(New)


