
#ifndef EVENTS_H
#define EVENTS_H
#include <iostream>
#include <ctime>
#include <conio.h>
#include <string>
#include <chrono>
#include <thread>
#include <istream>
#include<time.h>

using namespace std;
const int gn = 4;
//Person* initArrays(int);
int checkNumber();

struct TurnsMod
{
	int modTurns = 0;
	double modifier = 0;
	bool modCheck = true;
	TurnsMod() {};
	TurnsMod(int turns, double mod, bool check) { modTurns = turns; modifier = mod; modCheck = check; }
};

struct Person
{
	string name;
	double money = 2000;
	int turn = 0;          	// negative numbers add turns positive numbers skip turns 0 is base
	double modifier = 1;    	//modifys money for sales
	int index = 0;      	// player # in array
	int status = 0; //holds wether its an NPC or PC
	int modifierTurns = 0;
	TurnsMod array[gn];
	Person() { }
	Person(string n, double m, int t, double mod, int i, int s, int mt) { name = n; modifier = m; turn = t; modifier = mod; index = i; status = s; modifierTurns = mt; }
};

class Events
{
protected:
	string text;
	int minValue;
	int maxValue;
	int aggressiveRating;
	int cInterestRating;
	int passiveRating;
public:
	Events() { maxValue = 0; minValue = 0; aggressiveRating = 0; cInterestRating = 0; passiveRating = 0; }
	Events(string na) { text = na; }
	Events(string t, int a, int i, int p) { text = t; aggressiveRating = a; cInterestRating = i; passiveRating = p; }
	Events(string n, int minP, int maxP) { text = n; minValue = minP; maxValue = maxP; }
	void Sales(Person* player);
	void Fire(Person* player);
	void Robbery(Person* player);
	void SocialMedia(Person* player);
	void Audit(Person* player);
	void GoodRandomEvent(Person* player);
	void BonusRound(Person* player);
	void EndRoundEvent(Person* player, int numPlayer);
	void ChangeMoneyWMod(Person* player, double money) { player->money += (money * player->modifier); }
	void ChangeMoneyWOutMod(Person* player, double money) { player->money += money; }
	void ChangeModifier(Person* player, double modifier) { player->modifier += modifier / 100; }
	void ChangeTurns(Person* player, int turns) { player->turn += turns; }
	//void Wager(Person* player)
};


#endif
void putInTurnsMod(Person* player, int num, double mod);
int Keypresses();
void Challenge(Person* challenger, Person* challengee);



Person* BubbleSort(Person num[], int numPlayers) // takes the current Person Player array and sorts it from first to last on money and returns the new array
{                                            	// while leaving the old one intact
	int i, j, flag = 1;
	const int n = 4;
	Person temp;
	Person* playerArray = new Person[gn];
	int numLength = numPlayers;
	for (int l = 0; l <= numLength; l++)
	{
		playerArray[l] = num[l];
		playerArray[l].index = l;
	}
	for (i = 0; (i < numLength) && flag; i++)
	{
		flag = 0;
		for (j = 0; j < (numLength); j++)
		{
			if (playerArray[j + 1].money > playerArray[j].money)
			{
				temp = playerArray[j];
				playerArray[j] = playerArray[j + 1];
				playerArray[j + 1] = temp;
				flag = 1;
			}
		}
	}
	return playerArray;
}

int Choice3Q(Person* player)
{
	int random;
	int choice;
	random = rand() % 3 + 1;
	if (player->status)
	{
		choice = random;
		cout << "NPC #" << player->index + 1 << " picked " << random << endl;
	}
	else
		choice = _getch() - '0';
	while (choice < 1 || choice > 3)
	{
		cout << "Sorry try again must be a number from 1 to 3!" << endl;
		choice = _getch() - '0';
	}
	return choice;
}
int Choice2Q(Person* player)
{
	int random;
	int choice;
	random = rand() % 2 + 1;
	if (player->status)
	{
		choice = random;
		cout << "NPC #" << player->index + 1 << " picked " << random << endl;
	}
	else
		choice = _getch() - '0';
	while (choice < 1 || choice > 2)
	{
		cout << "Sorry try again must be 1 or 2!" << endl;
		choice = _getch() - '0';
	}
	return choice;
}



