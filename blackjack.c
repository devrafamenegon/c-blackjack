/*
	O blackjack é jogado com 1 a 9 baralhos de 52 cartas cada. Os valores das cartas correspondem ao seu valor numérico de 2 a 10.
	Todas as cartas de figuras (Valete, Dama, Rei) valem 10 e o Ás 1 ou 11, conforme o desejo dos detentores. 
	
	Resumindo... Ases contam como 1 ou 11, as cartas da Corte contam como 10 e todas as outras cartas têm seu valor nominal.
	
	Um Blackjack (Ás e uma carta cujo valor é 10) supera todas as outras combinações de cartas.
	
	Quando o total de um jogador ultrapassar 21 (rejeições), sua aposta no Blackjack será perdida.
	Um Blackjack (um ás com uma imagem ou qualquer carta de valor 10) é apenas com as duas primeiras cartas do jogador.
	
	Jokers não contam para nada, a menos que você esteja jogando um jogo especial de blackjack.
	O dealer e cada jogador começam com duas cartas.
	A primeira carta do dealer fica virada para cima, a segunda virada para baixo.
*/

#include <stdio.h>
#include <locale.h>
#include <time.h>
#include "blackjack.h"

int checkPlayerGameSituation(int sumOfPlayerCards){
	if(sumOfPlayerCards > 21){
		printf("Dealer Venceu!\n");
		return 1;
	}
	
	else if(sumOfPlayerCards == 21){
		printf("Soma das cartas 21, Você Venceu!\n");
		return 2;
	}
	
	else {
		return 0;
	}
}

