#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <algorithm>
#include <numeric>

class Card
{
public:
	Card(unsigned int cardNum): m_num(cardNum)
	{
		m_name = ConverCardNumToStr(cardNum);
	}
	~Card() {}
	std::string GetName()
	{
		return m_name;
	}
	unsigned int GetNum()
	{
		return m_num;
	}
	bool IsBetweenCards(Card* card1, Card* card2)
	{
		return (m_num > card1->GetNum() && m_num < card2->GetNum()) ||
			(m_num > card2->GetNum() && m_num < card1->GetNum());
	}
private:
	std::string m_name;
	unsigned int m_num;
	std::string ConverCardNumToStr(unsigned int cardNum)
	{
		if (cardNum > 1 && cardNum < 11) {
			return std::to_string(cardNum);
		} else if (cardNum == 1) {
			return "A";
		} else if (cardNum == 11) {
			return "Jack";
		} else if (cardNum == 12) {
			return "Quene";
		} else if (cardNum == 13) {
			return "King";
		}
		return "";
	}
};

class CardBoard
{
public:
	CardBoard()
	{
		std::vector<short> cardIndex(52);
		std::iota(cardIndex.begin(), cardIndex.end(), 0);
		m_cardIndex.assign(cardIndex.begin(), cardIndex.end());
	}
	~CardBoard() {}
	void ShuffleCards()
	{
		std::srand(unsigned(std::time(0)));
		std::random_shuffle(m_cardIndex.begin(), m_cardIndex.end());
	}
	Card* GetCardWithNum(short num)
	{
		if (num > 0 && num < 4) {
			return &m_cards.at(m_cardIndex.at(num)); 
		}
		return nullptr;
	}

private:
	std::array<Card, 52> m_cards = {
		1, 1, 1, 1,
		2, 2, 2, 2,
		3, 3, 3, 3,
		4, 4, 4, 4,
		5, 5, 5, 5,
		6, 6, 6, 6,
		7, 7, 7, 7,
		8, 8, 8, 8,
		9, 9, 9, 9,
		10, 10, 10, 10,
		11, 11, 11, 11,
		12, 12, 12, 12,
		13, 13, 13, 13
	};
	std::vector<short> m_cardIndex;
};

class Player
{
public:
	Player(unsigned int currentDollar): m_currentDollar(currentDollar) {}
	~Player() {}
	unsigned int GetCurrentDollar()
	{
		return m_currentDollar;
	}

	void SetBetDollar(unsigned int betDollar)
	{

		m_betDollar = betDollar <= m_currentDollar ? betDollar : m_currentDollar;
	}
	void SetBetResult(bool bWin)
	{
		if (bWin) {
			m_currentDollar += m_betDollar;
		} else {
			m_currentDollar -= (m_currentDollar >= m_betDollar) ? m_betDollar : m_currentDollar;
		}
	}
private:
	Player() {};
	unsigned int m_currentDollar;
	unsigned int m_betDollar;
};

class AceyDucey
{
public:
	AceyDucey(unsigned int iStartDollars = 100);
	~AceyDucey();
	void Introduction();
	void RoundStart();
	bool IsGameOver();
private:
	unsigned int m_startDollars;
	Player* m_player;
	CardBoard m_cardBoard;
};