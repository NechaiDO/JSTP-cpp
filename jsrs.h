//
// Created by nechaido on 25.03.16.
//

#ifndef JSTP_CPP_JSTPPARSER_H
#define JSTP_CPP_JSTPPARSER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

class JSTP_parser final {

    typedef std::string string;
    typedef std::vector<JSTP_parser> array;
    typedef std::map<std::string, JSTP_parser> object;

public:

    enum Type {
        UNDEFINED, NUL, BOOL, NUMBER, STRING, ARRAY, OBJECT
    };

    JSTP_parser();                          // UNDEFINED
    JSTP_parser(std::nullptr_t);            // NUL

    JSTP_parser(double val);                // NUMBER
    JSTP_parser(bool val);                  // BOOL

    JSTP_parser(const string& val);         // STRING
    JSTP_parser(string&& val);              // STRING
    JSTP_parser(const char* value);         // STRING

    JSTP_parser(const array& values);       // ARRAY
    JSTP_parser(array&& values);            // ARRAY

    JSTP_parser(const object& values);      // OBJECT
    JSTP_parser(object&& values);           // OBJECT



    Type type() const;

    bool is_undefined() const { return  type() == UNDEFINED; };
    bool is_null() const { return  type() == NUL; };
    bool is_bool() const { return  type() == BOOL; };
    bool is_number() const { return  type() == NUMBER; };
    bool is_string() const { return  type() == STRING; };
    bool is_array() const { return  type() == ARRAY; };
    bool is_object() const { return  type() == OBJECT; };

    /**
     * Returns the enclosed value if this is a boolean, false otherwise
     */
    bool bool_value() const;

    /**
     * Returns the enclosed value if this is a number, 0 otherwise
     */
    double number_value() const;

    /**
     * Returns the enclosed value if this is a string, '' otherwise
     */
    const string& string_value() const;

    /**
     * Return the enclosed std::vector if this is an array, or an empty vector otherwise.
     */
    const array& array_items() const;
    /**
     * Return the enclosed std::map if this is an object, or an empty map otherwise.
     */
    const object& object_items() const;


    /**
     * Return a reference to arr[i] if this is an array, UNDEFINED JSTP otherwise.
     */
    const JSTP_parser& operator[](size_t i) const;

    /*
     * Return a reference to obj[key] if this is an object, UNDEFINED JSTP otherwise.
     */
    const JSTP_parser& operator[](const string &key) const;

    /**
     * Serializator
     */
    string dump() const;

    /*
     * Parser of a Record Serialization
     */
    static JSTP_parser parse(const string& in, string& err);

    bool operator== (const JSTP_parser &rhs) const;
    bool operator<  (const JSTP_parser &rhs) const;
    bool operator!= (const JSTP_parser &rhs) const;
    bool operator<= (const JSTP_parser &rhs) const;
    bool operator>  (const JSTP_parser &rhs) const;
    bool operator>= (const JSTP_parser &rhs) const;


private:

    std::shared_ptr<JS_value> value;

    /**
     * Inner class for storing values
     * Behaviour of methods is similar to JSTP_parser one`s
     */
    class JS_value {
        friend class JSTP_parser;
    protected:
        virtual Type type() const = 0;

        virtual bool equals(const JS_value * other) const = 0;
        virtual bool less(const JS_value * other) const = 0;

        virtual void dump(string& out) const = 0;
        virtual bool bool_value() const;
        virtual double number_value() const;
        virtual const string& string_value() const;
        virtual const array& array_items() const;
        virtual const object &object_items() const;

        virtual const JSTP_parser& operator[](size_t i) const;
        virtual const JSTP_parser& operator[](const std::string &key) const;

        virtual ~JS_value() {}
    };
};


#endif //JSTP_CPP_JSTPPARSER_H