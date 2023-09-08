#include <string>
#include <utility>	
#include <vector>
#include <GL/glew.h>

class VertexArray {
private:
	float* _vertices;
	unsigned int* _vertexBufferObj;
	unsigned int* _vertexArrayObj;
	std::vector<std::pair<std::string, int>> _attribs;
public:
	VertexArray(float vertices[], unsigned int* vertexArrayObj, unsigned int* vertexBufferObj, std::vector<std::pair<std::string, int>> attribs);
	~VertexArray();
	void bind();
	void draw(unsigned int mode);
};


VertexArray::VertexArray(float vertices[], unsigned int* vertexArrayObj, unsigned int* vertexBufferObj, std::vector<std::pair<std::string, int>> attribs) {
	_vertices = vertices;
	_vertexBufferObj = vertexBufferObj;
	_vertexArrayObj = vertexArrayObj;
	_attribs = attribs;

	glGenBuffers(1, _vertexBufferObj);
	glGenVertexArrays(1, _vertexArrayObj);
}

void VertexArray::bind() {
	// bind vertex array object and vertex buffer to that vertex array object
	glBindVertexArray(*_vertexArrayObj);
	glBindBuffer(GL_ARRAY_BUFFER, *_vertexBufferObj);
	// bind data to vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
	// bind attribs to that buffer data

	int index = 0;
	for (auto attrib : _attribs) {
		glVertexAttribPointer(index, attrib.second, GL_FLOAT, GL_FALSE, attrib.second * sizeof(float), (void*)0);
		glEnableVertexAttribArray(index);
		index++;
	}
}

void VertexArray::draw(unsigned int mode) {
	glBindVertexArray(*_vertexArrayObj);
	switch (mode) {
	case GL_TRIANGLES:
		glDrawArrays(GL_TRIANGLES, 0, 3);
		break;
	}
}

VertexArray::~VertexArray() {
	delete _vertices;
	delete _vertexBufferObj;
	delete _vertexArrayObj;
}
