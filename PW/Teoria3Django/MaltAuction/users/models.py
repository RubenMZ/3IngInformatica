from django.db import models
from django.contrib.auth.models import User

# Create your models here.

# Three user groups will be considered

# Unregistered user:    Can browse but not sell or buy
# Registered user:      Can browse, sell or buy but not modify information of other things
# Adminitrator user:    Can do everything

# These groups are managed using hard-coded groups in the admin site

class AuctionUser(User):
    payment_details = models.TextField()
    postal_address = models.TextField()
    
    def __unicode__(self):
        return self.username + ": " + self.first_name + " " + self.last_name
