OpenStudio-HelloWorld
=====================

Example of a third party program that uses OpenStudio. It requires a recent build of OpenStudio (1.4.X should work) to compile.

The program is built using CMake (2.8.11 or newer). After the first configure, set `OPENSTUDIO_BUILD_DIR` to point to the OpenStudio build, configure again, and then generate. Depending upon your configuration, it may also be necessary to set `BOOST_ROOT` and `CMAKE_PREFIX_PATH`.
