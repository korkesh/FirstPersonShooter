//
//  shadowMapping.h
//  opengl-series
//
//  Created by Matthew Correia on 2014-07-17.
//
//

#ifndef __opengl_series__shadowMapping__
#define __opengl_series__shadowMapping__

// Expressed as float so gluPerspective division returns a float and not 0 (640/480 != 640.0/480.0).
#define RENDER_WIDTH 1024
#define RENDER_HEIGHT 768
#define SHADOW_MAP_RATIO 2

extern GLuint fboId;
extern GLuint depthTextureId;
extern GLhandleARB shadowShaderId;
extern GLuint shadowMapUniform;

void generateShadowFBO();
void loadShadowShader();

#endif /* defined(__opengl_series__shadowMapping__) */
