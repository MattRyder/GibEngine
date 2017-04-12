// #include "glmock.hpp"
// #include <pthread.h>
// #include <map>

// static std::map<pthread_t, GLMock* > gMap;
// static pthread_mutex_t gMutex = PTHREAD_MUTEX_INITIALIZER;

// GLMock::GLMock()
// {
//     pthread_mutex_lock(&gMutex);
//     gMap.insert(std::pair<pthread_t, GLMock* >(pthread_self(), this));
//     pthread_mutex_unlock(&gMutex);
// }

// GLMock::~GLMock()
// {
//     pthread_mutex_lock(&gMutex);
//     gMap.erase(pthread_self());
//     pthread_mutex_unlock(&gMutex);
// }

// static GLMock* getMock()
// {
//     pthread_mutex_lock(&gMutex);
//     std::map<pthread_t, GLMock*>::iterator it = gMap.find(pthread_self());
//     if (it == gMap.end()) {
//         std::cerr << "Initialize Mock first" << std::endl;
//         pthread_mutex_unlock(&gMutex);
//         std::abort();
//     }
//     pthread_mutex_unlock(&gMutex);
//     return it->second;
// }

// intmax_t imaxabs(intmax_t __n)
// {
//     return getMock()->imaxabs(__n);
// }
// imaxdiv_t imaxdiv(intmax_t __numer, intmax_t __denom)
// {
//     return getMock()->imaxdiv(__numer, __denom);
// }
// intmax_t strtoimax(const char *restrict __nptr, char **restrict __endptr, int __base)
// {
//     return getMock()->strtoimax(__nptr, __endptr, __base);
// }
// uintmax_t strtoumax(const char *restrict __nptr, char **restrict __endptr, int __base)
// {
//     return getMock()->strtoumax(__nptr, __endptr, __base);
// }
// intmax_t wcstoimax(const __gwchar_t *restrict __nptr, __gwchar_t **restrict __endptr, int __base)
// {
//     return getMock()->wcstoimax(__nptr, __endptr, __base);
// }
// uintmax_t wcstoumax(const __gwchar_t *restrict __nptr, __gwchar_t **restrict __endptr, int __base)
// {
//     return getMock()->wcstoumax(__nptr, __endptr, __base);
// }
// int gl3wInit()
// {
//     return getMock()->gl3wInit();
// }
// int gl3wIsSupported(int major, int minor)
// {
//     return getMock()->gl3wIsSupported(major, minor);
// }
// GL3WglProc gl3wGetProcAddress(const char * proc)
// {
//     return getMock()->gl3wGetProcAddress(proc);
// }
// void  mockgl3wActiveShaderProgram(GLuint pipeline, GLuint program)
// {
//     return getMock()->gl3wActiveShaderProgram(pipeline, program);
// }
// PFNGLACTIVESHADERPROGRAMPROC gl3wActiveShaderProgram = mockgl3wActiveShaderProgram;

// void  mockgl3wActiveTexture(GLenum texture)
// {
//     return getMock()->gl3wActiveTexture(texture);
// }
// PFNGLACTIVETEXTUREPROC gl3wActiveTexture = mockgl3wActiveTexture;

// void  mockgl3wAttachShader(GLuint program, GLuint shader)
// {
//     return getMock()->gl3wAttachShader(program, shader);
// }
// PFNGLATTACHSHADERPROC gl3wAttachShader = mockgl3wAttachShader;

// void  mockgl3wBeginConditionalRender(GLuint id, GLenum mode)
// {
//     return getMock()->gl3wBeginConditionalRender(id, mode);
// }
// PFNGLBEGINCONDITIONALRENDERPROC gl3wBeginConditionalRender = mockgl3wBeginConditionalRender;

// void  mockgl3wBeginQuery(GLenum target, GLuint id)
// {
//     return getMock()->gl3wBeginQuery(target, id);
// }
// PFNGLBEGINQUERYPROC gl3wBeginQuery = mockgl3wBeginQuery;

// void  mockgl3wBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
// {
//     return getMock()->gl3wBeginQueryIndexed(target, index, id);
// }
// PFNGLBEGINQUERYINDEXEDPROC gl3wBeginQueryIndexed = mockgl3wBeginQueryIndexed;

// void  mockgl3wBeginTransformFeedback(GLenum primitiveMode)
// {
//     return getMock()->gl3wBeginTransformFeedback(primitiveMode);
// }
// PFNGLBEGINTRANSFORMFEEDBACKPROC gl3wBeginTransformFeedback = mockgl3wBeginTransformFeedback;

// void  mockgl3wBindAttribLocation(GLuint program, GLuint index, const GLchar * name)
// {
//     return getMock()->gl3wBindAttribLocation(program, index, name);
// }
// PFNGLBINDATTRIBLOCATIONPROC gl3wBindAttribLocation = mockgl3wBindAttribLocation;

// void  mockgl3wBindBuffer(GLenum target, GLuint buffer)
// {
//     return getMock()->gl3wBindBuffer(target, buffer);
// }
// PFNGLBINDBUFFERPROC gl3wBindBuffer = mockgl3wBindBuffer;

// void  mockgl3wBindBufferBase(GLenum target, GLuint index, GLuint buffer)
// {
//     return getMock()->gl3wBindBufferBase(target, index, buffer);
// }
// PFNGLBINDBUFFERBASEPROC gl3wBindBufferBase = mockgl3wBindBufferBase;

// void  mockgl3wBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
// {
//     return getMock()->gl3wBindBufferRange(target, index, buffer, offset, size);
// }
// PFNGLBINDBUFFERRANGEPROC gl3wBindBufferRange = mockgl3wBindBufferRange;

// void  mockgl3wBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers)
// {
//     return getMock()->gl3wBindBuffersBase(target, first, count, buffers);
// }
// PFNGLBINDBUFFERSBASEPROC gl3wBindBuffersBase = mockgl3wBindBuffersBase;

// void  mockgl3wBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes)
// {
//     return getMock()->gl3wBindBuffersRange(target, first, count, buffers, offsets, sizes);
// }
// PFNGLBINDBUFFERSRANGEPROC gl3wBindBuffersRange = mockgl3wBindBuffersRange;

// void  mockgl3wBindFragDataLocation(GLuint program, GLuint color, const GLchar * name)
// {
//     return getMock()->gl3wBindFragDataLocation(program, color, name);
// }
// PFNGLBINDFRAGDATALOCATIONPROC gl3wBindFragDataLocation = mockgl3wBindFragDataLocation;

// void  mockgl3wBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name)
// {
//     return getMock()->gl3wBindFragDataLocationIndexed(program, colorNumber, index, name);
// }
// PFNGLBINDFRAGDATALOCATIONINDEXEDPROC gl3wBindFragDataLocationIndexed = mockgl3wBindFragDataLocationIndexed;

// void  mockgl3wBindFramebuffer(GLenum target, GLuint framebuffer)
// {
//     return getMock()->gl3wBindFramebuffer(target, framebuffer);
// }
// PFNGLBINDFRAMEBUFFERPROC gl3wBindFramebuffer = mockgl3wBindFramebuffer;

// void  mockgl3wBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
// {
//     return getMock()->gl3wBindImageTexture(unit, texture, level, layered, layer, access, format);
// }
// PFNGLBINDIMAGETEXTUREPROC gl3wBindImageTexture = mockgl3wBindImageTexture;

// void  mockgl3wBindImageTextures(GLuint first, GLsizei count, const GLuint * textures)
// {
//     return getMock()->gl3wBindImageTextures(first, count, textures);
// }
// PFNGLBINDIMAGETEXTURESPROC gl3wBindImageTextures = mockgl3wBindImageTextures;

// void  mockgl3wBindProgramPipeline(GLuint pipeline)
// {
//     return getMock()->gl3wBindProgramPipeline(pipeline);
// }
// PFNGLBINDPROGRAMPIPELINEPROC gl3wBindProgramPipeline = mockgl3wBindProgramPipeline;

// void  mockgl3wBindRenderbuffer(GLenum target, GLuint renderbuffer)
// {
//     return getMock()->gl3wBindRenderbuffer(target, renderbuffer);
// }
// PFNGLBINDRENDERBUFFERPROC gl3wBindRenderbuffer = mockgl3wBindRenderbuffer;

// void  mockgl3wBindSampler(GLuint unit, GLuint sampler)
// {
//     return getMock()->gl3wBindSampler(unit, sampler);
// }
// PFNGLBINDSAMPLERPROC gl3wBindSampler = mockgl3wBindSampler;

// void  mockgl3wBindSamplers(GLuint first, GLsizei count, const GLuint * samplers)
// {
//     return getMock()->gl3wBindSamplers(first, count, samplers);
// }
// PFNGLBINDSAMPLERSPROC gl3wBindSamplers = mockgl3wBindSamplers;

// void  mockgl3wBindTexture(GLenum target, GLuint texture)
// {
//     return getMock()->gl3wBindTexture(target, texture);
// }
// PFNGLBINDTEXTUREPROC gl3wBindTexture = mockgl3wBindTexture;

// void  mockgl3wBindTextureUnit(GLuint unit, GLuint texture)
// {
//     return getMock()->gl3wBindTextureUnit(unit, texture);
// }
// PFNGLBINDTEXTUREUNITPROC gl3wBindTextureUnit = mockgl3wBindTextureUnit;

// void  mockgl3wBindTextures(GLuint first, GLsizei count, const GLuint * textures)
// {
//     return getMock()->gl3wBindTextures(first, count, textures);
// }
// PFNGLBINDTEXTURESPROC gl3wBindTextures = mockgl3wBindTextures;

// void  mockgl3wBindTransformFeedback(GLenum target, GLuint id)
// {
//     return getMock()->gl3wBindTransformFeedback(target, id);
// }
// PFNGLBINDTRANSFORMFEEDBACKPROC gl3wBindTransformFeedback = mockgl3wBindTransformFeedback;

// void  mockgl3wBindVertexArray(GLuint array)
// {
//     return getMock()->gl3wBindVertexArray(array);
// }
// PFNGLBINDVERTEXARRAYPROC gl3wBindVertexArray = mockgl3wBindVertexArray;

// void  mockgl3wBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
// {
//     return getMock()->gl3wBindVertexBuffer(bindingindex, buffer, offset, stride);
// }
// PFNGLBINDVERTEXBUFFERPROC gl3wBindVertexBuffer = mockgl3wBindVertexBuffer;

// void  mockgl3wBindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides)
// {
//     return getMock()->gl3wBindVertexBuffers(first, count, buffers, offsets, strides);
// }
// PFNGLBINDVERTEXBUFFERSPROC gl3wBindVertexBuffers = mockgl3wBindVertexBuffers;

// void  mockgl3wBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
// {
//     return getMock()->gl3wBlendColor(red, green, blue, alpha);
// }
// PFNGLBLENDCOLORPROC gl3wBlendColor = mockgl3wBlendColor;

// void  mockgl3wBlendEquation(GLenum mode)
// {
//     return getMock()->gl3wBlendEquation(mode);
// }
// PFNGLBLENDEQUATIONPROC gl3wBlendEquation = mockgl3wBlendEquation;

// void  mockgl3wBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
// {
//     return getMock()->gl3wBlendEquationSeparate(modeRGB, modeAlpha);
// }
// PFNGLBLENDEQUATIONSEPARATEPROC gl3wBlendEquationSeparate = mockgl3wBlendEquationSeparate;

// void  mockgl3wBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
// {
//     return getMock()->gl3wBlendEquationSeparatei(buf, modeRGB, modeAlpha);
// }
// PFNGLBLENDEQUATIONSEPARATEIPROC gl3wBlendEquationSeparatei = mockgl3wBlendEquationSeparatei;

// void  mockgl3wBlendEquationSeparateiARB(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
// {
//     return getMock()->gl3wBlendEquationSeparateiARB(buf, modeRGB, modeAlpha);
// }
// PFNGLBLENDEQUATIONSEPARATEIARBPROC gl3wBlendEquationSeparateiARB = mockgl3wBlendEquationSeparateiARB;

// void  mockgl3wBlendEquationi(GLuint buf, GLenum mode)
// {
//     return getMock()->gl3wBlendEquationi(buf, mode);
// }
// PFNGLBLENDEQUATIONIPROC gl3wBlendEquationi = mockgl3wBlendEquationi;

// void  mockgl3wBlendEquationiARB(GLuint buf, GLenum mode)
// {
//     return getMock()->gl3wBlendEquationiARB(buf, mode);
// }
// PFNGLBLENDEQUATIONIARBPROC gl3wBlendEquationiARB = mockgl3wBlendEquationiARB;

// void  mockgl3wBlendFunc(GLenum sfactor, GLenum dfactor)
// {
//     return getMock()->gl3wBlendFunc(sfactor, dfactor);
// }
// PFNGLBLENDFUNCPROC gl3wBlendFunc = mockgl3wBlendFunc;

// void  mockgl3wBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
// {
//     return getMock()->gl3wBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
// }
// PFNGLBLENDFUNCSEPARATEPROC gl3wBlendFuncSeparate = mockgl3wBlendFuncSeparate;

// void  mockgl3wBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
// {
//     return getMock()->gl3wBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
// }
// PFNGLBLENDFUNCSEPARATEIPROC gl3wBlendFuncSeparatei = mockgl3wBlendFuncSeparatei;

// void  mockgl3wBlendFuncSeparateiARB(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
// {
//     return getMock()->gl3wBlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
// }
// PFNGLBLENDFUNCSEPARATEIARBPROC gl3wBlendFuncSeparateiARB = mockgl3wBlendFuncSeparateiARB;

// void  mockgl3wBlendFunci(GLuint buf, GLenum src, GLenum dst)
// {
//     return getMock()->gl3wBlendFunci(buf, src, dst);
// }
// PFNGLBLENDFUNCIPROC gl3wBlendFunci = mockgl3wBlendFunci;

// void  mockgl3wBlendFunciARB(GLuint buf, GLenum src, GLenum dst)
// {
//     return getMock()->gl3wBlendFunciARB(buf, src, dst);
// }
// PFNGLBLENDFUNCIARBPROC gl3wBlendFunciARB = mockgl3wBlendFunciARB;

// void  mockgl3wBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
// {
//     return getMock()->gl3wBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
// }
// PFNGLBLITFRAMEBUFFERPROC gl3wBlitFramebuffer = mockgl3wBlitFramebuffer;

// void  mockgl3wBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
// {
//     return getMock()->gl3wBufferData(target, size, data, usage);
// }
// PFNGLBUFFERDATAPROC gl3wBufferData = mockgl3wBufferData;

// void  mockgl3wBufferPageCommitmentARB(GLenum target, GLintptr offset, GLsizei size, GLboolean commit)
// {
//     return getMock()->gl3wBufferPageCommitmentARB(target, offset, size, commit);
// }
// PFNGLBUFFERPAGECOMMITMENTARBPROC gl3wBufferPageCommitmentARB = mockgl3wBufferPageCommitmentARB;

// void  mockgl3wBufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags)
// {
//     return getMock()->gl3wBufferStorage(target, size, data, flags);
// }
// PFNGLBUFFERSTORAGEPROC gl3wBufferStorage = mockgl3wBufferStorage;

// void  mockgl3wBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
// {
//     return getMock()->gl3wBufferSubData(target, offset, size, data);
// }
// PFNGLBUFFERSUBDATAPROC gl3wBufferSubData = mockgl3wBufferSubData;

// unsigned int  mockgl3wCheckFramebufferStatus(GLenum target)
// {
//     return getMock()->gl3wCheckFramebufferStatus(target);
// }
// PFNGLCHECKFRAMEBUFFERSTATUSPROC gl3wCheckFramebufferStatus = mockgl3wCheckFramebufferStatus;

// unsigned int  mockgl3wCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
// {
//     return getMock()->gl3wCheckNamedFramebufferStatus(framebuffer, target);
// }
// PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC gl3wCheckNamedFramebufferStatus = mockgl3wCheckNamedFramebufferStatus;

// void  mockgl3wClampColor(GLenum target, GLenum clamp)
// {
//     return getMock()->gl3wClampColor(target, clamp);
// }
// PFNGLCLAMPCOLORPROC gl3wClampColor = mockgl3wClampColor;

// void  mockgl3wClear(GLbitfield mask)
// {
//     return getMock()->gl3wClear(mask);
// }
// PFNGLCLEARPROC gl3wClear = mockgl3wClear;

// void  mockgl3wClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data)
// {
//     return getMock()->gl3wClearBufferData(target, internalformat, format, type, data);
// }
// PFNGLCLEARBUFFERDATAPROC gl3wClearBufferData = mockgl3wClearBufferData;

// void  mockgl3wClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
// {
//     return getMock()->gl3wClearBufferSubData(target, internalformat, offset, size, format, type, data);
// }
// PFNGLCLEARBUFFERSUBDATAPROC gl3wClearBufferSubData = mockgl3wClearBufferSubData;

// void  mockgl3wClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
// {
//     return getMock()->gl3wClearBufferfi(buffer, drawbuffer, depth, stencil);
// }
// PFNGLCLEARBUFFERFIPROC gl3wClearBufferfi = mockgl3wClearBufferfi;

// void  mockgl3wClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value)
// {
//     return getMock()->gl3wClearBufferfv(buffer, drawbuffer, value);
// }
// PFNGLCLEARBUFFERFVPROC gl3wClearBufferfv = mockgl3wClearBufferfv;

// void  mockgl3wClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value)
// {
//     return getMock()->gl3wClearBufferiv(buffer, drawbuffer, value);
// }
// PFNGLCLEARBUFFERIVPROC gl3wClearBufferiv = mockgl3wClearBufferiv;

// void  mockgl3wClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value)
// {
//     return getMock()->gl3wClearBufferuiv(buffer, drawbuffer, value);
// }
// PFNGLCLEARBUFFERUIVPROC gl3wClearBufferuiv = mockgl3wClearBufferuiv;

// void  mockgl3wClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
// {
//     return getMock()->gl3wClearColor(red, green, blue, alpha);
// }
// PFNGLCLEARCOLORPROC gl3wClearColor = mockgl3wClearColor;

// void  mockgl3wClearDepth(GLdouble depth)
// {
//     return getMock()->gl3wClearDepth(depth);
// }
// PFNGLCLEARDEPTHPROC gl3wClearDepth = mockgl3wClearDepth;

// void  mockgl3wClearDepthf(GLfloat d)
// {
//     return getMock()->gl3wClearDepthf(d);
// }
// PFNGLCLEARDEPTHFPROC gl3wClearDepthf = mockgl3wClearDepthf;

// void  mockgl3wClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data)
// {
//     return getMock()->gl3wClearNamedBufferData(buffer, internalformat, format, type, data);
// }
// PFNGLCLEARNAMEDBUFFERDATAPROC gl3wClearNamedBufferData = mockgl3wClearNamedBufferData;

// void  mockgl3wClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizei size, GLenum format, GLenum type, const void * data)
// {
//     return getMock()->gl3wClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
// }
// PFNGLCLEARNAMEDBUFFERSUBDATAPROC gl3wClearNamedBufferSubData = mockgl3wClearNamedBufferSubData;

// void  mockgl3wClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, const GLfloat depth, GLint stencil)
// {
//     return getMock()->gl3wClearNamedFramebufferfi(framebuffer, buffer, depth, stencil);
// }
// PFNGLCLEARNAMEDFRAMEBUFFERFIPROC gl3wClearNamedFramebufferfi = mockgl3wClearNamedFramebufferfi;

// void  mockgl3wClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value)
// {
//     return getMock()->gl3wClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
// }
// PFNGLCLEARNAMEDFRAMEBUFFERFVPROC gl3wClearNamedFramebufferfv = mockgl3wClearNamedFramebufferfv;

// void  mockgl3wClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value)
// {
//     return getMock()->gl3wClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
// }
// PFNGLCLEARNAMEDFRAMEBUFFERIVPROC gl3wClearNamedFramebufferiv = mockgl3wClearNamedFramebufferiv;

// void  mockgl3wClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value)
// {
//     return getMock()->gl3wClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
// }
// PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC gl3wClearNamedFramebufferuiv = mockgl3wClearNamedFramebufferuiv;

// void  mockgl3wClearStencil(GLint s)
// {
//     return getMock()->gl3wClearStencil(s);
// }
// PFNGLCLEARSTENCILPROC gl3wClearStencil = mockgl3wClearStencil;

// void  mockgl3wClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data)
// {
//     return getMock()->gl3wClearTexImage(texture, level, format, type, data);
// }
// PFNGLCLEARTEXIMAGEPROC gl3wClearTexImage = mockgl3wClearTexImage;

// unsigned int  mockgl3wClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
// {
//     return getMock()->gl3wClientWaitSync(sync, flags, timeout);
// }
// PFNGLCLIENTWAITSYNCPROC gl3wClientWaitSync = mockgl3wClientWaitSync;

// void  mockgl3wClipControl(GLenum origin, GLenum depth)
// {
//     return getMock()->gl3wClipControl(origin, depth);
// }
// PFNGLCLIPCONTROLPROC gl3wClipControl = mockgl3wClipControl;

// void  mockgl3wColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
// {
//     return getMock()->gl3wColorMask(red, green, blue, alpha);
// }
// PFNGLCOLORMASKPROC gl3wColorMask = mockgl3wColorMask;

// void  mockgl3wColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
// {
//     return getMock()->gl3wColorMaski(index, r, g, b, a);
// }
// PFNGLCOLORMASKIPROC gl3wColorMaski = mockgl3wColorMaski;

// void  mockgl3wCompileShader(GLuint shader)
// {
//     return getMock()->gl3wCompileShader(shader);
// }
// PFNGLCOMPILESHADERPROC gl3wCompileShader = mockgl3wCompileShader;

// void  mockgl3wCompileShaderIncludeARB(GLuint shader, GLsizei count, const GLchar *const * path, const GLint * length)
// {
//     return getMock()->gl3wCompileShaderIncludeARB(shader, count, path, length);
// }
// PFNGLCOMPILESHADERINCLUDEARBPROC gl3wCompileShaderIncludeARB = mockgl3wCompileShaderIncludeARB;

// void  mockgl3wCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
// {
//     return getMock()->gl3wCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
// }
// PFNGLCOMPRESSEDTEXIMAGE1DPROC gl3wCompressedTexImage1D = mockgl3wCompressedTexImage1D;

// void  mockgl3wCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
// {
//     return getMock()->gl3wCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
// }
// PFNGLCOMPRESSEDTEXIMAGE2DPROC gl3wCompressedTexImage2D = mockgl3wCompressedTexImage2D;

