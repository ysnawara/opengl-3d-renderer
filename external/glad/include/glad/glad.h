/*
 * GLAD - OpenGL Loader for GL 3.3 Core Profile
 * Generated for this project (minimal subset)
 */
#ifndef GLAD_GL_H_
#define GLAD_GL_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef APIENTRY
  #ifdef _WIN32
    #define APIENTRY __stdcall
  #else
    #define APIENTRY
  #endif
#endif

#ifndef APIENTRYP
  #define APIENTRYP APIENTRY *
#endif

/* ------------------------------------------------------------------ */
/*  GL type definitions                                                */
/* ------------------------------------------------------------------ */
typedef unsigned int   GLenum;
typedef unsigned char  GLboolean;
typedef unsigned int   GLbitfield;
typedef void           GLvoid;
typedef signed char    GLbyte;
typedef short          GLshort;
typedef int            GLint;
typedef unsigned char  GLubyte;
typedef unsigned short GLushort;
typedef unsigned int   GLuint;
typedef int            GLsizei;
typedef float          GLfloat;
typedef double         GLdouble;
typedef char           GLchar;
#ifdef _WIN64
  typedef long long       GLsizeiptr;
  typedef long long       GLintptr;
#else
  typedef long            GLsizeiptr;
  typedef long            GLintptr;
#endif

/* ------------------------------------------------------------------ */
/*  GL constants                                                       */
/* ------------------------------------------------------------------ */
/* Boolean */
#define GL_FALSE                          0
#define GL_TRUE                           1
#define GL_NONE                           0

/* Clear buffer bits */
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

/* Primitive types */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

/* Data types */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406

/* Enable/Disable caps */
#define GL_DEPTH_TEST                     0x0B71
#define GL_BLEND                          0x0BE2
#define GL_CULL_FACE                      0x0B44
#define GL_SCISSOR_TEST                   0x0C11
#define GL_MULTISAMPLE                    0x809D

/* Depth function */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

/* Blend func */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303

/* Face culling */
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408
#define GL_CW                             0x0900
#define GL_CCW                            0x0901

/* Polygon mode */
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

/* Texture targets */
#define GL_TEXTURE_2D                     0x0DE1

/* Texture parameters */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803

/* Texture filter modes */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

/* Texture wrap modes */
#define GL_REPEAT                         0x2901
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_MIRRORED_REPEAT                0x8370

/* Pixel formats */
#define GL_RED                            0x1903
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908

/* Pixel store */
#define GL_UNPACK_ALIGNMENT               0x0CF5

/* GetString targets */
#define GL_VENDOR                         0x1F00
#define GL_RENDERER                       0x1F01
#define GL_VERSION                        0x1F02

/* Buffer targets */
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893

/* Buffer usage */
#define GL_STREAM_DRAW                    0x88E0
#define GL_STATIC_DRAW                    0x88E4
#define GL_DYNAMIC_DRAW                   0x88E8

/* Shader types */
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31

/* Shader queries */
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_INFO_LOG_LENGTH                0x8B84

/* Texture units */
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7

/* Max */
#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872
#define GL_MAX_VERTEX_ATTRIBS             0x8869

/* Errors */
#define GL_NO_ERROR                       0

/* ------------------------------------------------------------------ */
/*  Function pointer types, extern declarations, and macros            */
/* ------------------------------------------------------------------ */

