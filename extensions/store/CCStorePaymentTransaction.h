
#ifndef __EXTENSIONS_CCSTORE_PAYMENT_TRANSACTION_H_
#define __EXTENSIONS_CCSTORE_PAYMENT_TRANSACTION_H_

#include <string>
#include "CCObject.h"
#include "CCStorePaymentTransactionWrapper.h"
#include "CCScriptSupport.h"

using namespace std;
using namespace cocos2d;

namespace extensions {
    
    typedef enum {
        CCStoreReceiptVerifyModeNone = 0,
        CCStoreReceiptVerifyModeDevice = 1,
        CCStoreReceiptVerifyModeServer
    } CCStoreReceiptVerifyMode;
    
    static const int CCStoreReceiptVerifyStatusUnknownError = -5;
    static const int CCStoreReceiptVerifyStatusInvalidReceipt = -4;
    static const int CCStoreReceiptVerifyStatusRequestFailed = -3;
    static const int CCStoreReceiptVerifyStatusInvalidResult = -2;
    static const int CCStoreReceiptVerifyStatusNone = -1;
    static const int CCStoreReceiptVerifyStatusOK = 0;
    typedef int CCStoreReceiptVerifyStatus;
    
    typedef enum {
        CCStorePaymentTransactionStateNull = 0,
        CCStorePaymentTransactionStatePurchasing = 1,
        CCStorePaymentTransactionStatePurchased,
        CCStorePaymentTransactionStateFailed,
        CCStorePaymentTransactionStateRestored,
        CCStorePaymentTransactionStateCancelled,
    } CCStorePaymentTransactionState;    
    
    static const char* const CCStorePaymentTransactionStateNames[] = {
        "unknown",
        "purchasing",
        "purchased",
        "failed",
        "restored",
        "cancelled"
    };
    
    class CCStorePaymentTransaction : public CCObject
    {
    public:
        static CCStorePaymentTransaction* transactionWithState(CCStorePaymentTransactionWrapper* transactionWapper,
                                                               CCStorePaymentTransactionState state,
                                                               const char* transactionId,
                                                               const char* productId,
                                                               int quantity,
                                                               double dateTime,
                                                               int receiptDataLength,
                                                               const void* receiptData,
                                                               int errorCode,
                                                               const char* errorDescription,
                                                               CCStorePaymentTransaction* originalTransaction,
                                                               CCStoreReceiptVerifyMode receiptVerifyMode,
                                                               CCStoreReceiptVerifyStatus receiptVerifyStatus);
        ~CCStorePaymentTransaction(void);
        
        CCStorePaymentTransactionWrapper* getTransactionWrapper(void)
        {
            return m_transactionWapper;
        }
        
        CCStorePaymentTransactionState getTransactionState(void)
        {
            return m_transactionState;
        }
        
        const string& getTransactionIdentifier(void)
        {
            return m_transactionIdentifier;
        }
        
        const string& getProductIdentifier(void)
        {
            return m_productIdentifier;
        }
        
        int getQuantity(void)
        {
            return m_quantity;
        }
        
        double getDateTime(void)
        {
            return m_dateTime;
        }
        
        int getReceiptDataLength(void)
        {
            return m_receiptDataLength;
        }
        
        const void* const getReceiptData(void)
        {
            return m_receiptData;
        }
        
        int getErrorCode(void)
        {
            return m_errorCode;
        }
        
        const string& getErrorDescription(void)
        {
            return m_errorDescription;
        }
        
        CCStorePaymentTransaction* getOriginalTransaction(void)
        {
            return m_originalTransaction;
        }
        
        CCStoreReceiptVerifyMode getReceiptVerifyMode(void)
        {
            return m_receiptVerifyMode;
        }
        
        int getReceiptVerifyStatus(void)
        {
            return m_receiptVerifyStatus;
        }
        
        const CCLuaTableDict convertToLuaTable(void);
        
    private:
        CCStorePaymentTransaction(void) {}
        
        bool initWithState(CCStorePaymentTransactionWrapper *transactionWapper,
                           CCStorePaymentTransactionState state,
                           const char* transactionId,
                           const char* productId,
                           int quantity,
                           double dateTime,
                           int receiptDataLength,
                           const void* receiptData,
                           int errorCode,
                           const char* errorDescription,
                           CCStorePaymentTransaction* originalTransaction,
                           CCStoreReceiptVerifyMode receiptVerifyMode,
                           CCStoreReceiptVerifyStatus receiptVerifyStatus);
        
        CCStorePaymentTransactionWrapper*   m_transactionWapper;
        CCStorePaymentTransactionState      m_transactionState;
        string                              m_transactionIdentifier;
        string                              m_productIdentifier;
        int                                 m_quantity;
        double                              m_dateTime;
        int                                 m_receiptDataLength;
        void*                               m_receiptData;
        int                                 m_errorCode;
        string                              m_errorDescription;
        CCStorePaymentTransaction*          m_originalTransaction;
        CCStoreReceiptVerifyMode            m_receiptVerifyMode;
        CCStoreReceiptVerifyStatus          m_receiptVerifyStatus;
    };
    
} // namespace store

#endif // __EXTENSIONS_CCSTORE_PAYMENT_TRANSACTION_H_
