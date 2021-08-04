#include "manInforTable.h"
#include "sqlite3.h"
#include "callback.h"
#include <iostream>
#include <iomanip>
#include <string>

int manInforTable::manID = 0;

manInforTable::manInforTable(const std::string& dirDB)
{
	sqlite3* DB;
	this->dirToDB = dirDB;
	rc = sqlite3_open(dirToDB.c_str(), &DB);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Connect to DB failed!\n");
	}
	else
	{
		fprintf(stdout, "Connect to DB successful!\n");
	}

	sqlite3_close(DB);
}

manInforTable::~manInforTable()
{
	if (errMsg)
	{
		delete errMsg;
		errMsg = nullptr;
	}
}

// DB
void manInforTable::connectToDB()
{
    sqlite3* DB;
    rc = sqlite3_open(dirToDB.c_str(), &DB);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Connect to DB failed!\n");
    }
    else
    {
        fprintf(stdout, "Connect to DB successful!\n");
    }

    sqlite3_close(DB);
}

// Get-set
void manInforTable::setDir(const std::string& dirToDB)
{
    this->dirToDB = dirToDB;
}

std::string manInforTable::getDir()
{
    return this->dirToDB;
}


void manInforTable::createTable()
{
	sqlCommand = "CREATE TABLE IF NOT EXISTS manInFor("
		"ManID INT PRIMARY KEY NOT NULL,"
		"Name VARCHAR(255) NOT NULL,"
		"Location VARCHAR(255) NOT NULL"
		//"AreaPassing TEXT NOT NULL"
		");"
		;

	sqlite3* DB;
	rc = sqlite3_open(dirToDB.c_str(), &DB);
	rc = sqlite3_exec(DB, sqlCommand.c_str(), callbackValues, 0, &errMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", errMsg);
		free(errMsg);
	}
	else
	{
		fprintf(stdout, "Created manInfor Table successfull\n");
	}


	sqlite3_close(DB);
}

void manInforTable::droptable()
{
	sqlCommand = "DROP TABLE IF EXISTS manInFor;";

	sqlite3* DB;
	rc = sqlite3_open(dirToDB.c_str(), &DB);
	rc = sqlite3_exec(DB, sqlCommand.c_str(), callbackValues, 0, &errMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", errMsg);
		free(errMsg);
	}
	else
	{
		fprintf(stdout, "Drop manInfor Table successfull\n");
	}


	sqlite3_close(DB);
}

void manInforTable::insertValues()
{

	mManInfor.push_back(manInformation);

	//std::string passingString = plusPassing(manInformation.mArea);
	sqlCommand = "INSERT INTO manInfor(ManID,Name,Location) "
		"VALUES(" + std::to_string(manInformation.Man_ID) + ",'" + manInformation.mName + "', '"
		+ manInformation.mName + "');"
		;
	
	sqlite3* DB;
    rc = sqlite3_open(dirToDB.c_str(), &DB);
	rc = sqlite3_exec(DB, sqlCommand.c_str(), callbackValues, 0, &errMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", errMsg);
		free(errMsg);
	}
	else
	{
		fprintf(stdout, "Insert value into manInfor Table successfull\n");
	}


	sqlite3_close(DB);
	manInformation.reset();
}

void manInforTable::insertValuesAuto()
{

	sqlCommand = "DELETE FROM manInfor;";

	for (int idex = 0; idex < 10; idex++)
	{
		manInforTable::manID++;
		ManInfor inforOfMan;
		inforOfMan.Man_ID = manInforTable::manID;
		inforOfMan.mName = "John " + std::to_string(idex + 1);
		
		if (idex % 2 == 0)
		{
			inforOfMan.mLocation = "Da Nang";
			/*inforOfMan.mArea = {
				"Da Nang", "Hue", "Quang Nam"
			};*/
		}
		else
		{
			if (idex % 3 == 0)
				inforOfMan.mLocation = "Hoa Khanh";
			else
				inforOfMan.mLocation = "Quang Nam";
			/*inforOfMan.mArea = {
				"Sai Gon", "Gia Lai", "Da Nang"
			};*/
		}

		//std::string passingString = plusPassing(inforOfMan.mArea);
		sqlCommand = "INSERT INTO manInfor(ManID,Name,Location)"
			"VALUES(" + std::to_string(inforOfMan.Man_ID) + ",'" + inforOfMan.mName + "', '"
			+ inforOfMan.mLocation + "');"
			;

		sqlite3* DB;
		rc = sqlite3_open(dirToDB.c_str(), &DB);
		rc = sqlite3_exec(DB, sqlCommand.c_str(), callbackValues, 0, &errMsg);

		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "Error: %s\n", errMsg);
			free(errMsg);
		}
		else
		{
			fprintf(stdout, "Insert manInfor Table successfull\n");
		}


		sqlite3_close(DB);
	}
}

void manInforTable::deleteValues()
{
	// delete all
	sqlCommand = "DELETE FROM manInfor;";

	sqlite3* DB;
	rc = sqlite3_open(dirToDB.c_str(), &DB);
	rc = sqlite3_exec(DB, sqlCommand.c_str(), callbackValues, 0, &errMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", errMsg);
		free(errMsg);
	}
	else
	{
		fprintf(stdout, "Delete all Values of manInfor Table successfull\n");
	}


	sqlite3_close(DB);
}

void manInforTable::updateValues()
{

}

void manInforTable::filterValues()
{
	std::cout << "\n\n\t**********List of Persons Who are in isoloated place**************" << std::endl;
	
	sqlite3* DB;
	rc = sqlite3_open(dirToDB.c_str(), &DB);

	sqlCommand = "SELECT Name, Location AS In_Isolated FROM manInFor LIMIT 1;";
	rc = sqlite3_exec(DB, sqlCommand.c_str(), callbackColName, 0, &errMsg);

	sqlCommand = "SELECT Name, Location FROM manInFor WHERE Location IN (SELECT namOfArea FROM Isolated);";
	rc = sqlite3_exec(DB, sqlCommand.c_str(), callbackValues, 0, &errMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", errMsg);
		free(errMsg);
	}


	sqlite3_close(DB);
}

void manInforTable::displayTable()
{
	std::cout << "\n\n\t************************* Information of Mans *************************";
	sqlCommand = "SELECT * FROM manInfor;";
	std::string sqlColName = "SELECT * FROM manInfor LIMIT 1;";
	sqlite3* DB;
	rc = sqlite3_open(dirToDB.c_str(), &DB);
	rc = sqlite3_exec(DB, sqlColName.c_str(), callbackColName, 0, &errMsg);
	rc = sqlite3_exec(DB, sqlCommand.c_str(), callbackValues, 0, &errMsg);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "Error: %s\n", errMsg);
		free(errMsg);
	}

	sqlite3_close(DB);
}

void manInforTable::increasingID()
{
	manInforTable::manID++;
}

int manInforTable::getManID()
{
	return manInforTable::manID;
}

void manInforTable::takeManInFor(const ManInfor& _inforOfMan)
{
	this->manInformation = _inforOfMan;
}


std::string plusPassing(std::vector<std::string> passing)
{
	std::string res = "";
    size_t len = passing.size();
    for (size_t idex = 0; idex < len; idex++)
	{
		res += passing[idex];
		if (idex + 1 < len)
			res += ", ";
	}

	return res;
}

