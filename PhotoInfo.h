/*************************************************************************
    > File Name: PhotoInfo.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _PHOTOINFO_H
#define _PHOTOINFO_H

#include "common/macro.h"
#include <string.h>

namespace raybo {
class PhotoInfo {
    GETSETVAR(int, user_id)
    GETSETVAR(int, last_publisher_id)
};
}  // namespace raybo

#endif
