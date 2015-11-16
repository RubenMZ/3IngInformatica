from django.shortcuts import render
from django.http import HttpResponse, Http404
from Noticias.models import New, Author, Section
from django.template import loader, Context, RequestContext

def index(request):
	lista = New.objects.all()
	plantilla = loader.get_template('Noticias/index.html')
	contexto = RequestContext(request, {'lista': lista,} )
	return HttpResponse(plantilla.render(contexto))

def detail(request, noticia_id):
	try:
		aux = New.objects.get(id=noticia_id)
		descrip = aux.description
	except New.DoesNotExist:
		raise Http404
	return HttpResponse("Descripcion: %s" %descrip)


def noticia_new(request):
	if request.method = 'POST':
		form = NoticiaForm(request.POST, request.FILES)
		if form.is_valid():
			form.save()
			return redirect(reverse_lazy())
	else:
		form=NoticiaForm()
	context = {'form':form}
	return render(request, 'Noticias/form.htmlo', context)
	
