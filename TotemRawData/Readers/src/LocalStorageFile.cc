#include "TotemRawData/Readers/interface/LocalStorageFile.h"

namespace Totem {
    bool LocalStorageFile::OpenFile() {
        file = fopen(const_cast<char*>(fileName.c_str()), const_cast<char*>("r"));
        return (bool) file;
    }

    int LocalStorageFile::Seek(long position, int origin) {
        return fseek(file, position, origin);
    }

    long LocalStorageFile::CurrentPosition() {
        return ftell(file);
    }

    bool LocalStorageFile::IsOpened() {
        return (bool) file;
    }

    int LocalStorageFile::CloseFile() {
        if(file)
            return fclose(file);
        return -1;
    }

    size_t LocalStorageFile::ReadData(void *ptr, size_t size, size_t nmemb) {
        return fread(ptr, size, nmemb, file);
    }

    int LocalStorageFile::CheckEOF() {
        return feof(file);
    }

    int LocalStorageFile::CheckError() {
        return ferror(file);
    }

    void LocalStorageFile::PrintError(const std::string &string) {
        perror(const_cast<char*>(string.c_str()));
    }
}
