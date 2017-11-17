#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <set>
#include <unordered_map>
#include <random>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;


class Nodo {
	private:
		string IpPropia;
		string PuertoPropio;

	public:
		string getIpPropia(){
			return IpPropia;
		}
		string getPuertoPropio(){
			return PuertoPropio;
		}
		void setIpPropia(string n){
			IpPropia = n;
		}
		void setPuertoPropio(string n){
			PuertoPropio = n;
		}
};



int main(){
	context ctx;
	unordered_map<string, string> Lista;
	Nodo Central;
	socket S_Espera(ctx,socket_type::rep);
	socket S_Envio(ctx,socket_type::req);

	Central.setIpPropia("tcp://localhost:");
	Central.setPuertoPropio("5500");

	string Direccion  = "tcp://*:" + Central.getPuertoPropio();

	S_Espera.bind(Direccion);
	while (true){
		message M;
		S_Espera.receive(M);
		string Accion;
		cout <<"gola: "<<Direccion <<endl;
		M >> Accion;

		if (Accion == "Ingresar"){
				string llave, Dato;
				M >> llave;
				M >> Dato;
				Lista[llave] = Dato;
				message R;
				R << "Nodo Agregado";
				S_Espera.send(R);
		}
	}

}
