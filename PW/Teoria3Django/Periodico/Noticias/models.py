from django.db import models
from django.contrib import admin

# Create your models here.

class Section(models.Model):
	name = models.CharField(max_length=100)
<<<<<<< HEAD
=======
	def __unicode__(self):
		return self.name
>>>>>>> 3176d90657fe8c399ed1fee758961ef0da271f3a


class Author(models.Model):
	name = models.CharField(max_length=100)
	age = models.IntegerField(blank=True, null=True)
	def __unicode__(self):
		return self.name


class New(models.Model):
	title = models.CharField(max_length=100)
	description = models.CharField(max_length=1000)
<<<<<<< HEAD
	author = models.ForeignKey(Author)
=======
	author = models.ManyToManyField(Author, blank=True)
>>>>>>> 3176d90657fe8c399ed1fee758961ef0da271f3a
	section = models.ForeignKey(Section)

	def __unicode__(self):
		return self.title

admin.site.register(Section)
admin.site.register(Author)
admin.site.register(New)


