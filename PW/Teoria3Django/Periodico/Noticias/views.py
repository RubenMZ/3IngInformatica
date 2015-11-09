from django.shortcuts import render
from django.http import HttpResponse
from Noticias.models import New, Author, Section
from django.template import loader, Context, RequestContext

def index(request):
	lista = New.objects.all()
	plantilla = loader.get_template('Noticias/index.html')
	contexto = RequestContext(request, {'lista': lista,} )
	return HttpResponse(plantilla.render(contexto))

def detail(request, noticia_id):
	aux = New.objects.get(id=noticia_id)
	title = aux.title
	descrip = aux.description
	return HttpResponse("Descripcion: %s" %descrip)
