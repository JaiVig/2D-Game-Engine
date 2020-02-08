#pragma once
#include<GL/glew.h>
#include"Vertex.h"
#include<glm/glm.hpp>
#include<vector>
namespace Crusty {

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};
struct Glyph {
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};

class RenderBatch {
public:
	RenderBatch(GLuint _offset,
				GLuint _numVertices,
				GLuint _Texture) :offset(_offset),
								  numVertices(_numVertices),
								  Texture(_Texture)
	{}

	GLuint offset;
	GLuint numVertices;
	GLuint Texture;
};


class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();
	void init();
	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect,const glm::vec4& uvRect,const GLuint& texture,const float& depth,const ColorRGBA8& color);
	void renderBatch();
private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);


	GLuint _vbo;
	GLuint _vao;
	GlyphSortType _sortType;
	std::vector<Glyph*> _glyphs;
	std::vector<RenderBatch> _renderBatches;
};

}

