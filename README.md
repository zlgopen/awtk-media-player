# awtk-media-player

AWTK 媒体播放器服务和相关控件。

### 1.编译：

1.获取awtk并编译

```
git clone https://github.com/zlgopen/awtk.git
cd awtk; scons; cd -
```

2.获取awtk-media-player并编译


```
git clone https://github.com/zlgopen/awtk-media-player.git
cd awtk-media-player
cd 3rd/ffmpeg && ./build.sh && cd -
scons
```

> 目前仅仅支持macos 和 linux

### 2.运行Demo：

* 视频播放器演示

```
./bin/demo_media_player
```

![](docs/images/video_player.png)

* 音频播放器演示

```
./bin/demo_audio_player
```

![](docs/images/audio_player.png)

### 3.文档

[架构介绍](docs/arch.md)

### 4.TODO

* 优化完善。
*  移植 ffmpeg 到 Windows(主要是用 scons 脚本写编译脚本)
* 基于 sndio 实现 audio device 用于嵌入式 linux 平台。
*  基于 aworks 实现 audio device。
* 移植 ffmpeg 到 aworks
* 完整的媒体播放器应用程序。
* 完整的音乐播放器应用程序。
