# File tree TUI

The goal of this project is to build a TUI in C to display a file tree, inspired by the tree command or [lsd –-tree](https://github.com/lsd-rs/lsd). It allows the user to collapse directories they don’t want to view, similar to the file tree structure in standard IDEs.

If you’re here, please note that this project does not simply display the file tree like the tree command. Instead, it creates a custom TUI experience.

# This project is NOT FINISHED YET

ToDo list

- Fix truncation when a longer file is selected
- Prevent users from entering a closed directory 
- Add icons (potentially by adapting code from [this file](https://github.com/lsd-rs/lsd/blob/master/src/theme/icon.rs))

## build

build with `make` command

