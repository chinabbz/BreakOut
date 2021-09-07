#include "sprite_renderer.h"

spriteRenderer::spriteRenderer(Shader &shader)
{
	this->shader = shader;
	this->initRenderer();
}

spriteRenderer::~spriteRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void spriteRenderer::initRenderer()
{
	float vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &this->quadVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将顶点数据绑定到当前默认的缓冲上,GL_STATIC_DRAW 表示我们的三角形位置数据不会被改变
	
	glBindVertexArray(this->quadVAO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);//解释顶点数据
	glEnableVertexAttribArray(0);//表明我们开启了 0 的这个通道，默认状态下是关闭的，因此我们在这里要开启一下

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void spriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	//先尺度再旋转再平移，因为矩阵是从右到左，所以顺序反过来了
	this->shader.use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	this->shader.setMat4("modelMatrix", model);

	// Render textured quad
	this->shader.setVec3("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}