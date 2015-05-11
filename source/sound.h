//
//  sound.h
//

#ifndef __openGLTutorial__sound__
#define __openGLTutorial__sound__

#include <iostream>

bool loadWavFile(const std::string filename, ALuint* buffer,
                 ALsizei* size, ALsizei* frequency,
                 ALenum* format);

#endif /* defined(__openGLTutorial__sound__) */
