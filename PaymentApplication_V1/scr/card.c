/*
 * card.c
 *
 *  Created on: Jun 3, 2024
 *      Author: Fady Emad
 */
/***************************includes**********************/
#include "card.h"
#include <stdio.h>
#include <string.h>
/*********************************************************/



/*This function will ask for the cardholder name and store it into card data
 *card holder name is 24 alphabetic characters string max and 20 min
 *if the card holder name is null, less than 20 characters or more than 24 will return Wrong_name error, else return card_ok
 */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Please enter your card holder name:\n");
	fflush(stdin); fflush(stdout);
	gets(cardData->cardHolderName);

	if (strlen(cardData->cardHolderName) > 24 || strlen(cardData->cardHolderName) < 20 || cardData->cardHolderName == NULL)
		return WRONG_NAME;
	return CARD_OK;

}



/*This function will ask for the card expiry date and store it in card data
 *card expiry date is 5 characters string in the format "MM/YY", e.g "05/25"
 *If the card expiry date is null, less or more than 5 characters, or has the wrong format will return WRONG_EXP_date error, else return CARD_OK
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Please enter your card expiry date:MM/YY\n");
	fflush(stdin); fflush(stdout);
	gets(cardData->cardExpirationDate);
	//after modification
	//getting month as a whole number
	uint8_t monthFirstDigit = cardData->cardExpirationDate[0] - '0';
	uint8_t monthSecondDigit = cardData->cardExpirationDate[1] - '0';
	uint8_t monthNumber = monthFirstDigit * 10 + monthSecondDigit;

	//checking if the month number is between 1 and 12 inclusive
	//what we want is (monthNumber >= 1 && monthNumber <= 12)

	if (strlen(cardData->cardExpirationDate) > 5 ||cardData->cardExpirationDate[2]!='/' || cardData->cardExpirationDate == NULL
			||!(monthNumber >= 1 && monthNumber <= 12))
		return WRONG_EXP_DATE;
	return CARD_OK;

}



/* This function will ask for the card's Primary Account Number and store in card data
 * Pan is 20 numeric characters string, 19 character max, and 16 character min.
 * If the PAN is NULL, less than 16 or more than 19 characters , will return WRONG_PAN error, else return CARD_OK
 */
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Please enter your Primary Account Number\n");
	fflush(stdin); fflush(stdout);
	gets(cardData->primaryAccountNumber);
	if (strlen(cardData->primaryAccountNumber) > 19 || strlen(cardData->primaryAccountNumber) < 16 || cardData->primaryAccountNumber == NULL)
		return WRONG_PAN;
	return CARD_OK;
}
