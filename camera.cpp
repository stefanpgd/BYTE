#include "precomp.h"
#include "ray.h"
#include "camera.h"
#include <Windows.h>
#include "RayTracingUtilities.h"


namespace Tmpl8 {

	camera::camera(float verticalFOV, vec3 lookFrom, vec3 lookAt, vec3 viewUp, float focusDistance)
	{
		m_lookFrom = lookFrom;
		m_lookAt = lookAt;
		m_viewUp = viewUp;
		m_verticalFOV = verticalFOV;
		m_focusDistance = focusDistance;
		//IMPORTANT NOTE
		//JaccoTemplate inverses the Y coördinate. This means the viewUp is actually a vector down in code, but the vector is making it go up. 
		float tangent = tan(degreesToRadians(m_verticalFOV) * 0.5f);

		m_aspectRatio = static_cast<float>(ScreenWidth) / static_cast<float>(ScreenHeight);
		m_viewportHeight = 2.0f * tangent;
		m_viewportWidth = m_viewportHeight * m_aspectRatio;

		m_lensRadius = m_aperture * 0.5f;

		setCameraPos();
	}

	ray camera::getRay(float u, float v)
	{
		//If aperture is 0, you should not have to do randomInUnitDisk, saving quite a few cycles. 
		vec3 offset = 0.f;
		if (m_lensRadius > 0.0001f)
		{
			vec3 rayDisk = m_lensRadius * randomInUnitDisk();
			offset = u * rayDisk.x + v * rayDisk.y;
		}
		return ray(offset + m_origin, m_lowerLeft + u * m_horizontal + v * m_vertical - m_origin - offset);
	}

	bool camera::cameraMovement(float deltaTime)
	{
		vec3 prevFrom = m_lookFrom;
		vec3 prevAt = m_lookAt;
		if (GetAsyncKeyState('W')) m_lookFrom.y -= 100 * deltaTime;
		if (GetAsyncKeyState('S')) m_lookFrom.y += 100 * deltaTime;
		if (GetAsyncKeyState('A')) m_lookFrom.x += 100 * deltaTime;
		if (GetAsyncKeyState('D')) m_lookFrom.x -= 100 * deltaTime;
		for (int i = 0; i < 3; i++)
		{
			if (m_lookFrom[i] != prevFrom[i] || m_lookAt[i] != prevAt[i])
			{
				setCameraPos();
				return true;
			}
		}

		return false;
	}

	void camera::setCameraPos()
	{
		m_cameraDirection = (m_lookFrom - m_lookAt).normalized();
		//U is horizontal
		m_cameraUOrientation = cross(m_viewUp, m_cameraDirection).normalized();
		//V is vertical. V is relative to U, so don't normalize V.
		m_cameraVOrientation = cross(m_cameraUOrientation, m_cameraDirection);
		m_origin = m_lookFrom;
		m_horizontal = m_viewportWidth * -m_cameraUOrientation * m_focusDistance;
		m_vertical = m_viewportHeight * m_cameraVOrientation * m_focusDistance;
		m_lowerLeft = m_origin - m_horizontal * 0.5f - m_vertical * 0.5f - m_cameraDirection * m_focusDistance;
	}
};