// void  mockgl3wCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
// {
//     return getMock()->gl3wCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
// }
// PFNGLCOMPRESSEDTEXIMAGE3DPROC gl3wCompressedTexImage3D = mockgl3wCompressedTexImage3D;

// void  mockgl3wCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
// {
//     return getMock()->gl3wCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
// }
// PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC gl3wCompressedTexSubImage1D = mockgl3wCompressedTexSubImage1D;

// void  mockgl3wCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
// {
//     return getMock()->gl3wCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
// }
// PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gl3wCompressedTexSubImage2D = mockgl3wCompressedTexSubImage2D;

// void  mockgl3wCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
// {
//     return getMock()->gl3wCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
// }
// PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC gl3wCompressedTextureSubImage1D = mockgl3wCompressedTextureSubImage1D;

// void  mockgl3wCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
// {
//     return getMock()->gl3wCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
// }
// PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC gl3wCompressedTextureSubImage2D = mockgl3wCompressedTextureSubImage2D;

// void  mockgl3wCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
// {
//     return getMock()->gl3wCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
// }
// PFNGLCOPYBUFFERSUBDATAPROC gl3wCopyBufferSubData = mockgl3wCopyBufferSubData;

// void  mockgl3wCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizei size)
// {
//     return getMock()->gl3wCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
// }
// PFNGLCOPYNAMEDBUFFERSUBDATAPROC gl3wCopyNamedBufferSubData = mockgl3wCopyNamedBufferSubData;

// void  mockgl3wCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
// {
//     return getMock()->gl3wCopyTexImage1D(target, level, internalformat, x, y, width, border);
// }
// PFNGLCOPYTEXIMAGE1DPROC gl3wCopyTexImage1D = mockgl3wCopyTexImage1D;

// void  mockgl3wCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
// {
//     return getMock()->gl3wCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
// }
// PFNGLCOPYTEXIMAGE2DPROC gl3wCopyTexImage2D = mockgl3wCopyTexImage2D;

// void  mockgl3wCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
// {
//     return getMock()->gl3wCopyTexSubImage1D(target, level, xoffset, x, y, width);
// }
// PFNGLCOPYTEXSUBIMAGE1DPROC gl3wCopyTexSubImage1D = mockgl3wCopyTexSubImage1D;

// void  mockgl3wCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
// }
// PFNGLCOPYTEXSUBIMAGE2DPROC gl3wCopyTexSubImage2D = mockgl3wCopyTexSubImage2D;

// void  mockgl3wCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
// }
// PFNGLCOPYTEXSUBIMAGE3DPROC gl3wCopyTexSubImage3D = mockgl3wCopyTexSubImage3D;

// void  mockgl3wCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
// {
//     return getMock()->gl3wCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
// }
// PFNGLCOPYTEXTURESUBIMAGE1DPROC gl3wCopyTextureSubImage1D = mockgl3wCopyTextureSubImage1D;

// void  mockgl3wCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
// }
// PFNGLCOPYTEXTURESUBIMAGE2DPROC gl3wCopyTextureSubImage2D = mockgl3wCopyTextureSubImage2D;

// void  mockgl3wCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
// }
// PFNGLCOPYTEXTURESUBIMAGE3DPROC gl3wCopyTextureSubImage3D = mockgl3wCopyTextureSubImage3D;

// void  mockgl3wCreateBuffers(GLsizei n, GLuint * buffers)
// {
//     return getMock()->gl3wCreateBuffers(n, buffers);
// }
// PFNGLCREATEBUFFERSPROC gl3wCreateBuffers = mockgl3wCreateBuffers;

// void  mockgl3wCreateFramebuffers(GLsizei n, GLuint * framebuffers)
// {
//     return getMock()->gl3wCreateFramebuffers(n, framebuffers);
// }
// PFNGLCREATEFRAMEBUFFERSPROC gl3wCreateFramebuffers = mockgl3wCreateFramebuffers;

// unsigned int  mockgl3wCreateProgram()
// {
//     return getMock()->gl3wCreateProgram();
// }
// PFNGLCREATEPROGRAMPROC gl3wCreateProgram = mockgl3wCreateProgram;

// void  mockgl3wCreateProgramPipelines(GLsizei n, GLuint * pipelines)
// {
//     return getMock()->gl3wCreateProgramPipelines(n, pipelines);
// }
// PFNGLCREATEPROGRAMPIPELINESPROC gl3wCreateProgramPipelines = mockgl3wCreateProgramPipelines;

// void  mockgl3wCreateQueries(GLenum target, GLsizei n, GLuint * ids)
// {
//     return getMock()->gl3wCreateQueries(target, n, ids);
// }
// PFNGLCREATEQUERIESPROC gl3wCreateQueries = mockgl3wCreateQueries;

// void  mockgl3wCreateRenderbuffers(GLsizei n, GLuint * renderbuffers)
// {
//     return getMock()->gl3wCreateRenderbuffers(n, renderbuffers);
// }
// PFNGLCREATERENDERBUFFERSPROC gl3wCreateRenderbuffers = mockgl3wCreateRenderbuffers;

// void  mockgl3wCreateSamplers(GLsizei n, GLuint * samplers)
// {
//     return getMock()->gl3wCreateSamplers(n, samplers);
// }
// PFNGLCREATESAMPLERSPROC gl3wCreateSamplers = mockgl3wCreateSamplers;

// unsigned int  mockgl3wCreateShader(GLenum type)
// {
//     return getMock()->gl3wCreateShader(type);
// }
// PFNGLCREATESHADERPROC gl3wCreateShader = mockgl3wCreateShader;

// unsigned int  mockgl3wCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const * strings)
// {
//     return getMock()->gl3wCreateShaderProgramv(type, count, strings);
// }
// PFNGLCREATESHADERPROGRAMVPROC gl3wCreateShaderProgramv = mockgl3wCreateShaderProgramv;

// struct __GLsync * mockgl3wCreateSyncFromCLeventARB(struct _cl_context * context, struct _cl_event * event, GLbitfield flags)
// {
//     return getMock()->gl3wCreateSyncFromCLeventARB(context, event, flags);
// }
// PFNGLCREATESYNCFROMCLEVENTARBPROC gl3wCreateSyncFromCLeventARB = mockgl3wCreateSyncFromCLeventARB;

// void  mockgl3wCreateTextures(GLenum target, GLsizei n, GLuint * textures)
// {
//     return getMock()->gl3wCreateTextures(target, n, textures);
// }
// PFNGLCREATETEXTURESPROC gl3wCreateTextures = mockgl3wCreateTextures;

// void  mockgl3wCreateTransformFeedbacks(GLsizei n, GLuint * ids)
// {
//     return getMock()->gl3wCreateTransformFeedbacks(n, ids);
// }
// PFNGLCREATETRANSFORMFEEDBACKSPROC gl3wCreateTransformFeedbacks = mockgl3wCreateTransformFeedbacks;

// void  mockgl3wCreateVertexArrays(GLsizei n, GLuint * arrays)
// {
//     return getMock()->gl3wCreateVertexArrays(n, arrays);
// }
// PFNGLCREATEVERTEXARRAYSPROC gl3wCreateVertexArrays = mockgl3wCreateVertexArrays;

// void  mockgl3wCullFace(GLenum mode)
// {
//     return getMock()->gl3wCullFace(mode);
// }
// PFNGLCULLFACEPROC gl3wCullFace = mockgl3wCullFace;

// void  mockgl3wDebugMessageCallback(GLDEBUGPROC callback, const void * userParam)
// {
//     return getMock()->gl3wDebugMessageCallback(callback, userParam);
// }
// PFNGLDEBUGMESSAGECALLBACKPROC gl3wDebugMessageCallback = mockgl3wDebugMessageCallback;

// void  mockgl3wDebugMessageCallbackARB(GLDEBUGPROCARB callback, const void * userParam)
// {
//     return getMock()->gl3wDebugMessageCallbackARB(callback, userParam);
// }
// PFNGLDEBUGMESSAGECALLBACKARBPROC gl3wDebugMessageCallbackARB = mockgl3wDebugMessageCallbackARB;

// void  mockgl3wDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled)
// {
//     return getMock()->gl3wDebugMessageControl(source, type, severity, count, ids, enabled);
// }
// PFNGLDEBUGMESSAGECONTROLPROC gl3wDebugMessageControl = mockgl3wDebugMessageControl;

// void  mockgl3wDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled)
// {
//     return getMock()->gl3wDebugMessageControlARB(source, type, severity, count, ids, enabled);
// }
// PFNGLDEBUGMESSAGECONTROLARBPROC gl3wDebugMessageControlARB = mockgl3wDebugMessageControlARB;

// void  mockgl3wDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf)
// {
//     return getMock()->gl3wDebugMessageInsert(source, type, id, severity, length, buf);
// }
// PFNGLDEBUGMESSAGEINSERTPROC gl3wDebugMessageInsert = mockgl3wDebugMessageInsert;

// void  mockgl3wDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf)
// {
//     return getMock()->gl3wDebugMessageInsertARB(source, type, id, severity, length, buf);
// }
// PFNGLDEBUGMESSAGEINSERTARBPROC gl3wDebugMessageInsertARB = mockgl3wDebugMessageInsertARB;

// void  mockgl3wDeleteBuffers(GLsizei n, const GLuint * buffers)
// {
//     return getMock()->gl3wDeleteBuffers(n, buffers);
// }
// PFNGLDELETEBUFFERSPROC gl3wDeleteBuffers = mockgl3wDeleteBuffers;

// void  mockgl3wDeleteFramebuffers(GLsizei n, const GLuint * framebuffers)
// {
//     return getMock()->gl3wDeleteFramebuffers(n, framebuffers);
// }
// PFNGLDELETEFRAMEBUFFERSPROC gl3wDeleteFramebuffers = mockgl3wDeleteFramebuffers;

// void  mockgl3wDeleteNamedStringARB(GLint namelen, const GLchar * name)
// {
//     return getMock()->gl3wDeleteNamedStringARB(namelen, name);
// }
// PFNGLDELETENAMEDSTRINGARBPROC gl3wDeleteNamedStringARB = mockgl3wDeleteNamedStringARB;

// void  mockgl3wDeleteProgram(GLuint program)
// {
//     return getMock()->gl3wDeleteProgram(program);
// }
// PFNGLDELETEPROGRAMPROC gl3wDeleteProgram = mockgl3wDeleteProgram;

// void  mockgl3wDeleteProgramPipelines(GLsizei n, const GLuint * pipelines)
// {
//     return getMock()->gl3wDeleteProgramPipelines(n, pipelines);
// }
// PFNGLDELETEPROGRAMPIPELINESPROC gl3wDeleteProgramPipelines = mockgl3wDeleteProgramPipelines;

// void  mockgl3wDeleteQueries(GLsizei n, const GLuint * ids)
// {
//     return getMock()->gl3wDeleteQueries(n, ids);
// }
// PFNGLDELETEQUERIESPROC gl3wDeleteQueries = mockgl3wDeleteQueries;

// void  mockgl3wDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers)
// {
//     return getMock()->gl3wDeleteRenderbuffers(n, renderbuffers);
// }
// PFNGLDELETERENDERBUFFERSPROC gl3wDeleteRenderbuffers = mockgl3wDeleteRenderbuffers;

// void  mockgl3wDeleteSamplers(GLsizei count, const GLuint * samplers)
// {
//     return getMock()->gl3wDeleteSamplers(count, samplers);
// }
// PFNGLDELETESAMPLERSPROC gl3wDeleteSamplers = mockgl3wDeleteSamplers;

// void  mockgl3wDeleteShader(GLuint shader)
// {
//     return getMock()->gl3wDeleteShader(shader);
// }
// PFNGLDELETESHADERPROC gl3wDeleteShader = mockgl3wDeleteShader;

// void  mockgl3wDeleteSync(GLsync sync)
// {
//     return getMock()->gl3wDeleteSync(sync);
// }
// PFNGLDELETESYNCPROC gl3wDeleteSync = mockgl3wDeleteSync;

// void  mockgl3wDeleteTextures(GLsizei n, const GLuint * textures)
// {
//     return getMock()->gl3wDeleteTextures(n, textures);
// }
// PFNGLDELETETEXTURESPROC gl3wDeleteTextures = mockgl3wDeleteTextures;

// void  mockgl3wDeleteTransformFeedbacks(GLsizei n, const GLuint * ids)
// {
//     return getMock()->gl3wDeleteTransformFeedbacks(n, ids);
// }
// PFNGLDELETETRANSFORMFEEDBACKSPROC gl3wDeleteTransformFeedbacks = mockgl3wDeleteTransformFeedbacks;

// void  mockgl3wDeleteVertexArrays(GLsizei n, const GLuint * arrays)
// {
//     return getMock()->gl3wDeleteVertexArrays(n, arrays);
// }
// PFNGLDELETEVERTEXARRAYSPROC gl3wDeleteVertexArrays = mockgl3wDeleteVertexArrays;

// void  mockgl3wDepthFunc(GLenum func)
// {
//     return getMock()->gl3wDepthFunc(func);
// }
// PFNGLDEPTHFUNCPROC gl3wDepthFunc = mockgl3wDepthFunc;

// void  mockgl3wDepthMask(GLboolean flag)
// {
//     return getMock()->gl3wDepthMask(flag);
// }
// PFNGLDEPTHMASKPROC gl3wDepthMask = mockgl3wDepthMask;

// void  mockgl3wDepthRange(GLdouble near, GLdouble far)
// {
//     return getMock()->gl3wDepthRange(near, far);
// }
// PFNGLDEPTHRANGEPROC gl3wDepthRange = mockgl3wDepthRange;

// void  mockgl3wDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v)
// {
//     return getMock()->gl3wDepthRangeArrayv(first, count, v);
// }
// PFNGLDEPTHRANGEARRAYVPROC gl3wDepthRangeArrayv = mockgl3wDepthRangeArrayv;

// void  mockgl3wDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
// {
//     return getMock()->gl3wDepthRangeIndexed(index, n, f);
// }
// PFNGLDEPTHRANGEINDEXEDPROC gl3wDepthRangeIndexed = mockgl3wDepthRangeIndexed;

// void  mockgl3wDepthRangef(GLfloat n, GLfloat f)
// {
//     return getMock()->gl3wDepthRangef(n, f);
// }
// PFNGLDEPTHRANGEFPROC gl3wDepthRangef = mockgl3wDepthRangef;

// void  mockgl3wDetachShader(GLuint program, GLuint shader)
// {
//     return getMock()->gl3wDetachShader(program, shader);
// }
// PFNGLDETACHSHADERPROC gl3wDetachShader = mockgl3wDetachShader;

// void  mockgl3wDisable(GLenum cap)
// {
//     return getMock()->gl3wDisable(cap);
// }
// PFNGLDISABLEPROC gl3wDisable = mockgl3wDisable;

// void  mockgl3wDisableVertexArrayAttrib(GLuint vaobj, GLuint index)
// {
//     return getMock()->gl3wDisableVertexArrayAttrib(vaobj, index);
// }
// PFNGLDISABLEVERTEXARRAYATTRIBPROC gl3wDisableVertexArrayAttrib = mockgl3wDisableVertexArrayAttrib;

// void  mockgl3wDisableVertexAttribArray(GLuint index)
// {
//     return getMock()->gl3wDisableVertexAttribArray(index);
// }
// PFNGLDISABLEVERTEXATTRIBARRAYPROC gl3wDisableVertexAttribArray = mockgl3wDisableVertexAttribArray;

// void  mockgl3wDisablei(GLenum target, GLuint index)
// {
//     return getMock()->gl3wDisablei(target, index);
// }
// PFNGLDISABLEIPROC gl3wDisablei = mockgl3wDisablei;

// void  mockgl3wDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
// {
//     return getMock()->gl3wDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
// }
// PFNGLDISPATCHCOMPUTEPROC gl3wDispatchCompute = mockgl3wDispatchCompute;

// void  mockgl3wDispatchComputeGroupSizeARB(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z)
// {
//     return getMock()->gl3wDispatchComputeGroupSizeARB(num_groups_x, num_groups_y, num_groups_z, group_size_x, group_size_y, group_size_z);
// }
// PFNGLDISPATCHCOMPUTEGROUPSIZEARBPROC gl3wDispatchComputeGroupSizeARB = mockgl3wDispatchComputeGroupSizeARB;

// void  mockgl3wDispatchComputeIndirect(GLintptr indirect)
// {
//     return getMock()->gl3wDispatchComputeIndirect(indirect);
// }
// PFNGLDISPATCHCOMPUTEINDIRECTPROC gl3wDispatchComputeIndirect = mockgl3wDispatchComputeIndirect;

// void  mockgl3wDrawArrays(GLenum mode, GLint first, GLsizei count)
// {
//     return getMock()->gl3wDrawArrays(mode, first, count);
// }
// PFNGLDRAWARRAYSPROC gl3wDrawArrays = mockgl3wDrawArrays;

// void  mockgl3wDrawArraysIndirect(GLenum mode, const void * indirect)
// {
//     return getMock()->gl3wDrawArraysIndirect(mode, indirect);
// }
// PFNGLDRAWARRAYSINDIRECTPROC gl3wDrawArraysIndirect = mockgl3wDrawArraysIndirect;

// void  mockgl3wDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
// {
//     return getMock()->gl3wDrawArraysInstanced(mode, first, count, instancecount);
// }
// PFNGLDRAWARRAYSINSTANCEDPROC gl3wDrawArraysInstanced = mockgl3wDrawArraysInstanced;

// void  mockgl3wDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
// {
//     return getMock()->gl3wDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
// }
// PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC gl3wDrawArraysInstancedBaseInstance = mockgl3wDrawArraysInstancedBaseInstance;

// void  mockgl3wDrawBuffer(GLenum buf)
// {
//     return getMock()->gl3wDrawBuffer(buf);
// }
// PFNGLDRAWBUFFERPROC gl3wDrawBuffer = mockgl3wDrawBuffer;

// void  mockgl3wDrawBuffers(GLsizei n, const GLenum * bufs)
// {
//     return getMock()->gl3wDrawBuffers(n, bufs);
// }
// PFNGLDRAWBUFFERSPROC gl3wDrawBuffers = mockgl3wDrawBuffers;

// void  mockgl3wDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices)
// {
//     return getMock()->gl3wDrawElements(mode, count, type, indices);
// }
// PFNGLDRAWELEMENTSPROC gl3wDrawElements = mockgl3wDrawElements;

// void  mockgl3wDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex)
// {
//     return getMock()->gl3wDrawElementsBaseVertex(mode, count, type, indices, basevertex);
// }
// PFNGLDRAWELEMENTSBASEVERTEXPROC gl3wDrawElementsBaseVertex = mockgl3wDrawElementsBaseVertex;

// void  mockgl3wDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect)
// {
//     return getMock()->gl3wDrawElementsIndirect(mode, type, indirect);
// }
// PFNGLDRAWELEMENTSINDIRECTPROC gl3wDrawElementsIndirect = mockgl3wDrawElementsIndirect;

// void  mockgl3wDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount)
// {
//     return getMock()->gl3wDrawElementsInstanced(mode, count, type, indices, instancecount);
// }
// PFNGLDRAWELEMENTSINSTANCEDPROC gl3wDrawElementsInstanced = mockgl3wDrawElementsInstanced;

// void  mockgl3wDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance)
// {
//     return getMock()->gl3wDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
// }
// PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC gl3wDrawElementsInstancedBaseInstance = mockgl3wDrawElementsInstancedBaseInstance;

// void  mockgl3wDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex)
// {
//     return getMock()->gl3wDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
// }
// PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC gl3wDrawElementsInstancedBaseVertex = mockgl3wDrawElementsInstancedBaseVertex;

// void  mockgl3wDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance)
// {
//     return getMock()->gl3wDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
// }
// PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC gl3wDrawElementsInstancedBaseVertexBaseInstance = mockgl3wDrawElementsInstancedBaseVertexBaseInstance;

// void  mockgl3wDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
// {
//     return getMock()->gl3wDrawRangeElements(mode, start, end, count, type, indices);
// }
// PFNGLDRAWRANGEELEMENTSPROC gl3wDrawRangeElements = mockgl3wDrawRangeElements;

// void  mockgl3wDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex)
// {
//     return getMock()->gl3wDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
// }
// PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC gl3wDrawRangeElementsBaseVertex = mockgl3wDrawRangeElementsBaseVertex;

// void  mockgl3wDrawTransformFeedback(GLenum mode, GLuint id)
// {
//     return getMock()->gl3wDrawTransformFeedback(mode, id);
// }
// PFNGLDRAWTRANSFORMFEEDBACKPROC gl3wDrawTransformFeedback = mockgl3wDrawTransformFeedback;

// void  mockgl3wDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
// {
//     return getMock()->gl3wDrawTransformFeedbackInstanced(mode, id, instancecount);
// }
// PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC gl3wDrawTransformFeedbackInstanced = mockgl3wDrawTransformFeedbackInstanced;

// void  mockgl3wDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
// {
//     return getMock()->gl3wDrawTransformFeedbackStream(mode, id, stream);
// }
// PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC gl3wDrawTransformFeedbackStream = mockgl3wDrawTransformFeedbackStream;

// void  mockgl3wDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
// {
//     return getMock()->gl3wDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
// }
// PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC gl3wDrawTransformFeedbackStreamInstanced = mockgl3wDrawTransformFeedbackStreamInstanced;

// void  mockgl3wEnable(GLenum cap)
// {
//     return getMock()->gl3wEnable(cap);
// }
// PFNGLENABLEPROC gl3wEnable = mockgl3wEnable;

// void  mockgl3wEnableVertexArrayAttrib(GLuint vaobj, GLuint index)
// {
//     return getMock()->gl3wEnableVertexArrayAttrib(vaobj, index);
// }
// PFNGLENABLEVERTEXARRAYATTRIBPROC gl3wEnableVertexArrayAttrib = mockgl3wEnableVertexArrayAttrib;

// void  mockgl3wEnableVertexAttribArray(GLuint index)
// {
//     return getMock()->gl3wEnableVertexAttribArray(index);
// }
// PFNGLENABLEVERTEXATTRIBARRAYPROC gl3wEnableVertexAttribArray = mockgl3wEnableVertexAttribArray;

// void  mockgl3wEnablei(GLenum target, GLuint index)
// {
//     return getMock()->gl3wEnablei(target, index);
// }
// PFNGLENABLEIPROC gl3wEnablei = mockgl3wEnablei;

// void  mockgl3wEndConditionalRender()
// {
//     return getMock()->gl3wEndConditionalRender();
// }
// PFNGLENDCONDITIONALRENDERPROC gl3wEndConditionalRender = mockgl3wEndConditionalRender;

