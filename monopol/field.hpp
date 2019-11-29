#include "fieldtype.hpp"

#ifndef FIELD_H
#define FIELD_H

class Field {
    private:
        FieldType type;
        int fieldNumber;
    
    public:
        Field(FieldType type, int fieldNumber);
        ~Field();
        FieldType getFieldType();
		int getFieldNumber();
		void setField(FieldType type, int fieldNumber);
};

#endif