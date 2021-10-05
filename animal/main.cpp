#include <sqlite3.h>
#include <iostream>
#include <string>

static int max_id_callback( void *max_id, int count, char **data, char **columns) {

    const char *max_as_text = data[0];
    std::cout << max_as_text << std::endl;
    return 0;
}

void ExecuteSqlite(sqlite3* DB, const std::string& strSQL)
{
    char* messaggeError;
    int iRet = sqlite3_exec(DB, strSQL.c_str(), NULL, 0, &messaggeError);
    if (iRet != SQLITE_OK) {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Success" << std::endl;
}

void InitTable(sqlite3* DB)
{
	std::string strCreateAnimalSQL = "CREATE TABLE IF NOT EXISTS ANIMAL("
				                      "ID INT PRIMARY KEY     NOT NULL, "
				                      "NAME           TEXT    NOT NULL);";
	std::string strCreateFeatureSQL = "CREATE TABLE IF NOT EXISTS FEATURE("
				                      "ID INT PRIMARY KEY     NOT NULL, "
				                      "NAME           TEXT    NOT NULL);";
	std::string strCreateAnimalFeatureSQL = "CREATE TABLE IF NOT EXISTS ANIMAL_FEATURE("
				                      "ID INT PRIMARY KEY     NOT NULL, "
				                      "ANIMAL_ID      INT    NOT NULL,"
				                      "ANIMAL_NAME    TEXT    NOT NULL,"
				                      "FEATURE_ID     INT    NOT NULL,"
				                      "FEATURE_NAME   TEXT    NOT NULL,"
				                      "FEATURE_HAS    INT    DEFAULT 0);";
	ExecuteSqlite(DB, strCreateAnimalSQL);
	ExecuteSqlite(DB, strCreateFeatureSQL);
	ExecuteSqlite(DB, strCreateAnimalFeatureSQL);
}

void InsertAnimal(sqlite3* DB, std::string strName)
{
	std::string sql = "INSERT INTO ANIMAL VALUES(1, '" + strName + "');";
	ExecuteSqlite(DB, sql);
	
	char* messaggeError;
	sqlite3_exec(DB, "SELECT MAX(ID) from ANIMAL;", max_id_callback, 0, &messaggeError);
	

}



int main()
{
    std::cout << "Sqlite version: " << sqlite3_libversion() << std::endl;

    sqlite3* mydb;
    int iRet = sqlite3_open("test.db", &mydb);
    if (iRet != SQLITE_OK) {
    	std::cerr << "Failed to open db file:" << iRet << std::endl;
    	return 0;
    }

    InsertAnimal(mydb, "test");
    
    sqlite3_close(mydb);

    return 0;
}