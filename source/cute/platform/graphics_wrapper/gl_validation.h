#ifndef OPENGL_VALIDATION_H
#define OPENGL_VALIDATION_H

#include <glad/glad.h>
#include <string>
#include <iostream>

#ifdef _DEBUG
#define GL_VALIDATION
#endif

#if defined(GL_VALIDATION)

inline void gl_check_error_(const char *file, int line);
inline void glBlitFramebuffer_(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter, const char *file, int line)
{
    glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    gl_check_error_(file, line);
}
inline void glReadBuffer_(GLenum src, const char *file, int line)
{
    glReadBuffer(src);
    gl_check_error_(file, line);
}
inline GLint glGetUniformLocation_(GLuint program, const GLchar *name, const char *file, int line)
{
    GLint location = glGetUniformLocation(program, name);
    gl_check_error_(file, line);
    return location;
}
inline void glEnable_(GLenum cap, const char *file, int line)
{
    glEnable(cap);
    gl_check_error_(file, line);
}
inline void glDepthFunc_(GLenum func, const char *file, int line)
{
    glDepthFunc(func);
    gl_check_error_(file, line);
}
inline void glDepthMask_(GLboolean flag, const char *file, int line)
{
    glDepthMask(flag);
    gl_check_error_(file, line);
}
inline void glGenBuffers_(GLsizei n, GLuint *buffers, const char *file, int line)
{
    glGenBuffers(n, buffers);
    gl_check_error_(file, line);
}
inline void glDeleteBuffers_(GLsizei n, const GLuint *buffers, const char *file, int line)
{
    glDeleteBuffers(n, buffers);
    gl_check_error_(file, line);
}
inline void glBindBuffer_(GLenum target, GLuint buffer, const char *file, int line)
{
    glBindBuffer(target, buffer);
    gl_check_error_(file, line);
}
inline void glGenFramebuffers_(GLsizei n, GLuint *framebuffers, const char *file, int line)
{
    glGenFramebuffers(n, framebuffers);
    gl_check_error_(file, line);
}
inline void glDeleteFramebuffers_(GLsizei n, const GLuint *framebuffers, const char *file, int line)
{
    glDeleteFramebuffers(n, framebuffers);
    gl_check_error_(file, line);
}
inline void glBindFramebuffer_(GLenum target, GLuint framebuffer, const char *file, int line)
{
    glBindFramebuffer(target, framebuffer);
    gl_check_error_(file, line);
}
inline void glGetIntegerv_(GLenum pname, GLint *data, const char *file, int line)
{
    glGetIntegerv(pname, data);
    gl_check_error_(file, line);
}
inline void glGenRenderbuffers_(GLsizei n, GLuint *renderbuffers, const char *file, int line)
{
    glGenRenderbuffers(n, renderbuffers);
    gl_check_error_(file, line);
}
inline void glDeleteRenderbuffers_(GLsizei n, const GLuint *renderbuffers, const char *file, int line)
{
    glDeleteRenderbuffers(n, renderbuffers);
    gl_check_error_(file, line);
}
inline void glBindRenderbuffer_(GLenum target, GLuint renderbuffer, const char *file, int line)
{
    glBindRenderbuffer(target, renderbuffer);
    gl_check_error_(file, line);
}
inline void glShaderSource_(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length, const char *file, int line)
{
    glShaderSource(shader, count, string, length);
    gl_check_error_(file, line);
}
inline void glCompileShader_(GLuint shader, const char *file, int line)
{
    glCompileShader(shader);
    gl_check_error_(file, line);
}
inline void glGetShaderiv_(GLuint shader, GLenum pname, GLint *params, const char *file, int line)
{
    glGetShaderiv(shader, pname, params);
    gl_check_error_(file, line);
}
inline void glGetShaderInfoLog_(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char *file, int line)
{
    glGetShaderInfoLog(shader, bufSize, length, infoLog);
    gl_check_error_(file, line);
}
inline void glDeleteShader_(GLuint shader, const char *file, int line)
{
    glDeleteShader(shader);
    gl_check_error_(file, line);
}
inline GLuint glCreateShader_(GLenum type, const char *file, int line)
{
    GLuint id = glCreateShader(type);
    gl_check_error_(file, line);
    return id;
}
inline GLuint glCreateProgram_(const char *file, int line)
{
    GLuint id = glCreateProgram();
    gl_check_error_(file, line);
    return id;
}
inline void glGetProgramiv_(GLuint program, GLenum pname, GLint *params, const char *file, int line)
{
    glGetProgramiv(program, pname, params);
    gl_check_error_(file, line);
}
inline void glDeleteProgram_(GLuint program, const char *file, int line)
{
    glDeleteProgram(program);
    gl_check_error_(file, line);
}
inline void glLinkProgram_(GLuint program, const char *file, int line)
{
    glLinkProgram(program);
    gl_check_error_(file, line);
}
inline void glAttachShader_(GLuint program, GLuint shader, const char *file, int line)
{
    glAttachShader(program, shader);
    gl_check_error_(file, line);
}
inline void glGetProgramInfoLog_(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog, const char *file, int line)
{
    glGetProgramInfoLog(program, bufSize, length, infoLog);
    gl_check_error_(file, line);
}
inline void glUseProgram_(GLuint program, const char *file, int line)
{
    glUseProgram(program);
    gl_check_error_(file, line);
}
inline void glUniform1f_(GLint location, GLfloat v0, const char *file, int line)
{
    glUniform1f(location, v0);
    gl_check_error_(file, line);
}
inline void glUniform2f_(GLint location, GLfloat v0, GLfloat v1, const char *file, int line)
{
    glUniform2f(location, v0, v1);
    gl_check_error_(file, line);
}
inline void glUniform3f_(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, const char *file, int line)
{
    glUniform3f(location, v0, v1, v2);
    gl_check_error_(file, line);
}
inline void glUniform4f_(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3, const char *file, int line)
{
    glUniform4f(location, v0, v1, v2, v3);
    gl_check_error_(file, line);
}
inline void glUniform1i_(GLint location, GLint v0, const char *file, int line)
{
    glUniform1i(location, v0);
    gl_check_error_(file, line);
}
inline void glUniform4fv_(GLint location, GLsizei count, const GLfloat *value, const char *file, int line)
{
    glUniform4fv(location, count, value);
    gl_check_error_(file, line);
}
inline void glUniformMatrix3fv_(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char *file, int line)
{
    glUniformMatrix3fv(location, count, transpose, value);
    gl_check_error_(file, line);
}
inline void glUniformMatrix4fv_(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value, const char *file, int line)
{
    glUniformMatrix4fv(location, count, transpose, value);
    gl_check_error_(file, line);
}
inline void glUniformBlockBinding_(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding, const char *file, int line)
{
    glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
    gl_check_error_(file, line);
}
inline void glGenVertexArrays_(GLsizei n, GLuint *arrays, const char *file, int line)
{
    glGenVertexArrays(n, arrays);
    gl_check_error_(file, line);
}
inline void glDeleteVertexArrays_(GLsizei n, const GLuint *arrays, const char *file, int line)
{
    glDeleteVertexArrays(n, arrays);
    gl_check_error_(file, line);
}
inline void glBindVertexArray_(GLuint array, const char *file, int line)
{
    glBindVertexArray(array);
    gl_check_error_(file, line);
}
inline void glTexParameteri_(GLenum target, GLenum pname, GLint param, const char *file, int line)
{
    glTexParameteri(target, pname, param);
    gl_check_error_(file, line);
}
inline void glGetFloatv_(GLenum pname, GLfloat *data, const char *file, int line)
{
    glGetFloatv(pname, data);
    gl_check_error_(file, line);
}
inline void glTexParameterf_(GLenum target, GLenum pname, GLfloat param, const char *file, int line)
{
    glTexParameterf(target, pname, param);
    gl_check_error_(file, line);
}
inline void glGenTextures_(GLsizei n, GLuint *textures, const char *file, int line)
{
    glGenTextures(n, textures);
    gl_check_error_(file, line);
}
inline void glDeleteTextures_(GLsizei n, const GLuint *textures, const char *file, int line)
{
    glDeleteTextures(n, textures);
    gl_check_error_(file, line);
}
inline void glBindTexture_(GLenum target, GLuint texture, const char *file, int line)
{
    glBindTexture(target, texture);
    gl_check_error_(file, line);
}
inline void glGenerateMipmap_(GLenum target, const char *file, int line)
{
    glGenerateMipmap(target);
    gl_check_error_(file, line);
}
inline void glTexImage2D_(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels, const char *file, int line)
{
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    gl_check_error_(file, line);
}
inline void glTexImage3D_(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels, const char *file, int line)
{
    glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
    gl_check_error_(file, line);
}
inline void glDisable_(GLenum cap, const char *file, int line)
{
    glDisable(cap);
    gl_check_error_(file, line);
}
inline void glCullFace_(GLenum mode, const char *file, int line)
{
    glCullFace(mode);
    gl_check_error_(file, line);
}
inline void glActiveTexture_(GLenum texture, const char *file, int line)
{
    glActiveTexture(texture);
    gl_check_error_(file, line);
}
inline void glBufferData_(GLenum target, GLsizeiptr size, const void *data, GLenum usage, const char *file, int line)
{
    glBufferData(target, size, data, usage);
    gl_check_error_(file, line);
}
inline void glEnableVertexAttribArray_(GLuint index, const char *file, int line)
{
    glEnableVertexAttribArray(index);
    gl_check_error_(file, line);
}
inline void glVertexAttribPointer_(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer, const char *file, int line)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    gl_check_error_(file, line);
}
inline void glDisableVertexAttribArray_(GLuint index, const char *file, int line)
{
    glDisableVertexAttribArray(index);
    gl_check_error_(file, line);
}
inline void glVertexAttribDivisor_(GLuint index, GLuint divisor, const char *file, int line)
{
    glVertexAttribDivisor(index, divisor);
    gl_check_error_(file, line);
}
inline void glBindBufferBase_(GLenum target, GLuint index, GLuint buffer, const char *file, int line)
{
    glBindBufferBase(target, index, buffer);
    gl_check_error_(file, line);
}
inline void glViewport_(GLint x, GLint y, GLsizei width, GLsizei height, const char *file, int line)
{
    glViewport(x, y, width, height);
    gl_check_error_(file, line);
}
inline void glClearColor_(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha, const char *file, int line)
{
    glClearColor(red, green, blue, alpha);
    gl_check_error_(file, line);
}
inline void glClear_(GLbitfield mask, const char *file, int line)
{
    glClear(mask);
    gl_check_error_(file, line);
}
inline void glBufferSubData_(GLenum target, GLintptr offset, GLsizeiptr size, const void *data, const char *file, int line)
{
    glBufferSubData(target, offset, size, data);
    gl_check_error_(file, line);
}
inline void glDrawElements_(GLenum mode, GLsizei count, GLenum type, const void *indices, const char *file, int line)
{
    glDrawElements(mode, count, type, indices);
    gl_check_error_(file, line);
}
inline void glGetActiveUniformBlockiv_(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params, const char *file, int line)
{
    glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
    gl_check_error_(file, line);
}
inline void glGetActiveUniformBlockName_(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName, const char *file, int line)
{
    glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
    gl_check_error_(file, line);
}
inline void glFramebufferTexture2D_(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, const char *file, int line)
{
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    gl_check_error_(file, line);
}
inline void glRenderbufferStorage_(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, const char *file, int line)
{
    glRenderbufferStorage(target, internalformat, width, height);
    gl_check_error_(file, line);
}
inline void glRenderbufferStorageMultisample_(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, const char *file, int line)
{
    glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
    gl_check_error_(file, line);
}
inline GLenum glCheckFramebufferStatus_(GLenum target, const char *file, int line)
{
    GLenum r = glCheckFramebufferStatus(target);
    gl_check_error_(file, line);
    return r;
}
inline void glTexImage2DMultisample_(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations, const char *file, int line)
{
    glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
    gl_check_error_(file, line);
}
inline void glPolygonMode_(GLenum face, GLenum mode, const char *file, int line)
{
    glPolygonMode(face, mode);
    gl_check_error_(file, line);
}
inline void glDrawBuffer_(GLenum buf, const char *file, int line)
{
    glDrawBuffer(buf);
    gl_check_error_(file, line);
}
inline void glDrawBuffers_(GLsizei n, const GLenum *bufs, const char *file, int line)
{
    glDrawBuffers(n, bufs);
    gl_check_error_(file, line);
}
inline void glFramebufferTexture_(GLenum target, GLenum attachment, GLuint texture, GLint level, const char *file, int line)
{
    glFramebufferTexture(target, attachment, texture, level);
    gl_check_error_(file, line);
}
bool gl_check_framebuffer_complete_(const char *file, int line);
#undef glGetUniformLocation
#undef glEnable
#undef glDepthFunc
#undef glDepthMask
#undef glGenBuffers
#undef glDeleteBuffers
#undef glBindBuffer
#undef glGenFramebuffers
#undef glDeleteFramebuffers
#undef glBindFramebuffer
#undef glGetIntegerv
#undef glGenRenderbuffers
#undef glDeleteRenderbuffers
#undef glBindRenderbuffer
#undef glShaderSource
#undef glCompileShader
#undef glGetShaderiv
#undef glGetShaderInfoLog
#undef glDeleteShader
#undef glCreateShader
#undef glCreateProgram
#undef glGetProgramiv
#undef glDeleteProgram
#undef glLinkProgram
#undef glAttachShader
#undef glGetProgramInfoLog
#undef glUseProgram
#undef glUniform1f
#undef glUniform2f
#undef glUniform3f
#undef glUniform4f
#undef glUniform1i
#undef glUniform4fv
#undef glUniformMatrix3fv
#undef glUniformMatrix4fv
#undef glUniformBlockBinding
#undef glGenVertexArrays
#undef glDeleteVertexArrays
#undef glBindVertexArray
#undef glTexParameteri
#undef glGetFloatv
#undef glTexParameterf
#undef glGenTextures
#undef glDeleteTextures
#undef glBindTexture
#undef glGenerateMipmap
#undef glTexImage2D
#undef glTexImage3D
#undef glDisable
#undef glCullFace
#undef glActiveTexture
#undef glBufferData
#undef glEnableVertexAttribArray
#undef glVertexAttribPointer
#undef glDisableVertexAttribArray
#undef glVertexAttribDivisor
#undef glBindBufferBase
#undef glViewport
#undef glClearColor
#undef glClear
#undef glBufferSubData
#undef glDrawElements
#undef glGetActiveUniformBlockiv
#undef glGetActiveUniformBlockName
#undef glFramebufferTexture2D
#undef glTexImage2DMultisample
#undef glRenderbufferStorage
#undef glRenderbufferStorageMultisample
#undef glCheckFramebufferStatus
#undef glFramebufferTexture
#undef glReadBuffer
#undef glDrawBuffers
#undef glDrawBuffer
#undef glPolygonMode
#undef glBlitFramebuffer

