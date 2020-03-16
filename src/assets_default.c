#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "assets/default/inc/strings/ko_KR.data"
#include "assets/default/inc/strings/zh_CN.data"
#include "assets/default/inc/strings/zh_TW.data"
#include "assets/default/inc/strings/en_US.data"
#include "assets/default/inc/styles/player.data"
#include "assets/default/inc/styles/main.data"
#include "assets/default/inc/styles/keyboard.data"
#include "assets/default/inc/styles/default.data"
#include "assets/default/inc/styles/window1.data"
#include "assets/default/inc/ui/kb_ascii.data"
#include "assets/default/inc/ui/kb_phone.data"
#include "assets/default/inc/ui/main.data"
#include "assets/default/inc/ui/kb_int.data"
#include "assets/default/inc/ui/kb_hex.data"
#include "assets/default/inc/ui/player_common.data"
#include "assets/default/inc/ui/settings.data"
#include "assets/default/inc/ui/kb_float.data"
#include "assets/default/inc/ui/video_player.data"
#include "assets/default/inc/ui/kb_ufloat.data"
#include "assets/default/inc/ui/kb_default.data"
#include "assets/default/inc/ui/audio_player.data"
#include "assets/default/inc/ui/kb_uint.data"
#ifdef WITH_STB_IMAGE
#include "assets/default/inc/images/checked.res"
#include "assets/default/inc/images/sound_plus.res"
#include "assets/default/inc/images/shift.res"
#include "assets/default/inc/images/earth.res"
#include "assets/default/inc/images/dialog_title.res"
#include "assets/default/inc/images/arrow_up_n.res"
#include "assets/default/inc/images/arrow_right_p.res"
#include "assets/default/inc/images/empty.res"
#include "assets/default/inc/images/edit_clear_p.res"
#include "assets/default/inc/images/arrow_up_o.res"
#include "assets/default/inc/images/arrow_left_o.res"
#include "assets/default/inc/images/en.res"
#include "assets/default/inc/images/arrow_left_n.res"
#include "assets/default/inc/images/radio_checked.res"
#include "assets/default/inc/images/zh.res"
#include "assets/default/inc/images/shifton.res"
#include "assets/default/inc/images/check.res"
#include "assets/default/inc/images/arrow_down_n.res"
#include "assets/default/inc/images/muted.res"
#include "assets/default/inc/images/arrow_down_o.res"
#include "assets/default/inc/images/play.res"
#include "assets/default/inc/images/unmuted.res"
#include "assets/default/inc/images/sound_minus.res"
#include "assets/default/inc/images/unchecked.res"
#include "assets/default/inc/images/arrow_down_p.res"
#include "assets/default/inc/images/switch.res"
#include "assets/default/inc/images/radio_unchecked.res"
#include "assets/default/inc/images/mode_2.res"
#include "assets/default/inc/images/mode_1.res"
#include "assets/default/inc/images/mode_0.res"
#include "assets/default/inc/images/arrow_up_p.res"
#include "assets/default/inc/images/edit_clear_o.res"
#include "assets/default/inc/images/arrow_right_n.res"
#include "assets/default/inc/images/arrow_right_o.res"
#include "assets/default/inc/images/edit_clear_n.res"
#include "assets/default/inc/images/pause.res"
#include "assets/default/inc/images/backspace.res"
#include "assets/default/inc/images/arrow_left_p.res"
#else
#include "assets/default/inc/images/arrow_right_o.data"
#include "assets/default/inc/images/sound_plus.data"
#include "assets/default/inc/images/muted.data"
#include "assets/default/inc/images/earth.data"
#include "assets/default/inc/images/shift.data"
#include "assets/default/inc/images/arrow_up_p.data"
#include "assets/default/inc/images/en.data"
#include "assets/default/inc/images/sound_minus.data"
#include "assets/default/inc/images/arrow_right_n.data"
#include "assets/default/inc/images/switch.data"
#include "assets/default/inc/images/checked.data"
#include "assets/default/inc/images/zh.data"
#include "assets/default/inc/images/arrow_right_p.data"
#include "assets/default/inc/images/arrow_up_o.data"
#include "assets/default/inc/images/mode_2.data"
#include "assets/default/inc/images/empty.data"
#include "assets/default/inc/images/radio_unchecked.data"
#include "assets/default/inc/images/shifton.data"
#include "assets/default/inc/images/arrow_up_n.data"
#include "assets/default/inc/images/unmuted.data"
#include "assets/default/inc/images/backspace.data"
#include "assets/default/inc/images/arrow_left_p.data"
#include "assets/default/inc/images/edit_clear_n.data"
#include "assets/default/inc/images/dialog_title.data"
#include "assets/default/inc/images/mode_0.data"
#include "assets/default/inc/images/arrow_down_p.data"
#include "assets/default/inc/images/play.data"
#include "assets/default/inc/images/pause.data"
#include "assets/default/inc/images/mode_1.data"
#include "assets/default/inc/images/edit_clear_o.data"
#include "assets/default/inc/images/arrow_left_o.data"
#include "assets/default/inc/images/check.data"
#include "assets/default/inc/images/arrow_down_o.data"
#include "assets/default/inc/images/radio_checked.data"
#include "assets/default/inc/images/unchecked.data"
#include "assets/default/inc/images/arrow_down_n.data"
#include "assets/default/inc/images/arrow_left_n.data"
#include "assets/default/inc/images/edit_clear_p.data"
#endif/*WITH_STB_IMAGE*/
#ifdef WITH_VGCANVAS
#endif/*WITH_VGCANVAS*/
#if defined(WITH_STB_FONT) || defined(WITH_FT_FONT)
#include "assets/default/inc/fonts/default_mini.res"
#include "assets/default/inc/fonts/thin.res"
#include "assets/default/inc/fonts/bold.res"
#include "assets/default/inc/fonts/default.res"
#include "assets/default/inc/fonts/ko_KR.res"
#include "assets/default/inc/fonts/italic.res"
#include "assets/default/inc/fonts/zh_TW.res"
#include "assets/default/inc/fonts/mono.res"
#include "assets/default/inc/fonts/light.res"
#include "assets/default/inc/fonts/led.res"
#else/*WITH_STB_FONT or WITH_FT_FONT*/
#endif/*WITH_STB_FONT or WITH_FT_FONT*/
#endif/*WITH_FS_RES*/

