#ifdef __GNUC__ /* Use the -Wno-unused-parameter */
#define UNIMPLEMENTED_PARM(x)
#define UNUSED_PARM(x) magick_unused_ ## x __attribute__((unused))
#define UNREFERENCED_PARM(x)
#define SWITCH_FALLTHROUGH __attribute__ ((fallthrough))
#else
// Use these to 'refer' to the formal parameters that we are not using
#define UNIMPLEMENTED_PARM(x)   (x)
#define UNUSED_PARM(x)   (x)
#define UNREFERENCED_PARM(x)    (x)
#define SWITCH_FALLTHROUGH
#endif
