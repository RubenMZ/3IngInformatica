# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('bottles', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='bottle',
            name='distilleryBottling',
            field=models.BooleanField(default=True),
        ),
    ]
