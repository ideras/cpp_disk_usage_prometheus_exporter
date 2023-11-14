#ifndef __EXPORTER_H__
#define __EXPORTER_H__

#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>
#include "dto/DiskUsageDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

#include <prometheus/gauge.h>
#include <prometheus/registry.h>
#include <prometheus/text_serializer.h>

namespace fs = std::filesystem;

class DiskUsage
{
public:
    DiskUsage() ;

    oatpp::Object<DiskUsageDto> getSize(const oatpp::String& path);
    void updateStats(const std::string& path);
    std::string getMetricsAsString();

private:
    double getFileSize(const std::string& entry_path);
    double getEntrySize(const fs::directory_entry& entry);

private:
    std::unique_ptr<prometheus::Registry> registry;
    prometheus::Family<prometheus::Gauge> *du_fam;
};

#endif
