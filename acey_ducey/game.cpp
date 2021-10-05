#include "game.h"

AceyDucey::AceyDucey(unsigned int iStartDollars)
{
	m_startDollars = iStartDollars;
	m_player = new Player(iStartDollars);
}

AceyDucey::~AceyDucey()
{
	delete m_player;
}

void AceyDucey::Introduction()
{
	std::string strIntroduction = "Acey decey is played in the following manner\n"
	"The Dealer(Computer) deals two cards face up\n"
	"you have an option to bet or not bet depending\n"
	"on whatever or not you feel the card will have\n"
	"a value between the first two\n"
	"if you do not want to bet, input a 0\n"
	"You now have " + std::to_string(m_startDollars) + "Dollars\n";

	std::cout << strIntroduction;
}

void AceyDucey::RoundStart()
{
	m_cardBoard.ShuffleCards();
	Card* card1 = m_cardBoard.GetCardWithNum(1);
	Card* card2 = m_cardBoard.GetCardWithNum(2);
	Card* card3 = m_cardBoard.GetCardWithNum(3);

	if (m_player == nullptr ||card1 == nullptr || card2 == nullptr || card3 == nullptr) {
		std::cout << "Something Wrong\n";
		return;
	}
	std::cout << "Here are your next two cards\n";
	std::cout << card1->GetName() << "\n";
	std::cout << card2->GetName() << "\n";

	std::cout << "What is your bet? ";
	unsigned int playerBet;
	std::cin >> playerBet;

	m_player->SetBetDollar(playerBet);
	std::cout << card3->GetName() << "\n";

	bool bWin = card3->IsBetweenCards(card1, card2);
	m_player->SetBetResult(bWin);

	if (bWin) {
		std::cout << "CHICKEN!!!\n";
	} else {
		std::cout << "Sorry you lose\nYou now have " +
			std::to_string(m_player->GetCurrentDollar()) + " Dollars\n";
	}
}

bool AceyDucey::IsGameOver()
{
	if (m_player == nullptr) {
		return true;
	}
	return (m_player->GetCurrentDollar() == 0);
}