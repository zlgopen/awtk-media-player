import os
import platform
import scripts.app_helper as app

helper = app.Helper(ARGUMENTS);
APP_ROOT = helper.APP_ROOT
X264_ROOT=os.path.abspath(os.path.join(helper.APP_ROOT, '3rd/ffmpeg/x264'))
FFMPEG_ROOT=os.path.abspath(os.path.join(APP_ROOT, '3rd/ffmpeg/ffmpeg'))

PLAYER_PROJS=[]
PLAYER_CCFLAGS = ''
PLAYER_CPPPATH=[]
PLAYER_LINKFLAGS=""
PLAYER_LIB_PATH=[]
FFMPEG_LIBS = []

PLAYER_LIBS = ["media_player_ffmpeg", "media_player_audio", "audio_device_sdl", "media_player_base", "lrc"]

OS_NAME = platform.system();

#os.environ['WITH_FFMPEG'] = 'false'
os.environ['WITH_FFMPEG'] = 'true'

if os.environ['WITH_FFMPEG'] == 'true':
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
  PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS 
elif OS_NAME == 'Linux':
  if os.environ['NATIVE_WINDOW'] == 'raw':
    PLAYER_PROJS += [
      '3rd/SDL/SConscript'
    ]
    PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS + ["SDL2", "asound"] 
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -D__USE_POSIX'
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -DSDL_TIMER_UNIX -DSDL_VIDEO_DRIVER_DUMMY '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -DSDL_AUDIO_DRIVER_ALSA -DWITH_SDL_AUDIO '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -DSDL_LOADSO_DLOPEN  -DSDL_STATIC_LIB -D__FLTUSED__ '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -DSDL_REAL_API -DSDL_HAPTIC_DISABLED -DSDL_SENSOR_DISABLED -DSDL_JOYSTICK_DISABLED '
    PLAYER_CCFLAGS = PLAYER_CCFLAGS + ' -D_GNU_SOURCE -DHAVE_SOCK_CLOEXEC -DHAVE_CLOCK_GETTIME '
    PLAYER_CPPPATH = PLAYER_CPPPATH + [
      os.path.join(APP_ROOT, "usr/include"),
      os.path.join(APP_ROOT, "3rd/SDL/src"),
      os.path.join(APP_ROOT, "3rd/SDL/include")
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
  os.path.join(APP_ROOT, '3rd/ffmpeg/x264')
] + PLAYER_CPPPATH

APP_LIB_PATH = PLAYER_LIB_PATH
APP_LINKFLAGS = PLAYER_LINKFLAGS
APP_CCFLAGS = ' -DBUILDING_LIBCURL ' + PLAYER_CCFLAGS
APP_LIBS = ['media_player_widgets'] + PLAYER_LIBS

helper.add_ccflags(APP_CCFLAGS).add_libpath(APP_LIB_PATH)
helper.add_libs(APP_LIBS).add_linkflags(APP_LINKFLAGS).add_cpppath(APP_CPPPATH).call(DefaultEnvironment)

SConscriptFiles=[
  'src/media_player/lrc/SConscript', 
  'src/media_player/base/SConscript', 
  'src/media_player/widgets/SConscript', 
  'src/media_player/audio_player/SConscript', 
  'src/media_player/audio_device/sdl/SConscript', 
  'demos/SConscript', 
  'tests/SConscript', 
] + PLAYER_PROJS;

SConscript(SConscriptFiles)

