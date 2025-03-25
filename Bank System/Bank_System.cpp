#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
#include "Header/types.h"

const std::string DATA_FILE = "ClientsData.txt";
const std::string SEPARATOR = " /##/ ";

float readNum(const std::string& msg, const std::string& separator = " ") {


    float num;

    std::cout << msg << separator;
    std::cin >> num;

    while (std::cin.fail()) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid Number! Enter a valid number:" << separator;
        std::cin >> num;
    }

    std::cin.ignore();

    return num;
}


float readNumInRange(const std::string& msg, float min, float max, const std::string& separator = " ") {

    float num;

    do {

        num = readNum(msg, separator);

    } while (num < min || num > max);

    return num;

}


float readPositiveNum(const std::string& msg, const std::string& separator = " ") {

    float num;

    do {

        num = readNum(msg, separator);

    } while (num < 1);

    return num;
}


std::string readText(const std::string& msg, const std::string& separator = " ") {

    std::string text;

    std::cout << msg << separator;
    getline(std::cin, text);

    return text;
}


char readChar(const std::string& msg, const std::string& separator = " ") {

    char letter;

    std::cout << msg << separator;
    std::cin >> letter;

    std::cin.ignore();

    return letter;
}


void clearScreen() {

    system("cls");
    std::cout << std::endl;
}


std::string Tabs(int numOfTabs) {

    std::string t;

    for (int i = 1; i <= numOfTabs; ++i) {

        t += '\t';
    }

    return t;
}


std::vector <std::string> splitText(const std::string& text, const std::string& separator = " ") {

    std::vector <std::string> vSplittedText;
    std::string word;

    int wordPos = 0;
    int separatorPos;
    int separatorLength = separator.length();


    while ((separatorPos = text.find(separator, wordPos)) != std::string::npos) {

        word = text.substr(wordPos, separatorPos - wordPos);

        if (!word.empty()) {

            vSplittedText.push_back(word);
        }

        wordPos = separatorPos + separatorLength;
    }

    if (wordPos < text.length()) {

        vSplittedText.push_back(text.substr(wordPos));
    }


    return vSplittedText;
}


void endService(const std::string& msg = "Press any key to return to main menu...") {


    std::cout << '\n' << msg;
    system("pause>0");

    clearScreen();
}

int readClientChoiceFromMenu(int numOfChoices) {

    int clientChoice = readNumInRange("Enter your choice:", 1, numOfChoices);

    return clientChoice;
}

std::string readAccountNum() {

    return readText("Enter account number:");
 }
 
 
 int readPincode() {
 
     return readPositiveNum("Enter pincode:");
 }
 
 
 std::string readClientName() {
 
     return readText("Enter client name:");
 }
 
 
 std::string readPhoneNum() {
 
     return readText("Enter phone number:");
 }
 
 
 float readAccountBalance() {
 
     return readPositiveNum("Enter account balance:", " $");
 }

 std::string readCountryPin() {

    return readText("Enter country pin:", " +");
}

int getClientIndex(const std::string& accountNum, const std::vector <types::sClientData>& vClientsData);

types::sClientData readClientData(std::vector <types::sClientData>& vClientsData) {

    types::sClientData clientData;


    clientData.accountNum = readText("Enter account number");

    while (getClientIndex(clientData.accountNum, vClientsData) != -1) {

        std::cout << "Client with account num (" << clientData.accountNum << ") is already added, ";
        clientData.accountNum = readText("Enter another account number:");
    }

    clientData.pincode = readPincode();
    clientData.name = readClientName();
    clientData.countryPin = readCountryPin();
    clientData.phoneNum = "+" + clientData.countryPin + " " + readPhoneNum();
    clientData.accountBalance = readAccountBalance();


    return clientData;
}


void readOtherClientData(types::sClientData& clientData) {

    clientData.pincode = readPincode();
    clientData.name = readClientName();
    clientData.countryPin = readCountryPin();
    clientData.phoneNum = readPhoneNum();
    clientData.accountBalance = readAccountBalance();
}


int readWithdrawAmount() {

    return readPositiveNum("\nEnter withdraw amount:", " $");
}

