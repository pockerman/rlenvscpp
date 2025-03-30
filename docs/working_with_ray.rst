Working with Ray
====================

This section describes how to work with `Ray <https://docs.ray.io/en/master/index.html>`_.
Specifically, we will discuss how to do distributed computing with the Ray library use the C++ API.


Install Ray
-----------

Ray is a Python library that exposes a C++ API. Thus, you can use ``pip`` in order to install it
on your system: 

.. code-block::

	pip install ray 
	

See the official `Installing Ray <https://docs.ray.io/en/latest/ray-overview/installation.html>`_ page for more options.
However, in our case we want to install Ray alongside its C++ API so install it using:

.. code-block::

	pip install -U ray[cpp]


Assuming that everything has worked fine, let's generate a project template. This is what we will be using
throughout this tutorial.

.. code-block::
	ray cpp --generate-bazel-project-template-to ray-template
	
The command above will create a directory called ``ray-template`` with the following structure

.. code-block::

	BUILD.bazel
	example.cc
	run.sh
	thirdparty
	WORKSPACE
	
Let's now review the core componets of Ray. You can find more information at 
`Overview of Ray <https://github.com/ray-project/ray-educational-materials/blob/main/Introductory_modules/Overview_of_Ray.ipynb>`_.

Ray core components
--------------------

Ray consists of a number of libraries. Schematically these are shown in the image below

.. figure:: ./images/ray_libs.png

	Stack of Ray libraries. Image from [1].


In order to use Ray's C++ API you need to i


Running Ray
-----------

We will first work using a single-node setting in order to get the basic components. We will then
move to multi-node setting.

For the multi-node setting, you must first run ray start on the 
command line to start the Ray cluster services on the machine before ``ray.init`` in Python to connect to the cluster services. 
On a single machine, you can run ``ray.init()`` without ``ray start``, 
which will both start the Ray cluster services and connect to them.


Submitting jobs with the Ray CLI
---------------------------------




References
-----------

1. `Overview of Ray <https://github.com/ray-project/ray-educational-materials/blob/main/Introductory_modules/Overview_of_Ray.ipynb>`_