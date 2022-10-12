#ifndef COMMON_H
#define COMMON_H
#include <QString>

enum ClientStatus
{
    CONNECT_SUCCESS,
    CONNECT_FAIL,
    OPEN_DIR,
    DOWNLOAD_FILE_SUCCESS,
    DOWNLOAD_FILE_FAIL,
    DOWNLOAD_DIR_SUCCESS,
    DOWNLOAD_DIR_FAIL,
    UPLOAD_FILE_SUCCESS,
    UPLOAD_FILE_FAIL,
    UPLOAD_DIR_SUCCESS,
    UPLOAD_DIR_FAIL,
    INFO,
    SUCCESS
};

enum FileType
{
    NORMAL,
    DIR
};

struct FileInfo
{
   FileType type;
   QString name;
};
#endif // COMMON_H