int getClientIndex(const std::string& accountNum, const std::vector <types::sClientData>& vClientsData) {

    int index = 0;

    for (const types::sClientData& clientData : vClientsData) {

        if (accountNum == clientData.accountNum)
            return index;

        else
            index++;
    }

    return -1;
}


std::vector <std::string> convertRecordToData(const std::string& record, const std::string& separator) {

    std::vector <std::string> vData;
    std::string data;

    int wordPos = 0;
    int separatorPos;
    int separatorLength = separator.length();


    while ((separatorPos = record.find(separator, wordPos)) != std::string::npos) {

        data = record.substr(wordPos, separatorPos - wordPos);

        if (!data.empty()) {

            vData.push_back(data);
        }

        wordPos = separatorPos + separatorLength;
    }

    if (wordPos < record.length()) {

        vData.push_back(record.substr(wordPos));
    }


    return vData;
}


types::sClientData fillClientData(const std::string& record, const std::string& separator) {

    std::vector <std::string> vData = convertRecordToData(record, separator);

    types::sClientData clientData;

    clientData.accountNum = vData[0];
    clientData.pincode = stoi(vData[1]);
    clientData.name = vData[2];
    clientData.phoneNum = vData[3];
    clientData.accountBalance = std::stof(vData[4]);

    return clientData;
}


int calcTotalBalanceOfClient(const std::vector <types::sClientData>& vClientsData) {

    int totalBalance = 0;

    for (const types::sClientData& clientData : vClientsData) {

        totalBalance += clientData.accountBalance;
    }

    return totalBalance;
}


void saveClientsToFile(const std::vector <types::sClientData>& vClientsData, const std::string& fileName = DATA_FILE, const std::string& separator = SEPARATOR);

void confirmAndProcessTransaction(int index, int moneyAmount, std::vector <types::sClientData>& vClientsData) {

    char sureToWithdraw = readChar("\nAre you sure you want to perform this transaction (y/n):");

    if (tolower(sureToWithdraw) == 'y') {

        vClientsData[index].accountBalance += moneyAmount;
        saveClientsToFile(vClientsData);
    }
}


void returnToMenu(types::eReturnToMenu menu = types::eReturnToMenu::MAIN_MENU) {

    switch (menu) {

    case types::eReturnToMenu::MAIN_MENU:

        endService();
        break;


    case types::eReturnToMenu::TRANSACTIONS_MENU:

        endService("Press 'Enter' key to return to transactions menu...");
        break;
    }
}

void printMainMenuScreen() {

    std::cout << "\t---- Main Menu ----\n";
    std::cout << "=====================================\n";
    std::cout << "[1] Add New Client\n";
    std::cout << "[2] Show All Clients\n";
    std::cout << "[3] Update Client Info\n";
    std::cout << "[4] Delete Client\n";
    std::cout << "[5] Find Client\n";
    std::cout << "[6] Transactions\n";
    std::cout << "[7] Exit\n";
    std::cout << "=====================================" << std::endl;
}


void printTransactionMenu() {

    std::cout << "\t---- Transaction Menu ----\n";
    std::cout << "====================================\n";
    std::cout << "[1] Deposit\n";
    std::cout << "[2] Withdraw\n";
    std::cout << "[3] Show Balances\n";
    std::cout << "[4] Return to main menu\n";
    std::cout << "====================================" << std::endl;
}


void printClientsListHeader(int numOfClients) {

    std::cout << '\n' << Tabs(4) << "Clients List (" << numOfClients << ") Client/s\n";

    
    std::cout << std::left;

    std::cout << "\n---------------------------------------------------------------------------------------\n";
    std::cout << "\n| " << std::setw(15) << "Account Num";
    std::cout << "| " << std::setw(10) << "Pincode";
    std::cout << "| " << std::setw(25) << "Client Name";
    std::cout << "| " << std::setw(20) << "Phone";
    std::cout << "| " << std::setw(10) << "Balance\n";
    std::cout << "\n---------------------------------------------------------------------------------------" << std::endl;
}


void printClientsListBody(const types::sClientData& clientData) {

    std::cout << std::left;


    std::cout << "| " << std::setw(15) << clientData.accountNum;
    std::cout << "| " << std::setw(10) << clientData.pincode;
    std::cout << "| " << std::setw(25) << clientData.name;
    std::cout << "| " << std::setw(20) << clientData.phoneNum;
    std::cout << "| $" << std::setw(10) << clientData.accountBalance << std::endl;
}


