#pragma once

#include <iostream>

enum eMainMenu {

    ADD_NEW_CLIENT = 1,
    SHOW_ALL_CLIENTS = 2,
    UPDATE_CLIENT_INFO = 3,
    REMOVE_CLIENT = 4,
    FIND_CLIENT = 5,
    TRANSACTIONS = 6,
    EXIT = 7
}

enum eTransactions {

    DEPOSIT = 1,
    WITHDRAW = 2,
    SHOW_ALL_BALANCES = 3,
    RETURN_TO_MAIN_MENU = 4 
}

struct sClient {

    std::string accountNum;
    int pincode;
    std::string name;
    std::string countryPin;
    std::string phone;
    float accountBalance;
}