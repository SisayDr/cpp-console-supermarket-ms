#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED
#include <iostream>
using namespace std;



const string productsFile = "./DB/Products.csv", salesFile = "./DB/Sales.csv";

string get_current_date(){
    time_t t = time(0);
    tm* now = localtime(&t);
    string today = to_string((now->tm_year+1900))+"-"+to_string(now->tm_mon+1)+"-"+to_string(now->tm_mday);

    return today;
}

void write_on_file(string line, string file){
    ofstream write_line;
    write_line.open(file, ios::app);
    write_line<<line<<"\n";
    write_line.close();


}

#endif // HELPERS_H_INCLUDED
