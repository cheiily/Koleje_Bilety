//
// Created by student on 21.05.2022.
//

#ifndef KOLEJEBILETY_EXCEPTIONS_H
#define KOLEJEBILETY_EXCEPTIONS_H

#include <stdexcept>
#include <memory>

#define emptyStringMsg "One of the crucial string-type values was attempted to be set empty. Which: "
#define collectionMismatchMsg "One of the passed collections does not match the function's requirements. Which: "
#define negativeValueMsg "One of the crucial numeric values was attempted to be set negative-or-zero. Which: "
#define nullPointerMsg "One of the crucial const pointer members was attempted to be set null. Which: "
#define unavailableMsg " unavailable "
#define quote(x) #x


/**
 * Base of all the Library-defined exceptions. Defines the behavior of all inheriting exception classes, while they only override the default message format. <br>
 * The message argument can be customized by the user with any of the following subclasses, however the other arguments will still be appended in a defined format.
 */
template <typename CStrMacro = const char *>
class GenericException : public std::logic_error {
public:
    explicit GenericException(const std::string & className, const std::string & fieldName, CStrMacro message)
            : logic_error(std::string(message) + (className.empty() ? unavailableMsg : className) + " - " + (fieldName.empty() ? unavailableMsg : fieldName))
    {}
};


class EmptyStringException : public GenericException<> {
public:
    explicit EmptyStringException(const std::string & className, const std::string & fieldName, const char * message = emptyStringMsg)
        : GenericException(className, fieldName, message) {}
};


class CollectionMismatchException : public GenericException<> {
public:
    explicit CollectionMismatchException(const std:: string & className, const std::string & fieldName, const char * message = collectionMismatchMsg)
            : GenericException(className, fieldName, message) {}
};

class NegativeNumericException : public GenericException<> {
public:
    explicit NegativeNumericException(const std::string & className, const std::string & fieldName, const char * message = negativeValueMsg)
            : GenericException(className, fieldName, message) {}
};

class NullPointerException : public GenericException<> {
public:
    explicit NullPointerException(const std::string & className, const std::string & fieldName, const char * message = nullPointerMsg)
    : GenericException(className, fieldName, message) {}
};


#endif //KOLEJEBILETY_EXCEPTIONS_H
