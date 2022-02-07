#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <vector>
#include <algorithm>

class StringUtil
{
public:
    /** Removes any whitespace characters, be it standard space or
        TABs and so on.
        @remarks
            The user may specify wether they want to trim only the
            beginning or the end of the std::string ( the default action is
            to trim both).
    */
	static void trim(std::string& str, bool left = true, bool right = true, std::string& delims = std::string(" \t\r"));

    /** Returns a std::stringVector that contains all the substrings delimited
        by the characters in the passed <code>delims</code> argument.
        @param
            delims A list of delimiter characters to split by
        @param
            maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
            parameters is > 0, the splitting process will stop after this many splits, left to right.
    */
	static std::vector<std::string> split(std::string& str, std::string& delims = std::string("\t\n "), unsigned int maxSplits = 0);

	/** Returns a std::stringVector that contains all the substrings delimited
        by the characters in the passed <code>delims</code> argument, 
		or in the <code>doubleDelims</code> argument, which is used to include (normal) 
		delimeters in the tokenised string. For example, "strings like this".
        @param
            delims A list of delimiter characters to split by
		@param
            delims A list of double delimeters characters to tokenise by
        @param
            maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
            parameters is > 0, the splitting process will stop after this many splits, left to right.
    */
	static std::vector<std::string> tokenise(std::string& str, std::string& delims = std::string("\t\n "), std::string& doubleDelims = std::string("\""), unsigned int maxSplits = 0);

	/** Lower-cases all the characters in the string.
    */
    static void toLowerCase(std::string& str);

    /** Upper-cases all the characters in the string.
    */
    static void toUpperCase(std::string& str);


    /** Returns whether the string begins with the pattern passed in.
    @param pattern The pattern to compare with.
    @param lowerCase If true, the start of the string will be lower cased before
        comparison, pattern should also be in lower case.
    */
    static bool startsWith(std::string& str, std::string& pattern, bool lowerCase = true);

    /** Returns whether the string ends with the pattern passed in.
    @param pattern The pattern to compare with.
    @param lowerCase If true, the end of the string will be lower cased before
        comparison, pattern should also be in lower case.
    */
    static bool endsWith(std::string& str, std::string& pattern, bool lowerCase = true);

    /** Method for standardising paths - use forward slashes only, end with slash.
    */
    static std::string standardisePath(std::string &init);

    /** Method for splitting a fully qualified filename into the base name
        and path.
    @remarks
        Path is standardised as in standardisePath
    */
    static void splitFilename(std::string& qualifiedName,
        std::string& outBasename, std::string& outPath);

	/** Method for splitting a fully qualified filename into the base name,
	extension and path.
	@remarks
	Path is standardised as in standardisePath
	*/
	static void splitFullFilename(std::string& qualifiedName, 
		std::string& outBasename, std::string& outExtention, 
		std::string& outPath);

	/** Method for splitting a filename into the base name
	and extension.
	*/
	static void splitBaseFilename(std::string& fullName, 
		std::string& outBasename, std::string& outExtention);


    /** Simple pattern-matching routine allowing a wildcard pattern.
    @param str std::string to test
    @param pattern Pattern to match against; can include simple '*' wildcards
    @param caseSensitive Whether the match is case sensitive or not
    */
    static bool match(std::string& str, std::string& pattern, bool caseSensitive = true);


	/** replace all instances of a sub-string with a another sub-string.
	@param source Source string
	@param replaceWhat Sub-string to find and replace
	@param replaceWithWhat Sub-string to replace with (the new sub-string)
	@returns An updated string with the sub-string replaced
	*/
	static std::string replaceAll(std::string& source, std::string& replaceWhat, std::string& replaceWithWhat);

    /// Constant blank string, useful for returning by ref where local does not exist
    static const std::string BLANK;
};

#endif