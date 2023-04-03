/********* >>>>>>Sunshine Supermarket MS<<<<< ************
****
****  TODO: Implement Binary Search tree Algorithm
****                     &
****          perform all the CRUD operations
****
****  Created By: Sisay Driba |  Created on: June 2022
************************************************************/


#include <iostream>
#import <fstream>
#import <string>
#include <conio.h>
#include <iomanip>
#include "./helpers.h"
#include "./menu.h"

using namespace std;


struct Product{
    string id;
    string category;
    string name;
    double purchasing_price;
    double selling_price;
    int quantity;
    string unit;
    string expire_date;
    Product *left;
    Product *right;
};

Product *root_product = NULL;
Product *parent_product = NULL;
Product *current_product = NULL;
Product *new_product = NULL;


struct Sales{
    string product_name;
    int quantity;
    string product_unit;
    double unit_price;
    double total_price;
    string date;
    Sales *left;
    Sales *right;
};

Sales *root_sales = NULL;
Sales *parent_sales = NULL;
Sales *current_sales = NULL;
Sales *new_sales = NULL;

int const id = 0, category = 1, name = 2, price = 3, expire_date = 4;//for sorting
int item_counter = 0;
bool sorted = false , filtered = false;
string sorting[] = {"Product ID", "Category", "Product Name", "Selling Price", "Expire Date"};
int sorted_by = category;


void load_products_from_file(int);
void invert_products_tree(Product*);
void display_operations();


void register_new_product(Product *new_product, int sort_by = name){
    if(root_product == NULL)
        root_product = new_product;
    else{
        current_product = root_product;
        while(true){
            parent_product = current_product;
            if(
               sort_by == id && new_product->id.compare(parent_product->id) < 0 ||
               sort_by == category && new_product->category.compare(parent_product->category) < 0 ||
               sort_by == name && new_product->name.compare(parent_product->name) < 0 ||
               sort_by == price && new_product->selling_price < parent_product->selling_price ||
               sort_by == expire_date && new_product->expire_date.compare(parent_product->expire_date) < 0){
                current_product = current_product->left;
                if(current_product == NULL){
                    parent_product->left = new_product;
                    return;
                }
            }
            else{
                current_product = current_product->right;
                if(current_product == NULL){
                    parent_product->right = new_product;
                    return;
                }
            }
        }
    }
}
void register_new_sales(Sales *new_sales){
    if(root_sales == NULL)
        root_sales = new_sales;
    else{
        current_sales = root_sales;
        while(true){
            parent_sales = current_sales;
            if(new_sales->date.compare(parent_sales->date) < 0){
                current_sales = current_sales->left;
                if(current_sales == NULL){
                    parent_sales->left = new_sales;
                    return;
                }
            }
            else{
                current_sales = current_sales->right;
                if(current_sales == NULL){
                    parent_sales->right = new_sales;
                    return;
                }
            }
        }
    }
}

struct Product *search_product(string value, Product *parent_product, int search_by){
    if(parent_product == root_product){
        system("cls");
        if(filtered)
            cout<<"\n                           ---------------------------------------------------------------------------------\n\t\t\t\t\t\t\t[ Filtered By "<<sorting[search_by]<<" ] ";
        cout<<"\n                           ---------------------------------------------------------------------------------\n";
        cout<<"\n                                        >>>>>>>>>>> Sunshine supermarket Products <<<<<<<<<  \n";
        cout<<"\n  ---------------------------------------------------------------------------------------------------------------------------------\n";
        cout<<left<<"    "<<setw(3)<<"No."<<setw(15)<<" | Product ID "<<setw(15)<<" | Category "<<setw(23)<<" | Product Name "<<setw(20)<<" | Purchasing Price"<<setw(17)<<" | Selling Price"<<setw(19)<<" | Available "<<setw(17)<<" | Expire Date";
        cout<<"\n  ---------------------------------------------------------------------------------------------------------------------------------\n";
    }
    if(root_product == NULL)
        cout<<"\t\t\t\t\t\t No product found!\n";
    if(parent_product != NULL){
        search_product(value, parent_product->left, search_by);
        if(
           search_by == id && parent_product->id == value ||
           search_by == category && parent_product->category == value ||
           search_by == name && parent_product->name == value
           ){
            cout<<left<<"    "<<setw(3)<<++item_counter<<" | "<<setw(12)<<parent_product->id<<" | "<<setw(12)<<parent_product->category<<" | "<<setw(20)<<parent_product->name<<" | "<<setw(17)<<parent_product->purchasing_price<<" | "<<setw(14)<<parent_product->selling_price<<" | "<<setw(4)<<parent_product->quantity<<setw(12)<<parent_product->unit<<" | "<<setw(15)<<parent_product->expire_date;
            cout<<"\n  ---------------------------------------------------------------------------------------------------------------------------------\n";
        }
        search_product(value, parent_product->right, search_by);
    }

}
struct Product *search_product_by_id(string product_id, Product *parent_product){
    current_product = root_product;
    while(current_product->id != product_id){
        if(current_product != NULL){
            if(current_product->id.compare(product_id) > 0)
                current_product = current_product->left;
            else
                current_product = current_product->right;

            if(current_product == NULL)
                break;
        }
    }
    if(current_product != NULL && current_product->id == product_id)
        return current_product;
    else
        return NULL;

}

