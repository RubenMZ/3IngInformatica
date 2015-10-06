class Publicacion:
	nPublicaciones=0
	def __init__(self, nombre,autor):
		self.n=nombre
		self.a=autor
		self.cod=Publicacion.nPublicaciones
		Publicacion.nPublicaciones+=1

	def nombre(self):
		return self.n

	def autor(self):
		return self.a

	def codigo(self):
		return self.cod

	def ejemplaresTotales(self):
		return self.nPublicaciones

class Comic(Publicacion):
	"""Clase para comics"""
	__nComic=0
	def __init__(self, nombre,autor):
		self.n=nombre
		self.a=autor
		self.cod=Publicacion.nPublicaciones
		Publicacion.nPublicaciones+=1
		Comic.__nComic+=1


	def ejemplares(self):
		return Comic.__nComic

class Libro(Publicacion):
	"""Clase para libros"""
	__nLibro=0
	def __init__(self, nombre,autor):
		self.n=nombre
		self.a=autor
		self.cod=Publicacion.nPublicaciones
		Publicacion.nPublicaciones+=1
		Libro.__nLibro+=1

	def ejemplares(self):
		return Libro.__nLibro


l1=Libro("LALALA", "Calderon")
l2=Libro("LALALA", "Awitaa")
c=Comic("Batman", "DC")
print "Libro: "+l1.nombre()+"; "+" Autor: "+l1.autor()+" con publicaciones: "+str(l1.ejemplares())+" y codigo: "+str(l1.codigo())
print "Libro: "+l2.nombre()+"; "+" Autor: "+l2.autor()+" con publicaciones: "+str(l2.ejemplares())+" y codigo: "+str(l2.codigo())
print "Comic: "+c.nombre()+"; "+" Autor: "+c.autor()+" con publicaciones: "+str(c.ejemplares())+" y codigo: "+str(c.codigo())

print "LIBROS: "+str(l1.ejemplaresTotales())