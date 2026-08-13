#最新动态

2026-08-13
  * 修复Windows平台播放视频过程中关闭程序出现线程野指针崩溃的问题(感谢雨欣提供补丁)
  * 修复嵌入式Linux平台上连续播放多个视频时程序崩溃的问题(感谢雨欣提供补丁)

2021-01-21
  * 更新文档。
  * 完善 audio_recorder。

2021-01-20
	* 修改 lrc 内存泄漏。
  * 增加 audio_recorder。

2020-12-23
  * 修改内存泄露(感谢兆坤提供补丁)

2020-12-14
  * 重新用object default实现decoder factory。

2020-12-09
 * 将 audio\_decoder\_mp3 移动到 audio\_decoders 目录。
 * 将 audio\_decoder 和 audio\_decoder\_factory 移到 base 目录。
 * 将 audio\_device\_sdl 移到 audio\_device 目录。
