from django.shortcuts import render, redirect, get_object_or_404
from django.core.urlresolvers import reverse
from django.http import HttpResponse
from bottles.models import Bottle, Distillery, Brand
from django.contrib.auth.decorators import login_required
from bottles.forms import BottleForm, DistilleryForm, BrandForm
from django.core.urlresolvers import reverse_lazy
import string

# Create your views here.

# Lists
def bottles_list(request):
    """
    Returns list of all bottles ordered
    """
    bottles = Bottle.objects.all().order_by('name')
    letters = string.ascii_uppercase
    context = {'bottles': bottles, 'letters': letters}
    
    return render(request, "bottles/bottles.html", context)

def bottles_list_alpha(request, letter):
    """
    Returns list of all bottles starting with lettter ordered
    """
    bottles = Bottle.objects.filter(name__startswith = letter).order_by('name')
    letters = string.ascii_uppercase
    context = {'bottles': bottles, 'letters': letters}
    
    return render(request, "bottles/bottles.html", context)

def bottles_list_brand(request, brand):
    """
    Returns list of all bottles from a brand
    """
    bottles = Bottle.objects.filter(brand__name = brand).order_by('name')
    title = "Brand: " + brand
    context = {'bottles': bottles, 'title': title}
    
    return render(request, "bottles/bottles_sublist.html", context)

def bottles_list_distillery(request, distillery):
    """
    Returns list of all bottles from a distillery
    """
    bottles = Bottle.objects.filter(brand__distillery__name = distillery).order_by('name')
    title = "Distillery: " + distillery
    subtitle = "Brands: "
    brands = Brand.objects.filter(distillery__name = distillery).order_by('name')
    for brand in brands:
        subtitle += brand.name + ", "
    context = {'bottles': bottles, 'title': title, 'subtitle': subtitle[:-2]}
    
    return render(request, "bottles/bottles_sublist.html", context)

def distilleries_list(request):
    """
    Returns list of all distilleries ordered
    """
    distilleries = Distillery.objects.all().order_by('name')
    letters = string.ascii_uppercase
    context = {'distilleries': distilleries, 'letters': letters}
    
    return render(request, "bottles/distilleries.html", context)

def distilleries_list_alpha(request, letter):
    """
    Returns list of all distilleries starting with lettter ordered
    """
    distilleries = Distillery.objects.filter(name__startswith = letter).order_by('name')
    letters = string.ascii_uppercase
    context = {'distilleries': distilleries, 'letters': letters}
    
    return render(request, "bottles/distilleries.html", context)

def brands_list(request):
    """
    Returns list of all brands ordered
    """
    brands = Brand.objects.all().order_by('name')
    letters = string.ascii_uppercase
    context = {'brands': brands, 'letters': letters}
    
    return render(request, "bottles/brands.html", context)

def brands_list_alpha(request, letter):
    """
    Returns list of all brands starting with lettter ordered
    """
    brands = Brand.objects.filter(name__startswith = letter).order_by('name')
    letters = string.ascii_uppercase
    context = {'brands': brands, 'letters': letters}
    
    return render(request, "bottles/brands.html", context)

# Details
def bottle(request, bottle_id):
    """
    Returns specific bottle
    """
    # bottle = Bottle.objects.get(id = bottle_id)
    bottle = get_object_or_404(Bottle, pk = bottle_id)
    context = {'bottle': bottle}
    
    return render(request, "bottles/bottle.html", context)

def distillery(request, distillery_name):
    """
    Returns specific distillery
    """
    distillery = get_object_or_404(Distillery, pk = distillery_name)
    brands = Brand.objects.filter(distillery__name = distillery_name)
    
    context = {'distillery': distillery, 'brands': brands}
    
    return render(request, "bottles/distillery.html", context)

# Distilleries by region.
def region(request, letter):
    # Distilleries of region letter
    distilleries = Distillery.objects.filter(region__iexact = letter).order_by('name')    
    context = {'distilleries': distilleries}
    
    return render(request, 'bottles/region.html', context)

# Add a bottle
@login_required(login_url = '/users/login')
def bottle_new(request):
    if request.method == 'POST':
        form = BottleForm(request.POST, request.FILES)
        if form.is_valid():
            form.save()
            return redirect(reverse_lazy('bottles:bottles_list'))
    else:
        form = BottleForm()
    context = {'form':form}
    
    return render(request, 'bottles/bottle_new.html', context)

