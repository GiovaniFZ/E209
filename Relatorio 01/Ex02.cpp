#include <iostream>
#include <iomanip>

using namespace std;
int main(){
	int n;
	int i;
	
	cin >> n;
	
	if(n >= 0 || n <= 50){
	
	for(i = n-1; i > 0; i--){
		cout << "Resto da divisao de " << n << " por " << i << ": " << n%i << endl;
		} 		
	}else{
		cout << "O numero deve ser entre 0 e 50!" << endl;
	}
	
	return 0;
}