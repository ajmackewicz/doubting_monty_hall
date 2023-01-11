/*
GOAL OF PROGRAM
To test whether switching will increase the odds
of choosing the prize from 1/n chance to 2/n

LOGICAL STRUCTURE OF MONTY HALL GAME
Set prize door.

Choose a door.

Eliminate a door from being a prize by opening it.

If toSwitch is set to true, switch doors.
If not toSwitch, do not switch doors.

Compare door choice to door with prize.
*/

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
using namespace std;

class MontyHallGame
{
public:
	MontyHallGame()
	{
		numberOfDoors = 0;
		toSwitch = false;
		prizeDoor = 0;
		chosenDoor = 0;
	}
	
	void setNumberOfDoors(unsigned int numb)
	{
		numberOfDoors = numb;
	}
	
	void setToSwitch(bool tSwitch)
	{
		toSwitch = tSwitch;
	}

	void initializePrizeDoor()
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dist(1, numberOfDoors);
		prizeDoor = dist(gen);
	}

	void chooseDoor()
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dist(1, numberOfDoors);

		chosenDoor = dist(gen);
	}

	void eliminateDoor()
	{
		do
		{
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> dist(1, numberOfDoors);

			openedDoor = dist(gen);
		// Don't open door that has already been opened or is the prize
		} while (openedDoor == chosenDoor || openedDoor == prizeDoor);
	}

	void switchDoor()
	{
		unsigned int newChosenDoor;
		do
		{
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> dist(1, numberOfDoors);
	
			newChosenDoor = dist(gen);
	
		// Don't switch door to one that was already opened or one that was just chosen
		} while (newChosenDoor == chosenDoor || newChosenDoor == openedDoor);

		chosenDoor = newChosenDoor;
	}

	bool chosePrizeDoor()
	{
		return (chosenDoor == prizeDoor);
	}

	void playGame()
	{
		initializePrizeDoor();
		chooseDoor();
		eliminateDoor();

		if (toSwitch)
			switchDoor();
	}

	int getResult()
	{
		if (chosePrizeDoor())
			return 1;
		else
			return 0;
	}

private:
	unsigned int numberOfDoors;
	bool toSwitch;
	unsigned int prizeDoor;
	unsigned int chosenDoor;
	unsigned int openedDoor;
};

void setNumberOfGames(unsigned int& numbOfGames)
{
	printf("Enter the number of Monty Hall games to play: \n");
	cin >> numbOfGames;
}

void setNumberOfDoors(unsigned int& numbOfDoors)
{
	printf("Enter the number of doors: \n");
	cin >> numbOfDoors;
}

void setToSwitch(bool& toSwitch)
{
	printf("Enter 1 if to switch the doors and 0 to not: \n");
	cin >> toSwitch;
}

class Timer
{
public:
	void startTime()
	{
		start = chrono::high_resolution_clock::now();
	}
	void stopTime()
	{
		end = chrono::high_resolution_clock::now();
	}
	double getDuration()
	{
		elapsed_time = end - start;
		double elapsed_seconds = elapsed_time.count(); 
		return elapsed_seconds;
	}
private:
	chrono::time_point<chrono::high_resolution_clock> start;
	chrono::time_point<chrono::high_resolution_clock> end;
	chrono::duration<double> elapsed_time;
};

int main()
{
	Timer initializationTimer;
	Timer processingTimer;
	unsigned int numbOfGames = 0;
	unsigned int numbOfGamesWon = 0;
	unsigned int numbOfDoors = 0;
	bool toSwitch = false;
	double percentWon = 0.0;
	double chanceWinWSwitch = 0.0;

	setNumberOfGames(numbOfGames);
	setNumberOfDoors(numbOfDoors);
	setToSwitch(toSwitch);

	printf("Initializing games' data . . .\n");
	initializationTimer.startTime();
	MontyHallGame *montyHallGame = new MontyHallGame[numbOfGames];

	for (int i = 0; i < numbOfGames; ++i)
	{
		montyHallGame[i].setNumberOfDoors(numbOfDoors);
		montyHallGame[i].setToSwitch(toSwitch);
	}
	initializationTimer.stopTime();
	printf("Finished initializing data.\n");
	printf("Initialization time: %f s\n", initializationTimer.getDuration());
	printf("\n");

	// Processing
	printf("Playing games . . .\n");
	processingTimer.startTime();
	for (int i = 0; i < numbOfGames; ++i)
	{
		montyHallGame[i].playGame();
		numbOfGamesWon += montyHallGame[i].getResult();
	}

	percentWon = numbOfGamesWon * 1.0 / numbOfGames;
	chanceWinWSwitch = 2 * 1.0 / numbOfDoors;

	processingTimer.stopTime();
	printf("Finished playing. Now to business.\n");
	printf("Processing time: %f s\n", processingTimer.getDuration());
	printf("\n");

	// Priting
	printf("Number of games: %u\n", numbOfGames);
	printf("Number of games won: %u\n", numbOfGamesWon);
	printf("Percent won: %f\n", percentWon);
	printf("Chance of winning if switching (2/numberOfGames): %f\n", chanceWinWSwitch);

	delete [] montyHallGame;

	return 0;
}
