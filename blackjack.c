/*
	O blackjack é jogado com 1 a 9 baralhos de 52 cartas cada. Os valores das cartas correspondem ao seu valor numérico de 2 a 10.
	Todas as cartas de figuras (Valete, Dama, Rei) contam 10 e o Ás 1 ou 11, conforme o desejo dos detentores. 
	Um Blackjack (Ás e uma carta cujo valor é 10) supera todas as outras combinações de cartas.
	Ases contam como 1 ou 11, as cartas da Corte contam como 10 e todas as outras cartas têm seu valor nominal.
	Quando o total de um jogador ultrapassar 21 (rejeições), sua aposta no Blackjack será perdida e a Casa renderá.
	Um Blackjack (um ás com uma imagem ou qualquer carta de valor 10) é apenas com as duas primeiras cartas do jogador.
	Na verdade, a maioria dos cassinos agora pede cartas para BJ em pacotes de 6 ou 8 baralhos sem os coringas incluídos.
	Vale a pena reorganizar ou eles vão deixar de fora todos juntos.
	Jokers não contam para nada, a menos que você esteja jogando um jogo especial de blackjack.
	Em segundo lugar, É um ás e um 10 Blackjack? O dealer e cada jogador começam com duas cartas.
	A primeira carta do dealer fica virada para cima, a segunda virada para baixo.
*/

#include <stdio.h>
#include <locale.h>
#include <time.h>

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
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
	
	startGame();
}

void printCard(int cardNumberAndSuit){
	
	char cardSuit = cardNumberAndSuit / 100;
 	int cardNumber = cardNumberAndSuit % 100;
	
	switch (cardNumber)
	{
		case 1: 
		{
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
			printf("*******\n");
			printf("*     *\n");
			printf("* %c   *\n", cardSuit);
			printf("*   K *\n");
			printf("*     *\n");
			printf("*******\n");
			break;
		}
		
		default: {
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

int startGame(void){
	
	system("cls");
	
	int cards[52];
	
	int playerCards[5];
	int botCards[5];
	
	int sumOfPlayerCards = 0;
	int sumOfBotCards = 0;
	
	char aceValue;
	
	//Embaralhando o baralho
	
	int t;
	int i;
	int desk[52];
	
	srand(time(NULL));
	
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
	
	//Passando as cartas ao Jogador
	playerCards[0] = cards[0];
	playerCards[1] = cards[1];
	
	//Passando as cartas ao Bot
	botCards[0] = cards[2];
	botCards[1] = cards[3];
	
	//Uma das cartas do bot
	printf("\nUma das cartas do bot:\n\n");
	printCard(botCards[0]);
	
	//Cartas do jogador
	printf("\nCartas do jogador:\n\n");
	printCard(playerCards[0]);
	printCard(playerCards[1]);
	
	
	for (i = 0; i < 2; i++){
		
		if(playerCards[i] % 100 == 1){
			
			//Definindo o valor do Ás
			printf("Escolha o valor do Ás (carta %d), a) '11' ou b) '1': ");
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
			sumOfPlayerCards += (playerCards % 100);
		}
	}
}
