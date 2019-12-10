#include "country.hpp"
#include <set>

Country::Country() {

}

Country::Country(string name, set<int> properties) {
    this->setName(name);
    this->setProperties(properties);
}

Country::~Country() {
    this->properties.clear();
}

string Country::getName() {
    return this->name;
}

void Country::setName(string name) {
    this->name = name;
}

set<int> Country::getProperties() {
    return this->properties;
}

void Country::setProperties(set<int> properties) {
    this->properties = properties;
}

