#pragma once

namespace Tmpl8
{
	class sceneLoader
	{
	public:
		sceneLoader();
		void loadScene(ListOfHittables& world, int sceneIndex);

	private:
		void makeFlake(vec3 center, int flakeDepth, float radius, ListOfHittables& world);
		int m_sceneIndex = 0;
		const int m_maxFlakeDepth = 6;
	};
}