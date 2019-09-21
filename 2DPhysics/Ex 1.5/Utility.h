#pragma once
#include <Box2D/Box2D.h>
#include <string>
#include <vector>
#include <glm.hpp>
#include <math.h>

#define PI 3.141592653589793238462643383279502884f

namespace Utility
{
	const unsigned int SCR_WIDTH = 1600;
	const unsigned int SCR_HEIGHT = 800;
	const unsigned int Ratio = 120;
	const b2Vec2 Gravity(0.0f, -9.8f);
	const std::string SingleColorShaderFrag = "Resources/Shaders/SingleColorShader.fs";
	const std::string FogShaderVert = "Resources/Shaders/FogObjectShader.vs";
	const std::string FogShaderFrag = "Resources/Shaders/FogObjectShader.fs";
	const std::string ObjectShaderVert = "Resources/Shaders/ObjectShaderV.vs";
	const std::string ObjectShaderFrag = "Resources/Shaders/ObjectShaderF.fs";
	const std::string CubeMapShaderFrag = "Resources/Shaders/CubeShader.fs";
	const std::string CubeMapShaderVert = "Resources/Shaders/CubeShader.vs";
	const std::string FogCubeMapShaderVert = "Resources/Shaders/FogCubeShader.vs";
	const std::string FogCubeMapShaderFrag = "Resources/Shaders/FogCubeShader.fs";
	const std::string TextShaderVert = "Resources/Shaders/Text.vs";
	const std::string TextShaderFrag = "Resources/Shaders/Text.fs";
};

namespace TexturePaths
{
	const std::string CubeMapTexture = "Resources/Textures/CubeMap/";
	const std::string WaterTexture = "Resources/Textures/Water.png";
	const std::string BlueSquareTexture = "Resources/Textures/Bluesquare.png";
	const std::string TestTexture = "Resources/Textures/desert.jpg";
}

namespace SoundnFonts
{
	const std::string NormalFontString = "Resources/Fonts/arial.ttf";
	const std::string GameOver = "Resources/Audio/Game_over_music.wav";
	const std::string BackgroundMusic = "Resources/Audio/CrabRave.wav";
	const std::string MenuMusic = "Resources/Audio/Menu_music.wav";
}

namespace ScreenInfo
{
	const unsigned int SCR_WIDTH = 1600;
	const unsigned int SCR_HEIGHT = 800;
};

struct Transform
{
	b2Vec2 Position;
	float Rotation;
	b2Vec2 Scale;

	Transform()
	{

	}

	inline Transform(b2Vec2 _Position, float _Rotation, b2Vec2 _Scale)
	{
		Position = _Position;
		Rotation = _Rotation;
		Scale = _Scale;
	}
};