import os
import platform
import scripts.app_helper as app

helper = app.Helper(ARGUMENTS);
APP_ROOT = helper.APP_ROOT
X264_ROOT=os.path.abspath(os.path.join(helper.APP_ROOT, '3rd/ffmpeg/x264'))
FFMPEG_ROOT=os.path.abspath(os.path.join(APP_ROOT, '3rd/ffmpeg/ffmpeg'))

PLAYER_CPPPATH=[]
PLAYER_LINKFLAGS=""
PLAYER_LIBS = ["media_player_ffmpeg", "media_player_audio", "audio_device_sdl", "media_player_base", "lrc"]

OS_NAME = platform.system();

FFMPEG_LIBS=["ffmpeg", "x264"]

if OS_NAME == 'Darwin':
  PLAYER_LINKFLAGS=" -framework  VideoToolbox -framework CoreVideo -framework CoreMedia " 
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework AudioToolbox -framework AVFoundation"
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework VideoDecodeAcceleration -framework Security"
  PLAYER_LINKFLAGS = PLAYER_LINKFLAGS + " -framework CoreFoundation"
  PLAYER_LIBS = PLAYER_LIBS + FFMPEG_LIBS 
elif OS_NAME == 'Linux':
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

APP_LINKFLAGS = PLAYER_LINKFLAGS
APP_CCFLAGS = ' -DBUILDING_LIBCURL '
APP_LIBS = ['media_player_widgets', 'SDL2'] + PLAYER_LIBS

helper.add_libs(APP_LIBS).add_linkflags(APP_LINKFLAGS).add_cpppath(APP_CPPPATH).call(DefaultEnvironment)

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

