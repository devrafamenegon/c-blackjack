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
		                                        
		"\tVoc� pode sair a qualquer momento apertando Ctrl + C.\n"
		"\tDivirta-se!, aperte Enter para come�ar......\n"
	);
	
	do{
		start = getchar();
	} while (start != '\n');
	
	startGame();
}

int startGame(void){
	
	int cards[52];
	
	int playerCards[5];
	int botCards[5];
	
	int sumOfPlayerCards = 0;
	int sumOfBotCards = 0;
	
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
}