// void  mockgl3wEndQuery(GLenum target)
// {
//     return getMock()->gl3wEndQuery(target);
// }
// PFNGLENDQUERYPROC gl3wEndQuery = mockgl3wEndQuery;

// void  mockgl3wEndQueryIndexed(GLenum target, GLuint index)
// {
//     return getMock()->gl3wEndQueryIndexed(target, index);
// }
// PFNGLENDQUERYINDEXEDPROC gl3wEndQueryIndexed = mockgl3wEndQueryIndexed;

// void  mockgl3wEndTransformFeedback()
// {
//     return getMock()->gl3wEndTransformFeedback();
// }
// PFNGLENDTRANSFORMFEEDBACKPROC gl3wEndTransformFeedback = mockgl3wEndTransformFeedback;

// struct __GLsync * mockgl3wFenceSync(GLenum condition, GLbitfield flags)
// {
//     return getMock()->gl3wFenceSync(condition, flags);
// }
// PFNGLFENCESYNCPROC gl3wFenceSync = mockgl3wFenceSync;

// void  mockgl3wFinish()
// {
//     return getMock()->gl3wFinish();
// }
// PFNGLFINISHPROC gl3wFinish = mockgl3wFinish;

// void  mockgl3wFlush()
// {
//     return getMock()->gl3wFlush();
// }
// PFNGLFLUSHPROC gl3wFlush = mockgl3wFlush;

// void  mockgl3wFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
// {
//     return getMock()->gl3wFlushMappedBufferRange(target, offset, length);
// }
// PFNGLFLUSHMAPPEDBUFFERRANGEPROC gl3wFlushMappedBufferRange = mockgl3wFlushMappedBufferRange;

// void  mockgl3wFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizei length)
// {
//     return getMock()->gl3wFlushMappedNamedBufferRange(buffer, offset, length);
// }
// PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC gl3wFlushMappedNamedBufferRange = mockgl3wFlushMappedNamedBufferRange;

// void  mockgl3wFramebufferParameteri(GLenum target, GLenum pname, GLint param)
// {
//     return getMock()->gl3wFramebufferParameteri(target, pname, param);
// }
// PFNGLFRAMEBUFFERPARAMETERIPROC gl3wFramebufferParameteri = mockgl3wFramebufferParameteri;

// void  mockgl3wFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
// {
//     return getMock()->gl3wFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
// }
// PFNGLFRAMEBUFFERRENDERBUFFERPROC gl3wFramebufferRenderbuffer = mockgl3wFramebufferRenderbuffer;

// void  mockgl3wFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
// {
//     return getMock()->gl3wFramebufferTexture(target, attachment, texture, level);
// }
// PFNGLFRAMEBUFFERTEXTUREPROC gl3wFramebufferTexture = mockgl3wFramebufferTexture;

// void  mockgl3wFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
// {
//     return getMock()->gl3wFramebufferTexture1D(target, attachment, textarget, texture, level);
// }
// PFNGLFRAMEBUFFERTEXTURE1DPROC gl3wFramebufferTexture1D = mockgl3wFramebufferTexture1D;

// void  mockgl3wFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
// {
//     return getMock()->gl3wFramebufferTexture2D(target, attachment, textarget, texture, level);
// }
// PFNGLFRAMEBUFFERTEXTURE2DPROC gl3wFramebufferTexture2D = mockgl3wFramebufferTexture2D;

// void  mockgl3wFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
// {
//     return getMock()->gl3wFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
// }
// PFNGLFRAMEBUFFERTEXTURE3DPROC gl3wFramebufferTexture3D = mockgl3wFramebufferTexture3D;

// void  mockgl3wFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
// {
//     return getMock()->gl3wFramebufferTextureLayer(target, attachment, texture, level, layer);
// }
// PFNGLFRAMEBUFFERTEXTURELAYERPROC gl3wFramebufferTextureLayer = mockgl3wFramebufferTextureLayer;

// void  mockgl3wFrontFace(GLenum mode)
// {
//     return getMock()->gl3wFrontFace(mode);
// }
// PFNGLFRONTFACEPROC gl3wFrontFace = mockgl3wFrontFace;

// void  mockgl3wGenBuffers(GLsizei n, GLuint * buffers)
// {
//     return getMock()->gl3wGenBuffers(n, buffers);
// }
// PFNGLGENBUFFERSPROC gl3wGenBuffers = mockgl3wGenBuffers;

// void  mockgl3wGenFramebuffers(GLsizei n, GLuint * framebuffers)
// {
//     return getMock()->gl3wGenFramebuffers(n, framebuffers);
// }
// PFNGLGENFRAMEBUFFERSPROC gl3wGenFramebuffers = mockgl3wGenFramebuffers;

// void  mockgl3wGenProgramPipelines(GLsizei n, GLuint * pipelines)
// {
//     return getMock()->gl3wGenProgramPipelines(n, pipelines);
// }
// PFNGLGENPROGRAMPIPELINESPROC gl3wGenProgramPipelines = mockgl3wGenProgramPipelines;

// void  mockgl3wGenQueries(GLsizei n, GLuint * ids)
// {
//     return getMock()->gl3wGenQueries(n, ids);
// }
// PFNGLGENQUERIESPROC gl3wGenQueries = mockgl3wGenQueries;

// void  mockgl3wGenRenderbuffers(GLsizei n, GLuint * renderbuffers)
// {
//     return getMock()->gl3wGenRenderbuffers(n, renderbuffers);
// }
// PFNGLGENRENDERBUFFERSPROC gl3wGenRenderbuffers = mockgl3wGenRenderbuffers;

// void  mockgl3wGenSamplers(GLsizei count, GLuint * samplers)
// {
//     return getMock()->gl3wGenSamplers(count, samplers);
// }
// PFNGLGENSAMPLERSPROC gl3wGenSamplers = mockgl3wGenSamplers;

// void  mockgl3wGenTextures(GLsizei n, GLuint * textures)
// {
//     return getMock()->gl3wGenTextures(n, textures);
// }
// PFNGLGENTEXTURESPROC gl3wGenTextures = mockgl3wGenTextures;

// void  mockgl3wGenTransformFeedbacks(GLsizei n, GLuint * ids)
// {
//     return getMock()->gl3wGenTransformFeedbacks(n, ids);
// }
// PFNGLGENTRANSFORMFEEDBACKSPROC gl3wGenTransformFeedbacks = mockgl3wGenTransformFeedbacks;

// void  mockgl3wGenVertexArrays(GLsizei n, GLuint * arrays)
// {
//     return getMock()->gl3wGenVertexArrays(n, arrays);
// }
// PFNGLGENVERTEXARRAYSPROC gl3wGenVertexArrays = mockgl3wGenVertexArrays;

// void  mockgl3wGenerateMipmap(GLenum target)
// {
//     return getMock()->gl3wGenerateMipmap(target);
// }
// PFNGLGENERATEMIPMAPPROC gl3wGenerateMipmap = mockgl3wGenerateMipmap;

// void  mockgl3wGenerateTextureMipmap(GLuint texture)
// {
//     return getMock()->gl3wGenerateTextureMipmap(texture);
// }
// PFNGLGENERATETEXTUREMIPMAPPROC gl3wGenerateTextureMipmap = mockgl3wGenerateTextureMipmap;

// void  mockgl3wGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
// }
// PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC gl3wGetActiveAtomicCounterBufferiv = mockgl3wGetActiveAtomicCounterBufferiv;

// void  mockgl3wGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
// {
//     return getMock()->gl3wGetActiveAttrib(program, index, bufSize, length, size, type, name);
// }
// PFNGLGETACTIVEATTRIBPROC gl3wGetActiveAttrib = mockgl3wGetActiveAttrib;

// void  mockgl3wGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
// {
//     return getMock()->gl3wGetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
// }
// PFNGLGETACTIVESUBROUTINENAMEPROC gl3wGetActiveSubroutineName = mockgl3wGetActiveSubroutineName;

// void  mockgl3wGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
// {
//     return getMock()->gl3wGetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
// }
// PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC gl3wGetActiveSubroutineUniformName = mockgl3wGetActiveSubroutineUniformName;

// void  mockgl3wGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values)
// {
//     return getMock()->gl3wGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
// }
// PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC gl3wGetActiveSubroutineUniformiv = mockgl3wGetActiveSubroutineUniformiv;

// void  mockgl3wGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
// {
//     return getMock()->gl3wGetActiveUniform(program, index, bufSize, length, size, type, name);
// }
// PFNGLGETACTIVEUNIFORMPROC gl3wGetActiveUniform = mockgl3wGetActiveUniform;

// void  mockgl3wGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
// {
//     return getMock()->gl3wGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
// }
// PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC gl3wGetActiveUniformBlockName = mockgl3wGetActiveUniformBlockName;

// void  mockgl3wGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
// }
// PFNGLGETACTIVEUNIFORMBLOCKIVPROC gl3wGetActiveUniformBlockiv = mockgl3wGetActiveUniformBlockiv;

// void  mockgl3wGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
// {
//     return getMock()->gl3wGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
// }
// PFNGLGETACTIVEUNIFORMNAMEPROC gl3wGetActiveUniformName = mockgl3wGetActiveUniformName;

// void  mockgl3wGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
// }
// PFNGLGETACTIVEUNIFORMSIVPROC gl3wGetActiveUniformsiv = mockgl3wGetActiveUniformsiv;

// void  mockgl3wGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
// {
//     return getMock()->gl3wGetAttachedShaders(program, maxCount, count, shaders);
// }
// PFNGLGETATTACHEDSHADERSPROC gl3wGetAttachedShaders = mockgl3wGetAttachedShaders;

// int  mockgl3wGetAttribLocation(GLuint program, const GLchar * name)
// {
//     return getMock()->gl3wGetAttribLocation(program, name);
// }
// PFNGLGETATTRIBLOCATIONPROC gl3wGetAttribLocation = mockgl3wGetAttribLocation;

// void  mockgl3wGetBooleani_v(GLenum target, GLuint index, GLboolean * data)
// {
//     return getMock()->gl3wGetBooleani_v(target, index, data);
// }
// PFNGLGETBOOLEANI_VPROC gl3wGetBooleani_v = mockgl3wGetBooleani_v;

// void  mockgl3wGetBooleanv(GLenum pname, GLboolean * data)
// {
//     return getMock()->gl3wGetBooleanv(pname, data);
// }
// PFNGLGETBOOLEANVPROC gl3wGetBooleanv = mockgl3wGetBooleanv;

// void  mockgl3wGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params)
// {
//     return getMock()->gl3wGetBufferParameteri64v(target, pname, params);
// }
// PFNGLGETBUFFERPARAMETERI64VPROC gl3wGetBufferParameteri64v = mockgl3wGetBufferParameteri64v;

// void  mockgl3wGetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetBufferParameteriv(target, pname, params);
// }
// PFNGLGETBUFFERPARAMETERIVPROC gl3wGetBufferParameteriv = mockgl3wGetBufferParameteriv;

// void  mockgl3wGetBufferPointerv(GLenum target, GLenum pname, void ** params)
// {
//     return getMock()->gl3wGetBufferPointerv(target, pname, params);
// }
// PFNGLGETBUFFERPOINTERVPROC gl3wGetBufferPointerv = mockgl3wGetBufferPointerv;

// void  mockgl3wGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data)
// {
//     return getMock()->gl3wGetBufferSubData(target, offset, size, data);
// }
// PFNGLGETBUFFERSUBDATAPROC gl3wGetBufferSubData = mockgl3wGetBufferSubData;

// void  mockgl3wGetCompressedTexImage(GLenum target, GLint level, void * img)
// {
//     return getMock()->gl3wGetCompressedTexImage(target, level, img);
// }
// PFNGLGETCOMPRESSEDTEXIMAGEPROC gl3wGetCompressedTexImage = mockgl3wGetCompressedTexImage;

// void  mockgl3wGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels)
// {
//     return getMock()->gl3wGetCompressedTextureImage(texture, level, bufSize, pixels);
// }
// PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC gl3wGetCompressedTextureImage = mockgl3wGetCompressedTextureImage;

// void  mockgl3wGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels)
// {
//     return getMock()->gl3wGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
// }
// PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC gl3wGetCompressedTextureSubImage = mockgl3wGetCompressedTextureSubImage;

// unsigned int  mockgl3wGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
// {
//     return getMock()->gl3wGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
// }
// PFNGLGETDEBUGMESSAGELOGPROC gl3wGetDebugMessageLog = mockgl3wGetDebugMessageLog;

// unsigned int  mockgl3wGetDebugMessageLogARB(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
// {
//     return getMock()->gl3wGetDebugMessageLogARB(count, bufSize, sources, types, ids, severities, lengths, messageLog);
// }
// PFNGLGETDEBUGMESSAGELOGARBPROC gl3wGetDebugMessageLogARB = mockgl3wGetDebugMessageLogARB;

// void  mockgl3wGetDoublei_v(GLenum target, GLuint index, GLdouble * data)
// {
//     return getMock()->gl3wGetDoublei_v(target, index, data);
// }
// PFNGLGETDOUBLEI_VPROC gl3wGetDoublei_v = mockgl3wGetDoublei_v;

// void  mockgl3wGetDoublev(GLenum pname, GLdouble * data)
// {
//     return getMock()->gl3wGetDoublev(pname, data);
// }
// PFNGLGETDOUBLEVPROC gl3wGetDoublev = mockgl3wGetDoublev;

// unsigned int  mockgl3wGetError()
// {
//     return getMock()->gl3wGetError();
// }
// PFNGLGETERRORPROC gl3wGetError = mockgl3wGetError;

// void  mockgl3wGetFloati_v(GLenum target, GLuint index, GLfloat * data)
// {
//     return getMock()->gl3wGetFloati_v(target, index, data);
// }
// PFNGLGETFLOATI_VPROC gl3wGetFloati_v = mockgl3wGetFloati_v;

// void  mockgl3wGetFloatv(GLenum pname, GLfloat * data)
// {
//     return getMock()->gl3wGetFloatv(pname, data);
// }
// PFNGLGETFLOATVPROC gl3wGetFloatv = mockgl3wGetFloatv;

// int  mockgl3wGetFragDataIndex(GLuint program, const GLchar * name)
// {
//     return getMock()->gl3wGetFragDataIndex(program, name);
// }
// PFNGLGETFRAGDATAINDEXPROC gl3wGetFragDataIndex = mockgl3wGetFragDataIndex;

// int  mockgl3wGetFragDataLocation(GLuint program, const GLchar * name)
// {
//     return getMock()->gl3wGetFragDataLocation(program, name);
// }
// PFNGLGETFRAGDATALOCATIONPROC gl3wGetFragDataLocation = mockgl3wGetFragDataLocation;

// void  mockgl3wGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
// }
// PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC gl3wGetFramebufferAttachmentParameteriv = mockgl3wGetFramebufferAttachmentParameteriv;

// void  mockgl3wGetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetFramebufferParameteriv(target, pname, params);
// }
// PFNGLGETFRAMEBUFFERPARAMETERIVPROC gl3wGetFramebufferParameteriv = mockgl3wGetFramebufferParameteriv;

// unsigned int  mockgl3wGetGraphicsResetStatus()
// {
//     return getMock()->gl3wGetGraphicsResetStatus();
// }
// PFNGLGETGRAPHICSRESETSTATUSPROC gl3wGetGraphicsResetStatus = mockgl3wGetGraphicsResetStatus;

// unsigned int  mockgl3wGetGraphicsResetStatusARB()
// {
//     return getMock()->gl3wGetGraphicsResetStatusARB();
// }
// PFNGLGETGRAPHICSRESETSTATUSARBPROC gl3wGetGraphicsResetStatusARB = mockgl3wGetGraphicsResetStatusARB;

// unsigned long  mockgl3wGetImageHandleARB(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format)
// {
//     return getMock()->gl3wGetImageHandleARB(texture, level, layered, layer, format);
// }
// PFNGLGETIMAGEHANDLEARBPROC gl3wGetImageHandleARB = mockgl3wGetImageHandleARB;

// void  mockgl3wGetInteger64i_v(GLenum target, GLuint index, GLint64 * data)
// {
//     return getMock()->gl3wGetInteger64i_v(target, index, data);
// }
// PFNGLGETINTEGER64I_VPROC gl3wGetInteger64i_v = mockgl3wGetInteger64i_v;

// void  mockgl3wGetInteger64v(GLenum pname, GLint64 * data)
// {
//     return getMock()->gl3wGetInteger64v(pname, data);
// }
// PFNGLGETINTEGER64VPROC gl3wGetInteger64v = mockgl3wGetInteger64v;

// void  mockgl3wGetIntegeri_v(GLenum target, GLuint index, GLint * data)
// {
//     return getMock()->gl3wGetIntegeri_v(target, index, data);
// }
// PFNGLGETINTEGERI_VPROC gl3wGetIntegeri_v = mockgl3wGetIntegeri_v;

// void  mockgl3wGetIntegerv(GLenum pname, GLint * data)
// {
//     return getMock()->gl3wGetIntegerv(pname, data);
// }
// PFNGLGETINTEGERVPROC gl3wGetIntegerv = mockgl3wGetIntegerv;

// void  mockgl3wGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params)
// {
//     return getMock()->gl3wGetInternalformati64v(target, internalformat, pname, bufSize, params);
// }
// PFNGLGETINTERNALFORMATI64VPROC gl3wGetInternalformati64v = mockgl3wGetInternalformati64v;

// void  mockgl3wGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params)
// {
//     return getMock()->gl3wGetInternalformativ(target, internalformat, pname, bufSize, params);
// }
// PFNGLGETINTERNALFORMATIVPROC gl3wGetInternalformativ = mockgl3wGetInternalformativ;

// void  mockgl3wGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val)
// {
//     return getMock()->gl3wGetMultisamplefv(pname, index, val);
// }
// PFNGLGETMULTISAMPLEFVPROC gl3wGetMultisamplefv = mockgl3wGetMultisamplefv;

// void  mockgl3wGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params)
// {
//     return getMock()->gl3wGetNamedBufferParameteri64v(buffer, pname, params);
// }
// PFNGLGETNAMEDBUFFERPARAMETERI64VPROC gl3wGetNamedBufferParameteri64v = mockgl3wGetNamedBufferParameteri64v;

// void  mockgl3wGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetNamedBufferParameteriv(buffer, pname, params);
// }
// PFNGLGETNAMEDBUFFERPARAMETERIVPROC gl3wGetNamedBufferParameteriv = mockgl3wGetNamedBufferParameteriv;

// void  mockgl3wGetNamedBufferPointerv(GLuint buffer, GLenum pname, void ** params)
// {
//     return getMock()->gl3wGetNamedBufferPointerv(buffer, pname, params);
// }
// PFNGLGETNAMEDBUFFERPOINTERVPROC gl3wGetNamedBufferPointerv = mockgl3wGetNamedBufferPointerv;

// void  mockgl3wGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizei size, void * data)
// {
//     return getMock()->gl3wGetNamedBufferSubData(buffer, offset, size, data);
// }
// PFNGLGETNAMEDBUFFERSUBDATAPROC gl3wGetNamedBufferSubData = mockgl3wGetNamedBufferSubData;

// void  mockgl3wGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
// }
// PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC gl3wGetNamedFramebufferAttachmentParameteriv = mockgl3wGetNamedFramebufferAttachmentParameteriv;

// void  mockgl3wGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param)
// {
//     return getMock()->gl3wGetNamedFramebufferParameteriv(framebuffer, pname, param);
// }
// PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC gl3wGetNamedFramebufferParameteriv = mockgl3wGetNamedFramebufferParameteriv;

// void  mockgl3wGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetNamedRenderbufferParameteriv(renderbuffer, pname, params);
// }
// PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC gl3wGetNamedRenderbufferParameteriv = mockgl3wGetNamedRenderbufferParameteriv;

// void  mockgl3wGetNamedStringARB(GLint namelen, const GLchar * name, GLsizei bufSize, GLint * stringlen, GLchar * string)
// {
//     return getMock()->gl3wGetNamedStringARB(namelen, name, bufSize, stringlen, string);
// }
// PFNGLGETNAMEDSTRINGARBPROC gl3wGetNamedStringARB = mockgl3wGetNamedStringARB;

// void  mockgl3wGetNamedStringivARB(GLint namelen, const GLchar * name, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetNamedStringivARB(namelen, name, pname, params);
// }
// PFNGLGETNAMEDSTRINGIVARBPROC gl3wGetNamedStringivARB = mockgl3wGetNamedStringivARB;

// void  mockgl3wGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label)
// {
//     return getMock()->gl3wGetObjectLabel(identifier, name, bufSize, length, label);
// }
// PFNGLGETOBJECTLABELPROC gl3wGetObjectLabel = mockgl3wGetObjectLabel;

// void  mockgl3wGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label)
// {
//     return getMock()->gl3wGetObjectPtrLabel(ptr, bufSize, length, label);
// }
// PFNGLGETOBJECTPTRLABELPROC gl3wGetObjectPtrLabel = mockgl3wGetObjectPtrLabel;

// void  mockgl3wGetPointerv(GLenum pname, void ** params)
// {
//     return getMock()->gl3wGetPointerv(pname, params);
// }
// PFNGLGETPOINTERVPROC gl3wGetPointerv = mockgl3wGetPointerv;

// void  mockgl3wGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary)
// {
//     return getMock()->gl3wGetProgramBinary(program, bufSize, length, binaryFormat, binary);
// }
// PFNGLGETPROGRAMBINARYPROC gl3wGetProgramBinary = mockgl3wGetProgramBinary;

// void  mockgl3wGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
// {
//     return getMock()->gl3wGetProgramInfoLog(program, bufSize, length, infoLog);
// }
// PFNGLGETPROGRAMINFOLOGPROC gl3wGetProgramInfoLog = mockgl3wGetProgramInfoLog;

// void  mockgl3wGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetProgramInterfaceiv(program, programInterface, pname, params);
// }
// PFNGLGETPROGRAMINTERFACEIVPROC gl3wGetProgramInterfaceiv = mockgl3wGetProgramInterfaceiv;

// void  mockgl3wGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
// {
//     return getMock()->gl3wGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
// }
// PFNGLGETPROGRAMPIPELINEINFOLOGPROC gl3wGetProgramPipelineInfoLog = mockgl3wGetProgramPipelineInfoLog;

// void  mockgl3wGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetProgramPipelineiv(pipeline, pname, params);
// }
// PFNGLGETPROGRAMPIPELINEIVPROC gl3wGetProgramPipelineiv = mockgl3wGetProgramPipelineiv;

