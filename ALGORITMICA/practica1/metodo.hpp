#include <vector>


class Metodo{

	private: 
		std::vector<int> vector_;
		int elementos_;

	public:
		inline void setVector(std::vector<int> v){vector_=v;};
		inline std::vector<int> getVector(){return vector_;};

		inline void setElementos(int n){elementos_=n;};
		inline int getElementos(){return elementos_;};

		virtual void ordenar()=0;
};
