/*
 * server.h
 *
 *  Created on: Jun 3, 2024
 *      Author: Fady Emad
 */
/***************************includes**********************/
#include "card.h"
#include "terminal.h"
/*********************************************************/


#ifndef SERVER_H
#define SERVER_H



typedef unsigned uint32_t;

typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef enum EN_transState_t
{
	APPROVED,
	DECLINED_INSUFFECIENT_FUND,
	DECLINED_STOLEN_CARD,
	FRAUD_CARD,
	INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef enum EN_serverError_t
{
	SERVER_OK,
	SAVING_FAILED,
	TRANSACTION_NOT_FOUND,
	ACCOUNT_NOT_FOUND,
	LOW_BALANCE
}EN_serverError_t;


typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;



/***************************API's**********************/
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_transaction_t* termData, ST_accountsDB_t* accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData);
EN_accountState_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
/******************************************************/


#endif
