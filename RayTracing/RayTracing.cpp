#include "RayTracing.h"

RayTracing::RayTracing()
{
}

void RayTracing::render(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3& color) {

	//glm::vec3 *image = new glm::vec3[width * height], *pixel = image;
	
	//void rayTrancingRec(raio) {
	//	Inicialize MAIS_PROXIMO para infinito e OBJETO_MAIS_PROXIMO para NULL
	//		Para cada objeto na cena{
	//		Se o raio intersecta esse objeto{
	//		Se a distancia at� essa interse��o � menor que MAIS_PROXIMO{
	//		MAIS_PROXIMO <-distancia at� essa interse��o
	//		OBJETO_MAIS_PROXIMO <-identificador desse objeto
	//	}
	//	}
	//	}
	//		Se OBJETO_MAIS_PROXIMO == 0 {
	//		Preencha esse pixel com a cor do fundo
	//	} Sen�o{
	//		Compute um raio para cada fonte de luz para checar por sombra(corO = ilumLocal() ou sombra)
	//		Se a superf�cie � reflectiva, gere o raio de reflex�o->corR = rayTrancingRec(raioRef)
	//			Se a superf�cie possui refra��o, gere o raio refratado->corT = rayTrancingRec(raioTransmitido, mat)
	//			Compute a cor do ponto ser� : cor = interpola��o(corO, corR, corT, kr, kt);
	//		retorna cor;
	//	}
	//}
}

RayTracing::~RayTracing()
{
}
