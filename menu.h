#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


char *main_title = "\n  -----------------------------------------------------"
                    "\n                  SUNSHINE SUPERMARKET"
                    "\n  -----------------------------------------------------\n";


char *main_menu ="\n     1. Register New Product\n"
                 "\n     2. Display Products\n"
                 "\n     3. Sell Product\n"
                 "\n     4. Display Sales\n"
                 "\n     5. Exit\n"
                 "\n\n  > ";


char *position_menu = "\n  ------------------------------"
                      "\n       Choose a Position "
                      "\n  ------------------------------"
                      "\n      1. End "
                      "\n      2. Middle"
                      "\n      3. Beginning "
                      "\n      4. Back To Main Menu "
                      "\n\n  ------------------------------\n"
                      "\n  > ";
int End = 1, Middle = 2, Beginning = 3;//Descriptive positional menu options code

char *search_menu =   "\n  --------------------------------------"
                      "\n      Choose an option to Search BY "
                      "\n  --------------------------------------"
                      "\n      1. Product ID "
                      "\n      2. Product category "
                      "\n      3. Product Name "
                      "\n\n  --------------------------------------\n"
                      "\n  > ";

char *product_sort_menu =     "\n  --------------------------------------"
                      "\n      Choose an option to Sort BY "
                      "\n  --------------------------------------"
                      "\n      1. Product ID "
                      "\n      2. Category "
                      "\n      3. Product Name "
                      "\n      4. Selling Price "
                      "\n      5. Expire Date "
                      "\n\n  --------------------------------------\n"
                      "\n  > ";

 char *exit_message = "\n\t  --------------------------------------"
                      "\n\t             Good Bye :) "
                      "\n\t  --------------------------------------\n";
#endif
