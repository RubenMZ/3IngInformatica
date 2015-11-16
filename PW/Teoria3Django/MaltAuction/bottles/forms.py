#encoding: utf-8
from django.forms.extras.widgets import SelectDateWidget
from django.forms import ModelForm
from django import forms
from bottles.models import Bottle, Distillery, Brand

class BottleForm(ModelForm):
    class Meta:
        model = Bottle
        
        # exclude = ['user', 'bottle', ]
        # fields = ['pub_date', 'headline', 'content', 'reporter']
        fields = '__all__'
        
    def __init__(self, *args, **kwargs):
        super(BottleForm, self).__init__(*args, **kwargs)
        self.fields['distilleryBottling'].label = "Distillery bottling"
        self.fields['independentBottler'].label = "Independent bottler"

class DistilleryForm(ModelForm):
    class Meta:
        model = Distillery
        
        fields = '__all__'
        
class BrandForm(ModelForm):
    class Meta:
        model = Brand
        
        fields = '__all__'