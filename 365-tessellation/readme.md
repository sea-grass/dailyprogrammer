# tessellate

See /r/dailyprogrammer#365

## Description

The program is run by supplying a filename that contains a pattern to
tessellate and a rotation to apply.

It will process the pattern and output a 2x2 tessellation of that
pattern to screen.

## What's finished

- [x] 90deg matrix rotation
- [ ] 180deg matrix rotation
- [ ] -90deg matrix rotation
- [ ] all symbols rotated
- [x] basic 2x2 pattern tessellation
- [ ] extensive tests
- [ ] custom nxn pattern tessellation

## To run

```
make
./tessellate tests/basic.txt
```

## Learning results

- See `printPattern` on how I printed a 1D array in a 2D format
using `printf`'s format specifiers.
- See `stitch` - A requirement of this problem led me to "stitch"
character arrays together. Not fully generalized; still specific
to this problem.

## Future tasks

- Needs more error handling
- Pretty sure there's a segfault in there somewhere
- Add unit tests
- Generalize functions
- Make it word with `n`x`m` patterns instead of only `n`x`n`
