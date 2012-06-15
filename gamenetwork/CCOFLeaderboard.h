
#ifndef __EXTENSIONS_CCOFLEADERBOARD_H_
#define __EXTENSIONS_CCOFLEADERBOARD_H_

#include <string>
#include "CCObject.h"

using namespace std;
using namespace cocos2d;

namespace extensions {
    
    class CCOFLeaderboard : public CCObject
    {
    public:
        static CCOFLeaderboard* leaderboardWithId(const char* id,
                                                  const char* name,
                                                  bool descendingScoreOrder,
                                                  int currentUserScore,
                                                  const char* currentUserScoreDisplayText);
        
        string id;
        string name;
        int currentUserScore;
        string currentUserScoreDisplayText;
        bool descendingScoreOrder;
        
    private:
        CCOFLeaderboard(void) {}
    };
    
}

#endif // __EXTENSIONS_CCOFLEADERBOARD_H_
