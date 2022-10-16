#pragma once

namespace Tmpl8 {
	constexpr int numberOfLights = 2;
	class Surface;
	class imageTexture;
	class Game
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
#pragma warning (disable: 4100)
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y) { /* implement if you want to detect mouse movement */ }
		void KeyUp(int key) { /* implement if you want to handle keys */ }
		void KeyDown(int key) { /* implement if you want to handle keys */ }

	private:
		Surface* screen{ nullptr };
		unsigned short int red;
		unsigned short int green;
		unsigned short int blue;

		Pixel color;
		float temporaryIntersect;
		const int maxDepth = 20;
		const int samples = 10000;
		int currentSample = 0;
		int tSeed;
		int* seedPointer;
		bool debugRays = false;
		//one of the values needs to be a float for the division to work, preferably both though. 
		const float DividedBySamples = 1.f / static_cast<float>(samples);
		void doRayTracing(int startX, int endX, int startY, int endY);
		vec3* savedColors;

	};

}; // namespace Tmpl8