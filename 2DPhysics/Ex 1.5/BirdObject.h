#pragma once
#include "Utility.h"
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Bird : public Object
{
public:
	Bird();
	~Bird();
	Bird(Transform _Transform, b2BodyType _Type, GLuint _ShaderProgram, GLuint _Texture);

	void Init(b2World * _World);
	void Process();
	void Render();

	b2Vec2 m_SpawnPos;
	bool m_bEnableDecay;
private:
	b2CircleShape CircleBody;
	float m_Radius;
	float m_fDecayTimer;
};