void printFoundedClient(const types::sClientData& clientData) {

    std::cout << "\nAccount Number: " << clientData.accountNum;
    std::cout << "\nPincode: " << clientData.pincode;
    std::cout << "\nClient Name: " << clientData.name;
    std::cout << "\nPhone Number: " << clientData.phoneNum;
    std::cout << "\nAccount Balance: $" << clientData.accountBalance << std::endl;
}


void printBalancesListHeader(int numOfClients) {

    std::cout << Tabs(4) << "Balances List (" << numOfClients << ") Client/s\n";


    std::cout << std::left;

    std::cout << "\n-----------------------------------------------------------------\n";
    std::cout << "\n| " << std::setw(15) << "Account Num";
    std::cout << "| " << std::setw(25) << "Client Name";
    std::cout << "| " << std::setw(10) << "Balance\n";
    std::cout << "\n------------------------------------------------------------------" << std::endl;
}


void printBalancesListBody(const types::sClientData& clientData) {

    std::cout << std::left;


    std::cout << "| " << std::setw(15) << clientData.accountNum;
    std::cout << "| " << std::setw(25) << clientData.name;
    std::cout << "| $" << std::setw(10) << clientData.accountBalance << std::endl;
}

std::vector <types::sClientData> loadClientsDataFromFileToVec(const std::string& fileName = DATA_FILE, const std::string& separator = SEPARATOR) {

    std::vector <types::sClientData> vClientsData;

    std::fstream File;

    File.open(fileName, std::ios::in);

    if (File.is_open()) {

        std::string currentClientData;

        while (std::getline(File, currentClientData)) {

            types::sClientData clientData = fillClientData(currentClientData, separator);

            vClientsData.push_back(clientData);
        }

        File.close();
    }

    return vClientsData;
}


std::string convertDataToRecord(const types::sClientData& clientData, const std::string& separator = SEPARATOR);

bool saveClientsToFileAfterDelete(const std::vector <types::sClientData>& vClientsData, const std::string& fileName = DATA_FILE, const std::string& separator = SEPARATOR) {

    std::fstream File;

    File.open(fileName, std::ios::out);

    if (File.is_open()) {

        for (const types::sClientData& clientData : vClientsData) {

            if (clientData.isDeleted == false) {

                File << convertDataToRecord(clientData, separator) << '\n';
            }
        }

        File.close();

        return true;
    }

    else
        return false;
}


bool saveRecordToFile(const std::string & record, const std::string & fileName = DATA_FILE) {

    std::fstream File;

    File.open(fileName, std::ios::app);

    if (File.is_open()) {

        File << record << '\n';

        File.close();

        return true;
    }

    else
        return false;
}


std::string convertDataToRecord(const types::sClientData& clientData, const std::string& separator) {

    std::string record = "";

    record += clientData.accountNum + separator;
    record += std::to_string(clientData.pincode) + separator;
    record += clientData.name + separator;
    record += clientData.phoneNum + separator;
    record += std::to_string(clientData.accountBalance);

    return record;
}


void saveClientsToFile(const std::vector <types::sClientData>& vClientsData, const std::string& fileName, const std::string& separator) {

    for (const types::sClientData& clientData : vClientsData) {

        saveRecordToFile(convertDataToRecord(clientData));
    }
}

void addNewClient(std::vector <types::sClientData>& vClientsData) {

    types::sClientData clientData;

    clientData = readClientData(vClientsData);

    saveRecordToFile(convertDataToRecord(clientData));

    std::cout << "\nClient is Added Successfully\n";

}

void addClients() {

    std::cout << Tabs(4) << "---------------------------------------\n";
    std::cout << Tabs(6) << "Add New Client\n";
    std::cout << Tabs(4) << "---------------------------------------" << std::endl;

    std::vector <types::sClientData> vClientsData = loadClientsDataFromFileToVec();

    char addAnotherClient;

    do {

        addNewClient(vClientsData);

        addAnotherClient = readChar("\nDo you want to add another client (y/n):");

    } while (tolower(addAnotherClient) == 'y');


    returnToMenu();
}


