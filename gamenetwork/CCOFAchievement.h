
#ifndef __EXTENSIONS_CCOFACHIEVEMENT_H_
#define __EXTENSIONS_CCOFACHIEVEMENT_H_

#include <string>
#include "CCObject.h"

using namespace std;
using namespace cocos2d;

namespace extensions {
    
    class CCOFAchievement : public CCObject
    {
    public:
        static CCOFAchievement* achievementWithId(const char* id,
                                                  const char* title,
                                                  const char* description,
                                                  const char* iconUrl,
                                                  bool isUnlocked,
                                                  bool isSecret);
        
        string  id;
        string  title;
        string  description;
        string  iconUrl;
        bool    isUnlocked;
        bool    isSecret;
        
    private:
        CCOFAchievement(void) {}
    };
    
}

#endif // __EXTENSIONS_CCOFACHIEVEMENT_H_
