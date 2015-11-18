#ifndef MONEDA_HPP
#define MONEDA_HPP

class Moneda{
	private:
		int etiqueta_;
		int valor_;
	public:
		inline void setValor(const int &x){valor_=x;};
		inline void setEtiqueta(const int &x){etiqueta_=x;};

		inline int getValor(){return valor_;};
		inline int getEtiqueta(){return etiqueta_;};

};

#endif