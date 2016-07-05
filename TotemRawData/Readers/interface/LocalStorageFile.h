/****************************************************************************
*
* This is a part of the TOTEM testbeam/monitoring software.
* This is a part of the TOTEM offline software.
* Authors: 
*	Mariusz Wojakowski
*
****************************************************************************/

#ifndef TOTEMRAWDATALIBRARY_LOCALSTORAGEFILE_H
#define TOTEMRAWDATALIBRARY_LOCALSTORAGEFILE_H

#include <fcntl.h>
#include <stdio.h>
#include <iostream>

#include "TotemRawData/Readers/interface/StorageFile.h"

namespace Totem {

/**
 * An implementation of StorageFile interface that provides access to files on local filesystem.
 *
 * \ingroup StorageFile
 **/

    class LocalStorageFile : public StorageFile {
    public:
        LocalStorageFile(std::string const &fileName) : StorageFile(fileName) {}
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
        FILE *file;
    };
}

#endif //TOTEMRAWDATALIBRARY_LOCALSTORAGEFILE_H
