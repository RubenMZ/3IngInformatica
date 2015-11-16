from django.shortcuts import render
from django.views.generic.list import ListView
from auction.models import Item

# Create your views here.

class CurrentAuctionList(ListView):
    
    model = Item
    
    # queryset = Item.objects.all()
    
    # def get_queryset(self):
    #     return Item.objects.all()
