#include "libavcodec/avcodec.h"
#include "libavcodec/h264chroma.h"
#include "libavcodec/blockdsp.h"
#include "libswresample/resample.h"
#include "libavcodec/vorbisdsp.h"
#include "libswscale/swscale.h"
#include "libavcodec/fmtconvert.h"
#include "libswscale/swscale_internal.h"
#include "libavcodec/mpegvideo.h"
#include "libavutil/samplefmt.h"
#include "libavutil/float_dsp.h"
#include "libswresample/swresample_internal.h"
#include "libswresample/audioconvert.h"
#include "libavutil/attributes.h"
#include "libavutil/cpu.h"
#include "libavutil/fixed_dsp.h"
#include "libavcodec/aac.h"
#include "libavcodec/aacsbr.h"
#include "libavcodec/bswapdsp.h"
#include "libavcodec/ac3dsp.h"
#include "libavcodec/bswapdsp.h"

int ff_frame_thread_encoder_init(AVCodecContext* avctx, AVDictionary* options) {
  return 0;
}

void ff_frame_thread_encoder_free(AVCodecContext* avctx) {
}

av_cold void ff_yuv2rgb_init_tables_ppc(SwsContext* c, const int inv_table[4], int brightness,
                                        int contrast, int saturation) {
}
av_cold void ff_sws_init_swscale_ppc(SwsContext* c) {
}
av_cold void ff_sws_init_swscale_x86(SwsContext* c) {
}
av_cold void ff_sws_init_swscale_aarch64(SwsContext* c) {
}
av_cold void ff_sws_init_swscale_arm(SwsContext* c) {
}
int ff_mpeg4_find_frame_end(ParseContext* pc, const uint8_t* buf, int buf_size) {
  return 0;
}
int ff_msmpeg4_decode_picture_header(MpegEncContext* s) {
  return 0;
}
int ff_wmv2_decode_picture_header(MpegEncContext* s) {
  return 0;
}
int ff_wmv2_decode_secondary_picture_header(MpegEncContext* s) {
  return 0;
}
void ff_aacdec_init_mips(AACContext* c) {
}
int ff_get_cpu_flags_aarch64(void) {
  return 0;
}
int ff_get_cpu_flags_arm(void) {
  return 0;
}
int ff_get_cpu_flags_ppc(void) {
  return 0;
}
int ff_get_cpu_flags_x86(void) {
  return 0;
}
size_t ff_get_cpu_max_align_aarch64(void) {
  return 0;
}
size_t ff_get_cpu_max_align_arm(void) {
  return 0;
}
size_t ff_get_cpu_max_align_ppc(void) {
  return 0;
}
size_t ff_get_cpu_max_align_x86(void) {
  return 0;
}
av_cold void rgb2rgb_init_x86(void) {
}
av_cold SwsFunc ff_yuv2rgb_init_x86(SwsContext* c) {
  return NULL;
}
av_cold SwsFunc ff_yuv2rgb_init_ppc(SwsContext* c) {
  return NULL;
}
av_cold void ff_get_unscaled_swscale_ppc(SwsContext* c) {
}
void ff_get_unscaled_swscale_arm(SwsContext* c) {
}
void ff_get_unscaled_swscale_aarch64(SwsContext* c) {
}
av_cold void ff_fft_init_aarch64(FFTContext* s) {
}
av_cold void ff_fft_init_x86(FFTContext* s) {
}
av_cold void ff_fft_init_arm(FFTContext* s) {
}
av_cold void ff_fft_init_mips(FFTContext* s) {
}
av_cold void ff_fft_init_ppc(FFTContext* s) {
}
av_cold void ff_rdft_init_arm(RDFTContext* s) {
}
int swri_rematrix_init_x86(struct SwrContext* s) {
  return 0;
}
av_cold void swri_audio_convert_init_aarch64(struct AudioConvert* ac, enum AVSampleFormat out_fmt,
                                             enum AVSampleFormat in_fmt, int channels) {
}
av_cold void swri_audio_convert_init_arm(struct AudioConvert* ac, enum AVSampleFormat out_fmt,
                                         enum AVSampleFormat in_fmt, int channels) {
}
av_cold void swri_audio_convert_init_x86(struct AudioConvert* ac, enum AVSampleFormat out_fmt,
                                         enum AVSampleFormat in_fmt, int channels) {
}
av_cold void ff_mpv_common_init_arm(MpegEncContext* s) {
}
av_cold void ff_mpv_common_init_axp(MpegEncContext* s) {
}
av_cold void ff_mpv_common_init_neon(MpegEncContext* s) {
}
av_cold void ff_mpv_common_init_ppc(MpegEncContext* s) {
}
av_cold void ff_mpv_common_init_x86(MpegEncContext* s) {
}
av_cold void ff_mpv_common_init_mips(MpegEncContext* s) {
}
void ff_wmv2_add_mb(MpegEncContext* s, int16_t block1[6][64], uint8_t* dest_y, uint8_t* dest_cb,
                    uint8_t* dest_cr) {
}
av_cold void ff_h263dsp_init_x86(H263DSPContext* c) {
}
av_cold void ff_h263dsp_init_mips(H263DSPContext* c) {
}
void ff_qpeldsp_init_x86(QpelDSPContext* c) {
}