void display_products(Product *parent_product){
    if(parent_product == root_product){
        system("cls");
        if(sorted)
            cout<<"\n                           ---------------------------------------------------------------------------------\n\t\t\t\t\t\t\t[ Sorted By "<<sorting[sorted_by]<<" ] ";
        cout<<"\n                           ---------------------------------------------------------------------------------\n";
        cout<<"\n                                        >>>>>>>>>>> Sunshine supermarket Products <<<<<<<<<  \n";
        cout<<"\n  ---------------------------------------------------------------------------------------------------------------------------------\n";
        cout<<left<<"    "<<setw(3)<<"No."<<setw(15)<<" | Product ID "<<setw(15)<<" | Category "<<setw(23)<<" | Product Name "<<setw(20)<<" | Purchasing Price"<<setw(17)<<" | Selling Price"<<setw(19)<<" | Available "<<setw(17)<<" | Expire Date";
        cout<<"\n  ---------------------------------------------------------------------------------------------------------------------------------\n";
    }
    if(root_product == NULL)
        cout<<"\t\t\t\t\t\t No product found!\n";
    else if(parent_product != NULL){
        display_products(parent_product->left);
        cout<<left<<"    "<<setw(3)<<++item_counter<<" | "<<setw(12)<<parent_product->id<<" | "<<setw(12)<<parent_product->category<<" | "<<setw(20)<<parent_product->name<<" | "<<setw(17)<<parent_product->purchasing_price<<" | "<<setw(14)<<parent_product->selling_price<<" | "<<setw(4)<<parent_product->quantity<<setw(12)<<parent_product->unit<<" | "<<setw(15)<<parent_product->expire_date;
        cout<<"\n  ---------------------------------------------------------------------------------------------------------------------------------\n";
        display_products(parent_product->right);
    }

}
void display_sales(Sales *parent_sales){
    if(parent_sales == root_sales){
        system("cls");
        cout<<"\n                   -------------------------------------------------------------------\n";
        cout<<"\n                          >>>>>>>>>>> Sunshine supermarket Sales <<<<<<<<<  \n";
        cout<<"\n  ----------------------------------------------------------------------------------------------\n";
        cout<<left<<"    "<<setw(3)<<"No."<<setw(23)<<" | Product Name "<<setw(20)<<" | Total Price"<<setw(19)<<" | Quantity "<<setw(17)<<" | Date";
        cout<<"\n  ----------------------------------------------------------------------------------------------\n";
    }
    if(root_sales == NULL)
        cout<<"\t\t\t\t No Sales found!\n";
    else if(parent_sales != NULL){
        display_sales(parent_sales->left);
        cout<<left<<"    "<<setw(3)<<++item_counter<<" | "<<setw(20)<<parent_sales->product_name<<" | "<<setw(17)<<(to_string(parent_sales->total_price).substr(0, to_string(parent_sales->total_price).find(".")+3)+" ETB")<<" | "<<setw(4)<<parent_sales->quantity<<setw(12)<<parent_sales->product_unit<<" | "<<setw(15)<<parent_sales->date;
        cout<<"\n  ----------------------------------------------------------------------------------------------\n";
        display_sales(parent_sales->right);
    }

}

