#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

/**
  * @desc é um pow *-*
*/
unsigned long long Exp(unsigned long long num, int exp){
	unsigned long long saida=1;
	int i;
	for(i=0;i<exp;i++){
		saida*=num;
	}
	return saida;
}

/**
  * @desc encontrar o valor de (num^exp)%mod
	* @prop ((a%n)^t)%n=(a^t)%n
	* @prop a^t=a^t[0]*a^t[1]*a^t[2]... Em que t[0] é o valor do bit mais significativo de t[]
		Exemplo: a^55=a^32*a^16*a^4*a^2*a que é computacionalmente muito mais barato
	* @param unsigned long long $num - valor do bloco
	* @param unsigned long long $exp - o expoente
	* @param unsigned long long $mod - o módulo
  * @return unsigned long long $(saida*prox)%mod - calcula de modo recursivo o valor de (num^exp)%mod
*/
unsigned long long msgExpMod(unsigned long long num, int exp, int mod){
	if(exp>0){
		unsigned long long saida, prox;
		if(exp%2==0){
			saida=1;
		}
		else{
			saida=num;
		}
		//saida=Exp(num, exp%2);
		prox=msgExpMod((num*num)%mod, exp/2, mod);
		return (saida*prox)%mod;
	}
	return 1;
}

/**
  * @desc a funcão transforma o bloco de 3 algarismos para a base 9. Ela é necessária para extinguir o problema que envolve os zeros a esquerda no bloco.
	* Após a codificacão e no momento da decodificacão é impossível recuperar os zeros a esquerda por limitacões da própria linguagem. Para resolver isso,
	* além de transformar os blocos para a base 9 (0 a 8) a funćão soma 111 para extinguir os zeros e se trabalhar somente de 1 a 9
	* @param int $numero - o valor do bloco a ser trocado de baseNoveCustom
  * @return o valor do bloco na base 9 somado a 111
*/
int itoc9(int numero){
	int u, d, c;
	u=numero%9;
	d=(numero/9)%9;
	c=numero/81;
	return 111+c*100+d*10+u;
}

/**
  * @desc encontrar o totiente de modulo
	* @param unsigned long long $modulo - o numero a ser encontrado o totiente
  * @return unsigned long long $totiente - o totiente de modulo
*/
unsigned long long totiente(unsigned long long modulo) {
	unsigned long long moduloalt=modulo, totiente=1;
	int *fatores;
	unsigned long long i;
	fatores = (int *)calloc((modulo/2)+1, sizeof(int));
	for(i=2;i<(modulo/2)+1;i++){
		// checa se moduloalt é múltiplo de i
		if(moduloalt%i==0) {
			moduloalt/=i;
			fatores[i]++;
			i--;
		}
	}
	// percorre fatores[] e calcula totiente pela definicão
	for(i=2;i<(modulo/2)+1;i++){
		if(fatores[i]!=0){
			totiente*=(i-1)*Exp(i, fatores[i]-1);
		}
	}
	free(fatores);
	return totiente;
}

/**
  * @desc converte de base9Custom para base 10
	* @param int $numero - o valor do bloco a ser trocado para a base 10
  * @return o valor do bloco na base 10
*/

int c9toi(int numero){
	int u, d, c;
	u=numero%10-1;
	d=(numero/10)%10-1;
	c=numero/100-1;
	return u+d*9+c*81;
}

/**
  * @desc encontra quantos algarismos um número tem
	* @param int $numero
  * @return $saida - quantidade de algarismos do $numero
*/
int numchar(int numero){
	int saida=1;
	while(numero>=10){
		saida++;
		numero/=10;
	}
	return saida;
}