// unsigned int  mockgl3wGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name)
// {
//     return getMock()->gl3wGetProgramResourceIndex(program, programInterface, name);
// }
// PFNGLGETPROGRAMRESOURCEINDEXPROC gl3wGetProgramResourceIndex = mockgl3wGetProgramResourceIndex;

// int  mockgl3wGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name)
// {
//     return getMock()->gl3wGetProgramResourceLocation(program, programInterface, name);
// }
// PFNGLGETPROGRAMRESOURCELOCATIONPROC gl3wGetProgramResourceLocation = mockgl3wGetProgramResourceLocation;

// int  mockgl3wGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name)
// {
//     return getMock()->gl3wGetProgramResourceLocationIndex(program, programInterface, name);
// }
// PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC gl3wGetProgramResourceLocationIndex = mockgl3wGetProgramResourceLocationIndex;

// void  mockgl3wGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name)
// {
//     return getMock()->gl3wGetProgramResourceName(program, programInterface, index, bufSize, length, name);
// }
// PFNGLGETPROGRAMRESOURCENAMEPROC gl3wGetProgramResourceName = mockgl3wGetProgramResourceName;

// void  mockgl3wGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params)
// {
//     return getMock()->gl3wGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
// }
// PFNGLGETPROGRAMRESOURCEIVPROC gl3wGetProgramResourceiv = mockgl3wGetProgramResourceiv;

// void  mockgl3wGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values)
// {
//     return getMock()->gl3wGetProgramStageiv(program, shadertype, pname, values);
// }
// PFNGLGETPROGRAMSTAGEIVPROC gl3wGetProgramStageiv = mockgl3wGetProgramStageiv;

// void  mockgl3wGetProgramiv(GLuint program, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetProgramiv(program, pname, params);
// }
// PFNGLGETPROGRAMIVPROC gl3wGetProgramiv = mockgl3wGetProgramiv;

// void  mockgl3wGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetQueryIndexediv(target, index, pname, params);
// }
// PFNGLGETQUERYINDEXEDIVPROC gl3wGetQueryIndexediv = mockgl3wGetQueryIndexediv;

// void  mockgl3wGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params)
// {
//     return getMock()->gl3wGetQueryObjecti64v(id, pname, params);
// }
// PFNGLGETQUERYOBJECTI64VPROC gl3wGetQueryObjecti64v = mockgl3wGetQueryObjecti64v;

// void  mockgl3wGetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetQueryObjectiv(id, pname, params);
// }
// PFNGLGETQUERYOBJECTIVPROC gl3wGetQueryObjectiv = mockgl3wGetQueryObjectiv;

// void  mockgl3wGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params)
// {
//     return getMock()->gl3wGetQueryObjectui64v(id, pname, params);
// }
// PFNGLGETQUERYOBJECTUI64VPROC gl3wGetQueryObjectui64v = mockgl3wGetQueryObjectui64v;

// void  mockgl3wGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
// {
//     return getMock()->gl3wGetQueryObjectuiv(id, pname, params);
// }
// PFNGLGETQUERYOBJECTUIVPROC gl3wGetQueryObjectuiv = mockgl3wGetQueryObjectuiv;

// void  mockgl3wGetQueryiv(GLenum target, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetQueryiv(target, pname, params);
// }
// PFNGLGETQUERYIVPROC gl3wGetQueryiv = mockgl3wGetQueryiv;

// void  mockgl3wGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetRenderbufferParameteriv(target, pname, params);
// }
// PFNGLGETRENDERBUFFERPARAMETERIVPROC gl3wGetRenderbufferParameteriv = mockgl3wGetRenderbufferParameteriv;

// void  mockgl3wGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetSamplerParameterIiv(sampler, pname, params);
// }
// PFNGLGETSAMPLERPARAMETERIIVPROC gl3wGetSamplerParameterIiv = mockgl3wGetSamplerParameterIiv;

// void  mockgl3wGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params)
// {
//     return getMock()->gl3wGetSamplerParameterIuiv(sampler, pname, params);
// }
// PFNGLGETSAMPLERPARAMETERIUIVPROC gl3wGetSamplerParameterIuiv = mockgl3wGetSamplerParameterIuiv;

// void  mockgl3wGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params)
// {
//     return getMock()->gl3wGetSamplerParameterfv(sampler, pname, params);
// }
// PFNGLGETSAMPLERPARAMETERFVPROC gl3wGetSamplerParameterfv = mockgl3wGetSamplerParameterfv;

// void  mockgl3wGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetSamplerParameteriv(sampler, pname, params);
// }
// PFNGLGETSAMPLERPARAMETERIVPROC gl3wGetSamplerParameteriv = mockgl3wGetSamplerParameteriv;

// void  mockgl3wGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
// {
//     return getMock()->gl3wGetShaderInfoLog(shader, bufSize, length, infoLog);
// }
// PFNGLGETSHADERINFOLOGPROC gl3wGetShaderInfoLog = mockgl3wGetShaderInfoLog;

// void  mockgl3wGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision)
// {
//     return getMock()->gl3wGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
// }
// PFNGLGETSHADERPRECISIONFORMATPROC gl3wGetShaderPrecisionFormat = mockgl3wGetShaderPrecisionFormat;

// void  mockgl3wGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
// {
//     return getMock()->gl3wGetShaderSource(shader, bufSize, length, source);
// }
// PFNGLGETSHADERSOURCEPROC gl3wGetShaderSource = mockgl3wGetShaderSource;

// void  mockgl3wGetShaderiv(GLuint shader, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetShaderiv(shader, pname, params);
// }
// PFNGLGETSHADERIVPROC gl3wGetShaderiv = mockgl3wGetShaderiv;

// const unsigned char * mockgl3wGetString(GLenum name)
// {
//     return getMock()->gl3wGetString(name);
// }
// PFNGLGETSTRINGPROC gl3wGetString = mockgl3wGetString;

// const unsigned char * mockgl3wGetStringi(GLenum name, GLuint index)
// {
//     return getMock()->gl3wGetStringi(name, index);
// }
// PFNGLGETSTRINGIPROC gl3wGetStringi = mockgl3wGetStringi;

// unsigned int  mockgl3wGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name)
// {
//     return getMock()->gl3wGetSubroutineIndex(program, shadertype, name);
// }
// PFNGLGETSUBROUTINEINDEXPROC gl3wGetSubroutineIndex = mockgl3wGetSubroutineIndex;

// int  mockgl3wGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name)
// {
//     return getMock()->gl3wGetSubroutineUniformLocation(program, shadertype, name);
// }
// PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC gl3wGetSubroutineUniformLocation = mockgl3wGetSubroutineUniformLocation;

// void  mockgl3wGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
// {
//     return getMock()->gl3wGetSynciv(sync, pname, bufSize, length, values);
// }
// PFNGLGETSYNCIVPROC gl3wGetSynciv = mockgl3wGetSynciv;

// void  mockgl3wGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels)
// {
//     return getMock()->gl3wGetTexImage(target, level, format, type, pixels);
// }
// PFNGLGETTEXIMAGEPROC gl3wGetTexImage = mockgl3wGetTexImage;

// void  mockgl3wGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params)
// {
//     return getMock()->gl3wGetTexLevelParameterfv(target, level, pname, params);
// }
// PFNGLGETTEXLEVELPARAMETERFVPROC gl3wGetTexLevelParameterfv = mockgl3wGetTexLevelParameterfv;

// void  mockgl3wGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetTexLevelParameteriv(target, level, pname, params);
// }
// PFNGLGETTEXLEVELPARAMETERIVPROC gl3wGetTexLevelParameteriv = mockgl3wGetTexLevelParameteriv;

// void  mockgl3wGetTexParameterIiv(GLenum target, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetTexParameterIiv(target, pname, params);
// }
// PFNGLGETTEXPARAMETERIIVPROC gl3wGetTexParameterIiv = mockgl3wGetTexParameterIiv;

// void  mockgl3wGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params)
// {
//     return getMock()->gl3wGetTexParameterIuiv(target, pname, params);
// }
// PFNGLGETTEXPARAMETERIUIVPROC gl3wGetTexParameterIuiv = mockgl3wGetTexParameterIuiv;

// void  mockgl3wGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params)
// {
//     return getMock()->gl3wGetTexParameterfv(target, pname, params);
// }
// PFNGLGETTEXPARAMETERFVPROC gl3wGetTexParameterfv = mockgl3wGetTexParameterfv;

// void  mockgl3wGetTexParameteriv(GLenum target, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetTexParameteriv(target, pname, params);
// }
// PFNGLGETTEXPARAMETERIVPROC gl3wGetTexParameteriv = mockgl3wGetTexParameteriv;

// unsigned long  mockgl3wGetTextureHandleARB(GLuint texture)
// {
//     return getMock()->gl3wGetTextureHandleARB(texture);
// }
// PFNGLGETTEXTUREHANDLEARBPROC gl3wGetTextureHandleARB = mockgl3wGetTextureHandleARB;

// void  mockgl3wGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
// {
//     return getMock()->gl3wGetTextureImage(texture, level, format, type, bufSize, pixels);
// }
// PFNGLGETTEXTUREIMAGEPROC gl3wGetTextureImage = mockgl3wGetTextureImage;

// void  mockgl3wGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params)
// {
//     return getMock()->gl3wGetTextureLevelParameterfv(texture, level, pname, params);
// }
// PFNGLGETTEXTURELEVELPARAMETERFVPROC gl3wGetTextureLevelParameterfv = mockgl3wGetTextureLevelParameterfv;

// void  mockgl3wGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetTextureLevelParameteriv(texture, level, pname, params);
// }
// PFNGLGETTEXTURELEVELPARAMETERIVPROC gl3wGetTextureLevelParameteriv = mockgl3wGetTextureLevelParameteriv;

// void  mockgl3wGetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetTextureParameterIiv(texture, pname, params);
// }
// PFNGLGETTEXTUREPARAMETERIIVPROC gl3wGetTextureParameterIiv = mockgl3wGetTextureParameterIiv;

// void  mockgl3wGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params)
// {
//     return getMock()->gl3wGetTextureParameterIuiv(texture, pname, params);
// }
// PFNGLGETTEXTUREPARAMETERIUIVPROC gl3wGetTextureParameterIuiv = mockgl3wGetTextureParameterIuiv;

// void  mockgl3wGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params)
// {
//     return getMock()->gl3wGetTextureParameterfv(texture, pname, params);
// }
// PFNGLGETTEXTUREPARAMETERFVPROC gl3wGetTextureParameterfv = mockgl3wGetTextureParameterfv;

// void  mockgl3wGetTextureParameteriv(GLuint texture, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetTextureParameteriv(texture, pname, params);
// }
// PFNGLGETTEXTUREPARAMETERIVPROC gl3wGetTextureParameteriv = mockgl3wGetTextureParameteriv;

// unsigned long  mockgl3wGetTextureSamplerHandleARB(GLuint texture, GLuint sampler)
// {
//     return getMock()->gl3wGetTextureSamplerHandleARB(texture, sampler);
// }
// PFNGLGETTEXTURESAMPLERHANDLEARBPROC gl3wGetTextureSamplerHandleARB = mockgl3wGetTextureSamplerHandleARB;

// void  mockgl3wGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
// {
//     return getMock()->gl3wGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
// }
// PFNGLGETTRANSFORMFEEDBACKVARYINGPROC gl3wGetTransformFeedbackVarying = mockgl3wGetTransformFeedbackVarying;

// void  mockgl3wGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param)
// {
//     return getMock()->gl3wGetTransformFeedbacki64_v(xfb, pname, index, param);
// }
// PFNGLGETTRANSFORMFEEDBACKI64_VPROC gl3wGetTransformFeedbacki64_v = mockgl3wGetTransformFeedbacki64_v;

// void  mockgl3wGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param)
// {
//     return getMock()->gl3wGetTransformFeedbacki_v(xfb, pname, index, param);
// }
// PFNGLGETTRANSFORMFEEDBACKI_VPROC gl3wGetTransformFeedbacki_v = mockgl3wGetTransformFeedbacki_v;

// void  mockgl3wGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param)
// {
//     return getMock()->gl3wGetTransformFeedbackiv(xfb, pname, param);
// }
// PFNGLGETTRANSFORMFEEDBACKIVPROC gl3wGetTransformFeedbackiv = mockgl3wGetTransformFeedbackiv;

// unsigned int  mockgl3wGetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName)
// {
//     return getMock()->gl3wGetUniformBlockIndex(program, uniformBlockName);
// }
// PFNGLGETUNIFORMBLOCKINDEXPROC gl3wGetUniformBlockIndex = mockgl3wGetUniformBlockIndex;

// void  mockgl3wGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const * uniformNames, GLuint * uniformIndices)
// {
//     return getMock()->gl3wGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
// }
// PFNGLGETUNIFORMINDICESPROC gl3wGetUniformIndices = mockgl3wGetUniformIndices;

// int  mockgl3wGetUniformLocation(GLuint program, const GLchar * name)
// {
//     return getMock()->gl3wGetUniformLocation(program, name);
// }
// PFNGLGETUNIFORMLOCATIONPROC gl3wGetUniformLocation = mockgl3wGetUniformLocation;

// void  mockgl3wGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params)
// {
//     return getMock()->gl3wGetUniformSubroutineuiv(shadertype, location, params);
// }
// PFNGLGETUNIFORMSUBROUTINEUIVPROC gl3wGetUniformSubroutineuiv = mockgl3wGetUniformSubroutineuiv;

// void  mockgl3wGetUniformdv(GLuint program, GLint location, GLdouble * params)
// {
//     return getMock()->gl3wGetUniformdv(program, location, params);
// }
// PFNGLGETUNIFORMDVPROC gl3wGetUniformdv = mockgl3wGetUniformdv;

// void  mockgl3wGetUniformfv(GLuint program, GLint location, GLfloat * params)
// {
//     return getMock()->gl3wGetUniformfv(program, location, params);
// }
// PFNGLGETUNIFORMFVPROC gl3wGetUniformfv = mockgl3wGetUniformfv;

// void  mockgl3wGetUniformiv(GLuint program, GLint location, GLint * params)
// {
//     return getMock()->gl3wGetUniformiv(program, location, params);
// }
// PFNGLGETUNIFORMIVPROC gl3wGetUniformiv = mockgl3wGetUniformiv;

// void  mockgl3wGetUniformuiv(GLuint program, GLint location, GLuint * params)
// {
//     return getMock()->gl3wGetUniformuiv(program, location, params);
// }
// PFNGLGETUNIFORMUIVPROC gl3wGetUniformuiv = mockgl3wGetUniformuiv;

// void  mockgl3wGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param)
// {
//     return getMock()->gl3wGetVertexArrayIndexed64iv(vaobj, index, pname, param);
// }
// PFNGLGETVERTEXARRAYINDEXED64IVPROC gl3wGetVertexArrayIndexed64iv = mockgl3wGetVertexArrayIndexed64iv;

// void  mockgl3wGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param)
// {
//     return getMock()->gl3wGetVertexArrayIndexediv(vaobj, index, pname, param);
// }
// PFNGLGETVERTEXARRAYINDEXEDIVPROC gl3wGetVertexArrayIndexediv = mockgl3wGetVertexArrayIndexediv;

// void  mockgl3wGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param)
// {
//     return getMock()->gl3wGetVertexArrayiv(vaobj, pname, param);
// }
// PFNGLGETVERTEXARRAYIVPROC gl3wGetVertexArrayiv = mockgl3wGetVertexArrayiv;

// void  mockgl3wGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetVertexAttribIiv(index, pname, params);
// }
// PFNGLGETVERTEXATTRIBIIVPROC gl3wGetVertexAttribIiv = mockgl3wGetVertexAttribIiv;

// void  mockgl3wGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params)
// {
//     return getMock()->gl3wGetVertexAttribIuiv(index, pname, params);
// }
// PFNGLGETVERTEXATTRIBIUIVPROC gl3wGetVertexAttribIuiv = mockgl3wGetVertexAttribIuiv;

// void  mockgl3wGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params)
// {
//     return getMock()->gl3wGetVertexAttribLdv(index, pname, params);
// }
// PFNGLGETVERTEXATTRIBLDVPROC gl3wGetVertexAttribLdv = mockgl3wGetVertexAttribLdv;

// void  mockgl3wGetVertexAttribLui64vARB(GLuint index, GLenum pname, GLuint64EXT * params)
// {
//     return getMock()->gl3wGetVertexAttribLui64vARB(index, pname, params);
// }
// PFNGLGETVERTEXATTRIBLUI64VARBPROC gl3wGetVertexAttribLui64vARB = mockgl3wGetVertexAttribLui64vARB;

// void  mockgl3wGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer)
// {
//     return getMock()->gl3wGetVertexAttribPointerv(index, pname, pointer);
// }
// PFNGLGETVERTEXATTRIBPOINTERVPROC gl3wGetVertexAttribPointerv = mockgl3wGetVertexAttribPointerv;

// void  mockgl3wGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params)
// {
//     return getMock()->gl3wGetVertexAttribdv(index, pname, params);
// }
// PFNGLGETVERTEXATTRIBDVPROC gl3wGetVertexAttribdv = mockgl3wGetVertexAttribdv;

// void  mockgl3wGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params)
// {
//     return getMock()->gl3wGetVertexAttribfv(index, pname, params);
// }
// PFNGLGETVERTEXATTRIBFVPROC gl3wGetVertexAttribfv = mockgl3wGetVertexAttribfv;

// void  mockgl3wGetVertexAttribiv(GLuint index, GLenum pname, GLint * params)
// {
//     return getMock()->gl3wGetVertexAttribiv(index, pname, params);
// }
// PFNGLGETVERTEXATTRIBIVPROC gl3wGetVertexAttribiv = mockgl3wGetVertexAttribiv;

// void  mockgl3wGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels)
// {
//     return getMock()->gl3wGetnCompressedTexImage(target, lod, bufSize, pixels);
// }
// PFNGLGETNCOMPRESSEDTEXIMAGEPROC gl3wGetnCompressedTexImage = mockgl3wGetnCompressedTexImage;

// void  mockgl3wGetnCompressedTexImageARB(GLenum target, GLint lod, GLsizei bufSize, void * img)
// {
//     return getMock()->gl3wGetnCompressedTexImageARB(target, lod, bufSize, img);
// }
// PFNGLGETNCOMPRESSEDTEXIMAGEARBPROC gl3wGetnCompressedTexImageARB = mockgl3wGetnCompressedTexImageARB;

// void  mockgl3wGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
// {
//     return getMock()->gl3wGetnTexImage(target, level, format, type, bufSize, pixels);
// }
// PFNGLGETNTEXIMAGEPROC gl3wGetnTexImage = mockgl3wGetnTexImage;

// void  mockgl3wGetnTexImageARB(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * img)
// {
//     return getMock()->gl3wGetnTexImageARB(target, level, format, type, bufSize, img);
// }
// PFNGLGETNTEXIMAGEARBPROC gl3wGetnTexImageARB = mockgl3wGetnTexImageARB;

// void  mockgl3wGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
// {
//     return getMock()->gl3wGetnUniformdv(program, location, bufSize, params);
// }
// PFNGLGETNUNIFORMDVPROC gl3wGetnUniformdv = mockgl3wGetnUniformdv;

// void  mockgl3wGetnUniformdvARB(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
// {
//     return getMock()->gl3wGetnUniformdvARB(program, location, bufSize, params);
// }
// PFNGLGETNUNIFORMDVARBPROC gl3wGetnUniformdvARB = mockgl3wGetnUniformdvARB;

// void  mockgl3wGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
// {
//     return getMock()->gl3wGetnUniformfv(program, location, bufSize, params);
// }
// PFNGLGETNUNIFORMFVPROC gl3wGetnUniformfv = mockgl3wGetnUniformfv;

// void  mockgl3wGetnUniformfvARB(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
// {
//     return getMock()->gl3wGetnUniformfvARB(program, location, bufSize, params);
// }
// PFNGLGETNUNIFORMFVARBPROC gl3wGetnUniformfvARB = mockgl3wGetnUniformfvARB;

// void  mockgl3wGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params)
// {
//     return getMock()->gl3wGetnUniformiv(program, location, bufSize, params);
// }
// PFNGLGETNUNIFORMIVPROC gl3wGetnUniformiv = mockgl3wGetnUniformiv;

// void  mockgl3wGetnUniformivARB(GLuint program, GLint location, GLsizei bufSize, GLint * params)
// {
//     return getMock()->gl3wGetnUniformivARB(program, location, bufSize, params);
// }
// PFNGLGETNUNIFORMIVARBPROC gl3wGetnUniformivARB = mockgl3wGetnUniformivARB;

// void  mockgl3wGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
// {
//     return getMock()->gl3wGetnUniformuiv(program, location, bufSize, params);
// }
// PFNGLGETNUNIFORMUIVPROC gl3wGetnUniformuiv = mockgl3wGetnUniformuiv;

// void  mockgl3wGetnUniformuivARB(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
// {
//     return getMock()->gl3wGetnUniformuivARB(program, location, bufSize, params);
// }
// PFNGLGETNUNIFORMUIVARBPROC gl3wGetnUniformuivARB = mockgl3wGetnUniformuivARB;

// void  mockgl3wHint(GLenum target, GLenum mode)
// {
//     return getMock()->gl3wHint(target, mode);
// }
// PFNGLHINTPROC gl3wHint = mockgl3wHint;

// void  mockgl3wInvalidateBufferData(GLuint buffer)
// {
//     return getMock()->gl3wInvalidateBufferData(buffer);
// }
// PFNGLINVALIDATEBUFFERDATAPROC gl3wInvalidateBufferData = mockgl3wInvalidateBufferData;

// void  mockgl3wInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
// {
//     return getMock()->gl3wInvalidateBufferSubData(buffer, offset, length);
// }
// PFNGLINVALIDATEBUFFERSUBDATAPROC gl3wInvalidateBufferSubData = mockgl3wInvalidateBufferSubData;

// void  mockgl3wInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments)
// {
//     return getMock()->gl3wInvalidateFramebuffer(target, numAttachments, attachments);
// }
// PFNGLINVALIDATEFRAMEBUFFERPROC gl3wInvalidateFramebuffer = mockgl3wInvalidateFramebuffer;

// void  mockgl3wInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments)
// {
//     return getMock()->gl3wInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
// }
// PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC gl3wInvalidateNamedFramebufferData = mockgl3wInvalidateNamedFramebufferData;

// void  mockgl3wInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
// }
// PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC gl3wInvalidateNamedFramebufferSubData = mockgl3wInvalidateNamedFramebufferSubData;