void Events::Sales(Person* player)
{
	int random = 0, random2 = 0, random3 = 0, random4 = 0, max = 0;
	double total;
	const int n = 10;
	Events outcomes[n];
	Events customerReponses[n];
	Events customerTypes[n];
	int choice;
	outcomes[0] = { "They buy nothing " , 0,0 };
	outcomes[1] = { "They buy a game from the used game bin ", 10,10 };
	outcomes[2] = { "They buy a new controller ", 30,20 };
	outcomes[3] = { "They buy a brand new game " ,50,30 };
	outcomes[4] = { "They buy a few accessories totalling ", 100,30 };
	outcomes[5] = { "They purchase a used console", 200,50 };
	outcomes[6] = { "They buy a brand new console", 300,100 };
	outcomes[7] = { "They look around eventually deciding to buy a few assorted games ", 400,150 };
	outcomes[8] = { "They purchase a console and a few controllers ", 500,200 };
	outcomes[9] = { "They buy the mega console pack", 600,200 };
	customerReponses[0] = { "They respond negatively and leave the store ",0,0 };
	customerReponses[1] = { "They respond somewhat warily ",1,0 };
	customerReponses[2] = { "They seem indifferent to you ",2,1 };
	customerReponses[3] = { "They seem to be somewhat interested in you", 4,1 };
	customerReponses[4] = { "They like whatever you're doing! Keep doing it! ", 4,3 };
	customerReponses[5] = { "They seem to be in a very good mood no matter what you do", 3,5 };
	customerReponses[6] = { "They're absolutely glowing with excitement " , 2 , 7 };
	customerTypes[0] = { "They look like they're having a bad day ", 0 , 1 ,2 };
	customerTypes[1] = { "A young parent and their child come into the store", 1 ,2 ,0 };
	customerTypes[2] = { "They look like they could use help",2,1 ,0 };
	customerTypes[3] = { "They come straight to you to ask about the newest game",2 ,1 ,0 };
	customerTypes[4] = { "They're absolutely fuming with anger",0 , 0 ,2 };
	customerTypes[5] = { "They're beaming as radiantly as the sun!",1 , 2, 0 };
	customerTypes[6] = { "They look like they know what they're here for" , 0 , 1 , 2 };
	customerTypes[7] = { "They say hello and go about their business" , 1 , 1 ,1 };
	random4 = rand() % 7;
	cout << "A customer enters the store! " << customerTypes[random4].text << endl << "How do you choose to pursue them?\n";
	cout << "1) Passively.\n" << "2) Casual Interest.\n" << "3) Aggresively.\n";
	choice = Choice3Q(player);
	switch (choice)
	{
	case 1:
		cout << "You chose to passively sell.\n";
		random3 = rand() % 4;
		random3 += customerTypes[random4].passiveRating;
		if (random3 > 0)
			random2 = rand() % customerReponses[random3].minValue + customerReponses[random3].maxValue;
		if (random2 > 0)
		{
			max = outcomes[random2].maxValue;
			random = rand() % max + outcomes[random2].minValue;
		}
		total = random;
		cout << customerReponses[random3].text << endl;
		cout << outcomes[random2].text << " for " << total << endl;
		ChangeMoneyWMod(player, total);
		break;
	case 2:
		cout << "You chose to a show a casual interest towards them\n";
		random3 = rand() % 4;
		random3 += customerTypes[random4].cInterestRating;
		if (random3 > 0)
			random2 = rand() % customerReponses[random3].minValue + customerReponses[random3].maxValue;
		if (random2 > 0)
		{
			max = outcomes[random2].maxValue;
			random = rand() % max + outcomes[random2].minValue;
		}
		total = random;
		cout << customerReponses[random3].text << endl;
		cout << outcomes[random2].text << " for " << total << endl;
		ChangeMoneyWMod(player, total);
		break;
	case 3:
		cout << "You pursued them aggresively\n";
		random3 = rand() % 4;
		random3 += customerTypes[random4].aggressiveRating;
		if (random3 > 0)
			random2 = rand() % customerReponses[random3].minValue + customerReponses[random3].maxValue;
		if (random2 > 0)
		{
			max = outcomes[random2].maxValue;
			random = rand() % max + outcomes[random2].minValue;
		}
		total = random;
		cout << customerReponses[random3].text << endl;
		cout << outcomes[random2].text << " for " << total << endl;
		ChangeMoneyWMod(player, total);
		break;
	}
}

