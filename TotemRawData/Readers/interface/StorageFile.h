/****************************************************************************
*
* This is a part of the TOTEM testbeam/monitoring software.
* This is a part of the TOTEM offline software.
* Authors: 
*	Mariusz Wojakowski
*
****************************************************************************/

#ifndef TOTEMRAWDATALIBRARY_STORAGEFILE_H
#define TOTEMRAWDATALIBRARY_STORAGEFILE_H

#include <string>
#include <cstdio>

/**
 * \defgroup StorageFile Storage
 *
 * StorageFile and all inherited classes provide abstraction layer upon different types of storage.
 **/

namespace Totem {

/**
 * StorageFile is a unified interface for accessing files on different storage systems (local, CASTOR, EOS, ...).
 *
 * It provides methods for opening/closing file, reading data, seeking, checking errors, etc.
 * If you want to use new type of storage, you have to inherit from StorageFile class and implement all methods.
 *
 * \ingroup StorageFile
 **/
    class StorageFile {
    public:
        StorageFile(const std::string &fileName) : fileName(fileName) {};
        virtual ~StorageFile() {};
        virtual bool OpenFile() = 0;                                            ///< opens a file
        virtual int Seek(long position, int origin = SEEK_SET) = 0;             ///< sets the position indicator to a provided as an argument position
        virtual long CurrentPosition() = 0;                                     ///< returns current position of the position indicator
        virtual bool IsOpened() = 0;                                            ///< returns true when file is opened
        virtual int CloseFile() = 0;                                            ///< closes the file associated with StorageFile object
        virtual size_t ReadData(void *ptr, size_t size, size_t nmemb) = 0;      ///< reads 'nmemb' elements of size 'size' and stores them in block of memory pointed by 'ptr'
        virtual int CheckEOF() = 0;                                             ///< returns a value different from zero when meets EOF
        virtual int CheckError() = 0;                                           ///< returns a value different from zero when meets an error
        virtual void PrintError(const std::string &) = 0;                       ///< prints error on standard output
        virtual std::string GetURLPath();                                       ///< returns URL path of file associated with StorageFile object

        /**
         * Creates an instance of appropriate StorageFile object for given URL path.
         * The match between URL path and type of object is chosen using the given criteria:
         *   - RFIOStorageFile: if URL path starts with "/castor" or "rfio://"
         *   - XRootStorageFile: if URL path starts with "root://" or "xroot://"
         *   - LocalStorageFile: when none of the above requirements is met
         **/
        static StorageFile* CreateInstance(const std::string &urlPath);

    protected:
        const std::string fileName;
    };
}


#endif //TOTEMRAWDATALIBRARY_STORAGEFILE_H
