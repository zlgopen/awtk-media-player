cd ffmpeg && ./myconfig && make && cd -

cd x264 && ./configure && make && cd - 

find . -name \*.a -exec cp -fv {} ../../lib \;

