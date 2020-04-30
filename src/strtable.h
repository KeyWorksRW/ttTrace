// If you use the _tt() macro (see ttTR.h in ttLib) then it will load a string resource when compiled for Windows. If compiled with
// wxWidgets on a non-Windows platform, it will load the translated string produced by the xgettext system that wxWidgets supports.

// Note: Windows saves strings in consecutive blocks of 16, so it is useful to keep id numbers consecutive.

#ifdef _WIN32
// #if 0  // comment out above and uncomment this to test non-Windows builds on a Windows platform

    #define IDS_FILE_MAPPING_ERROR 1024  // "Unable to create file mapping memory for messages"
    #define IDS_FILE_SAVED         1025  // "Contents saved to "
    #define IDS_DISPLAY_HELP_MSG 1026  // "display this help message"

#else

constexpr auto IDS_FILE_MAPPING_ERROR = "Unable to create file mapping memory for messages";
constexpr auto IDS_FILE_SAVED = "Contents saved to ";
constexpr auto IDS_DISPLAY_HELP_MSG = "display this help message";

#endif
