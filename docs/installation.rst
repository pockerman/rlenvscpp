Installation
============

This section describes how to install ``rlenvscpp``.

Dependencies
------------

The library has the following general dependencies

- A compiler that supports C++20 e.g. g++-11
- `Boost C++ <https://www.boost.org/>`_ 
- `CMake >= 3.10 <https://cmake.org/>`_
- `Gtest  <https://github.com/google/googletest>`_  (if configured with tests)
- `Eigen3 <https://eigen.tuxfamily.org/index.php?title=Main_Page>`_


``rlenvscpp`` also incorporates, see ``(src/extern)``, the following libraries

- `HTTPRequest <https://github.com/elnormous/HTTPRequest>`_
- `nlohmann/json <https://github.com/nlohmann/json>`_


Using the Gymnasium environments requires `Gymnasium <https://github.com/Farama-Foundation/Gymnasium/tree/main>`_ 
installed on your machine. In addition, you need to install

- `FastAPI <https://fastapi.tiangolo.com/>`_
- `Uvicorn <https://www.uvicorn.org/>`_
- `Pydantic <a href="https://docs.pydantic.dev/latest/>`_

By installing the requirement under ``requirements.txt`` should set your Python environment  up correctly.

There are extra dependencies if you want to generate the documentation. Namely,

- Doxygen
- Sphinx
- sphinx_rtd_theme
- breathe
- m2r2

Building the code
-----------------

The usual CMake based installation process is used. Namely

.. code-block::

	mkdir build && cd build && cmake ..
	make install


You can toggle the following variables

- CMAKE_BUILD_TYPE (default is RELEASE)
- ENABLE_TESTS_FLAG (default is OFF)
- ENABLE_EXAMPLES_FLAG (default is OFF)
- ENABLE_DOC_FLAG (default is OFF)

For example enbling the examples 

.. code-block::

	cmake -DENABLE_EXAMPLES_FLAG=ON ..
	make install


Run the tests
-------------

You can execute all the tests by running the helper script ``execute_tests.sh``.


Build the documentation
-----------------------


Issues
-------

**Could not find ``boost_system``**

It is likely that you are missing the boost_system library with your local Boost installation. This may be the case
is you installed boost via a package manager. On a Ubuntu machine the following should resolve the issue

.. code-block::

	sudo apt-get update -y
	sudo apt-get install -y libboost-system-dev


**FastAPI throws 422 Unpocessable entity**

Typically, this is a problem with how the client (400-range error) specified the data
to be sent to the server. 