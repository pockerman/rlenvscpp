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

Ray consists of a number of libraries.
These are:

- Ray core
- Ray AIR
- Ray cluster


Schematically these are shown in the image below

.. figure:: ./images/ray_libs.png

	Stack of Ray libraries. Image from [1].

Ray core
---------

Ray core is a rather low-level distributed computing framework. Its main key abstractions are

- `Tasks <a href="https://docs.ray.io/en/latest/ray-core/tasks.html">`_
- `Actors <https://docs.ray.io/en/latest/ray-core/actors.html>`_
- `Objects <https://docs.ray.io/en/latest/ray-core/objects.html>`_

See example 

Ray enables arbitrary functions to be executed asynchronously on separate Python workers. Such functions are called Ray remote functions 
and their asynchronous invocations are called Ray tasks. Here is an example.

Actors extend the Ray API from functions (tasks) to classes. An actor is essentially a stateful worker (or a service). 
When a new actor is instantiated, a new worker is created, 
and methods of the actor are scheduled on that specific worker and can access and mutate the state of that worker.

In Ray, tasks and actors create and compute on objects. We refer to these objects as 
remote objects because they can be stored anywhere in a Ray cluster, and we use object refs to refer to them. 
Remote objects are cached in Ray’s distributed shared-memory object store, and there is one object store per 
node in the cluster. In the cluster setting, 
a remote object can live on one or many nodes, independent of who holds the object ref(s).



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