#include <iostream>
#include <fstream>
#include <json/json.h>


int main()
{
        Json::Value people;

    std::ifstream hh("results.json",std::ifstream::binary);

    hh >> people;
    hh.close();
    long actual = people["clicks"].asInt() ;

    std::cout << people["clicks"] << "\n";
    actual++;
    people["clicks"] = actual  ;

    std::cout << people["clicks"] << "\n";

    std::ofstream out("results.json", std::ofstream::binary);
    out << people;
    out.close();
    
}