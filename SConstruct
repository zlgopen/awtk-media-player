import os
import platform
import scripts.app_helper as app

helper = app.Helper(ARGUMENTS);
APP_ROOT = helper.APP_ROOT
PLAYER_PROJS=[]
PLAYER_CCFLAGS = ''
PLAYER_CPPPATH=[]
PLAYER_LINKFLAGS=""
PLAYER_LIB_PATH=[]
FFMPEG_LIBS = []
OS_NAME = platform.system();

PLAYER_LIBS = ["shine"]

#If you need not ffmpeg, set it false
#os.environ['WITH_FFMPEG'] = 'false'
os.environ['WITH_FFMPEG'] = 'true'

if os.environ['WITH_FFMPEG'] == 'true':
    PLAYER_CCFLAGS += ' -DWITH_PLAYER_FFMPEG '
    FFMPEG_LIBS=["ffmpeg", "x264"]
    PLAYER_PROJS = [
      '3rd/ffmpeg/SConscript',
      'src/media_player/ffmpeg/SConscript', 
    ]
  

if OS_NAME == 'Darwin':
  PLAYER_LINKFLAGS=" -framework  VideoToolbox -framework CoreVideo -framework CoreMedia " 
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework AudioToolbox -framework AVFoundation"
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework VideoDecodeAcceleration -framework Security"
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework CoreFoundation"
  PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS + ["SDL2"] 
elif OS_NAME == 'Linux':
  if os.environ['LINUX_FB'] == 'true':
    PLAYER_PROJS += [
      '3rd/SDL/SConscript'
    ]
    PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS + ["SDL2", "asound"] 
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -D__USE_POSIX '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -DSDL_TIMER_UNIX -DSDL_VIDEO_DRIVER_DUMMY '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -DSDL_AUDIO_DRIVER_ALSA -DWITH_SDL_AUDIO '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -DSDL_LOADSO_DLOPEN  -DSDL_STATIC_LIB -D__FLTUSED__ '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -DSDL_REAL_API -DSDL_HAPTIC_DISABLED -DSDL_SENSOR_DISABLED -DSDL_JOYSTICK_DISABLED '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -D_GNU_SOURCE -DHAVE_SOCK_CLOEXEC -DHAVE_CLOCK_GETTIME '
    PLAYER_CPPPATH = PLAYER_CPPPATH + [
      os.path.join(APP_ROOT, "usr/include"),
      os.path.join(APP_ROOT, "3rd/SDL/src"),
      os.path.join(APP_ROOT, "3rd/SDL/include"),
      os.path.join(APP_ROOT, "3rd/ffmpeg/ffmpeg/compat/atomics/pthread")
    ]
    PLAYER_LIB_PATH = [
      os.path.join(APP_ROOT, "usr/lib")
    ]
  else:
    PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS  + ["asound"] 

elif OS_NAME == 'Windows':
  PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS
  PLAYER_CPPPATH=[os.path.join(APP_ROOT, '3rd/ffmpeg/ffmpeg/compat/atomics/win32')]

APP_CPPPATH = ['.', 
  os.path.join(APP_ROOT, 'src'),
  os.path.join(APP_ROOT, '3rd'),
  os.path.join(APP_ROOT, '3rd/ffmpeg/ffmpeg'),
  os.path.join(APP_ROOT, '3rd/ffmpeg/x264'),
  os.path.join(APP_ROOT, '3rd/shine/src')
] + PLAYER_CPPPATH

APP_LIBS = PLAYER_LIBS
APP_LIB_PATH = PLAYER_LIB_PATH
APP_LINKFLAGS = PLAYER_LINKFLAGS
APP_CCFLAGS = ' -DBUILDING_LIBCURL ' + PLAYER_CCFLAGS

helper.set_dll_def('src/media_player.def')
helper.add_ccflags(APP_CCFLAGS).add_libpath(APP_LIB_PATH)
helper.add_libs(APP_LIBS).add_linkflags(APP_LINKFLAGS).add_cpppath(APP_CPPPATH).call(DefaultEnvironment)

SConscriptFiles=[
  '3rd/ffmpeg/SConscript',
  '3rd/shine/SConscript',
  'src/media_player/SConscript',
  'demos/SConscript', 
  'tools/SConscript', 
  'tests/SConscript', 
]

helper.SConscript(SConscriptFiles)

