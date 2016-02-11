#include "platform_file_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

FileData get_asset_data(const char* relative_path);
void release_asset_data(const FileData* file_data);

#ifdef __cplusplus
}
#endif
