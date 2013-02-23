ffmpeg vc ce
============

based on source code: ffmpeg-export-2010-09-26,  build with vs2008

support feature:

- rtsp
- avi
- mpeg4 decoder

Prerequisites: [SDL](http://www.libsdl.org/) for ce and vc, you can find the files under `src\ffmpeg-export-2010-09-26\build`, but I fogot how I get those files, :(

see [more](http://simplehappy.iteye.com/blog/777025)

the configure(linux) is:

`
./configure --disable-doc --disable-ffmpeg --disable-ffprobe --disable-ffserver --disable-avdevice --disable-avfilter --disable-pthreads --disable-mpegaudio-hp --disable-everything 
--enable-decoder=mpeg4 --enable-decoder=h264 --enable-decoder=svq3 
--enable-protocol=file --enable-protocol=rtp --enable-protocol=http 
--enable-demuxer=avi --enable-demuxer=sdp --enable-demuxer=rtsp  --enable-demuxer=mpegts 
--enable-parser=mpeg4video 
--disable-asm --disable-altivec --disable-amd3dnow --disable-amd3dnowext --disable-mmx --disable-mmx2 --disable-sse --disable-ssse3 --disable-armv5te --disable-armv6 --disable-armv6t2 --disable-armvfp --disable-iwmmxt --disable-mmi --disable-neon --disable-vis --disable-yasm --disable-optimizations --disable-zlib
`

2010.10

