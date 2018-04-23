#include "obj.h"

obj::obj() {
}

string obj::getName() {
	return name;
}

string obj::getMTLname() {
	return mtlName;
}

void obj::setName(string newName) {
	name = newName;
}

void obj::setMTLname(string newMTLname) {
	mtlName = newMTLname;
}

obj::~obj() {
}
