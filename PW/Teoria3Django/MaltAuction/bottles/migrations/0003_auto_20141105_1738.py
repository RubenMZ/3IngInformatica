# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('bottles', '0002_auto_20141105_1709'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='distillery',
            name='address',
        ),
        migrations.RemoveField(
            model_name='distillery',
            name='description',
        ),
        migrations.RemoveField(
            model_name='distillery',
            name='history',
        ),
        migrations.RemoveField(
            model_name='distillery',
            name='picture',
        ),
        migrations.RemoveField(
            model_name='distillery',
            name='status',
        ),
    ]