void Events::Fire(Person* player)
{
	int choice = 0;
	int random = 0;
	cout << "A fire broke out in your store last night.\n";
	cout << "Do you file an insurance claim? Enter 1 or use your own money to rebuild right away! Enter 2 or Do you repair the store by yourself? Press 3\n";
	choice = Choice3Q(player);
	switch (choice)
	{
	case 1:
		random = rand() % 1000 + 500;
		cout << "You get " << random << " dollars but miss three turns\n";
		ChangeMoneyWOutMod(player, random);
		ChangeTurns(player, 3);
		break;
	case 2:
		random = rand() % 300 + 300;
		cout << "You rebuild right away not losing anytime but losing " << random << " dollars\n";
		ChangeMoneyWOutMod(player, -random);
		break;
	case 3:
		cout << "You repair your store by yourself not costing you any money but you lose one turn\n";
		ChangeTurns(player, 1);
		break;
	}
}

void Events::Robbery(Person* player)
{
	int choice;
	int random;
	cout << "Your store is being robbed!!!!\n";
	cout << "Do nothing? Press 1 Try and stop them? Press 2 Call the Police? Press 3\n";
	choice = Choice3Q(player);
	switch (choice)
	{
	case 1:
		random = rand() % 500 + 100;
		cout << "They get away with " << random << " dollars worth of merchandise\n";
		ChangeMoneyWOutMod(player, -random);
		break;
	case 2:
		cout << "They get away with nothing but you lose your next turn\n";
		ChangeTurns(player, 1);
		break;
	case 3:
		random = rand() % 100 + 50;
		cout << "They get away but after hearing that you're calling the police they drop most of their loot and run you only lose " << random << " dollars and one turn\n";
		ChangeMoneyWOutMod(player, -random);
		ChangeTurns(player, 1);
		break;
	}
}

void Events::SocialMedia(Person* player)
{
	string MoreOrLess[2] = { "more", "less" };
	const int n = 10;
	Events reviews[n];
	Events outcomes[n];
	int random;
	reviews[0] = { "A positive review about your store is posted online", 10,0 };
	reviews[1] = { "A negative review about your store is posted online",-10,1 };
	reviews[2] = { "News of your store is trending. It's positive!",10,0 };
	reviews[3] = { "News of your store is trending. It's negative.",-10,1 };
	reviews[4] = { "You post an ad on social media about your store. It's well received!",10,0 };
	reviews[5] = { "You post an ad on social media about your store. It's poorly received.",-10,1 };
	random = rand() % 5;
	cout << reviews[random].text << " You now earn " << reviews[random].minValue << "% " << MoreOrLess[reviews[random].maxValue] << " of a sale when you sell an item" << endl;
	ChangeModifier(player, reviews[random].minValue);
}

void Events::Audit(Person* player)
{
	double random, random2;
	double total;
	cout << "The IRS is auditing you!\n";
	random = rand() % 100;
	random2 = rand() % 15 + 1;
	if (random < 90)
	{
		cout << "You owe them money! Pay up! You lose " << random2 << "% of your total money.\n";
		total = player->money * random2 / 100;
		ChangeMoneyWOutMod(player, -total);
	}
	else
	{
		total = random2 * 100;
		cout << "The IRS realizes it owes you money! To the sum of " << random2 * 100 << " dollars!\n";
		ChangeMoneyWOutMod(player, total);
	}
}

