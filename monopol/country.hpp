#include <set>
#include <string>

#ifndef COUNTRY_HPP
#define COUNTRY_HPP

using namespace std;

class Country {
    private:
        string name;
        set<int> properties;
    
    public:
        Country();
        Country(string name, set<int> properties);
        ~Country();
        string getName();
        void setName(string name);
        set<int> getProperties();
        void setProperties(set<int> properties);
};

#endif