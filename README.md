# PhantomFuck

**Because sometimes, writing invisible code in a language named after a profanity is the only logical next step.**

---

## Overview

PhantomFuck is an esoteric programming language so committed to confusion that it uses _only_ zero-width UTF-8 characters. Each pair of zero-width characters maps directly to a Brainfuck token, letting you produce Brainfuck logic that’s utterly unreadable in a typical text editor.

This is some next-level “I want to watch the world burn” coding, deliberately hidden in plain sight, showcasing the inherent masochism of esolang enthusiasts. It’s both a middle finger to readability and a homage to Brainfuck’s minimalistic spirit.

PhantomFuck is self-aware enough to know that it’s an absolute pain in the ass to debug or even see in your editor. But hey, the show must go on.

---

## Rationale

- **Chaos**  
  Let’s not pretend we’re saving the world here. We’re just messing with convention.  
- **Art**  
  Some folks paint landscapes with watercolors; some folks encode logic with invisible Unicode. Who are we to judge?

---

## Character Mapping

Below is the official mapping from zero-width characters to Brainfuck tokens. Each token consists of two zero-width characters, which we notate (for your reading convenience) as follows:

| PhantomFuck Pair    | Brainfuck Token | Description      |
|---------------------|-----------------|------------------|
| U+200B U+200B (1,1) | `>`             | Move pointer right  |
| U+200B U+200C (1,2) | `<`             | Move pointer left   |
| U+200B U+200D (1,3) | `+`             | Increment cell      |
| U+200C U+200B (2,1) | `-`             | Decrement cell      |
| U+200C U+200C (2,2) | `.`             | Output byte         |
| U+200C U+200D (2,3) | `,`             | Input byte          |
| U+200D U+200B (3,1) | `[`             | Loop start          |
| U+200D U+200C (3,2) | `]`             | Loop end            |

**Yes, it’s exactly as fucked up as it sounds.** Your code becomes a cryptic soup of invisible runes, each pair of zero-width characters forming a Brainfuck instruction.

---

## Example

```// Good luck seeing anything here.```

Of course, the actual PhantomFuck file is a black void. No, your browser/editor is not broken; it’s just how we like it.

---

## Usage

- **Interpreter**: .\PhantomFuck.exe .\HelloWorld.phf
- **Translator**: .\BrainFuckToPhantomFuck.exe .\HelloWorld.bf .\HelloWorld.phf

## Implementation & Philosophy
PhantomFuck implements the standard Brainfuck tape system, pointer movement, and loops. When you run a PhantomFuck file, each pair of zero-width characters is translated to its Brainfuck equivalent, which is then executed by a Brainfuck interpreter.

## We are fully aware that:

- Collaboration on a PhantomFuck project is the absolute definition of “team-building exercise from hell.”
- Debugging is basically guesswork and frantic copying into some hex or character inspector.
- Sanity is optional when using this language.
- We embrace these truths, if only to prove that we can.

## Why “PhantomFuck”?
Because we can. Because esoteric languages exist for the sole purpose of pushing boundaries and messing with minds. If you’re going to subvert readability, you might as well go big.

## Contributing
Have some horrifying improvements? Or maybe you just want to fix a bug in the interpreter so it’s actually possible to use? Pull requests are welcome. Just don’t ask us to make the language more readable. That defeats the entire purpose.

## License
Licensed under the MIT License. Because if we’re going to create a zero-width fiasco, at least we can do it under a permissive license.

