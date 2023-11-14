
#ifndef __STATIC_CONTROLLER_H__
#define __STATIC_CONTROLLER_H__

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

class StaticController : public oatpp::web::server::api::ApiController {
public:
  StaticController(const std::shared_ptr<ObjectMapper>& objectMapper)
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  static std::shared_ptr<StaticController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<StaticController>(objectMapper);
  }

  ENDPOINT("GET", "/", root) {
    const char* html =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"utf-8\">\n"
        "	<meta name=\"viewport\" content=\"width=device-width\">\n"
        "	<title>Disk Usage Prometheus Exporter</title>\n"
        "</head>\n"
        "<body>\n"
        "<h1>Disk Usage Prometheus Exporter</h1>\n"
        "<p>\n"
        "	<a href=\"/metrics\">Metrics</a>\n"
        "</p>\n"
        "<p>\n"
        "	<a href=\"https://github.com/dundee/disk_usage_exporter\">Homepage</a>\n"
        "</p>\n"
        "</body>\n"
        "</html>;\n";

    auto response = createResponse(Status::CODE_200, html);
    response->putHeader(Header::CONTENT_TYPE, "text/html");
    return response;
  }

  ENDPOINT("GET", "/algo", algo) {
        const char* html =
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "<head>\n"
        "    <meta charset=\"utf-8\">\n"
        "	<meta name=\"viewport\" content=\"width=device-width\">\n"
        "	<title>Algo bla bla ...</title>\n"
        "</head>\n"
        "<body>\n"
        "<h1>Bla bla ....</h1>\n"
        "<p>\n"
        "	<a href=\"/metrics\">Metrics</a>\n"
        "</p>\n"
        "</body>\n"
        "</html>;\n";

    auto response = createResponse(Status::CODE_200, html);
    response->putHeader(Header::CONTENT_TYPE, "text/html");
    return response;
  }
};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif //__STATIC_CONTROLLER_H__
