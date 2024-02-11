# SoarProto v2.00

## Description

A brief description of the project.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Changes

### Name Changes

we

### Integration Instructions

- Completely disable mev_power_enable on the embedded side
- Removed MEV state telemetry message
- enums in back end will be stored as strings in db
- No flash on db
- No Seq on DB
- naks cause bug that we keep sending naks back and forth over and over

- Need to fix control nak but not an issue
  - Top priority
- ACK Only protocol??