void Events::GoodRandomEvent(Person* player)
{
	const int n = 10;
	int random1, random2, random3;
	float percent;
	int choice;
	double total;
	Events goodEvents[n];
	goodEvents[0] = { "Do you want to have a sale?" };
	goodEvents[1] = { "Would you like to give back to the community?" };
	goodEvents[2] = { "Do you want to add a coffee stand to your store?" };
	goodEvents[3] = { "Do you want to host a games night at your store?" };
	goodEvents[4] = { "Renovate your store?" };
	goodEvents[5] = { "Donate some of your old items to good will?" };
	goodEvents[6] = { "Take inventory of your stock?" };
	random1 = rand() % 6;
	do
	{
		random2 = rand() % 6;
	} while (random1 == random2);
	do
	{
		random3 = rand() % 6;
	} while (random1 == random3 || random2 == random3);

	cout << "Pick what you're going to do! \n" << "1) " << goodEvents[random1].text << endl;
	cout << "2) " << goodEvents[random2].text << endl;
	cout << "3) " << goodEvents[random3].text << endl;
	choice = Choice3Q(player);
	switch (choice)
	{
	case 1: choice = random1; break;
	case 2: choice = random2; break;
	case 3: choice = random3; break;
	}
	switch (choice)
	{
	case 0:
		random1 = rand() % 9 + 1;
		total = random1 * 100;
		cout << "You've decided to have a sale! People come far and wide to buy from you! You make " << total << " dollars.\n";
		ChangeMoneyWOutMod(player, total);
		break;
	case 1:
		random1 = rand() % 9 + 1;
		cout << "You gave back to the community and the community is now giving back to you you're earning an extra " << random1 << "% per sale.\n";
		ChangeModifier(player, random1);
		break;
	case 2:
		random1 = rand() % 10 + 10;
		cout << "You've succesfully added a coffee stand to your store. You can now charge a premium for your games. You're making an extra " << random1 << "% per sale.\n";
		percent = random1;
		ChangeModifier(player, random1);
		break;
	case 3:
		random1 = rand() % 9 + 1;
		total = random1 * 150;
		cout << "As you're hosting a game night at your store people are buying up all kinds of items. You make an extra " << total << " dollars tonight!\n";
		ChangeMoneyWOutMod(player, total);
		break;
	case 4:
		random1 = rand() % 9 + 1;
		total = random1 * 100;
		cout << "You spruce up your store and have a grand reopening! People come far and wide to buy your games. You make " << total <<
			" dollars and an extra TURN! Congratulations!!\n";
		ChangeMoneyWOutMod(player, total);
		ChangeTurns(player, -1);
		break;
	case 5:
		random1 = rand() % 30 + 30;
		cout << "News of your giving nature gets out people come to show you support. You're now making an extra " << random1 << "% per sale for 2 turns.\n";
		putInTurnsMod(player, 2, random1);
		break;
	case 6:
		random1 = rand() % 10 + 10;
		total = random1 * 200;
		cout << "You discover you have some collectibles that sell for a lot of money! You make " << total << " dollars from their sale\n";
		ChangeMoneyWOutMod(player, total);
		break;
	}
}