void showAllClients() {

    std::vector <types::sClientData> vClientsData = loadClientsDataFromFileToVec();

    if (vClientsData.empty())
        std::cout << "\nThere isn't any client had been added yet!" << std::endl;

    else
    {

        std::cout << Tabs(4) << "-------------------------------\n";
        std::cout << Tabs(5) << "Show All Clients\n";
        std::cout << Tabs(4) << "-------------------------------" << std::endl;

        printClientsListHeader(vClientsData.size());

        for (const types::sClientData& clientData : vClientsData) {

            printClientsListBody(clientData);
        }
    }

    returnToMenu();
}

void updateClientDataByAccountNum(const std::string& accountNum, std::vector <types::sClientData>& vClientsData) {

    int clientIndex = getClientIndex(accountNum, vClientsData);

    if (clientIndex != -1) {

        printFoundedClient(vClientsData[clientIndex]);

        char areSureToUpdate = readChar("\nAre you sure you want to update client info (y/n):");

        if (tolower(areSureToUpdate) == 'y') {

            readOtherClientData(vClientsData[clientIndex]);
            saveClientsToFile(vClientsData);

            std::cout << "\nClient Info Updated Successfully" << std::endl;
        }
    }

    else {

        std::cout << "\nClient with account number (" << accountNum << ") isn't founded" << std::endl;
    }
}

void updateClientData() {

    std::cout << Tabs(4) << "----------------------------\n";
    std::cout << Tabs(5) << "Update Client Info\n";
    std::cout << Tabs(4) << "----------------------------" << std::endl;

    std::vector <types::sClientData> vClientsData = loadClientsDataFromFileToVec();

    std::string accountNum = readAccountNum();

    updateClientDataByAccountNum(accountNum, vClientsData);

    returnToMenu();
}

void deleteClientByAccountNum(const std::string& accountNum, std::vector <types::sClientData>& vClientsData) {

    int clientIndex = getClientIndex(accountNum, vClientsData);

    if (clientIndex != -1) {

        printFoundedClient(vClientsData[clientIndex]);

        char AreSureToDelete = readChar("\nAre you sure you want to delete client info (y/n):");

        if (tolower(AreSureToDelete) == 'y')
        {
            vClientsData[clientIndex].isDeleted = true;

            saveClientsToFileAfterDelete(vClientsData);
            vClientsData = loadClientsDataFromFileToVec();
        }
    }

    else {

        std::cout << "\nClient with account number (" << accountNum << ") isn't founded" << std::endl;
    }
}

void deleteClient() {

    std::cout << Tabs(4) << "------------------------------\n";
    std::cout << Tabs(5) << "Delete Client\n";
    std::cout << Tabs(4) << "------------------------------" << std::endl;

    std::vector <types::sClientData> vClientsData = loadClientsDataFromFileToVec();

    std::string accountNum = readAccountNum();

    deleteClientByAccountNum(accountNum, vClientsData);

    returnToMenu();
}

void findClientByAccountNum(const std::string& accountNum, const std::vector <types::sClientData>& vClientsData) {

    int clientIndex = getClientIndex(accountNum, vClientsData);


    if (clientIndex == -1) {

        std::cout << "\nClient with account number (" << accountNum << ") isn't founded" << std::endl;
    }

    else {

        printFoundedClient(vClientsData[clientIndex]);
    }
}

void findClient() {

    std::vector <types::sClientData> vClientsData = loadClientsDataFromFileToVec();

    std::cout << Tabs(4) << "------------------------------\n";
    std::cout << Tabs(5) << "Find Client\n";
    std::cout << Tabs(4) << "------------------------------" << std::endl;

    std::string accountNum = readAccountNum();

    findClientByAccountNum(accountNum, vClientsData);
    endService();
}

void findClientGetIndexPrintClient(int& clientIndex, const std::vector <types::sClientData>& vClientsData) {

    std::string accountNum = readAccountNum();


    while ((clientIndex = getClientIndex(accountNum, vClientsData)) == -1) {

        std::cout << "\nClient with account number (" << accountNum << ") isn't founded, ";
        accountNum = readAccountNum();
    }


    std::cout << "\nThe following are the clients data:\n";
    printFoundedClient(vClientsData[clientIndex]);
}

