import os
import sys
import platform

sys.path.insert(0, '../awtk/')
import awtk_config as awtk

RES_ROOT    = awtk.TK_DEMO_ROOT.replace("\\", "\\\\")
APP_ROOT    = os.path.normpath(os.getcwd())
APP_SRC     = os.path.join(APP_ROOT, 'src')
APP_BIN_DIR = os.path.join(APP_ROOT, 'bin')
APP_LIB_DIR = os.path.join(APP_ROOT, 'lib')

X264_ROOT=os.path.abspath(os.path.join(APP_ROOT, '3rd/ffmpeg/x264'))
FFMPEG_ROOT=os.path.abspath(os.path.join(APP_ROOT, '3rd/ffmpeg/ffmpeg'))

PLAYER_CPPPATH=[]
PLAYER_LINKFLAGS=""
PLAYER_LIBS = ["media_player_ffmpeg", "media_player_audio", "audio_device_sdl", "media_player_base", "lrc"]

OS_NAME = platform.system();

FFMPEG_LIBS=[
 "avformat",
 "avcodec", 
 "avformat",
 "avdevice",
 "avresample", 
 "avfilter",
 "avutil", 
 "swscale",
 "swresample",
 "postproc",
 "x264"]

if OS_NAME == 'Darwin':
  PLAYER_LINKFLAGS=" -framework  VideoToolbox -framework CoreVideo -framework CoreMedia " 
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework AudioToolbox -framework AVFoundation"
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework VideoDecodeAcceleration -framework Security"
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework CoreFoundation"
  PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS #+ ['iconv', 'pthread', 'lzma', 'bz2', 'z']
elif OS_NAME == 'Linux':
  PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS  + ["asound"] 
elif OS_NAME == 'Windows':
  PLAYER_CPPPATH=[os.path.join(APP_ROOT, '3rd/ffmpeg/ffmpeg/compat/atomics/win32')]
  print("debug");

APP_CPPPATH = ['.', 
  os.path.join(APP_ROOT, 'src'),
  os.path.join(APP_ROOT, '3rd'),
  os.path.join(APP_ROOT, '3rd/ffmpeg/ffmpeg'),
  os.path.join(APP_ROOT, '3rd/ffmpeg/x264')
] + PLAYER_CPPPATH

os.environ['APP_SRC'] = APP_SRC;
os.environ['APP_ROOT'] = APP_ROOT;
os.environ['BIN_DIR'] = APP_BIN_DIR;
os.environ['LIB_DIR'] = APP_LIB_DIR;

APP_LIBPATH = [APP_LIB_DIR]
APP_LIBS = ['assets', 'media_player_widgets'] + PLAYER_LIBS
APP_LINKFLAGS = PLAYER_LINKFLAGS
APP_CCFLAGS = ' -DBUILDING_LIBCURL -DRES_ROOT=\"\\\"'+RES_ROOT+'\\\"\" '

DefaultEnvironment(
  CPPPATH   = awtk.CPPPATH + APP_CPPPATH,
  LINKFLAGS = awtk.LINKFLAGS + APP_LINKFLAGS,
  LIBS      = APP_LIBS + awtk.LIBS,
  LIBPATH   = APP_LIBPATH + awtk.LIBPATH,
  CCFLAGS   = APP_CCFLAGS + awtk.CCFLAGS, 
  OS_SUBSYSTEM_CONSOLE=awtk.OS_SUBSYSTEM_CONSOLE,
  OS_SUBSYSTEM_WINDOWS=awtk.OS_SUBSYSTEM_WINDOWS)

SConscriptFiles=[
  '3rd/ffmpeg/SConscript',
  'src/media_player/lrc/SConscript', 
  'src/media_player/base/SConscript', 
  'src/media_player/ffmpeg/SConscript', 
  'src/media_player/widgets/SConscript', 
  'src/media_player/audio_player/SConscript', 
  'src/media_player/audio_device/sdl/SConscript', 
  'demos/SConscript', 
  'tests/SConscript', 
]

SConscript(SConscriptFiles)

