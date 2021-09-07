#include "Block.h"

Object::Object(){}
Object::Object(glm::vec2 inPos, glm::vec2 inSize, glm::vec3 inColor) :Pos(inPos), Size(inSize), Color(inColor){}

Block::Block(glm::vec2 inPos, glm::vec2 inSize, glm::vec3 inColor, bool type):Object(inPos, inSize, inColor), canDestroy(type)
{

}

Player::Player(){}

Player::Player(glm::vec2 inPos, glm::vec2 inSize, glm::vec3 inColor) :Object(inPos, inSize, inColor)
{
	this->velocity = 40;
}

Ball::Ball(){}

Ball::Ball(glm::vec2 inPos, float inRadius, glm::vec3 inColor) :Object(inPos, glm::vec2(0.0f), inColor), radius(inRadius)
{
	
}

void Ball::move(float dt, int window_width, int window_height)
{
	this->Pos += this->velocity * dt;
	// 检查是否在窗口边界以外，如果是的话反转速度并恢复到正确的位置
	if (this->Pos.x <= 0.0f)
	{
		this->velocity.x = -this->velocity.x;
		//this->Pos.x = 0.0f;
	}
	else if (this->Pos.x + this->radius >= window_width)
	{
		this->velocity.x = -this->velocity.x;
		//this->Pos.x = window_width - this->Size.x;
	}
	if (this->Pos.y <= 0.0f)
	{
		this->velocity.y = -this->velocity.y;
		//this->Pos.y = 0.0f;
	}
	else if (this->Pos.y + this->radius >= window_height) {
		this->state = ball_Begin;
	}
}