// void  mockgl3wInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
// }
// PFNGLINVALIDATESUBFRAMEBUFFERPROC gl3wInvalidateSubFramebuffer = mockgl3wInvalidateSubFramebuffer;

// void  mockgl3wInvalidateTexImage(GLuint texture, GLint level)
// {
//     return getMock()->gl3wInvalidateTexImage(texture, level);
// }
// PFNGLINVALIDATETEXIMAGEPROC gl3wInvalidateTexImage = mockgl3wInvalidateTexImage;

// void  mockgl3wInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
// {
//     return getMock()->gl3wInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
// }
// PFNGLINVALIDATETEXSUBIMAGEPROC gl3wInvalidateTexSubImage = mockgl3wInvalidateTexSubImage;

// unsigned char  mockgl3wIsBuffer(GLuint buffer)
// {
//     return getMock()->gl3wIsBuffer(buffer);
// }
// PFNGLISBUFFERPROC gl3wIsBuffer = mockgl3wIsBuffer;

// unsigned char  mockgl3wIsEnabled(GLenum cap)
// {
//     return getMock()->gl3wIsEnabled(cap);
// }
// PFNGLISENABLEDPROC gl3wIsEnabled = mockgl3wIsEnabled;

// unsigned char  mockgl3wIsEnabledi(GLenum target, GLuint index)
// {
//     return getMock()->gl3wIsEnabledi(target, index);
// }
// PFNGLISENABLEDIPROC gl3wIsEnabledi = mockgl3wIsEnabledi;

// unsigned char  mockgl3wIsFramebuffer(GLuint framebuffer)
// {
//     return getMock()->gl3wIsFramebuffer(framebuffer);
// }
// PFNGLISFRAMEBUFFERPROC gl3wIsFramebuffer = mockgl3wIsFramebuffer;

// unsigned char  mockgl3wIsImageHandleResidentARB(GLuint64 handle)
// {
//     return getMock()->gl3wIsImageHandleResidentARB(handle);
// }
// PFNGLISIMAGEHANDLERESIDENTARBPROC gl3wIsImageHandleResidentARB = mockgl3wIsImageHandleResidentARB;

// unsigned char  mockgl3wIsNamedStringARB(GLint namelen, const GLchar * name)
// {
//     return getMock()->gl3wIsNamedStringARB(namelen, name);
// }
// PFNGLISNAMEDSTRINGARBPROC gl3wIsNamedStringARB = mockgl3wIsNamedStringARB;

// unsigned char  mockgl3wIsProgram(GLuint program)
// {
//     return getMock()->gl3wIsProgram(program);
// }
// PFNGLISPROGRAMPROC gl3wIsProgram = mockgl3wIsProgram;

// unsigned char  mockgl3wIsProgramPipeline(GLuint pipeline)
// {
//     return getMock()->gl3wIsProgramPipeline(pipeline);
// }
// PFNGLISPROGRAMPIPELINEPROC gl3wIsProgramPipeline = mockgl3wIsProgramPipeline;

// unsigned char  mockgl3wIsQuery(GLuint id)
// {
//     return getMock()->gl3wIsQuery(id);
// }
// PFNGLISQUERYPROC gl3wIsQuery = mockgl3wIsQuery;

// unsigned char  mockgl3wIsRenderbuffer(GLuint renderbuffer)
// {
//     return getMock()->gl3wIsRenderbuffer(renderbuffer);
// }
// PFNGLISRENDERBUFFERPROC gl3wIsRenderbuffer = mockgl3wIsRenderbuffer;

// unsigned char  mockgl3wIsSampler(GLuint sampler)
// {
//     return getMock()->gl3wIsSampler(sampler);
// }
// PFNGLISSAMPLERPROC gl3wIsSampler = mockgl3wIsSampler;

// unsigned char  mockgl3wIsShader(GLuint shader)
// {
//     return getMock()->gl3wIsShader(shader);
// }
// PFNGLISSHADERPROC gl3wIsShader = mockgl3wIsShader;

// unsigned char  mockgl3wIsSync(GLsync sync)
// {
//     return getMock()->gl3wIsSync(sync);
// }
// PFNGLISSYNCPROC gl3wIsSync = mockgl3wIsSync;

// unsigned char  mockgl3wIsTexture(GLuint texture)
// {
//     return getMock()->gl3wIsTexture(texture);
// }
// PFNGLISTEXTUREPROC gl3wIsTexture = mockgl3wIsTexture;

// unsigned char  mockgl3wIsTextureHandleResidentARB(GLuint64 handle)
// {
//     return getMock()->gl3wIsTextureHandleResidentARB(handle);
// }
// PFNGLISTEXTUREHANDLERESIDENTARBPROC gl3wIsTextureHandleResidentARB = mockgl3wIsTextureHandleResidentARB;

// unsigned char  mockgl3wIsTransformFeedback(GLuint id)
// {
//     return getMock()->gl3wIsTransformFeedback(id);
// }
// PFNGLISTRANSFORMFEEDBACKPROC gl3wIsTransformFeedback = mockgl3wIsTransformFeedback;

// unsigned char  mockgl3wIsVertexArray(GLuint array)
// {
//     return getMock()->gl3wIsVertexArray(array);
// }
// PFNGLISVERTEXARRAYPROC gl3wIsVertexArray = mockgl3wIsVertexArray;

// void  mockgl3wLineWidth(GLfloat width)
// {
//     return getMock()->gl3wLineWidth(width);
// }
// PFNGLLINEWIDTHPROC gl3wLineWidth = mockgl3wLineWidth;

// void  mockgl3wLinkProgram(GLuint program)
// {
//     return getMock()->gl3wLinkProgram(program);
// }
// PFNGLLINKPROGRAMPROC gl3wLinkProgram = mockgl3wLinkProgram;

// void  mockgl3wLogicOp(GLenum opcode)
// {
//     return getMock()->gl3wLogicOp(opcode);
// }
// PFNGLLOGICOPPROC gl3wLogicOp = mockgl3wLogicOp;

// void  mockgl3wMakeImageHandleNonResidentARB(GLuint64 handle)
// {
//     return getMock()->gl3wMakeImageHandleNonResidentARB(handle);
// }
// PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC gl3wMakeImageHandleNonResidentARB = mockgl3wMakeImageHandleNonResidentARB;

// void  mockgl3wMakeImageHandleResidentARB(GLuint64 handle, GLenum access)
// {
//     return getMock()->gl3wMakeImageHandleResidentARB(handle, access);
// }
// PFNGLMAKEIMAGEHANDLERESIDENTARBPROC gl3wMakeImageHandleResidentARB = mockgl3wMakeImageHandleResidentARB;

// void  mockgl3wMakeTextureHandleNonResidentARB(GLuint64 handle)
// {
//     return getMock()->gl3wMakeTextureHandleNonResidentARB(handle);
// }
// PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC gl3wMakeTextureHandleNonResidentARB = mockgl3wMakeTextureHandleNonResidentARB;

// void  mockgl3wMakeTextureHandleResidentARB(GLuint64 handle)
// {
//     return getMock()->gl3wMakeTextureHandleResidentARB(handle);
// }
// PFNGLMAKETEXTUREHANDLERESIDENTARBPROC gl3wMakeTextureHandleResidentARB = mockgl3wMakeTextureHandleResidentARB;

// void * mockgl3wMapBuffer(GLenum target, GLenum access)
// {
//     return getMock()->gl3wMapBuffer(target, access);
// }
// PFNGLMAPBUFFERPROC gl3wMapBuffer = mockgl3wMapBuffer;

// void * mockgl3wMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
// {
//     return getMock()->gl3wMapBufferRange(target, offset, length, access);
// }
// PFNGLMAPBUFFERRANGEPROC gl3wMapBufferRange = mockgl3wMapBufferRange;

// void * mockgl3wMapNamedBuffer(GLuint buffer, GLenum access)
// {
//     return getMock()->gl3wMapNamedBuffer(buffer, access);
// }
// PFNGLMAPNAMEDBUFFERPROC gl3wMapNamedBuffer = mockgl3wMapNamedBuffer;

// void * mockgl3wMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizei length, GLbitfield access)
// {
//     return getMock()->gl3wMapNamedBufferRange(buffer, offset, length, access);
// }
// PFNGLMAPNAMEDBUFFERRANGEPROC gl3wMapNamedBufferRange = mockgl3wMapNamedBufferRange;

// void  mockgl3wMemoryBarrier(GLbitfield barriers)
// {
//     return getMock()->gl3wMemoryBarrier(barriers);
// }
// PFNGLMEMORYBARRIERPROC gl3wMemoryBarrier = mockgl3wMemoryBarrier;

// void  mockgl3wMemoryBarrierByRegion(GLbitfield barriers)
// {
//     return getMock()->gl3wMemoryBarrierByRegion(barriers);
// }
// PFNGLMEMORYBARRIERBYREGIONPROC gl3wMemoryBarrierByRegion = mockgl3wMemoryBarrierByRegion;

// void  mockgl3wMinSampleShading(GLfloat value)
// {
//     return getMock()->gl3wMinSampleShading(value);
// }
// PFNGLMINSAMPLESHADINGPROC gl3wMinSampleShading = mockgl3wMinSampleShading;

// void  mockgl3wMinSampleShadingARB(GLfloat value)
// {
//     return getMock()->gl3wMinSampleShadingARB(value);
// }
// PFNGLMINSAMPLESHADINGARBPROC gl3wMinSampleShadingARB = mockgl3wMinSampleShadingARB;

// void  mockgl3wMultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount)
// {
//     return getMock()->gl3wMultiDrawArrays(mode, first, count, drawcount);
// }
// PFNGLMULTIDRAWARRAYSPROC gl3wMultiDrawArrays = mockgl3wMultiDrawArrays;

// void  mockgl3wMultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride)
// {
//     return getMock()->gl3wMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
// }
// PFNGLMULTIDRAWARRAYSINDIRECTPROC gl3wMultiDrawArraysIndirect = mockgl3wMultiDrawArraysIndirect;

// void  mockgl3wMultiDrawArraysIndirectCountARB(GLenum mode, GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
// {
//     return getMock()->gl3wMultiDrawArraysIndirectCountARB(mode, indirect, drawcount, maxdrawcount, stride);
// }
// PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC gl3wMultiDrawArraysIndirectCountARB = mockgl3wMultiDrawArraysIndirectCountARB;

// void  mockgl3wMultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const * indices, GLsizei drawcount)
// {
//     return getMock()->gl3wMultiDrawElements(mode, count, type, indices, drawcount);
// }
// PFNGLMULTIDRAWELEMENTSPROC gl3wMultiDrawElements = mockgl3wMultiDrawElements;

// void  mockgl3wMultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const * indices, GLsizei drawcount, const GLint * basevertex)
// {
//     return getMock()->gl3wMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
// }
// PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC gl3wMultiDrawElementsBaseVertex = mockgl3wMultiDrawElementsBaseVertex;

// void  mockgl3wMultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride)
// {
//     return getMock()->gl3wMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
// }
// PFNGLMULTIDRAWELEMENTSINDIRECTPROC gl3wMultiDrawElementsIndirect = mockgl3wMultiDrawElementsIndirect;

// void  mockgl3wMultiDrawElementsIndirectCountARB(GLenum mode, GLenum type, GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
// {
//     return getMock()->gl3wMultiDrawElementsIndirectCountARB(mode, type, indirect, drawcount, maxdrawcount, stride);
// }
// PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC gl3wMultiDrawElementsIndirectCountARB = mockgl3wMultiDrawElementsIndirectCountARB;

// void  mockgl3wNamedBufferData(GLuint buffer, GLsizei size, const void * data, GLenum usage)
// {
//     return getMock()->gl3wNamedBufferData(buffer, size, data, usage);
// }
// PFNGLNAMEDBUFFERDATAPROC gl3wNamedBufferData = mockgl3wNamedBufferData;

// void  mockgl3wNamedBufferPageCommitmentARB(GLuint buffer, GLintptr offset, GLsizei size, GLboolean commit)
// {
//     return getMock()->gl3wNamedBufferPageCommitmentARB(buffer, offset, size, commit);
// }
// PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC gl3wNamedBufferPageCommitmentARB = mockgl3wNamedBufferPageCommitmentARB;

// void  mockgl3wNamedBufferPageCommitmentEXT(GLuint buffer, GLintptr offset, GLsizei size, GLboolean commit)
// {
//     return getMock()->gl3wNamedBufferPageCommitmentEXT(buffer, offset, size, commit);
// }
// PFNGLNAMEDBUFFERPAGECOMMITMENTEXTPROC gl3wNamedBufferPageCommitmentEXT = mockgl3wNamedBufferPageCommitmentEXT;

// void  mockgl3wNamedBufferStorage(GLuint buffer, GLsizei size, const void * data, GLbitfield flags)
// {
//     return getMock()->gl3wNamedBufferStorage(buffer, size, data, flags);
// }
// PFNGLNAMEDBUFFERSTORAGEPROC gl3wNamedBufferStorage = mockgl3wNamedBufferStorage;

// void  mockgl3wNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizei size, const void * data)
// {
//     return getMock()->gl3wNamedBufferSubData(buffer, offset, size, data);
// }
// PFNGLNAMEDBUFFERSUBDATAPROC gl3wNamedBufferSubData = mockgl3wNamedBufferSubData;

// void  mockgl3wNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
// {
//     return getMock()->gl3wNamedFramebufferDrawBuffer(framebuffer, buf);
// }
// PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC gl3wNamedFramebufferDrawBuffer = mockgl3wNamedFramebufferDrawBuffer;

// void  mockgl3wNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs)
// {
//     return getMock()->gl3wNamedFramebufferDrawBuffers(framebuffer, n, bufs);
// }
// PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC gl3wNamedFramebufferDrawBuffers = mockgl3wNamedFramebufferDrawBuffers;

// void  mockgl3wNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param)
// {
//     return getMock()->gl3wNamedFramebufferParameteri(framebuffer, pname, param);
// }
// PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC gl3wNamedFramebufferParameteri = mockgl3wNamedFramebufferParameteri;

// void  mockgl3wNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
// {
//     return getMock()->gl3wNamedFramebufferReadBuffer(framebuffer, src);
// }
// PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC gl3wNamedFramebufferReadBuffer = mockgl3wNamedFramebufferReadBuffer;

// void  mockgl3wNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
// {
//     return getMock()->gl3wNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
// }
// PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC gl3wNamedFramebufferRenderbuffer = mockgl3wNamedFramebufferRenderbuffer;

// void  mockgl3wNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
// {
//     return getMock()->gl3wNamedFramebufferTexture(framebuffer, attachment, texture, level);
// }
// PFNGLNAMEDFRAMEBUFFERTEXTUREPROC gl3wNamedFramebufferTexture = mockgl3wNamedFramebufferTexture;

// void  mockgl3wNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
// {
//     return getMock()->gl3wNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
// }
// PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC gl3wNamedFramebufferTextureLayer = mockgl3wNamedFramebufferTextureLayer;

// void  mockgl3wNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
// }
// PFNGLNAMEDRENDERBUFFERSTORAGEPROC gl3wNamedRenderbufferStorage = mockgl3wNamedRenderbufferStorage;

// void  mockgl3wNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
// }
// PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC gl3wNamedRenderbufferStorageMultisample = mockgl3wNamedRenderbufferStorageMultisample;

// void  mockgl3wNamedStringARB(GLenum type, GLint namelen, const GLchar * name, GLint stringlen, const GLchar * string)
// {
//     return getMock()->gl3wNamedStringARB(type, namelen, name, stringlen, string);
// }
// PFNGLNAMEDSTRINGARBPROC gl3wNamedStringARB = mockgl3wNamedStringARB;

// void  mockgl3wObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label)
// {
//     return getMock()->gl3wObjectLabel(identifier, name, length, label);
// }
// PFNGLOBJECTLABELPROC gl3wObjectLabel = mockgl3wObjectLabel;

// void  mockgl3wObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label)
// {
//     return getMock()->gl3wObjectPtrLabel(ptr, length, label);
// }
// PFNGLOBJECTPTRLABELPROC gl3wObjectPtrLabel = mockgl3wObjectPtrLabel;

// void  mockgl3wPatchParameterfv(GLenum pname, const GLfloat * values)
// {
//     return getMock()->gl3wPatchParameterfv(pname, values);
// }
// PFNGLPATCHPARAMETERFVPROC gl3wPatchParameterfv = mockgl3wPatchParameterfv;

// void  mockgl3wPatchParameteri(GLenum pname, GLint value)
// {
//     return getMock()->gl3wPatchParameteri(pname, value);
// }
// PFNGLPATCHPARAMETERIPROC gl3wPatchParameteri = mockgl3wPatchParameteri;

// void  mockgl3wPauseTransformFeedback()
// {
//     return getMock()->gl3wPauseTransformFeedback();
// }
// PFNGLPAUSETRANSFORMFEEDBACKPROC gl3wPauseTransformFeedback = mockgl3wPauseTransformFeedback;

// void  mockgl3wPixelStoref(GLenum pname, GLfloat param)
// {
//     return getMock()->gl3wPixelStoref(pname, param);
// }
// PFNGLPIXELSTOREFPROC gl3wPixelStoref = mockgl3wPixelStoref;

// void  mockgl3wPixelStorei(GLenum pname, GLint param)
// {
//     return getMock()->gl3wPixelStorei(pname, param);
// }
// PFNGLPIXELSTOREIPROC gl3wPixelStorei = mockgl3wPixelStorei;

// void  mockgl3wPointParameterf(GLenum pname, GLfloat param)
// {
//     return getMock()->gl3wPointParameterf(pname, param);
// }
// PFNGLPOINTPARAMETERFPROC gl3wPointParameterf = mockgl3wPointParameterf;

// void  mockgl3wPointParameterfv(GLenum pname, const GLfloat * params)
// {
//     return getMock()->gl3wPointParameterfv(pname, params);
// }
// PFNGLPOINTPARAMETERFVPROC gl3wPointParameterfv = mockgl3wPointParameterfv;

// void  mockgl3wPointParameteri(GLenum pname, GLint param)
// {
//     return getMock()->gl3wPointParameteri(pname, param);
// }
// PFNGLPOINTPARAMETERIPROC gl3wPointParameteri = mockgl3wPointParameteri;

// void  mockgl3wPointParameteriv(GLenum pname, const GLint * params)
// {
//     return getMock()->gl3wPointParameteriv(pname, params);
// }
// PFNGLPOINTPARAMETERIVPROC gl3wPointParameteriv = mockgl3wPointParameteriv;

// void  mockgl3wPointSize(GLfloat size)
// {
//     return getMock()->gl3wPointSize(size);
// }
// PFNGLPOINTSIZEPROC gl3wPointSize = mockgl3wPointSize;

// void  mockgl3wPolygonMode(GLenum face, GLenum mode)
// {
//     return getMock()->gl3wPolygonMode(face, mode);
// }
// PFNGLPOLYGONMODEPROC gl3wPolygonMode = mockgl3wPolygonMode;

// void  mockgl3wPolygonOffset(GLfloat factor, GLfloat units)
// {
//     return getMock()->gl3wPolygonOffset(factor, units);
// }
// PFNGLPOLYGONOFFSETPROC gl3wPolygonOffset = mockgl3wPolygonOffset;

// void  mockgl3wPopDebugGroup()
// {
//     return getMock()->gl3wPopDebugGroup();
// }
// PFNGLPOPDEBUGGROUPPROC gl3wPopDebugGroup = mockgl3wPopDebugGroup;

// void  mockgl3wPrimitiveRestartIndex(GLuint index)
// {
//     return getMock()->gl3wPrimitiveRestartIndex(index);
// }
// PFNGLPRIMITIVERESTARTINDEXPROC gl3wPrimitiveRestartIndex = mockgl3wPrimitiveRestartIndex;

// void  mockgl3wProgramBinary(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length)
// {
//     return getMock()->gl3wProgramBinary(program, binaryFormat, binary, length);
// }
// PFNGLPROGRAMBINARYPROC gl3wProgramBinary = mockgl3wProgramBinary;

// void  mockgl3wProgramParameteri(GLuint program, GLenum pname, GLint value)
// {
//     return getMock()->gl3wProgramParameteri(program, pname, value);
// }
// PFNGLPROGRAMPARAMETERIPROC gl3wProgramParameteri = mockgl3wProgramParameteri;

// void  mockgl3wProgramUniform1d(GLuint program, GLint location, GLdouble v0)
// {
//     return getMock()->gl3wProgramUniform1d(program, location, v0);
// }
// PFNGLPROGRAMUNIFORM1DPROC gl3wProgramUniform1d = mockgl3wProgramUniform1d;

// void  mockgl3wProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniform1dv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM1DVPROC gl3wProgramUniform1dv = mockgl3wProgramUniform1dv;

// void  mockgl3wProgramUniform1f(GLuint program, GLint location, GLfloat v0)
// {
//     return getMock()->gl3wProgramUniform1f(program, location, v0);
// }
// PFNGLPROGRAMUNIFORM1FPROC gl3wProgramUniform1f = mockgl3wProgramUniform1f;

// void  mockgl3wProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniform1fv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM1FVPROC gl3wProgramUniform1fv = mockgl3wProgramUniform1fv;

// void  mockgl3wProgramUniform1i(GLuint program, GLint location, GLint v0)
// {
//     return getMock()->gl3wProgramUniform1i(program, location, v0);
// }
// PFNGLPROGRAMUNIFORM1IPROC gl3wProgramUniform1i = mockgl3wProgramUniform1i;

// void  mockgl3wProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value)
// {
//     return getMock()->gl3wProgramUniform1iv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM1IVPROC gl3wProgramUniform1iv = mockgl3wProgramUniform1iv;

// void  mockgl3wProgramUniform1ui(GLuint program, GLint location, GLuint v0)
// {
//     return getMock()->gl3wProgramUniform1ui(program, location, v0);
// }
// PFNGLPROGRAMUNIFORM1UIPROC gl3wProgramUniform1ui = mockgl3wProgramUniform1ui;

// void  mockgl3wProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
// {
//     return getMock()->gl3wProgramUniform1uiv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM1UIVPROC gl3wProgramUniform1uiv = mockgl3wProgramUniform1uiv;

// void  mockgl3wProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
// {
//     return getMock()->gl3wProgramUniform2d(program, location, v0, v1);
// }
// PFNGLPROGRAMUNIFORM2DPROC gl3wProgramUniform2d = mockgl3wProgramUniform2d;

// void  mockgl3wProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniform2dv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM2DVPROC gl3wProgramUniform2dv = mockgl3wProgramUniform2dv;

