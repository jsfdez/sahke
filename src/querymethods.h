#ifndef QUERYMETHODS_H
#define QUERYMETHODS_H

#include <cstring>
#include "queries.h"

template<class T>
struct QueryMethodsBase : query_methods {
    QueryMethodsBase(T* ctx);

    T* context;
    peer_id_t peerId;
};

template<class T>
QueryMethodsBase<T>::QueryMethodsBase(T* ctx)
{
    context = ctx;
    on_answer = nullptr;
    on_error = nullptr;
    on_timeout = nullptr;
}

#endif // QUERYMETHODS_H
