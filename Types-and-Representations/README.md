# Types and their Representations

This repository contains two programs

* `show-types`
* `show-reps`

Which print out information about the way types are represented on a given
machine.

### Building

Compile the code by running:
```
make
```

### Running

Once you've build the code, examine their output by running:
```
./show-types | more
```
(the `| more` part causes all the output not to scroll by in one go, press space to page through it), and similarly run
```
./show-reps | more
```

### Investigating More...

You can look at and edit the code if you want.  It's probably best to focus on `main`.   The other functions use C++ features we haven't looked at yet in the course and so might seem a bit strange (but you'll understand by the end of the course!).

For example, there is also a type called `int_fast32_t` which is at least 32-bits, but can be larger if that's faster.  You could add a line `show-types.cpp` to investigate it.
