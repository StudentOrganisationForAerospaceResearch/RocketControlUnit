<div align="middle">
<img alt="Avionics" src="https://user-images.githubusercontent.com/78698227/194972541-2e244866-7485-4ec7-a6b4-b8dcc82c1b35.png" width="400"/>
</div>

<a href="https://docs.python.org/3/reference/" rel="Python 3 Reference">![Python 3](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)</a>
<a href="https://www.raspberrypi.com/products/raspberry-pi-400/" rel="RPI 400">![Raspberry Pi](https://img.shields.io/badge/-RaspberryPi-C51A4A?style=for-the-badge&logo=Raspberry-Pi)</a>
<a href="https://www.raspberrypi.com/software/operating-systems/" rel="Raspbian">![Raspbian](https://img.shields.io/badge/Debian-D70A53?style=for-the-badge&logo=debian&logoColor=white)</a>
<a href="https://github.com/StudentOrganisationForAerospaceResearch/RocketControlUnit.git" rel="GitHub">![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)</a>

![](https://img.shields.io/github/repo-size/StudentOrganisationForAerospaceResearch/RocketControlUnit?label=Size)
![](https://img.shields.io/github/commit-activity/m/StudentOrganisationForAerospaceResearch/RocketControlUnit)
![](https://img.shields.io/github/contributors/StudentOrganisationForAerospaceResearch/RocketControlUnit)

Hello

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
    - [x] GPIO Read
    - [ ] GPIO Write
    - [ ] ADC Integration
- [ ] Repo organization
    - [ ] `main.py`
    - [ ] sub-directories
- [ ] GitHub Actions/Workflow
    - [x] First setup
    - [ ] Testing
    - [x] Cool badges
