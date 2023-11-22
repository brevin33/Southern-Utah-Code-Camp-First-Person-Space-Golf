#include "mesh.h"
#include <map>
#include <vector>



struct Triangle
{
	uint32_t vertex[3];
};

struct v3
{
	float pos[3];
};

v3 normalize(v3 v) {
	float magnitude = glm::sqrt(v.pos[0] * v.pos[0] + v.pos[1] * v.pos[1] + v.pos[2] * v.pos[2]);
	v.pos[0] = v.pos[0] / magnitude;
	v.pos[1] = v.pos[1] / magnitude;
	v.pos[2] = v.pos[2] / magnitude;
	return v;
}

v3 add(v3 first, v3 second) {
	first.pos[0] += second.pos[0];
	first.pos[1] += second.pos[1];
	first.pos[2] += second.pos[2];
	return first;
}

using TriangleList = std::vector<Triangle>;
using VertexList = std::vector<v3>;
using Lookup = std::map<std::pair<uint32_t, uint32_t>, uint32_t>;

namespace icosahedron
{
	const float X = .525731112119133606f;
	const float Z = .850650808352039932f;
	const float N = 0.f;

	static const VertexList vertices =
	{
	  {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
	  {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
	  {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
	};

	static const TriangleList triangles =
	{
	  {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
	  {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
	  {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
	  {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
	};
}

uint32_t vertex_for_edge(Lookup& lookup,
	VertexList& vertices, uint32_t first, uint32_t second)
{
	Lookup::key_type key(first, second);
	if (key.first > key.second)
		std::swap(key.first, key.second);

	auto inserted = lookup.insert({ key, vertices.size() });
	if (inserted.second)
	{
		auto& edge0 = vertices[first];
		auto& edge1 = vertices[second];
		auto point = normalize(add(edge0, edge1));
		vertices.push_back(point);
	}

	return inserted.first->second;
}

TriangleList subdivide(VertexList& vertices,
	TriangleList triangles)
{
	Lookup lookup;
	TriangleList result;

	for (auto&& each : triangles)
	{
		std::array<uint32_t, 3> mid;
		for (int edge = 0; edge < 3; ++edge)
		{
			mid[edge] = vertex_for_edge(lookup, vertices,
				each.vertex[edge], each.vertex[(edge + 1) % 3]);
		}

		result.push_back({ each.vertex[0], mid[0], mid[2] });
		result.push_back({ each.vertex[1], mid[1], mid[0] });
		result.push_back({ each.vertex[2], mid[2], mid[1] });
		result.push_back({ mid[0], mid[1], mid[2] });
	}

	return result;
}

using IndexedMesh = std::pair<VertexList, TriangleList>;

IndexedMesh make_icosphere(int subdivisions)
{
	VertexList vertices = icosahedron::vertices;
	TriangleList triangles = icosahedron::triangles;

	for (int i = 0; i < subdivisions; ++i)
	{
		triangles = subdivide(vertices, triangles);
	}

	return{ vertices, triangles };
}

void Mesh::makeCircle(int subdivisions)
{
	vertices.clear();
	indices.clear();
	IndexedMesh circlePosAndIndies = make_icosphere(subdivisions);
	for (size_t i = 0; i < circlePosAndIndies.first.size(); i++)
	{
		Vertex vertex;
		v3 v = circlePosAndIndies.first[i];
		vertex.pos = glm::vec3(v.pos[0], v.pos[1], v.pos[2]);
		vertices.push_back(vertex);
	}

	for (size_t i = 0; i < circlePosAndIndies.second.size(); i++)
	{
		uint32_t i1 = circlePosAndIndies.second[i].vertex[0];
		uint32_t i2 = circlePosAndIndies.second[i].vertex[1];
		uint32_t i3 = circlePosAndIndies.second[i].vertex[2];
		indices.push_back(i1);
		indices.push_back(i2);
		indices.push_back(i3);
	}
}
