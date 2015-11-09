from django.conf.urls import patterns, include, url

from Noticias import views

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'Periodico.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^$', views.index, name='index'),
    url(r'^(?P<noticia_id>\d+)/$', views.detail, name = 'detail')
)
