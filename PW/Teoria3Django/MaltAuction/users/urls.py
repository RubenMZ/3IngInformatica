from django.conf.urls import patterns, url
from django.core.urlresolvers import reverse
from django.contrib.staticfiles.urls import staticfiles_urlpatterns
from django.conf.urls.static import static
from django.conf import settings
from users.views import RegisterUser, LoginUser, LogoutUser, UpdateProfile

urlpatterns = patterns('',
    url(r'^register/$', RegisterUser.as_view(), name = "register"),
    url(r'^update/(?P<pk>\d+)/$', UpdateProfile.as_view(), name = "update"),
    url(r'^login/$', LoginUser.as_view(), name = 'login'),
    url(r'^logout/$', LogoutUser.as_view(), name = 'logout'),
    url(r'^change_passwd/', 'django.contrib.auth.views.password_change', 
        {'template_name':'users/passwd_change_form.html', 'post_change_redirect' : 'home:home'}, name = "change_passwd"), 
) + static(settings.MEDIA_URL, document_root = settings.MEDIA_ROOT) + static(settings.STATIC_URL, document_root = settings.STATIC_ROOT)
