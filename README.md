# Quackbox Controller Monorepo

This repository contains various examples and tests for different components of the COMStroller, a game controller designed for the COMS Console (Quackbox). The purpose of this monorepo is to organize and manage the development and testing of individual components that make up the COMStroller. The main project directory that will be deployed to the real controllers is in the `COMStroller` directory.

## Structure

The repository is organized into several directories, each containing specific examples and tests for different components:

- `test-examples/joystick`: Contains examples and tests related to the joystick component of the COMStroller.
- `test-examples/button`: Contains examples and tests related to the button component of the COMStroller.
- `test-examples/button-matrix`: Contains examples and tests related to the button matrix component of the COMStroller.
- `components`: This directory will house separate components for the COMStroller. Each component will have its own project structure and tests.
- `COMStroller`: The main project directory that will be deployed to the real controllers. This directory contains the core codebase and configurations necessary for the deployment and operation of the COMStroller on the COMS Console (Quackbox).

## Getting Started

To get started with the development and testing of the COMStroller components, follow these steps:

1. **Clone the repository:**
    ```sh
    git clone https://github.com/rit-coms/COMStroller.git
    cd COMStroller
    ```

2. **Set up the development environment:**
    Ensure you have the necessary tools and dependencies installed. Refer to the ESP-IDF documentation for setting up the environment.

3. **Build and run examples:**
    Navigate to the specific example directory and follow the instructions provided in the README files to build and run the examples.

## Contributing

We welcome contributions to improve the COMStroller and its components. If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).