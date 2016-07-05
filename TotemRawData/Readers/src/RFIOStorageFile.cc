#include "TotemRawData/Readers/interface/StorageFile.h"
#include "TotemRawData/Readers/interface/RFIOStorageFile.h"

namespace Totem {
    bool RFIOStorageFile::OpenFile() {
        file = rfio_fopen(const_cast<char*>(fileName.c_str()), const_cast<char*>("r"));
        return (bool) file;
    }

    int RFIOStorageFile::Seek(long position, int origin) {
        if (rfio_feof(file)) {
            Reopen();
        }
        return rfio_fseek(file, position, origin);
    }

    long RFIOStorageFile::CurrentPosition() {
        return rfio_ftell(file);
    }

    bool RFIOStorageFile::IsOpened() {
        return (bool) file;
    }

    int RFIOStorageFile::CloseFile() {
        return rfio_fclose(file);
    }

    size_t RFIOStorageFile::ReadData(void *ptr, size_t size, size_t nmemb) {
        return rfio_fread(ptr, size, nmemb, file);
    }
    int RFIOStorageFile::CheckEOF() {
        return rfio_feof(file);
    }

    int RFIOStorageFile::CheckError() {
        return rfio_ferror(file);
    }

    void RFIOStorageFile::PrintError(const std::string &string) {
        rfio_perror(const_cast<char*>(string.c_str()));
    }

    void RFIOStorageFile::Reopen() {
        rfio_fclose(file);
        file = rfio_fopen(const_cast<char*>(fileName.c_str()), const_cast<char*>("r"));
    }
}
