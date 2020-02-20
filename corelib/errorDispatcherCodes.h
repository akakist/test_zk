#ifndef _______errorDispatcherCodes____H
#define _______errorDispatcherCodes____H
enum ErrorDispatcherClass
{
    FATAL,
    INFO,
    TRACE,

};
enum ErrorDispatcherCode
{
    ED_AUDIO_INIT_ERROR,
    ED_avcodec_decode_video2_error,
    ED_FILE_ERROR,
    ED_DFSIO_ERROR,
    ED_UNSUPPORTED_CONTENT,
    ED_STATUS_NOTIFY,
    ED_CANNOT_FIND_REMOTE_SERVICE,
    ED_NOTIFY_PAUSE_FROM_PLAYER_TO_UI,
    ED_NOTIFY_PLAY_FROM_PLAYER_TO_UI,
    ED_NOTIFY_STOP_FROM_PLAYER_TO_UI,
    ED_NOTIFY_MONEY_REQUIRED_TO_PLAY,
    ED_NOTIFY_PRICE_EXCEEDS_MAX_PRICE,
    ED_OPEN_FILE_ERROR,
    ED_VERSION_WRONG,
    ED_VIDEO_PAUSED,
    ED_VIDEO_UNPAUSED,
    ED_TOGGLE_MENU,

};
#endif
