/****************************************************************************
*
* This is a part of the TOTEM testbeam/monitoring software.
* This is a part of the TOTEM offline software.
* Authors: 
*	Mariusz Wojakowski
*
****************************************************************************/

#ifndef TOTEMRAWDATALIBRARY_CASTORSTORAGEFILE_H
#define TOTEMRAWDATALIBRARY_CASTORSTORAGEFILE_H

#include "TotemRawData/Readers/interface/StorageFile.h"
#include "shift.h"

namespace Totem {

/**
 * An implementation of StorageFile interface that provides access to files using the RFIO protocol.
 *
 * \ingroup StorageFile
 **/

    class RFIOStorageFile : public StorageFile {
    public:
        RFIOStorageFile(std::string const &fileName) : StorageFile(fileName) {}
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
        void Reopen();
    };
}

#endif //TOTEMRAWDATALIBRARY_CASTORSTORAGEFILE_H