// void  mockgl3wProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
// {
//     return getMock()->gl3wProgramUniform2f(program, location, v0, v1);
// }
// PFNGLPROGRAMUNIFORM2FPROC gl3wProgramUniform2f = mockgl3wProgramUniform2f;

// void  mockgl3wProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniform2fv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM2FVPROC gl3wProgramUniform2fv = mockgl3wProgramUniform2fv;

// void  mockgl3wProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
// {
//     return getMock()->gl3wProgramUniform2i(program, location, v0, v1);
// }
// PFNGLPROGRAMUNIFORM2IPROC gl3wProgramUniform2i = mockgl3wProgramUniform2i;

// void  mockgl3wProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value)
// {
//     return getMock()->gl3wProgramUniform2iv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM2IVPROC gl3wProgramUniform2iv = mockgl3wProgramUniform2iv;

// void  mockgl3wProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
// {
//     return getMock()->gl3wProgramUniform2ui(program, location, v0, v1);
// }
// PFNGLPROGRAMUNIFORM2UIPROC gl3wProgramUniform2ui = mockgl3wProgramUniform2ui;

// void  mockgl3wProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
// {
//     return getMock()->gl3wProgramUniform2uiv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM2UIVPROC gl3wProgramUniform2uiv = mockgl3wProgramUniform2uiv;

// void  mockgl3wProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
// {
//     return getMock()->gl3wProgramUniform3d(program, location, v0, v1, v2);
// }
// PFNGLPROGRAMUNIFORM3DPROC gl3wProgramUniform3d = mockgl3wProgramUniform3d;

// void  mockgl3wProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniform3dv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM3DVPROC gl3wProgramUniform3dv = mockgl3wProgramUniform3dv;

// void  mockgl3wProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
// {
//     return getMock()->gl3wProgramUniform3f(program, location, v0, v1, v2);
// }
// PFNGLPROGRAMUNIFORM3FPROC gl3wProgramUniform3f = mockgl3wProgramUniform3f;

// void  mockgl3wProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniform3fv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM3FVPROC gl3wProgramUniform3fv = mockgl3wProgramUniform3fv;

// void  mockgl3wProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
// {
//     return getMock()->gl3wProgramUniform3i(program, location, v0, v1, v2);
// }
// PFNGLPROGRAMUNIFORM3IPROC gl3wProgramUniform3i = mockgl3wProgramUniform3i;

// void  mockgl3wProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value)
// {
//     return getMock()->gl3wProgramUniform3iv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM3IVPROC gl3wProgramUniform3iv = mockgl3wProgramUniform3iv;

// void  mockgl3wProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
// {
//     return getMock()->gl3wProgramUniform3ui(program, location, v0, v1, v2);
// }
// PFNGLPROGRAMUNIFORM3UIPROC gl3wProgramUniform3ui = mockgl3wProgramUniform3ui;

// void  mockgl3wProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
// {
//     return getMock()->gl3wProgramUniform3uiv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM3UIVPROC gl3wProgramUniform3uiv = mockgl3wProgramUniform3uiv;

// void  mockgl3wProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
// {
//     return getMock()->gl3wProgramUniform4d(program, location, v0, v1, v2, v3);
// }
// PFNGLPROGRAMUNIFORM4DPROC gl3wProgramUniform4d = mockgl3wProgramUniform4d;

// void  mockgl3wProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniform4dv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM4DVPROC gl3wProgramUniform4dv = mockgl3wProgramUniform4dv;

// void  mockgl3wProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
// {
//     return getMock()->gl3wProgramUniform4f(program, location, v0, v1, v2, v3);
// }
// PFNGLPROGRAMUNIFORM4FPROC gl3wProgramUniform4f = mockgl3wProgramUniform4f;

// void  mockgl3wProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniform4fv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM4FVPROC gl3wProgramUniform4fv = mockgl3wProgramUniform4fv;

// void  mockgl3wProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
// {
//     return getMock()->gl3wProgramUniform4i(program, location, v0, v1, v2, v3);
// }
// PFNGLPROGRAMUNIFORM4IPROC gl3wProgramUniform4i = mockgl3wProgramUniform4i;

// void  mockgl3wProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value)
// {
//     return getMock()->gl3wProgramUniform4iv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM4IVPROC gl3wProgramUniform4iv = mockgl3wProgramUniform4iv;

// void  mockgl3wProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
// {
//     return getMock()->gl3wProgramUniform4ui(program, location, v0, v1, v2, v3);
// }
// PFNGLPROGRAMUNIFORM4UIPROC gl3wProgramUniform4ui = mockgl3wProgramUniform4ui;

// void  mockgl3wProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
// {
//     return getMock()->gl3wProgramUniform4uiv(program, location, count, value);
// }
// PFNGLPROGRAMUNIFORM4UIVPROC gl3wProgramUniform4uiv = mockgl3wProgramUniform4uiv;

// void  mockgl3wProgramUniformHandleui64ARB(GLuint program, GLint location, GLuint64 value)
// {
//     return getMock()->gl3wProgramUniformHandleui64ARB(program, location, value);
// }
// PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC gl3wProgramUniformHandleui64ARB = mockgl3wProgramUniformHandleui64ARB;

// void  mockgl3wProgramUniformHandleui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 * values)
// {
//     return getMock()->gl3wProgramUniformHandleui64vARB(program, location, count, values);
// }
// PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC gl3wProgramUniformHandleui64vARB = mockgl3wProgramUniformHandleui64vARB;

// void  mockgl3wProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix2dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX2DVPROC gl3wProgramUniformMatrix2dv = mockgl3wProgramUniformMatrix2dv;

// void  mockgl3wProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix2fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX2FVPROC gl3wProgramUniformMatrix2fv = mockgl3wProgramUniformMatrix2fv;

// void  mockgl3wProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix2x3dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC gl3wProgramUniformMatrix2x3dv = mockgl3wProgramUniformMatrix2x3dv;

// void  mockgl3wProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix2x3fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC gl3wProgramUniformMatrix2x3fv = mockgl3wProgramUniformMatrix2x3fv;

// void  mockgl3wProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix2x4dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC gl3wProgramUniformMatrix2x4dv = mockgl3wProgramUniformMatrix2x4dv;

// void  mockgl3wProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix2x4fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC gl3wProgramUniformMatrix2x4fv = mockgl3wProgramUniformMatrix2x4fv;

// void  mockgl3wProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix3dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX3DVPROC gl3wProgramUniformMatrix3dv = mockgl3wProgramUniformMatrix3dv;

// void  mockgl3wProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix3fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX3FVPROC gl3wProgramUniformMatrix3fv = mockgl3wProgramUniformMatrix3fv;

// void  mockgl3wProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix3x2dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC gl3wProgramUniformMatrix3x2dv = mockgl3wProgramUniformMatrix3x2dv;

// void  mockgl3wProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix3x2fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC gl3wProgramUniformMatrix3x2fv = mockgl3wProgramUniformMatrix3x2fv;

// void  mockgl3wProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix3x4dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC gl3wProgramUniformMatrix3x4dv = mockgl3wProgramUniformMatrix3x4dv;

// void  mockgl3wProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix3x4fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC gl3wProgramUniformMatrix3x4fv = mockgl3wProgramUniformMatrix3x4fv;

// void  mockgl3wProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix4dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX4DVPROC gl3wProgramUniformMatrix4dv = mockgl3wProgramUniformMatrix4dv;

// void  mockgl3wProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix4fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX4FVPROC gl3wProgramUniformMatrix4fv = mockgl3wProgramUniformMatrix4fv;

// void  mockgl3wProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix4x2dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC gl3wProgramUniformMatrix4x2dv = mockgl3wProgramUniformMatrix4x2dv;

// void  mockgl3wProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix4x2fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC gl3wProgramUniformMatrix4x2fv = mockgl3wProgramUniformMatrix4x2fv;

// void  mockgl3wProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wProgramUniformMatrix4x3dv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC gl3wProgramUniformMatrix4x3dv = mockgl3wProgramUniformMatrix4x3dv;

// void  mockgl3wProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wProgramUniformMatrix4x3fv(program, location, count, transpose, value);
// }
// PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC gl3wProgramUniformMatrix4x3fv = mockgl3wProgramUniformMatrix4x3fv;

// void  mockgl3wProvokingVertex(GLenum mode)
// {
//     return getMock()->gl3wProvokingVertex(mode);
// }
// PFNGLPROVOKINGVERTEXPROC gl3wProvokingVertex = mockgl3wProvokingVertex;

// void  mockgl3wPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message)
// {
//     return getMock()->gl3wPushDebugGroup(source, id, length, message);
// }
// PFNGLPUSHDEBUGGROUPPROC gl3wPushDebugGroup = mockgl3wPushDebugGroup;

// void  mockgl3wQueryCounter(GLuint id, GLenum target)
// {
//     return getMock()->gl3wQueryCounter(id, target);
// }
// PFNGLQUERYCOUNTERPROC gl3wQueryCounter = mockgl3wQueryCounter;

// void  mockgl3wReadBuffer(GLenum src)
// {
//     return getMock()->gl3wReadBuffer(src);
// }
// PFNGLREADBUFFERPROC gl3wReadBuffer = mockgl3wReadBuffer;

// void  mockgl3wReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels)
// {
//     return getMock()->gl3wReadPixels(x, y, width, height, format, type, pixels);
// }
// PFNGLREADPIXELSPROC gl3wReadPixels = mockgl3wReadPixels;

// void  mockgl3wReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data)
// {
//     return getMock()->gl3wReadnPixels(x, y, width, height, format, type, bufSize, data);
// }
// PFNGLREADNPIXELSPROC gl3wReadnPixels = mockgl3wReadnPixels;

// void  mockgl3wReadnPixelsARB(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data)
// {
//     return getMock()->gl3wReadnPixelsARB(x, y, width, height, format, type, bufSize, data);
// }
// PFNGLREADNPIXELSARBPROC gl3wReadnPixelsARB = mockgl3wReadnPixelsARB;

// void  mockgl3wReleaseShaderCompiler()
// {
//     return getMock()->gl3wReleaseShaderCompiler();
// }
// PFNGLRELEASESHADERCOMPILERPROC gl3wReleaseShaderCompiler = mockgl3wReleaseShaderCompiler;

// void  mockgl3wRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wRenderbufferStorage(target, internalformat, width, height);
// }
// PFNGLRENDERBUFFERSTORAGEPROC gl3wRenderbufferStorage = mockgl3wRenderbufferStorage;

// void  mockgl3wRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wRenderbufferStorageMultisample(target, samples, internalformat, width, height);
// }
// PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC gl3wRenderbufferStorageMultisample = mockgl3wRenderbufferStorageMultisample;

// void  mockgl3wResumeTransformFeedback()
// {
//     return getMock()->gl3wResumeTransformFeedback();
// }
// PFNGLRESUMETRANSFORMFEEDBACKPROC gl3wResumeTransformFeedback = mockgl3wResumeTransformFeedback;

// void  mockgl3wSampleCoverage(GLfloat value, GLboolean invert)
// {
//     return getMock()->gl3wSampleCoverage(value, invert);
// }
// PFNGLSAMPLECOVERAGEPROC gl3wSampleCoverage = mockgl3wSampleCoverage;

// void  mockgl3wSampleMaski(GLuint maskNumber, GLbitfield mask)
// {
//     return getMock()->gl3wSampleMaski(maskNumber, mask);
// }
// PFNGLSAMPLEMASKIPROC gl3wSampleMaski = mockgl3wSampleMaski;

// void  mockgl3wSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param)
// {
//     return getMock()->gl3wSamplerParameterIiv(sampler, pname, param);
// }
// PFNGLSAMPLERPARAMETERIIVPROC gl3wSamplerParameterIiv = mockgl3wSamplerParameterIiv;

// void  mockgl3wSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param)
// {
//     return getMock()->gl3wSamplerParameterIuiv(sampler, pname, param);
// }
// PFNGLSAMPLERPARAMETERIUIVPROC gl3wSamplerParameterIuiv = mockgl3wSamplerParameterIuiv;

// void  mockgl3wSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
// {
//     return getMock()->gl3wSamplerParameterf(sampler, pname, param);
// }
// PFNGLSAMPLERPARAMETERFPROC gl3wSamplerParameterf = mockgl3wSamplerParameterf;

// void  mockgl3wSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param)
// {
//     return getMock()->gl3wSamplerParameterfv(sampler, pname, param);
// }
// PFNGLSAMPLERPARAMETERFVPROC gl3wSamplerParameterfv = mockgl3wSamplerParameterfv;

// void  mockgl3wSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
// {
//     return getMock()->gl3wSamplerParameteri(sampler, pname, param);
// }
// PFNGLSAMPLERPARAMETERIPROC gl3wSamplerParameteri = mockgl3wSamplerParameteri;

// void  mockgl3wSamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param)
// {
//     return getMock()->gl3wSamplerParameteriv(sampler, pname, param);
// }
// PFNGLSAMPLERPARAMETERIVPROC gl3wSamplerParameteriv = mockgl3wSamplerParameteriv;

// void  mockgl3wScissor(GLint x, GLint y, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wScissor(x, y, width, height);
// }
// PFNGLSCISSORPROC gl3wScissor = mockgl3wScissor;

// void  mockgl3wScissorArrayv(GLuint first, GLsizei count, const GLint * v)
// {
//     return getMock()->gl3wScissorArrayv(first, count, v);
// }
// PFNGLSCISSORARRAYVPROC gl3wScissorArrayv = mockgl3wScissorArrayv;

// void  mockgl3wScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wScissorIndexed(index, left, bottom, width, height);
// }
// PFNGLSCISSORINDEXEDPROC gl3wScissorIndexed = mockgl3wScissorIndexed;

// void  mockgl3wScissorIndexedv(GLuint index, const GLint * v)
// {
//     return getMock()->gl3wScissorIndexedv(index, v);
// }
// PFNGLSCISSORINDEXEDVPROC gl3wScissorIndexedv = mockgl3wScissorIndexedv;

// void  mockgl3wShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length)
// {
//     return getMock()->gl3wShaderBinary(count, shaders, binaryformat, binary, length);
// }
// PFNGLSHADERBINARYPROC gl3wShaderBinary = mockgl3wShaderBinary;

// void  mockgl3wShaderSource(GLuint shader, GLsizei count, const GLchar *const * string, const GLint * length)
// {
//     return getMock()->gl3wShaderSource(shader, count, string, length);
// }
// PFNGLSHADERSOURCEPROC gl3wShaderSource = mockgl3wShaderSource;

// void  mockgl3wShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
// {
//     return getMock()->gl3wShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
// }
// PFNGLSHADERSTORAGEBLOCKBINDINGPROC gl3wShaderStorageBlockBinding = mockgl3wShaderStorageBlockBinding;

// void  mockgl3wStencilFunc(GLenum func, GLint ref, GLuint mask)
// {
//     return getMock()->gl3wStencilFunc(func, ref, mask);
// }
// PFNGLSTENCILFUNCPROC gl3wStencilFunc = mockgl3wStencilFunc;

// void  mockgl3wStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
// {
//     return getMock()->gl3wStencilFuncSeparate(face, func, ref, mask);
// }
// PFNGLSTENCILFUNCSEPARATEPROC gl3wStencilFuncSeparate = mockgl3wStencilFuncSeparate;

// void  mockgl3wStencilMask(GLuint mask)
// {
//     return getMock()->gl3wStencilMask(mask);
// }
// PFNGLSTENCILMASKPROC gl3wStencilMask = mockgl3wStencilMask;

// void  mockgl3wStencilMaskSeparate(GLenum face, GLuint mask)
// {
//     return getMock()->gl3wStencilMaskSeparate(face, mask);
// }
// PFNGLSTENCILMASKSEPARATEPROC gl3wStencilMaskSeparate = mockgl3wStencilMaskSeparate;

// void  mockgl3wStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
// {
//     return getMock()->gl3wStencilOp(fail, zfail, zpass);
// }
// PFNGLSTENCILOPPROC gl3wStencilOp = mockgl3wStencilOp;

// void  mockgl3wStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
// {
//     return getMock()->gl3wStencilOpSeparate(face, sfail, dpfail, dppass);
// }
// PFNGLSTENCILOPSEPARATEPROC gl3wStencilOpSeparate = mockgl3wStencilOpSeparate;

// void  mockgl3wTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
// {
//     return getMock()->gl3wTexBuffer(target, internalformat, buffer);
// }
// PFNGLTEXBUFFERPROC gl3wTexBuffer = mockgl3wTexBuffer;

// void  mockgl3wTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
// {
//     return getMock()->gl3wTexBufferRange(target, internalformat, buffer, offset, size);
// }
// PFNGLTEXBUFFERRANGEPROC gl3wTexBufferRange = mockgl3wTexBufferRange;

// void  mockgl3wTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels)
// {
//     return getMock()->gl3wTexImage1D(target, level, internalformat, width, border, format, type, pixels);
// }
// PFNGLTEXIMAGE1DPROC gl3wTexImage1D = mockgl3wTexImage1D;

// void  mockgl3wTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)
// {
//     return getMock()->gl3wTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
// }
// PFNGLTEXIMAGE2DPROC gl3wTexImage2D = mockgl3wTexImage2D;

// void  mockgl3wTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
// {
//     return getMock()->gl3wTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
// }
// PFNGLTEXIMAGE2DMULTISAMPLEPROC gl3wTexImage2DMultisample = mockgl3wTexImage2DMultisample;

// void  mockgl3wTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
// {
//     return getMock()->gl3wTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
// }
// PFNGLTEXIMAGE3DPROC gl3wTexImage3D = mockgl3wTexImage3D;

// void  mockgl3wTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
// {
//     return getMock()->gl3wTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
// }
// PFNGLTEXIMAGE3DMULTISAMPLEPROC gl3wTexImage3DMultisample = mockgl3wTexImage3DMultisample;

// void  mockgl3wTexPageCommitmentARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean resident)
// {
//     return getMock()->gl3wTexPageCommitmentARB(target, level, xoffset, yoffset, zoffset, width, height, depth, resident);
// }
// PFNGLTEXPAGECOMMITMENTARBPROC gl3wTexPageCommitmentARB = mockgl3wTexPageCommitmentARB;

// void  mockgl3wTexParameterIiv(GLenum target, GLenum pname, const GLint * params)
// {
//     return getMock()->gl3wTexParameterIiv(target, pname, params);
// }
// PFNGLTEXPARAMETERIIVPROC gl3wTexParameterIiv = mockgl3wTexParameterIiv;

// void  mockgl3wTexParameterIuiv(GLenum target, GLenum pname, const GLuint * params)
// {
//     return getMock()->gl3wTexParameterIuiv(target, pname, params);
// }
// PFNGLTEXPARAMETERIUIVPROC gl3wTexParameterIuiv = mockgl3wTexParameterIuiv;

// void  mockgl3wTexParameterf(GLenum target, GLenum pname, GLfloat param)
// {
//     return getMock()->gl3wTexParameterf(target, pname, param);
// }
// PFNGLTEXPARAMETERFPROC gl3wTexParameterf = mockgl3wTexParameterf;

// void  mockgl3wTexParameterfv(GLenum target, GLenum pname, const GLfloat * params)
// {
//     return getMock()->gl3wTexParameterfv(target, pname, params);
// }
// PFNGLTEXPARAMETERFVPROC gl3wTexParameterfv = mockgl3wTexParameterfv;

// void  mockgl3wTexParameteri(GLenum target, GLenum pname, GLint param)
// {
//     return getMock()->gl3wTexParameteri(target, pname, param);
// }
// PFNGLTEXPARAMETERIPROC gl3wTexParameteri = mockgl3wTexParameteri;

// void  mockgl3wTexParameteriv(GLenum target, GLenum pname, const GLint * params)
// {
//     return getMock()->gl3wTexParameteriv(target, pname, params);
// }
// PFNGLTEXPARAMETERIVPROC gl3wTexParameteriv = mockgl3wTexParameteriv;

// void  mockgl3wTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
// {
//     return getMock()->gl3wTexStorage1D(target, levels, internalformat, width);
// }
// PFNGLTEXSTORAGE1DPROC gl3wTexStorage1D = mockgl3wTexStorage1D;

// void  mockgl3wTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wTexStorage2D(target, levels, internalformat, width, height);
// }
// PFNGLTEXSTORAGE2DPROC gl3wTexStorage2D = mockgl3wTexStorage2D;

// void  mockgl3wTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
// {
//     return getMock()->gl3wTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
// }
// PFNGLTEXSTORAGE2DMULTISAMPLEPROC gl3wTexStorage2DMultisample = mockgl3wTexStorage2DMultisample;

// void  mockgl3wTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
// {
//     return getMock()->gl3wTexStorage3D(target, levels, internalformat, width, height, depth);
// }
// PFNGLTEXSTORAGE3DPROC gl3wTexStorage3D = mockgl3wTexStorage3D;

// void  mockgl3wTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
// {
//     return getMock()->gl3wTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
// }
// PFNGLTEXSTORAGE3DMULTISAMPLEPROC gl3wTexStorage3DMultisample = mockgl3wTexStorage3DMultisample;

// void  mockgl3wTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
// {
//     return getMock()->gl3wTexSubImage1D(target, level, xoffset, width, format, type, pixels);
// }
// PFNGLTEXSUBIMAGE1DPROC gl3wTexSubImage1D = mockgl3wTexSubImage1D;

// void  mockgl3wTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
// {
//     return getMock()->gl3wTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
// }
// PFNGLTEXSUBIMAGE2DPROC gl3wTexSubImage2D = mockgl3wTexSubImage2D;

// void  mockgl3wTextureBarrier()
// {
//     return getMock()->gl3wTextureBarrier();
// }
// PFNGLTEXTUREBARRIERPROC gl3wTextureBarrier = mockgl3wTextureBarrier;

// void  mockgl3wTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer)
// {
//     return getMock()->gl3wTextureBuffer(texture, internalformat, buffer);
// }
// PFNGLTEXTUREBUFFERPROC gl3wTextureBuffer = mockgl3wTextureBuffer;

// void  mockgl3wTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizei size)
// {
//     return getMock()->gl3wTextureBufferRange(texture, internalformat, buffer, offset, size);
// }
// PFNGLTEXTUREBUFFERRANGEPROC gl3wTextureBufferRange = mockgl3wTextureBufferRange;

// void  mockgl3wTextureParameterIiv(GLuint texture, GLenum pname, const GLint * params)
// {
//     return getMock()->gl3wTextureParameterIiv(texture, pname, params);
// }
// PFNGLTEXTUREPARAMETERIIVPROC gl3wTextureParameterIiv = mockgl3wTextureParameterIiv;

