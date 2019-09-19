#ifndef __QL_AMR_H__
#define __QL_AMR_H__

/**
 * @brief   Audio Amr mode
 */
typedef enum {
    AUD_AMRNB_MR475 = 0,
    AUD_AMRNB_MR515,
    AUD_AMRNB_MR59,
    AUD_AMRNB_MR67,
    AUD_AMRNB_MR74,
    AUD_AMRNB_MR795,
    AUD_AMRNB_MR102,
    AUD_AMRNB_MR122,
} Enum_AudAMRNB_Mode;

/**
 * @brief amrnb encoder handle init function
 *
 * @param amrnb
 *      pointer of pointer for the amrnb encoder handle.
 *
 * @return 
 *      Succeed: 0. \n 
 *      Fail:    -1.
 */
int Ql_amrnb_enc_init(void **amrnb);

/**
 * @brief amrnb encoder handle deinit function
 *
 * @param amrnb
 *      pointer of amrnb encoder handle.
 *
 * @return 
 *      Succeed: 0. \n 
 *      Fail:    -1.
 */
int Ql_amrnb_enc_deinit(void *amrnb);

/**
 * @brief function convert wav data to amrnb data
 * @detail
 *      Can only convert 320bytes wav data(one amr frame) each time. \n
 *
 * @param amrnb
 *      pointer of amrnb handle.
 * @param mode
 *      reference to @ref Enum_AudAMRNB_Mode
 * @param inbuf
 *      input wav data buffer
 * @param outbuf
 *      output amrnb data buffer(just one amrnb frame)
 *
 * @return 
 *      Succeed: size of amrnb frame. \n 
 *      Fail:    -1.
 */
int Ql_wav2amrnb(void *amrnb, int mode, unsigned char *inbuf, unsigned char *outbuf);

/**
 * @brief Get amrnb frame size(include head byte).
 *
 * @param head
 *      amrnb frame head byte.
 *
 * @return 
 *      amrnb frame size(include head byte). 
 */
int Ql_amrnb_get_fsize(char head);

/**
 * @brief amrnb decoder handle init function 
 *
 * @param amrnb
 *      pointer of pointer for amrnb decoder handle.
 *
 * @return 
 *      Succeed: 0. \n 
 *      Fail:    -1.
 */
int Ql_amrnb_dec_init(void **amrnb);

/**
 * @brief amrnb decoder handle deinit function 
 *
 * @param amrnb
 *      pointer of amrnb decoder handle.
 *
 * @return 
 *      Succeed: 0. \n 
 *      Fail:    -1.
 */
int Ql_amrnb_dec_deinit(void *amrnb);

/**
 * @brief function convert wav data to amrnb data
 * @detail
 *      Can only convert one amrnb frame (320bytes wav data) each time. \n
 *
 * @param amrnb
 *      pointer of amrnb handle.
 * @param inbuf
 *      input amrnb data buffer(just one amrnb frame).
 * @param outbuf
 *      output wav data buffer(320 bytes).
 *
 * @return 
 *      Succeed: size of amrnb frame(320). \n 
 *      Fail:    -1.
 */
int Ql_amrnb2wav(void *amrnb, unsigned char *inbuf, unsigned char *outbuf);

/**
 * @brief Get amrwb frame size(include head byte).
 *
 * @param head
 *      amrwb frame head byte.
 *
 * @return 
 *      amrwb frame size(include head byte). 
 */
int Ql_amrwb_get_fsize(char head);

#endif
