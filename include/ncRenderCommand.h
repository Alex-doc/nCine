#ifndef CLASS_NCRENDERCOMMAND
#define CLASS_NCRENDERCOMMAND

#if defined(__ANDROID__)
	#include <GLES/gl.h>
	#include <GLES/glext.h>
#elif !defined(NO_GLEW)
	#include <GL/glew.h>
#else
	#include <GL/gl.h>
	#include <GL/glext.h>
#endif

#include "ncPoint.h"
#include "ncList.h"

class ncRenderMaterial
{
private:
	GLfloat m_fColor[4];
	GLuint m_uTextureGLId;

public:
	ncRenderMaterial(GLfloat fColor[4], GLuint uTextureGLId)
		: m_uTextureGLId(uTextureGLId)
	{
		m_fColor[0] = fColor[0];	m_fColor[1] = fColor[1];
		m_fColor[2] = fColor[2];	m_fColor[3] = fColor[3];
	}
	ncRenderMaterial(GLuint uTextureGLId) : m_uTextureGLId(uTextureGLId)
	{
		m_fColor[0] = 1.0f;		m_fColor[1] = 1.0f;
		m_fColor[2] = 1.0f;		m_fColor[3] = 1.0f;
	}
	ncRenderMaterial() : m_uTextureGLId(0)
	{
		m_fColor[0] = 1.0f;		m_fColor[1] = 1.0f;
		m_fColor[2] = 1.0f;		m_fColor[3] = 1.0f;
	}

	void SetColor(GLfloat fR, GLfloat fG, GLfloat fB, GLfloat fA)
	{
		m_fColor[0] = fR;	m_fColor[1] = fG;
		m_fColor[2] = fB;	m_fColor[3] = fA;
	}

	void SetColor(GLfloat fColor[4])
	{
		m_fColor[0] = fColor[0];	m_fColor[1] = fColor[1];
		m_fColor[2] = fColor[2];	m_fColor[3] = fColor[3];
	}

	inline GLuint TextureGLId() const { return m_uTextureGLId; }
	inline void SetTextureGLId(GLuint uTextureGLId) { m_uTextureGLId = uTextureGLId; }

	void Bind() const;
};

class ncRenderTransformation
{
private:
	float m_fScaleX;
	float m_fScaleY;
	ncPoint m_position;

public:
	ncRenderTransformation() : m_fScaleX(1.0f), m_fScaleY(1.0f), m_position(0, 0) { }

	ncRenderTransformation(const ncPoint& position)
		: m_fScaleX(1.0f), m_fScaleY(1.0f), m_position(position) { }

	void SetScale(float fScaleX, float fScaleY)
	{
		m_fScaleX = fScaleX;	m_fScaleY = fScaleY;
	}

	void SetPosition(const ncPoint& pos)
	{
		m_position = pos;
	}

	void Apply() const;
};

class ncRenderGeometry
{
protected:
	GLenum m_eDrawType;
	GLint m_iFirstVertex;
	GLsizei m_iNumVertices;
	GLfloat *m_fVertices;
	GLfloat *m_fTexCoords;

public:
	ncRenderGeometry(GLenum eDrawType, GLint iFirstVertex, GLsizei iNumVertices, GLfloat *fVertices, GLfloat *fTexCoords)
		: m_eDrawType(eDrawType),
		  m_iFirstVertex(iFirstVertex), m_iNumVertices(iNumVertices),
		  m_fVertices(fVertices), m_fTexCoords(fTexCoords) { }
	ncRenderGeometry(GLsizei iNumVertices, GLfloat *fVertices, GLfloat *fTexCoords)
		: m_eDrawType(GL_TRIANGLES),
		  m_iFirstVertex(0), m_iNumVertices(iNumVertices),
		  m_fVertices(fVertices), m_fTexCoords(fTexCoords) { }
	ncRenderGeometry()
		: m_eDrawType(GL_TRIANGLES),
		  m_iFirstVertex(0), m_iNumVertices(0),
		  m_fVertices(NULL), m_fTexCoords(NULL) { }

	void SetData(GLenum eDrawType, GLint iFirstVertex, GLsizei iNumVertices, GLfloat *fVertices, GLfloat *fTexCoords)
	{
		m_eDrawType = eDrawType;
		m_iFirstVertex = iFirstVertex;
		m_iNumVertices = iNumVertices;
		m_fVertices = fVertices;
		m_fTexCoords = fTexCoords;
	}

	void Draw() const;
};

/*
class ncQuadNode : public ncGeometricNode
{
private:
	GLfloat m_fQVertices[12];
	GLfloat m_fQTexCoords[12];

public:
	ncQuadNode() : ncGeometricNode(6, m_fQVertices, m_fQTexCoords)
	{
		m_fQVertices[0] = 0.0f;		m_fQVertices[1] = 0.0f;
		m_fQVertices[2] = 0.0f;		m_fQVertices[3] = 100.0f;
		m_fQVertices[4] = 100.0f;		m_fQVertices[5] = 100.0f;

		m_fQVertices[6] = 100.0f;		m_fQVertices[7] = 100.0f;
		m_fQVertices[8] = 100.0f;		m_fQVertices[9] = 0.0f;
		m_fQVertices[10] = 0.0f;	m_fQVertices[11] = 0.0f;


		m_fQTexCoords[0] = 0.0f;	m_fQTexCoords[1] = 1.0f;
		m_fQTexCoords[2] = 0.0f;	m_fQTexCoords[3] = 0.0f;
		m_fQTexCoords[4] = 1.0f;	m_fQTexCoords[5] = 0.0f;

		m_fQTexCoords[6] = 1.0f;	m_fQTexCoords[7] = 0.0f;
		m_fQTexCoords[8] = 1.0f;	m_fQTexCoords[9] = 1.0f;
		m_fQTexCoords[10] = 0.0f;	m_fQTexCoords[11] = 1.0f;
	}

	virtual void IssueCommand() { ncGeometricNode::IssueCommand(); }
};
*/

/// The class wrapping all the information needed for issueing a draw command
class ncRenderCommand
{
private:
	unsigned long int m_uSortKey;
//	bool m_bDirtyKey;

	int m_iPriority;
	ncRenderMaterial m_material;
	ncRenderTransformation m_transformation;
	ncRenderGeometry m_geometry;

public:
	inline int Priority() const { return m_iPriority; }
	inline void SetPriority(int iPriority) { m_iPriority = iPriority; }
	inline const ncRenderMaterial& Material() const { return m_material; }
	inline ncRenderMaterial& Material() { return m_material; }
	inline const ncRenderTransformation& Transformation() const { return m_transformation; }
	inline ncRenderTransformation& Transformation() { return m_transformation; }
	inline const ncRenderGeometry& Geometry() const { return m_geometry; }
	inline ncRenderGeometry& Geometry() { return m_geometry; }

	inline unsigned long int SortKey() const { return m_uSortKey; }
	void CalculateSortKey();
	void Issue() const;
};

#endif
