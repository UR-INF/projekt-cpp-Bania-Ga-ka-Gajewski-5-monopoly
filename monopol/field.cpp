#include "field.hpp"

Field::Field(FieldType type, int fieldNumber) {
    this->type = type;
    this->fieldNumber = fieldNumber;
}

Field::~Field() {

}

FieldType Field::getFieldType() {
    return this->type;
}