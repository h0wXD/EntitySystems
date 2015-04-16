#include <Game/Basic2DShader.h>
#include <iostream>
#include <string>

namespace game
{
	Basic2DShader::Basic2DShader()
	{
		const char *vertexSource =
			"#version 330 core\n"

			"layout (location = 0) in vec2 aPosition;"

			"out vec2 _position;"
			"uniform mat4 uProjection;"
			"uniform vec3 uOffset;"

			"void main()"
			"{"
			"   /*gl_Position = uProjection * vec3(aPosition + uOffset.xy, uOffset.z);*/"
			"   gl_Position = vec4(vec3(aPosition + uOffset.xy, uOffset.z), 1);"
			"   _position = aPosition + uOffset.xy;"
			"}";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, nullptr);
		glCompileShader(vertexShader);
		GLint success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar log[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, log);
			std::cerr << log << std::endl;
		}

		const char *fragmentSource =
			"#version 330 core\n"
			"#define MAX_LIGHTS 16\n"

			"struct Light"
			"{"
			"   vec2  position;"
			"   vec3  color;"
			"   float decay;"
			"};"

			"struct Ambient"
			"{"
			"   vec3  color;"
			"   float intensity;"
			"};"

			"out vec4 _color;"
			"in vec2 _position;"
			"uniform int uLightCount;"
			"uniform Light uLights[MAX_LIGHTS];"
			"uniform Ambient uAmbient;"

			"void main()"
			"{"
			"   vec4 outColor = vec4(0.2f, 0.5f, 0.2f, 1.0f);"
			"   vec3 ambient = uAmbient.color * uAmbient.intensity * outColor.xyz;"
			"   vec3 light = vec3(0,0,0);"
			"   for (int i = 0; i < uLightCount; ++i)"
			"   {"
			"       vec2 translated = uLights[i].position - _position;"
			"       float distance = sqrt(translated.x * translated.x + translated.y * translated.y);"
			"       light += outColor.xyz * uLights[i].color / distance * uLights[i].decay;"
			"   }"
			"   _color = vec4(ambient + light, 1.0);"
			"}";

		

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar log[512];
			glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
			std::cerr << log << std::endl;
		}

		_program = glCreateProgram();
		glAttachShader(_program, vertexShader);
		glAttachShader(_program, fragmentShader);
		glLinkProgram(_program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		_offset = glGetUniformLocation(_program, "uOffset");
		_lightCount = glGetUniformLocation(_program, "uLightCount");
		_projection = glGetUniformLocation(_program, "uProjection");

		for (int i = 0; i < 16; ++i)
		{
			auto index = std::string("uLights[") + std::to_string(i) + std::string("]");
			_light.Position[i] = glGetUniformLocation(_program, std::string(index + ".position").c_str());
			_light.Color[i] = glGetUniformLocation(_program, std::string(index + ".color").c_str());
			_light.Decay[i] = glGetUniformLocation(_program, std::string(index + ".decay").c_str());
		}

		_ambient.Color = glGetUniformLocation(_program, "uAmbient.color");
		_ambient.Intensity = glGetUniformLocation(_program, "uAmbient.intensity");

	}

	Basic2DShader &Basic2DShader::Get()
	{
		static Basic2DShader shader;
		return shader;
	}
}
