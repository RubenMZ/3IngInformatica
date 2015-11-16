from django.db import models
from django.contrib.auth.models import User

# Create your models here.
class Distillery(models.Model):
    name = models.CharField(max_length = 100, primary_key = True)
    REGION_CHOICES = (
        ('C', 'Campbeltown'),
        ('H', 'Highlands'),
        ('D', 'Islands'),
        ('I', 'Islay'),
        ('L', 'Lowlands'),
        ('S', 'Speyside'),
        ('R', 'Ireland'),
        ('J', 'Japan'),
        ('U', 'USA'),
        ('W', 'Rest of the world'),
    )
    region = models.CharField(max_length = 1, choices = REGION_CHOICES)
    STATUS_CHOICES = (
        ('W', 'Working'),
        ('C', 'Closed'),
        ('D', 'Demolished'),
        ('M', 'Mothballed'),
        ('I', 'Dismantled'),
        ('S', 'Silent'),
    )
    status = models.CharField(max_length = 1, choices = STATUS_CHOICES, default = 'W')
    description = models.TextField(default = "")
    yearFounded = models.IntegerField('year founded')
    yearClosed = models.IntegerField(null = True, blank = True)
    webpage = models.URLField(null = True, blank = True)
    picture = models.ImageField(upload_to = 'distilleries', verbose_name = 'Picture', default = None)

    def __unicode__(self):
        return self.name
    
    # Other methods can be added
    def print_details(self):
        return  "%s founded in %d and located in %s"  % (self.name, self.yearFounded, self.get_region_display())

class Brand(models.Model):
    name = models.CharField(max_length = 100, primary_key = True)
    description = models.TextField()
    distillery = models.ForeignKey(Distillery)

    def    __unicode__(self):
        return self.name
    
    # For Python 3
    # def __str__(self):
    #   return self.name

class Bottle(models.Model):
    name = models.CharField(unique = True, max_length = 200)
    age = models.IntegerField(null = True, blank = True)
    vintage = models.IntegerField(null = True, blank = True)
    bottled = models.IntegerField(null = True, blank = True)
    distilleryBottling = models.BooleanField(default = True)
    independentBottler = models.CharField(max_length = 200, null = True, blank = True)
    strength = models.FloatField()
    brand = models.ForeignKey(Brand)
    comment = models.TextField(null = True, blank = True)
    cask = models.CharField(max_length = 100, null = True, blank = True)
    picture = models.ImageField(upload_to = 'bottles', verbose_name = 'Picture')
    bottles = models.IntegerField(null = True, blank = True)

    def __unicode__(self):
        return self.name
