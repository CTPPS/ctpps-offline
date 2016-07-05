#include <fcntl.h>
#include "TotemRawData/Readers/interface/XRootStorageFile.h"

namespace Totem {
    bool XRootStorageFile::OpenFile() {
        fd = XrdPosixXrootd::Open(fileName.c_str(), O_RDONLY);

        return fd != -1;
    }

    int XRootStorageFile::Seek(long position, int origin) {
        return XrdPosixXrootd::Lseek(fd, position, origin);
    }

    long XRootStorageFile::CurrentPosition() {
        return XrdPosixXrootd::Lseek(fd, 0, SEEK_CUR);
    }

    bool XRootStorageFile::IsOpened() {
        return fd != -1;
    }

    int XRootStorageFile::CloseFile() {
        return XrdPosixXrootd::Close(fd);
    }

    size_t XRootStorageFile::ReadData(void *ptr, size_t size, size_t nmemb) {
        return XrdPosixXrootd::Read(fd, ptr, size*nmemb);
    }

    int XRootStorageFile::CheckEOF() {
        char buf[2];
        int read = XrdPosixXrootd::Read(fd, buf, 1);
        if(read==0) {
            return 1;
        }
        else {
            Seek(-1, SEEK_CUR);
            return 0;
        }
    }

    int XRootStorageFile::CheckError() {
        return XrdPosixXrootd::Read(fd, NULL, 0);
    }

    void XRootStorageFile::PrintError(string const &message) {
        perror(const_cast<char*>(message.c_str()));
    }
}
