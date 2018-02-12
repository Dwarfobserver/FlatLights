
#pragma once

#include <string>

namespace fl {

	namespace detail {
		template <class F>
		struct defer {
			explicit defer(F&& f) : f_(std::move(f)), enabled_(true) {}
			explicit defer(F const& f) : f_(f), enabled_(true) {}

			~defer() noexcept(std::is_nothrow_invocable_v<F>) { if (enabled_) f_(); }

			defer(defer&& d) noexcept(std::is_nothrow_move_constructible_v<F>) :
				f_(std::move(d.f_)), enabled_(true) { d.enabled_ = false; }

			defer(defer const&) = delete;
		private:
			F f_;
			bool enabled_; // Mandatory while no template deduction available or copy elision garanteed
		};
		/*  >> No template deduction guide <<
		template <class F> defer(F&&)->defer<F>; */

		void assert_failed(char const* expr, char const* file, int line, std::string const& msg);
	}

	/// Defer a functor's execution to the scope's ending.
	/// The returned vlaue must not be discarded (as the function will be ran at it's destructor).
	template <class F>
	[[nodiscard]]
	detail::defer<F> defer(F&& f) {
		return detail::defer<F>{ std::forward<F>(f) };
	}
}

#ifndef NDEBUG
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
  /// Assert that 'expression' can be evaluated to true, or throw an exception containing the given message.
  #define FL_ASSERT()       ((void) 0)
#endif
