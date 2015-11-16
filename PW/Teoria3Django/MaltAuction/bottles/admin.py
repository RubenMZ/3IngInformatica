from django.contrib import admin
from bottles.models import Bottle, Distillery, Brand

# Register your models here.
admin.site.register(Bottle)
admin.site.register(Distillery)
admin.site.register(Brand)
