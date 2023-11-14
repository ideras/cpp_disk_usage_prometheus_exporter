#ifndef __DISK_USAGE_DTO_H__
#define __DISK_USAGE_DTO_H__

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DiskUsageDto : public oatpp::DTO {

  DTO_INIT(DiskUsageDto, DTO)

  DTO_FIELD(String, path);
  DTO_FIELD(Float64, size);
};

#include OATPP_CODEGEN_END(DTO)

#endif //__DISK_USAGE_DTO_H__
