#include <GLee.h>
#include <boost/format.hpp>

#include "../kazbase/logging.h"
#include "../kazbase/exceptions.h"

void check_and_log_error(std::string file, int lineno) {
    GLuint error = glGetError();
    if(error != GL_NO_ERROR) {
        L_ERROR((boost::format("An OpenGL error occurred: %s:%d - %d") % file % lineno % error).str());
        throw RuntimeError("GL ERROR");
    }
}

