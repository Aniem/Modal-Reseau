/**
 * @file counter.h
 * @brief Atomic counter management
 */

#ifndef MODAL_ATOM_COUNTER_H
#define MODAL_ATOM_COUNTER_H

#include "../mutex.h"

namespace Modal
{
    namespace atom
    {
        /**
         * @class Counter
         * @brief Atomic counter implementation
         */
        class Counter
        {
        public:
            /**
             * @brief Constructor
             * @param initial Initial value
             */
            Counter(unsigned long initial = 0);

            /**
             * @brief Get value
             * @return counter value
             */
            unsigned long get();

            /**
             * @brief Increment and get old value of the counter
             * @return value before increment
             */
            unsigned long getIncrement();

        private:
            Mutex mut;
            unsigned long cnt;

            // Disable copy
            Counter(const Counter&);
            const Counter& operator=(const Counter&);
        };
    }
}

#endif /* MODAL_ATOM_COUNTER_H */

