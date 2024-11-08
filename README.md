# File tree TUI

The goal of this project is to build a TUI in C to display a file tree, inspired by the tree command or [lsd –-tree](https://github.com/lsd-rs/lsd). It allows the user to collapse directories they don’t want to view, similar to the file tree structure in standard IDEs.

If you’re here, please note that this project **does not** simply display the file tree like the tree command. Instead, it creates a custom TUI experience.


I'm mainly building this for myself.
I want to use this as an exercise, and the goal usage is with the [helix editor](https://helix-editor.com/) and [zellij](https://zellij.dev).
later on I will put some images to let y'all see how it looks like, both alone and with my zellij layout.

\*sad hamster gif\*

# This project is NOT FINISHED YET

ToDo list:

- Fix truncation when a longer file is selected
- Make the damn selection blink
- Avoid flickering when an edit occurs.
- Prevent users from entering a closed directory 
- Add icons (potentially by adapting code from [this file](https://github.com/lsd-rs/lsd/blob/master/src/theme/icon.rs))
- Add args (like -all, -icons, -colors, -closed, -opened, -sort)
- Add sort type
- Add config file (with default closed dirs for example)
- Add system calls to update the TUI if something changes and for displaing if a file is modified somewhere

Later on:
- add commands to do some operations in the tree, such as rename, touch, trash, delete, move, copy, paste, cut.

## build

build with `make` command

