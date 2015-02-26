/**********************************************************************
cs1713p2.h
Purpose:
    Defines constants for
        maximum sizes
        boolean values
        error and warning messages
        program return codes
    Defines typedefs for
        Customer - includes email address, full name, and postal address
        PurchaseItem - items the customer wants to purchase
        Stock - one stock item
    Prototypes
Notes:
    
**********************************************************************/
/**** constants ****/

/* maximum constants */
#define MAX_STOCK 20		   // maximum size of the inventory array (stockM)

/* boolean constants */
#define FALSE           0
#define TRUE            1

/****  Error Messages ****/

/* Error messages for command line arguments */
#define ERR_MISSING_SWITCH          "missing switch"
#define ERR_EXPECTED_SWITCH         "expected switch, found"
#define ERR_MISSING_ARGUMENT        "missing argument for"

/* Error message for inventory data processing */

#define ERR_INVENTORY_FILENAME      "invalid inventory file name, "
#define ERR_TOO_MANY_STOCK_ITEMS    "more stock items in inventory than our array allows"
#define ERR_INVALID_INVENTORY_DATA  "invalid inventory file data"

/* Error messages for customer data processing */
#define ERR_CUSTOMER_ORDER_FILENAME "invalid customer order file name"
#define ERR_CUSTOMER_ID_DATA        "invalid customer id data"
#define ERR_CUSTOMER_ADDRESS_DATA   "invalid customer address data"
#define ERR_PURCHASE_ITEM_DATA      "invalid purchase item data"
#define WARN_STOCK_NR_NOT_FOUND     "stock number not found "
#define WARN_NOT_ENOUGH_IN_STOCK    "not enough inventory in stock"

/* program return codes */
#define ERR_COMMAND_LINE_SYNTAX     -1      // invalid command line syntax
#define USAGE_ONLY                  -2      // show usage only
#define ERROR_PROCESSING            -3
#define WARNING_INVALID_ORDER_DATA  1       // some invalid order request records were 
                                            // encountered, but we continued processing

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
    int iRequestQty;                        // quantity requested

} PurchaseItem;

/* Stock is used for one stock item 
*/
typedef struct
{
    char        szStockNumber[7];           // Stock Number for a stock item
    long        lStockQty;                  // quantity in stock
    double      dUnitPrice;                 // price per unit of stock
    char        szStockName[31];            // name of the stock item
} Stock;

/* prototypes */
void exitError(char *pszMessage, char *pszDiagnosticInfo);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);