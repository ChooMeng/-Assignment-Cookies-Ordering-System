#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#pragma warning (disable:4996)

/*
=======================
   Constant Variable
=======================
*/
#define P_LOVELETTERS 25.00
#define P_NUTCOOKIES 20.00
#define P_ASSORTEDCOOKIES 15.00
const char PHONE[12] = "012-3456789";

/*
======================
 Function Declaration
======================
*/
void startscreen();
void getdate();
void menu();
void order();
void orderstart();
void orderplace();
void ordercancel();
void displaycanceled();
void summary();
void luckydraw(int userbalance);
void rollluckydraw();
int membercard();
void voucher(double ctotal);

/*
======================
 Variable Declaration
======================
*/
char date[41];
char cardid[8];
int ordernumber = 0;
int numLoveLetters = 0;
int numNutCookies = 0;
int numAssortedCookies = 0;
int luckydrawchance = 0;
int totalluckydraw = 0;
double totalLoveLetters = 0;
double totalNutCookies = 0;
double totalAssortedCookies = 0;
double total = 0;
double subtotal = 0;
double deposit = 0;
double balance = 0;
double discountprice = 0;

void main() {
	// Display start screen title
	startscreen();
	// Get date
	getdate();
	// Start order system
	orderstart();
	system("pause");
}

