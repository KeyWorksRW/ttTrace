// If you use the _tt() macro (see ttTR.h in ttLib) then it will load a string resource when compiled for Windows. If compiled with
// wxWidgets on a non-Windows platform, it will load the translated string produced by the xgettext system that wxWidgets supports.

// Note: Windows saves strings in consecutive blocks of 16, so it is useful to keep id numbers consecutive.

#ifdef _WIN32
// #if 0  // comment out above and uncomment this to test non-Windows builds on a Windows platform

    #define IDS_OOM                512  // ""There is not enough memory available for this task."
    #define IDS_CANNOT_OPEN        513  // "Cannot open %ks"
    #define IDS_INTERNAL_ERROR     514  // "An internal error has occurred."
    #define IDS_FILE_MAPPING_ERROR 515  // "Unable to create file mapping memory for messages"
    #define IDS_WRITE_ERROR        516  // "An error occurred while writing to \042%s\042."
    #define IDS_FILE_SAVED         517  // "Contents saved to "

#else

constexpr auto IDS_OOM = "There is not enough memory available for this task.\nQuit one or more applications to increase available "
                         "constexpr auto memory, and then try again.";
constexpr auto IDS_CANNOT_OPEN = "Cannot open %ks";
constexpr auto IDS_INTERNAL_ERROR = "An internal error has occurred.";
constexpr auto IDS_FILE_MAPPING_ERROR = "Unable to create file mapping memory for messages";
constexpr auto IDS_WRITE_ERROR = "An error occurred while writing to \042%s\042.";
constexpr auto IDS_FILE_SAVED = "Contents saved to ";

#endif
