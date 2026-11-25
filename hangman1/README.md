# Hangman

A console Hangman game with easy, medium, and hard word lists, optional hints, replay controls, and persistent statistics. The statistics file is `hangman_statistics.txt` in the current working directory; it records completed games, wins, losses, and incorrect guesses.

## Build

Run from this directory:

```sh
g++ main.cpp game.cpp wordselector.cpp draw.cpp -o hangman
```

## Run

```sh
./hangman
```

Choose Play Game, select a difficulty, and enter one letter per guess. Statistics are saved after each completed round and can be viewed from the main menu.
