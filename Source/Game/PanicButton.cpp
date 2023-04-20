#include "PanicButton.h"
#include "Engine/BoxCollider.h"
#include "Engine/Utilities.h"
#include "Graphics/SpriteRenderer.h"
#include "Graphics/PostProcessor.h"

PanicButton::PanicButton()
{
	buttonSprite = new SpriteRenderer("button.png", &transform);
	buttonPressedSprite = new SpriteRenderer("buttonPressed.png", &transform);

	transform.Scale.x = 2.0f;
	transform.Position.y = 15.7f;
	transform.Position.y = -3.0f;
	transform.Position.x = RandomInRange(-10.0f, 10.0f);

	collider = new BoxCollider(this, glm::vec2(0.5f, 0.3f), "button");
	block = new SpriteRenderer("block.png", &blockTransform);

	for (int i = 0; i < 22; i++)
	{
		Transform t;
		t.Position.x = RandomInRange(-20.0f, 20.0f);
		t.Position.y = RandomInRange(20.0f, 255.0f);
		t.Position.z = 0.25f;
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

		if (announcementTime > 8.2f && !playedMusic)
		{
			playedMusic = true;
			Audio::PlaySound("alarmMusic.wav", 1.0f);
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