from django.conf.urls import patterns, url
from django.core.urlresolvers import reverse
from django.contrib.staticfiles.urls import staticfiles_urlpatterns
from django.conf.urls.static import static
from django.conf import settings
from django.views.generic import TemplateView

from bottles import views

urlpatterns = patterns('',
    # Lists
    url(r'^bottle/list/$', views.bottles_list, name = "bottles_list"),
    url(r'^bottle/list/(?P<letter>\w)/$', views.bottles_list_alpha, name = "bottles_list_alpha"),
    url(r'^bottle/list/brand/(?P<brand>\w+)/$', views.bottles_list_brand, name = "bottles_list_brand"),
    url(r'^bottle/list/distillery/(?P<distillery>\w+)/$', views.bottles_list_distillery, name = "bottles_list_distillery"),
    url(r'^distillery/list/$', views.distilleries_list, name = "distilleries_list"),
    url(r'^distillery/list/(?P<letter>\w)/$', views.distilleries_list_alpha, name = "distilleries_list_alpha"),
    url(r'^region/(?P<letter>\w)/$', views.region, name = "region"),
    url(r'^brand/list/$', views.brands_list, name = "brands_list"),
    url(r'^brand/list/(?P<letter>\w)/$', views.brands_list_alpha, name = "brands_list_alpha"),
    
    # Add
    url(r'^bottle/new/$', views.bottle_new, name = 'bottle_new'),
    url(r'^distillery/new/$', views.distillery_new, name = 'distillery_new'),
    url(r'^brand/new/$', views.brand_new, name = 'brand_new'),
    
    # Search
    url(r'^bottle/search/', views.bottle_search, name = "bottle_search"),
    url(r'^distillery/search/', views.distillery_search, name = "distillery_search"),
    url(r'^brand/search/', views.brand_search, name = "brand_search"),
    
    # Details
    url(r'^bottle/(?P<bottle_id>\d+)/$', views.bottle, name = "bottle"),    
    url(r'^distillery/(?P<distillery_name>\w+)/$', views.distillery, name = "distillery"),
    
    # Delete
    url(r'^bottle/delete/(?P<bottle_id>\d+)/$', views.bottle_delete, name = "bottle_delete"),
    url(r'^distillery/delete/(?P<distillery_name>\w+)/$', views.distillery_delete, name = "distillery_delete"),
    
    # Edit
    url(r'^bottle/edit/(?P<bottle_id>\d+)/$', views.bottle_edit, name = 'bottle_edit'),
    url(r'^distillery/edit/(?P<distillery_name>\w+)/$', views.distillery_edit, name = 'distillery_edit'),
     
) + static(settings.MEDIA_URL, document_root = settings.MEDIA_ROOT) + static(settings.STATIC_URL, document_root = settings.STATIC_ROOT)