#define glBlitFramebuffer(GLint_srcX0, GLint_srcY0, GLint_srcX1, GLint_srcY1, GLint_dstX0, GLint_dstY0, GLint_dstX1, GLint_dstY1, GLbitfield_mask, GLenum_filter) glBlitFramebuffer_(GLint_srcX0, GLint_srcY0, GLint_srcX1, GLint_srcY1, GLint_dstX0, GLint_dstY0, GLint_dstX1, GLint_dstY1, GLbitfield_mask, GLenum_filter, __FILE__, __LINE__)
#define glReadBuffer(GLenum_src) glReadBuffer_(GLenum_src, __FILE__, __LINE__)
#define glGetActiveUniformBlockName(GLuint_program, GLuint_uniformBlockIndex, GLsizei_bufSize, GLsizei_ptr_length, GLchar_ptr_uniformBlockName) glGetActiveUniformBlockName_(GLuint_program, GLuint_uniformBlockIndex, GLsizei_bufSize, GLsizei_ptr_length, GLchar_ptr_uniformBlockName, __FILE__, __LINE__)
#define glGetUniformLocation(GLuint_program, const_GLchar_ptr_name) glGetUniformLocation_(GLuint_program, const_GLchar_ptr_name, __FILE__, __LINE__)
#define glEnable(GLenum_cap) glEnable_(GLenum_cap, __FILE__, __LINE__)
#define glDepthFunc(GLenum_func) glDepthFunc_(GLenum_func, __FILE__, __LINE__)
#define glDepthMask(GLboolean_flag) glDepthMask_(GLboolean_flag, __FILE__, __LINE__)
#define glGenBuffers(GLsizei_n, GLuint_ptr_buffers) glGenBuffers_(GLsizei_n, GLuint_ptr_buffers, __FILE__, __LINE__)
#define glDeleteBuffers(GLsizei_n, const_GLuint_ptr_buffers) glDeleteBuffers_(GLsizei_n, const_GLuint_ptr_buffers, __FILE__, __LINE__)
#define glBindBuffer(GLenum_target, GLuint_buffer) glBindBuffer_(GLenum_target, GLuint_buffer, __FILE__, __LINE__)
#define glGenFramebuffers(GLsizei_n, GLuint_ptr_framebuffers) glGenFramebuffers_(GLsizei_n, GLuint_ptr_framebuffers, __FILE__, __LINE__)
#define glDeleteFramebuffers(GLsizei_n, const_GLuint_ptr_framebuffers) glDeleteFramebuffers_(GLsizei_n, const_GLuint_ptr_framebuffers, __FILE__, __LINE__)
#define glBindFramebuffer(GLenum_target, GLuint_framebuffer) glBindFramebuffer_(GLenum_target, GLuint_framebuffer, __FILE__, __LINE__)
#define glGetIntegerv(GLenum_pname, GLint_ptr_data) glGetIntegerv_(GLenum_pname, GLint_ptr_data, __FILE__, __LINE__)
#define glGenRenderbuffers(GLsizei_n, GLuint_ptr_renderbuffers) glGenRenderbuffers_(GLsizei_n, GLuint_ptr_renderbuffers, __FILE__, __LINE__)
#define glDeleteRenderbuffers(GLsizei_n, const_GLuint_ptr_renderbuffers) glDeleteRenderbuffers_(GLsizei_n, const_GLuint_ptr_renderbuffers, __FILE__, __LINE__)
#define glBindRenderbuffer(GLenum_target, GLuint_renderbuffer) glBindRenderbuffer_(GLenum_target, GLuint_renderbuffer, __FILE__, __LINE__)
#define glShaderSource(GLuint_shader, GLsizei_count, const_GLchar_ptr_const_ptr_string, const_GLint_ptr_length) glShaderSource_(GLuint_shader, GLsizei_count, const_GLchar_ptr_const_ptr_string, const_GLint_ptr_length, __FILE__, __LINE__)
#define glCompileShader(GLuint_shader) glCompileShader_(GLuint_shader, __FILE__, __LINE__)
#define glGetShaderiv(GLuint_shader, GLenum_pname, GLint_ptr_params) glGetShaderiv_(GLuint_shader, GLenum_pname, GLint_ptr_params, __FILE__, __LINE__)
#define glGetShaderInfoLog(GLuint_shader, GLsizei_bufSize, GLsizei_ptr_length, GLchar_ptr_infoLog) glGetShaderInfoLog_(GLuint_shader, GLsizei_bufSize, GLsizei_ptr_length, GLchar_ptr_infoLog, __FILE__, __LINE__)
#define glDeleteShader(GLuint_shader) glDeleteShader_(GLuint_shader, __FILE__, __LINE__)
#define glCreateShader(GLenum_type) glCreateShader_(GLenum_type, __FILE__, __LINE__)
#define glCreateProgram() glCreateProgram_(__FILE__, __LINE__)
#define glGetProgramiv(GLuint_program, GLenum_pname, GLint_ptr_params) glGetProgramiv_(GLuint_program, GLenum_pname, GLint_ptr_params, __FILE__, __LINE__)
#define glDeleteProgram(GLuint_program) glDeleteProgram_(GLuint_program, __FILE__, __LINE__)
#define glLinkProgram(GLuint_program) glLinkProgram_(GLuint_program, __FILE__, __LINE__)
#define glAttachShader(GLuint_program, GLuint_shader) glAttachShader_(GLuint_program, GLuint_shader, __FILE__, __LINE__)
#define glGetProgramInfoLog(GLuint_program, GLsizei_bufSize, GLsizei_ptr_length, GLchar_ptr_infoLog) glGetProgramInfoLog_(GLuint_program, GLsizei_bufSize, GLsizei_ptr_length, GLchar_ptr_infoLog, __FILE__, __LINE__)
#define glUseProgram(GLuint_program) glUseProgram_(GLuint_program, __FILE__, __LINE__)
#define glUniform1f(GLint_location, GLfloat_v0) glUniform1f_(GLint_location, GLfloat_v0, __FILE__, __LINE__)
#define glUniform2f(GLint_location, GLfloat_v0, GLfloat_v1) glUniform2f_(GLint_location, GLfloat_v0, GLfloat_v1, __FILE__, __LINE__)
#define glUniform3f(GLint_location, GLfloat_v0, GLfloat_v1, GLfloat_v2) glUniform3f_(GLint_location, GLfloat_v0, GLfloat_v1, GLfloat_v2, __FILE__, __LINE__)
#define glUniform4f(GLint_location, GLfloat_v0, GLfloat_v1, GLfloat_v2, GLfloat_v3) glUniform4f_(GLint_location, GLfloat_v0, GLfloat_v1, GLfloat_v2, GLfloat_v3, __FILE__, __LINE__)
#define glUniform1i(GLint_location, GLint_v0) glUniform1i_(GLint_location, GLint_v0, __FILE__, __LINE__)
#define glUniform4fv(GLint_location, GLsizei_count, const_GLfloat_ptr_value) glUniform4fv_(GLint_location, GLsizei_count, const_GLfloat_ptr_value, __FILE__, __LINE__)
#define glUniformMatrix3fv(GLint_location, GLsizei_count, GLboolean_transpose, const_GLfloat_ptr_value) glUniformMatrix3fv_(GLint_location, GLsizei_count, GLboolean_transpose, const_GLfloat_ptr_value, __FILE__, __LINE__)
#define glUniformMatrix4fv(GLint_location, GLsizei_count, GLboolean_transpose, const_GLfloat_ptr_value) glUniformMatrix4fv_(GLint_location, GLsizei_count, GLboolean_transpose, const_GLfloat_ptr_value, __FILE__, __LINE__)
#define glUniformBlockBinding(GLuint_program, GLuint_uniformBlockIndex, GLuint_uniformBlockBinding) glUniformBlockBinding_(GLuint_program, GLuint_uniformBlockIndex, GLuint_uniformBlockBinding, __FILE__, __LINE__)
#define glGenVertexArrays(GLsizei_n, GLuint_ptr_arrays) glGenVertexArrays_(GLsizei_n, GLuint_ptr_arrays, __FILE__, __LINE__)
#define glDeleteVertexArrays(GLsizei_n, const_GLuint_ptr_arrays) glDeleteVertexArrays_(GLsizei_n, const_GLuint_ptr_arrays, __FILE__, __LINE__)
#define glBindVertexArray(GLuint_array) glBindVertexArray_(GLuint_array, __FILE__, __LINE__)
#define glTexParameteri(GLenum_target, GLenum_pname, GLint_param) glTexParameteri_(GLenum_target, GLenum_pname, GLint_param, __FILE__, __LINE__)
#define glGetFloatv(GLenum_pname, GLfloat_ptr_data) glGetFloatv_(GLenum_pname, GLfloat_ptr_data, __FILE__, __LINE__)
#define glTexParameterf(GLenum_target, GLenum_pname, GLfloat_param) glTexParameterf_(GLenum_target, GLenum_pname, GLfloat_param, __FILE__, __LINE__)
#define glGenTextures(GLsizei_n, GLuint_ptr_textures) glGenTextures_(GLsizei_n, GLuint_ptr_textures, __FILE__, __LINE__)
#define glDeleteTextures(GLsizei_n, const_GLuint_ptr_textures) glDeleteTextures_(GLsizei_n, const_GLuint_ptr_textures, __FILE__, __LINE__)
#define glBindTexture(GLenum_target, GLuint_texture) glBindTexture_(GLenum_target, GLuint_texture, __FILE__, __LINE__)
#define glGenerateMipmap(GLenum_target) glGenerateMipmap_(GLenum_target, __FILE__, __LINE__)
#define glTexImage2D(GLenum_target, GLint_level, GLint_internalformat, GLsizei_width, GLsizei_height, GLint_border, GLenum_format, GLenum_type, const_void_ptr_pixels) glTexImage2D_(GLenum_target, GLint_level, GLint_internalformat, GLsizei_width, GLsizei_height, GLint_border, GLenum_format, GLenum_type, const_void_ptr_pixels, __FILE__, __LINE__)
#define glTexImage3D(GLenum_target, GLint_level, GLint_internalformat, GLsizei_width, GLsizei_height, GLsizei_depth, GLint_border, GLenum_format, GLenum_type, const_void_ptr_pixels) glTexImage3D_(GLenum_target, GLint_level, GLint_internalformat, GLsizei_width, GLsizei_height, GLsizei_depth, GLint_border, GLenum_format, GLenum_type, const_void_ptr_pixels, __FILE__, __LINE__)
#define glDisable(GLenum_cap) glDisable_(GLenum_cap, __FILE__, __LINE__)
#define glCullFace(GLenum_mode) glCullFace_(GLenum_mode, __FILE__, __LINE__)
#define glActiveTexture(GLenum_texture) glActiveTexture_(GLenum_texture, __FILE__, __LINE__)
#define glBufferData(GLenum_target, GLsizeiptr_size, const_void_ptr_data, GLenum_usage) glBufferData_(GLenum_target, GLsizeiptr_size, const_void_ptr_data, GLenum_usage, __FILE__, __LINE__)
#define glEnableVertexAttribArray(GLuint_index) glEnableVertexAttribArray_(GLuint_index, __FILE__, __LINE__)
#define glVertexAttribPointer(GLuint_index, GLint_size, GLenum_type, GLboolean_normalized, GLsizei_stride, const_void_ptr_pointer) glVertexAttribPointer_(GLuint_index, GLint_size, GLenum_type, GLboolean_normalized, GLsizei_stride, const_void_ptr_pointer, __FILE__, __LINE__)
#define glDisableVertexAttribArray(GLuint_index) glDisableVertexAttribArray_(GLuint_index, __FILE__, __LINE__)
#define glVertexAttribDivisor(GLuint_index, GLuint_divisor) glVertexAttribDivisor_(GLuint_index, GLuint_divisor, __FILE__, __LINE__)
#define glBindBufferBase(GLenum_target, GLuint_index, GLuint_buffer) glBindBufferBase_(GLenum_target, GLuint_index, GLuint_buffer, __FILE__, __LINE__)
#define glViewport(GLint_x, GLint_y, GLsizei_width, GLsizei_height) glViewport_(GLint_x, GLint_y, GLsizei_width, GLsizei_height, __FILE__, __LINE__)
#define glClearColor(GLfloat_red, GLfloat_green, GLfloat_blue, GLfloat_alpha) glClearColor_(GLfloat_red, GLfloat_green, GLfloat_blue, GLfloat_alpha, __FILE__, __LINE__)
#define glClear(GLbitfield_mask) glClear_(GLbitfield_mask, __FILE__, __LINE__)
#define glBufferSubData(GLenum_target, GLintptr_offset, GLsizeiptr_size, const_void_ptr_data) glBufferSubData_(GLenum_target, GLintptr_offset, GLsizeiptr_size, const_void_ptr_data, __FILE__, __LINE__)
#define glDrawElements(GLenum_mode, GLsizei_count, GLenum_type, const_void_ptr_indices) glDrawElements_(GLenum_mode, GLsizei_count, GLenum_type, const_void_ptr_indices, __FILE__, __LINE__)
#define glGetActiveUniformBlockiv(GLuint_program, GLuint_uniformBlockIndex, GLenum_pname, GLint_ptr_params) glGetActiveUniformBlockiv_(GLuint_program, GLuint_uniformBlockIndex, GLenum_pname, GLint_ptr_params, __FILE__, __LINE__)
#define glFramebufferTexture2D(GLenum_target, GLenum_attachment, GLenum_textarget, GLuint_texture, GLint_level) glFramebufferTexture2D_(GLenum_target, GLenum_attachment, GLenum_textarget, GLuint_texture, GLint_level, __FILE__, __LINE__)
#define glRenderbufferStorage(GLenum_target, GLenum_internalformat, GLsizei_width, GLsizei_height) glRenderbufferStorage_(GLenum_target, GLenum_internalformat, GLsizei_width, GLsizei_height, __FILE__, __LINE__)
#define glRenderbufferStorageMultisample(GLenum_target, GLsizei_samples, GLenum_internalformat, GLsizei_width, GLsizei_height) glRenderbufferStorageMultisample_(GLenum_target, GLsizei_samples, GLenum_internalformat, GLsizei_width, GLsizei_height, __FILE__, __LINE__)
#define glCheckFramebufferStatus(GLenum_target) glCheckFramebufferStatus_(GLenum_target, __FILE__, __LINE__)
#define glTexImage2DMultisample(GLenum_target, GLsizei_samples, GLenum_internalformat, GLsizei_width, GLsizei_height, GLboolean_fixedsamplelocations) glTexImage2DMultisample_(GLenum_target, GLsizei_samples, GLenum_internalformat, GLsizei_width, GLsizei_height, GLboolean_fixedsamplelocations, __FILE__, __LINE__)
#define glDrawBuffer(GLenum_buf) glDrawBuffer_(GLenum_buf, __FILE__, __LINE__)
#define glDrawBuffers(GLsizei_n, const_GLenum_ptr_bufs) glDrawBuffers_(GLsizei_n, const_GLenum_ptr_bufs, __FILE__, __LINE__)
#define glFramebufferTexture(GLenum_target, GLenum_attachment, GLuint_texture, GLint_level) glFramebufferTexture_(GLenum_target, GLenum_attachment, GLuint_texture, GLint_level, __FILE__, __LINE__)
#define glPolygonMode(GLenum_face, GLenum_mode) glPolygonMode_(GLenum_face, GLenum_mode, __FILE__, __LINE__)
#define gl_check_framebuffer_complete() gl_check_framebuffer_complete_(__FILE__, __LINE__)
#define gl_check_error() gl_check_error_()

#else

#define gl_check_framebuffer_complete()
#define gl_check_error()

#endif

#endif