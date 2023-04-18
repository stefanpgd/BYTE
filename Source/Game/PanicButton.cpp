#include "PanicButton.h"
#include "Engine/BoxCollider.h"
#include "Engine/Utilities.h"
#include "Graphics/SpriteRenderer.h"
#include "Engine/Audio.h"
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

}

void PanicButton::Update(float deltaTime)
{
	if (pressed)
	{
		t = Lerp(t, 0.2f, deltaTime * 0.5f);
		Camera::ApplyScreenshake(1.0f, t);

		announcementTime += deltaTime;

		if (announcementTime > 8.2f && !playedMusic)
		{
			playedMusic = true;
			Audio::PlaySound("alarmMusic.wav", 0.65);
		}
	}
}

void PanicButton::Draw(Camera* camera)
{
	if (pressed)
	{
		buttonPressedSprite->Draw(camera);
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
			Audio::PlaySound("selfdestruct.wav");
			Audio::PlaySound("alarm.mp3");

			PostProcessor::runAlarmEffects = true;

			pressed = true;
		}
	}
}