from django.conf.urls import patterns, include, url
from django.contrib import admin
from django.conf import settings
from django.conf.urls.static import static
from django.views.generic import TemplateView

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'MaltAuction.views.home', name = 'home'),
    # url(r'^blog/', include('blog.urls')),
    
    url(r'^$', include('home.urls', namespace = 'home')),
    url(r'^about/$', TemplateView.as_view(template_name = 'about.html'), name = 'about'),
    url(r'^bottles/', include('bottles.urls', namespace = "bottles")),
    url(r'^auction/', include('auction.urls', namespace = "auction")),
    url(r'^users/', include('users.urls', namespace = "users")),
    url(r'^admin/', include(admin.site.urls)),
) + static(settings.MEDIA_URL, document_root = settings.MEDIA_ROOT) + static(settings.STATIC_URL, document_root = settings.STATIC_ROOT)
