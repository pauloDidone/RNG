#include <bitset>
#include <iostream>
#include <fstream>

//parâmetro de controle do numero de cadeis de bits geradas para os 3 geradores
#define nCadeias  1000

using namespace std;

//protótipos das funções
void lfsr_f ();

void lfsr_g ();

void mTwister ();

//função principal que chama em sequencia os 3 geradores
int main()
{
lfsr_f();

lfsr_g();

mTwister();
	
return 0;
}

//gerador lfsr Fibonacci
void lfsr_f (){	
	
	int periodo = 0;	
	bitset<32> seed, lfsr, aux, um;
	seed=4357;	
	lfsr=seed;	
	um = 0b1;	

	ofstream outputFile("lfsr_f.txt");

	do
	{
		//cout << lfsr << endl;
		outputFile << lfsr << endl;
		//configuração dos taps nas posições 32, 22, 2 e 1, conforme polinômio primitivo para 32 bits
	    	aux  = ((lfsr >> 0) ^ (lfsr >> 10) ^ (lfsr >> 30) ^ (lfsr >> 31) ) & um;
	    	lfsr =  (lfsr >> 1) | (aux << 31);
	    	++periodo;
       
	}while (lfsr != seed && periodo!= nCadeias);
	outputFile.close();
	
}

//gerador lfsr Galois
void lfsr_g (){	
	
	int periodo = 0;	
	bitset<32> seed, lfsr, um, aux;
	seed=4357;	
	lfsr=seed;	
	um = 1;
	
	ofstream outputFile("lfsr_g.txt");
	
	do
	{
		//cout << lfsr << endl;
		outputFile << lfsr << endl;
		aux = lfsr & um;   
	    	lfsr >>= 1;              
	    	if (aux==um) {
			//configuração dos taps nas posições 32, 22, 2 e 1, conforme polinômio primitivo para 32 bits	                 
			lfsr ^= 0b10000000001000000000000000000011;
	    	}
	    	++periodo;
	}while (lfsr != seed && periodo!= nCadeias);
	outputFile.close();	
}

//gerador mersenne twister
void mTwister(){
	
	//parâmetros de período  
	int N = 624, M = 397;	
	
	//parâmetro de controle do vetor de trabalho, inicializa logo depois das N sementes iniciais
	static int i=N+1;
	
	bitset<32> W_R_BITS = 0x80000000; // bits  mais significativos
	bitset<32>   R_BITS = 0x7fffffff; // bits menos significativos
	bitset<32>        A = 0x9908b0df; // constante A
	
	bitset<32> um = 0x1;
	bitset<32> mascaraB = 0x9d2c5680;
	bitset<32> mascaraC = 0xefc60000;

	bitset<32> mt[N]; // vetor de trabalho
	bitset<32> saida; //vetor de saida
	bitset<32> matA[2]={0x0, A};		

	//inicializa array com sementes diferentes de zero
	unsigned long seed = 4357, allOne = 0xffffffff;	
	mt[0]= seed & allOne;
	for (int k=1; k<N; k++){
	        mt[k] = (69069 * (int)mt[k-1].to_ulong() ) & allOne;
	}	
	
	//abre arquivo de saída
	ofstream outputFile("mTwister.txt");	
	
	//loop principal. gera nCadeias de numeros binários aleatórios
	for (int j=0; j<nCadeias; j++) {
		//Implementação da fórmula de recorrência do MT. Processa N palavras por vez a apartir de N sementes
		if (i >= N) { 
			int l;
	       		for (l=0;l<N-M;l++) {				
				saida = (mt[l] & W_R_BITS) | (mt[l+1] & R_BITS);				
	       			mt[l] = mt[l+M] ^ (saida >> 1) ^ matA[(int)((saida & um).to_ulong())];
	       		}
	       		for (;l<N-1;l++) {				
	       			saida = (mt[l] & W_R_BITS) | (mt[l+1] & R_BITS);
	       			mt[l] = mt[l+(M-N)] ^ (saida >> 1) ^ matA[(int)((saida & um).to_ulong())];
	       		}
			saida = (mt[N-1] & W_R_BITS) | (mt[0] & R_BITS);
			mt[N-1] = mt[M-1] ^ (saida >> 1) ^ matA[(int)((saida & um).to_ulong())];
			i = 0;

		}	  
		saida = mt[i++];
		saida ^= (saida >> 11);
		saida ^= (saida << 7) & mascaraB;
		saida ^= (saida << 15) & mascaraC;
		saida ^= (saida >> 18); 
		
		//grava linha no arquivo contendo uma cadeia e imprime na tela
		outputFile << saida << endl;
		//cout << saida << endl;
	}
	//fecha arquivo de saída
	outputFile.close();	
}
