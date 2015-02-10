/**********************************************************************
cs1713p1.h
Purpose:
    Defines typedefs for
        Customer - includes email address, full name, and postal address
        PurchaseItem - items the customer wants to purchase
    Defines constants for
        boolean values
        error messages
        program return codes
    Prototypes
Notes:
    
**********************************************************************/

/**** typedefs ****/

// Customer information 
typedef struct
{
    char        szEmailAddr[51];            // customer's email address is used
                                            // to uniquely define a customer
    char        szFullName[31];             // customer full name
    char        szStreetAddress[31];        // street number, street name, and 
                                            // (optional) apartment number
    char        szCity[21];                 // address city
    char        szStateCd[3];               // address state code
    char        szZipCd[6];                 // address zip code
} Customer;

// Purchase Item 
typedef struct
{
    char szStockNumber[7];                  // stock number of the item requestes
    int iRequestQty;                       // quantity requested

} PurchaseItem;

/**** constants ****/

// boolean
#define FALSE           0
#define TRUE            1

/*  Error Messages */
#define ERR_MISSING_SWITCH          "missing switch"
#define ERR_EXPECTED_SWITCH         "expected switch, found"
#define ERR_MISSING_ARGUMENT        "missing argument for"
#define ERR_CUSTOMER_ORDER_FILENAME "invalid customer order file name"
#define ERR_CUSTOMER_ID_DATA        "invalid customer id data"
#define ERR_CUSTOMER_ADDRESS_DATA   "invalid customer address data"
#define ERR_PURCHASE_ITEM_DATA      "invalid purchase item data"

/* program return codes */
#define ERR_COMMAND_LINE_SYNTAX     -1      // invalid command line syntax
#define USAGE_ONLY                  -2      // show usage only
#define ERROR_PROCESSING            -3
#define WARNING_INVALID_ORDER_DATA  1       // some invalid order request records were 
                                            // encountered, but we continued processing

/* prototypes */
void exitError(char *pszMessage, char *pszDiagnosticInfo);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);
