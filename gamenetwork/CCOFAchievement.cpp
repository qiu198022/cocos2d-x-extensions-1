
#include "CCOFAchievement.h"

namespace extensions {
    
    CCOFAchievement* CCOFAchievement::achievementWithId(const char* id,
                                                        const char* title,
                                                        const char* description,
                                                        const char* iconUrl,
                                                        bool isUnlocked,
                                                        bool isSecret)
    {
        CCOFAchievement* ach = new CCOFAchievement();
        ach->id = id;
        ach->title = title;
        ach->description = description;
        ach->iconUrl = iconUrl;
        ach->isUnlocked = isUnlocked;
        ach->isSecret = isSecret;
        ach->autorelease();
        return ach;
    }
    
}
