
#ifndef GAME_LIT_2D_H
#define GAME_LIT_2D_H

#include <GL/glew.h>
#include <Game/Vector2.h>

namespace game
{
	class Lit2D
	{
		static const int MAX_SPOTLIGHTS = 8,
			MAX_POINTLIGHTS = 8;

		GLuint _program;
		
		struct
		{
			float R, G, B;
		} _ambientLight;

		struct
		{
			float R[MAX_POINTLIGHTS];
			float G[MAX_POINTLIGHTS];
			float B[MAX_POINTLIGHTS];
			float Intensity[MAX_POINTLIGHTS];
			Vector2f Position[MAX_POINTLIGHTS];
		} _pointLight;

		struct
		{
			float R[MAX_SPOTLIGHTS];
			float G[MAX_SPOTLIGHTS];
			float B[MAX_SPOTLIGHTS];
			float CutOffAngle[MAX_SPOTLIGHTS];
			Vector2f Position[MAX_SPOTLIGHTS];
			Vector2f Direction[MAX_SPOTLIGHTS];
		} _spotLight;

		Lit2D() { }

	public:
		static Lit2D &Get();
		void Use() const;
	};
}

#endif
