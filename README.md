# Rocket Control Unit

<a href="https://docs.python.org/3/reference/" rel="Python 3 Reference">![Python 3](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)</a>
<a href="https://www.raspberrypi.com/products/raspberry-pi-5/" rel="RPI 5">![Raspberry Pi](https://img.shields.io/badge/-RaspberryPi-C51A4A?style=for-the-badge&logo=Raspberry-Pi)</a>
<a href="https://svelte.dev/" rel="Svelte">![Git](https://img.shields.io/badge/SvelteKit-FF3E00?style=for-the-badge&logo=Svelte&logoColor=white)</a>
<a href="https://www.typescriptlang.org/" rel="TypeScript">![Git](https://img.shields.io/badge/TypeScript-007ACC?style=for-the-badge&logo=typescript&logoColor=white)</a>
<a href="https://pocketbase.io/" rel="Pocketbase">![Git](https://img.shields.io/badge/PocketBase-B8DBE4?style=for-the-badge&logo=PocketBase&logoColor=white)</a>
<a href="https://www.skeleton.dev/" rel="Skeleton">![Git](https://img.shields.io/badge/Tailwind_CSS-38B2AC?style=for-the-badge&logo=tailwind-css&logoColor=white)</a>
<a href="https://github.com/StudentOrganisationForAerospaceResearch/RocketControlUnit.git" rel="GitHub">![Git](https://img.shields.io/badge/git-%23F05033.svg?style=for-the-badge&logo=git&logoColor=white)</a>

![](https://img.shields.io/github/repo-size/StudentOrganisationForAerospaceResearch/RocketControlUnit?label=Size)
![](https://img.shields.io/github/commit-activity/m/StudentOrganisationForAerospaceResearch/RocketControlUnit)
![](https://img.shields.io/github/contributors/StudentOrganisationForAerospaceResearch/RocketControlUnit)

## Table of Contents

- [Description](#description)
- [Technology Stack](#technology-stack)
  - [SvelteKit](#svelte)
  - [Python](#python)
  - [PocketBase](#pocketbase)
  - [Skeleton](#skeleton)
  - [RaspberryPi](#raspberry-pi)
- [Dependencies](#dependencies)
- [Insallation Guide](#installation-guide)
- [TODO](#todo)

## Description

This is the repository for the rocket control unit. This software allows us to interface with our ground systems and rocket through an easy to use and functional dashboard.

The backend runs on a raspberry pi 5 and uses python. the raspberry pi is connected through UART and GPIO to the RCU-STM PCB.

The frontend is built on SvelteKit and Skeleton for UI components. Svelte is a compiled framework allowing for maximum performance.

To connect the backend to the frontend we use a self-hosted instance of PocketBase. PocketBase is a real-time database allowing for instant telemetry and commands. This also allows us to store all telemetry and analyze or process the data later on.

## Technology Stack

### Svelte

Svelte is a modern JavaScript framework designed to build user interfaces. Unlike traditional frameworks that shift much of the work to the browser, Svelte shifts this burden to the build step, resulting in highly optimized and performant applications. With its reactive approach, Svelte simplifies complex UI development by efficiently updating the DOM without unnecessary runtime overhead.

### Python

Python is a versatile and widely-used programming language known for its readability and ease of use. Python's extensive libraries and frameworks, coupled with its straightforward syntax, make it great for our needs.

### PocketBase

PocketBase is a real-time database designed for seamless data synchronization between applications. By providing a self-hosted instance, it offers us the flexibility to maintain control over out data while ensuring instant updates and efficient communication between backend and frontend. PocketBase is particularly useful for our application requiring real-time telemetry, command execution, and data storage.

### Skeleton

Skeleton is a lightweight CSS framework that provides a simple and responsive foundation for web development. It offers a set of styles for common HTML elements, making it easy to create clean and consistent user interfaces. While not as feature-rich as some larger frameworks, Skeleton is ideal for our use case where a minimalistic approach to styling and responsiveness is desired.

### Raspberry Pi

Raspberry Pi is a small, single-board computer running a version of Debian. The Raspberry Pi 5, in particular, is equipped with sufficient processing power and connectivity options. The Raspberry Pi serves as the backend infrastructure for the Rocket Control Unit in this project, connecting to the RCU and Flight PCBs.

## Dependencies

You will need Python 3.11 or greater.
You will need a PocketBase binary for your specific OS.
Svelte dependencies are inside the package.json
Python dependencies are inside the requrements.txt

## Installation Guide

- Clone repository

    ```sh
    git clone https://github.com/StudentOrganisationForAerospaceResearch/RocketControlUnit.git
    ```

    ```sh
    cd RocketControlUnit
    ```

- Database Setup
  - Download PocketBase Binary
    - Go to https://pocketbase.io/docs/ and download the build for your specific OS.
  - Move PocketBase Binary

    - Move the PocketBase binary to the `database` directory of the `RocketControlUnit` project. Replace `path_to_pocketbase_binary` with the actual path of the PocketBase binary on your system:

        ```sh
        mv path_to_pocketbase_binary RocketControlUnit/database/
        ```

  - Hosting Database

    ```sh
    cd RocketControlUnit/database/
    ```

    ```sh
    ./pocketbase serve
    ```

    Now enter the `Admin UI` URL into a browser and create a PocketBase account.

    You will now be able to access the PocketBase admin dashboard

- Backend Setup

    ```sh
    cd RocketControlUnit/backend
    ```

    ```sh
    pip install -r requirements.txt
    ```

- Frontend Setup

    ```sh
    cd RocketControlUnit/RocketControlUnitGUI/
    ```

    ```sh
    npm install
    ```

    To run an instance for development:

    ```sh
    npm run dev
    ```

    To build for production using the node adapter:

    ```sh
    npm i -D @sveltejs/adapter-node
    ```

    > **_NOTE:_**  You may have to run the above with `--force` or `--legacy-peer-deps`.

    ```sh
    npm run build
    ```

    ```sh
    npm ci --omit dev
    ```

    > **_NOTE:_**  You may have to run the above with `--force` or `--legacy-peer-deps`.

    ```sh
    node build
    ```

    By default, the server will accept connections on `0.0.0.0` using port 3000. These can be customised with the `PORT` and `HOST` environment variables:

    ```sh
    HOST=127.0.0.1 PORT=4000 node build
    ```

    To preview the app:

    ```sh
    npm run build
    ```

    ```sh
    npm run preview
    ```

## TODO

- Backend
  - [ ] Finish Serial Handler
  - [ ] Finish Database Handler
- Database
  - [ ] Add BackendCommands Table
- Frontend
  - [ ] Finish Background Creation
  - [ ] Move Components in Place
  - [ ] Add Loadcell Calibration
  - [ ] Add Fluid Flow Animation
  - [ ] Add Authentication
  - [ ] Add Test State
  - [x] Figure Out Deployment
- [ ] Integration Test
