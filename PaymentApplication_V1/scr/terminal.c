/*
 * terminal.c
 *
 *  Created on: Jun 3, 2024
 *      Author: Fady Emad
 */

/***************************includes**********************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "terminal.h"
#include "card.h"
/*********************************************************/




typedef unsigned int uint32_t;



/*will ask for the transaction data and store it in terminal data.
 *Transaction date is 10 characters string in the format DD / MM / YYYY, e.g 25 / 06 / 2022.
 *If the transaction date is NULL, less than 10 characters or wrong format will return WRONG_DATE error, else return OK.
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	printf("Please enter the transacion date:DD/MM/YY\n");
	fflush(stdin); fflush(stdout);
	gets(termData->transactionDate);
	//after modification
	//getting month as a whole number
	uint8_t monthFirstDigit = termData->transactionDate[3] - '0';
	uint8_t monthSecondDigit = termData->transactionDate[4] - '0';
	uint8_t monthNumber = monthFirstDigit * 10 + monthSecondDigit;
	//checking if the month number is between 1 and 12 inclusive

	//getting day as a whole number
	uint8_t dayFirstDigit = termData->transactionDate[0] - '0';
	uint8_t daySecondDigit = termData->transactionDate[1] - '0';
	uint8_t dayNumber = dayFirstDigit * 10 + daySecondDigit;
	//checking if day is between 1 and 31 inclusive
	if (strlen(termData->transactionDate) < 10 || termData->transactionDate == NULL|| termData->transactionDate[2]!='/'||
			termData->transactionDate[5] != '/'|| !(monthNumber >= 1 && monthNumber <= 12)|| !(dayNumber >= 1 && dayNumber <= 31))
		return WRONG_DATE;
	return TERMINAL_OK;
}



//This function compares the card expiry date with the transaction date.
//If the card expiration date is before the transaction date will return EXPIRED_CARD, else return OK.
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t  termData) {
	//2 digits of the year
	//MM/YY
	uint8_t expirationDateYears1 = cardData.cardExpirationDate[3] - '0';
	uint8_t expirationDateYears2 = cardData.cardExpirationDate[4] - '0';
	uint8_t expyear = 10 * expirationDateYears1 + expirationDateYears2;
	printf("the expiration year is :%d\n", expyear);
	fflush(stdin); fflush(stdout);
	//2 digits of the month
	//MM/Yy
	uint8_t expirationDateMonth1 = cardData.cardExpirationDate[0] - '0';
	uint8_t expirationDateMonth2 = cardData.cardExpirationDate[1] - '0';
	uint8_t expmonth = 10 * expirationDateMonth1 + expirationDateMonth2;
	printf("the expiration month is :%d\n", expmonth);
	fflush(stdin); fflush(stdout);


	// terminal date example: DD/MM/YYYY
	// last 2 digits indicates to years that will be compared
	uint8_t transDateYears1 = termData.transactionDate[8] - '0';
	uint8_t transDateYears2 = termData.transactionDate[9] - '0';
	uint8_t transyear = 10 * transDateYears1 + transDateYears2;
	printf("the transaction year is :%d\n", transyear);
	fflush(stdin); fflush(stdout);

	// Months digits that will be compared
	uint8_t transDateMonth1 = termData.transactionDate[3] - '0';
	uint8_t transDateMonth2 = termData.transactionDate[4] - '0';
	uint8_t transmonth = 10 * transDateMonth1 + transDateMonth2;
	printf("the transaction month is :%d\n", transmonth);
	fflush(stdin); fflush(stdout);

	// comparing
	if (expyear < transyear) return EXPIRED_CARD;
	else if (transyear < expyear) return TERMINAL_OK;
	else if (expmonth < transmonth) return EXPIRED_CARD;
	else if (transmonth < expmonth)return TERMINAL_OK;
	else return TERMINAL_OK;
}


//This function asks for the transaction amount and saves it into terminal data.
//If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return OK.
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Please enter the transacion amount:\n");
	fflush(stdin); fflush(stdout);
	scanf_s("%f", &termData->transAmount);
	if (termData->transAmount <= 0)
		return INVALID_AMOUNT;
	return TERMINAL_OK;
}

//This function compares the transaction amount with the terminal max amount.
//If the transaction amount is larger than the terminal max amount will return EXCEED_MAX_AMOUNT, else return OK.
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	return TERMINAL_OK;
}


//This function sets the maximum allowed amount into terminal data.
//Transaction max amount is a float number.
//If transaction max amount less than or equal to 0 will return INVALID_MAX_AMOUNT error, else return OK.
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	printf("Please set the max amount:\n");
	fflush(stdin); fflush(stdout);
	scanf_s("%f", &termData->maxTransAmount);
	if (termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	return TERMINAL_OK;
}
