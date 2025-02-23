
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
environment. Currently, ```rlenvscpp``` provides the following vector environments: 

| Environment         |   Use REST   | Example                                                    |
| :----------------   | :----------: | :----:                                                     |
| AcrobotV            |   Yes        |  <a href="examples/example_8/example_8.cpp">example_8</a>  |

Various RL algorithms using the environments can be found at <a href="https://github.com/pockerman/cuberl/tree/master">cuberl</a>.


Dynamics 
---------

Apart from the exposed environments, ```rlenvscpp``` exposes classes that 
describe the dynamics of some popular rigid bodies:

| Dynamics            |                       Example                                |
| :----------------   | :----------------------------------------------------------: | 
| Differential drive  |  <a href="examples/example_9/example_9.cpp">example_9</a>    |
| Quadrotor           |  <a href="examples/example_10/example_10.cpp">example_10</a> |
| Bicycle vehicle     |  TODO                                                        |

Miscellaneous
-------------

| Item                   |                       Example                                |
| :----------------      | :----------------------------------------------------------: | 
| Environment trajectory |  <a href="examples/example_3/example_3.cpp">example_3</a>    |
| WaypointTrajectory     |  <a href="examples/example_11/example_11.cpp">example_11</a> |
| TensorboardServer      |  <a href="examples/example_12/example_12.cpp">example_12</a> |
