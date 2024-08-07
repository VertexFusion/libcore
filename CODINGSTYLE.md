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


## Artistic Style (astyle)

For artistic style, please use the following settings:

~~~
astyle -A1 -s3 -C -S -N -U -Y -xw -p -k1 -xC100 *
~~~

