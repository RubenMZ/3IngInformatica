# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('bottles', '0004_auto_20141205_1022'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='bottle',
            name='owner',
        ),
        migrations.AddField(
            model_name='bottle',
            name='bottles',
            field=models.IntegerField(null=True, blank=True),
            preserve_default=True,
        ),
    ]