void Events::EndRoundEvent(Person player[], int numPlayer) //come back event for last place
{
	Person* arrayPlayer = BubbleSort(player, numPlayer);
	int choice;
	int random;
	int challengeNum;
	double prize;
	int playerNumber = arrayPlayer[numPlayer].index;
	cout << endl << "You're last place Player #" << playerNumber + 1 << endl;
	cout << "Here's your chance to make a come back!\n";
	cout << "Do you want to be Nice or Mean? \nPress 1 for nice, 2 for Mean, or 3 to challenge the any player.\n";
	choice = Choice3Q(&player[playerNumber]);
	switch (choice)
	{
	case 1:
		random = rand() % 10 + 10;
		prize = random * 200;
		cout << "You decided to be nice and safe. You get " << prize << " dollars! Congrats!" << endl;
		player[arrayPlayer[numPlayer].index].money += prize;
		break;
	case 2:
		random = rand() % 10 + 20;
		prize = random;
		cout << "You just lowered everyone else's sales modifier by " << prize << "% ! Better watch your back.\n";
		for (int i = 0; i < numPlayer; i++)
		{
			player[arrayPlayer[i].index].modifier += -(prize / 100);
		}
		break;
	case 3:
		cout << "Which player would you like to challenge? Enter the leaderboard position of the person you'd like to challenge.\n";
		challengeNum = Choice3Q(&player[playerNumber]);
		cout << "You challenge player " << challengeNum << " to a game of bacarrat. \nThe player whose hand is closest to 9 wins. The wager is $1000.\n";
		cout << "In case of a draw, neither player wins.\n";
		Challenge(&player[playerNumber], &player[arrayPlayer[challengeNum - 1].index]);
		break;
	}
}

void Events::BonusRound(Person* player)
{
	int i = 1;
	int start = clock();
	int keyPress;
	double diff;
	//	using namespace std::chrono_literals;
	cout << "Here's a chance to show your speed. How many fliers can you hand out in 10 seconds?\n";
	cout << "The more fliers you hand out by pressing the left and right arrow keys in succession the more money you'll make.\n";
	cout << "Starting in 3 seconds. GET READY!\n";
	for (i = 1; i <= 3; i++)
	{
		this_thread::sleep_for(1s);
		cout << i << endl;
	}
	cout << "GO!!" << endl;
	if (player->status == 1)
		keyPress = rand() % 20 + 30;
	else
		keyPress = Keypresses();
	keyPress *= 2;
	cout << "Good job! You got " << keyPress / 2 << " combos! You'll get an extra " << keyPress << "% per sale! For 3 Turns.\n";
	putInTurnsMod(player, 3, keyPress);
	do {
		cout << "Press Enter to continue\n";
		keyPress = _getch();
	} while (!(keyPress == 13));
}

int Keypresses()
{
	int combos = 0;
	int left = 0;
	int right = 0;
	double diff;
	bool status = false, status2 = false;
	int start = clock();
	do
	{
		left = _getch();
		right = _getch();

		if (right == 75)
			status = true;
		else if (right == 77)
			status2 = true;

		if (status && status2)
		{
			cout << combos++ << " combos " << endl;
			right = 0;
			status = false;
			status2 = false;
		}
		diff = (clock() - start) / (double)(CLOCKS_PER_SEC);
	} while (diff < 13.0);
	return combos;
}

void Challenge(Person* challenger, Person* challengee)
{
	int i, hand_total, card,
		hand_1 = 0, hand_2 = 0;
	time_t t;

	printf("Player 1's draw: ");
	for (i = 0; i < 3; i++)
	{
		card = rand() % 10 + 1;
		printf("%d\t", card);
		hand_1 = hand_1 + card;
	}


	printf("\nPlayer 2's draw: ");
	for (i = 0; i < 3; i++)
	{
		card = rand() % 10 + 1;
		printf("%d\t", card);
		hand_2 = hand_2 + card;
	}
	printf("\nPlayer 1's hand: %d\n", hand_1 % 10);
	printf("Player 2's hand: %d\n", hand_2 % 10);

	if ((hand_1 % 10) > (hand_2 % 10))
	{
		//hand_1 wins
		cout << "The challenger has won.";
		challenger->money += 1000;
		challengee->money -= 1000;
	}
	else
	{
		//hand_2 wins
		cout << "The challengee has won.";
		challengee->money += 1000;
		challenger->money -= 1000;
	}
}
