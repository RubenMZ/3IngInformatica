#ifndef DETERMINANTERECURSIVO_HPP
#define DETERMINANTERECURSIVO_HPP

#include "matriz.hpp"

template <class T>
class DeterminanteRecursivo{

	public:
		
		T determinanteRecursivo(const Matriz <T> &m, const int &n){
			double det=0, p=0, h=0, k=0, i=0, j=0;
		 	Matriz<T> temp(n,n);

			if(n==1) {
				return m.elemento(1,1);
			} else 
				if(n==2) {
				 	det=(m.elemento(1,1)*m.elemento(2,2)-m.elemento(1,2)*m.elemento(2,1));
					return det;
				} else {
				 	for(p=1;p<=n;p++) {
				 		h = 1;
				 		k = 1;
				 		for(i=2;i<=n;i++) {
							 for( j=1;j<=n;j++) {
							 	if(j==p) {
							 		continue;
							 	}
							 	temp.elemento(h,k,m.elemento(i,j));
							 	k++;
							 	if(k==n) {
							 		h++;
							 		k = 1;
							 	}
							 }
				 		}
				 		det=det+m.elemento(1,p)*pow(-1,p)*determinanteRecursivo(temp,n-1);
				 	}
					 return (-1)*det;
			 	}

		}
		inline DeterminanteRecursivo(){};
		inline ~DeterminanteRecursivo(){};
};

#endif