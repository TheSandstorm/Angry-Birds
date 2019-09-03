#pragma once
#include <string>
#include <vector>
#include <glm.hpp>

namespace Utility
{
	const unsigned int SCR_WIDTH = 1600;
	const unsigned int SCR_HEIGHT = 800;
	const std::string SingleColorShaderFrag = "Resources/Shaders/SingleColorShader.fs";
	const std::string FogShaderVert = "Resources/Shaders/FogObjectShader.vs";
	const std::string FogShaderFrag = "Resources/Shaders/FogObjectShader.fs";
	const std::string ModelFogShaderVert = "Resources/Shaders/FogModel.vs";
	const std::string ModelFogShaderFrag = "Resources/Shaders/FogModel.fs";
	const std::string ObjectShaderVert = "Resources/Shaders/ObjectShaderV.vs";
	const std::string ObjectShaderFrag = "Resources/Shaders/ObjectShaderF.fs";
	const std::string ModelShaderVert = "Resources/Shaders/Model.vs";
	const std::string ModelShaderFrag = "Resources/Shaders/Model.fs";
	const std::string CubeMapShaderFrag = "Resources/Shaders/CubeShader.fs";
	const std::string CubeMapShaderVert = "Resources/Shaders/CubeShader.vs";
	const std::string FogCubeMapShaderVert = "Resources/Shaders/FogCubeShader.vs";
	const std::string FogCubeMapShaderFrag = "Resources/Shaders/FogCubeShader.fs";
	const std::string TessShaderVert = "Resources/Shaders/TessShader.vs";
	const std::string TessShaderTCSQuad = "Resources/Shaders/TessShaderQuad.tcs";
	const std::string TessShaderTESQuad = "Resources/Shaders/TessShaderQuad.tes";
	const std::string TessShaderTCSTri = "Resources/Shaders/TessShaderTri.tcs";
	const std::string TessShaderTESTri = "Resources/Shaders/TessShaderTri.tes";
	const std::string TessShaderFrag = "Resources/Shaders/TessShader.fs";
	const std::string GeometryShaderVert = "Resources/Shaders/GeometryShader.vs";
	const std::string GeometryShaderGeom = "Resources/Shaders/GeometryShader.gs";
	const std::string TextShaderVert = "Resources/Shaders/Text.vs";
	const std::string TextShaderFrag = "Resources/Shaders/Text.fs";

	const std::string PlayerModel = "Resources/Models/Tank/Tank.obj";
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
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	inline Transform(glm::vec3 _Position, glm::vec3 _Rotation, glm::vec3 _Scale)
	{
		Position = _Position;
		Rotation = _Rotation;
		Scale = _Scale;
	}
};