#ifndef __ISTRING_H__
#define __ISTRING_H__
#include "interfaces/IBase.h"

__NAMESPACE_GUARD_BEGIN(ZDC)
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)
__EXTERN_C_GUARD_BEGIN

FORWARD_DECLARE_INTERFACE(IAsciiString);
FORWARD_DECLARE_INTERFACE(IUtf8String);
FORWARD_DECLARE_INTERFACE(IUtf16String);
FORWARD_DECLARE_INTERFACE(IUtf32String);

typedef char           char_ascii_t;
typedef unsigned char  char_utf8_t;
typedef unsigned short char_utf16_t;
typedef unsigned int   char_utf32_t;

/**
 * @brief An ambiguous string, its format is unknown until casted using TryCastTo to one of its substrings; or
 * when using the provided ToAscii, ToUtf8, ToUtf16, or ToUtf32 functions.
 */
DECLARE_INTERFACE IString
INTERFACE_INHERITS_FROM(IBase)
{
public:
    DECLARE_INTERFACE_VFTABLE_(IBase)
    /**
     * @note Use Size function to determine the number of bytes used by this string.
     * @returns The length of the string in terms of characters, excluding the null terminator.
    */
    DECLARE_INTERFACE_VFUNCTION(Length, size_t)(IThis) PURE;
    /**
     * @note Use Length function to determine the number of characters used by this string, character size is determined by which string interface we are.
     * @returns The number of bytes used by the string, excluding the null terminator.
     */
    DECLARE_INTERFACE_VFUNCTION(Size, size_t)(IThis) PURE;
    /**
     * @returns The capacity of the buffer, in terms of bytes.
     */
    DECLARE_INTERFACE_VFUNCTION(Capacity, size_t)(IThis) PURE;
    /**
     * @brief Clears this string interface, turning it into an empty string.
     */
    DECLARE_INTERFACE_VFUNCTION(Clear,void)(IThis) PURE;
    /**
     * @brief Creates a substring out of this string's content's.
     * @param nOffset The starting offset at which we will begin the substring, must be less than Size.
     * @param nLength The length of the string to copy, anything above Size will result in all characters from nOffset to string end being copied.
     * @param ppString A pointer to a IString interface pointer that will receive the substring, must convert from there.
     * @returns True if the substring was successfully created and stored in ppString, otherwise False. 
     */
    DECLARE_INTERFACE_VFUNCTION(Substring,bool_t)(IThis_ size_t nOffset, size_t nLength, IString** ppString);
    /**
     * @brief Converts, or references, the string into an Ascii compatible format.
     * @note This function should only be used if, and only if, the caller cannot support UTF-8; since these two formats are so similar it doesn't make sense to strip UTF-8 characters unless its unsupported.
     * @note If this interface already represents an Ascii compatible formatted string then we simply set ppString to a reference of this interface.
     * @param ppString A pointer to an IString pointer that will be populated with the converted string.
     * @returns True if the conversion, or reference, was successfull; otherwise false.
    */
    DECLARE_INTERFACE_VFUNCTION(ToAscii, bool)(IThis_ IAsciiString** ppString) PURE;
    /**
     * @brief Converts, or references, the string into a UTF-8 compatible format.
     * @note If this interface already represents an UTF-8 compatible formatted string then we simply set ppString to a reference of this interface.
     * @param ppString A pointer to an IString pointer that will be populated with the converted string.
     * @returns True if the conversion, or reference, was successfull; otherwise false.
    */
    DECLARE_INTERFACE_VFUNCTION(ToUtf8, bool)(IThis_ IUtf8String** ppString) PURE;
    /**
     * @brief Converts, or references, the string into a UTF-16 compatible format.
     * @note If this interface already represents an UTF-16 compatible formatted string then we simply set ppString to a reference of this interface.
     * @param ppString A pointer to an IString pointer that will be populated with the converted string.
     * @returns True if the conversion, or reference, was successfull; otherwise false.
    */
    DECLARE_INTERFACE_VFUNCTION(ToUtf16, bool)(IThis_ IUtf16String** ppString) PURE;
    /**
     * @brief Converts, or references, the string into a UTF-32 compatible format.
     * @note If this interface already represents an UTF-32 compatible formatted string then we simply set ppString to a reference of this interface.
     * @param ppString A pointer to an IString pointer that will be populated with the converted string.
     * @returns True if the conversion, or reference, was successfull; otherwise false.
    */
    DECLARE_INTERFACE_VFUNCTION(ToUtf32, bool)(IThis_ IUtf32String** ppString) PURE;
    DELCARE_INTERFACE_VFTABLE_END
};

