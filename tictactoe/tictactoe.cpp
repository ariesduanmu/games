#include <iostream>
#include <vector>
#include <algorithm>

enum Piece{
	PIECE_EMPTY = -1,
	PIECE_PLAYER_A,
	PIECE_PLAYER_B
};
enum Player{
	PLAYER_A,
	PLAYER_B
};

static const unsigned int MAX_POS = 9;
static const unsigned int EACH_LINE_ITEM = 3;

class Game
{
public:
	Player GetCurrentPlayer() const {
		return currentPlayer;
	}

	std::vector<Piece> GetPieces() const {
		return pieces;
	}

	bool IsGameOver() const {
		return (std::find(pieces.cbegin(), pieces.cend(), PIECE_EMPTY) == pieces.cend());
	}

	bool HasWinner(Player& winner) {
		if (IsThreeInLine(0, 1, 2) || IsThreeInLine(0, 3, 6) || IsThreeInLine(0, 4, 8)) {
			winner = (pieces[0] == PIECE_PLAYER_A) ? PLAYER_A : PLAYER_B;
			return true;
		}

		if (IsThreeInLine(1, 4, 7) || IsThreeInLine(3, 4, 5) || IsThreeInLine(2, 4, 6)) {
			winner = (pieces[4] == PIECE_PLAYER_A) ? PLAYER_A : PLAYER_B;
			return true;
		}
		if (IsThreeInLine(6, 7, 8) || IsThreeInLine(2, 5, 8)) {
			winner = (pieces[8] == PIECE_PLAYER_A) ? PLAYER_A : PLAYER_B;
			return true;
		}

		return false;
	}

	bool GameRound(const unsigned int pos) {
		if (pos >= MAX_POS || pieces[pos] != PIECE_EMPTY) {
			return false;
		}

		pieces[pos] = (currentPlayer == PLAYER_A) ? PIECE_PLAYER_A : PIECE_PLAYER_B;
		SwitchPlayer();
		return true;
	}

private:
	
	std::vector<Piece> pieces{std::vector<Piece>(MAX_POS, PIECE_EMPTY)};
	Player currentPlayer = PLAYER_A;

	void SwitchPlayer() {
		currentPlayer = (currentPlayer == PLAYER_A) ? PLAYER_B : PLAYER_A;
	}

	bool IsThreeInLine(const unsigned int pos1, const unsigned int pos2, const unsigned int pos3) {
		return (pieces[pos1] == pieces[pos2] && pieces[pos1] == pieces[pos3] && pieces[pos1] != PIECE_EMPTY);
	}

};

class GameStr
{
public:
	static std::string GetPlayerString(const Player player) {
		return (player == PLAYER_A) ? "A" : "B";
	}

	static std::string GetPiecesString(const std::vector<Piece>& pieces) {
		unsigned int i = 0;
		std::string strPieces;
		for (; i < MAX_POS; ++i) {
			switch (pieces[i]) {
			case PIECE_EMPTY:
				strPieces += " ";
				break;
			case PIECE_PLAYER_A:
				strPieces += "O";
				break;
			case PIECE_PLAYER_B:
				strPieces += "X";
				break;
			}

			if ((i + 1) % EACH_LINE_ITEM == 0) {
				strPieces += "\n-----\n";
			} else {
				strPieces += "|";
			}
		}
		return strPieces;
	}

	static std::string ValidPositionsString(const std::vector<Piece>& pieces) {
		std::string strPositions;
		unsigned int i = 0;
		for (; i < MAX_POS; ++i) {
			if (pieces[i] == PIECE_EMPTY) {
				if (strPositions.size() > 0) {
					strPositions += ",";
				}
				strPositions += std::to_string(i);
			}
		}
		return strPositions;
	}
};

int main(int argc, char ** agrv)
{
	Game game;
	std::vector<Piece> pieces;
	std::vector<unsigned int> positions;
	Player winner;
	unsigned int pos;
	while (true) {
		pieces = game.GetPieces();
		std::cout << "Current Board:" << std::endl;
		std::cout << GameStr::GetPiecesString(pieces) << std::endl;
		if (game.HasWinner(winner)) {
			std::cout << "Winner is:" << GameStr::GetPlayerString(winner) << std::endl;
			break;
		} else if (game.IsGameOver()) {
			std::cout << "Game Over" << std::endl;
			break;
		}

		std::cout << GameStr::GetPlayerString(game.GetCurrentPlayer()) << " your turn!!!" << std::endl;
		std::cout << "Please Choose a Position from: " << GameStr::ValidPositionsString(pieces) << std::endl;
		std::cin >> pos;
		if (!game.GameRound(pos)) {
			std::cout << "Invalid Position:" << pos << std::endl;
		}
	}
	std::cout << "Game Over!" << std::endl;
}