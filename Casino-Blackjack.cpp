#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "Card.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

vector<Card> makeDeck();
vector<Card> makeUserDeck();
vector<Card> makeCPDeck();

vector<Card> shuffleUserDeck(vector<Card> deck, vector<Card> userDeck);
vector<Card> shuffleCPDeck(vector<Card> deck, vector<Card> cpDeck);

Card getRandomCard(vector<Card> deck);
string getCardSuit(Card card);

void printHands(vector<Card> userDeck, vector<Card> cpDeck);
void printInitialHands(vector<Card> userDeck, vector<Card> cpDeck);
void printHand(vector<Card> plDeck);

int generatePlayChance();
void startPlay(vector<Card> deck, vector<Card> userDeck, vector<Card> cpDeck);
void endPlay(vector<Card> deck, vector<Card> userDeck, vector<Card> cpDeck);

PlayState validateScore(vector<Card> userDeck);
void tallyScore(vector<Card> userDeck, vector<Card> cpDeck);
int tallyCardValue(vector<Card> plDeck);



int main()
{
    char buff;

    cout << "Hello World!\n";
    cout << "Loading blackjack...\n";
    
    cout << "\n> ";
    cin >> buff;
    vector<Card> deck = makeDeck();

    vector<Card> userDeck = shuffleUserDeck(deck, makeUserDeck());
    vector<Card> cpDeck = shuffleCPDeck(deck, makeCPDeck());

    cout << "Game Starting...";
    cout << "\n> ";
    cin >> buff;

    startPlay(deck, userDeck, cpDeck);

}

