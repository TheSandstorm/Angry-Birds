#pragma once
#include "Utility.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Enemy : public Object
{
public:
	Enemy();
	~Enemy();
	Enemy(Transform _Transform, b2BodyType _Type, GLuint _ShaderProgram, GLuint _Texture);

	b2Vec2 m_SpawnPos;

	void Init(b2World * _World);
	bool Process();
	void Render();
	void SetPosition(b2Vec2 _Pos);



protected:

	b2CircleShape CircleBody;
	float m_Radius;


};