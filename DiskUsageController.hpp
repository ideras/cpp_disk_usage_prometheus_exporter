
#ifndef UserController_hpp
#define UserController_hpp

#include "DiskUsage.h"

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Disk usage REST controller.
 */
class DiskUsageController : public oatpp::web::server::api::ApiController {
public:
  DiskUsageController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}

public:

  static std::shared_ptr<DiskUsageController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<DiskUsageController>(objectMapper);
  }
 
  ENDPOINT("GET", "du/{path}", getSize, PATH(String, path))
  {
    return createDtoResponse(Status::CODE_200, du.getSize(path));
  }
  
  ENDPOINT("GET", "/metrics", getMetrics)
  {
    std::string text = du.getMetricsAsString();

    auto response = createResponse(Status::CODE_200, text);
    response->putHeader(Header::CONTENT_TYPE, "text/plain");

    return response;
  }

  private:
    DiskUsage du;
};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* UserController_hpp */
