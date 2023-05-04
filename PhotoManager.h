/*************************************************************************
    > File Name: PhotoManager.h
    > Author: racle
    > Mail: racleray@qq.com
    > Created Time:
 ************************************************************************/

#ifndef _PHOTOMANAGER_H
#define _PHOTOMANAGER_H

#include "PhotoInfo.h"

namespace raybo {
class PhotoManager {
private:
    PhotoInfo photos_[MAX_MESSAGES];
    GETSETVAR(int, photo_count)

public:
    void Start();
    void Proc();
    void Shutdown();
    void Restart();

    int        CreatePhoto(int user_id);
    PhotoInfo* GetPhoto(int user_id);
    int        UpdatePhoto(int user_id, int publisher_id, int publish_time,
                           int publish_message_id);
};

}  // namespace raybo

#endif