void invert_products_tree(Product *current_product) {
	if (current_product == NULL)
		return;
	else{
		struct Product *temp;

		/* recursive calls */
		invert_products_tree(current_product->left);
		invert_products_tree(current_product->right);

		/* swap the pointers in this node */
		temp = current_product->left;
		current_product->left = current_product->right;
		current_product->right = temp;
	}
}

void update_products_file(Product *current_product){
  if (current_product != NULL) {
    update_products_file(current_product->left);
    string line = current_product->id+", "+current_product->category+", "+current_product->name+", "+to_string(current_product->purchasing_price).substr(0, to_string(current_product->purchasing_price).find(".")+3)+", "+to_string(current_product->selling_price).substr(0, to_string(current_product->selling_price).find(".")+3)+", "+to_string(current_product->quantity)+", "+current_product->unit+", "+current_product->expire_date;
    write_on_file(line, productsFile);
    update_products_file(current_product->right);
  }
}

struct Product *min_product(Product *parent_product) {
    current_product = parent_product;

  // Find the leftmost leaf
  while (current_product->left != NULL)
    current_product = current_product->left;

  return current_product;
}
struct Product *delete_product(Product *parent_product, string product_id){
    if(parent_product == NULL) return parent_product;

    if(product_id.compare(parent_product->id) < 0)
        parent_product->left =  delete_product(parent_product->left, product_id);
    else if(product_id.compare(parent_product->id) > 0)
        parent_product->right =  delete_product(parent_product->right, product_id);
    else{
        if(parent_product->left == NULL && parent_product->right == NULL)
            return NULL;
        else if(parent_product->left == NULL){
            current_product = parent_product->right;
            delete(parent_product);
            return current_product;
        }
        else if(parent_product->right == NULL){
            current_product = parent_product->left;
            delete(parent_product);
            return current_product;
        }

        current_product = min_product(parent_product->right);

        parent_product->id = current_product->id;

        parent_product->right = delete_product(parent_product->right, current_product->id);
    }
    return parent_product;

}

