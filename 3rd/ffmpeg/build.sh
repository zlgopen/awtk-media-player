cd ffmpeg && ./myconfig && make && cd -

cd x264 && ./myconfig && make && cd - 

find . -name \*.a -exec cp -fv {} ../../lib \;

