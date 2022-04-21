#include <iostream>
#include <string>
#include <conio.h>
#include "Events.h"
using namespace std;
bool winCondition(int gameMode, Person players[], int numPlayer, int round);
void playGame(Person player[], int numPlayers, int gameMode);
void leaderBoard(Person player[], int numPlayers);
void startGame(Person player[]);
void startMenu(Person player[]);
void turnSkipped(Person* player);
void extraTurn(Person* player);
void finalScoreBoard(Person player[], int numPlayers);
void gameSetup(Person player[]);
void TurnBasedModifier(Person* player);
void putInTurnsMod(Person* player, int num, double mod);
int checkNumber();

void extraTurn(Person* player)
{
	player->turn++;
	cout << endl << "You gained an extra turn this round!!" << endl << endl;
}
void turnSkipped(Person* player)
{
	player->turn--;
	if (player->turn == 0)
	{
		cout << "Sorry you lost a turn but you'll be back in the action next round!\n";
	}
	else
		cout << "Sorry you lost a turn just " << player->turn << " more to go!\n";
}
void startGame(Person player[])
{
	char choice = 'y';
	do {
		gameSetup(player);
		cout << endl << endl << "Would you like to play again? If Yes enter Y if No type N\n";
		cin >> choice;
		choice = toupper(choice);
	} while (choice != 'N');
}
int checkNumber() //makes sure the item being put in is an int if not it clears it from memory and asks for input again
{
	int number = 0;
	while (!(cin >> number)) {
		cin.clear(); //clears from memory
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	}
	return number;
}
void gameSetup(Person player[])
{
	int numPlayers;
	int gameMode;
	int status;

	string modeArray[3] = { "Normal Mode first to $10000","Quickplay highest score at the end of 10 rounds","Endless goes forever" };
	cout << "Enter the number of players 1 - " << gn << ": \n";
	numPlayers = _getch() - '0';

	while (numPlayers < 1 || numPlayers > gn)
	{
		cout << "Sorry try again must be 1 - " << gn << "!" << endl;
		numPlayers = _getch() - '0';
	}

	cout << "Which game mode would you like to play.\n" << "1) for Normal Play first to $10000.\n"
		<< "2) for Quick Play 10 rounds.\n" << "3) for Endless.\n";
	gameMode = _getch() - '0';

	while (gameMode < 1 || gameMode > 3)
	{
		cout << "Sorry try again must be 1 or 2 or 3!" << endl;
		gameMode = _getch() - '0';
	}
	cout << endl << "You picked " << numPlayers << " players, " << modeArray[gameMode - 1] << "." << endl;
	cout << "There will be " << gn - numPlayers << " NPC player(s)." << endl;
	system("pause");
	status = gn - numPlayers;
	numPlayers = gn - 1; // keeps it aligned with the array being 0-3
	for (int i = 0; i < status; i++)
		player[numPlayers - i].status = 1;
	for (int j = 0; j <= gn; j++)
		player[j].index = j;
	playGame(player, numPlayers, gameMode);
}
void startMenu(Person player[])
{
	char choice;
	cout << "Start The Game?\nY/N\n";
	choice = _getch();
	choice = toupper(choice);
	while (choice != 'Y' && choice != 'N')
	{
		cout << "Enter Y to play or N to quit" << endl;
		choice = _getch();
		choice = toupper(choice);
	}
	switch (choice)
	{
	case 'Y':
		startGame(player);
		break;
	case 'N':
		//quit
		exit(0);
		break;
	}
}
void quit(bool& run)
{
	run = false;
	return;
}
void finalScoreBoard(Person player[], int numPlayers)
{
	string place[gn] = { "First","Second","Third","Fourth" };
	Person* array = BubbleSort(player, numPlayers);
	int playerNumber = array[0].index;
	cout << endl << "Congratulations Player #" << playerNumber + 1 << " you won!!!!" << endl;
	for (int i = 0; i <= numPlayers; i++)
	{
		cout << place[i] << " place player #" << array[i].index + 1 << "'s total" << "\t-----\t" << array[i].money << endl;
	}
	system("pause");
}