// void  mockgl3wTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params)
// {
//     return getMock()->gl3wTextureParameterIuiv(texture, pname, params);
// }
// PFNGLTEXTUREPARAMETERIUIVPROC gl3wTextureParameterIuiv = mockgl3wTextureParameterIuiv;

// void  mockgl3wTextureParameterf(GLuint texture, GLenum pname, GLfloat param)
// {
//     return getMock()->gl3wTextureParameterf(texture, pname, param);
// }
// PFNGLTEXTUREPARAMETERFPROC gl3wTextureParameterf = mockgl3wTextureParameterf;

// void  mockgl3wTextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param)
// {
//     return getMock()->gl3wTextureParameterfv(texture, pname, param);
// }
// PFNGLTEXTUREPARAMETERFVPROC gl3wTextureParameterfv = mockgl3wTextureParameterfv;

// void  mockgl3wTextureParameteri(GLuint texture, GLenum pname, GLint param)
// {
//     return getMock()->gl3wTextureParameteri(texture, pname, param);
// }
// PFNGLTEXTUREPARAMETERIPROC gl3wTextureParameteri = mockgl3wTextureParameteri;

// void  mockgl3wTextureParameteriv(GLuint texture, GLenum pname, const GLint * param)
// {
//     return getMock()->gl3wTextureParameteriv(texture, pname, param);
// }
// PFNGLTEXTUREPARAMETERIVPROC gl3wTextureParameteriv = mockgl3wTextureParameteriv;

// void  mockgl3wTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width)
// {
//     return getMock()->gl3wTextureStorage1D(texture, levels, internalformat, width);
// }
// PFNGLTEXTURESTORAGE1DPROC gl3wTextureStorage1D = mockgl3wTextureStorage1D;

// void  mockgl3wTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wTextureStorage2D(texture, levels, internalformat, width, height);
// }
// PFNGLTEXTURESTORAGE2DPROC gl3wTextureStorage2D = mockgl3wTextureStorage2D;

// void  mockgl3wTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
// {
//     return getMock()->gl3wTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
// }
// PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC gl3wTextureStorage2DMultisample = mockgl3wTextureStorage2DMultisample;

// void  mockgl3wTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
// {
//     return getMock()->gl3wTextureStorage3D(texture, levels, internalformat, width, height, depth);
// }
// PFNGLTEXTURESTORAGE3DPROC gl3wTextureStorage3D = mockgl3wTextureStorage3D;

// void  mockgl3wTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
// {
//     return getMock()->gl3wTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
// }
// PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC gl3wTextureStorage3DMultisample = mockgl3wTextureStorage3DMultisample;

// void  mockgl3wTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
// {
//     return getMock()->gl3wTextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
// }
// PFNGLTEXTURESUBIMAGE1DPROC gl3wTextureSubImage1D = mockgl3wTextureSubImage1D;

// void  mockgl3wTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
// {
//     return getMock()->gl3wTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
// }
// PFNGLTEXTURESUBIMAGE2DPROC gl3wTextureSubImage2D = mockgl3wTextureSubImage2D;

// void  mockgl3wTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
// {
//     return getMock()->gl3wTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
// }
// PFNGLTEXTUREVIEWPROC gl3wTextureView = mockgl3wTextureView;

// void  mockgl3wTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer)
// {
//     return getMock()->gl3wTransformFeedbackBufferBase(xfb, index, buffer);
// }
// PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC gl3wTransformFeedbackBufferBase = mockgl3wTransformFeedbackBufferBase;

// void  mockgl3wTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizei size)
// {
//     return getMock()->gl3wTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
// }
// PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC gl3wTransformFeedbackBufferRange = mockgl3wTransformFeedbackBufferRange;

// void  mockgl3wTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const * varyings, GLenum bufferMode)
// {
//     return getMock()->gl3wTransformFeedbackVaryings(program, count, varyings, bufferMode);
// }
// PFNGLTRANSFORMFEEDBACKVARYINGSPROC gl3wTransformFeedbackVaryings = mockgl3wTransformFeedbackVaryings;

// void  mockgl3wUniform1d(GLint location, GLdouble x)
// {
//     return getMock()->gl3wUniform1d(location, x);
// }
// PFNGLUNIFORM1DPROC gl3wUniform1d = mockgl3wUniform1d;

// void  mockgl3wUniform1dv(GLint location, GLsizei count, const GLdouble * value)
// {
//     return getMock()->gl3wUniform1dv(location, count, value);
// }
// PFNGLUNIFORM1DVPROC gl3wUniform1dv = mockgl3wUniform1dv;

// void  mockgl3wUniform1f(GLint location, GLfloat v0)
// {
//     return getMock()->gl3wUniform1f(location, v0);
// }
// PFNGLUNIFORM1FPROC gl3wUniform1f = mockgl3wUniform1f;

// void  mockgl3wUniform1fv(GLint location, GLsizei count, const GLfloat * value)
// {
//     return getMock()->gl3wUniform1fv(location, count, value);
// }
// PFNGLUNIFORM1FVPROC gl3wUniform1fv = mockgl3wUniform1fv;

// void  mockgl3wUniform1i(GLint location, GLint v0)
// {
//     return getMock()->gl3wUniform1i(location, v0);
// }
// PFNGLUNIFORM1IPROC gl3wUniform1i = mockgl3wUniform1i;

// void  mockgl3wUniform1iv(GLint location, GLsizei count, const GLint * value)
// {
//     return getMock()->gl3wUniform1iv(location, count, value);
// }
// PFNGLUNIFORM1IVPROC gl3wUniform1iv = mockgl3wUniform1iv;

// void  mockgl3wUniform1ui(GLint location, GLuint v0)
// {
//     return getMock()->gl3wUniform1ui(location, v0);
// }
// PFNGLUNIFORM1UIPROC gl3wUniform1ui = mockgl3wUniform1ui;

// void  mockgl3wUniform1uiv(GLint location, GLsizei count, const GLuint * value)
// {
//     return getMock()->gl3wUniform1uiv(location, count, value);
// }
// PFNGLUNIFORM1UIVPROC gl3wUniform1uiv = mockgl3wUniform1uiv;

// void  mockgl3wUniform2d(GLint location, GLdouble x, GLdouble y)
// {
//     return getMock()->gl3wUniform2d(location, x, y);
// }
// PFNGLUNIFORM2DPROC gl3wUniform2d = mockgl3wUniform2d;

// void  mockgl3wUniform2dv(GLint location, GLsizei count, const GLdouble * value)
// {
//     return getMock()->gl3wUniform2dv(location, count, value);
// }
// PFNGLUNIFORM2DVPROC gl3wUniform2dv = mockgl3wUniform2dv;

// void  mockgl3wUniform2f(GLint location, GLfloat v0, GLfloat v1)
// {
//     return getMock()->gl3wUniform2f(location, v0, v1);
// }
// PFNGLUNIFORM2FPROC gl3wUniform2f = mockgl3wUniform2f;

// void  mockgl3wUniform2fv(GLint location, GLsizei count, const GLfloat * value)
// {
//     return getMock()->gl3wUniform2fv(location, count, value);
// }
// PFNGLUNIFORM2FVPROC gl3wUniform2fv = mockgl3wUniform2fv;

// void  mockgl3wUniform2i(GLint location, GLint v0, GLint v1)
// {
//     return getMock()->gl3wUniform2i(location, v0, v1);
// }
// PFNGLUNIFORM2IPROC gl3wUniform2i = mockgl3wUniform2i;

// void  mockgl3wUniform2iv(GLint location, GLsizei count, const GLint * value)
// {
//     return getMock()->gl3wUniform2iv(location, count, value);
// }
// PFNGLUNIFORM2IVPROC gl3wUniform2iv = mockgl3wUniform2iv;

// void  mockgl3wUniform2ui(GLint location, GLuint v0, GLuint v1)
// {
//     return getMock()->gl3wUniform2ui(location, v0, v1);
// }
// PFNGLUNIFORM2UIPROC gl3wUniform2ui = mockgl3wUniform2ui;

// void  mockgl3wUniform2uiv(GLint location, GLsizei count, const GLuint * value)
// {
//     return getMock()->gl3wUniform2uiv(location, count, value);
// }
// PFNGLUNIFORM2UIVPROC gl3wUniform2uiv = mockgl3wUniform2uiv;

// void  mockgl3wUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
// {
//     return getMock()->gl3wUniform3d(location, x, y, z);
// }
// PFNGLUNIFORM3DPROC gl3wUniform3d = mockgl3wUniform3d;

// void  mockgl3wUniform3dv(GLint location, GLsizei count, const GLdouble * value)
// {
//     return getMock()->gl3wUniform3dv(location, count, value);
// }
// PFNGLUNIFORM3DVPROC gl3wUniform3dv = mockgl3wUniform3dv;

// void  mockgl3wUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
// {
//     return getMock()->gl3wUniform3f(location, v0, v1, v2);
// }
// PFNGLUNIFORM3FPROC gl3wUniform3f = mockgl3wUniform3f;

// void  mockgl3wUniform3fv(GLint location, GLsizei count, const GLfloat * value)
// {
//     return getMock()->gl3wUniform3fv(location, count, value);
// }
// PFNGLUNIFORM3FVPROC gl3wUniform3fv = mockgl3wUniform3fv;

// void  mockgl3wUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
// {
//     return getMock()->gl3wUniform3i(location, v0, v1, v2);
// }
// PFNGLUNIFORM3IPROC gl3wUniform3i = mockgl3wUniform3i;

// void  mockgl3wUniform3iv(GLint location, GLsizei count, const GLint * value)
// {
//     return getMock()->gl3wUniform3iv(location, count, value);
// }
// PFNGLUNIFORM3IVPROC gl3wUniform3iv = mockgl3wUniform3iv;

// void  mockgl3wUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
// {
//     return getMock()->gl3wUniform3ui(location, v0, v1, v2);
// }
// PFNGLUNIFORM3UIPROC gl3wUniform3ui = mockgl3wUniform3ui;

// void  mockgl3wUniform3uiv(GLint location, GLsizei count, const GLuint * value)
// {
//     return getMock()->gl3wUniform3uiv(location, count, value);
// }
// PFNGLUNIFORM3UIVPROC gl3wUniform3uiv = mockgl3wUniform3uiv;

// void  mockgl3wUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
// {
//     return getMock()->gl3wUniform4d(location, x, y, z, w);
// }
// PFNGLUNIFORM4DPROC gl3wUniform4d = mockgl3wUniform4d;

// void  mockgl3wUniform4dv(GLint location, GLsizei count, const GLdouble * value)
// {
//     return getMock()->gl3wUniform4dv(location, count, value);
// }
// PFNGLUNIFORM4DVPROC gl3wUniform4dv = mockgl3wUniform4dv;

// void  mockgl3wUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
// {
//     return getMock()->gl3wUniform4f(location, v0, v1, v2, v3);
// }
// PFNGLUNIFORM4FPROC gl3wUniform4f = mockgl3wUniform4f;

// void  mockgl3wUniform4fv(GLint location, GLsizei count, const GLfloat * value)
// {
//     return getMock()->gl3wUniform4fv(location, count, value);
// }
// PFNGLUNIFORM4FVPROC gl3wUniform4fv = mockgl3wUniform4fv;

// void  mockgl3wUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
// {
//     return getMock()->gl3wUniform4i(location, v0, v1, v2, v3);
// }
// PFNGLUNIFORM4IPROC gl3wUniform4i = mockgl3wUniform4i;

// void  mockgl3wUniform4iv(GLint location, GLsizei count, const GLint * value)
// {
//     return getMock()->gl3wUniform4iv(location, count, value);
// }
// PFNGLUNIFORM4IVPROC gl3wUniform4iv = mockgl3wUniform4iv;

// void  mockgl3wUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
// {
//     return getMock()->gl3wUniform4ui(location, v0, v1, v2, v3);
// }
// PFNGLUNIFORM4UIPROC gl3wUniform4ui = mockgl3wUniform4ui;

// void  mockgl3wUniform4uiv(GLint location, GLsizei count, const GLuint * value)
// {
//     return getMock()->gl3wUniform4uiv(location, count, value);
// }
// PFNGLUNIFORM4UIVPROC gl3wUniform4uiv = mockgl3wUniform4uiv;

// void  mockgl3wUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
// {
//     return getMock()->gl3wUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
// }
// PFNGLUNIFORMBLOCKBINDINGPROC gl3wUniformBlockBinding = mockgl3wUniformBlockBinding;

// void  mockgl3wUniformHandleui64ARB(GLint location, GLuint64 value)
// {
//     return getMock()->gl3wUniformHandleui64ARB(location, value);
// }
// PFNGLUNIFORMHANDLEUI64ARBPROC gl3wUniformHandleui64ARB = mockgl3wUniformHandleui64ARB;

// void  mockgl3wUniformHandleui64vARB(GLint location, GLsizei count, const GLuint64 * value)
// {
//     return getMock()->gl3wUniformHandleui64vARB(location, count, value);
// }
// PFNGLUNIFORMHANDLEUI64VARBPROC gl3wUniformHandleui64vARB = mockgl3wUniformHandleui64vARB;

// void  mockgl3wUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix2dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX2DVPROC gl3wUniformMatrix2dv = mockgl3wUniformMatrix2dv;

// void  mockgl3wUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix2fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX2FVPROC gl3wUniformMatrix2fv = mockgl3wUniformMatrix2fv;

// void  mockgl3wUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix2x3dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX2X3DVPROC gl3wUniformMatrix2x3dv = mockgl3wUniformMatrix2x3dv;

// void  mockgl3wUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix2x3fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX2X3FVPROC gl3wUniformMatrix2x3fv = mockgl3wUniformMatrix2x3fv;

// void  mockgl3wUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix2x4dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX2X4DVPROC gl3wUniformMatrix2x4dv = mockgl3wUniformMatrix2x4dv;

// void  mockgl3wUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix2x4fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX2X4FVPROC gl3wUniformMatrix2x4fv = mockgl3wUniformMatrix2x4fv;

// void  mockgl3wUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix3dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX3DVPROC gl3wUniformMatrix3dv = mockgl3wUniformMatrix3dv;

// void  mockgl3wUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix3fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX3FVPROC gl3wUniformMatrix3fv = mockgl3wUniformMatrix3fv;

// void  mockgl3wUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix3x2dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX3X2DVPROC gl3wUniformMatrix3x2dv = mockgl3wUniformMatrix3x2dv;

// void  mockgl3wUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix3x2fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX3X2FVPROC gl3wUniformMatrix3x2fv = mockgl3wUniformMatrix3x2fv;

// void  mockgl3wUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix3x4dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX3X4DVPROC gl3wUniformMatrix3x4dv = mockgl3wUniformMatrix3x4dv;

// void  mockgl3wUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix3x4fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX3X4FVPROC gl3wUniformMatrix3x4fv = mockgl3wUniformMatrix3x4fv;

// void  mockgl3wUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix4dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX4DVPROC gl3wUniformMatrix4dv = mockgl3wUniformMatrix4dv;

// void  mockgl3wUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix4fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX4FVPROC gl3wUniformMatrix4fv = mockgl3wUniformMatrix4fv;

// void  mockgl3wUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix4x2dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX4X2DVPROC gl3wUniformMatrix4x2dv = mockgl3wUniformMatrix4x2dv;

// void  mockgl3wUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix4x2fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX4X2FVPROC gl3wUniformMatrix4x2fv = mockgl3wUniformMatrix4x2fv;

// void  mockgl3wUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
// {
//     return getMock()->gl3wUniformMatrix4x3dv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX4X3DVPROC gl3wUniformMatrix4x3dv = mockgl3wUniformMatrix4x3dv;

// void  mockgl3wUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
// {
//     return getMock()->gl3wUniformMatrix4x3fv(location, count, transpose, value);
// }
// PFNGLUNIFORMMATRIX4X3FVPROC gl3wUniformMatrix4x3fv = mockgl3wUniformMatrix4x3fv;

// void  mockgl3wUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices)
// {
//     return getMock()->gl3wUniformSubroutinesuiv(shadertype, count, indices);
// }
// PFNGLUNIFORMSUBROUTINESUIVPROC gl3wUniformSubroutinesuiv = mockgl3wUniformSubroutinesuiv;

// unsigned char  mockgl3wUnmapBuffer(GLenum target)
// {
//     return getMock()->gl3wUnmapBuffer(target);
// }
// PFNGLUNMAPBUFFERPROC gl3wUnmapBuffer = mockgl3wUnmapBuffer;

// unsigned char  mockgl3wUnmapNamedBuffer(GLuint buffer)
// {
//     return getMock()->gl3wUnmapNamedBuffer(buffer);
// }
// PFNGLUNMAPNAMEDBUFFERPROC gl3wUnmapNamedBuffer = mockgl3wUnmapNamedBuffer;

// void  mockgl3wUseProgram(GLuint program)
// {
//     return getMock()->gl3wUseProgram(program);
// }
// PFNGLUSEPROGRAMPROC gl3wUseProgram = mockgl3wUseProgram;

// void  mockgl3wUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
// {
//     return getMock()->gl3wUseProgramStages(pipeline, stages, program);
// }
// PFNGLUSEPROGRAMSTAGESPROC gl3wUseProgramStages = mockgl3wUseProgramStages;

// void  mockgl3wValidateProgram(GLuint program)
// {
//     return getMock()->gl3wValidateProgram(program);
// }
// PFNGLVALIDATEPROGRAMPROC gl3wValidateProgram = mockgl3wValidateProgram;

// void  mockgl3wValidateProgramPipeline(GLuint pipeline)
// {
//     return getMock()->gl3wValidateProgramPipeline(pipeline);
// }
// PFNGLVALIDATEPROGRAMPIPELINEPROC gl3wValidateProgramPipeline = mockgl3wValidateProgramPipeline;

// void  mockgl3wVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
// {
//     return getMock()->gl3wVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
// }
// PFNGLVERTEXARRAYATTRIBBINDINGPROC gl3wVertexArrayAttribBinding = mockgl3wVertexArrayAttribBinding;

// void  mockgl3wVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
// {
//     return getMock()->gl3wVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
// }
// PFNGLVERTEXARRAYATTRIBFORMATPROC gl3wVertexArrayAttribFormat = mockgl3wVertexArrayAttribFormat;

// void  mockgl3wVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
// {
//     return getMock()->gl3wVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
// }
// PFNGLVERTEXARRAYATTRIBIFORMATPROC gl3wVertexArrayAttribIFormat = mockgl3wVertexArrayAttribIFormat;

// void  mockgl3wVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
// {
//     return getMock()->gl3wVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
// }
// PFNGLVERTEXARRAYATTRIBLFORMATPROC gl3wVertexArrayAttribLFormat = mockgl3wVertexArrayAttribLFormat;

// void  mockgl3wVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor)
// {
//     return getMock()->gl3wVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
// }
// PFNGLVERTEXARRAYBINDINGDIVISORPROC gl3wVertexArrayBindingDivisor = mockgl3wVertexArrayBindingDivisor;

// void  mockgl3wVertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
// {
//     return getMock()->gl3wVertexArrayElementBuffer(vaobj, buffer);
// }
// PFNGLVERTEXARRAYELEMENTBUFFERPROC gl3wVertexArrayElementBuffer = mockgl3wVertexArrayElementBuffer;

// void  mockgl3wVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
// {
//     return getMock()->gl3wVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
// }
// PFNGLVERTEXARRAYVERTEXBUFFERPROC gl3wVertexArrayVertexBuffer = mockgl3wVertexArrayVertexBuffer;

// void  mockgl3wVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides)
// {
//     return getMock()->gl3wVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
// }
// PFNGLVERTEXARRAYVERTEXBUFFERSPROC gl3wVertexArrayVertexBuffers = mockgl3wVertexArrayVertexBuffers;

// void  mockgl3wVertexAttrib1d(GLuint index, GLdouble x)
// {
//     return getMock()->gl3wVertexAttrib1d(index, x);
// }
// PFNGLVERTEXATTRIB1DPROC gl3wVertexAttrib1d = mockgl3wVertexAttrib1d;

// void  mockgl3wVertexAttrib1dv(GLuint index, const GLdouble * v)
// {
//     return getMock()->gl3wVertexAttrib1dv(index, v);
// }
// PFNGLVERTEXATTRIB1DVPROC gl3wVertexAttrib1dv = mockgl3wVertexAttrib1dv;

// void  mockgl3wVertexAttrib1f(GLuint index, GLfloat x)
// {
//     return getMock()->gl3wVertexAttrib1f(index, x);
// }
// PFNGLVERTEXATTRIB1FPROC gl3wVertexAttrib1f = mockgl3wVertexAttrib1f;

// void  mockgl3wVertexAttrib1fv(GLuint index, const GLfloat * v)
// {
//     return getMock()->gl3wVertexAttrib1fv(index, v);
// }
// PFNGLVERTEXATTRIB1FVPROC gl3wVertexAttrib1fv = mockgl3wVertexAttrib1fv;

// void  mockgl3wVertexAttrib1s(GLuint index, GLshort x)
// {
//     return getMock()->gl3wVertexAttrib1s(index, x);
// }
// PFNGLVERTEXATTRIB1SPROC gl3wVertexAttrib1s = mockgl3wVertexAttrib1s;

// void  mockgl3wVertexAttrib1sv(GLuint index, const GLshort * v)
// {
//     return getMock()->gl3wVertexAttrib1sv(index, v);
// }
// PFNGLVERTEXATTRIB1SVPROC gl3wVertexAttrib1sv = mockgl3wVertexAttrib1sv;

// void  mockgl3wVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
// {
//     return getMock()->gl3wVertexAttrib2d(index, x, y);
// }
// PFNGLVERTEXATTRIB2DPROC gl3wVertexAttrib2d = mockgl3wVertexAttrib2d;

// void  mockgl3wVertexAttrib2dv(GLuint index, const GLdouble * v)
// {
//     return getMock()->gl3wVertexAttrib2dv(index, v);
// }
// PFNGLVERTEXATTRIB2DVPROC gl3wVertexAttrib2dv = mockgl3wVertexAttrib2dv;

// void  mockgl3wVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
// {
//     return getMock()->gl3wVertexAttrib2f(index, x, y);
// }
// PFNGLVERTEXATTRIB2FPROC gl3wVertexAttrib2f = mockgl3wVertexAttrib2f;

// void  mockgl3wVertexAttrib2fv(GLuint index, const GLfloat * v)
// {
//     return getMock()->gl3wVertexAttrib2fv(index, v);
// }
// PFNGLVERTEXATTRIB2FVPROC gl3wVertexAttrib2fv = mockgl3wVertexAttrib2fv;

