//
//  drawingUtilities.h.h
//  Version1
//
//  Created by Jean-Yves Hervé on 2023-10-30.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include "glPlatform.h"

//	Rendering modes
//
enum class RenderingMode
{
		WireframeRender,
		FlatShadingRender,
		SmoothShadingRender
};

union Material
{
	GLfloat aMaterial[17];

	struct sMaterial{
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat emission[4];
		GLfloat shiny;
	};
	
};

void setCurrentMaterial(GLfloat ambRed, GLfloat ambGreen, GLfloat ambBlue, GLfloat difRed,
	GLfloat difGreen, GLfloat difBlue, GLfloat specRed, GLfloat specGreen,
	GLfloat specBlue, GLfloat shine);
void setCurrentMaterial(const Material& mat);

//void saveAndSetMaterial(Material& currentMat, const Material& newMat);

void updateRenderingMode(RenderingMode renderingMode);

void drawReferenceFrame(void);

#endif //	UTILITIES_H
