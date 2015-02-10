/**********************************************************************
cs1713p1.c
Purpose:
    This program reads customer orders to produce output suitable for 
    warehouse personnel to pull the stock and mail it to the customer.  
Command Parameters:
    order -c customerOrderFileName  
Input:
    Order       Stream input file which contains orders for products.   
                There are three different kinds of lines of data for each order:
                Customer Identification Information:
                o One line per order
                o szEmailAddr    szFullName
                  50s            30s (may contain spaces)
                Customer Address Information (separated by commas)
                o One line per order
                o szStreetAddress            szCity   szStateCd   szZipCd
                  30s (may contain spaces)   20s      2s          5s
                Purchase Item:
                o 0 to many of them per order (terminated by 000000 
                  in the Stock Number and 0 in the Request Quantity)
                o szStockNumber   iRequestQty
                  6s              4d
Results:
    Prints each order in a readable format which is suitable for warehouse
    personnel to use to pull the stock.
    Examples:
        ******************* Order **********************
        petem@xyz.net Pete Moss
        123 Boggy Lane
        New Orleans, LA 70112
           Stock    Quantity      
           SBB001         10      
           SBG002         50      
           MCW001          2      
           SBG002         10      
        ******************* Order **********************
        pcorn@abc.net Pop Corn
        456 Kernel
        San Antonio, TX 78210
           Stock    Quantity      
           BOM001          2      
           NHC001         50       
           SBG002        100      
           MCW001         50      
           XXX001         20 
           SBG002        100      
Returns:
    0  normal
    -1 invalid command line syntax
    -2 show usage only
    -3 error during processing, see stderr for more information
Notes:
    order -?  will provide the usage information.  In some shells,
                   you will have to type order -\?
  
**********************************************************************/
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cs1713p1.h"
FILE *pfileOrder;                   // stream Input for Customer Order data

void processCommandSwitches(int argc, char *argv[], char **ppszOrderFileName);
int processOrders();

int main(int argc, char *argv[])
{
    char            *pszOrderFileName = NULL;
    int             rc;
 
    // Process the command switches
    processCommandSwitches(argc, argv,  &pszOrderFileName);
    
    // open the Customer Order stream data file
    if (pszOrderFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-c");
    
    pfileOrder = fopen(pszOrderFileName, "r");
    if (pfileOrder == NULL)
        exitError(ERR_CUSTOMER_ORDER_FILENAME, pszOrderFileName);
   
    // process the orders
    rc = processOrders();

    printf("\n");    // included so that you can put a breakpoint on this line
    return rc;
}

/****** you need to document and code this function *****/

int processOrders()
{
    char szInputBuffer[100];
    Customer customer;
    PurchaseItem item;

    //Read in the lines
    while (fgets(szInputBuffer, 100, pfileOrder) != NULL)
    {
        printf("************** Order ********************\n");
        //Grab name/email
        sscanf(szInputBuffer, "%s %[^\n]\n"
                , customer.szEmailAddr
                , customer.szFullName);
        printf("%-15s %15s\n"
                , customer.szEmailAddr
                , customer.szFullName);

        //Grab address
        fgets(szInputBuffer, 100, pfileOrder);
        sscanf(szInputBuffer, "%[^,],%[^,],%[^,],%s\n"
                , customer.szStreetAddress
                , customer.szCity
                , customer.szStateCd
                , customer.szZipCd);
        printf("%s\n%s, %s %s\n"
                , customer.szStreetAddress
                , customer.szCity
                , customer.szStateCd
                , customer.szZipCd);

        //Print Orders
        printf("%10s %20s\n"
                , "Stock"
                , "Quantity");
        while (fgets(szInputBuffer, 100, pfileOrder) != NULL)
        {
            sscanf(szInputBuffer, "%s %d"
                    , item.szStockNumber
                    , &item.iRequestQty);

            //check for errors
            //if qty is not a number, return error
            if(isdigit(item.iRequestQty) > 0)
            //if(isdigit(10) > 0)
            {
                exitError(ERR_PURCHASE_ITEM_DATA, szInputBuffer);
            }

            //if end of items reached, stop looping through items
            if(strncmp(item.szStockNumber, "000000", 6) == 0) break;
            printf("%10s %20d\n"
                    , item.szStockNumber
                    , item.iRequestQty);
        }
    }
}


/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszOrderFileName)
Purpose:
    Checks the syntax of command line arguments and returns the filenames.
    If any switches are unknown, it exits with an error.
Parameters:
    I   int argc                        count of command line arguments
    I   char *argv[]                    array of command line arguments
    O   char **ppszOrderFileName        order file name
Notes:
    If a -? switch is passed, the usage is printed and the program exits
    with USAGE_ONLY.
    If a syntax error is encountered (e.g., unknown switch), the program
    prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszOrderFileName)
{
    int i;
    int rc = 0; 
    int bShowCommandHelp = FALSE;
    
    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
            case 'c':                   // Customer Order File Name
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszOrderFileName = argv[i];
                break;
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        }
    }
}

/******************** exitError *****************************
    void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    Prints an error message and diagnostic to stderr.  Exits with
    ERROR_PROCESSING.
Parameters:
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
    fprintf(stderr, "Error: %s %s\n"
        , pszMessage
        , pszDiagnosticInfo);
    exit(ERROR_PROCESSING);
}
/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    If this is an argument error (iArg >= 0), it prints a formatted message
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits
    with ERR_COMMAND_LINE_SYNTAX.

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    if (iArg >= 0)
        fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
            , iArg
            , pszMessage
            , pszDiagnosticInfo);
    fprintf(stderr, "order -c customerOrderFile\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