void product_registration_handler(){
    system("cls");
    cout<<"\n    >>>>>>>>>>> Add New Product <<<<<<<<<  \n\n";
    new_product = new Product();

    cout<<"\t Product Name: ";
    cin.ignore();
    getline(cin, new_product->name);
    cout<<"\n\t Product ID: ";
    cin>>new_product->id;
    cout<<"\n\t Category: ";
    cin>>new_product->category;
    cout<<"\n\t Purchasing Price: ";
    cin>>new_product->purchasing_price;
    cout<<"\n\t Selling Price: ";
    cin>>new_product->selling_price;
    cout<<"\n\t Quantity: ";
    cin>>new_product->quantity;
    cout<<"\n\t Unit: ";
    cin>>new_product->unit;
    cout<<"\n\t Expire Date (yyyy-mm-dd): ";
    cin>>new_product->expire_date;

    new_product->left = NULL;
    new_product->right = NULL;
    register_new_product(new_product);

    string product_details = new_product->id+", "+new_product->category+", "+new_product->name+", "+to_string(new_product->purchasing_price).substr(0, to_string(new_product->purchasing_price).find(".")+3)+", "+to_string(new_product->selling_price).substr(0, to_string(new_product->selling_price).find(".")+3)+", "+to_string(new_product->quantity)+", "+new_product->unit+", "+new_product->expire_date;
    write_on_file(product_details, productsFile);
    cout<<"\n  -----------------------------------------------------\n";
    cout<<"              Item registered Successfully! ";
    cout<<"\n  -----------------------------------------------------\n";

}
void delete_product_handler(){
    string product_id;
    cout<<"   Enter Product Id: ";
    cin>>product_id;
    current_product = search_product_by_id(product_id, root_product);
    if(current_product == NULL){
        cout<<"    Product not found!\n";
        return;
    }

    root_product = delete_product(root_product, product_id);

    ofstream emptyfy;
    emptyfy.open(productsFile);
    emptyfy.close();

    update_products_file(root_product);

    if(root_product != NULL){
        cout<<"\n  -----------------------------------------------------\n";
        cout<<"              Product Deleted Successfully! ";
        cout<<"\n  -----------------------------------------------------\n";
    }
}
void update_product_handler(){
    string product_id;
    cout<<"   Enter Product Id: ";
    cin>>product_id;
    current_product = search_product_by_id(product_id, root_product);
    if(current_product == NULL){
        cout<<"    Product not found!\n";
        return;
    }

    cout<<"\t New Product Name: ";
    cin.ignore();
    getline(cin, current_product->name);
    cout<<"\n\t New Product ID: ";
    cin>>current_product->id;
    cout<<"\n\t New Category: ";
    cin>>current_product->category;
    cout<<"\n\t New Purchasing Price: ";
    cin>>current_product->purchasing_price;
    cout<<"\n\t New Selling Price: ";
    cin>>current_product->selling_price;
    cout<<"\n\t New Quantity: ";
    cin>>current_product->quantity;
    cout<<"\n\t New Unit: ";
    cin>>current_product->unit;
    cout<<"\n\t New Expire Date (yyyy-mm-dd): ";
    cin>>current_product->expire_date;


    ofstream emptyfy;
    emptyfy.open(productsFile);
    emptyfy.close();

    update_products_file(root_product);
    cout<<"\n  -----------------------------------------------------\n";
    cout<<"              Product Updated Successfully! ";
    cout<<"\n  -----------------------------------------------------\n";

}
void search_products_handler(){
    int search_by;
    string value;
    cout<<search_menu;
    cin>>search_by;
    switch(search_by){
        case 1:
            cout<<"   Enter Product Id: ";
            break;
        case 2:
            cout<<"   Enter Product Category: ";
            break;
        case 3:
            cout<<"   Enter Product Name: ";
            break;
        default:
            cout<<"    Invalid Input!";
            break;
            return;

    }
    cin>>value;
    filtered = true;
    search_product(value, root_product, search_by-1);
    if(item_counter == 0)
        cout<<"\t\t\t\t\t\t No product found!\n";

}
void sort_products_handler(){
    int sort_by;
    char wanna_desc;
    cout<<product_sort_menu;
    cin>>sort_by;
    root_product = NULL;
    load_products_from_file(sort_by-1);
    sorted = true;
    sorted_by = sort_by-1;
    display_products(root_product);
    cout<<" Sort In DESC (y, n): ";
    cin>>wanna_desc;
    item_counter = 0;
    if(wanna_desc == 'y'){
        invert_products_tree(root_product);
        display_products(root_product);
        display_operations();
    }
}

void display_operations(){
    int op;
    item_counter = 0;
    cout<<"\n     1. Sort    2. Search    3. Update   4. Delete   5. Go Back    6. Exit";
    cout<<"\n  -----------------------------------------------------------------------------\n";
    cout<<"   Choose Operation: ";
    cin>>op;
    switch(op){
        case 1:
            sort_products_handler();
            break;
        case 2:
            search_products_handler();
            break;
        case 3:
            update_product_handler();
            break;
        case 4:
            delete_product_handler();
            break;
        case 5:
            return;
            break;
        case 6:
            exit(0);

    }
}

