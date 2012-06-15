
#ifndef  __EXTENSIONS_CCSTORE_H_
#define  __EXTENSIONS_CCSTORE_H_

#include <map>
#include "CCObject.h"
#include "CCSet.h"
#include "CCScriptSupport.h"
#include "CCStoreProduct.h"
#include "CCStorePaymentTransaction.h"
#include "CCStoreTransactionObserver.h"
#include "CCStoreProductsRequestDelegate.h"

using namespace std;
using namespace cocos2d;

namespace extensions {
    
    typedef bool CCStoreIsSandbox;
    
    typedef map<const string, CCStorePaymentTransaction*>   CCStorePaymentTransactions;
    typedef CCStorePaymentTransactions::iterator            CCStorePaymentTransactionsIterator;
    
    class CCStore : public CCStoreTransactionObserver, public CCStoreProductsRequestDelegate
    {
    public:
        static CCStore* sharedStore(void);
        static void purgeSharedStore(void);
        
        ~CCStore(void);
        
        // 初始化
        void postInitWithTransactionObserver(CCStoreTransactionObserver* observer);
        
        // 初始化 Lua
        void postInitWithTransactionListenerLua(LUA_FUNCTION listener);
        
        // 确认当前是否可以进行交易
        bool canMakePurchases(void);
        
        // 载入指定产品的信息
        void loadProducts(CCSet* productsId, CCStoreProductsRequestDelegate* delegate);
        
        // 载入指定产品的信息 Lua
        void loadProductsLua(LUA_TABLE __LUA_TABLE__, LUA_FUNCTION callback);
        
        // 取消载入产品信息的操作
        void cancelLoadProducts(void);
        
        /** @brief 确定指定的产品是否已经载入
         
         @param productId 要检查的产品 ID
         */
        bool isProductLoaded(const char* productId);
        
        /** @brief 购买指定的产品
        
         @param productId 要购买产品的 ID
         
         指定 ID 的产品信息必须之前成功调用 loadProducts() 载入。如果指定的产品尚未载入，则返回 false。
         */
        bool purchase(const char* productId);
        
        /** @brief 结束交易 */
        void finishTransaction(CCStorePaymentTransaction *transaction);
        void finishTransactionLua(const char* transactionIdentifier);

        // 确定当前的收据验证模式
        CCStoreReceiptVerifyMode getReceiptVerifyMode(void);
        
        // 设置收据验证模式
        void setReceiptVerifyMode(CCStoreReceiptVerifyMode mode, CCStoreIsSandbox isSandbox = true);
        
        // 确定验证收据的服务器 URL
        const char* getReceiptVerifyServerUrl(void);
        
        // 设置验证收据的服务器 URL
        void setReceiptVerifyServerUrl(const char* url);
        
#pragma mark -
#pragma mark delegates
        
        virtual void transactionCompleted(CCStorePaymentTransaction* transaction);
        virtual void transactionFailed(CCStorePaymentTransaction* transaction);
        virtual void transactionRestored(CCStorePaymentTransaction* transaction);
        
        virtual void requestProductsCompleted(CCArray* products, CCArray* invalidProductsId = NULL);
        virtual void requestProductsFailed(int errorCode, const char* errorString);
        
    private:
        CCStore(void)
        : m_observer(NULL)
        , m_listener(0)
        , m_loadProductsCallback(0)
        , m_isLoadProductsLuaNotCompleted(false)
        {
        }
        bool init(void);
        
        static CCStore*             s_sharedStore;
        CCStoreTransactionObserver* m_observer;
        LUA_FUNCTION                m_listener;
        LUA_FUNCTION                m_loadProductsCallback;
        bool                        m_isLoadProductsLuaNotCompleted;
        CCStorePaymentTransactions  m_transactions;
                
        void passCCStorePaymentTransactionToLuaListener(CCStorePaymentTransaction* transaction);
    };
    
} //namespace store

#endif // __EXTENSIONS_CCSTORE_H_
