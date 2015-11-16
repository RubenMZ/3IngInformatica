# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
from django.conf import settings


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='Bottle',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('name', models.CharField(unique=True, max_length=200)),
                ('age', models.IntegerField(null=True, blank=True)),
                ('vintage', models.IntegerField(null=True, blank=True)),
                ('bottled', models.IntegerField(null=True, blank=True)),
                ('distilleryBottling', models.BooleanField()),
                ('independentBottler', models.CharField(max_length=200, null=True, blank=True)),
                ('strength', models.FloatField()),
                ('comment', models.TextField()),
                ('cask', models.CharField(max_length=100, null=True, blank=True)),
                ('picture', models.ImageField(upload_to=b'bottles', verbose_name=b'Picture')),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Brand',
            fields=[
                ('name', models.CharField(max_length=100, serialize=False, primary_key=True)),
                ('description', models.TextField()),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Distillery',
            fields=[
                ('name', models.CharField(max_length=100, serialize=False, primary_key=True)),
                ('region', models.CharField(max_length=1, choices=[(b'C', b'Campbeltown'), (b'H', b'Highlands'), (b'D', b'Islands'), (b'I', b'Islay'), (b'L', b'Lowlands'), (b'S', b'Speyside'), (b'R', b'Ireland'), (b'J', b'Japan'), (b'U', b'USA'), (b'W', b'Rest of the world')])),
                ('status', models.CharField(max_length=1, choices=[(b'W', b'Working'), (b'C', b'Closed'), (b'D', b'Demolished'), (b'M', b'Mothballed'), (b'I', b'Dismantled'), (b'S', b'Silent')])),
                ('address', models.CharField(max_length=500)),
                ('history', models.TextField()),
                ('description', models.TextField()),
                ('yearFounded', models.IntegerField(verbose_name=b'year founded')),
                ('yearClosed', models.IntegerField(null=True, blank=True)),
                ('picture', models.ImageField(upload_to=b'distilleries', verbose_name=b'Picture')),
                ('webpage', models.URLField(null=True, blank=True)),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.AddField(
            model_name='brand',
            name='distillery',
            field=models.ForeignKey(to='bottles.Distillery'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='bottle',
            name='brand',
            field=models.ForeignKey(to='bottles.Brand'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='bottle',
            name='owner',
            field=models.ForeignKey(to=settings.AUTH_USER_MODEL),
            preserve_default=True,
        ),
    ]
