#ifndef __QL_MIXER_H__
#define __QL_MIXER_H__
/**
 * @brief Set alsa controls
 * @details
 *      eg: \n
 *      set codec 5616 main volume : \n
 *      Ql_ctl_set_mixer_value("DAC1 Playback Volume", 2, "175 175");
 *
 * @param device
 *      alsa controls' string.
 * @param count
 *      alsa controls' parameter numbers
 * @param value
 *      alsa contorls' parameter string
 *
 * @return 
 *      Succeed: TRUE. \n
 *      Fail:    FALSE.
 * @code{c}
 *      //Set one para opration:
 *      Ql_clt_set_mixer_value("SEC_MI2S_RX Audio Mixer MultiMedia1", 1, "1");
 *      
 *      //Set two para opration:
 *      Ql_clt_set_mixer_value("DAC1 Playback Volume", 2, "175 175");
 *      
 *      //Set three para opration:
 *      Ql_clt_set_mixer_value("Voice Rx Gain", 3, "0 -1 500");
 * @endcode
 */
boolean Ql_clt_set_mixer_value(const char *device, int count, const char *value);

/**
 * @brief Get alsa controls
 *
 * @param device
 *      alsa controls' string.
 *
 * @return 
 *      Succeed: parameter numbers. \n
 *      Fail:    -1.
 * @code{c}
 *      //Get codec alc5616 main volume :
 *      ret = Ql_ctl_Get_mixer_value("DAC1 Playback Volume", &ev);
 *      //ret must be 2. \n
 *      //ev->value.integer.value[0] is left channel volume for alc5616 main volume.
 *      //ev->value.integer.value[1] is right channel volume for alc5616 main volume.
 * @endcode
 */
int Ql_clt_get_mixer_value(const char *device, struct snd_ctl_elem_value *ev);

#endif
