#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ball_State {
	ball_Begin,
	ball_Move
};

class Object {
public:
	Object();
	Object(glm::vec2 inPos, glm::vec2 inSize, glm::vec3 inColor);
	glm::vec2 Pos, Size;
	glm::vec3 Color;
};

class Block:public Object {
public:
	Block(glm::vec2 inPos, glm::vec2 inSize, glm::vec3 inColor, bool type);
	bool canDestroy;
};

class Player:public Object {
public:
	Player();
	Player(glm::vec2 inPos, glm::vec2 inSize, glm::vec3 inColor);
	int velocity;
};

class Ball :public Object {
public:
	glm::vec2 velocity;
	int state;
	float radius;

	Ball();
	Ball(glm::vec2 inPos, float radius, glm::vec3 inColor);
	void move(float dt, int window_width, int window_height);
};