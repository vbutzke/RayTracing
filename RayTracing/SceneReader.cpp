#include "SceneReader.h"

SceneReader::SceneReader()
{
}

bool SceneReader::isTransformationContinuous(string transformation) {
	if (transformation == "true") {
		return true;
	}
	return false;
}

scene SceneReader::readConfigFile(string filename, model* modelObj) {
	std::ifstream file;
	file.open(filename);
	std::stringstream filestream;
	filestream << file.rdbuf();
	std::string vertexCode;
	vertexCode = filestream.str();
	vector <string> token = tokenize(vertexCode);
	scene scene;
	int objSize;
	int count = 0;
	double first;
	double second;
	double third;
	double fourth;

	for (int i = 0; i < token.size(); i++) {
		if (token[i] == "file name") {
			scene.setFileName(token[++i]);
		}

		if (token[i] == "light") {
			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setPositions(glm::vec3(first, second, third));

			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setColors(glm::vec3(first, second, third));

			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setObjectColors(glm::vec3(first, second, third));
		}
		if (token[i] == "camera") {
			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setUpVector(glm::vec3(first, second, third));

			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setWhereToLook(glm::vec3(first, second, third));

			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setEyeLine(glm::vec3(first, second, third));
		}
		if (token[i] == "projection") {
			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			fourth = ::atof(token[++i].c_str());
			scene.setProjection(glm::vec4(first, second, third, fourth));
		}

		if (token[i] == "transformations") {
			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setRotation(glm::vec3(first, second, third));
			scene.setAngle(::atof(token[++i].c_str()));

			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setTranslation(glm::vec3(first, second, third));

			first = ::atof(token[++i].c_str());
			second = ::atof(token[++i].c_str());
			third = ::atof(token[++i].c_str());
			scene.setScale(glm::vec3(first, second, third));
		}

		if (token[i] == "objects") {
			vector<obj> temp = scene.getObjects();
			obj nobj;
			nobj.setName(token[++i]);
			nobj.setMTLname(token[++i]);
			temp.push_back(nobj);
			scene.setObjects(temp);
		}

		//anima��o
	}

	return scene;
}

void SceneReader::read(string fileName, model* modelObj) {

	std::ifstream file;
	file.open(fileName);
	std::stringstream filestream;
	filestream << file.rdbuf();
	std::string vertexCode;
	vertexCode = filestream.str();
	vector <string> obj = tokenize(vertexCode);
	std::string coord;
	std::string f;  //v�rtices
	std::string fn; //normais
	std::string ft; //texturas
	int posFirst; //primeira barra da face
	int posSec;   //segunda barra da face
	string material;
	bool readPrvsF = false;


	vector<GLfloat> verticesObj;
	vector<GLfloat> verticesNormais;
	vector<GLfloat> verticesTexturas;
	vector<GLuint> indicesNormais;
	vector<GLuint> indicesObj;
	vector<GLuint> indicesTexturas;


	for (int i = 0; i < obj.size(); i++) {
		if (obj[i] == "v") {
			verticesObj.push_back(::atof(obj[++i].c_str()));
			verticesObj.push_back(::atof(obj[++i].c_str()));
			verticesObj.push_back(::atof(obj[++i].c_str()));
		}
		if (obj[i] == "vn") {
			verticesNormais.push_back(::atof(obj[++i].c_str()));
			verticesNormais.push_back(::atof(obj[++i].c_str()));
			verticesNormais.push_back(::atof(obj[++i].c_str()));
		}
		if (obj[i] == "vt") {
			verticesTexturas.push_back(::atof(obj[++i].c_str()));
			verticesTexturas.push_back(::atof(obj[++i].c_str()));
		}
		if (obj[i] == "f") {
			int cont = 1;
			while (cont <= 3) {
				coord = obj[++i];
				posFirst = coord.find("/");
				f = coord.substr(0, posFirst);
				posSec = coord.find("/", posFirst + 1);
				ft = coord.substr(posFirst + 1, 1);
				fn = coord.substr(posSec + 1);
				indicesObj.push_back(::atof(f.c_str()) - 1);
				indicesNormais.push_back(::atof(fn.c_str()) - 1);
				indicesTexturas.push_back(::atof(ft.c_str()) - 1);
				cont++;
			}
		}
		int next = i;
		next++;
		if ((next >= obj.size()) || (next<obj.size() && obj[next] == "v")) {
			if (readPrvsF) {
				readPrvsF = false;
				mesh mesh(material);
				mesh.createMesh(verticesObj, verticesNormais, verticesTexturas, indicesNormais, indicesObj, indicesTexturas);
				modelObj->addMesh(mesh);
			}
		}
		if (obj[i] == "usemtl") {
			material = obj[++i];
			readPrvsF = true;
		}
	}
}

void SceneReader::readMTL(string fileName, model* modelObj) {

	std::ifstream file;
	file.open(fileName);
	std::stringstream filestream;
	filestream << file.rdbuf();
	std::string vertexCode;
	vertexCode = filestream.str();
	vector <string> obj = tokenize(vertexCode);

	string name, map_Kd;
	GLfloat Ns, Ni, d, illum;
	GLfloat Tf[3], Ka[3], Kd[3], Ks[3];
	bool readPrvsTexture = false;

	for (int i = 0; i < obj.size(); i++) {
		if (obj[i] == "newmtl") {
			name = obj[++i];
		}
		if (obj[i] == "Ns") {
			Ns = ::atof(obj[++i].c_str());
		}
		if (obj[i] == "Ni") {
			Ni = ::atof(obj[++i].c_str());
		}
		if (obj[i] == "d") {
			d = ::atof(obj[++i].c_str());
		}
		if (obj[i] == "Tf") {
			Tf[0] = ::atof(obj[++i].c_str());
			Tf[1] = ::atof(obj[++i].c_str());
			Tf[2] = ::atof(obj[++i].c_str());
		}
		if (obj[i] == "illum") {
			illum = ::atof(obj[++i].c_str());
		}
		if (obj[i] == "Ka") {
			Ka[0] = ::atof(obj[++i].c_str());
			Ka[1] = ::atof(obj[++i].c_str());
			Ka[2] = ::atof(obj[++i].c_str());
		}
		if (obj[i] == "Kd") {
			Kd[0] = ::atof(obj[++i].c_str());
			Kd[1] = ::atof(obj[++i].c_str());
			Kd[2] = ::atof(obj[++i].c_str());
		}
		if (obj[i] == "Ks") {
			Ks[0] = ::atof(obj[++i].c_str());
			Ks[1] = ::atof(obj[++i].c_str());
			Ks[2] = ::atof(obj[++i].c_str());
		}
		if (obj[i] == "map_Kd") {
			map_Kd = obj[++i];
			readPrvsTexture = true;
		}
		int next = i;
		next++;
		if ((next >= obj.size()) || (next < obj.size() && obj[next] == "newmtl")) {
			if (readPrvsTexture) {
				mtl mtl(name, Ns, Ni, d, Tf, illum, Ka, Kd, Ks, map_Kd);
				modelObj->addMTL(mtl);
				readPrvsTexture = false;
				Ns, Ni, d, illum = 0;
				name, map_Kd = "";
				std::fill_n(Tf, 3, 0);
				std::fill_n(Ka, 3, 0);
				std::fill_n(Kd, 3, 0);
				std::fill_n(Ks, 3, 0);
			}
		}
	}
}

SceneReader::~SceneReader()
{
}