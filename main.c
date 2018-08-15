#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"funcoes.h"

int main() {
  srand(time(NULL));
	char *mensagemd, letrad;
	int flagd=0, count=0;
	mensagemd=(char *)malloc(sizeof(char));

	// Pega a mensagemd
  printf("Digite a mensagem e os primos\n");
  printf("Exemplo: \"mensagem\" 29 31\n");
	while(1){
		scanf("%c", &letrad);
		if(letrad=='"'&&flagd==1){
			break;
		}
		if(letrad=='"'){
			flagd++;
			continue;
		}
		if(flagd==1){
			count++;
			mensagemd=(char *)realloc(mensagemd, count);
			mensagemd[count-1]=letrad;
		}
	}
	int p, q;
	// Le p e q
	scanf("%d %d", &p, &q);
	// Define as variáveis n, totiente(n)
	unsigned long long n=p*q, t=(p-1)*(q-1), e, j, mdc;
	int i;
	// Encontra valor de e que é o menor primo entre si com totiente(n)
	for(e=2;e<t;e++){
		mdc=1;
		for(j=2;j<=e;j++){
			if(e%j==0&&t%j==0){
				mdc=j;
				break;
			}
		}
		if(mdc==1){
			break;
		}
	}
	char *ascii;
	int baseNoveCustom;
	ascii=(char *)malloc(3*count*sizeof(char));
	// Transforma char em valor número na base 9custom (de 1 a 9)
	for(i=0;i<count;i++){
		baseNoveCustom=itoc9(mensagemd[i]);
		ascii[3*i]=baseNoveCustom/100+48;
		ascii[3*i+1]=(baseNoveCustom/10)%10+48;
		ascii[3*i+2]=baseNoveCustom%10+48;
	}
	// Comeca a printar os blocos
	printf("\n\"");
	int pointer=0, random;
	char *blocod;
	blocod=(char *)malloc(3*sizeof(char));
	// Utiliza o vetor ascii completo da mensagemd e quebra em blocods de tamanho 1 a 3 e codifica utilizando o expoente 'e' e o módulo 'n'
	while(1){
		random=rand()%3+1;
		if(pointer+random<=count*3){
			if(random==3){
				blocod[0]=ascii[pointer];
				blocod[1]=ascii[pointer+1];
				blocod[2]=ascii[pointer+2];
			}
			else if(random==2){
				blocod[0]='0';
				blocod[1]=ascii[pointer];
				blocod[2]=ascii[pointer+1];
			}
			else{
				blocod[0]='0';
				blocod[1]='0';
				blocod[2]=ascii[pointer];
			}
			if((unsigned int)atoi(blocod)>=t){
				continue;
			}
//*******************************

				printf("%llu", msgExpMod((unsigned long long)atoi(blocod), e, n));
//*******************************
			pointer+=random;
			if(pointer==count*3){
				break;
			}
			printf(" ");
		}
	}
	// encontra a segunda chave privada 'd' (que é inverso multiplicativo de 'e' módulo 't')
	/* O Teorema de Euler afirma que dado dois números a e n primos entre si:
	 a^(totiente(n)) é congruente a 1 módulo n então, podemos afirmar que
	 a^(totiente(n)-1) é inverso multiplicativo de a módulo n pois
	 a^(totiente(n)) = a*a^(totiente(n)-1)
 */
	unsigned long long d=msgExpMod(e, totiente(p-1)*totiente(q-1)-1, t);
	/*for(d=2;;d++){
		//printf("como ta o d? %llu\n", d);
		if((e*d)%t==1){
			break;
		}
	}*/
	printf("\" '.' %llu %llu\n", n, d);
  printf("Mensagem criptografada, caractere especial e chave\n");

  ///////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////

  /*
		* @param $entrada - conjunto de blocos
		* @param $bloco - um bloco
		* @param $mensagem - conjunto de blocos decodificados
	*/
	char *entrada, *mensagem, *bloco, letra;
	int flag=0, ecount=0, bcount=0, mcount=0;
	entrada=(char *)malloc(sizeof(char));
	bloco=(char *)malloc(sizeof(char));
	mensagem=(char *)malloc(sizeof(char));

	// Lê o conjunto de blocos ($entrada)
  printf("\nDigite a mensagem, o caractere especial e a chave\n");
  printf("Exemplo: \"771 250 44 516\" '.' 899 611\n");
	while(1){
		scanf("%c", &letra);
		if(letra=='"'&&flag==1){
			break;
		}
		if(letra=='"'){
			flag++;
			continue;
		}
		if(flag==1){
			ecount++;
			entrada=(char *)realloc(entrada, ecount);
			entrada[ecount-1]=letra;
		}
	}
	ecount++;
	entrada=(char *)realloc(entrada, ecount);
	entrada[ecount-1]=' ';
	char id[3];
	// unsigned long long n, d; COMENTEI AQUI
	// Lê 'n' e 'd'
	scanf("%s %llu %llu", id, &n, &d);
	// int count=0, baseNoveCustom; COMENTEI AQUI
  count=0;
	int num;
	// Pega os blocos, decodifica e escreve na $mensagem
	while(1){
		if(count==ecount){
			break;
		}
		letra=entrada[count];
		// printf("%c", letra);
		count++;
		if(letra==' '){
			// printf(".%s. ", bloco);
			//baseNoveCustom=(int)rsa_modExp((long long)atoi(bloco), (long long)d, (long long)n);
			// decodifica o bloco
			baseNoveCustom=(int)msgExpMod((unsigned long long)atoi(bloco), d, n);
			//baseNoveCustom=(int)((long long int)atoi(bloco)^d)%(long long int)n;
			num=numchar(baseNoveCustom);
			mcount+=num;
			mensagem=(char *)realloc(mensagem, mcount);
			if(num==3){
				mensagem[mcount-1]=baseNoveCustom%10+48;
				mensagem[mcount-2]=(baseNoveCustom/10)%10+48;
				mensagem[mcount-3]=baseNoveCustom/100+48;
			}
			else if(num==2){
				mensagem[mcount-1]=baseNoveCustom%10+48;
				mensagem[mcount-2]=(baseNoveCustom/10)%10+48;
			}
			else{
				mensagem[mcount-1]=baseNoveCustom%10+48;
			}
			bcount=0;
			continue;
		}
		bcount++;
		bloco=(char *)realloc(bloco, bcount+1);
		//printf("\nadicionei %c ao bloco, tamanho do bloco: %d\n", letra, bcount);
		bloco[bcount-1]=letra;
		bloco[bcount]='\0';
	}
	// printf("\n%s\n", mensagem);
	// int i; COMENTEI AQUI
	printf("\nMensagem decodificada:\n\"");
	for(i=0;i<mcount/3;i++){
		printf("%c", c9toi((mensagem[3*i]-48)*100+(mensagem[3*i+1]-48)*10+mensagem[3*i+2]-48));
	}
	printf("\"\n\n");


  return 0;
}
