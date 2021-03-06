/**
 * @file tls-pointer-detail.h
 * @brief TLS pointer implementation
 *
 * You should never include this file directly
 */
#ifndef MODAL_TLS_POINTER_DETAIL_H
#define MODAL_TLS_POINTER_DETAIL_H

#include "tls-pointer.h"


namespace Modal
{

    template<typename T> void TLSPointer<T>::_default_destructor(T* object) {
        delete object;
    }

    template<typename T> TLSPointer<T>::TLSPointer(void (*destructor)(T*))
    : destructor(destructor), constructor(NULL) {
        int key_create_status = pthread_key_create(&key,
                reinterpret_cast<void_destructor_func*> (this->destructor));
        MODAL_ASSERT_NO_LOG(key_create_status == 0);
    }

    template<typename T> TLSPointer<T>::TLSPointer(T* (*constructor_)(), void (*destructor_)(T*))
    : destructor(destructor_), constructor(constructor_) {
        int key_create_status = pthread_key_create(&key,
                reinterpret_cast<void_destructor_func*> (this->destructor));
        MODAL_ASSERT_NO_LOG(key_create_status == 0);
    }

    template<typename T> TLSPointer<T>::~TLSPointer() {
        pthread_key_delete(key);
    }

    template<typename T> T* TLSPointer<T>::get() {
        T* result = static_cast<T*> (pthread_getspecific(key));

        if (result == NULL && this->constructor != NULL) {
            result = this->constructor();
            pthread_setspecific(key, static_cast<void *> (result));
        }

        return result;
    }

    template<typename T> void TLSPointer<T>::reset(T* new_value) {
        T* current = static_cast<T*> (pthread_getspecific(key));

        if (new_value != current) {
            // Destroy old value
            if (current != NULL && this->destructor != NULL)
                this->destructor(current);
            pthread_setspecific(key, static_cast<void *> (new_value));
        }
    }

    template<typename T> T* TLSPointer<T>::release() {
        T* temp = static_cast<T*> (pthread_getspecific(key));
        pthread_setspecific(key, NULL);
        return temp;
    }
}

#endif /* MODAL_TLS_POINTER_DETAIL_H */
