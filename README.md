# Tic-Tac-Toe

![Screenshot](https://github.com/kirusfg/tictactoe/blob/main/img/screenshot.png?raw=true)

This task is a recap of Lab 5, but a little bit more challenging, and if
completed, more rewarding.

Just as in Lab 5, you need to complete `state.cpp`, which is implementation of
the `State` class in our program. Implement all the methods it requires, half of
which are identical to your lab.

The logic of the game is different this time, and we cannot depend on some
simple metric do decide the winner as in Nim. The `Game` class routinely
calls a `winner` method of the state do check if the last move has decided
who won. More than that, there is also a possibility of a tie, hence the
`std::optional<Value>` return type of the method.

This should not take you long if you have done Lab 5. You are encouraged to look
at the game code overall to see how games operate (all games have some sort of a
loop running at all times and updating systems, entities, etc.). Change colors,
the decorations, make them configurable, if you want to.

Next weekend you are going to implement an AI to compete against, as this one
still does only random moves.

## Getting started
You are on GitHub, one of the biggest `git` hosting providers. `git`, in turn,
is a version control system developed by Linus Torvalds, the maker of Linux. It
is the most popular one by far, and the earlier you get comfortable with it -
the better.

Git is likely installed if you are on MacOS or Linux. In any way, using **package
managers** for downloading programs is the most convenient path, even on Windows.
The most prominent package manager on Windows is `winget`, on MacOS it's `brew`,
while Linux distributions have their own: `apt`, `pacman`, `yum`, `dnf`, etc.

Installing any software with a package manager is a matter of running one command:
```sh
apt install git # Ubuntu
pacman -S git # Arch
brew install git # MacOS
```

Install a package manager (if there isn't already one) for your OS, install git,
and proceed to the next steps.

## Working with Git

In order to download the source code, you need to "clone" this repository to your
machine:

```sh
cd your-preferred-directory
git clone https://github.com/kirusfg/tictactoe.git
```

This will create a folder called `tictactoe` subdirectory and populate it with
the files from this repository. Make sure you are on the `main` branch:

```sh
cd tictactoe
git checkout -m main
```

## Building

There is a Makefile provided, as well as the VS Code tasks for running the make
commands, as well as the game itself.

To build using `make`, simply run

```sh
make
```

In order to build the program with debug symbols (without them, you will not be
able to see much while debugging; breakpoints will not work, either), run

```sh
make debug
```

If you want to use VS Code for building, run the available Build tasks from the
command pallette (Ctrl+Shift+P): either Build (Release), Build (Debug), or Run.

The build artifacts reside in the `build` directory. To run the game, simply do

```sh
./build/tictactoe
```

## Solution

It is obviously counter-productive to look at the solution right away, but if
you are really stuck, there is a working implementation residing on the `finished`
branch. You can browse that branch on the GitHub, or in your IDE if you check out
that branch:

```sh
git checkout -m finished
```
