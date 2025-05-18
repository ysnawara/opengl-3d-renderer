#include <glad/glad.h>
#include <stddef.h>

/* GL 1.0 / 1.1 */
PFNGLVIEWPORTPROC        glad_glViewport        = NULL;
PFNGLCLEARPROC           glad_glClear           = NULL;
PFNGLCLEARCOLORPROC      glad_glClearColor      = NULL;
PFNGLENABLEPROC          glad_glEnable          = NULL;
PFNGLDISABLEPROC         glad_glDisable         = NULL;
PFNGLDEPTHFUNCPROC       glad_glDepthFunc       = NULL;
PFNGLBLENDFUNCPROC       glad_glBlendFunc       = NULL;
PFNGLCULLFACEPROC        glad_glCullFace        = NULL;
PFNGLFRONTFACEPROC       glad_glFrontFace       = NULL;
PFNGLPOLYGONMODEPROC     glad_glPolygonMode     = NULL;
PFNGLPIXELSTOREIPROC     glad_glPixelStorei     = NULL;
PFNGLTEXIMAGE2DPROC      glad_glTexImage2D      = NULL;
PFNGLTEXSUBIMAGE2DPROC   glad_glTexSubImage2D   = NULL;
PFNGLTEXPARAMETERIPROC   glad_glTexParameteri   = NULL;
PFNGLDRAWARRAYSPROC      glad_glDrawArrays      = NULL;
PFNGLDRAWELEMENTSPROC    glad_glDrawElements    = NULL;
PFNGLGENTEXTURESPROC     glad_glGenTextures     = NULL;
PFNGLDELETETEXTURESPROC  glad_glDeleteTextures  = NULL;
PFNGLBINDTEXTUREPROC     glad_glBindTexture     = NULL;
PFNGLGETERRORPROC        glad_glGetError        = NULL;
PFNGLGETSTRINGPROC       glad_glGetString       = NULL;
PFNGLGETINTEGERVPROC     glad_glGetIntegerv     = NULL;

/* GL 1.3 */
PFNGLACTIVETEXTUREPROC   glad_glActiveTexture   = NULL;

/* GL 1.5 */
PFNGLGENBUFFERSPROC      glad_glGenBuffers      = NULL;
PFNGLDELETEBUFFERSPROC   glad_glDeleteBuffers   = NULL;
PFNGLBINDBUFFERPROC      glad_glBindBuffer      = NULL;
PFNGLBUFFERDATAPROC      glad_glBufferData      = NULL;
PFNGLBUFFERSUBDATAPROC   glad_glBufferSubData   = NULL;

/* GL 2.0 */
PFNGLCREATESHADERPROC             glad_glCreateShader             = NULL;
PFNGLDELETESHADERPROC             glad_glDeleteShader             = NULL;
PFNGLSHADERSOURCEPROC             glad_glShaderSource             = NULL;
PFNGLCOMPILESHADERPROC            glad_glCompileShader            = NULL;
PFNGLGETSHADERIVPROC              glad_glGetShaderiv              = NULL;
PFNGLGETSHADERINFOLOGPROC         glad_glGetShaderInfoLog         = NULL;
PFNGLCREATEPROGRAMPROC            glad_glCreateProgram            = NULL;
PFNGLDELETEPROGRAMPROC            glad_glDeleteProgram            = NULL;
PFNGLATTACHSHADERPROC             glad_glAttachShader             = NULL;
PFNGLLINKPROGRAMPROC              glad_glLinkProgram              = NULL;
PFNGLVALIDATEPROGRAMPROC          glad_glValidateProgram          = NULL;
PFNGLGETPROGRAMIVPROC             glad_glGetProgramiv             = NULL;
PFNGLGETPROGRAMINFOLOGPROC        glad_glGetProgramInfoLog        = NULL;
PFNGLUSEPROGRAMPROC               glad_glUseProgram               = NULL;
PFNGLGETUNIFORMLOCATIONPROC       glad_glGetUniformLocation       = NULL;
PFNGLUNIFORM1IPROC               glad_glUniform1i               = NULL;
PFNGLUNIFORM1FPROC               glad_glUniform1f               = NULL;
PFNGLUNIFORM3FPROC               glad_glUniform3f               = NULL;
PFNGLUNIFORM3FVPROC              glad_glUniform3fv              = NULL;
PFNGLUNIFORM4FPROC               glad_glUniform4f               = NULL;
PFNGLUNIFORMMATRIX4FVPROC        glad_glUniformMatrix4fv        = NULL;
PFNGLVERTEXATTRIBPOINTERPROC     glad_glVertexAttribPointer     = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glad_glEnableVertexAttribArray  = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray = NULL;
PFNGLGETATTRIBLOCATIONPROC        glad_glGetAttribLocation        = NULL;

/* GL 3.0 */
PFNGLGENVERTEXARRAYSPROC    glad_glGenVertexArrays    = NULL;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC    glad_glBindVertexArray    = NULL;
PFNGLGENERATEMIPMAPPROC     glad_glGenerateMipmap     = NULL;

