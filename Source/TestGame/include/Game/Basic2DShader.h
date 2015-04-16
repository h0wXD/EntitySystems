

#ifndef GAME_BASIC_2D_SHADER_H
#define GAME_BASIC_2D_SHADER_H

#include <GL/glew.h>
#include <Game/Vector2.h>

namespace game
{
	class Basic2DShader
	{
		GLuint _program;

		GLint _offset;
		GLint _lightCount;
		GLint _projection;

		struct
		{
			GLint Position[16];
			GLint Color[16];
			GLint Intensity[16];
		} _light;

		struct
		{
			GLint Color;
			GLint Intensity;
		} _ambient;

		Basic2DShader();
	public:
		static Basic2DShader &Get();
		void Use() const
		{
			glUseProgram(_program);
		}

		void SetOffset(Vector2f offset, float depth) const
		{
			glUniform3f(_offset, offset.x, offset.y, depth);
		}

		void SetLightCount(int lightCount) const
		{
			glUniform1i(_lightCount, lightCount);
		}

		void SetProjection() const {}

		void SetLightPosition(int i, Vector2f position) const
		{
			glUniform2f(_light.Position[i], position.x, position.y);
		}

		void SetLightColor(int i, float r, float g, float b) const
		{
			glUniform3f(_light.Color[i], r, g, b);
		}

		void SetLightIntensity(int i, float decay) const
		{
			glUniform1f(_light.Intensity[i], decay);
		}

		void SetAmbientColor(float r, float g, float b) const
		{
			glUniform3f(_ambient.Color, r, g, b);
		}

		void SetAmbientIntensity(float intensity) const
		{
			glUniform1f(_ambient.Intensity, intensity);
		}
	};
}

#endif
