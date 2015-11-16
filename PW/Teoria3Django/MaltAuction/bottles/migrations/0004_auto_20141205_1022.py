# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('bottles', '0003_auto_20141105_1738'),
    ]

    operations = [
        migrations.AddField(
            model_name='distillery',
            name='description',
            field=models.TextField(default=b''),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='distillery',
            name='picture',
            field=models.ImageField(default=None, upload_to=b'distilleries', verbose_name=b'Picture'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='distillery',
            name='status',
            field=models.CharField(default=b'W', max_length=1, choices=[(b'W', b'Working'), (b'C', b'Closed'), (b'D', b'Demolished'), (b'M', b'Mothballed'), (b'I', b'Dismantled'), (b'S', b'Silent')]),
            preserve_default=True,
        ),
    ]
