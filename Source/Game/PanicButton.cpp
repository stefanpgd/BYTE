#include "PanicButton.h"
#include "Engine/BoxCollider.h"
#include "Engine/Utilities.h"
#include "Graphics/SpriteRenderer.h"
#include "Graphics/TextRenderer.h"
#include "Graphics/PostProcessor.h"
#include "GameSystems/GameTime.h"

#include <imgui.h>

PanicButton::PanicButton()
{
	buttonSprite = new SpriteRenderer("button.png", &transform);
	buttonPressedSprite = new SpriteRenderer("buttonPressed.png", &transform);

	transform.Scale.x = 2.0f;
	transform.Position.y = 15.7f;
	//transform.Position.y = -3.0f;
	transform.Position.x = RandomInRange(-10.0f, 10.0f);

	collider = new BoxCollider(this, glm::vec2(0.5f, 0.3f), "button");
	block = new SpriteRenderer("block.png", &blockTransform);

	textRenderer = new TextRenderer("00:00:00", &textTransform);
	textRenderer->color = glm::vec4(1.0f, 0.15f, 0.0f, 1.0f);
	textRenderer->emission = 2.5f;

	textTransform.Position = glm::vec3(-6.92f, -5.11f, 0.0f);
	textTransform.Scale = glm::vec3(2.0f);

	for (int i = 0; i < 22; i++)
	{
		Transform t;
		t.Position.x = RandomInRange(-20.0f, 20.0f);
		t.Position.y = RandomInRange(20.0f, 255.0f);
		t.Position.z = RandomInRange(0.1f, 2.5f);
		t.Scale = glm::vec3(4.05f, 2.0f, 1.0f);
		t.Scale *= RandomInRange(0.3f, 0.9f);
		t.Rotation.x = Random01();
		t.Rotation.z = RandomInRange(0.0f, 360.0f);

		droppingBlocks.push_back(t);
	}
}

void PanicButton::Update(float deltaTime)
{
	if (pressed)
	{
		t = Lerp(t, 0.23f, deltaTime * 0.5f);

		Camera::ApplyScreenshake(1.0f, t);

		announcementTime += deltaTime;
		blockFallSpeed += deltaTime * 0.2f;

		if (announcementTime > 8.2f && !playedMusic)
		{
			playedMusic = true;
			Audio::PlaySound("alarmMusic.wav", 1.0f);
		}

		if (announcementTime > 10.0f)
		{
			eventTimer -= deltaTime;

			int minutes = glm::floor(eventTimer / 60);
			int seconds = (int)eventTimer % 60;
			int milliseconds = glm::fract(eventTimer) * 100.0;

			std::string timerText;
			if (seconds < 10)
			{
				timerText = "0" + std::to_string(minutes) + ":0" + std::to_string(seconds) + ":" + std::to_string(milliseconds);
			}
			else
			{
				timerText = "0" + std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(milliseconds);
			}

			textRenderer->UpdateText(timerText);
		}

		for (Transform& t : droppingBlocks)
		{
			t.Position.y -= blockFallSpeed * t.Scale.y * deltaTime;

			float m = t.Rotation.x * 2.0f - 1.0f;
			t.Rotation.z += blockRotationSpeed * m * deltaTime;

			if (t.Position.y < -20.0f)
			{
				t.Position.x = RandomInRange(-20.0f, 20.0f);
				t.Position.y = RandomInRange(20.0f, 255.0f);
				t.Position.z = RandomInRange(0.1f, 10.5f);

				t.Scale = glm::vec3(4.05f, 2.0f, 1.0f);
				t.Scale *= RandomInRange(0.3f, 0.9f);
			}
		}
	}
}

void PanicButton::Draw(Camera* camera)
{
	if (pressed)
	{
		buttonPressedSprite->Draw(camera);
		textRenderer->Draw(camera);

		for (Transform& t : droppingBlocks)
		{
			blockTransform = t;
			block->Draw(camera);
		}
	}
	else
	{
		buttonSprite->Draw(camera);
	}
}

void PanicButton::OnCollision(BoxCollider* collider)
{
	if (!pressed)
	{
		if (collider->Tag == "ball")
		{
			Audio::PlaySound("buttonClick.wav");
			Audio::PlaySound("selfdestruct.wav", 1.25f);
			Audio::PlaySound("alarm.mp3", 1.25f);

			PostProcessor::runAlarmEffects = true;

			pressed = true;
		}
	}
}

void PanicButton::ImGuiDraw()
{
	ImGui::Begin("Button");
	ImGui::DragFloat3("Pos", &textTransform.Position[0], 0.01f);
	ImGui::DragFloat3("Scale", &textTransform.Scale[0], 0.01f);
	ImGui::End();
}