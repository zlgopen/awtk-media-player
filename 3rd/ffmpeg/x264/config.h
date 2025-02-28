#define ARCH_X86_64 1

#ifdef WIN32
#define STACK_ALIGNMENT 4
//#define HAVE_POSIXTHREAD 0
#define HAVE_BEOSTHREAD 0
#define HAVE_WIN32THREAD 1
#define SYS_WINDOWS 1
#define HAVE_LAVF 0
#define HAVE_AVS 0
#define USE_AVXSYNTH 0
#elif defined(MACOS)
#define SYS_MACOSX 1
#else
#define STACK_ALIGNMENT 64
#define HAVE_POSIXTHREAD 1
#define HAVE_BEOSTHREAD 0
#define HAVE_WIN32THREAD 0
#define HAVE_OPENCL (BIT_DEPTH==8)
#define HAVE_LAVF 1
#define HAVE_AVS 1
#define USE_AVXSYNTH 1
#endif

#define HAVE_THREAD 1
#define HAVE_LOG2F 1
#define HAVE_STRTOK_R 1
#define HAVE_CLOCK_GETTIME 1
#define HAVE_MMAP 1
#define HAVE_SWSCALE 1
#define HAVE_VECTOREXT 1
#define fseek fseeko
#define ftell ftello
#define HAVE_BITDEPTH8 1
#define CHROMA_FORMAT CHROMA_422
#define HAVE_INTERLACED 1
#define HAVE_MALLOC_H 0
#define HAVE_ALTIVEC 0
#define HAVE_ALTIVEC_H 0
#define HAVE_MMX 0
#define HAVE_ARMV6 0
#define HAVE_ARMV6T2 0
#define HAVE_NEON 0
#define HAVE_AARCH64 0
#define HAVE_FFMS 0
#define HAVE_GPAC 0
#define HAVE_GPL 0
#define HAVE_CPU_COUNT 0
#define HAVE_THP 0
#define HAVE_LSMASH 0
#define HAVE_X86_INLINE_ASM 0
#define HAVE_AS_FUNC 0
#define HAVE_INTEL_DISPATCHER 0
#define HAVE_MSA 0
#define HAVE_WINRT 0
#define HAVE_VSX 0
#define HAVE_ARM_INLINE_ASM 0
#define HAVE_BITDEPTH10 0
