#pragma once
namespace Tmpl8 {

	class ray;
	class camera
	{
	public:
		camera(float verticalFOV, vec3 lookFrom, vec3 lookAt, vec3 viewUp, float focusDistance);
		bool cameraMovement(float deltaTime);
		ray getRay(float u, float v);

		float m_aspectRatio;
		float m_viewportHeight;
		float m_viewportWidth;
		float m_focalLength;
		vec3 m_lookFrom;
		vec3 m_lookAt;

	private:

		void setCameraPos();

		vec3 m_origin;
		vec3 m_horizontal;
		vec3 m_vertical;
		vec3 m_lowerLeft;
		vec3 m_cameraDirection;
		vec3 m_cameraUOrientation;
		vec3 m_cameraVOrientation;

		//So it might be weird for me to put aperture in here, since it means I have to go out of my way to change Depth of Field
		//Well, I don't like how Depth of Field looks, so I don't want to put it on. 
		float m_aperture = 0.f;
		float m_lensRadius;
		float m_verticalFOV;
		float m_focusDistance;
		vec3 m_viewUp;
	};
}