int gladLoadGL(GLADloadproc load) {
    if (!load) return 0;

    /* GL 1.0 / 1.1 */
    glad_glViewport       = (PFNGLVIEWPORTPROC)load("glViewport");
    glad_glClear          = (PFNGLCLEARPROC)load("glClear");
    glad_glClearColor     = (PFNGLCLEARCOLORPROC)load("glClearColor");
    glad_glEnable         = (PFNGLENABLEPROC)load("glEnable");
    glad_glDisable        = (PFNGLDISABLEPROC)load("glDisable");
    glad_glDepthFunc      = (PFNGLDEPTHFUNCPROC)load("glDepthFunc");
    glad_glBlendFunc      = (PFNGLBLENDFUNCPROC)load("glBlendFunc");
    glad_glCullFace       = (PFNGLCULLFACEPROC)load("glCullFace");
    glad_glFrontFace      = (PFNGLFRONTFACEPROC)load("glFrontFace");
    glad_glPolygonMode    = (PFNGLPOLYGONMODEPROC)load("glPolygonMode");
    glad_glPixelStorei    = (PFNGLPIXELSTOREIPROC)load("glPixelStorei");
    glad_glTexImage2D     = (PFNGLTEXIMAGE2DPROC)load("glTexImage2D");
    glad_glTexSubImage2D  = (PFNGLTEXSUBIMAGE2DPROC)load("glTexSubImage2D");
    glad_glTexParameteri  = (PFNGLTEXPARAMETERIPROC)load("glTexParameteri");
    glad_glDrawArrays     = (PFNGLDRAWARRAYSPROC)load("glDrawArrays");
    glad_glDrawElements   = (PFNGLDRAWELEMENTSPROC)load("glDrawElements");
    glad_glGenTextures    = (PFNGLGENTEXTURESPROC)load("glGenTextures");
    glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC)load("glDeleteTextures");
    glad_glBindTexture    = (PFNGLBINDTEXTUREPROC)load("glBindTexture");
    glad_glGetError       = (PFNGLGETERRORPROC)load("glGetError");
    glad_glGetString      = (PFNGLGETSTRINGPROC)load("glGetString");
    glad_glGetIntegerv    = (PFNGLGETINTEGERVPROC)load("glGetIntegerv");

    /* GL 1.3 */
    glad_glActiveTexture  = (PFNGLACTIVETEXTUREPROC)load("glActiveTexture");

    /* GL 1.5 */
    glad_glGenBuffers     = (PFNGLGENBUFFERSPROC)load("glGenBuffers");
    glad_glDeleteBuffers  = (PFNGLDELETEBUFFERSPROC)load("glDeleteBuffers");
    glad_glBindBuffer     = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
    glad_glBufferData     = (PFNGLBUFFERDATAPROC)load("glBufferData");
    glad_glBufferSubData  = (PFNGLBUFFERSUBDATAPROC)load("glBufferSubData");

    /* GL 2.0 */
    glad_glCreateShader             = (PFNGLCREATESHADERPROC)load("glCreateShader");
    glad_glDeleteShader             = (PFNGLDELETESHADERPROC)load("glDeleteShader");
    glad_glShaderSource             = (PFNGLSHADERSOURCEPROC)load("glShaderSource");
    glad_glCompileShader            = (PFNGLCOMPILESHADERPROC)load("glCompileShader");
    glad_glGetShaderiv              = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
    glad_glGetShaderInfoLog         = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog");
    glad_glCreateProgram            = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram");
    glad_glDeleteProgram            = (PFNGLDELETEPROGRAMPROC)load("glDeleteProgram");
    glad_glAttachShader             = (PFNGLATTACHSHADERPROC)load("glAttachShader");
    glad_glLinkProgram              = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
    glad_glValidateProgram          = (PFNGLVALIDATEPROGRAMPROC)load("glValidateProgram");
    glad_glGetProgramiv             = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv");
    glad_glGetProgramInfoLog        = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetProgramInfoLog");
    glad_glUseProgram               = (PFNGLUSEPROGRAMPROC)load("glUseProgram");
    glad_glGetUniformLocation       = (PFNGLGETUNIFORMLOCATIONPROC)load("glGetUniformLocation");
    glad_glUniform1i               = (PFNGLUNIFORM1IPROC)load("glUniform1i");
    glad_glUniform1f               = (PFNGLUNIFORM1FPROC)load("glUniform1f");
    glad_glUniform3f               = (PFNGLUNIFORM3FPROC)load("glUniform3f");
    glad_glUniform3fv              = (PFNGLUNIFORM3FVPROC)load("glUniform3fv");
    glad_glUniform4f               = (PFNGLUNIFORM4FPROC)load("glUniform4f");
    glad_glUniformMatrix4fv        = (PFNGLUNIFORMMATRIX4FVPROC)load("glUniformMatrix4fv");
    glad_glVertexAttribPointer     = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
    glad_glEnableVertexAttribArray  = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");
    glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)load("glDisableVertexAttribArray");
    glad_glGetAttribLocation        = (PFNGLGETATTRIBLOCATIONPROC)load("glGetAttribLocation");

    /* GL 3.0 */
    glad_glGenVertexArrays    = (PFNGLGENVERTEXARRAYSPROC)load("glGenVertexArrays");
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load("glDeleteVertexArrays");
    glad_glBindVertexArray    = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
    glad_glGenerateMipmap     = (PFNGLGENERATEMIPMAPPROC)load("glGenerateMipmap");

    return glad_glClear != NULL;
}
