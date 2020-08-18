// Due to an inability to supress assert popups when building against mingw-w64 and running on wine
// We are wrapping the assert macro so that we can substitute functional behavior with that setup

// This copies the semantics of cassert, re-including the file re-defines the macro.
#undef cata_assert

// Might as well handle NDEBUG at the top level instead of just wrapping one variant.
#ifdef NDEBUG
#define cata_assert(_Expression) ((void)0)
#else
#ifdef _WIN32
#include <cstdlib>
#include <cstdio>
#define cata_assert(_Expression) \
    (void) \
    ( ( !!( _Expression ) ) || ( fprintf( stderr, "%s, %s, %s\n", #_Expression, __FILE__, __LINE__ ) && \
                                 std::exit( -1 ) ) )
#else
#include <cassert>
#define cata_assert(_Expression) \
    assert(_Expression)
#endif // _WIN32
#endif // NDEBUG