void Deposit() {

    std::vector <types::sClientData> vClientsData = loadClientsDataFromFileToVec();


    std::cout << Tabs(4) << "------------------------\n";
    std::cout << Tabs(5) << "Deposit\n";
    std::cout << Tabs(4) << "------------------------" << std::endl;


    int clientIndex;
    findClientGetIndexPrintClient(clientIndex, vClientsData);


    int depositAmount = readPositiveNum("\nEnter deposit amount:");
    
    confirmAndProcessTransaction(clientIndex, depositAmount, vClientsData);

    returnToMenu(types::eReturnToMenu::TRANSACTIONS_MENU);
}


void Withdraw() {

    std::vector <types::sClientData> vClientsData = loadClientsDataFromFileToVec();

    std::cout << Tabs(4) << "------------------------\n";
    std::cout << Tabs(5) << "Withdraw\n";
    std::cout << Tabs(4) << "------------------------" << std::endl;


    int clientIndex;
    findClientGetIndexPrintClient(clientIndex, vClientsData);


    int withdrawAmount = readWithdrawAmount();

    while (withdrawAmount > vClientsData[clientIndex].accountBalance) {

        std::cout << "\nAmount exceeds the account balance, you can withdraw up to $" << vClientsData[clientIndex].accountBalance << '\n';
        withdrawAmount = readWithdrawAmount();
    }


    confirmAndProcessTransaction(clientIndex, withdrawAmount * -1, vClientsData);

    returnToMenu(types::eReturnToMenu::TRANSACTIONS_MENU);
}


void showBalances() {

    std::vector <types::sClientData> vClientsData = loadClientsDataFromFileToVec();

    printBalancesListHeader(vClientsData.size());

    int totalBalance = 0;

    for (const types::sClientData& clientData : vClientsData) {

        printBalancesListBody(clientData);
        totalBalance += clientData.accountBalance;
    }

    std::cout << "-------------------------------------------------------------------\n";

    std::cout << '\n' << Tabs(4) << "Total Balance: $" << totalBalance << std::endl;

    returnToMenu(types::eReturnToMenu::TRANSACTIONS_MENU);
}

void applyTransaction(types::eTransactionsMenu transactionChoose) {

    clearScreen();

    switch (transactionChoose) {

    case types::eTransactionsMenu::DEPOSIT:

        Deposit();
        break;

    case types::eTransactionsMenu::WITHDRAW:

        Withdraw();
        break;

    case types::eTransactionsMenu::SHOW_ALL_BALANCES:

        showBalances();
        break;

    case types::eTransactionsMenu::RETURN_TO_MAIN_MENU:

        return;
    }
}

void Transactions() {

    types::eTransactionsMenu clientChoice;

    do {

        printTransactionMenu();

        clientChoice = (types::eTransactionsMenu)readClientChoiceFromMenu(4);

        applyTransaction(clientChoice);

    } while (clientChoice != types::eTransactionsMenu::RETURN_TO_MAIN_MENU);
}


void Exit() {

    std::cout << Tabs(4) << "------------------------\n";
    std::cout << Tabs(5) << "Exit\n";
    std::cout << Tabs(4) << "------------------------\n";
}

void applyClientService(types::eMainMenu clientService) {

    clearScreen();

    switch (clientService) {

    case types::eMainMenu::ADD_NEW_CLIENT:

        addClients();
        break;

    case types::eMainMenu::SHOW_ALL_CLIENTS:

        showAllClients();
        break;

    case types::eMainMenu::UPDATE_CLIENT_INFO:

        updateClientData();
        break;

    case types::eMainMenu::DELETE_CLIENT:

        deleteClient();
        break;

    case types::eMainMenu::FIND_CLIENT:

        findClient();
        break;

    case types::eMainMenu::TRANSACTIONS:

        Transactions();
        break;

    case types::eMainMenu::EXIT:

        Exit();
        break;
    }
}


void startProgram() {

    types::eMainMenu clientService;

    do {

        printMainMenuScreen();

        clientService = (types::eMainMenu)readClientChoiceFromMenu(7);

        applyClientService(clientService);

    } while (clientService != types::eMainMenu::EXIT);

}

int main() {

    startProgram();


    return 0;
}