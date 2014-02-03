SideQuest II Styleguide
=======================

This document will serve as a code style guide for SideQuest. If you propose pull requests, please make sure your code conforms to this style guide.

Language
--------
The programming language is C++, and the code will make use of C++11 features.

Indentation
-----------
Please use tabs for indentation. Tabs are not only made for this, everyone can set them to the amount of spaces he/she would like to see.

Max. Line lenght
----------------
The line should fit into 1280px with respect to GUI elements of an IDE on the side. 

Documentation
-------------
We use Doxygen for documentation. The preferred doxygen comment style is this one:

```cpp
/**
  Your documentation text here
*/
```
Bracket rules
-------------
Give the curly brackets their own line so that they match up vertically.

```cpp
void foo()
{

}
```
