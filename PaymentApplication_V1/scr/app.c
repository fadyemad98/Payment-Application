/*
 * app.c
 *
 *  Created on: Jun 3, 2024
 *      Author: Fady Emad
 */

/***************************includes**********************/
#include <stdio.h>
#include "stdlib.h"
#include "card.h"
#include "terminal.h"
#include "server.h"
/*********************************************************/



void appStart(void) {

	ST_cardData_t Customer_cardData ;
	ST_cardData_t* Custom_ptr = &Customer_cardData;
	ST_terminalData_t Terminal;
	ST_terminalData_t* Term_ptr = &Terminal;


	while (1)
	{
		if (getCardHolderName(Custom_ptr) == WRONG_NAME) {
			printf("XX-------XX-->Please re-enter your name: \n");
			fflush(stdin);
			fflush(stdout);}
		else {
			printf("------- SUCCESS!\n");
			fflush(stdin);
			fflush(stdout);
			break;
		}
	}

	while (1) {
		if (getCardExpiryDate(Custom_ptr) == WRONG_EXP_DATE){ printf("Please re-enter the date in a right formula\n");
		fflush(stdin);
		fflush(stdout);
		}else { printf("------- SUCCESS!\n");
		fflush(stdin);
		fflush(stdout);
		break;
		}
	}



	while(1){
		if (getCardPAN(Custom_ptr) == WRONG_PAN)
		{
		printf("-------> Please enter a valid PAN!!!!!!!!!!!\n");
		fflush(stdin);
		fflush(stdout);
		}
		else { printf("------- SUCCESS!\n");
		fflush(stdin);
		fflush(stdout);
		break;
		}

	}
	while (1) {
		if (getTransactionDate(Term_ptr) == WRONG_DATE){
		printf("XX-------XX--> Please re-enter a valid date!\n");
		fflush(stdin); fflush(stdout);
		}else {
			printf("------- SUCCESS!\n");
			fflush(stdin); fflush(stdout);
			break;
		}

	}
	uint8_t isExpired= isCardExpired(Customer_cardData, Terminal);
	if ( isExpired== EXPIRED_CARD) {
		printf("XX-------XX  YOUR CARD IS EXPIRED!\n");
		fflush(stdin); fflush(stdout);
		exit(1);

	}
	else if (isExpired == TERMINAL_OK) {
		uint8_t getTransaction = getTransactionAmount(Term_ptr);
		if (getTransaction == TERMINAL_OK) {
			uint8_t setMax = setMaxAmount(Term_ptr);
			if (setMax == TERMINAL_OK) {
				if (isBelowMaxAmount(Term_ptr) == TERMINAL_OK) {
					printf("------- Valid amount less than the maximum!");
					fflush(stdin);
					fflush(stdout);


				}
				else if (isBelowMaxAmount(Term_ptr) == EXCEED_MAX_AMOUNT) {
					printf("XX-------XX   Transaction failed!  \n\n   you have exceeded the max amount");
					fflush(stdin);
					fflush(stdout);
					exit(1);
				}
			}
			else if (setMax == INVALID_MAX_AMOUNT) {
				printf("XX-------XX--> please enter a valid max amount!\n");
				fflush(stdin);
				fflush(stdout);
			}
		}
		else if (getTransaction == INVALID_AMOUNT) {
			printf("XX-------XX--> please enter a valid amount!\n");
			fflush(stdin);
			fflush(stdout);
		}

	}

	//creating the transaction
	ST_transaction_t transaction = {Customer_cardData,Terminal,APPROVED ,23};
	ST_transaction_t* transptr = &transaction;

	uint8_t validityOfTransaction= recieveTransactionData(transptr);

	if (validityOfTransaction == APPROVED) {
		printf("\n------- Transaction success: ENOUGH BALANCE!\n");
		fflush(stdin); fflush(stdout);
		printf("########################################################\n");
	}
	else if (validityOfTransaction == DECLINED_INSUFFECIENT_FUND)
	{
		printf("\nXX-------XX  Transaction failed: LOW BALANCE!\n");
		fflush(stdin); fflush(stdout);
		printf("########################################################\n");
	}
	else if (validityOfTransaction ==DECLINED_STOLEN_CARD) {
		printf("%s", "XX-------XX  your account is Blocked!\n");
		fflush(stdin); fflush(stdout);
		printf("########################################################\n");
	}
	else if (validityOfTransaction == FRAUD_CARD) {
		printf("\n%s", "XX-------XX  Account is not Valid!\n");
		fflush(stdin); fflush(stdout);
		printf("########################################################\n");
	}


}
int main() {
	while(1){
	printf("########################################################\n");
	printf("########################################################\n");
	printf("##----------Welcome to Payment Application-----------###\n");
	printf("########################################################\n");
	printf("########################################################\n\n");
	appStart();
	printf("########################################################\n");
	printf("\n\n\n\n\n\n\n\n");
	}
}
