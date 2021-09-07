#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Block.h"
#include "shader.h"
#include "texture.h"
#include "sprite_renderer.h"


enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game {
public:
	//游戏状态
	GameState State;
	//构造/析构函数
	Game();
	~Game();
	void GameInit(int width, int height);
	void MapLoad(const char* mapfile);
	void MapInit(std::vector<std::vector<int>> tileData);
	void Rend();
	void ProcessInput(GLFWwindow *window);
	void update(float dt);
	bool CheckCollision(Ball &one, Object &two);
	void DoCollision();
private:
	std::vector<Block> blocks;
	Player player;
	Ball ball;
	int window_width;
	int window_height;
};