#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "shader.h"
#include "camera.h"
#include "texture.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class spriteRenderer {
public:
	spriteRenderer(Shader &shader);
	~spriteRenderer();
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
	Shader shader;
	unsigned int quadVAO;
	void initRenderer();//初始化渲染器，在(0,0)位置生成一个单位大小的正方形
};

#endif // !SPRITE_RENDERER_H
