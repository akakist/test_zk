QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH+=.. /Users/Sergej/znamenka/proj/lib/jsoncpp-0.5.0/include ../corelib
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += REAL_DOUBLE
SOURCES += \
        ../corelib/DBH.cpp \
        ../corelib/Integer.cpp \
        ../corelib/Rational.cpp \
        ../corelib/_QUERY.cpp \
        ../corelib/__crc16.cpp \
        ../corelib/__crc32.cpp \
        ../corelib/__crc64.cpp \
        ../corelib/_bitStream.cpp \
        ../corelib/broadcaster.cpp \
        ../corelib/commonError.cpp \
        ../corelib/configDB.cpp \
        ../corelib/epoll_socket_info.cpp \
        ../corelib/event.cpp \
        ../corelib/eventDeque.cpp \
        ../corelib/httpConnection.cpp \
        ../corelib/ioBuffer.cpp \
        ../corelib/jpge.cpp \
        ../corelib/js_utils.cpp \
        ../corelib/jsonHandler.cpp \
        ../corelib/listenerBase.cpp \
        ../corelib/listenerBuffered.cpp \
        ../corelib/listenerBuffered1Thread.cpp \
        ../corelib/listenerPolled.cpp \
        ../corelib/listenerSimple.cpp \
        ../corelib/logging.cpp \
        ../corelib/msockaddr_in.cpp \
        ../corelib/mtimespec.cpp \
        ../corelib/mutexInspector.cpp \
        ../corelib/mutexable.cpp \
        ../corelib/neighbours.cpp \
        ../corelib/networkMultiplexor.cpp \
        ../corelib/objectHandler.cpp \
        ../corelib/route_t.cpp \
        ../corelib/socketsContainer.cpp \
        ../corelib/st_rsa.cpp \
        ../corelib/trashable.cpp \
        ../corelib/unknown.cpp \
        ../corelib/url.cpp \
        ../corelib/webDumpable.cpp \
        ../lib/jsoncpp-0.5.0/src/lib_json/json_reader.cpp \
        ../lib/jsoncpp-0.5.0/src/lib_json/json_value.cpp \
        ../lib/jsoncpp-0.5.0/src/lib_json/json_writer.cpp \
        ../modules/objectProxy/objectProxyService.cpp \
        ../modules/socket/socketService.cpp \
        ../modules/timer/timerService.cpp \
        ../mt_lib/CInstance.cpp \
        ../mt_lib/CUtils.cpp \
        ../mt_lib/configObj.cpp \
        ../mt_lib/iutils_decl.cpp \
        ../mt_lib/threadNameCtl.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../corelib/AUTHCOOKIE_id.h \
    ../corelib/CHUNK_id.h \
    ../corelib/CLASS_id.h \
    ../corelib/CONTAINER.h \
    ../corelib/CapsId.h \
    ../corelib/DATA_id.h \
    ../corelib/DBH.h \
    ../corelib/DB_POSTFIX.h \
    ../corelib/DB_id.h \
    ../corelib/EVENT_id.h \
    ../corelib/ErrorDispatcherHelper.h \
    ../corelib/GlobalCookie_id.h \
    ../corelib/IConfigDB.h \
    ../corelib/IConfigObj.h \
    ../corelib/IGEOIP.h \
    ../corelib/IInstance.h \
    ../corelib/ILogger.h \
    ../corelib/IObjectProxy.h \
    ../corelib/IProgress.h \
    ../corelib/IRPC.h \
    ../corelib/ISSL.h \
    ../corelib/ITests.h \
    ../corelib/IThreadNameController.h \
    ../corelib/IUtils.h \
    ../corelib/Integer.h \
    ../corelib/JAVACOOKIE_id.h \
    ../corelib/REF.h \
    ../corelib/Rational.h \
    ../corelib/Real.h \
    ../corelib/SEQ_id.h \
    ../corelib/SERVICE_id.h \
    ../corelib/SOCKET_fd.h \
    ../corelib/SOCKET_id.h \
    ../corelib/URI.h \
    ../corelib/USER_id.h \
    ../corelib/VERSION_id.h \
    ../corelib/_QUERY.h \
    ../corelib/__crc16.h \
    ../corelib/__crc32.h \
    ../corelib/__crc64.h \
    ../corelib/_bitStream.h \
    ../corelib/broadcaster.h \
    ../corelib/bufferVerify.h \
    ../corelib/colorOutput.h \
    ../corelib/commonError.h \
    ../corelib/compat_win32.h \
    ../corelib/configDB.h \
    ../corelib/dfsErrors.h \
    ../corelib/e_poll.h \
    ../corelib/epoll_socket_info.h \
    ../corelib/errorDispatcherCodes.h \
    ../corelib/event.h \
    ../corelib/eventDeque.h \
    ../corelib/eventEnum.h \
    ../corelib/evfilt_name.h \
    ../corelib/gTry.h \
    ../corelib/httpConnection.h \
    ../corelib/ifaces.h \
    ../corelib/ioBuffer.h \
    ../corelib/jpeg_decoder.h \
    ../corelib/jpge.h \
    ../corelib/js_utils.h \
    ../corelib/jsonHandler.h \
    ../corelib/linkinfo.h \
    ../corelib/listenerBase.h \
    ../corelib/listenerBuffered.h \
    ../corelib/listenerBuffered1Thread.h \
    ../corelib/listenerPolled.h \
    ../corelib/listenerSimple.h \
    ../corelib/logging.h \
    ../corelib/msockaddr_in.h \
    ../corelib/mtimespec.h \
    ../corelib/mutexInspector.h \
    ../corelib/mutex_inspector_entry.h \
    ../corelib/mutexable.h \
    ../corelib/neighbours.h \
    ../corelib/networkMultiplexor.h \
    ../corelib/objectHandler.h \
    ../corelib/pollable.h \
    ../corelib/queryResult.h \
    ../corelib/refstring.h \
    ../corelib/route_t.h \
    ../corelib/serviceEnum.h \
    ../corelib/socketsContainer.h \
    ../corelib/st_FILE.h \
    ../corelib/st_malloc.h \
    ../corelib/st_rsa.h \
    ../corelib/timerHelper.h \
    ../corelib/tools_mt.h \
    ../corelib/trashable.h \
    ../corelib/unknown.h \
    ../corelib/unknownCastDef.h \
    ../corelib/url.h \
    ../corelib/userObjectHandler.h \
    ../corelib/version_mega.h \
    ../corelib/webDumpable.h \
    ../modules/objectProxy/objectProxyService.h \
    ../modules/socket/socketService.h \
    ../modules/socket/socketStats.h \
    ../modules/timer/timerService.h \
    ../mt_lib/CInstance.h \
    ../mt_lib/CUtils.h \
    ../mt_lib/configObj.h \
    ../mt_lib/progressor.h \
    ../mt_lib/threadNameCtl.h \
    ../mt_lib/utils_local.h

DISTFILES += \
    ../corelib/CMakeLists.txt \
    ../mt_lib/CMakeLists.txt