DECLARE_INTERFACE IAsciiString
INTERFACE_INHERITS_FROM(IString)
{
public:
    DECLARE_INTERFACE_VFTABLE_(IString)
    /**
     * @note Doesn't support UTF-8 strings, any non-ascii compliant characters will be stripped out.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @param strValue The desired string value to be used.
     * @returns True if the string value was set to the given string value, otherwise False.
     */
    DECLARE_INTERFACE_VFUNCTION(Set, bool)(IThis_ const char_ascii_t* strValue) PURE;
    /**
     * @returns The string value inside this string, otherwise nullptr for empty strings.
     */
    DECLARE_INTERFACE_VFUNCTION(Get, const char_ascii_t*)(IThis) PURE;
    /**
     * @brief Prepends a character to the string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be prepended to the string.
     * @returns True if the character was successfully prepended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(PrependChar, bool)(IThis_ char_ascii_t cValue) PURE;
    /**
     * @brief Inserts a character into the string at a given offset.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be inserted into the string.
     * @param nOffset The offset at which the character will be inserted, if higher than Size then the character will just be appended.
     * @returns True if the character was successfully inserted, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(InsertChar, bool)(IThis_ char_ascii_t cValue, size_t nOffset) PURE;
    /**
     * @brief Appends a character to the string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be appended to the string.
     * @returns True if the character was successfully appended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(AppendChar, bool)(IThis_ char_ascii_t cValue) PURE;
    /**
     * @brief Prepends a string to this string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The string to be prepended to this string.
     * @returns True if the string was successfully prepended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(PrependString, bool)(IThis_ const char_ascii_t* strValue) PURE;
    /**
     * @brief Inserts a string into the string at a given offset.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The substring to be inserted into the string.
     * @param nOffset The offset at which the string will be inserted, if higher than Size then the string will just be appended.
     * @returns True if the string was successfully inserted, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(InsertString, bool)(IThis_ const char_ascii_t* strValue, size_t nOffset) PURE;
    /**
     * @brief Appends a string to this string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The string to be appended to this string.
     * @returns True if the string was successfully appended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(AppendString, bool)(IThis_ const char_ascii_t* strValue) PURE;
    DELCARE_INTERFACE_VFTABLE_END
};

DECLARE_INTERFACE IUtf8String
INTERFACE_INHERITS_FROM(IString)
{
public:
    DECLARE_INTERFACE_VFTABLE_(IString)
    /**
     * @note Doesn't support UTF-8 strings, any non-ascii compliant characters will be stripped out.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @param strValue The desired string value to be used.
     * @returns True if the string value was set to the given string value, otherwise False.
     */
    DECLARE_INTERFACE_VFUNCTION(Set, bool)(IThis_ const char_utf8_t* strValue) PURE;
    /**
     * @returns The string value inside this string, otherwise nullptr for empty strings.
     */
    DECLARE_INTERFACE_VFUNCTION(Get, const char_utf8_t*)(IThis) PURE;
    /**
     * @brief Prepends a character to the string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be prepended to the string.
     * @returns True if the character was successfully prepended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(PrependChar, bool)(IThis_ char_utf8_t cValue) PURE;
    /**
     * @brief Inserts a character into the string at a given offset.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be inserted into the string.
     * @param nOffset The offset at which the character will be inserted, if higher than Size then the character will just be appended.
     * @returns True if the character was successfully inserted, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(InsertChar, bool)(IThis_ char_utf8_t cValue, size_t nOffset) PURE;
    /**
     * @brief Appends a character to the string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be appended to the string.
     * @returns True if the character was successfully appended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(AppendChar, bool)(IThis_ char_utf8_t cValue) PURE;
    /**
     * @brief Prepends a string to this string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The string to be prepended to this string.
     * @returns True if the string was successfully prepended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(PrependString, bool)(IThis_ const char_utf8_t* strValue) PURE;
    /**
     * @brief Inserts a string into the string at a given offset.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The substring to be inserted into the string.
     * @param nOffset The offset at which the string will be inserted, if higher than Size then the string will just be appended.
     * @returns True if the string was successfully inserted, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(InsertString, bool)(IThis_ const char_utf8_t* strValue, size_t nOffset) PURE;
    /**
     * @brief Appends a string to this string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The string to be appended to this string.
     * @returns True if the string was successfully appended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(AppendString, bool)(IThis_ const char_utf8_t* strValue) PURE;
    DELCARE_INTERFACE_VFTABLE_END
};

DECLARE_INTERFACE IUtf16String
INTERFACE_INHERITS_FROM(IString)
{
public:
    DECLARE_INTERFACE_VFTABLE_(IString)
    /**
     * @note Doesn't support UTF-8 strings, any non-ascii compliant characters will be stripped out.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @param strValue The desired string value to be used.
     * @returns True if the string value was set to the given string value, otherwise False.
     */
    DECLARE_INTERFACE_VFUNCTION(Set, bool)(IThis_ const char_utf16_t* strValue) PURE;
    /**
     * @returns The string value inside this string, otherwise nullptr for empty strings.
     */
    DECLARE_INTERFACE_VFUNCTION(Get, const char_utf16_t*)(IThis) PURE;
    /**
     * @brief Prepends a character to the string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be prepended to the string.
     * @returns True if the character was successfully prepended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(PrependChar, bool)(IThis_ char_utf16_t cValue) PURE;
    /**
     * @brief Inserts a character into the string at a given offset.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be inserted into the string.
     * @param nOffset The offset at which the character will be inserted, if higher than Size then the character will just be appended.
     * @returns True if the character was successfully inserted, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(InsertChar, bool)(IThis_ char_utf16_t cValue, size_t nOffset) PURE;
    /**
     * @brief Appends a character to the string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be appended to the string.
     * @returns True if the character was successfully appended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(AppendChar, bool)(IThis_ char_utf16_t cValue) PURE;
    /**
     * @brief Prepends a string to this string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The string to be prepended to this string.
     * @returns True if the string was successfully prepended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(PrependString, bool)(IThis_ const char_utf16_t* strValue) PURE;
    /**
     * @brief Inserts a string into the string at a given offset.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The substring to be inserted into the string.
     * @param nOffset The offset at which the string will be inserted, if higher than Size then the string will just be appended.
     * @returns True if the string was successfully inserted, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(InsertString, bool)(IThis_ const char_utf16_t* strValue, size_t nOffset) PURE;
    /**
     * @brief Appends a string to this string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The string to be appended to this string.
     * @returns True if the string was successfully appended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(AppendString, bool)(IThis_ const char_utf16_t* strValue) PURE;
    DELCARE_INTERFACE_VFTABLE_END
};

DECLARE_INTERFACE IUtf32String
INTERFACE_INHERITS_FROM(IString)
{
public:
    DECLARE_INTERFACE_VFTABLE_(IString)
    /**
     * @note Doesn't support UTF-8 strings, any non-ascii compliant characters will be stripped out.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @param strValue The desired string value to be used.
     * @returns True if the string value was set to the given string value, otherwise False.
     */
    DECLARE_INTERFACE_VFUNCTION(Set, bool)(IThis_ const char_utf32_t* strValue) PURE;
    /**
     * @returns The string value inside this string, otherwise nullptr for empty strings.
     */
    DECLARE_INTERFACE_VFUNCTION(Get, const char_utf32_t*)(IThis) PURE;
    /**
     * @brief Prepends a character to the string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be prepended to the string.
     * @returns True if the character was successfully prepended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(PrependChar, bool)(IThis_ char_utf32_t cValue) PURE;
    /**
     * @brief Inserts a character into the string at a given offset.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be inserted into the string.
     * @param nOffset The offset at which the character will be inserted, if higher than Size then the character will just be appended.
     * @returns True if the character was successfully inserted, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(InsertChar, bool)(IThis_ char_utf32_t cValue, size_t nOffset) PURE;
    /**
     * @brief Appends a character to the string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param cValue The character to be appended to the string.
     * @returns True if the character was successfully appended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(AppendChar, bool)(IThis_ char_utf32_t cValue) PURE;
    /**
     * @brief Prepends a string to this string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The string to be prepended to this string.
     * @returns True if the string was successfully prepended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(PrependString, bool)(IThis_ const char_utf32_t* strValue) PURE;
    /**
     * @brief Inserts a string into the string at a given offset.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The substring to be inserted into the string.
     * @param nOffset The offset at which the string will be inserted, if higher than Size then the string will just be appended.
     * @returns True if the string was successfully inserted, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(InsertString, bool)(IThis_ const char_utf32_t* strValue, size_t nOffset) PURE;
    /**
     * @brief Appends a string to this string.
     * @note String will not support characters of value <32 excluding: 0x10 (16; aka new-line character).
     * @note Unsupported characters will be stripped out of string.
     * @param strValue The string to be appended to this string.
     * @returns True if the string was successfully appended, otherwise false; may fail due to a memory allocation error.
     */
    DECLARE_INTERFACE_VFUNCTION(AppendString, bool)(IThis_ const char_utf32_t* strValue) PURE;
    DELCARE_INTERFACE_VFTABLE_END
};

__EXTERN_C_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
#endif//__ISTRING_H__ GUARD