ffmpeg vc ce
============

based on source code: ffmpeg-export-2010-09-26

the modified source for VC and CE support rstp, avi, mpeg4

the configure is:

`
./configure --disable-doc --disable-ffmpeg --disable-ffprobe --disable-ffserver --disable-avdevice --disable-avfilter --disable-pthreads --disable-mpegaudio-hp --disable-everything 
--enable-decoder=mpeg4 --enable-decoder=h264 --enable-decoder=svq3 
--enable-protocol=file --enable-protocol=rtp --enable-protocol=http 
--enable-demuxer=avi --enable-demuxer=sdp --enable-demuxer=rtsp  --enable-demuxer=mpegts 
--enable-parser=mpeg4video 
--disable-asm --disable-altivec --disable-amd3dnow --disable-amd3dnowext --disable-mmx --disable-mmx2 --disable-sse --disable-ssse3 --disable-armv5te --disable-armv6 --disable-armv6t2 --disable-armvfp --disable-iwmmxt --disable-mmi --disable-neon --disable-vis --disable-yasm --disable-optimizations --disable-zlib
`

[http://simplehappy.iteye.com/blog/777025](http://simplehappy.iteye.com/blog/777025)