void load_products_from_file(int sort_by = 0){
    string product_details[8];
    string data = "";
    int count_data;

    ifstream csvfile;
    csvfile.open(productsFile);
    string line;

    if(csvfile.is_open()){
        while(getline(csvfile, line)){
            new_product = new Product();
            line +=" ";
            count_data = 0;
            for(int i=0; i<line.length(); i++){
                if(line[i] == ',' || i+1==line.length()){
                    product_details[count_data] = data;
                    count_data++;
                    ++i;
                    data = "";
                }
                else data += line[i];
            }
            new_product->id = product_details[0];
            new_product->category = product_details[1];
            new_product->name = product_details[2];
            new_product->purchasing_price = stod(product_details[3]);
            new_product->selling_price = stod(product_details[4]);
            new_product->quantity = stoi(product_details[5]);
            new_product->unit = product_details[6];
            new_product->expire_date = product_details[7];

            new_product->left = NULL;
            new_product->right = NULL;

            register_new_product(new_product, sort_by);
        }
    }
    csvfile.close();
}
void load_sales_from_file(int sort_by = 0){
    string sales_details[6];
    string data = "";
    int count_data;

    ifstream csvfile;
    csvfile.open(salesFile);
    string line;

    if(csvfile.is_open()){
        while(getline(csvfile, line)){
            new_sales = new Sales();
            line +=" ";
            count_data = 0;
            for(int i=0; i<line.length(); i++){
                if(line[i] == ',' || i+1==line.length()){
                    sales_details[count_data] = data;
                    count_data++;
                    ++i;
                    data = "";
                }
                else data += line[i];
            }
            new_sales->product_name = sales_details[0];
            new_sales->quantity = stoi(sales_details[1]);
            new_sales->product_unit = sales_details[2];
            new_sales->unit_price = stod(sales_details[3]);
            new_sales->total_price = stod(sales_details[4]);
            new_sales->date = sales_details[5];

            new_sales->left = NULL;
            new_sales->right = NULL;

            register_new_sales(new_sales);
        }
    }
    csvfile.close();
}

void sell_product_handler(){
    new_sales = new Sales();

    system("cls");
    string product_id;
    double total_price;
    int quantity;
    char sold;


    cout<<"\n          >>>>>>>>> Check out Items <<<<<<<<<\n\n";
    cout<<"   Enter Product Id: ";
    cin>>product_id;
    current_product = search_product_by_id(product_id, root_product);
    if(current_product != NULL){
        new_sales->product_name = current_product->name;
        new_sales->unit_price = current_product->selling_price;
        new_sales->product_unit = current_product->unit;

         cout<<"\n\t>>>>> Selling "<<current_product->name<<" <<<<<\n"<<endl;
         cout<<"    Available Quantity: "<<current_product->quantity;
         cout<<"\n        Enter Quantity: ";
         cin>>quantity;
         total_price = quantity*current_product->selling_price;
         cout<<"           Total Price: "<<total_price<<" ETB"<<endl;
         cout<<"\n  -----------------------------------------------------";
         cout<<"\n    Product Sold (y, n): ";
         cin>>sold;
         cout<<"  -----------------------------------------------------";


         new_sales->quantity = quantity;
         new_sales->total_price = total_price;
         new_sales->date = get_current_date();


         if(sold == 'y' || sold == 'Y'){
            if(quantity > current_product->quantity || quantity < 0){
                cout<<"      Invalid Quantity!";
                return;
            }
            current_product->quantity -=  quantity;
            cout<<"\n    "<<quantity<<" "<<current_product->name<<" sold!\n";
            cout<<"    "<<current_product->quantity<<" "<<current_product->unit<<" is left\n";

            register_new_sales(new_sales);
            string sales_details = new_sales->product_name+", "+to_string(new_sales->quantity)+",  "+new_sales->product_unit+", "+to_string(new_sales->unit_price).substr(0, to_string(new_sales->unit_price).find(".")+3)+", "+to_string(new_sales->total_price).substr(0, +to_string(new_sales->total_price).find(".")+3)+", "+new_sales->date;
            write_on_file(sales_details, salesFile);

            ofstream emptyfy;
            emptyfy.open(productsFile);
            emptyfy.close();

            update_products_file(root_product);
         }
         else
            cout<<"\n    Product selling canceled!";

    }
     else
        cout<<"\n    Product Not found!";

}

int main(){
    load_sales_from_file();
    load_products_from_file();
    int opt;
    do{
        system("cls");
        cout<<main_title<<main_menu;
        cin>>opt;
        switch(opt){
            case 1:
                product_registration_handler();
                break;
            case 2:
                display_products(root_product);
                if(item_counter > 1)
                    display_operations();
                break;
            case 3:
                sell_product_handler();
                break;
            case 4:
                display_sales(root_sales);
                break;
            case 5:
                exit(0);
                break;
        }
        cout<<"\n\n\n   </ Enter any key to continue>";
        getch();
    }while(opt != 5);
    return 0;
}
