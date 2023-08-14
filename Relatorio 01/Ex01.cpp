#include <iostream>
#include <iomanip>

using namespace std;
int main(){
	int numLaranjas = 0;
	float resultado = 0;
	
	cin >> numLaranjas;
			
	if(numLaranjas < 12){
		cout << "Preco da unidade: R$0.80" << endl;
		resultado = numLaranjas*0.8;
	}else{
		resultado = numLaranjas*0.65;
		cout << "Preco da unidade: R$0.65" << endl;
	}
	cout << fixed << setprecision(2) << "Preco total: R$" << resultado << endl;
	return 0;
}