// Display start screen
void startscreen() {
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("\tTARUC FESTIVE COOKIES Sdn Bhd\n");
	printf("\t > Cookies Ordering System <\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

// Enter date
void getdate() {
	printf("Enter Today's Date > ");
	gets(date);
}

//Display the list of prices for different cookies and discounts available
void menu() {
	printf("\n");
	printf("==================[MENU]==================\n");
	printf("\t\t|\t |     Price     |\n");
	printf("    Category\t|  Unit\t |  (per  unit)  |\n");
	printf("----------------|--------|---------------|\n");
	printf("  Love Letters\t|        |               |\n");
	printf("  (Kuih Kapit)\t|  tin   |%15.2f|\n", P_LOVELETTERS);
	printf("----------------|--------|---------------|\n");
	printf("  Nut Cookies \t|  jar   |%15.2f|\n", P_NUTCOOKIES);
	printf("----------------|--------|---------------|\n");
	printf("Assorted Cookies|  jar   |%15.2f|\n", P_ASSORTEDCOOKIES);
	printf("==================[MENU]==================\n");
	printf("..............................................\n");
	printf("Discounts:\n");
	printf("* 5%% - Order totaling between RM500 - RM1000\n");
	printf("* 10%% - Order totaling more than RM1000\n");
	printf("LuckyDraw:\n");
	printf("* Every RM400 get 1 luckydraw chance.\n");
	printf("MemberCard:\n");
	printf("* 2%% discount\n");
	printf("Gift Voucher:\n");
	printf("* RM10 Offer - Order totaling between RM600 - RM1200\n");
	printf("* RM20 Offer - Order totaling more than RM1200\n");
	printf("..............................................\n");
}

//Ordering Service	
void order() {
	char nextorder;
	do {
		menu();
		orderplace();
		// Ask user want to next order or not
		printf("Next Order (Y=yes)/(N=no) > ");
		rewind(stdin);
		nextorder = getchar();
		while (!(tolower(nextorder) == 'y' || tolower(nextorder) == 'n')) {
			printf("Invalid! Type (Y=yes)/(N=no)\n");
			printf("Next Order (Y=yes)/(N=no) > ");
			rewind(stdin);
			nextorder = getchar();
		}
	} while (tolower(nextorder) == 'y');
}

// Ask to start order service or not
void orderstart() {
	char startorder;
	rewind(stdin);
	printf("Start Order (Y=yes/N=no) ? > ");
	startorder = getchar();
	while (!(tolower(startorder) == 'y' || tolower(startorder) == 'n')) {
		printf("Invalid, Use Y for yes to start order\n");
		rewind(stdin);
		printf("Start Order (Y=yes/N=no) ? > ");
		startorder = getchar();
	}
	switch (tolower(startorder)) {
	case 'y':
		order();
		summary();
		break;
	case 'n':
		printf("\t\t************************\n");
		printf("\t\t> ORDER SYSTEM STOPPED <\n");
		printf("\t\t************************\n");
		return;
		break;
	}
}

//Create New Order
void orderplace() {
	int cnumLoveLetters;
	int cnumNutCookies;
	int cnumAssortedCookies;
	int cdiscount;
	int havecard;
	double ctotalLoveLetters;
	double ctotalNutCookies;
	double ctotalAssortedCookies;
	double csubtotal = 0;
	double ctotal = 0;
	double cdeposit = 0;
	double cbalance = 0;
	double cdiscountprice;
	char oconfirm;
	// Ask customer have membercard or not
	havecard = membercard();
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\t\t\t\t\t       Order No: %3.d\n", ++ordernumber);
	printf("\t\t\t\t\t       *************\n");
	printf("-------------------------------------------\t-----------\n");
	printf("   \t\t   ITEM\t\t\t\t   PRICE\n");
	printf("-------------------------------------------\t-----------\n");
	// LOVE LETTERS
	printf(">>>> LOVE LETTERS \t@ RM %.2f/tin \t :\n", P_LOVELETTERS);
	printf("\t\t\t\tQuantity : ");
	scanf("%d", &cnumLoveLetters);
	ctotalLoveLetters = cnumLoveLetters * P_LOVELETTERS;
	csubtotal += ctotalLoveLetters;
	printf("\t\t\tLOVELETTERS Total: \tRM%8.2f\n", ctotalLoveLetters);
	printf("\t\tOrder SubTotal: RM%8.2f\n\n", csubtotal);
	// NUT COOKIES
	printf(">>>> NUT COOKIES \t@ RM %.2f/jar \t :\n", P_NUTCOOKIES);
	printf("\t\t\t\tQuantity : ");
	scanf("%d", &cnumNutCookies);
	ctotalNutCookies = cnumNutCookies * P_NUTCOOKIES;
	csubtotal += ctotalNutCookies;
	printf("\t\t\tNUT COOKIES Total: \tRM%8.2f\n", ctotalNutCookies);
	printf("\t\tOrder SubTotal: RM%8.2f\n\n", csubtotal);
	// ASSORTED COOKIES
	printf(">>>> ASSORTED COOKIES \t@ RM %.2f/jar \t :\n", P_ASSORTEDCOOKIES);
	printf("\t\t\t\tQuantity : ");
	scanf("%d", &cnumAssortedCookies);
	ctotalAssortedCookies = cnumAssortedCookies * P_ASSORTEDCOOKIES;
	printf("\t\t   Assorted COOKIES Total: \tRM%8.2f\n", ctotalAssortedCookies);
	// Calculate SubTotal
	csubtotal += ctotalAssortedCookies;
	printf("\t\t\t\t\t\t-----------\n");
	printf("\t\t\t\tSUBTOTAL : \tRM%8.2f\n", csubtotal);
	printf("\t\t\t\t\t\t-----------\n");
	// Order Confirmation
	rewind(stdin);
	printf("Confirm/ Cancel Order (Y=confirm)/(N=cancel) ? > ");
	oconfirm = getchar();
	switch (tolower(oconfirm)) {
	case 'y':
		break;
	case 'n':
		ordercancel();
		return;
		break;
	default:
		do {
			printf("Invalid. \'Y\' for confirm / \'N\' for cancel\n");
			rewind(stdin);
			printf("Confirm/ Cancel Order (Y=confirm)/(N=cancel) ? > ");
			oconfirm = getchar();
		} while (!(tolower(oconfirm) == 'y' || tolower(oconfirm) == 'n'));
		if (oconfirm == 'n')
			ordercancel();
		return;
		break;
	}
	// Discount Section
	if (csubtotal >= 500)
		if (csubtotal <= 1000)
			cdiscount = 5;
		else
			cdiscount = 10;
	else
		cdiscount = 0;
	if (havecard > 0) {
		cdiscount += 2;
	}
	cdiscountprice = (cdiscount / 100.00) * csubtotal;
	printf("\t\t\t   Discount(%2d%%) : \tRM%8.2f\n", cdiscount, cdiscountprice);
	// Payment Section
	ctotal = csubtotal - cdiscountprice;
	printf("\t\t\t\t   Total : \tRM%8.2f\n", ctotal);
	printf("\t\t\t\t Deposit : \tRM  ");
	scanf("%lf", &cdeposit);
	cbalance = ctotal - cdeposit;
	printf("\t\t\t\t Balance : \tRM%8.2f\n", cbalance);
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\n\n");
	// Order Note
	printf("*******************************************************************|\n");
	printf("\t\t   TARUC FESTIVE COOKIES Sdn Bhd   \t\t   |\n");
	printf("\t\t          > ORDER NOTE <       \t Phone: %s|\n", PHONE);
	printf("*******************************************************************|\n");
	printf("Order No: %.3d\t\t\t\t    Date: %17s|\n", ordernumber, date);
	// Display Customer ID
	if (havecard > 0) {
		printf("Customer ID: C%s\t\t\t\t\t\t   |\n", cardid);
	}
	printf("\t\t\t[ Ready in 4days ]\t\t\t   |\n");
	printf("-------------------------------------------------------------------|\n");
	printf("     | QTY |\t\t       ITEMS\t\t       |   PRICE   |\n");
	printf("-----|-----|-------------------------------------------|-----------|\n");
	printf(">>>  | %3d |  LOVE LETTERS \t\t@ RM %.2f/tin | RM%8.2f|\n", cnumLoveLetters, P_LOVELETTERS, ctotalLoveLetters);
	printf(">>>  | %3d |  NUT COOKIES \t\t@ RM %.2f/jar | RM%8.2f|\n", cnumNutCookies, P_NUTCOOKIES, ctotalNutCookies);
	printf(">>>  | %3d |  ASSORTED COOKIES  \t@ RM %.2f/jar | RM%8.2f|\n", cnumAssortedCookies, P_ASSORTEDCOOKIES, ctotalAssortedCookies);
	printf("-------------------------------------------------------------------|\n");
	printf("\t\t\t\t\tSUBTOTAL       : RM%8.2f|\n", csubtotal);
	printf("\t\t\t\t\tDISCOUNT (%2d%%) : RM%8.2f|\n", cdiscount, cdiscountprice);
	printf("\t\t\t\t\tTOTAL          : RM%8.2f|\n", ctotal);
	printf("\t\t\t\t\tDEPOSIT        : RM%8.2f|\n", cdeposit);
	printf("\t\t\t\t\tBALANCE        : RM%8.2f|\n", cbalance);
	printf("*******************************************************************|\n");
	printf("Thank you for ordering.\t\t\t\t\t\t   |\n");
	printf("Hope you come next time.\t\t\t\t\t   |\n");
	printf("Take this order note to claim your order.\t\t\t   |\n");
	printf("*******************************************************************|\n");
	luckydraw((int)cbalance); // Check how many luckydraw chance can customer get
	printf("*******************************************************************|\n");
	rollluckydraw();
	voucher(ctotal);
	// Summary Addtraction
	totalAssortedCookies += ctotalAssortedCookies;
	totalLoveLetters += ctotalLoveLetters;
	totalNutCookies += ctotalNutCookies;
	total += ctotal;
	numAssortedCookies += cnumAssortedCookies;
	numLoveLetters += cnumLoveLetters;
	numNutCookies += cnumNutCookies;
	discountprice += cdiscountprice;
	balance += cbalance;
	deposit += cdeposit;
	subtotal += csubtotal;
}

// Perform Order cancel action
void ordercancel() {
	displaycanceled();
	printf("\t   > Your order has now been canceled. <\n");
	ordernumber--; // Reduce order number 
}

// Display 'Canceled' word
void displaycanceled() {
	printf("=============================================================\n");
	printf(" #####\t  ### \t#    #\t #####\t#####\t#    \t#####\t#### \n");
	printf("#     \t#    #\t##   #\t#     \t#    \t#    \t#    \t#   #\n");
	printf("#     \t######\t# #  #\t#     \t#####\t#    \t#####\t#   #\n");
	printf("#     \t#    #\t#  # #\t#     \t#    \t#    \t#    \t#   #\n");
	printf(" #####\t#    #\t#   ##\t #####\t#####\t#####\t#####\t#### \n");
	printf("=============================================================\n");
}

// Display Order Summary 
void summary() {
	printf("*****************************************************************\n");
	printf("|        @@@@  @    @  @    @  @    @    @    @@@@   @   @      |\n");
	printf("|       @      @    @  @@  @@  @@  @@   @ @   @   @  @   @      |\n");
	printf("|        @@@@  @    @  @ @@ @  @ @@ @  @   @  @@@@    @@@       |\n");
	printf("|           @  @    @  @    @  @    @  @@@@@  @ @      @        |\n");
	printf("|       @@@@    @@@@   @    @  @    @  @   @  @  @     @        |\n");
	printf("*****************************************************************\n");
	printf("\t\tORDER SUMMARY [%17s]\n", date);
	printf("\t\t================================\n");
	printf("Total Number of Customer Orders : %d\n", ordernumber);
	printf("=================================================================\n");
	printf("   TOTAL   |       ORDERS  \t|    UNIT PRICE    |   AMOUNT   |\n");
	printf("-----------|--------------------|------------------|------------|\n");
	printf("    %3d    |  LOVE LETTERS\t|   RM %.2f/tin   | RM%8.2f |\n", numLoveLetters, P_LOVELETTERS, totalLoveLetters);
	printf("    %3d    |  NUT COOKIES\t|   RM %.2f/jar   | RM%8.2f |\n", numNutCookies, P_NUTCOOKIES, totalNutCookies);
	printf("    %3d    |  ASSORTED COOKIES\t|   RM %.2f/jar   | RM%8.2f |\n", numAssortedCookies, P_ASSORTEDCOOKIES, totalAssortedCookies);
	printf("=================================================================\n");
	printf("\t\t\t\t    |SUBTOTAL      | RM%8.2f |\n", subtotal);
	printf("\t\t\t\t    |DISCOUNT      | RM%8.2f |\n", discountprice);
	printf("\t\t\t\t    |TOTAL         | RM%8.2f |\n", total);
	printf("\t\t\t\t    |DEPOSIT       | RM%8.2f |\n", deposit);
	printf("\t\t\t\t    |BALANCE       | RM%8.2f |\n", balance);
	printf("=================================================================\n");
	printf("Total Lucky Draw chance given to customer: %d\n", totalluckydraw);
	printf("=================================================================\n");
}

// Calculate luckydraw chance
void luckydraw(int userbalance) {
	luckydrawchance = userbalance / 400;
	printf("\t      !  You get %d time luckydraw chance.  !\t\t   |\n", luckydrawchance);
	totalluckydraw += luckydrawchance;
}

// Random pick number for luckydraw
void rollluckydraw() {
	char ynluckydraw;
	if (luckydrawchance > 0) {
		rewind(stdin);
		// Ask user want to lucky draw or not
		printf("Do you want to luckydraw? (y=yes/n=no) > ");
		ynluckydraw = tolower(getchar());
		switch (ynluckydraw) {
		case 'y':
			// Display luckydraw number win
			printf("Luckydraw number you win = ");
			srand((int)time(NULL));
			for (luckydrawchance; luckydrawchance > 0; luckydrawchance--) {
				if (luckydrawchance == 1) {
					printf("%d \n", rand() % 10 + 1);
				}
				else {
					printf("%d, ", rand() % 10 + 1);
				}
			}
			break;
		case 'n':
			break;
		default:
			printf("Invalid, use (y=yes/n=no)\n");
			rollluckydraw();
		}
	}
}

// MemberCard Section
int membercard() {
	char yesorno;
	int havecard = 0;
	rewind(stdin);
	// Ask user have member card or not
	printf("Have Member Card? (y=yes)/(n=no) > ");
	yesorno = getchar();
	while (!(tolower(yesorno) == 'y' || tolower(yesorno) == 'n')) {
		printf("Invalid! Use (y=yes)/(n=no)\n");
		rewind(stdin);
		printf("Have Member Card? (y=yes)/(n=no) > ");
		yesorno = getchar();
	}
	switch (tolower(yesorno)) {
	case 'y':
		rewind(stdin);
		// Ask user to key in member card ID
		printf("Enter MemberCard ID (EG:C*******)> C");
		gets(cardid);
		havecard = 1;
		break;
	case 'n':
		havecard = 0;
		break;
	}
	return havecard;
}

// Print voucher for customer
void voucher(double ctotal) {
	if (ctotal >= 600) {
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
		printf("\t\tTARUC FESTIVE COOKIES Sdn Bhd\n");
		printf("\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
		printf("\t\t\t[GIFT VOUCHER]\n");
		// Display RM10 Offer voucher if balance between 600 to 1200
		if (ctotal <= 1200) {
			printf("\t####  #   #  ##   ###      ####  ##### #####\n");
			printf("\t#   # ## ## # #  #   #    #    # #     #    \n");
			printf("\t####  # # #   #  #   #    #    # ##### #####\n");
			printf("\t##    #   #   #  #   #    #    # #     #    \n");
			printf("\t# #   #   # ####  ###      ####  #     #    \n");
		}
		// Display RM20 Offer voucher if balance more than 1200
		else {
			printf("\t####  #   # ####    ###      ####  ##### #####\n");
			printf("\t#   # ## ##     #  #   #    #    # #     #    \n");
			printf("\t####  # # #   #    #   #    #    # ##### #####\n");
			printf("\t##    #   #  #     #   #    #    # #     #    \n");
			printf("\t# #   #   # #####   ###      ####  #     #    \n");
		}
		printf("\t*Can use at any game store of TARUC Festive*\n");
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}
}