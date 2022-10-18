#include "Deck.h"
#include "Side.h"
#include <algorithm>
#include <iostream>
using namespace std;

void Game(Deck playerDeck, Deck cpuDeck, Side playerSide, Side cpuSide);
void filler(int array[52]);
string faceCards (int card);

int main() {
	//creating the decks and shuffling
	int array[52];
	filler(array);
	int n = sizeof(array) / sizeof(array[0]);
	random_shuffle(array, array + n);
	//creating the decks for the player and the cpu
	Deck player;
	Side secondHand;
	
	Deck cpu;
	Side cpuHand;
	//filling the linked list decks
	for(int x = 0; x < 52; x++){
		if(x%2 == 0){
			player.enqueue(array[x]);
		}
		else{
			cpu.enqueue(array[x]);
		}
	}
	
	Game(player, cpu, secondHand, cpuHand);
	return 0;
}

void filler(int empty[52]){
	int cardNum = 1;
	for(int i = 0; i < 52; i++){
		if(i%4 == 0){
			cardNum += 1;
		}
		empty[i] = cardNum;
	}
}

string faceCards (int card){
  if (card == 11){
    return "Jack";
  }
  else if (card == 12){
    return "Queen";
  }
  else if (card == 13){
    return "King";
  }
  else if (card == 14){
    return "Ace";
  }
  else{
    return to_string(card);
  }
}

bool cpuLogic(Deck cpuDeck, Side cpuSide){
	if(cpuDeck.peek() >=10 && !cpuSide.isFull()){
		cpuSide.push(cpuDeck.dequeue());
	}
	else if(cpuDeck.peek() <= 4 && !cpuSide.isEmpty()){
		return true;
	}
	return false;
}

