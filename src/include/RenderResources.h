#ifndef CLASS_NCINE_RENDERRESOURCES
#define CLASS_NCINE_RENDERRESOURCES

#include "GLBufferObject.h"
#include "GLShaderProgram.h"

namespace ncine {

/// The class creating and handling common OpenGL rendering resources
class RenderResources
{
  public:
	typedef struct
	{
		GLfloat position[2];
	} VertexFormatPos2;

	typedef struct
	{
		GLfloat position[2];
		GLfloat texcoords[2];
	} VertexFormatPos2Tex2;

	static inline const GLBufferObject* quadVbo() { return quadVbo_; }
	static inline const GLShaderProgram* spriteShaderProgram() { return spriteShaderProgram_; }
	static inline const GLShaderProgram* textnodeShaderProgram() { return textnodeShaderProgram_; }
	static inline const GLShaderProgram* colorShaderProgram() { return colorShaderProgram_; }

  private:
	static GLBufferObject *quadVbo_;
	static GLShaderProgram *spriteShaderProgram_;
	static GLShaderProgram *textnodeShaderProgram_;
	static GLShaderProgram *colorShaderProgram_;

	static void create();
	static void dispose();

	/// Static class, no constructor
	RenderResources();
	/// Static class, no copy constructor
	RenderResources(const RenderResources& other);
	/// Static class, no assignement operator
	RenderResources& operator=(const RenderResources& other);

	// The Application class needs to create and dispose the resources
	friend class Application;
};

}

#endif