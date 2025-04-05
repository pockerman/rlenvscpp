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
	
	ray::Shutdown();
	
	std::cout<<"Result is: "<<result<<std::endl;
	std::cout<<"Running normal C++ stuff here..."<<std::endl;
	result = do_sth();
	std::cout<<"Result is: "<<result<<std::endl;
	
	return 0;
}
