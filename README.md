<div align="middle">
<img alt="Avionics" src="https://user-images.githubusercontent.com/78698227/194972541-2e244866-7485-4ec7-a6b4-b8dcc82c1b35.png" width="400"/>
</div>


## Table of Contents

1. [What is this?](#what-is-this)
    1. [Dependencies]()
        1. [Linux Only](#linux-only)
        2. [Windows Users](#windows-users)
    2. [Style Guide](#style-guide)
        1. [Type Hinting](#type-hinting)
2. [TODO](#todo)

# What is this?

This is the repo for the rocket control unit.

Most of the development is done in [python](https://www.python.org/download/releases/3.0/),
and access to the RCU can be done through ssh.

Contact a lead for information regarding ssh access.

## Dependencies

### Linux Only

The biggest dependencies will require you to use the `RPi.GPIO` python library.
This can only be done on Linux, LOL.
```bash
# pip install RPi.GPIO
```

### Windows Users

Windows users should enable [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
and clone the repo and instal `RPi.GPIO` through pip as above and
make changes from there.

## Getting Started

See the following [examples directory](https://sourceforge.net/p/raspberry-gpio-python/wiki/Examples/)
for use on how to get started.

## Style Guide

All code should adhere to the [PEP8](https://peps.python.org/pep-0008/)
code standard.
There are [autoformatters](https://pypi.org/project/autopep8/) available which can do this for you.

### Type Hinting

Code should use typehints when available to allow for better readability.

# TODO

- [x] Create repo
- [ ] Get basic GPIO functionality working
    - [ ] GPIO Read
    - [ ] GPIO Write
    - [ ] ADC Integration
- [ ] Repo organization
    - [ ] `main.py`
    - [ ] sub-directories
