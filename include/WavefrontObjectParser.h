
#ifndef WAVEFRONT_OBJECT_PARSER_H
#define WAVEFRONT_OBJECT_PARSER_H

#include <sstream>
#include <string_view>
#include <deque>
#include <vector>
#include <string>

#include "WavefrontObject.h"

using Float3 = std::tuple<float, float, float>;
using Float2 = std::pair<float, float>;

class WfParser
{
private:
	WfParser() = delete;
	WfParser(WfParser const&) = delete;
	WfParser& operator=(WfParser const&) = delete;

	static std::string curObjName;
	static std::deque<Float3> vtxPosBuffer;
	static std::deque<Float3> vtxNormBuffer;
	static std::deque<Float2> txtPosBuffer;
	static std::deque<Vertex> faceVertexBuffer;

	static void evalVertexPos(std::string const& line);
	static void evalVertexNormal(std::string const& line);
	static void evalVertexTexture(std::string const& line);
	static void evalFace(std::string const& line);
	static void evalGroup(std::string const& line);

public:
	static std::deque<WfObj*> parse(std::string_view fileName, std::stringstream& ss);
};

#endif