ret_t assets_init_default(void) {
  assets_manager_t* am = assets_manager();

#ifdef WITH_FS_RES
  assets_manager_preload(am, ASSET_TYPE_FONT, "default");
  assets_manager_preload(am, ASSET_TYPE_STYLE, "default");
#else
  assets_manager_add(am, strings_ko_KR);
  assets_manager_add(am, strings_zh_CN);
  assets_manager_add(am, strings_zh_TW);
  assets_manager_add(am, strings_en_US);
  assets_manager_add(am, style_player);
  assets_manager_add(am, style_main);
  assets_manager_add(am, style_keyboard);
  assets_manager_add(am, style_default);
  assets_manager_add(am, style_window1);
  assets_manager_add(am, ui_kb_ascii);
  assets_manager_add(am, ui_kb_phone);
  assets_manager_add(am, ui_main);
  assets_manager_add(am, ui_kb_int);
  assets_manager_add(am, ui_kb_hex);
  assets_manager_add(am, ui_player_common);
  assets_manager_add(am, ui_settings);
  assets_manager_add(am, ui_kb_float);
  assets_manager_add(am, ui_video_player);
  assets_manager_add(am, ui_kb_ufloat);
  assets_manager_add(am, ui_kb_default);
  assets_manager_add(am, ui_audio_player);
  assets_manager_add(am, ui_kb_uint);
  assets_manager_add(am, image_arrow_right_o);
  assets_manager_add(am, image_sound_plus);
  assets_manager_add(am, image_muted);
  assets_manager_add(am, image_earth);
  assets_manager_add(am, image_shift);
  assets_manager_add(am, image_arrow_up_p);
  assets_manager_add(am, image_en);
  assets_manager_add(am, image_sound_minus);
  assets_manager_add(am, image_arrow_right_n);
  assets_manager_add(am, image_switch);
  assets_manager_add(am, image_checked);
  assets_manager_add(am, image_zh);
  assets_manager_add(am, image_arrow_right_p);
  assets_manager_add(am, image_arrow_up_o);
  assets_manager_add(am, image_mode_2);
  assets_manager_add(am, image_empty);
  assets_manager_add(am, image_radio_unchecked);
  assets_manager_add(am, image_shifton);
  assets_manager_add(am, image_arrow_up_n);
  assets_manager_add(am, image_unmuted);
  assets_manager_add(am, image_backspace);
  assets_manager_add(am, image_arrow_left_p);
  assets_manager_add(am, image_edit_clear_n);
  assets_manager_add(am, image_dialog_title);
  assets_manager_add(am, image_mode_0);
  assets_manager_add(am, image_arrow_down_p);
  assets_manager_add(am, image_play);
  assets_manager_add(am, image_pause);
  assets_manager_add(am, image_mode_1);
  assets_manager_add(am, image_edit_clear_o);
  assets_manager_add(am, image_arrow_left_o);
  assets_manager_add(am, image_check);
  assets_manager_add(am, image_arrow_down_o);
  assets_manager_add(am, image_radio_checked);
  assets_manager_add(am, image_unchecked);
  assets_manager_add(am, image_arrow_down_n);
  assets_manager_add(am, image_arrow_left_n);
  assets_manager_add(am, image_edit_clear_p);
#if defined(WITH_STB_FONT) || defined(WITH_FT_FONT)
  assets_manager_add(am, font_default_mini);
  assets_manager_add(am, font_thin);
  assets_manager_add(am, font_bold);
  assets_manager_add(am, font_default);
  assets_manager_add(am, font_ko_KR);
  assets_manager_add(am, font_italic);
  assets_manager_add(am, font_zh_TW);
  assets_manager_add(am, font_mono);
  assets_manager_add(am, font_light);
  assets_manager_add(am, font_led);
#else/*WITH_STB_FONT or WITH_FT_FONT*/
#endif/*WITH_STB_FONT or WITH_FT_FONT*/
#ifdef WITH_VGCANVAS
#endif/*WITH_VGCANVAS*/
#endif

  tk_init_assets();
  return RET_OK;
}
