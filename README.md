# fsplit
Easily split a file into multiple files, especially across multiple drives.

Usage: `fsplit filename1 size1 [filename2 size 2] ... [lastfilename]`

If the last file specified is not accompanied by a file size, then all remaining
bytes are written to that file.

Input is expected to be received via stdin.

The files can then be reassembled with a tool such as cat, taking care to maintain
the original file order:
`cat filename1 filename2 ... lastfilename`
