from django.shortcuts import render
from bottles.models import Bottle, Distillery, Brand

# Create your views here.
def home(request):
    # Distilleries by regions
    REGION_CHOICES = ('C', 'H', 'D', 'I', 'L', 'S', 'R', 'J', 'U', 'W')
    by_region = []
    for r in REGION_CHOICES:
        another = Distillery.objects.filter(region = r).order_by('name')
        by_region.append(another)
        
    # Last bottles added
    bottles = Bottle.objects.all()[:5]
        
    context = {'by_region':by_region, 'bottles':bottles}
    return render(request, 'home/home.html', context)
