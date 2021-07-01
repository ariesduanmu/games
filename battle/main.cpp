#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>


typedef  enum {
	SHIP_TYPE_DESTROYER,
	SHIP_TYPE_CRUISERS,
	SHIP_TYPE_AIRCRAFT,
} ShipType;

typedef unsigned int ShipNumber ;

struct Coordinate {
	unsigned int x;
	unsigned int y;
};

class Game
{
public:
	Game()
	{
		m_shipLiveInfo.clear();
		for (auto iter = m_shipNumberInfo.begin(); iter != m_shipNumberInfo.end(); ++iter) {
			unsigned int iLive = 0;
			auto fleetIter = m_shipFleetInfo.find(iter->second);
			if (fleetIter != m_shipFleetInfo.end()) {
				iLive = fleetIter->second;
			}
			m_shipLiveInfo.insert(std::pair<ShipNumber, unsigned int>(iter->first, iLive));
		}
		InitMap();
	}
	virtual ~Game() {}
	void Attack(const Coordinate& coordinate, ShipNumber& iAttackShip)
	{
		iAttackShip = 0;
		if (coordinate.x <= m_iMapWidth && coordinate.y <= m_iMapHeight && coordinate.x > 0 && coordinate.y > 0) {
			iAttackShip = m_gameMap[coordinate.x - 1][coordinate.y - 1];
			std::cout << "Attack " << iAttackShip << std::endl;
			m_gameMap[coordinate.x - 1][coordinate.y - 1] = 0;
			auto iter = m_shipLiveInfo.find(iAttackShip);
			if (iter != m_shipLiveInfo.end()) {
				--(iter->second);	
			}
		}
	}

	bool IsShipStillSurvive(ShipNumber& iShip)
	{
		std::map<ShipNumber, unsigned int>::iterator iter = m_shipLiveInfo.find(iShip);
		if (iter == m_shipLiveInfo.end()) {
			return true;
		}
		return (iter->second > 0);
	}

	bool IsGameOver()
	{
		for (auto iter = m_shipLiveInfo.begin(); iter != m_shipLiveInfo.end(); ++iter) {
			if (iter->second > 0) {
				return false;
			}
		}
		return true;
	}
	

	void ShipLost(unsigned int& iDestroyer, unsigned int& iCruisers, unsigned int& iAircraft)
	{
		for (auto iter = m_shipLiveInfo.begin(); iter != m_shipLiveInfo.end(); ++iter) {
			auto shipIter = m_shipNumberInfo.find(iter->first);
			if (shipIter == m_shipNumberInfo.end()) {
				continue;
			}
			ShipType shipType = shipIter->second;
			if (iter->second == 0) {
				switch (shipType) {
					case SHIP_TYPE_DESTROYER:
						++iDestroyer;
						break;
					case SHIP_TYPE_CRUISERS:
						++iCruisers;
						break;
					case SHIP_TYPE_AIRCRAFT:
						++iAircraft;
						break;
				}
			}
		}
	}


	static const unsigned int m_iMapWidth = 6;
	static const unsigned int m_iMapHeight = 6;

private:
	
	std::vector<std::vector<ShipNumber>> m_gameMap;
	std::map<ShipNumber, unsigned int> m_shipLiveInfo;
	static const std::map<ShipType, unsigned int> m_shipFleetInfo;
	static const std::map<unsigned int, ShipType> m_shipNumberInfo;

	void InitMap()
	{
		// TODO: random map algorithm
		m_gameMap = {
			{0,0,0,2,2,6},
			{0,4,4,4,6,0},
			{5,0,0,6,0,0},
			{5,0,6,0,0,3},
			{5,1,0,0,0,3},
			{5,0,1,0,0,3},
		};
	}

};

const std::map<ShipNumber, ShipType> Game::m_shipNumberInfo = {
	{1, SHIP_TYPE_DESTROYER},
	{2, SHIP_TYPE_DESTROYER},
	{3, SHIP_TYPE_CRUISERS},
	{4, SHIP_TYPE_CRUISERS},
	{5, SHIP_TYPE_AIRCRAFT},
	{6, SHIP_TYPE_AIRCRAFT},
};

const std::map<ShipType, unsigned int> Game::m_shipFleetInfo = {
	{SHIP_TYPE_DESTROYER, 2},
	{SHIP_TYPE_CRUISERS, 3},
	{SHIP_TYPE_AIRCRAFT, 4}
};

int main(int argc, char** argv)
{
	Game game = Game();
	Coordinate cor;
	std::string strPosition;
	std::vector<unsigned int> positionNums;
	ShipNumber iAttack;
	bool isFirstStart = true;
	unsigned int iDestroyerLost = 0;
	unsigned int iCruisersLost = 0;
	unsigned int iAircraftLost = 0;
	while (!game.IsGameOver()) {
		iDestroyerLost = 0;
		iCruisersLost = 0;
		iAircraftLost = 0;
		
		if (isFirstStart) {
			std::cout << "Start Game" << std::endl;
			isFirstStart = false;
		} else {
			std::cout << "Try Again" << std::endl;
		}

		positionNums.clear();
		std::cin >> strPosition;
		std::stringstream ss(strPosition);
		for (unsigned int i; ss>>i;) {
			positionNums.push_back(i);
			if (ss.peek() == ',') {
				ss.ignore();
			}
		}
		if (positionNums.size() < 2) {
			std::cout << "InValid Input" << std::endl;
			continue;
		}
		cor.x = positionNums[0];
		cor.y = positionNums[1];

		if (cor.x > Game::m_iMapWidth || cor.x == 0 || cor.y > Game::m_iMapHeight || cor.y == 0) {
			std::cout << "InValid Input" << std::endl;
			continue;
		}

		game.Attack(cor, iAttack);
		if (iAttack > 0) {
			std::cout << "A Direction Hit On Ship Number " << iAttack << std::endl;
			if (!game.IsShipStillSurvive(iAttack)) {
				std::cout << "And you sunk it. Hurrah for the good guys." << std::endl;
				std::cout << "So far the bad gut have lost" << std::endl;
				game.ShipLost(iDestroyerLost, iCruisersLost, iAircraftLost);
				std::cout << iDestroyerLost << " Destroyer(s), " << iCruisersLost;
				std::cout << " Cruiser(s), And " << iAircraftLost << " Aircraft Carrier(s)." << std::endl;
			}
		} else {
			std::cout << "Splash!" << std::endl;
		}
	}
	
	return 0;
}