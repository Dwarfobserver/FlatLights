
#pragma once

#include <string>

namespace fl::detail {
	void gl_check_errors();
	void assert_failed(char const* expr, char const* file, int line, std::string const& msg);
}

#ifndef NDEBUG
  /// Throw an exception for the last OpenGL error encoutered, if there is one.
  #define GL_CHECK_ERRORS() (void) (fl::detail::gl_check_errors())

  /// Assert that 'expression' can be evaluated to true, or throw an exception containing the given message.
  #define FL_ASSERT(expression, message) (void) (  \
				(static_cast<bool>(expression)) || \
				(fl::detail::assert_failed(        \
					#expression,                   \
					__FILE__,                      \
					(int)(__LINE__),               \
					message), 0)                   \
		  )
#else
  /// Throw an exception for the last OpenGL error encoutered, if there is one.
  #define GL_CHECK_ERRORS() ((void) 0)

  /// Assert that 'expression' can be evaluated to true, or throw an exception containing the given message.
  #define FL_ASSERT()       ((void) 0)
#endif
