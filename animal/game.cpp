#include <iostream>
#include <string>

class Game
{
public:
	Game()
	{
		int iRet = sqlite3_open(strDBFilename.c_str(), &m_gamedb);
		if (iRet != SQLITE_OK) {
    		m_isDBValid = false;
    		return;
    	}

    
	}

	~Game()
	{
		if (m_isDBValid) {
			sqlite3_close(m_gamedb);
		}
	}
	void Run()
	{
		if (!m_isDBValid) {
			std::cerr << "Failed to run game" << std::endl;
			return
		}
		std::string strAnswer = "Y";
		int iSuspectAnimalID;

		while (strAnswer == "Y") {
			std::cout << "Are you thinking of an animal? ";
			std::cin >> strAnswer;
			std::cout << std::endl;
			m_isGameStart = true;
			if (IsSuccessGuessAnimal(iSuspectAnimalID)) {
				std::cout << "Why not try another animal?" << std::endl;
			} else {
				InputNewAnimal(iSuspectAnimalID)
			}
		}
		
	}
private: 
	static const std::string m_strDBFilename = "test.db";
	sqlite3* m_gamedb;
	bool m_isDBValid;
	bool IsSuccessGuessAnimal(int& iSuspectAnimalID)
	{

	}

	void InputNewAnimal(int& iSuspectAnimalID, std::string& strSuspectAnimal)
	{
		std::string strNewAmimal;
		std::string strDistingushQuestion;
		std::string strAnswer;
		std::cout << "The Animal you were thinking of was a? ";
		std::cin >> strNewAmimal;
		std::cout << std::endl;
		std::cout << "Please type in a question what would distinguish a " << strNewAmimal << " from a " << strSuspectAnimal << std::endl;
		std::cout << "? "
		std::cin >> strDistingushQuestion;
		std::cout << std::endl;
		std::cout << "For a " << strNewAmimal << " the answer would be? ";
		std::cin >> strAnswer;
		std::cout << std::endl;

		int iAnimalID = SqlInsertAnimal(strNewAmimal);
		int iQuestionID = SqlInsertFeature(strDistingushQuestion);
		SqlInsertAnimalFeature(iAnimalID, strNewAmimal, iQuestionID, strDistingushQuestion, (strAnswer == "YES"));
		SqlInsertAnimalFeature(iSuspectAnimalID, strSuspectAnimal, iQuestionID, strDistingushQuestion, (strAnswer == "NO"));

	}


	bool SqlInsertAnimal(const std::string& strNewAmimal, )
	{
		int id = sqlite3_last_insert_rowid(m_gamedb);
		std::string sql = "INSERT INTO ANIMAL VALUES(" + std::to_string(id+1) + ", '" + strNewAmimal + "');";
		id = sqlite3_last_insert_rowid(m_gamedb);

		return id;
	}

};