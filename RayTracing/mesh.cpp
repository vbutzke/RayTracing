#include "mesh.h"

mesh::mesh(string mtlNamep) {
	mtlName = mtlNamep;
}

void mesh::createMesh(vector<GLfloat> vObj, vector<GLfloat> vNormais, vector<GLfloat> vTexturas, vector<GLuint> iNormais, vector<GLuint> iObj, vector<GLuint> iTexturas) {

	for (int i = 0; i < vObj.size(); i++) {
		vo.push_back(vObj[i]);
	}

	for (int j = 0; j < vNormais.size(); j++) {
		vn.push_back(vNormais[j]);
	}

	for (int k = 0; k < vTexturas.size(); k++) {
		vt.push_back(vTexturas[k]);
	}

	for (int l = 0; l < iObj.size(); l++) {
		io.push_back(iObj[l]);
	}

	for (int m = 0; m < iNormais.size(); m++) {
		in.push_back(iNormais[m]);
	}

	for (int n = 0; n < iTexturas.size(); n++) {
		it.push_back(iTexturas[n]);
	}

}

void mesh::bindMesh(){

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBOv);
	glGenBuffers(1, &VBOn);
	glGenBuffers(1, &VBOt);
	glGenBuffers(1, &EBOv);
	glGenBuffers(1, &EBOn);
	glGenBuffers(1, &EBOt);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBOv);
	glBufferData(GL_ARRAY_BUFFER, vo.size()*sizeof(GLfloat), &vo[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOv);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, io.size() * sizeof(GLuint), &io[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Normal attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBOn);
	glBufferData(GL_ARRAY_BUFFER, vn.size() * sizeof(GLfloat), &vn[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	//Texture attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBOt);
	glBufferData(GL_ARRAY_BUFFER, vt.size() * sizeof(GLfloat), &vt[0], GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

int mesh::bindTexture(vector<mtl> mtls, Shader* shader) {
	int i = 0;
	textures texture;
	int textureBind = 0;

	while (i<mtls.size()) {
		if (getMTLName() == mtls[i].getName()) {
			textureBind = texture.createTexture(mtls[i].getMap_Kd().c_str());
			break;
		}
		i++;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureBind);
	glBindTexture(GL_TEXTURE_2D, EBOt);
	glUniform1i(glGetUniformLocation(shader->Program, "texture1"), 0);
	return textureBind;
}

void mesh::draw(Shader* shader, int texture){
	shader->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, io.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

string mesh::getMTLName() {
	return mtlName;
}

void mesh::terminate() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBOv);
	glDeleteBuffers(1, &VBOn);
	glDeleteBuffers(1, &VBOt);
}

mesh::~mesh()
{
}