/* --- GL 1.0 / 1.1 ------------------------------------------------ */
typedef void      (APIENTRYP PFNGLVIEWPORTPROC)(GLint, GLint, GLsizei, GLsizei);
typedef void      (APIENTRYP PFNGLCLEARPROC)(GLbitfield);
typedef void      (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void      (APIENTRYP PFNGLENABLEPROC)(GLenum);
typedef void      (APIENTRYP PFNGLDISABLEPROC)(GLenum);
typedef void      (APIENTRYP PFNGLDEPTHFUNCPROC)(GLenum);
typedef void      (APIENTRYP PFNGLBLENDFUNCPROC)(GLenum, GLenum);
typedef void      (APIENTRYP PFNGLCULLFACEPROC)(GLenum);
typedef void      (APIENTRYP PFNGLFRONTFACEPROC)(GLenum);
typedef void      (APIENTRYP PFNGLPOLYGONMODEPROC)(GLenum, GLenum);
typedef void      (APIENTRYP PFNGLPIXELSTOREIPROC)(GLenum, GLint);
typedef void      (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void      (APIENTRYP PFNGLTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void*);
typedef void      (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum, GLenum, GLint);
typedef void      (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum, GLint, GLsizei);
typedef void      (APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const void*);
typedef void      (APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei, GLuint*);
typedef void      (APIENTRYP PFNGLDELETETEXTURESPROC)(GLsizei, const GLuint*);
typedef void      (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum, GLuint);
typedef GLenum    (APIENTRYP PFNGLGETERRORPROC)(void);
typedef const GLubyte* (APIENTRYP PFNGLGETSTRINGPROC)(GLenum);
typedef void      (APIENTRYP PFNGLGETINTEGERVPROC)(GLenum, GLint*);

extern PFNGLVIEWPORTPROC        glad_glViewport;
extern PFNGLCLEARPROC           glad_glClear;
extern PFNGLCLEARCOLORPROC      glad_glClearColor;
extern PFNGLENABLEPROC          glad_glEnable;
extern PFNGLDISABLEPROC         glad_glDisable;
extern PFNGLDEPTHFUNCPROC       glad_glDepthFunc;
extern PFNGLBLENDFUNCPROC       glad_glBlendFunc;
extern PFNGLCULLFACEPROC        glad_glCullFace;
extern PFNGLFRONTFACEPROC       glad_glFrontFace;
extern PFNGLPOLYGONMODEPROC     glad_glPolygonMode;
extern PFNGLPIXELSTOREIPROC     glad_glPixelStorei;
extern PFNGLTEXIMAGE2DPROC      glad_glTexImage2D;
extern PFNGLTEXSUBIMAGE2DPROC   glad_glTexSubImage2D;
extern PFNGLTEXPARAMETERIPROC   glad_glTexParameteri;
extern PFNGLDRAWARRAYSPROC      glad_glDrawArrays;
extern PFNGLDRAWELEMENTSPROC    glad_glDrawElements;
extern PFNGLGENTEXTURESPROC     glad_glGenTextures;
extern PFNGLDELETETEXTURESPROC  glad_glDeleteTextures;
extern PFNGLBINDTEXTUREPROC     glad_glBindTexture;
extern PFNGLGETERRORPROC        glad_glGetError;
extern PFNGLGETSTRINGPROC       glad_glGetString;
extern PFNGLGETINTEGERVPROC     glad_glGetIntegerv;

#define glViewport        glad_glViewport
#define glClear           glad_glClear
#define glClearColor      glad_glClearColor
#define glEnable          glad_glEnable
#define glDisable         glad_glDisable
#define glDepthFunc       glad_glDepthFunc
#define glBlendFunc       glad_glBlendFunc
#define glCullFace        glad_glCullFace
#define glFrontFace       glad_glFrontFace
#define glPolygonMode     glad_glPolygonMode
#define glPixelStorei     glad_glPixelStorei
#define glTexImage2D      glad_glTexImage2D
#define glTexSubImage2D   glad_glTexSubImage2D
#define glTexParameteri   glad_glTexParameteri
#define glDrawArrays      glad_glDrawArrays
#define glDrawElements    glad_glDrawElements
#define glGenTextures     glad_glGenTextures
#define glDeleteTextures  glad_glDeleteTextures
#define glBindTexture     glad_glBindTexture
#define glGetError        glad_glGetError
#define glGetString       glad_glGetString
#define glGetIntegerv     glad_glGetIntegerv

/* --- GL 1.3 ------------------------------------------------------- */
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum);
extern PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
#define glActiveTexture glad_glActiveTexture

/* --- GL 1.5 ------------------------------------------------------- */
typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei, const GLuint*);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum, GLuint);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, const void*);

extern PFNGLGENBUFFERSPROC     glad_glGenBuffers;
extern PFNGLDELETEBUFFERSPROC  glad_glDeleteBuffers;
extern PFNGLBINDBUFFERPROC     glad_glBindBuffer;
extern PFNGLBUFFERDATAPROC     glad_glBufferData;
extern PFNGLBUFFERSUBDATAPROC  glad_glBufferSubData;

#define glGenBuffers      glad_glGenBuffers
#define glDeleteBuffers   glad_glDeleteBuffers
#define glBindBuffer      glad_glBindBuffer
#define glBufferData      glad_glBufferData
#define glBufferSubData   glad_glBufferSubData

