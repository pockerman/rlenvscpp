Using Ray core Tasks
===========================

This example will show you how to use one of Ray's core abstractions.
Namely how to create Ray `Tasks <a href="https://docs.ray.io/en/latest/ray-core/tasks.html">`_, 

With Ray we can execute arbitrary functions on separate workers.
These functions are called Ray tasks. The code snippet below shows 
you how to create a Ray Task:

.. code-block::

	// we need to include the Ray API
	#include <ray/api.h>
	
	// This is the C++ function we want to execute
	int do_sth() {
	  return 1;
	}
	
	// In order to be able to execute this function
	// we need to register it using `RAY_REMOTE`.
	RAY_REMOTE(do_sth);
	
	int main(int argc, char **argv) {
		
		// We need to initialize Ray before using it
		ray::Init();

		// Invoke the above method as a Ray task.
		// This will immediately return an object ref (a future) and then create
		// a task that will be executed on a worker process.
		auto res = ray::Task(do_sth).Remote();
	
		// The result can be retrieved with ``ray::ObjectRef::Get``.
		auto result = *res.Get();
		
		// shutodown Ray
		ray::Shutdown();
		
		std::cout<<"Result is: "<<result<<std::endl;
		std::cout<<"Running normal C++ stuff here..."<<std::endl;
		
		result = do_sth();
		std::cout<<"Result is: "<<result<<std::endl;
		
		
		return 0;
	}

You can build the code using the ``cmake`` toolchain, but Ray favors `Bazel <https://bazel.build/>`_ 
for building and running jobs. Let's see how we can use this to build the example.
Copy the following files and directories from ``external/ray`` directory:

-	``run.sh``
-  ``BUILD.bazel``
-  ``WORKSPACE``
- ``thirdparty`` 

into the directory where the ``ray_example_1`` is located.
Edit the ``run.sh`` file and change the line where the ``bazel`` executable is called to this:

.. code-block::

	bazel build //:ray_example_1
	
In addition you need to change where the Ray library is located.
Edit the line where the ``LD_LIBRARY_PATH`` variable is declared. This should
point to ``external/ray/thirdparty/lib`` path.

.. code-block::

	LD_LIBRARY_PATH="thirdparty/lib" "${ROOT_DIR}"/bazel-bin/ray_example_1

Edit the ``BUILD.bazel`` file and change accordingly the variables:

.. code-block::

	cc_binary(
		name = "ray_example_1",
		srcs = glob([
			"*.cpp",
		]),
		data = [
			"ray_example_1.so",
		],
		linkstatic = True,
		deps = [
			":ray_api",
		],
	)

	cc_binary(
		name = "ray_example_1.so",
		srcs = glob([
			"*.cpp",
		]),
		linkopts = ["-shared"],
		linkstatic = True,
		deps = [
			":ray_api",
		],
	)

	cc_library(
		name = "ray_api",
		srcs = [
			"thirdparty/lib/libray_api.so",
		],
		hdrs = glob([
			"thirdparty/include/**/*.h",
			"thirdparty/include/**/*.hpp",
		]),
		linkopts = ["-Wl,-rpath,./"],
		strip_include_prefix = "thirdparty/include",
		visibility = ["//visibility:public"],
	)

In order to build and run the example execute the ``run.sh`` script. This should
produce the following output:

.. code-block::

	INFO: Analyzed target //:ray_example_2 (1 packages loaded, 3440 targets configured).
	INFO: Found 1 target...
	Target //:ray_example_2 up-to-date:
	bazel-bin/ray_example_2
	INFO: Elapsed time: 2.509s, Critical Path: 2.15s
	INFO: 4 processes: 4 linux-sandbox.
	INFO: Build completed successfully, 6 total actions
	[2025-04-05 12:13:21,602 I 24601 24601] config_internal.cc:216: No code search path found yet. The program location path "/home/alex/.cache/bazel/_bazel_alex/25a018d10ef2129864cd574bc2dbc5b9/execroot/__main__/bazel-out/k8-fastbuild/bin" will be added for searching dynamic libraries by default. And you can add some search paths by '--ray_code_search_path'
	[2025-04-05 12:13:21,603 I 24601 24601] process_helper.cc:51: ray start --head --port 6379 --redis-username default --redis-password 5241590000000000 --node-ip-address '192.168.0.129'
	2025-04-05 12:13:22,376 - INFO - NumExpr defaulting to 8 threads.
	Usage stats collection is enabled. To disable this, add `--disable-usage-stats` to the command that starts the cluster, or run the following command: `ray disable-usage-stats` before starting the cluster. See https://docs.ray.io/en/master/cluster/usage-stats.html for more details.
	
	Local node IP: 192.168.0.129

	--------------------
	Ray runtime started.
	--------------------

	Next steps
	To add another node to this Ray cluster, run
		ray start --address='192.168.0.129:6379'
	
	To connect to this Ray cluster:
		import ray
		ray.init(_node_ip_address='192.168.0.129')
	
	To submit a Ray job using the Ray Jobs CLI:
		RAY_ADDRESS='http://127.0.0.1:8265' ray job submit --working-dir . -- python my_script.py
	
	See https://docs.ray.io/en/latest/cluster/running-applications/job-submission/index.html 
	for more information on submitting Ray jobs to the Ray cluster.
	
	To terminate the Ray runtime, run
		ray stop
	
	To view the status of the cluster, use
		ray status
	
	To monitor and debug Ray, view the dashboard at 
		127.0.0.1:8265
	
	If connection to the dashboard fails, check your firewall settings and network configuration.
	[2025-04-05 12:13:25,278 I 24601 24601] gcs_client.cc:98: GcsClient has no Cluster ID set, and won't fetch from GCS.
	[2025-04-05 12:13:25,292 I 24601 24601] gcs_client.cc:98: GcsClient has no Cluster ID set, and won't fetch from GCS.
	2025-04-05 12:13:26,854 - INFO - NumExpr defaulting to 8 threads.
	Stopped all 5 Ray processes.
	Result is: 1
	Running normal C++ stuff here...
	Result is: 1



