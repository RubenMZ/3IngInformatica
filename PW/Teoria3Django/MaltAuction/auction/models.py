from django.db import models
from django.db.models.fields import IntegerField
from bottles.models import Bottle

# Create your models here.

# Item to be auctioned
class Item(models.Model):
    bottle = models.ForeignKey(Bottle)
    reserve = models.IntegerField(default = 0)
    beginAuction = models.DateField(blank = True, null = True)
    endAuction = models.DateField(blank = True, null = True)
    

    def __unicode__(self):
        return self.bottle.name
 
class Bid(models.Model):
    #bidder = models.ForeignKey(User)
    value = models.IntegerField()
