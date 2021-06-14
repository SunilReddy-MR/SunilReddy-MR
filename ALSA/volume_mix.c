#include <alsa/asoundlib.h>
#include <alsa/mixer.h>

int main(int argc, char *argv[])
{
  /*  long volume;
    if (argc != 3) {
        printf("Usage: %s snd_card_name vol\n",argv[0]);
        return 1;
    }
    volume = atol(argv[2]);
*/
    long min, max;
    int ret;
    long volume;
    volume=0; 
    const char * channel_name;

    snd_mixer_selem_channel_id_t channe1=0;
    snd_mixer_selem_channel_id_t channe2=1;
    
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    const char *card = "hw:1";
    const char *selem_name = "PCM";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_malloc(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    //printf("Playback volume min =%ld\n",min);
    //printf("Playback volume max =%ld\n",max);

    ret = snd_mixer_selem_has_capture_channel(elem,channe1);
    printf("channel available =%d\n",ret);
    printf("channel =%d\n",channe1);
    ret =0;
    
    ret = snd_mixer_selem_set_playback_volume(elem, channe1,0*max/100);
    //printf("set volume ret =%d \n",ret);
    printf("Playback volume set retchannel1  =%d and value =%d \n",snd_mixer_selem_get_playback_volume(elem,channe1,&volume),volume);
    
    ret = snd_mixer_selem_has_capture_channel(elem,channe1);
    printf("channel available =%d\n",ret);
    printf("channel =%d\n",channe1);
    ret =0;

    ret = snd_mixer_selem_set_playback_volume(elem, channe2,100*max/100);
    printf("set volume ret =%d \n",ret);
    printf("Playback volume set channel2 ret  =%d and value =%ld \n",snd_mixer_selem_get_playback_volume(elem,channe2,&volume),volume);




    channel_name = snd_mixer_selem_channel_name(channe1);  
    printf("channe1_name =%s\n",channel_name);    

    channel_name = snd_mixer_selem_channel_name(channe2);
    printf("channe2_name =%s\n",channel_name);

    //snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);
    //printf("Mixer closing succesfully\n");
    //snd_mixer_close(handle);
    
    ret = snd_mixer_selem_get_playback_volume(elem,SND_MIXER_SCHN_FRONT_RIGHT, &volume);

    printf("ret =%d\n",ret);
    printf("palyback volume =%ld\n",volume);

   
   printf("Mixer closing succesfully\n");
   snd_mixer_close(handle);
   
    return 0;
}