vector<Card> makeDeck()
{
    cout << "Creating deck...\n";

    vector<Card> deck;

    int suitTicker = 0;
    int cardTicker = 0;
    Suit cSuit;
    for (size_t i = 0; i < 52; i++)
    {
        if (cardTicker == 14)
        {
            cardTicker = 0;
        }

        switch (suitTicker)
        {
        case 0:
            cSuit = Suit::SPADE;
            break;
        case 1:
            cSuit = Suit::DIAMOND;
            break;
        case 2:
            cSuit = Suit::HEART;
            break;
        case 3:
            cSuit = Suit::CLUB;
            break;
        default:
            cSuit = Suit::CLUB;
            suitTicker = 0;
            break;
        }

        deck.push_back(Card(cardTicker, cSuit));

        suitTicker++;
        cardTicker++;
    }

    return deck;
}
vector<Card> makeUserDeck()
{ 
    return vector<Card>{};

}
vector<Card> makeCPDeck()
{
    return vector<Card>{};
}
vector<Card> shuffleUserDeck(vector<Card> deck, vector<Card> userDeck)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 51);

    for (size_t i = 0; i < 2; i++)
    {
        userDeck.push_back(deck[dist(rd)]);
    }

    return userDeck;
}
vector<Card> shuffleCPDeck(vector<Card> deck, vector<Card> cpDeck)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 51);

    for (size_t i = 0; i < 2; i++)
    {
        cpDeck.push_back(deck[dist(rd)]);
    }

    return cpDeck;
}
Card getRandomCard(vector<Card> deck)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 51);

    return deck[dist(rd)];
}
string getCardSuit(Card card)
{
    switch (card.suit)
    {
    case Suit::SPADE:
        return "S";
    case Suit::DIAMOND:
        return "D";
    case Suit::HEART:
        return "H";
    case Suit::CLUB:
        return "C";
    default:
        return "ERR";
    }
}
void printInitialHands(vector<Card> userDeck, vector<Card> cpDeck)
{
    system("cls");
    cout << "\n\n\n\n";
    cout << "Dealer's Hand: \n";
    cout << cpDeck[0].value << getCardSuit(cpDeck[0]) << " " << "%";
    cout << "\n\n\n\n";
    cout << "Your Hand :\n";
    cout << userDeck[0].value << getCardSuit(userDeck[0]) << " " << userDeck[1].value << getCardSuit(userDeck[1]);
    cout << "\n\n";
}
void printHands(vector<Card> userDeck, vector<Card> cpDeck)
{
    system("cls");
    //cout << "\n\n\n\n";
    //cout << "Dealer's Hand: \n";

    //for (Card card : cpDeck)
    //    cout << card.value << getCardSuit(card) << " ";

    cout << "\n\n\n\n";
    cout << "Dealer's Hand: \n";
    cout << cpDeck[0].value << getCardSuit(cpDeck[0]) << " " << "%";

    cout << "\n\n\n\n";
    cout << "Your Hand :\n";

    for (Card card : userDeck)
        cout << card.value << getCardSuit(card)<< " ";

    cout << "\n\n";
}
void printHand(vector<Card> plDeck) 
{
    for (Card card : plDeck)
        cout << card.value << getCardSuit(card) << " ";
}
int generatePlayChance()
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 1);

    return dist(rd);
}
void startPlay(vector<Card> deck, vector<Card> userDeck, vector<Card> cpDeck)
{
    bool playIsGood = true;

    printInitialHands(userDeck, cpDeck);

    while (playIsGood)
    {
        bool inputIsGood = false;
        while (!inputIsGood)
        {
            cout << "H for hit, S for Stand: ";

            string userInput;
            cin >> userInput;

            if (userInput == "H")
            {
                inputIsGood = true;
                userDeck.push_back(getRandomCard(deck));
                PlayState state = validateScore(userDeck);

                switch (state)
                {
                case BLACKJACK:
                    playIsGood = false;
                    cout << "\n\nBLACKJACK!\n\n";
                    endPlay(deck, userDeck, cpDeck);
                    break;
                case BUST:
                    playIsGood = false;
                    cout << "\n\nBUST\n\n";
                    endPlay(deck, userDeck, cpDeck);
                    break;
                case VALID:
                    // continue on
                    playIsGood = true;
                    //inputIsGood = true;
                    printHands(userDeck, cpDeck);
                    break;
                default:
                    break;
                }
            }
            else if (userInput == "S")
            {
                inputIsGood = true;
                playIsGood = false; // break out of all loops, play ended
                endPlay(deck, userDeck, cpDeck);
            }
            else 
            {
                cout << "\n\nInput Failure!\n\n";
            }
        }

    }

}
void endPlay(vector<Card> deck, vector<Card> userDeck, vector<Card> cpDeck) 
{
    if (userDeck[0].value + userDeck[1].value >= 17) 
        tallyScore(userDeck, cpDeck); // dealer stands
    else
    {
        int playChance = generatePlayChance();

        // dealers turn
        bool playIsGood = true;
        while (playIsGood)
        {
            if (playChance == 1)
            {
                cpDeck.push_back(getRandomCard(deck));
                PlayState state = validateScore(cpDeck);

                switch (state)
                {
                case BLACKJACK:
                    playIsGood = false;
                    cout << "\n\nCP HAS BLACKJACK!\n\n";
                    tallyScore(userDeck, cpDeck);
                    break;
                case BUST:
                    playIsGood = false;
                    cout << "\n\nCP BUST!\n\n";
                    tallyScore(userDeck, cpDeck);
                    break;
                case VALID:
                    playIsGood = true;
                    break;
                default:
                    break;
                }
            }
            else
            {
                // dealer stands
                playIsGood = false;
                tallyScore(userDeck, cpDeck);
            }
        }
    }
}
PlayState validateScore(vector<Card> plDeck)
{
    int userCardValueTotal = 0;
    for (Card card : plDeck)
    {
        userCardValueTotal += card.value;
    }

    if (userCardValueTotal > 21) return PlayState::BUST;
    else if (userCardValueTotal == 21) return PlayState::BLACKJACK;
    else return PlayState::VALID;
}
void tallyScore(vector<Card> userDeck, vector<Card> cpDeck)
{
    cout << "\n\nGENERATE SCORE\n\n";

    char buff;
    cin >> buff;

    system("cls");

    int userDeckTotal = tallyCardValue(userDeck);
    int cpDeckTotal = tallyCardValue(cpDeck);

    PlayState plState;
    GameState gmState;

    // final result
    if (userDeckTotal == cpDeckTotal)
    {
        cout << "\n\n GAME RESULT: DRAW!";
        gmState = GameState::DRAW;

        cout << "\n\nCOMPUTER HAND: \n";
        printHand(cpDeck);
        cout << "\n\n";

        cout << "\n\nUSER HAND: \n";
        printHand(userDeck);
        cout << "\n\n";
    }
    else if (userDeckTotal > 21 && cpDeckTotal > 21)
    {
        cout << "\n\n GAME RESULT: DRAW!";
        gmState = GameState::DRAW;

        cout << "\n\nCOMPUTER HAND: \n";
        printHand(cpDeck);
        cout << "\n\n";

        cout << "\n\nUSER HAND: \n";
        printHand(userDeck);
        cout << "\n\n";
    }
    else if (userDeckTotal == 21 && cpDeckTotal == 21)
    {
        cout << "\n\n GAME RESULT: DRAW!";
        gmState = GameState::DRAW;

        cout << "\n\nCOMPUTER HAND: \n";
        printHand(cpDeck);
        cout << "\n\n";

        cout << "\n\nUSER HAND: \n";
        printHand(userDeck);
        cout << "\n\n";
    }
    else if (userDeckTotal < 21 && cpDeckTotal > 21)
    {
        cout << "\n\n GAME RESULT: WIN!";
        gmState = GameState::PL_WIN;

        cout << "\n\nCOMPUTER HAND: \n";
        printHand(cpDeck);
        cout << "\n\n";

        cout << "\n\nUSER HAND: \n";
        printHand(userDeck);
        cout << "\n\n";
    }
    else if (userDeckTotal > 21 && cpDeckTotal < 21)
    {
        cout << "\n\n GAME RESULT: LOSS!";
        gmState = GameState::PL_LOSS;

        cout << "\n\nCOMPUTER HAND: \n";
        printHand(cpDeck);
        cout << "\n\n";

        cout << "\n\nUSER HAND: \n";
        printHand(userDeck);
        cout << "\n\n";
    }
    else if (userDeckTotal > cpDeckTotal)
    {
        cout << "\n\n GAME RESULT: WIN!";
        gmState = GameState::PL_WIN;

        cout << "\n\nCOMPUTER HAND: \n";
        printHand(cpDeck);
        cout << "\n\n";

        cout << "\n\nUSER HAND: \n";
        printHand(userDeck);
        cout << "\n\n";
    }
    else if (userDeckTotal < cpDeckTotal)
    {
        cout << "\n\n GAME RESULT: LOSS!";
        gmState = GameState::PL_LOSS;

        cout << "\n\nCOMPUTER HAND: \n";
        printHand(cpDeck);
        cout << "\n\n";

        cout << "\n\nUSER HAND: \n";
        printHand(userDeck);
        cout << "\n\n";
    }
}
int tallyCardValue(vector<Card> plDeck)
{
    int cardTotal = 0;
    for (Card card : plDeck)
    {
        cardTotal += card.value;
    }

    return cardTotal;
}
