#include <iostream>
#include "TotemRawData/Readers/interface/StorageFile.h"
#include "TotemRawData/Readers/interface/LocalStorageFile.h"

#include "TotemRawData/Readers/interface/RFIOStorageFile.h"

#include "TotemRawData/Readers/interface/XRootStorageFile.h"

namespace Totem {

StorageFile* StorageFile::CreateInstance(const std::string &urlPath)
{
  if (urlPath.find("/castor") == 0 || urlPath.find("rfio://") == 0)
  {
    return new RFIOStorageFile(urlPath);
  }
  else if (urlPath.find("root://") == 0 || urlPath.find("xroot://") == 0)
  {
    return new XRootStorageFile(urlPath);
  }

  return new LocalStorageFile(urlPath);
}

std::string StorageFile::GetURLPath()
{
  return fileName;
}

}
