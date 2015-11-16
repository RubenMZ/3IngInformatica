# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('users', '0001_initial'),
    ]

    operations = [
        migrations.RenameField(
            model_name='auctionuser',
            old_name='paymentDetails',
            new_name='address',
        ),
        migrations.RenameField(
            model_name='auctionuser',
            old_name='sendingAddress',
            new_name='payment_details',
        ),
    ]
