Coding Style
============

After many years of programming and insight into many different "styles", discarding guidelines 
that were once considered useful, the following definitions have proven to be good in the long 
term for us. Of course there are other good guidelines, but these are the ones that are binding
for our projects. We therefore expressly ask you to implement them.

There will still be files that do not comply with these guidelines because the code has grown 
naturally over time. If you touch such a file, please update it to the new standards as best you
can.

## User Interface Strings

Depending on the context we use two different styles for formatting the strings:

### "Title Case"

"Title case" means, that every word begins with an upper case letter. Exception: Short words like in, of, to etc.

Used in:
- Text fragments
- Menu items
- Buttons
- Titles
- Column titles
- Technical short description (like names of parameters or variables)

### "Sentence Style"

"Sentence style" means, writing like regular text.

Used in:
- Error messages
- Status messages
- Complete sentences

## Naming Conventions

- Our code lines have maximum 100 characters. For idention we use 3 spaces.

- We use camel case syntax for common names like class names, function names, member names etc.
  Example: `StringList`, `Vertex2`, `ExampleClass`

- Class names and Enums starts with upper case, variable names and member functions with lower case.

- We use `setSize(...)` as common setter method and `size()` as corresponding getter method. Avoid
  using `getSize()`. In some rare cases using `getSize()` is the better solution, but in general: avoid.

- Some names of variables have a prefix letter:
  - Members of classes uses `m`. Example: `int32 mWidth;`
  - Global variables uses `g`. Example: `int32 gCount;`
  - Enum members uses `k` as first letter usually followed by a short word or abbreviation to
    characterize the enum, whe the value comes from: Example: `kLnWt100`, `kVersionR14`

- If possible, we do not use reference indicators like `int32 miWidth`. Avoid storing same value in 
  different types of data.

- We have defined short abbreviations for common data types. `int32` or `uint32` for `int` or 
  `unsigned int`. Please use this.

## Artistic Style (astyle)

For artistic style, please use the following settings:

-A1: Brackets ANSI/BSD-Style
-s3: Indent: 3 spaces
-C: Indent 'class' and 'struct'
-S: Indent 'switch' blocks
-N: Indent namespaces
-U: Remove extra space padding around parenthesis on the inside and outside.
-Y: Indent C++ comments beginning in column one.
-p: Insert  space  padding  around  operators.
-k1: Attach a pointer or reference operator (*, &, or ^) to the type
~~~
astyle --recursive -A1 -s3 -C -S -N -U -Y -p -k1 *.h *.hpp *.cpp
~~~

