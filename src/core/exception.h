/**
 * @file exception.h
 * @brief Modal exceptions
 */
#ifndef MODAL_EXCEPTION_H
#define MODAL_EXCEPTION_H

#include <string>

namespace Modal
{
    /**
     * @class Exception
     * @brief Modal raw exception
     */
    class Exception
    {
    public:
        /**
         * @brief Build an exception
         * @param type
         * @param module
         * @param message
         */
        Exception(const char *type, const char *module, const char *message);

        /**
         * @brief Append text to the message
         * @param txt text to append
         */
        void append(const std::string& txt);

        /**
         * @brief Print an exception
         * @param os output stream
         * @param e
         */
        friend std::ostream& operator<<(std::ostream& os, const Exception& e);

        /**
         * @brief Get message
         */
        const std::string& getMessage() const;

    protected:
        /**
         * @brief Exception type
         */
        std::string type;

        /**
         * @brief Module which throws the exception
         */
        std::string module;

        /**
         * @brief Exception text
         */
        std::string message;
    };
    /**
     * @class FailException
     * @brief Modal failure
     */
    class FailException : public Exception
    {
    public:
        /**
         * @brief Build an "Modal fails" exception
         * @param module
         * @param message
         */
        FailException(const char *module, const char *message);
    };
    /**
     * @class ErrException
     * @brief View standard errors (errno and errstr) in an exception
     */
    class ErrException : public FailException
    {
    public:
        /**
         * @brief Build an standard error exception
         * @param module
         * @param fct failed function name
         */
        ErrException(const char *module, const char *fct);
    };
    /**
     * @class MinorException
     * @brief Internal Modal exception (meant to be caught at some point)
     */
    class MinorException : public Exception
    {
    public:
        /**
         * @brief Build an internal Modal exception
         * @param module
         * @param message error message to be logged
         */
        MinorException(const char *module, const char *message);
    };
    /**
     * @class ParserException
     * @brief Exception which is raised when invalid data is parsed
     */
    class ParserException : public Exception
    {
    public:
        /**
         * @brief Build a parser exception
         * @param module
         * @param message
         */
        ParserException(const char *module, const char *message);
    };
}

#endif /* MODAL_EXCEPTION_H */
