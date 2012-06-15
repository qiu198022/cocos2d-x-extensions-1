
#include "CCOFLeaderboard.h"

namespace extensions {
    
    CCOFLeaderboard* CCOFLeaderboard::leaderboardWithId(const char* id,
                                                        const char* name,
                                                        bool descendingScoreOrder,
                                                        int currentUserScore,
                                                        const char* currentUserScoreDisplayText)
    {
        CCOFLeaderboard* board = new CCOFLeaderboard();
        board->id = id;
        board->name = name;
        board->descendingScoreOrder = descendingScoreOrder;
        board->currentUserScore = currentUserScore;
        board->currentUserScoreDisplayText = currentUserScoreDisplayText;
        board->autorelease();
        return board;
    }
    
}
