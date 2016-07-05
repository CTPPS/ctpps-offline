/****************************************************************************
*
* This is a part of the TOTEM testbeam/monitoring software.
* This is a part of the TOTEM offline software.
* Authors: 
*	Mariusz Wojakowski
*
****************************************************************************/

#ifndef TOTEMRAWDATALIBRARY_XROOTSTORAGEFILE_H
#define TOTEMRAWDATALIBRARY_XROOTSTORAGEFILE_H

#include "TotemRawData/Readers/interface/StorageFile.h"
#include <XrdPosix/XrdPosixXrootd.hh>
//#include "XrdClient/XrdClient.hh"


using namespace std;

namespace Totem {

/**
 * An implementation of StorageFile interface that provides access to files using XRoot protocol.
 *
 * \ingroup StorageFile
 **/

    class XRootStorageFile : public StorageFile {
    public:
        XRootStorageFile(std::string const &fileName) : StorageFile(fileName) {}
        virtual bool OpenFile();
        virtual int Seek(long position, int origin = SEEK_SET);
        virtual long CurrentPosition();
        virtual bool IsOpened();
        virtual int CloseFile();
        virtual size_t ReadData(void *ptr, size_t size, size_t nmemb);
        virtual int CheckEOF();
        virtual int CheckError();
        virtual void PrintError(const std::string &);

    private:
        int fd;
    };
}

#endif //TOTEMRAWDATALIBRARY_XROOTSTORAGEFILE_H
