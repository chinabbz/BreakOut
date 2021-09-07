#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Game::Game()
{
	
}

void Game::GameInit(int width, int height)
{
	this->player = Player(glm::vec2(100, height - 20), glm::vec2(100, 20), glm::vec3(1.0f));
	this->ball = Ball(glm::vec2(this->player.Pos.x + this->player.Size.x / 2, this->player.Pos.y - 10.0), 10.0, glm::vec3(1.0f));
	std::cout << this->ball.radius << std::endl;
	window_width = width;
	window_height = height;
	this->ball.state = ball_Begin;
}

Game::~Game()
{

}

void Game::MapLoad(const char* mapfile)
{
	// 从文件中加载
	int tileCode;
	std::string line;
	std::ifstream fstream(mapfile);
	std::vector<std::vector<int>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // 读取关卡文件的每一行
		{
			std::istringstream sstream(line);
			std::vector<int> row;
			while (sstream >> tileCode) // 读取被空格分隔的每个数字
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		this->MapInit(tileData);
	}
}

void Game::MapInit(std::vector<std::vector<int>> tileData)
{
	int unit_width = this->window_width / tileData[0].size();
	int unit_height = this->window_height /2/ tileData.size();
	//将砖块数据放入vector中
	for (int y = 0; y < tileData.size(); y++) {
		for (int x = 0; x < tileData[0].size(); x++) {
			if (tileData[y][x] == 1) {
				this->blocks.push_back(Block(glm::vec2(x * unit_width, y * unit_height), glm::vec2(unit_width, unit_height), glm::vec3(0.8f, 0.8f, 0.7f), false));
			}if (tileData[y][x] > 1) {
				this->blocks.push_back(Block(glm::vec2(x * unit_width, y * unit_height), glm::vec2(unit_width, unit_height), glm::vec3(0.2f, 0.6f, 1.0f), true));
			}
		}
	}
}

void Game::Rend()
{
	Shader screenShader("shader.vs", "shader.fs");
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, static_cast<GLfloat>(this->window_width), static_cast<GLfloat>(this->window_height), 0.0f, -1.0f, 1.0f);//正视投影
	screenShader.use();
	screenShader.setMat4("projection", projection);
	screenShader.setInt("texture1", 0);

	Texture2D texture1;
	int width, height, nrChannels;
	unsigned char* data = stbi_load("resources/textures/block_solid.png", &width, &height, &nrChannels, 0);
	texture1.Generate(width, height, data, nrChannels);

	Texture2D texture2;
	data = stbi_load("resources/textures/block.png", &width, &height, &nrChannels, 0);
	texture2.Generate(width, height, data, nrChannels);

	Texture2D player_Tex;
	data = stbi_load("resources/textures/paddle.png", &width, &height, &nrChannels, 0);
	player_Tex.Generate(width, height, data, nrChannels);

	Texture2D ball_Tex;
	data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	ball_Tex.Generate(width, height, data, nrChannels);

	stbi_image_free(data);

	spriteRenderer sprite(screenShader);

	for (auto &it : this->blocks) {
		if(it.canDestroy)
			sprite.DrawSprite(texture2, it.Pos, it.Size, 0.0f, it.Color);
		else
			sprite.DrawSprite(texture1, it.Pos, it.Size, 0.0f, it.Color);
	}
	sprite.DrawSprite(player_Tex, player.Pos, player.Size, 0.0f, player.Color);
	
	sprite.DrawSprite(ball_Tex, ball.Pos, glm::vec2(ball.radius, ball.radius), 0.0f, ball.Color);
}

void Game::ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		if(this->player.Pos.x>0)
			this->player.Pos.x -= this->player.velocity;

	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		if (this->player.Pos.x < this->window_width-player.Size.x)
			this->player.Pos.x += this->player.velocity;

	if (this->ball.state == ball_Begin) {
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			this->ball.state = ball_Move;
			this->ball.velocity = glm::vec2(200.0f, -200.0f);
		}
	}
		
}

void Game::update(float dt)
{
	if (this->ball.state == ball_Begin) {
		this->ball.Pos.x = this->player.Pos.x + this->player.Size.x / 2;
		this->ball.Pos.y = this->player.Pos.y - this->ball.radius;
	}
		
	if (this->ball.state == ball_Move) {
		this->ball.move(dt, this->window_width, this->window_height);
		this->DoCollision();
	}
		

	
		
}

bool Game::CheckCollision(Ball &one, Object &two)
{
	// 获取圆的中心 
	glm::vec2 center(one.Pos + one.radius);
	// 计算AABB的信息（中心、半边长）
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(
		two.Pos.x + aabb_half_extents.x,
		two.Pos.y + aabb_half_extents.y
	);
	// 获取两个中心的差矢量
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	// 获得圆心center和最近点closest的矢量并判断是否 length <= radius
	difference = closest - center;
	if (glm::length(difference) < one.radius) {
		glm::vec2 center_to_closest = closest - aabb_center;
		if (fabs(center_to_closest.x - aabb_half_extents.x) < 0.01 || fabs(center_to_closest.x + aabb_half_extents.x) < 0.01)
			this->ball.velocity.x = -this->ball.velocity.x;
		if (fabs(center_to_closest.y - aabb_half_extents.y) < 0.01 || fabs(center_to_closest.y + aabb_half_extents.y) < 0.01) {
			std::cout << center_to_closest.y << "," << aabb_half_extents.y << std::endl;
			this->ball.velocity.y = -this->ball.velocity.y;
		}
			
		return true;
	}
	else
		return false;
}

void Game::DoCollision()
{
	for (int i = 0; i < blocks.size();i++) {
		if (blocks[i].canDestroy) {
			if (CheckCollision(ball, blocks[i])) {
				blocks.erase(std::begin(blocks) + i);
				i--;
			}
		}
	}
	//与玩家的碰撞
	if(this->ball.velocity.y > 0)
		CheckCollision(ball, this->player);
}