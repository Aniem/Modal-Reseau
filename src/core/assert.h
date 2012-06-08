/**
 * @file assert.h
 * @brief Assert() macro implementation with Modal logger
 *
 * You need to include log.h and exception.h to use this file
 */
#ifndef MODAL_ASSERT_H
#define MODAL_ASSERT_H

#include <iostream>

/**
 * @def MODAL_ASSERT(condition)
 * An assert using Modal' logging system.
 */
#define MODAL_ASSERT(condition)\
{\
    if(!(bool)(condition)){\
        Modal::log::fatal << "\n[ASSERT] " #condition "\n";\
        Modal::log::fatal << "    - Function: " << __FUNCTION__ << " \n";\
        Modal::log::fatal << "    - File: " << __FILE__ << " : " << __LINE__ << Modal::log::endl;\
        throw Modal::FailException("assert", #condition);\
    }\
}

/**
 * @def MODAL_ASSERT_WARN(condition)
 * An assert using Modal' logging system. It does not throw an exception thus it only warns about the error.
 */
#define MODAL_ASSERT_WARN(condition)\
{\
    if(!(bool)(condition)){\
        Modal::log::fatal << "\n[ASSERT] " #condition "\n";\
        Modal::log::fatal << "    - Function: " << __FUNCTION__ << " \n";\
        Modal::log::fatal << "    - File: " << __FILE__ << " : " << __LINE__ << Modal::log::endl;\
    }\
}

/**
 * @def MODAL_ASSERT_NO_LOG(condition)
 * An assert that does not use Modal' logging system (for use in the logging system).
 */
#define MODAL_ASSERT_NO_LOG(condition)\
{\
    if(!(bool)(condition)){\
        std::cerr << "[ASSERT] " #condition "\n";\
        std::cerr << "    - Function: " << __FUNCTION__ << " \n";\
        std::cerr << "    - File: " << __FILE__ << " : " << __LINE__ << std::endl;\
        throw Modal::FailException("assert", #condition);\
    }\
}

#endif /* MODAL_ASSERT_H */
