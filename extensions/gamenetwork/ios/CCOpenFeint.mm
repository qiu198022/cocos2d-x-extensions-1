
#import "CCOpenFeint.h"
#import "CCOpenFeint_objc.h"
#import "OFAchievement.h"
#import "OFLeaderboard.h"

#include "CCOFAchievement.h"
#include "CCOFLeaderboard.h"

namespace extensions {
    
    void CCOpenFeint::postInitWithProductKey(const char* productKey, const char* secret, const char* displayName)
    {
        NSString* _productKey = [NSString stringWithUTF8String:productKey ? productKey : ""];
        NSString* _secret = [NSString stringWithUTF8String:secret ? secret : ""];
        NSString* _displayName = [NSString stringWithUTF8String:displayName ? displayName : ""];
        [[CCOpenFeint_objc sharedInstance] postInitWithProductKey:_productKey
                                                            andSecret:_secret
                                                       andDisplayName:_displayName];
    }
    
    void CCOpenFeint::showDashboard(void)
    {
        [[CCOpenFeint_objc sharedInstance] showDashboard];
    }
    
    void CCOpenFeint::showLeaderboards(void)
    {
        [[CCOpenFeint_objc sharedInstance] showLeaderboards];
    }
    
    void CCOpenFeint::showLeaderboards(const char* leaderboardId)
    {
        if (!leaderboardId) leaderboardId = "";
        [[CCOpenFeint_objc sharedInstance] showLeaderboards:[NSString stringWithUTF8String:leaderboardId]];
    }
    
    void CCOpenFeint::showAchievements(void)
    {
        [[CCOpenFeint_objc sharedInstance] showAchievements];
    }
    
    void CCOpenFeint::showChallenges(void)
    {
        [[CCOpenFeint_objc sharedInstance] showChallenges];
    }
    
    void CCOpenFeint::showFriends(void)
    {
        [[CCOpenFeint_objc sharedInstance] showFriends];
    }
    
    void CCOpenFeint::showPlaying(void)
    {
        [[CCOpenFeint_objc sharedInstance] showPlaying];
    }
    
    CCArray* CCOpenFeint::getAchievements(void)
    {
        NSArray* achievements = [[CCOpenFeint_objc sharedInstance] getAchievements];
        CCArray* arr = CCArray::arrayWithCapacity([achievements count]);
        
        for (int i = 0; i < [achievements count]; ++i)
        {
            OFAchievement* ach = [achievements objectAtIndex:i];
            const char* achievementId = [ach.resourceId cStringUsingEncoding:NSUTF8StringEncoding];
            const char* title = [ach.title cStringUsingEncoding:NSUTF8StringEncoding];
            const char* description = [ach.description cStringUsingEncoding:NSUTF8StringEncoding];
            const char* iconUrl = [ach.iconUrl cStringUsingEncoding:NSUTF8StringEncoding];
            CCOFAchievement* ccach = CCOFAchievement::achievementWithId(achievementId,
                                                                        title,
                                                                        description,
                                                                        iconUrl,
                                                                        ach.isUnlocked,
                                                                        ach.isSecret);
            arr->addObject(ccach);
        }
        
        return arr;
    }
    
    LUA_TABLE CCOpenFeint::getAchievementsLua(void)
    {
        CCArray* achievements = getAchievements();
        CCLuaTableArray achievements_;
        
        for (int i = 0; i < achievements->count(); ++i)
        {
            CCOFAchievement* ach = static_cast<CCOFAchievement*>(achievements->objectAtIndex(i));
            CCLuaTableDict ach_;
            
            ach_["id"] = CCLuaValue::valueWithString(ach->id);
            ach_["title"] = CCLuaValue::valueWithString(ach->title);
            ach_["description"] = CCLuaValue::valueWithString(ach->description);
            ach_["iconUrl"] = CCLuaValue::valueWithString(ach->iconUrl);
            ach_["isUnlocked"] = CCLuaValue::valueWithBoolean(ach->isUnlocked);
            ach_["isSecret"] = CCLuaValue::valueWithBoolean(ach->isSecret);
            
            achievements_.push_back(CCLuaValue::valueWithCCLuaTableDict(ach_));
        }
        
        CCScriptEngineProtocol* engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        engine->cleanLuaStack();
        engine->pushCCLuaTableArrayToLuaStack(&achievements_);
        return 1;
    }
    
    void CCOpenFeint::unlockAchievement(const char* achievementId)
    {
        if (!achievementId) achievementId = "";
        [[CCOpenFeint_objc sharedInstance] unlockAchievement:[NSString stringWithUTF8String:achievementId]];
    }
    
    CCArray* CCOpenFeint::getLeaderboards(void)
    {
        NSArray* leaderboards = [[CCOpenFeint_objc sharedInstance] getLeaderboards];
        CCArray* arr = CCArray::arrayWithCapacity([leaderboards count]);
        
        for (int i = 0; i < [leaderboards count]; ++i)
        {
            OFLeaderboard* board = [leaderboards objectAtIndex:i];
            const char* leaderboardId = [board.leaderboardId cStringUsingEncoding:NSUTF8StringEncoding];
            const char* name = [board.name cStringUsingEncoding:NSUTF8StringEncoding];
            const char* currentUserScoreDisplayText = [board.currentUserScore.displayText
                                                       cStringUsingEncoding:NSUTF8StringEncoding];
            CCOFLeaderboard* ccboard = CCOFLeaderboard::leaderboardWithId(leaderboardId,
                                                                          name,
                                                                          board.descendingScoreOrder,
                                                                          board.currentUserScore.score,
                                                                          currentUserScoreDisplayText);
            arr->addObject(ccboard);
        }
        
        return arr;
    }
    
    LUA_TABLE CCOpenFeint::getLeaderboardsLua(void)
    {
        CCArray* leaderboards = getLeaderboards();
        CCLuaTableArray leaderboards_;
        
        for (int i = 0; i < leaderboards->count(); ++i)
        {
            CCOFLeaderboard* board = static_cast<CCOFLeaderboard*>(leaderboards->objectAtIndex(i));
            CCLuaTableDict board_;
            
            board_["id"] = CCLuaValue::valueWithString(board->id);
            board_["name"] = CCLuaValue::valueWithString(board->name);
            board_["descendingScoreOrder"] = CCLuaValue::valueWithBoolean(board->descendingScoreOrder);
            board_["currentUserScore"] = CCLuaValue::valueWithInt(board->currentUserScore);
            board_["currentUserScoreDisplayText"] = CCLuaValue::valueWithString(board->currentUserScoreDisplayText);
            
            leaderboards_.push_back(CCLuaValue::valueWithCCLuaTableDict(board_));
        }
        
        CCScriptEngineProtocol* engine = CCScriptEngineManager::sharedManager()->getScriptEngine();
        engine->cleanLuaStack();
        engine->pushCCLuaTableArrayToLuaStack(&leaderboards_);
        return 1;
    }
    
    void CCOpenFeint::setHighScore(const char* leaderboardId, int score, const char* displayText)
    {
        if (!leaderboardId) leaderboardId = "";
        if (!displayText) displayText = "";
        [[CCOpenFeint_objc sharedInstance] setHighScore:[NSString stringWithUTF8String:leaderboardId]
                                                   andScore:[NSNumber numberWithInt:score]
                                             andDisplayText:[NSString stringWithUTF8String:displayText]];
    }
    
}