//Função para printar as cartas em tela
void printCard(int cardNumberAndSuit){
	
	char cardSuit = cardNumberAndSuit / 100;
 	int cardNumber = cardNumberAndSuit % 100;
	
	switch (cardNumber)
	{
		case 1: 
		{
			//Ás
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", cardSuit);
			printf("*   A *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}		
		
		case 11:
		{
			//Valete
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", cardSuit);
			printf("*   J *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		
		case 12:
		{
			//Dama
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", cardSuit);
			printf("*   Q *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		
		case 13:
		{
			//Rei
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", cardSuit);
			printf("*   K *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		
		default: 
		{
			//Cartar numéricas
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", cardSuit);
			printf("*  %2d *\n", cardNumber);
			printf("*     *\n");
			printf("*******\n");
			break;
		}
	}
}

//Função para embaralhar as cartas
int shuffle(int cards[]){
	
	int t;
	int i;
	int desk[52];
		
	for (i = 0; i < 52; i++){
		desk[i] = ( i/13 + 3 ) * 100 + i % 13 + 1;
	}
	
	srand(time(NULL));
	
	for (i = 0; i < 52; i++)
	{
		do
		{
			t = rand() % 52;
		} while (desk[t] == 0);

		cards[i] = desk[t];
		desk[t] = 0;
	}
	
	return 0;
}

//Função de início de jogo (separada da main para podermos reiniciar o jogo facilmente)
void startGame(void){
	
	int cards[52];
	
	int playerCards[5];
	int dealerCards[5];
	
	int sumOfPlayerCards = 0;
	int sumOfdealerCards = 0;
	
	char aceValue;
	int i;
	
	char start;
	
	printf(
		"\n\tBem vindo ao\n\n\t"
		"88          88                       88        88                       88\n\t"         
		"88          88                       88        ''                       88\n\t"         
		"88          88                       88                                 88\n\t"       
		"88,dPPYba,  88 ,adPPYYba,  ,adPPYba, 88   ,d8  88 ,adPPYYba,  ,adPPYba, 88   ,d8\n\t"  
		"88P      8a 88        `Y8 a8         88 ,a8    88        `Y8 a8         88 ,a8\n\t"    
		"88       d8 88 ,adPPPPP88 8b         8888[     88 ,adPPPPP88 8b         8888[\n\t"      
		"88b,   ,a8  88 88,    ,88  8a,   ,aa 88  Yba,  88 88,    ,88  8a,   ,aa 88  Yba,\n\t"   
		"8Y Ybbd8    88   8bbdP Y8    Ybbd8   88    Y8a 88   8bbdP Y8    Ybbd8   88    Y8a\n\t" 
		"                                             ,88\n\t"                                 
		"                                            888P\n\n"
		                                        
		"\tVocê pode sair a qualquer momento apertando Ctrl + C.\n"
		"\tDivirta-se!, aperte Enter para começar......"
	);
	
	do{
		start = getchar();
	} while (start != '\n');
	
	system("cls");
	
	//Embaralhando o baralho
	shuffle(cards);
	
	//Passando as cartas ao jogador
	playerCards[0] = cards[0];
	playerCards[1] = cards[1];
	
	//Passando as cartas ao Dealer
	dealerCards[0] = cards[2];
	dealerCards[1] = cards[3];
	
	//Uma das cartas do dealer
	printf("\nUma das cartas do dealer:\n\n");
	printCard(dealerCards[0]);
	
	//Cartas do jogador
	printf("\nCartas do jogador:\n\n");
	printCard(playerCards[0]);
	printCard(playerCards[1]);
	
	//laço para verificar e somar o valor das cartas do jogador
	for (i = 0; i < 2; i++){
		
		if(playerCards[i] % 100 == 1){
			//Definindo o valor do Ás
			printf("\nEscolha o valor do Ás (carta %d), a) '11' ou b) '1': ", i + 1);
			do {
				aceValue = getchar();
			} while (aceValue != 'a' && aceValue != 'b');
			
			//Ás valendo 11
			if(aceValue == 'a'){
				sumOfPlayerCards += 11;
			}
			
			//Ás valendo 1
			else {
				sumOfPlayerCards += 1;
			}
		}
		
		//Somando o valor do rei, dama ou valete
		else if(playerCards[i] % 100 > 10){
			sumOfPlayerCards += 10;
		}
		
		//Somando o valor das cartas numéricas
		else {
			sumOfPlayerCards += (playerCards[i] % 100);
		}
	}
	
	printf("\nSoma das cartas do Jogador: %d\n\n", sumOfPlayerCards);
	
	checkPlayerGameSituation(sumOfPlayerCards);
	
	//Caso o jogador queira mais cartas
	for (i = 0; i < 3; i++){
		char moreCards;
		
		printf("Deseja receber mais cartas? Digite 's' ou 'n': ");
		
		do{
			moreCards = getchar();
		} while(moreCards != 's' && moreCards != 'n');
		
		if(moreCards == 's'){
			playerCards[i + 2] = cards[i + 4];
			printf("\n\nVocê recebeu outra carta!\n");
			printf("Sua %d° carta é:\n\n", i + 3);
			printCard(playerCards[i + 2]);
		}
		
		else {
			return;
		}
		
		if(playerCards[i + 2] % 100 == 1){
			
			//Definindo o valor do Ás
			printf("\nEscolha o valor do Ás (carta %d), a) '11' ou b) '1': ", i + 1);
			do {
				aceValue = getchar();
			} while (aceValue != 'a' && aceValue != 'b');
			
			//Ás valendo 11
			if(aceValue == 'a'){
				sumOfPlayerCards += 11;
			}
			
			//Ás valendo 1
			else {
				sumOfPlayerCards += 1;
			}
		}
		
		//Somando o valor do rei, dama ou valete
		else if(playerCards[i + 2] % 100 > 10){
			sumOfPlayerCards += 10;
		}
		
		//Somando o valor das cartas numéricas
		else {
			sumOfPlayerCards += (playerCards[i + 2] % 100);
		}
		
		printf("\nSoma das cartas do Jogador: %d\n\n", sumOfPlayerCards);
		
		int playerGameSituation = checkPlayerGameSituation(sumOfPlayerCards);
		
		if(playerGameSituation != 0) return;
	}
	
	if (i == 3)
	{
		printf("Parabéns, você venceu! Pois a soma de suas 5 cartas não ultrapassou 21.\n");
		return;
	}
}

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
	char again;
	
	startGame();
	
	printf("\nDeseja jogar novamente? Digite 's' ou 'n':\n");
	do{
		again = getchar();
	} while (again!='s' && again!='n');
   
	if (again == 's')
	{
		main();
	}
  
	return 0;
}