/* --- GL 2.0 ------------------------------------------------------- */
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum);
typedef void   (APIENTRYP PFNGLDELETESHADERPROC)(GLuint);
typedef void   (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar* const*, const GLint*);
typedef void   (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint);
typedef void   (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint, GLenum, GLint*);
typedef void   (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)(void);
typedef void   (APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint);
typedef void   (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint, GLuint);
typedef void   (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint);
typedef void   (APIENTRYP PFNGLVALIDATEPROGRAMPROC)(GLuint);
typedef void   (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint, GLenum, GLint*);
typedef void   (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void   (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint);
typedef GLint  (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar*);
typedef void   (APIENTRYP PFNGLUNIFORM1IPROC)(GLint, GLint);
typedef void   (APIENTRYP PFNGLUNIFORM1FPROC)(GLint, GLfloat);
typedef void   (APIENTRYP PFNGLUNIFORM3FPROC)(GLint, GLfloat, GLfloat, GLfloat);
typedef void   (APIENTRYP PFNGLUNIFORM3FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void   (APIENTRYP PFNGLUNIFORM4FPROC)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void   (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void   (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void   (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void   (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef GLint  (APIENTRYP PFNGLGETATTRIBLOCATIONPROC)(GLuint, const GLchar*);

extern PFNGLCREATESHADERPROC             glad_glCreateShader;
extern PFNGLDELETESHADERPROC             glad_glDeleteShader;
extern PFNGLSHADERSOURCEPROC             glad_glShaderSource;
extern PFNGLCOMPILESHADERPROC            glad_glCompileShader;
extern PFNGLGETSHADERIVPROC              glad_glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC         glad_glGetShaderInfoLog;
extern PFNGLCREATEPROGRAMPROC            glad_glCreateProgram;
extern PFNGLDELETEPROGRAMPROC            glad_glDeleteProgram;
extern PFNGLATTACHSHADERPROC             glad_glAttachShader;
extern PFNGLLINKPROGRAMPROC              glad_glLinkProgram;
extern PFNGLVALIDATEPROGRAMPROC          glad_glValidateProgram;
extern PFNGLGETPROGRAMIVPROC             glad_glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC        glad_glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC               glad_glUseProgram;
extern PFNGLGETUNIFORMLOCATIONPROC       glad_glGetUniformLocation;
extern PFNGLUNIFORM1IPROC               glad_glUniform1i;
extern PFNGLUNIFORM1FPROC               glad_glUniform1f;
extern PFNGLUNIFORM3FPROC               glad_glUniform3f;
extern PFNGLUNIFORM3FVPROC              glad_glUniform3fv;
extern PFNGLUNIFORM4FPROC               glad_glUniform4f;
extern PFNGLUNIFORMMATRIX4FVPROC        glad_glUniformMatrix4fv;
extern PFNGLVERTEXATTRIBPOINTERPROC     glad_glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC  glad_glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray;
extern PFNGLGETATTRIBLOCATIONPROC        glad_glGetAttribLocation;

#define glCreateShader             glad_glCreateShader
#define glDeleteShader             glad_glDeleteShader
#define glShaderSource             glad_glShaderSource
#define glCompileShader            glad_glCompileShader
#define glGetShaderiv              glad_glGetShaderiv
#define glGetShaderInfoLog         glad_glGetShaderInfoLog
#define glCreateProgram            glad_glCreateProgram
#define glDeleteProgram            glad_glDeleteProgram
#define glAttachShader             glad_glAttachShader
#define glLinkProgram              glad_glLinkProgram
#define glValidateProgram          glad_glValidateProgram
#define glGetProgramiv             glad_glGetProgramiv
#define glGetProgramInfoLog        glad_glGetProgramInfoLog
#define glUseProgram               glad_glUseProgram
#define glGetUniformLocation       glad_glGetUniformLocation
#define glUniform1i                glad_glUniform1i
#define glUniform1f                glad_glUniform1f
#define glUniform3f                glad_glUniform3f
#define glUniform3fv               glad_glUniform3fv
#define glUniform4f                glad_glUniform4f
#define glUniformMatrix4fv         glad_glUniformMatrix4fv
#define glVertexAttribPointer      glad_glVertexAttribPointer
#define glEnableVertexAttribArray  glad_glEnableVertexAttribArray
#define glDisableVertexAttribArray glad_glDisableVertexAttribArray
#define glGetAttribLocation        glad_glGetAttribLocation

/* --- GL 3.0 ------------------------------------------------------- */
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei, GLuint*);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint*);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum);

extern PFNGLGENVERTEXARRAYSPROC    glad_glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC    glad_glBindVertexArray;
extern PFNGLGENERATEMIPMAPPROC     glad_glGenerateMipmap;

#define glGenVertexArrays    glad_glGenVertexArrays
#define glDeleteVertexArrays glad_glDeleteVertexArrays
#define glBindVertexArray    glad_glBindVertexArray
#define glGenerateMipmap     glad_glGenerateMipmap

/* ------------------------------------------------------------------ */
/*  Loader                                                             */
/* ------------------------------------------------------------------ */
typedef void* (*GLADloadproc)(const char* name);
int gladLoadGL(GLADloadproc load);

#ifdef __cplusplus
}
#endif

#endif /* GLAD_GL_H_ */