void leaderBoard(Person player[], int numPlayers)
{
	string place[gn] = { "First","Second","Third","Fourth" };
	Person* array = BubbleSort(player, numPlayers);
	for (int i = 0; i <= numPlayers; i++)
	{
		cout << place[i] << " place player #" << array[i].index + 1 << "'s total" << "\t-----\t" << array[i].money << endl;
	}
}


void playGame(Person player[], int numPlayers, int gameMode)
{
	Events event;
	int random;
	int count = 0;
	int choice = 0;
	int win = true;
	bool status = true;
	while (win)
	{
		int i = 0;
		for (i; i <= numPlayers; i++)
		{
			system("cls");
			cout << endl << endl << "------------------------------------- Player #" << i + 1
				<< "---------------------------------\n";
			if (player[i].turn <= 0)
			{
				status = true;
				while (player[i].turn <= 0 && status)
				{
					TurnBasedModifier(&player[i]);
					choice = rand() % 110;
					if (choice < 50) choice = 1;
					else if (choice < 60) choice = 2;
					else if (choice < 70) choice = 3;
					else if (choice < 80)  choice = 4;
					else if (choice < 90) choice = 5;
					else if (choice < 100) choice = 6;
					else choice = 7;
					switch (choice)
					{
					case 1:
						event.Sales(&player[i]);
						break;
					case 2:
						event.Robbery(&player[i]);
						break;
					case 3:
						event.GoodRandomEvent(&player[i]);
						break;
					case 4:
						event.Audit(&player[i]);
						break;
					case 5:
						event.Fire(&player[i]);
						break;
					case 6:
						event.SocialMedia(&player[i]);
						break;
					case 7:
						event.BonusRound(&player[i]);
						break;
					}
					if (player[i].turn < 0) extraTurn(&player[i]);
					else status = false;
				}
			}
			else turnSkipped(&player[i]);
			system("pause");
		}
		count++;
		system("cls");
		cout << endl << endl << "Leader Board at the end of round # " << count << endl;
		leaderBoard(player, numPlayers);
		event.EndRoundEvent(player, numPlayers);
		system("pause");
		win = winCondition(gameMode, player, numPlayers, count);
	}
	system("cls");
	finalScoreBoard(player, numPlayers);
}


void putInTurnsMod(Person* player, int num, double mod)
{
	bool status = true;
	double total = mod / 100;
	int i = 0;
	for (int i = 0; i < gn; i++)
	{
		if (player->array[i].modTurns == 0 && status)
		{
			player->array[i] = { num,total,true };
			status = false;
		}
	}
}


void TurnBasedModifier(Person* player)
{
	for (int i = 0; i < gn; i++)
	{
		if (player->array[i].modCheck && player->array[i].modTurns == 0)
		{
			player->modifier -= player->array[i].modifier;
			player->array[i].modCheck = false;
		}
		if (player->array[i].modTurns > 0)
		{
			if (player->array[i].modCheck)
				player->modifier += player->array[i].modifier;
			player->array[i].modCheck = false;
			if (player->array[i].modTurns == 1)
				player->array[i].modCheck = true;
			player->array[i].modTurns--;
		}
	}
}


bool winCondition(int gameMode, Person players[], int numPlayer, int round)
{
	switch (gameMode)
	{
	case 1: //normal play
			//check win condition: money = $10K
		for (int i = 0; i < numPlayer; i++)
		{
			if (players[i].money >= 10000)
				return false;
		}
		return true;
	case 2: //quick play
			//check win condition: rounds = 10
		if (round >= 10)
		{
			return false;
		}
		return true;
	case 3:
		return true;
	}
}


int main()
{
	Person player[gn];
	srand(time(NULL));
	startMenu(player);
	system("pause");
	return 0;
}

