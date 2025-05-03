
#include "WavefrontObjectParser.h"
#include <tuple>

std::string WfParser::curObjName;
std::deque<Float3> WfParser::vtxPosBuffer;
std::deque<Float3> WfParser::vtxNormBuffer;
std::deque<Float2> WfParser::txtPosBuffer;
std::deque<Vertex> WfParser::faceVertexBuffer;

void WfParser::evalVertexPos(std::string const& line)
{
	std::stringstream ss(line);
	Float3 result;
	char c;

	auto& [x, y, z] = result;
	if (!(ss >> c >> x >> y >> z))
		return;
	vtxPosBuffer.push_back(result);
}

void WfParser::evalVertexNormal(std::string const& line)
{
	std::stringstream ss(line);
	Float3 result;
	char c;

	auto& [x, y, z] = result;
	if (!(ss >> c >> c >> x >> y >> z))
		return;
	vtxNormBuffer.push_back(result);
}

void WfParser::evalVertexTexture(std::string const& line)
{
	std::stringstream ss(line);
	Float2 result;
	char c;

	auto& [x, y] = result;
	if (!(ss >> c >> c >> x >> y))
		return;
	txtPosBuffer.push_back(result);
}

void WfParser::evalFace(std::string const& line)	// parse "f i/i/i i/i/i i/i/i"
{
	std::stringstream ss(line);
	std::array<int, 3> pIdx;
	std::deque<Vertex> tempVertexBuffer;
	char c;

	ss >> c;
	while (true)
	{
		std::fill(pIdx.begin(), pIdx.end(), 0);
		tempVertexBuffer.push_back({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });

		// parse and get index of content
		if (!(ss >> pIdx[0]))
			return;
		if (!(isspace(ss.peek()) || ss.eof()))	// next is not space
		{
			if (!(ss >> c && c == '/'))	// delimeter check, must be '/'
				return;
			if (!(ss >> pIdx[1]))	// value check
				return;
			if (!(isspace(ss.peek() || ss.eof())))
			{
				if (!(ss >> c && c == '/'))	// delimeter check, must be '/'
					return;
				if (!(ss >> pIdx[2]))	// value check
					return;
			}
		}

		// index convesion, relative 1-based index to 0 based absolute index
		for (int j = 0; j < 3; ++j)
		{
			if (pIdx[j] < 0)
			{
				if (j == 0)
					pIdx[j] = vtxPosBuffer.size() + pIdx[j];
				else if (j == 1)
					pIdx[j] = vtxNormBuffer.size() + pIdx[j];
				else if (j == 2)
					pIdx[j] = txtPosBuffer.size() + pIdx[j];
			}
			else
			{
				--pIdx[j];
			}
		}

		// index range check
		if (pIdx[0] >= static_cast<int>(vtxPosBuffer.size())
			|| pIdx[1] >= static_cast<int>(txtPosBuffer.size())
			|| pIdx[2] >= static_cast<int>(vtxNormBuffer.size()))
			return;

		// create result
		if (pIdx[0] >= 0)
		{
			auto const [x, y, z] = vtxPosBuffer[pIdx[0]];
			tempVertexBuffer.back().px = x;
			tempVertexBuffer.back().py = y;
			tempVertexBuffer.back().pz = z;
		}
		else	// necessary
		{
			return;
		}

		if (pIdx[1] >= 0)
		{
			auto const [x, y] = txtPosBuffer[pIdx[1]];
			tempVertexBuffer.back().tx = x;
			tempVertexBuffer.back().ty = y;
		}
		if (pIdx[2] >= 0)
		{
			auto const [x, y, z] = vtxNormBuffer[pIdx[2]];
			tempVertexBuffer.back().vnx = x;
			tempVertexBuffer.back().vny = y;
			tempVertexBuffer.back().vnz = z;
		}

		if (ss.eof())
			break;
	}

	for (size_t i = 2; i < tempVertexBuffer.size(); ++i)
	{
		faceVertexBuffer.push_back(tempVertexBuffer[0]);
		faceVertexBuffer.push_back(tempVertexBuffer[i - 1]);
		faceVertexBuffer.push_back(tempVertexBuffer[i]);
	}
}

void WfParser::evalGroup(std::string const& line)
{
	std::stringstream ss(line);
	std::string name;
	char c;

	ss >> c >> name;
	curObjName = name;
}

void clearBuffers(
	std::deque<Float3>& v,
	std::deque<Float2>& vt,
	std::deque<Float3>& vn,
	std::deque<Vertex>& vf)
{
	v.clear();
	vt.clear();
	vn.clear();
	vf.clear();
}

std::deque<WfObj*> WfParser::parse(std::string_view fileName, std::stringstream& ss)
{
	std::deque<WfObj*> result;
	std::string lineBuffer;

	curObjName = fileName;
	while (std::getline(ss, lineBuffer))
	{
		// match statement
		if (std::string_view(lineBuffer.data(), 2) == "vn")
		{
			evalVertexNormal(lineBuffer);
		}
		else if (std::string_view(lineBuffer.data(), 2) == "vt")
		{
			evalVertexTexture(lineBuffer);
		}
		else if (lineBuffer.front() == 'v')
		{
			evalVertexPos(lineBuffer);
		}
		else if (lineBuffer.front() == 'f')
		{
			evalFace(lineBuffer);
		}
		else if (lineBuffer.front() == 'g' || lineBuffer.front() == 'o')
		{
			if (!faceVertexBuffer.empty())
			{
				result.push_back(new WfObj(curObjName, faceVertexBuffer));
			}
			evalGroup(lineBuffer);
			curObjName = std::string(fileName) + "_" + curObjName;
		}
		else	// including comment, skip the whole line
		{
			continue;
		}
	}

	// add single object
	if (!faceVertexBuffer.empty())
	{
		result.push_back(new WfObj(curObjName, faceVertexBuffer));
		clearBuffers(vtxPosBuffer, txtPosBuffer, vtxNormBuffer, faceVertexBuffer);
	}
	return result;
}
