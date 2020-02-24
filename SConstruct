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

APP_CPPPATH = ['.', 
  os.path.join(APP_ROOT, 'src'),
  os.path.join(APP_ROOT, '3rd/ffmpeg/ffmpeg'),
  os.path.join(APP_ROOT, '3rd/ffmpeg/x264')
]

os.environ['APP_SRC'] = APP_SRC;
os.environ['APP_ROOT'] = APP_ROOT;
os.environ['BIN_DIR'] = APP_BIN_DIR;
os.environ['LIB_DIR'] = APP_LIB_DIR;

APP_CCFLAGS = ' -DBUILDING_LIBCURL -DRES_ROOT=\"\\\"'+RES_ROOT+'\\\"\" '
APP_LIBS = ['assets']
APP_LIBPATH = [APP_LIB_DIR]
APP_LINKFLAGS = ''

DefaultEnvironment(
  CPPPATH   = awtk.CPPPATH + APP_CPPPATH,
  LINKFLAGS = awtk.LINKFLAGS + APP_LINKFLAGS,
  LIBS      = APP_LIBS + awtk.LIBS,
  LIBPATH   = APP_LIBPATH + awtk.LIBPATH,
  CCFLAGS   = APP_CCFLAGS + awtk.CCFLAGS, 
  OS_SUBSYSTEM_CONSOLE=awtk.OS_SUBSYSTEM_CONSOLE,
  OS_SUBSYSTEM_WINDOWS=awtk.OS_SUBSYSTEM_WINDOWS)

SConscriptFiles=[
  'src/media_player/SConscript', 
  'tests/SConscript', 
  'demos/SConscript'
]

SConscript(SConscriptFiles)

