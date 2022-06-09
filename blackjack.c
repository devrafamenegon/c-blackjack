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

void checkGameSituation(int sumOfPlayerCards, int sumOfDealerCards, int* gameStatus){
	if(sumOfDealerCards > 21){
		printf("Soma das cartas do Dealer maior que 21, Jogador Venceu!\n");
		gameStatus = 0;
		restartGame();
	}
	
	else if(sumOfDealerCards == 21){
		printf("Soma das cartas 21, Dealer Venceu!\n");
		gameStatus = 0;
		restartGame();
	}
	
	if(sumOfPlayerCards > 21){
		printf("Soma das cartas do Jogador maior que 21, Dealer Venceu!\n");
		gameStatus = 0;
		restartGame();
	}
	
	else if(sumOfPlayerCards == 21){
		printf("Soma das cartas 21, Você Venceu!\n");
		gameStatus = 0;
		restartGame();
	}
}

//Função para transformar valete, rei e dama para um valor 10
int standardizeValueOfRealCards(int carta)
{
	if ((carta % 100 == 11) ||(carta % 100 == 12) ||(carta % 100 == 13)){
		return (carta / 100) * 100 + 10;
	}
	else {
		return carta;
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
			printf(" _____ \n");
			printf("¦     ¦\n");
			printf("¦%c    ¦\n", cardSuit);
			printf("¦  A  ¦\n");
			printf("¦    %c¦\n", cardSuit);
			printf("¦_____¦\n");
			break;
		}	
		
		case 11:
		{
			//Valete
			printf(" _____ \n");
			printf("¦     ¦\n");
			printf("¦ %c   ¦\n", cardSuit);
			printf("¦  J  ¦\n");
			printf("¦    %c¦\n", cardSuit);
			printf("¦_____¦\n");
			break;
		}
		
		case 12:
		{
			//Dama
			printf(" _____ \n");
			printf("¦     ¦\n");
			printf("¦ %c   ¦\n", cardSuit);
			printf("¦  Q  ¦\n");
			printf("¦    %c¦\n", cardSuit);
			printf("¦_____¦\n");
			break;
		}
		
		case 13:
		{
			//Rei
			printf(" _____ \n");
			printf("¦     ¦\n");
			printf("¦%c    ¦\n", cardSuit);
			printf("¦  K  ¦\n");
			printf("¦    %c¦\n", cardSuit);
			printf("¦_____¦\n");
			break;
		}
		
		default: 
		{
			//Cartar numéricas
			printf(" _____ \n");
			printf("¦     ¦\n");
			printf("¦%c    ¦\n", cardSuit);
			printf("¦ %2d  ¦\n", cardNumber);
			printf("¦    %c¦\n", cardSuit);
			printf("¦_____¦\n");
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
void startGame(){
	
	int cards[52];
	
	int playerCards[5];
	int dealerCards[5];
	
	int sumOfPlayerCards = 0;
	int sumOfDealerCards = 0;
	
	char aceValue;
	int gameStatus = 1;
	int i;
	
	char start;
	
	printf(
		"\nBem vindo ao\n\n"
		"88          88                       88        88                       88\n"         
		"88          88                       88        ''                       88\n"         
		"88          88                       88                                 88\n"       
		"88,dPPYba,  88 ,adPPYYba,  ,adPPYba, 88   ,d8  88 ,adPPYYba,  ,adPPYba, 88   ,d8\n"  
		"88P      8a 88        `Y8 a8         88 ,a8    88        `Y8 a8         88 ,a8\n"    
		"88       d8 88 ,adPPPPP88 8b         8888[     88 ,adPPPPP88 8b         8888[\n"      
		"88b,   ,a8  88 88,    ,88  8a,   ,aa 88  Yba,  88 88,    ,88  8a,   ,aa 88  Yba,\n"   
		"8Y Ybbd8    88   8bbdP Y8    Ybbd8   88    Y8a 88   8bbdP Y8    Ybbd8   88    Y8a\n" 
		"                                             ,88\n"                                 
		"                                            888P\n\n"
		                                        
		"Você pode sair a qualquer momento apertando Ctrl + C.\n"
		"Divirta-se!, aperte Enter para começar......"
	);
	
	do{
		start = getchar();
	} while (start != '\n');

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
	
	printf("\nSoma das cartas do Jogador: %d\n", sumOfPlayerCards);
	
	checkGameSituation(sumOfPlayerCards, sumOfDealerCards, &gameStatus);
	
	//Caso o jogador queira mais cartas
	for (i = 0; i < 3; i++){
		char moreCards;
		
		printf("\nDeseja receber mais cartas? Digite 's' ou 'n': ");
		
		do{
			moreCards = getchar();
		} while(moreCards != 's' && moreCards != 'n');
		
		if (moreCards == 's'){
			playerCards[i + 2] = cards[i + 4];
			printf("\nVocê recebeu outra carta!\n");
			printf("Sua %d° carta é:\n", i + 3);
			printCard(playerCards[i + 2]);
			
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
			
			checkGameSituation(sumOfPlayerCards, sumOfDealerCards, &gameStatus);
		}
		
		else {
			printf("\nSoma das cartas do Jogador: %d\n\n", sumOfPlayerCards);
			break;
		}
	}
	
	if (i == 3 && sumOfPlayerCards <= 21)
	{
		printf("Parabéns, você venceu! Pois a soma de suas 5 cartas não ultrapassou 21.\n");
		return;
	}
	
	//as 2 cartas do dealer
	//i = 0;
	printf("Cartas do Dealer:\n");
	printCard(dealerCards[0]);
	printCard(dealerCards[1]);

	if (dealerCards[0] % 100 + dealerCards[1] % 100 == 2)
	{
		sumOfDealerCards = 12; //2 ás
	}
	else if ((standardizeValueOfRealCards(dealerCards[0])) % 100 + (standardizeValueOfRealCards(dealerCards[1])) % 100 == 1)
	{
		sumOfDealerCards = 21;
		printf("Dealer Venceu!\n");
		return;
	}
	else if (dealerCards[0] % 100 == 1 || dealerCards[1] % 100 == 1)
	{
		sumOfDealerCards = (dealerCards[0] + dealerCards[1]) % 100 + (rand() % 2) * 10;
	}
	else
	{
		sumOfDealerCards = (standardizeValueOfRealCards(dealerCards[0])) % 100 + (standardizeValueOfRealCards(dealerCards[1])) % 100;
	}
	
	printf("Soma das cartas do dealer: %d\n\n", sumOfDealerCards);
	
	//Caso o Dealer tenha a soma de cartas < 17
	//i=0;
	for (i = 0; i < 3 && sumOfDealerCards < 17; i++)
	{
		dealerCards[i + 2] = cards[i + 7];
		printf("O Dealer escolheu comprar\n");
		printf("Sua %d° carta é:\n", i + 3);
		printCard(dealerCards[i + 2]);
		
		if (dealerCards[i + 2] % 100 == 1)
		{
			if (sumOfDealerCards + 11 <= 21)
			{
				printf("Dealer escolheu o Ás valendo 11\n");
				sumOfDealerCards += 11;
			}
			else
			{
				printf("Dealer escolheu o Ás valendo 1\n");
				sumOfDealerCards += 1;
			}
		}
		
		else if(dealerCards[i + 2] % 100 > 10){
			sumOfDealerCards += 10;
		}
			
		//Somando o valor das cartas numéricas
		else {
			sumOfDealerCards += (dealerCards[i + 2] % 100);
		}
		
		printf("Soma das cartas do dealer:%d\n\n", sumOfDealerCards);
	}
	
	if (i == 3 && sumOfDealerCards <= 21)
	{
		printf("Vitória do Dealer! Pois a soma de suas 5 cartas não ultrapassaram 21.\n");
		return;
	}
	
	//Finalizando...
	if (sumOfDealerCards > 21 || sumOfPlayerCards > sumOfDealerCards)
	{
		printf("Jogador Venceu!\n");
		return;
	}
	else if (sumOfPlayerCards == sumOfDealerCards)
	{
		printf("Jogador e Dealer empataram!\n");
		return;
	}
	else if (sumOfPlayerCards < sumOfDealerCards)
	{
		printf("Dealer Venceu!\n");
		return;
	}
		
	return;
}

void restartGame(){
	char again;
	
	printf("\nDeseja jogar novamente? Digite 's' ou 'n':\n");
	do{
		again = getchar();
	} while (again != 's' && again != 'n');
   
	if (again == 's')
	{
		main();
	}
  
	return;
}

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
	startGame();
	restartGame();
}
