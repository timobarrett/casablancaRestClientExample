# casablancaRestClientExample
Example of using the Microsoft Rest Casablanca library on Linux.  Examples of platforms other than Microsoft are lacking.
Plan to include eclipse CDT information for this project as it becomes defined.

Configuration tips for the use of eclipse in Java:
tool settings (c/c++ Build/settings)
        make sure that -std=c++11 is in the options listed - setting Language
                standard is not enough on the Dialect options
        Set the Includes - include path tp point to the casablancea includes dir
        set the Casablanca Libraries path to the Binaries directory built
        add cpprest and common_utilities to the libraries list
Paths and Symbols (c/c++ General settings)
        GNU C++ make sure the include directory for casablanca is defined
        Libraries - make sure the cpprest and common_utilites are defined
        Library Path - make sure that the path to the Binaries built are defined
Provides tab (preprocessor Include paths, macros etc.)
        make sure the CDT GCC Built-in Compiler settings contain -std=c++11

