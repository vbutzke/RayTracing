#include "mtl.h"

mtl::mtl(string namep, GLfloat Nsp, GLfloat Nip, GLfloat dp, GLfloat Tfp[3], GLfloat illump, GLfloat Kap[3], GLfloat Kdp[3], GLfloat Ksp[3], string map_Kdp) {
	name = namep;
	Ns = Nsp;
	Ni = Nip;
	d = dp;

	Tf[0] = Tfp[0];
	Tf[1] = Tfp[1];
	Tf[2] = Tfp[2];

	illum = illump;

	Ka[0] = Kap[0];
	Ka[1] = Kap[1];
	Ka[2] = Kap[2];

	Kd[0] = Kdp[0];
	Kd[1] = Kdp[1];
	Kd[2] = Kdp[2];

	Ks[0] = Ksp[0];
	Ks[1] = Ksp[1];
	Ks[2] = Ksp[2];

	map_Kd = map_Kdp;
}

string mtl::getName() {
	return name;
}

GLfloat mtl::getNs(){
	return Ns;
}

GLfloat mtl::getNi(){
	return Ni;
}

GLfloat mtl::getD(){
	return d;
}

GLfloat mtl::getIllum(){
	return illum;
}

GLfloat* mtl::getTf(){
	return Tf;
}

GLfloat* mtl::getKa(){
	return Ka;
}

GLfloat* mtl::getKd(){
	return Kd;
}

GLfloat* mtl::getKs(){
	return Ks;
}

string mtl::getMap_Kd(){
	return map_Kd;
}

mtl::~mtl()
{
}
