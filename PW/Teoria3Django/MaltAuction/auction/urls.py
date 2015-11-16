from django.conf.urls import patterns, url
from django.core.urlresolvers import reverse
from django.contrib.staticfiles.urls import staticfiles_urlpatterns
from django.conf.urls.static import static
from django.conf import settings
from auction.views import CurrentAuctionList

urlpatterns = patterns('',
    url(r'^list/$', CurrentAuctionList.as_view(), name = "list"),
) + static(settings.MEDIA_URL, document_root = settings.MEDIA_ROOT) + static(settings.STATIC_URL, document_root = settings.STATIC_ROOT)
