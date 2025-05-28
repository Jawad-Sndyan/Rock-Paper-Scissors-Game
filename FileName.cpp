#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<windows.h>  
using namespace std;
enum enGameChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };
struct stRoundStats
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner RoundWinner;
	string RoundWinnerName = "";
};
struct stGameStats
{
	short GameRounds = 0;
	short PlayerWinesCounter = 0;
	short ComputerWinesCounter = 0;
	short DrawsCounter = 0;
	enWinner GameWinner;
	string GameWinnerName = "";
};

void ResetScreen() {
	system("cls");
	system("color 0F");
}
int RandomNumber(int From, int To)
{
	return(rand() % (To - From + 1) + From);
}
enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}
int HowManyRoundsToPlay()
{
	int Rounds = 0;
	do
	{
		cout << "How many rounds do you want to play from 1 to 10 ";
		cin >> Rounds;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			Rounds = 0;
		}
	} while (Rounds < 1 || Rounds > 10);
	return Rounds;
}
enGameChoice PlayerChoice()
{
	int choice = 0;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> choice;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			choice = 0;
		}
	} while (choice < 1 || choice > 3);
	return (enGameChoice)choice;
}
enWinner RoundWinner(stRoundStats Winner)
{
	if (Winner.PlayerChoice == Winner.ComputerChoice)
		return enWinner::Draw;
	switch (Winner.PlayerChoice)
	{
	case enGameChoice::Rock:
		return (Winner.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player;
	case enGameChoice::Paper:
		return (Winner.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player;
	case enGameChoice::Scissors:
		return (Winner.ComputerChoice == enGameChoice::Rock) ? enWinner::Computer : enWinner::Player;
	}
}
enWinner GetGameWinner(stGameStats Winner)
{
	if (Winner.ComputerWinesCounter == Winner.PlayerWinesCounter)
		return enWinner::Draw;
	else if (Winner.ComputerWinesCounter < Winner.PlayerWinesCounter)
		return enWinner::Player;
	else
		return enWinner::Computer;
}
string WinnerName(enWinner Winner)
{
	string arrGameWinner[3] = { "Player","Computer","No one won (Draw)" };
	return arrGameWinner[Winner - 1];
}
string GameChoice(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Rock","Paper","Scissors" };
	return arrGameChoice[Choice - 1];
}
string Tabs(short TabsNumber)
{
	string Tab = "";
	for (int i = 1;i <= TabsNumber;i++)
	{
		Tab += "\t";
	}
	return Tab;
}
void PrintRoundStats(stRoundStats Stats)
{
	cout << "\n_______________ Round [" << Stats.RoundNumber << "] _______________\n";
	cout << "Player1 Choice: " << GameChoice(Stats.PlayerChoice) << endl;
	cout << "Computer Choice: " << GameChoice(Stats.ComputerChoice) << endl;
	cout << "Round Winner   : [" << Stats.RoundWinnerName << "]\n";
	cout << "_________________________________________\n" << endl;
}
void PrintGameStats(stGameStats Stats)
{
	cout << Tabs(2) << "--------------------------------------------------------\n";
	cout << Tabs(4) << "+++ G a m e O v e r +++\n";
	cout << Tabs(2) << "--------------------------------------------------------\n";
	cout << Tabs(4) << "Rounds Played : " << Stats.GameRounds << endl;
	cout << Tabs(4) << "Player Wines : " << Stats.PlayerWinesCounter << " Time(s)" << endl;
	cout << Tabs(4) << "Computer Wines : " << Stats.ComputerWinesCounter << " Time(s)" << endl;
	cout << Tabs(4) << "Draws : " << Stats.DrawsCounter << " Time(s)" << endl;
	cout << Tabs(4) << "Final Winner : " << Stats.GameWinnerName << endl;
	cout << Tabs(2) << "--------------------------------------------------------\n";
}
stGameStats FillstGameStats(int RoundesToPlay, int PlayerWines, int ComputerWines, int Draws)
{
	stGameStats GameStats;
	GameStats.GameRounds = RoundesToPlay;
	GameStats.ComputerWinesCounter = ComputerWines;
	GameStats.PlayerWinesCounter = PlayerWines;
	GameStats.DrawsCounter = Draws;
	GameStats.GameWinner = GetGameWinner(GameStats);
	GameStats.GameWinnerName = WinnerName(GameStats.GameWinner);

	return GameStats;
}
stGameStats PlayGame(int RoundesToPlay)
{
	stRoundStats RoundStats;
	int PlayerWinesCounter = 0, ComputerWinesCounter = 0, DrawsCounter = 0;
	for (int Round = 1;Round <= RoundesToPlay;Round++)
	{
		RoundStats.RoundNumber = Round;
		RoundStats.PlayerChoice = PlayerChoice();
		RoundStats.ComputerChoice = GetComputerChoice();
		RoundStats.RoundWinner = RoundWinner(RoundStats);
		RoundStats.RoundWinnerName = WinnerName(RoundStats.RoundWinner);

		if (RoundStats.RoundWinner == enWinner::Computer)
		{
			ComputerWinesCounter++;
			system("color 4F");
			cout << "\a";
		}
		else if (RoundStats.RoundWinner == enWinner::Player)
		{
			PlayerWinesCounter++;
			system("color 2F");
		}
		else
		{
			DrawsCounter++;
			system("color 6F");
		}

		PrintRoundStats(RoundStats);
	}
	return FillstGameStats(RoundesToPlay, PlayerWinesCounter, ComputerWinesCounter, DrawsCounter);
}
void Game()
{
	char PlayAgain = 'y';
	stGameStats Game;
	do
	{
		Game = PlayGame(HowManyRoundsToPlay());
		Sleep(500);
		system("color 0F");
		PrintGameStats(Game);
		cout << Tabs(2) << "Do you want to play again Y / N ";
		cin >> PlayAgain;
		cout << endl;
		if (PlayAgain == 'y' || PlayAgain == 'Y')
			ResetScreen();
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
	srand(time(0));
	Game();
	return 0;
}

