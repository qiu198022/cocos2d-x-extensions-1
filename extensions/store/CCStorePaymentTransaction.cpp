
#include "CCStorePaymentTransaction.h"

namespace extensions {
    
    CCStorePaymentTransaction*
    CCStorePaymentTransaction::transactionWithState(CCStorePaymentTransactionWrapper* transactionWapper,
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
                                                    CCStoreReceiptVerifyStatus receiptVerifyStatus)
    {
        CCStorePaymentTransaction* transaction = new CCStorePaymentTransaction();
        transaction->initWithState(transactionWapper,
                                   state,
                                   transactionId,
                                   productId,
                                   quantity,
                                   dateTime,
                                   receiptDataLength,
                                   receiptData,
                                   errorCode,
                                   errorDescription,
                                   originalTransaction,
                                   receiptVerifyMode,
                                   receiptVerifyStatus);
        transaction->autorelease();
        return transaction;
    }
    
    CCStorePaymentTransaction::~CCStorePaymentTransaction(void)
    {
        CC_SAFE_RELEASE(m_originalTransaction);
        if (m_receiptData)
        {
            free(m_receiptData);
        }
        if (m_transactionWapper)
        {
            delete m_transactionWapper;
        }
        
        CCLOG("~~ CCStorePaymentTransaction::~CCStorePaymentTransaction()");
    }
    
    bool CCStorePaymentTransaction::initWithState(CCStorePaymentTransactionWrapper* transactionWapper,
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
                                                  CCStoreReceiptVerifyStatus receiptVerifyStatus)
    {
        m_transactionWapper = transactionWapper;
        m_transactionState = state;
        m_transactionIdentifier = transactionId;
        m_productIdentifier = productId;
        m_quantity = quantity;
        m_dateTime = dateTime;
        m_receiptDataLength = receiptDataLength;
        if (receiptDataLength > 0)
        {
            m_receiptData = malloc(receiptDataLength);
            memcpy(m_receiptData, receiptData, receiptDataLength);
        }
        else
        {
            m_receiptData = NULL;
        }
        m_errorCode = errorCode;
        m_errorDescription = errorDescription ? errorDescription : "";
        m_originalTransaction = originalTransaction;
        if (m_originalTransaction)
        {
            m_originalTransaction->retain();
        }
        
        m_receiptVerifyMode = receiptVerifyMode;
        m_receiptVerifyStatus = receiptVerifyStatus;
        
        return true;
    }
    
    const CCLuaTableDict CCStorePaymentTransaction::convertToLuaTable(void)
    {
        CCLuaTableDict transaction_;
        
        transaction_["state"] = CCLuaValue::valueWithString(CCStorePaymentTransactionStateNames[m_transactionState]);
        transaction_["transactionIdentifier"] = CCLuaValue::valueWithString(m_transactionIdentifier);
        transaction_["productIdentifier"] = CCLuaValue::valueWithString(m_productIdentifier);
        transaction_["quantity"] = CCLuaValue::valueWithInt(m_quantity);
        transaction_["date"] = CCLuaValue::valueWithFloat(m_dateTime);
        transaction_["errorCode"] = CCLuaValue::valueWithInt(m_errorCode);
        transaction_["errorString"] = CCLuaValue::valueWithString(m_errorDescription);
        transaction_["receiptVerifyMode"] = CCLuaValue::valueWithInt(m_receiptVerifyMode);
        transaction_["receiptVerifyStatus"] = CCLuaValue::valueWithInt(m_receiptVerifyStatus);
        
        if (m_receiptDataLength > 0)
        {
            transaction_["receipt"] = CCLuaValue::valueWithString((const char*)(m_receiptData));
        }
        
        if (m_originalTransaction)
        {
            const CCLuaTableDict originalTransaction_ = m_originalTransaction->convertToLuaTable();
            transaction_["originalTransaction"] = CCLuaValue::valueWithCCLuaTableDict(originalTransaction_);
        }
        
        return transaction_;
    }
    
} // namespace store