// void  mockgl3wVertexAttrib2s(GLuint index, GLshort x, GLshort y)
// {
//     return getMock()->gl3wVertexAttrib2s(index, x, y);
// }
// PFNGLVERTEXATTRIB2SPROC gl3wVertexAttrib2s = mockgl3wVertexAttrib2s;

// void  mockgl3wVertexAttrib2sv(GLuint index, const GLshort * v)
// {
//     return getMock()->gl3wVertexAttrib2sv(index, v);
// }
// PFNGLVERTEXATTRIB2SVPROC gl3wVertexAttrib2sv = mockgl3wVertexAttrib2sv;

// void  mockgl3wVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
// {
//     return getMock()->gl3wVertexAttrib3d(index, x, y, z);
// }
// PFNGLVERTEXATTRIB3DPROC gl3wVertexAttrib3d = mockgl3wVertexAttrib3d;

// void  mockgl3wVertexAttrib3dv(GLuint index, const GLdouble * v)
// {
//     return getMock()->gl3wVertexAttrib3dv(index, v);
// }
// PFNGLVERTEXATTRIB3DVPROC gl3wVertexAttrib3dv = mockgl3wVertexAttrib3dv;

// void  mockgl3wVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
// {
//     return getMock()->gl3wVertexAttrib3f(index, x, y, z);
// }
// PFNGLVERTEXATTRIB3FPROC gl3wVertexAttrib3f = mockgl3wVertexAttrib3f;

// void  mockgl3wVertexAttrib3fv(GLuint index, const GLfloat * v)
// {
//     return getMock()->gl3wVertexAttrib3fv(index, v);
// }
// PFNGLVERTEXATTRIB3FVPROC gl3wVertexAttrib3fv = mockgl3wVertexAttrib3fv;

// void  mockgl3wVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
// {
//     return getMock()->gl3wVertexAttrib3s(index, x, y, z);
// }
// PFNGLVERTEXATTRIB3SPROC gl3wVertexAttrib3s = mockgl3wVertexAttrib3s;

// void  mockgl3wVertexAttrib3sv(GLuint index, const GLshort * v)
// {
//     return getMock()->gl3wVertexAttrib3sv(index, v);
// }
// PFNGLVERTEXATTRIB3SVPROC gl3wVertexAttrib3sv = mockgl3wVertexAttrib3sv;

// void  mockgl3wVertexAttrib4Nbv(GLuint index, const GLbyte * v)
// {
//     return getMock()->gl3wVertexAttrib4Nbv(index, v);
// }
// PFNGLVERTEXATTRIB4NBVPROC gl3wVertexAttrib4Nbv = mockgl3wVertexAttrib4Nbv;

// void  mockgl3wVertexAttrib4Niv(GLuint index, const GLint * v)
// {
//     return getMock()->gl3wVertexAttrib4Niv(index, v);
// }
// PFNGLVERTEXATTRIB4NIVPROC gl3wVertexAttrib4Niv = mockgl3wVertexAttrib4Niv;

// void  mockgl3wVertexAttrib4Nsv(GLuint index, const GLshort * v)
// {
//     return getMock()->gl3wVertexAttrib4Nsv(index, v);
// }
// PFNGLVERTEXATTRIB4NSVPROC gl3wVertexAttrib4Nsv = mockgl3wVertexAttrib4Nsv;

// void  mockgl3wVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
// {
//     return getMock()->gl3wVertexAttrib4Nub(index, x, y, z, w);
// }
// PFNGLVERTEXATTRIB4NUBPROC gl3wVertexAttrib4Nub = mockgl3wVertexAttrib4Nub;

// void  mockgl3wVertexAttrib4Nubv(GLuint index, const GLubyte * v)
// {
//     return getMock()->gl3wVertexAttrib4Nubv(index, v);
// }
// PFNGLVERTEXATTRIB4NUBVPROC gl3wVertexAttrib4Nubv = mockgl3wVertexAttrib4Nubv;

// void  mockgl3wVertexAttrib4Nuiv(GLuint index, const GLuint * v)
// {
//     return getMock()->gl3wVertexAttrib4Nuiv(index, v);
// }
// PFNGLVERTEXATTRIB4NUIVPROC gl3wVertexAttrib4Nuiv = mockgl3wVertexAttrib4Nuiv;

// void  mockgl3wVertexAttrib4Nusv(GLuint index, const GLushort * v)
// {
//     return getMock()->gl3wVertexAttrib4Nusv(index, v);
// }
// PFNGLVERTEXATTRIB4NUSVPROC gl3wVertexAttrib4Nusv = mockgl3wVertexAttrib4Nusv;

// void  mockgl3wVertexAttrib4bv(GLuint index, const GLbyte * v)
// {
//     return getMock()->gl3wVertexAttrib4bv(index, v);
// }
// PFNGLVERTEXATTRIB4BVPROC gl3wVertexAttrib4bv = mockgl3wVertexAttrib4bv;

// void  mockgl3wVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
// {
//     return getMock()->gl3wVertexAttrib4d(index, x, y, z, w);
// }
// PFNGLVERTEXATTRIB4DPROC gl3wVertexAttrib4d = mockgl3wVertexAttrib4d;

// void  mockgl3wVertexAttrib4dv(GLuint index, const GLdouble * v)
// {
//     return getMock()->gl3wVertexAttrib4dv(index, v);
// }
// PFNGLVERTEXATTRIB4DVPROC gl3wVertexAttrib4dv = mockgl3wVertexAttrib4dv;

// void  mockgl3wVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
// {
//     return getMock()->gl3wVertexAttrib4f(index, x, y, z, w);
// }
// PFNGLVERTEXATTRIB4FPROC gl3wVertexAttrib4f = mockgl3wVertexAttrib4f;

// void  mockgl3wVertexAttrib4fv(GLuint index, const GLfloat * v)
// {
//     return getMock()->gl3wVertexAttrib4fv(index, v);
// }
// PFNGLVERTEXATTRIB4FVPROC gl3wVertexAttrib4fv = mockgl3wVertexAttrib4fv;

// void  mockgl3wVertexAttrib4iv(GLuint index, const GLint * v)
// {
//     return getMock()->gl3wVertexAttrib4iv(index, v);
// }
// PFNGLVERTEXATTRIB4IVPROC gl3wVertexAttrib4iv = mockgl3wVertexAttrib4iv;

// void  mockgl3wVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
// {
//     return getMock()->gl3wVertexAttrib4s(index, x, y, z, w);
// }
// PFNGLVERTEXATTRIB4SPROC gl3wVertexAttrib4s = mockgl3wVertexAttrib4s;

// void  mockgl3wVertexAttrib4sv(GLuint index, const GLshort * v)
// {
//     return getMock()->gl3wVertexAttrib4sv(index, v);
// }
// PFNGLVERTEXATTRIB4SVPROC gl3wVertexAttrib4sv = mockgl3wVertexAttrib4sv;

// void  mockgl3wVertexAttrib4ubv(GLuint index, const GLubyte * v)
// {
//     return getMock()->gl3wVertexAttrib4ubv(index, v);
// }
// PFNGLVERTEXATTRIB4UBVPROC gl3wVertexAttrib4ubv = mockgl3wVertexAttrib4ubv;

// void  mockgl3wVertexAttrib4uiv(GLuint index, const GLuint * v)
// {
//     return getMock()->gl3wVertexAttrib4uiv(index, v);
// }
// PFNGLVERTEXATTRIB4UIVPROC gl3wVertexAttrib4uiv = mockgl3wVertexAttrib4uiv;

// void  mockgl3wVertexAttrib4usv(GLuint index, const GLushort * v)
// {
//     return getMock()->gl3wVertexAttrib4usv(index, v);
// }
// PFNGLVERTEXATTRIB4USVPROC gl3wVertexAttrib4usv = mockgl3wVertexAttrib4usv;

// void  mockgl3wVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
// {
//     return getMock()->gl3wVertexAttribBinding(attribindex, bindingindex);
// }
// PFNGLVERTEXATTRIBBINDINGPROC gl3wVertexAttribBinding = mockgl3wVertexAttribBinding;

// void  mockgl3wVertexAttribDivisor(GLuint index, GLuint divisor)
// {
//     return getMock()->gl3wVertexAttribDivisor(index, divisor);
// }
// PFNGLVERTEXATTRIBDIVISORPROC gl3wVertexAttribDivisor = mockgl3wVertexAttribDivisor;

// void  mockgl3wVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
// {
//     return getMock()->gl3wVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
// }
// PFNGLVERTEXATTRIBFORMATPROC gl3wVertexAttribFormat = mockgl3wVertexAttribFormat;

// void  mockgl3wVertexAttribI1i(GLuint index, GLint x)
// {
//     return getMock()->gl3wVertexAttribI1i(index, x);
// }
// PFNGLVERTEXATTRIBI1IPROC gl3wVertexAttribI1i = mockgl3wVertexAttribI1i;

// void  mockgl3wVertexAttribI1iv(GLuint index, const GLint * v)
// {
//     return getMock()->gl3wVertexAttribI1iv(index, v);
// }
// PFNGLVERTEXATTRIBI1IVPROC gl3wVertexAttribI1iv = mockgl3wVertexAttribI1iv;

// void  mockgl3wVertexAttribI1ui(GLuint index, GLuint x)
// {
//     return getMock()->gl3wVertexAttribI1ui(index, x);
// }
// PFNGLVERTEXATTRIBI1UIPROC gl3wVertexAttribI1ui = mockgl3wVertexAttribI1ui;

// void  mockgl3wVertexAttribI1uiv(GLuint index, const GLuint * v)
// {
//     return getMock()->gl3wVertexAttribI1uiv(index, v);
// }
// PFNGLVERTEXATTRIBI1UIVPROC gl3wVertexAttribI1uiv = mockgl3wVertexAttribI1uiv;

// void  mockgl3wVertexAttribI2i(GLuint index, GLint x, GLint y)
// {
//     return getMock()->gl3wVertexAttribI2i(index, x, y);
// }
// PFNGLVERTEXATTRIBI2IPROC gl3wVertexAttribI2i = mockgl3wVertexAttribI2i;

// void  mockgl3wVertexAttribI2iv(GLuint index, const GLint * v)
// {
//     return getMock()->gl3wVertexAttribI2iv(index, v);
// }
// PFNGLVERTEXATTRIBI2IVPROC gl3wVertexAttribI2iv = mockgl3wVertexAttribI2iv;

// void  mockgl3wVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
// {
//     return getMock()->gl3wVertexAttribI2ui(index, x, y);
// }
// PFNGLVERTEXATTRIBI2UIPROC gl3wVertexAttribI2ui = mockgl3wVertexAttribI2ui;

// void  mockgl3wVertexAttribI2uiv(GLuint index, const GLuint * v)
// {
//     return getMock()->gl3wVertexAttribI2uiv(index, v);
// }
// PFNGLVERTEXATTRIBI2UIVPROC gl3wVertexAttribI2uiv = mockgl3wVertexAttribI2uiv;

// void  mockgl3wVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
// {
//     return getMock()->gl3wVertexAttribI3i(index, x, y, z);
// }
// PFNGLVERTEXATTRIBI3IPROC gl3wVertexAttribI3i = mockgl3wVertexAttribI3i;

// void  mockgl3wVertexAttribI3iv(GLuint index, const GLint * v)
// {
//     return getMock()->gl3wVertexAttribI3iv(index, v);
// }
// PFNGLVERTEXATTRIBI3IVPROC gl3wVertexAttribI3iv = mockgl3wVertexAttribI3iv;

// void  mockgl3wVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
// {
//     return getMock()->gl3wVertexAttribI3ui(index, x, y, z);
// }
// PFNGLVERTEXATTRIBI3UIPROC gl3wVertexAttribI3ui = mockgl3wVertexAttribI3ui;

// void  mockgl3wVertexAttribI3uiv(GLuint index, const GLuint * v)
// {
//     return getMock()->gl3wVertexAttribI3uiv(index, v);
// }
// PFNGLVERTEXATTRIBI3UIVPROC gl3wVertexAttribI3uiv = mockgl3wVertexAttribI3uiv;

// void  mockgl3wVertexAttribI4bv(GLuint index, const GLbyte * v)
// {
//     return getMock()->gl3wVertexAttribI4bv(index, v);
// }
// PFNGLVERTEXATTRIBI4BVPROC gl3wVertexAttribI4bv = mockgl3wVertexAttribI4bv;

// void  mockgl3wVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
// {
//     return getMock()->gl3wVertexAttribI4i(index, x, y, z, w);
// }
// PFNGLVERTEXATTRIBI4IPROC gl3wVertexAttribI4i = mockgl3wVertexAttribI4i;

// void  mockgl3wVertexAttribI4iv(GLuint index, const GLint * v)
// {
//     return getMock()->gl3wVertexAttribI4iv(index, v);
// }
// PFNGLVERTEXATTRIBI4IVPROC gl3wVertexAttribI4iv = mockgl3wVertexAttribI4iv;

// void  mockgl3wVertexAttribI4sv(GLuint index, const GLshort * v)
// {
//     return getMock()->gl3wVertexAttribI4sv(index, v);
// }
// PFNGLVERTEXATTRIBI4SVPROC gl3wVertexAttribI4sv = mockgl3wVertexAttribI4sv;

// void  mockgl3wVertexAttribI4ubv(GLuint index, const GLubyte * v)
// {
//     return getMock()->gl3wVertexAttribI4ubv(index, v);
// }
// PFNGLVERTEXATTRIBI4UBVPROC gl3wVertexAttribI4ubv = mockgl3wVertexAttribI4ubv;

// void  mockgl3wVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
// {
//     return getMock()->gl3wVertexAttribI4ui(index, x, y, z, w);
// }
// PFNGLVERTEXATTRIBI4UIPROC gl3wVertexAttribI4ui = mockgl3wVertexAttribI4ui;

// void  mockgl3wVertexAttribI4uiv(GLuint index, const GLuint * v)
// {
//     return getMock()->gl3wVertexAttribI4uiv(index, v);
// }
// PFNGLVERTEXATTRIBI4UIVPROC gl3wVertexAttribI4uiv = mockgl3wVertexAttribI4uiv;

// void  mockgl3wVertexAttribI4usv(GLuint index, const GLushort * v)
// {
//     return getMock()->gl3wVertexAttribI4usv(index, v);
// }
// PFNGLVERTEXATTRIBI4USVPROC gl3wVertexAttribI4usv = mockgl3wVertexAttribI4usv;

// void  mockgl3wVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
// {
//     return getMock()->gl3wVertexAttribIFormat(attribindex, size, type, relativeoffset);
// }
// PFNGLVERTEXATTRIBIFORMATPROC gl3wVertexAttribIFormat = mockgl3wVertexAttribIFormat;

// void  mockgl3wVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
// {
//     return getMock()->gl3wVertexAttribIPointer(index, size, type, stride, pointer);
// }
// PFNGLVERTEXATTRIBIPOINTERPROC gl3wVertexAttribIPointer = mockgl3wVertexAttribIPointer;

// void  mockgl3wVertexAttribL1d(GLuint index, GLdouble x)
// {
//     return getMock()->gl3wVertexAttribL1d(index, x);
// }
// PFNGLVERTEXATTRIBL1DPROC gl3wVertexAttribL1d = mockgl3wVertexAttribL1d;

// void  mockgl3wVertexAttribL1dv(GLuint index, const GLdouble * v)
// {
//     return getMock()->gl3wVertexAttribL1dv(index, v);
// }
// PFNGLVERTEXATTRIBL1DVPROC gl3wVertexAttribL1dv = mockgl3wVertexAttribL1dv;

// void  mockgl3wVertexAttribL1ui64ARB(GLuint index, GLuint64EXT x)
// {
//     return getMock()->gl3wVertexAttribL1ui64ARB(index, x);
// }
// PFNGLVERTEXATTRIBL1UI64ARBPROC gl3wVertexAttribL1ui64ARB = mockgl3wVertexAttribL1ui64ARB;

// void  mockgl3wVertexAttribL1ui64vARB(GLuint index, const GLuint64EXT * v)
// {
//     return getMock()->gl3wVertexAttribL1ui64vARB(index, v);
// }
// PFNGLVERTEXATTRIBL1UI64VARBPROC gl3wVertexAttribL1ui64vARB = mockgl3wVertexAttribL1ui64vARB;

// void  mockgl3wVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
// {
//     return getMock()->gl3wVertexAttribL2d(index, x, y);
// }
// PFNGLVERTEXATTRIBL2DPROC gl3wVertexAttribL2d = mockgl3wVertexAttribL2d;

// void  mockgl3wVertexAttribL2dv(GLuint index, const GLdouble * v)
// {
//     return getMock()->gl3wVertexAttribL2dv(index, v);
// }
// PFNGLVERTEXATTRIBL2DVPROC gl3wVertexAttribL2dv = mockgl3wVertexAttribL2dv;

// void  mockgl3wVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
// {
//     return getMock()->gl3wVertexAttribL3d(index, x, y, z);
// }
// PFNGLVERTEXATTRIBL3DPROC gl3wVertexAttribL3d = mockgl3wVertexAttribL3d;

// void  mockgl3wVertexAttribL3dv(GLuint index, const GLdouble * v)
// {
//     return getMock()->gl3wVertexAttribL3dv(index, v);
// }
// PFNGLVERTEXATTRIBL3DVPROC gl3wVertexAttribL3dv = mockgl3wVertexAttribL3dv;

// void  mockgl3wVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
// {
//     return getMock()->gl3wVertexAttribL4d(index, x, y, z, w);
// }
// PFNGLVERTEXATTRIBL4DPROC gl3wVertexAttribL4d = mockgl3wVertexAttribL4d;

// void  mockgl3wVertexAttribL4dv(GLuint index, const GLdouble * v)
// {
//     return getMock()->gl3wVertexAttribL4dv(index, v);
// }
// PFNGLVERTEXATTRIBL4DVPROC gl3wVertexAttribL4dv = mockgl3wVertexAttribL4dv;

// void  mockgl3wVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
// {
//     return getMock()->gl3wVertexAttribLFormat(attribindex, size, type, relativeoffset);
// }
// PFNGLVERTEXATTRIBLFORMATPROC gl3wVertexAttribLFormat = mockgl3wVertexAttribLFormat;

// void  mockgl3wVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
// {
//     return getMock()->gl3wVertexAttribLPointer(index, size, type, stride, pointer);
// }
// PFNGLVERTEXATTRIBLPOINTERPROC gl3wVertexAttribLPointer = mockgl3wVertexAttribLPointer;

// void  mockgl3wVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
// {
//     return getMock()->gl3wVertexAttribP1ui(index, type, normalized, value);
// }
// PFNGLVERTEXATTRIBP1UIPROC gl3wVertexAttribP1ui = mockgl3wVertexAttribP1ui;

// void  mockgl3wVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
// {
//     return getMock()->gl3wVertexAttribP1uiv(index, type, normalized, value);
// }
// PFNGLVERTEXATTRIBP1UIVPROC gl3wVertexAttribP1uiv = mockgl3wVertexAttribP1uiv;

// void  mockgl3wVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
// {
//     return getMock()->gl3wVertexAttribP2ui(index, type, normalized, value);
// }
// PFNGLVERTEXATTRIBP2UIPROC gl3wVertexAttribP2ui = mockgl3wVertexAttribP2ui;

// void  mockgl3wVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
// {
//     return getMock()->gl3wVertexAttribP2uiv(index, type, normalized, value);
// }
// PFNGLVERTEXATTRIBP2UIVPROC gl3wVertexAttribP2uiv = mockgl3wVertexAttribP2uiv;

// void  mockgl3wVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
// {
//     return getMock()->gl3wVertexAttribP3ui(index, type, normalized, value);
// }
// PFNGLVERTEXATTRIBP3UIPROC gl3wVertexAttribP3ui = mockgl3wVertexAttribP3ui;

// void  mockgl3wVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
// {
//     return getMock()->gl3wVertexAttribP3uiv(index, type, normalized, value);
// }
// PFNGLVERTEXATTRIBP3UIVPROC gl3wVertexAttribP3uiv = mockgl3wVertexAttribP3uiv;

// void  mockgl3wVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
// {
//     return getMock()->gl3wVertexAttribP4ui(index, type, normalized, value);
// }
// PFNGLVERTEXATTRIBP4UIPROC gl3wVertexAttribP4ui = mockgl3wVertexAttribP4ui;

// void  mockgl3wVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
// {
//     return getMock()->gl3wVertexAttribP4uiv(index, type, normalized, value);
// }
// PFNGLVERTEXATTRIBP4UIVPROC gl3wVertexAttribP4uiv = mockgl3wVertexAttribP4uiv;

// void  mockgl3wVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
// {
//     return getMock()->gl3wVertexAttribPointer(index, size, type, normalized, stride, pointer);
// }
// PFNGLVERTEXATTRIBPOINTERPROC gl3wVertexAttribPointer = mockgl3wVertexAttribPointer;

// void  mockgl3wVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
// {
//     return getMock()->gl3wVertexBindingDivisor(bindingindex, divisor);
// }
// PFNGLVERTEXBINDINGDIVISORPROC gl3wVertexBindingDivisor = mockgl3wVertexBindingDivisor;

// void  mockgl3wViewport(GLint x, GLint y, GLsizei width, GLsizei height)
// {
//     return getMock()->gl3wViewport(x, y, width, height);
// }
// PFNGLVIEWPORTPROC gl3wViewport = mockgl3wViewport;

// void  mockgl3wViewportArrayv(GLuint first, GLsizei count, const GLfloat * v)
// {
//     return getMock()->gl3wViewportArrayv(first, count, v);
// }
// PFNGLVIEWPORTARRAYVPROC gl3wViewportArrayv = mockgl3wViewportArrayv;

// void  mockgl3wViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
// {
//     return getMock()->gl3wViewportIndexedf(index, x, y, w, h);
// }
// PFNGLVIEWPORTINDEXEDFPROC gl3wViewportIndexedf = mockgl3wViewportIndexedf;

// void  mockgl3wViewportIndexedfv(GLuint index, const GLfloat * v)
// {
//     return getMock()->gl3wViewportIndexedfv(index, v);
// }
// PFNGLVIEWPORTINDEXEDFVPROC gl3wViewportIndexedfv = mockgl3wViewportIndexedfv;

// void  mockgl3wWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
// {
//     return getMock()->gl3wWaitSync(sync, flags, timeout);
// }
// PFNGLWAITSYNCPROC gl3wWaitSync = mockgl3wWaitSync;