void ff_qpeldsp_init_mips(QpelDSPContext* c) {
}
int ff_rv_decode_dc(MpegEncContext* s, int n) {
  return 0;
}
av_cold void ff_xvid_idct_init(IDCTDSPContext* c, AVCodecContext* avctx) {
}
av_cold void ff_float_dsp_init_aarch64(AVFloatDSPContext* fdsp) {
}
av_cold void ff_float_dsp_init_arm(AVFloatDSPContext* fdsp) {
}
av_cold void ff_float_dsp_init_ppc(AVFloatDSPContext* fdsp, int bit_exact) {
}
av_cold void ff_float_dsp_init_x86(AVFloatDSPContext* fdsp) {
}
void ff_float_dsp_init_mips(AVFloatDSPContext* fdsp) {
}
av_cold void ff_mdct15_init_x86(MDCT15Context* s) {
}
void ff_aacsbr_func_ptr_init_mips(AACSBRContext* c) {
}
av_cold void ff_fixed_dsp_init_x86(AVFixedDSPContext* fdsp) {
}
av_cold void ff_ac3dsp_init_arm(AC3DSPContext* c, int bit_exact) {
}
av_cold void ff_ac3dsp_init_x86(AC3DSPContext* c, int bit_exact) {
}
void ff_ac3dsp_init_mips(AC3DSPContext* c, int bit_exact) {
}
void ff_ac3dsp_set_downmix_x86(AC3DSPContext* c) {
}
av_cold void ff_bswapdsp_init_x86(BswapDSPContext* c) {
}
av_cold void ff_fmt_convert_init_aarch64(FmtConvertContext* c, AVCodecContext* avctx) {
}
av_cold void ff_fmt_convert_init_arm(FmtConvertContext* c, AVCodecContext* avctx) {
}
av_cold void ff_fmt_convert_init_ppc(FmtConvertContext* c, AVCodecContext* avctx) {
}
av_cold void ff_fmt_convert_init_x86(FmtConvertContext* c, AVCodecContext* avctx) {
}
av_cold void ff_fmt_convert_init_mips(FmtConvertContext* c) {
}
av_cold void ff_vorbisdsp_init_aarch64(VorbisDSPContext* c) {
}
av_cold void ff_vorbisdsp_init_x86(VorbisDSPContext* dsp) {
}
av_cold void ff_vorbisdsp_init_arm(VorbisDSPContext* c) {
}
av_cold void ff_vorbisdsp_init_ppc(VorbisDSPContext* c) {
}
av_cold void swri_resample_dsp_x86_init(ResampleContext* c) {
}
av_cold void swri_resample_dsp_arm_init(ResampleContext* c) {
}
av_cold void swri_resample_dsp_aarch64_init(ResampleContext* c) {
}
av_cold void ff_blockdsp_init_alpha(BlockDSPContext* c) {
}
av_cold void ff_blockdsp_init_arm(BlockDSPContext* c) {
}
av_cold void ff_blockdsp_init_ppc(BlockDSPContext* c) {
}
av_cold void ff_blockdsp_init_x86(BlockDSPContext* c, AVCodecContext* avctx) {
}
void ff_blockdsp_init_mips(BlockDSPContext* c) {
}
av_cold void ff_h264chroma_init_aarch64(H264ChromaContext* c, int bit_depth) {
}
av_cold void ff_h264chroma_init_arm(H264ChromaContext* c, int bit_depth) {
}
av_cold void ff_h264chroma_init_ppc(H264ChromaContext* c, int bit_depth) {
}
av_cold void ff_h264chroma_init_x86(H264ChromaContext* c, int bit_depth) {
}
av_cold void ff_h264chroma_init_mips(H264ChromaContext* c, int bit_depth) {
}
av_cold int ff_init_scantable_permutation_x86(uint8_t* idct_permutation,
                                              enum idct_permutation_type perm_type) {
}
av_cold void ff_idctdsp_init_aarch64(IDCTDSPContext* c, AVCodecContext* avctx,
                                     unsigned high_bit_depth) {
}
av_cold void ff_idctdsp_init_alpha(IDCTDSPContext* c, AVCodecContext* avctx,
                                   unsigned high_bit_depth) {
}
av_cold void ff_idctdsp_init_arm(IDCTDSPContext* c, AVCodecContext* avctx,
                                 unsigned high_bit_depth) {
}
av_cold void ff_idctdsp_init_ppc(IDCTDSPContext* c, AVCodecContext* avctx,
                                 unsigned high_bit_depth) {
}
av_cold void ff_idctdsp_init_x86(IDCTDSPContext* c, AVCodecContext* avctx,
                                 unsigned high_bit_depth) {
}
av_cold void ff_idctdsp_init_mips(IDCTDSPContext* c, AVCodecContext* avctx,
                                  unsigned high_bit_depth) {
}
av_cold void ff_hpeldsp_init_aarch64(HpelDSPContext* c, int flags) {
}
av_cold void ff_hpeldsp_init_alpha(HpelDSPContext* c, int flags) {
}
av_cold void ff_hpeldsp_init_arm(HpelDSPContext* c, int flags) {
}
av_cold void ff_hpeldsp_init_ppc(HpelDSPContext* c, int flags) {
}
av_cold void ff_hpeldsp_init_x86(HpelDSPContext* c, int flags) {
}
void ff_hpeldsp_init_mips(HpelDSPContext* c, int flags) {
}
av_cold void ff_mpegvideodsp_init_ppc(MpegVideoDSPContext* c) {
}
av_cold void ff_mpegvideodsp_init_x86(MpegVideoDSPContext* c) {
}
av_cold void ff_videodsp_init_aarch64(VideoDSPContext* ctx, int bpc) {
}
av_cold void ff_videodsp_init_arm(VideoDSPContext* ctx, int bpc) {
}
av_cold void ff_videodsp_init_ppc(VideoDSPContext* ctx, int bpc) {
}
av_cold void ff_videodsp_init_x86(VideoDSPContext* ctx, int bpc) {
}
av_cold void ff_videodsp_init_mips(VideoDSPContext* ctx, int bpc) {
}
void ff_h261_loop_filter(MpegEncContext* s) {
}
void ff_mspel_motion(MpegEncContext* s, uint8_t* dest_y, uint8_t* dest_cb, uint8_t* dest_cr,
                     uint8_t** ref_picture, op_pixels_func (*pix_op)[4], int motion_x, int motion_y,
                     int h) {
}
av_cold void ff_me_cmp_init_alpha(MECmpContext* c, AVCodecContext* avctx) {
}
av_cold void ff_me_cmp_init_arm(MECmpContext* c, AVCodecContext* avctx) {
}
av_cold void ff_me_cmp_init_ppc(MECmpContext* c, AVCodecContext* avctx) {
}
av_cold void ff_me_cmp_init_x86(MECmpContext* c, AVCodecContext* avctx) {
}
av_cold void ff_me_cmp_init_mips(MECmpContext* c, AVCodecContext* avctx) {
}
#include "libavcodec/h264dsp.h"
av_cold void ff_h264dsp_init_aarch64(H264DSPContext* c, const int bit_depth,
                                     const int chroma_format_idc) {
}
av_cold void ff_h264dsp_init_arm(H264DSPContext* c, const int bit_depth,
                                 const int chroma_format_idc) {
}
av_cold void ff_h264dsp_init_ppc(H264DSPContext* c, const int bit_depth,
                                 const int chroma_format_idc) {
}
av_cold void ff_h264dsp_init_x86(H264DSPContext* c, const int bit_depth,
                                 const int chroma_format_idc) {
}
av_cold void ff_h264dsp_init_mips(H264DSPContext* c, const int bit_depth,
                                  const int chroma_format_idc) {
}
#include "libavcodec/h264pred.h"
av_cold void ff_h264_pred_init_aarch64(H264PredContext* h, int codec_id, int bit_depth,
                                       const int chroma_format_idc) {
}
av_cold void ff_h264_pred_init_arm(H264PredContext* h, int codec_id, int bit_depth,
                                   const int chroma_format_idc) {
}
av_cold void ff_h264_pred_init_x86(H264PredContext* h, int codec_id, const int bit_depth,
                                   const int chroma_format_idc) {
}
av_cold void ff_h264_pred_init_mips(H264PredContext* h, int codec_id, int bit_depth,
                                    const int chroma_format_idc) {
}
#include "libavcodec/h264qpel.h"
av_cold void ff_h264qpel_init_aarch64(H264QpelContext* c, int bit_depth) {
}
av_cold void ff_h264qpel_init_arm(H264QpelContext* c, int bit_depth) {
}
av_cold void ff_h264qpel_init_ppc(H264QpelContext* c, int bit_depth) {
}
av_cold void ff_h264qpel_init_x86(H264QpelContext* c, int bit_depth) {
}
av_cold void ff_h264qpel_init_mips(H264QpelContext* c, int bit_depth) {
}
#include "libavcodec/sbrdsp.h"
av_cold void ff_sbrdsp_init_arm(SBRDSPContext* s) {
}
av_cold void ff_sbrdsp_init_aarch64(SBRDSPContext* s) {
}
av_cold void ff_sbrdsp_init_x86(SBRDSPContext* s) {
}
void ff_sbrdsp_init_mips(SBRDSPContext* s) {
}
#include "libavcodec/opus_pvq.h"
av_cold void ff_celt_pvq_init_x86(CeltPVQ* s) {
}
#include "libavcodec/opusdsp.h"
av_cold void ff_opus_dsp_init_x86(OpusDSP* ctx) {
}
av_cold void ff_opus_dsp_init_aarch64(OpusDSP* ctx) {
}
#include "libavcodec/aacpsdsp.h"
av_cold void ff_psdsp_init_arm(PSDSPContext* s) {
}
av_cold void ff_psdsp_init_aarch64(PSDSPContext* s) {
}
void ff_psdsp_init_mips(PSDSPContext* s) {
}
av_cold void ff_psdsp_init_x86(PSDSPContext* s) {
}
