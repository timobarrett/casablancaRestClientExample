# casablancaRestClientExample
Example of using the Microsoft Rest Casablanca library on Linux.  Examples of platforms other than Microsoft are lacking.
Plan to include eclipse CDT information for this project as it becomes defined.

<h1>Configuration tips for the use of eclipse CDT on linux:</h1>

<h2>tool settings (c/c++ Build/settings)</h2>
        make sure that -std=c++11 is in the options listed - setting Language
                standard is not enough on the Dialect options
        Set the Includes - include path tp point to the casablancea includes dir
        set the Casablanca Libraries path to the Binaries directory built
        add cpprest and common_utilities to the libraries list
        
<h2>Paths and Symbols (c/c++ General settings)</h2>
        GNU C++ make sure the include directory for casablanca is defined
        Libraries - make sure the cpprest and common_utilites are defined
        Library Path - make sure that the path to the Binaries built are defined
        
<h2>Provides tab (preprocessor Include paths, macros etc.)</h2>
        make sure the CDT GCC Built-in Compiler settings contain -std=c++11

