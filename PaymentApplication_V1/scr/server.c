/*
 * server.c
 *
 *  Created on: Jun 3, 2024
 *      Author: Fady Emad
 */

/***************************includes**********************/
#include "server.h"
#include <stdio.h>
#include <string.h>
/*********************************************************/

/***************************Global variables**********************/
//Global object of structure for found account in the database
ST_accountsDB_t* foundAccount = NULL;

//Index
uint8_t INDEX;

//The accounts  Database
ST_accountsDB_t dataBase[] =
{
		{3000.0,	RUNNING,	"3456123567456789"},
		{20000.0,	RUNNING,	"5807007076043875"},
		{9255.25,	RUNNING,	"5616495789163412",},
		{15070.25,	BLOCKED,	"4512678324393423"},
		{11040.0,	RUNNING,	"2532186464493213"},
		{2000.50,	RUNNING,	"6548237546546546"},
		{0.00, 		RUNNING,	"9713624865745474"},
		{1.00,  	RUNNING,	"7933453534148546" },
		{ 50.1, 	RUNNING,	"8257555406406435"},
		{ 0.63, 	BLOCKED,	"4554353678987654"},
};
//index of the found account
uint8_t INDEX;
ST_transaction_t transactions[] = {0};

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

	uint8_t isValid = isValidAccount((ST_cardData_t*)transData, dataBase);
	if (isValid == SERVER_OK) {
		uint32_t isBLOCKED = isBlockedAccount(foundAccount);
		if (isBLOCKED == RUNNING) {

			uint8_t isAmountAv = isAmountAvailable(transData, foundAccount);
			if (isAmountAv == SERVER_OK) {

				saveTransaction(transData);

				return APPROVED;
			}
			else if (isAmountAv == LOW_BALANCE) {
				return DECLINED_INSUFFECIENT_FUND;
			}
		}
		else if(isBLOCKED==BLOCKED)
		{

			return DECLINED_STOLEN_CARD;
		}
	}
	else {
		return FRAUD_CARD;
	}
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
	//getting number of elements in the database
	uint32_t sizeDB = sizeof(dataBase) / sizeof(ST_accountsDB_t);

	for (uint32_t i = 0; i < sizeDB; i++) {
		//to detect the found account and pass it to isAmountAvaliable later

		ST_accountsDB_t* currentAccount = (accountRefrence + i);

		if (strcmp(cardData->primaryAccountNumber,currentAccount->primaryAccountNumber)==0) {

			printf("\nAccount is Valid!");
			foundAccount = currentAccount;

			INDEX = i;
			return SERVER_OK;
		}
	}
	printf("\n%s", "Account is not Valid!");
	return ACCOUNT_NOT_FOUND;
}
EN_accountState_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	if (accountRefrence->state == BLOCKED) {

		return BLOCKED;
	}
	else if (accountRefrence->state == RUNNING) {
		printf("\n%s", "your account is Running");
		return RUNNING;
	}
}
EN_serverError_t isAmountAvailable(ST_transaction_t* termData, ST_accountsDB_t* accountRefrence) {

	if (accountRefrence->balance < termData->terminalData.transAmount) {



		return LOW_BALANCE;
	}
	else
	{


		return SERVER_OK;
	}
}
uint8_t lastTransactionNum = 0;
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	transactions[lastTransactionNum].cardHolderData = transData->cardHolderData;
	transactions[lastTransactionNum].terminalData = transData->terminalData;
	transactions[lastTransactionNum].transactionSequenceNumber++;

	//editing the database
	foundAccount->balance -= transactions[lastTransactionNum].terminalData.transAmount;
	printf("your transaction is done and your new balance is: %f", foundAccount->balance);
	fflush(stdin); fflush(stdout);
	uint32_t isSaved = getTransaction(transactions[lastTransactionNum].transactionSequenceNumber, transData);

	//increment the index
	lastTransactionNum++;
	if (isSaved == SERVER_OK) {
		return SERVER_OK;
	}
	else
	{
		return SAVING_FAILED;
	}
}


EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
	if (transactionSequenceNumber == transData->transactionSequenceNumber) {
		return SERVER_OK;
	}
	else {
		return TRANSACTION_NOT_FOUND;
	}
}
