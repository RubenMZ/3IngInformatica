#encoding: utf-8
from django.forms.extras.widgets import SelectDateWidget
from django.forms import ModelForm
from django import forms
from django.contrib.auth.forms import UserCreationForm
from users.models import AuctionUser

class RegisterForm(UserCreationForm):

    class Meta:
        model = AuctionUser
        fields = ['first_name', 'last_name', 'username', 'email', 'postal_address', 'payment_details']