#include <thread>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> result;
string ip;

void curl(string what)
{
    system(("curl https://ipapi.co/" + ip + "/" + what + "/ 2>nul > " + what + ".txt").c_str());

    ifstream file(what + ".txt");

    if (file.is_open())
    {
        string save;
        
        getline(file, save);
        file.close();
        remove((what + ".txt").c_str());
        
        save = what + ": " + save;
        result.push_back(save);

        return;
    }
    else
        return;
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        cout << "Syntax: lookup.exe <ip-addr>";
        return 0;
    }
    ip = argv[1];
    
    thread country(curl, "country");
    thread city(curl, "city");
    thread region(curl, "region");
    thread postal(curl, "postal");
    thread country_calling_code(curl, "country_calling_code");
    thread currency(curl, "currency");
    thread languages(curl, "languages");
    
    // Wait for Threads
    
    country.join();
    city.join();
    region.join();
    postal.join();
    currency.join();
    country_calling_code.join();
    languages.join();
    
    // Output Vector
    
    for (int i = 0; i < result.size(); i++)
    {
        cout << "\n" << result[i];
    }

    cout << "\n";

    return 0;
}