# Add a distillery
@login_required(login_url = '/users/login')
def distillery_new(request):
    if request.method == 'POST':
        form = DistilleryForm(request.POST, request.FILES)
        if form.is_valid():
            form.save()
            return redirect(reverse_lazy('bottles:distilleries_list'))
    else:
        form = DistilleryForm()
    context = {'form':form}
    
    return render(request, 'bottles/distillery_new.html', context)

# Add a brand
@login_required(login_url = '/users/login')
def brand_new(request):
    if request.method == 'POST':
        form = BrandForm(request.POST, request.FILES)
        if form.is_valid():
            form.save()
            return redirect(reverse_lazy('bottles:brands_list'))
    else:
        form = BrandForm()
    context = {'form':form}
    
    return render(request, 'bottles/brand_new.html', context)

# Edit a bottle
@login_required(login_url = '/users/login')
def bottle_edit(request, bottle_id):
    bottle = get_object_or_404(Bottle, pk = bottle_id)
    if request.method == 'POST':
        form = BottleForm(request.POST, request.FILES, instance = bottle)
        if form.is_valid():
            form.save()
            return redirect(reverse_lazy('bottles:bottles_list'))
    else:
        form = BottleForm(instance = bottle)
    context = {'form':form}
    
    return render(request, 'bottles/bottle_new.html', context)

# Edit a distillery
@login_required(login_url = '/users/login')
def distillery_edit(request, distillery_name):
    distillery = get_object_or_404(Distillery, pk = distillery_name)
    if request.method == 'POST':
        form = DistilleryForm(request.POST, request.FILES, instance = distillery)
        if form.is_valid():
            form.save()
            return redirect(reverse_lazy('distillerys:distillerys_list'))
    else:
        form = DistilleryForm(instance = distillery)
    context = {'form':form}
    
    return render(request, 'bottles/distillery_new.html', context)

# Search bottle
def bottle_search(request):
    if 'query' in request.GET:
        bottles =  Bottle.objects.filter(name__icontains = request.GET['query']) 
        letters = string.ascii_uppercase
        context = {'bottles': bottles, 'letters': letters}
    
        return render(request, "bottles/bottles.html", context)
    else:
        message = 'You submitted an empty form.'
        context = {'message': message}
        return render(request, "bottles/error_message.html", context)
        
# Search distillery
def distillery_search(request):
    if 'query' in request.GET:
        distilleries =  Distillery.objects.filter(name__icontains = request.GET['query']) 
        letters = string.ascii_uppercase
        context = {'distilleries': distilleries, 'letters': letters}
    
        return render(request, "bottles/distilleries.html", context)
    else:
        message = 'You submitted an empty form.'
        context = {'message': message}
        return render(request, "bottles/error_message.html", context)
    
# Search brand
def brand_search(request):
    if 'query' in request.GET:
        brands =  Brand.objects.filter(name__icontains = request.GET['query']) 
        letters = string.ascii_uppercase
        context = {'brands': brands, 'letters': letters}
    
        return render(request, "bottles/brands.html", context)
    else:
        message = 'You submitted an empty form.'
        context = {'message': message}
        return render(request, "bottles/error_message.html", context)

# Delete
@login_required(login_url = '/users/login')
def bottle_delete(request, bottle_id):
    """
    Returns specific bottle
    """
    bottle = get_object_or_404(Bottle, pk = bottle_id)
    
    # Only staff can delete bottle
    if request.user.is_staff:       
        bottle.delete()
    else:
        message = "You have no permissions for deleting a bottle"
        context = {'message': message}
        return render(request, "bottles/error_message.html", context)
    
    return redirect(reverse_lazy('bottles:bottles_list'))
@login_required(login_url = '/users/login')

def distillery_delete(request, distillery_name):
    """
    Returns specific distillery
    """
    distillery = get_object_or_404(Distillery, pk = distillery_name)
    
    # Only staff can delete distillery
    if request.user.is_staff:       
        distillery.delete()
    else:
        message = "You have no permissions for deleting a distillery"
        context = {'message': message}
        return render(request, "bottles/error_message.html", context)
    
    return redirect(reverse_lazy('bottles:distilleries_list'))
