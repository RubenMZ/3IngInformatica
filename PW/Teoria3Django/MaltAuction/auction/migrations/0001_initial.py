# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('bottles', '0005_auto_20141206_1226'),
    ]

    operations = [
        migrations.CreateModel(
            name='Item',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('price', models.IntegerField()),
                ('reserve', models.IntegerField(default=0)),
                ('bottle', models.ForeignKey(to='bottles.Bottle')),
            ],
            options={
            },
            bases=(models.Model,),
        ),
    ]
