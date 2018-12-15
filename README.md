# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Synonym of a desease named silicosis

## According to its man page, what does `getrusage` do?

Get and return the resurce usage measure

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Because the data size is large, consuming more memory to copy the value to the function

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

It filters characters seeing if is alphanumerical or if it has apostrophes unless if it's the first character, after it appends in the position of the
cursor the character in an array of 45 + \0 elements and update the cursor.
If the cursor is too big, a while loop finish the word and restart the cursor.
If it has number, a while loop finish the word and restart the cursor.
If the cursor is not reseted, a \0 finish the word and update the counter of number of words.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf doesn't support special filter of length size, number and special characteres.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

To avoid acidental changes
