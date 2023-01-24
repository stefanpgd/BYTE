#pragma once

class Camera;
class Player;

class GameManager
{
public:
	GameManager();

	void Update(float deltaTime);
	void Draw();
	void ImGuiDraw();

private:
	Camera* camera;

	Player* player;
};