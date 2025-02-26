
# rlenvscpp

``rlenvscpp`` is an effort to provide implementations and wrappers of environments suitable for training reinforcement learning agents
using  C++. In addition, the library provides various utilities such as experiment tracking,
representing trajectories  via waypoints and simple implementation of popular dynamics such as 
quadrotor dynamics.

Environments
------------

Currently, ``rlenvscpp`` provides the following environments:

+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| Environment         |   Use REST   | Example                                                                                             |
+=====================+==============+=====================================================================================================+
| FrozenLake 4x4 map  |   Yes        | `example_1 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_1/example_1.cpp>`_  |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| FrozenLake 8x8 map  |   Yes        | TODO                                                                                                |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| Blackjack           |   Yes        | `example_1 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_1/example_1.cpp>`_  |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| CliffWalking        |   Yes        | `example_1 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_1/example_1.cpp>`_  |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| CartPole            |   Yes        | TODO                                                                                                |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| MountainCar         |   Yes        | TODO                                                                                                |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| Taxi                |   Yes        | `example_1 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_1/example_1.cpp>`_  |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| Pendulum            |   Yes        | `example_1 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_6/example_6.cpp>`_  |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| Acrobot             |   Yes        | TODO                                                                                                |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| GymWalk             |   Yes        | TODO                                                                                                |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| gym-pybullet-drones |  TODO        | TODO                                                                                                |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| GridWorld           |   No         | `example_1 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_5/example_5.cpp>`_  |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| Connect2            |   No         | `example_1 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_7/example_7.cpp>`_  |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+

The Gymnasium (former OpenAI-Gym) environments utilise a REST API to communicate requests to/from the 
environment and ``rlenvscpp``.

Some environments have a vector implementation meaning multiple instances of the same
environment. Currently, ``rlenvscpp`` provides the following vector environments: 

+---------------------+--------------+-----------------------------------------------------------------------------------------------------+
| Environment         |   Use REST   | Example                                                                                             |
+=====================+==============+=====================================================================================================+
| AcrobotV            |   Yes        |  `example_8 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_8/example_8.cpp>`_ |
+---------------------+--------------+-----------------------------------------------------------------------------------------------------+

Various RL algorithms using the environments can be found at `cuberl <https://github.com/pockerman/cuberl/tree/master>`_.


Dynamics 
---------

Apart from the exposed environments, ``rlenvscpp`` exposes classes that 
describe the dynamics of some popular rigid bodies:

+---------------------+-------------------------------------------------------------------------------------------------------+
| Dynamics            |                       Example                                                                         |
+=====================+=======================================================================================================+
| Differential drive  |  `example_9 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_9/example_9.cpp>`_   |
+---------------------+-------------------------------------------------------------------------------------------------------+
| Quadrotor           |  `example_10 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_10/example_10.cpp>`_|
+---------------------+-------------------------------------------------------------------------------------------------------+
| Bicycle vehicle     |  TODO                                                                                                 |
+---------------------+-------------------------------------------------------------------------------------------------------+

Miscellaneous
-------------

+------------------------+-------------------------------------------------------------------------------------------------------+
| Item                   |                       Example                                                                         |
+========================+=======================================================================================================+ 
| Environment trajectory |  `example_3 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_3/example_3.cpp>`_   |
+------------------------+-------------------------------------------------------------------------------------------------------+
| WaypointTrajectory     |  `example_11 <https://github.com/pockerman/rlenvscpp/blob/master/examples/example_11/example_11.cpp>`_|
+------------------------+-------------------------------------------------------------------------------------------------------+
| TensorboardServer      |  `example 12 <https://github.com/pockerman/rlenvscpp/tree/master/examples/example_12>`_               |
+------------------------+-------------------------------------------------------------------------------------------------------+
