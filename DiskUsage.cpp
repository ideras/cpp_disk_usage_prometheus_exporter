#include <iostream>
#include "DiskUsage.h"

DiskUsage::DiskUsage(): 
    du_fam (nullptr),
    registry(new prometheus::Registry)
{
}

double DiskUsage::getEntrySize(const fs::directory_entry& entry)
{
    double size = 0;

    if (!entry.is_directory() || entry.is_symlink()) {
        try {
            size = entry.file_size();
        } catch (const fs::filesystem_error&) {
            size = 0;
        }
   } else {
        
        for (const auto& de : 
             fs::directory_iterator(entry.path(),
                                    fs::directory_options::skip_permission_denied))
        {
            size += getEntrySize(de);
        }
   } 

   return size;
}

double DiskUsage::getFileSize(const std::string& entry_path)
{
    fs::path filepath(entry_path);
    fs::directory_entry dentry(filepath);

    return getEntrySize(dentry);
}

void DiskUsage::updateStats(const std::string& path)
{
    if (du_fam != nullptr)
    {
        registry->Remove(*du_fam);
    }

    du_fam = std::addressof(prometheus::BuildGauge()
                                .Name("node_disk_usage_bytes")
                                .Help("Disk usage of the directory/file")
                                .Register(*registry)
                            );

    auto& du = *du_fam;

    fs::directory_options flags = fs::directory_options::none |
                                fs::directory_options::skip_permission_denied;
    for (const fs::directory_entry& de : fs::directory_iterator(path, flags))
    {
        if (de.is_directory() && !de.is_symlink())
        {
            double size = getFileSize(de.path().string());
            prometheus::Labels lbl_path;

            prometheus::Gauge& gauge = du.Add({{"path", de.path()}});
            gauge.Set(size);
        }
    }
}

std::string DiskUsage::getMetricsAsString()
{
    prometheus::TextSerializer ts;

    updateStats("/var");
    return ts.Serialize(registry->Collect());
}

oatpp::Object<DiskUsageDto> DiskUsage::getSize(const oatpp::String& path)
{
    oatpp::Object<DiskUsageDto> dudto = oatpp::Object<DiskUsageDto>::createShared();

    std::string the_path = "/" + *path;
    dudto->path = the_path;
    dudto->size = getFileSize(the_path);

    return dudto;
}