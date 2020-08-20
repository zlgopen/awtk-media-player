# awtk-media-player

AWTK 媒体播放器服务和相关控件。

### 1. 编译：

1. 获取 awtk 并编译

```
git clone https://github.com/zlgopen/awtk.git
cd awtk; scons; cd -
```

2. 获取 awtk-media-player 并编译

```
git clone https://github.com/zlgopen/awtk-media-player.git
cd awtk-media-player
```

* 生成资源

```
python ./scripts/update_res.py all
```

> 或者通过 designer 生成资源


* 编译PC版本

```
scons
```

* 编译LINUX FB版本

```
scons LINUX_FB=true
```

> 完整编译选项请参考[编译选项](https://github.com/zlgopen/awtk-widget-generator/blob/master/docs/build_options.md)

> 目前仅仅支持 macos 和 linux

### 2. 运行 Demo：

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

### 3. 文档

[架构介绍](docs/arch.md)

### 4.TODO

* 优化完善。
* 移植 ffmpeg 到 Windows
* 移植 ffmpeg 到 aworks
* 基于 sndio 实现 audio device 用于嵌入式 linux 平台。
* 基于 aworks 实现 audio device。
