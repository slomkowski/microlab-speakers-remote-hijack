# Microlab speaker auto start

You'll find more info on https://slomkowski.eu/projects/microlab-speakers-remote-hijack/.

Compiled under *avr-gcc*, *CMake* required.

## Compile

```
mkdir -p build
cd build
cmake ..
make
```

## Program the Digispark

```
micronucleus --run microlab-speaker-remote-hijack.hex
```

Then plug the Digispark module. It is programmed.