void Game(Deck playerDeck, Deck cpuDeck, Side playerSide, Side cpuSide){
  cout << "Hello and welcome to the game of War!" << endl;
	//Game mode selection
	cout << "Would you like to play until you are out of card's or a certian amount of turns?" << endl;
	cout << "1. Out of Cards" << endl;
	cout << "2. Number of turns" << endl;
	int inputMode;
	cin >> inputMode;
	int totalTurns = 1;
  
	//Turn finder if that game mode is selected
	if(inputMode == 2){
		cout << "How many turns would you like to play?" << endl;
		cin.ignore();
		cin >> totalTurns;
	}
	int turnNumber = 0;
	
  bool hasCards = true, cpuHasCards = true;
  while (((hasCards == true) && (cpuHasCards == true)) && totalTurns != turnNumber){
	  
	  int opt = 0;
	  cout << endl << "1. Play deck card only" << endl;
	  cout << "2. Play deck and side deck cards" << endl;
	  cout << "3. Move Card to Side Deck" << endl;
	  cout << "4. Peek top card" << endl;
	  cout << "5. Ask CPU how many cards it has left in its deck" << endl;
	  cout << "6. Check how many cards you have left in your deck" << endl;
	  cout << "7. Check how many cards are in your sidepile" << endl;
		
	  cout << "Enter an instruction (1 - 7): ";
	  cin.ignore();
	  cin >> opt;
	  

	  if (opt == 1){
		  //Play game
		  int playerCard = playerDeck.dequeue();
		  bool logic = false;
			int cpuFirstCard;
			int cpuSecondCard = 0;
      
			if(logic){
				cpuFirstCard = cpuDeck.dequeue();
				cpuSecondCard = cpuSide.pop();
        cout << "You drew a " << faceCards(playerCard) << " and CPU drew a " << faceCards(cpuFirstCard) << " and a " << faceCards(cpuSecondCard) << endl;
			}
			else{
				cpuFirstCard = cpuDeck.dequeue();
        cout << "You drew a " << faceCards(playerCard) << " and CPU drew a " << faceCards(cpuFirstCard) << endl;
			}
      
		  int cpuCard = cpuFirstCard + cpuSecondCard;
		  if(cpuCard >= playerCard){
        cout << "CPU Wins the hand! They get the cards!" << endl << endl;
			  cpuDeck.enqueue(playerCard);
			  cpuDeck.enqueue(cpuFirstCard);
				if(logic){
					cpuDeck.enqueue(cpuSecondCard);
				}
			}
		  else{
        cout << "You won the hand! You got the cards!" << endl << endl;
			  playerDeck.enqueue(playerCard);
			  playerDeck.enqueue(cpuCard);
				if(logic){
					playerDeck.enqueue(cpuSecondCard);
				}
			}
		  
		  //for second gamemode 
		  if(inputMode ==2){
			  turnNumber += 1;
			}
		}
      
	  else if (opt == 2){
      //
			if(!playerSide.isEmpty()){
				int playerCard = playerDeck.dequeue();
				int secondCard = playerSide.pop();
        int total = playerCard + secondCard;
				bool logic = false;
				int cpuFirstCard;
				int cpuSecondCard = 0;
	      
				if(logic){
					cpuFirstCard = cpuDeck.dequeue();
					cpuSecondCard = cpuSide.pop();
	        cout << "You drew a " << faceCards(playerCard) << " and a " << faceCards(secondCard) << " and CPU drew a " << faceCards(cpuFirstCard) << " and a " << faceCards(cpuSecondCard) << endl;
				}
				else{
					cpuFirstCard = cpuDeck.dequeue();
	        cout << "You drew a " << faceCards(playerCard) << " and a " << faceCards(secondCard) << " and CPU drew a " << faceCards(cpuFirstCard) << endl;
				}
	      
			  int cpuCard = cpuFirstCard + cpuSecondCard;
				
				if(cpuCard >= total){
          cout << "CPU Wins the hand! They get the cards!" << endl << endl;
				  cpuDeck.enqueue(playerCard);
					cpuDeck.enqueue(secondCard);
				  cpuDeck.enqueue(cpuCard);
					if(logic){
					cpuDeck.enqueue(cpuSecondCard);
					}
				}
		  	else{
          cout << "You won the hand! You got the cards!" << endl << endl;
			  	playerDeck.enqueue(playerCard);
          playerDeck.enqueue(secondCard);
			  	playerDeck.enqueue(cpuCard);
					if(logic){
					playerDeck.enqueue(cpuSecondCard);
					}
				}
				if(inputMode ==2){
			  turnNumber += 1;
				}
			}
			else{
				cout << "Your side pile is empty" << endl;
			}
	  }
    else if (opt == 3){
		  if (!playerSide.isFull()) playerSide.push(playerDeck.dequeue());
		  else cout << "Your side deck is full. Card not added" << endl;
    }
    else if (opt == 4){
      cout << "Your top deck card is a " << faceCards(playerDeck.peek()) << endl;
    }
    else if (opt == 5){
      cout << "The CPU has " << cpuDeck.length() << " cards on its deck"<< endl;
    }
	  else if (opt == 6){
		  cout << "You have " << playerDeck.length() << " cards on your deck"<< endl;
	  }
	  else if(opt == 7){
		  cout << "You have " << playerSide.length() << " cards on your side pile"<< endl;
	  }
    else{
      cout << "ERROR. Enter a value 1-7" << endl << endl;
      continue;
    }
		if(playerDeck.isEmpty() && !playerSide.isEmpty()){
			playerDeck.enqueue(playerSide.pop());
		}
    if (playerDeck.isEmpty() == true){
      cout << "You've run out of cards! CPU won the game! Try again?" << endl;
      hasCards = false;
    }
    if (cpuDeck.isEmpty() == true){
      cout << "CPU has run out of cards! You won the game! Play again?" << endl;
      cpuHasCards = false;
    }
  }
  if (inputMode == 2){
    if (cpuDeck.length() >= playerDeck.length()){
      cout << "CPU won the game! Try again?" << endl;
    }
    else{
      cout << "You won the game! Play again?" << endl;
    }
  }
}

