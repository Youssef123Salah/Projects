#pragma once

#include <iostream>

namespace types {

    enum eMainMenu {

        ADD_NEW_CLIENT = 1,

        SHOW_ALL_CLIENTS = 2,

        UPDATE_CLIENT_INFO = 3,

        DELETE_CLIENT = 4,

        FIND_CLIENT = 5,

        TRANSACTIONS = 6,

        EXIT = 7
    };

    enum eTransactionsMenu {

        DEPOSIT = 1,

        WITHDRAW = 2,

        SHOW_ALL_BALANCES = 3,

        RETURN_TO_MAIN_MENU = 4,
    };

    enum eReturnToMenu {

        MAIN_MENU = 1,

        TRANSACTIONS_MENU = 2,
    };


    struct sClientData {

        std::string accountNum;
        int pincode;
        std::string name;
        std::string countryPin;
        std::string phoneNum;
        float accountBalance;
        bool isDeleted = false;
    };
}