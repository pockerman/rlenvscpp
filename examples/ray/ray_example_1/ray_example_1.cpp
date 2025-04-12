// we need to include the Ray API
#include <ray/api.h>

// msgpack is needed to serialize the RayActor class
#include <msgpack.hpp>


// This is the C++ function we want to execute
int do_sth() {
  return 1;
}


void run_task(){
	
	// Invoke the above method as a Ray task.
	// This will immediately return an object ref (a future) and then create
	// a task that will be executed on a worker process.
	auto res = ray::Task(do_sth).Remote();
	
	// The result can be retrieved with ``ray::ObjectRef::Get``.
	auto result = *res.Get();
	
	std::cout<<"Result is: "<<result<<std::endl;
	
}
	
// In order to be able to execute this function
// we need to register it using `RAY_REMOTE`.
RAY_REMOTE(do_sth);

class RayActor
{
public:
	
	int ray_actor_do_sth(){return 2;}
	
	// we need this for msgpack to work
	template <typename Packer>
    void msgpack_pack(Packer& pk) const {
		pk.pack(*this);
	}
	
};

RayActor create_actor(){
	return new RayActor();
}

RAY_REMOTE(create_actor, &RayActor::ray_actor_do_sth);

void run_actor(){
	
	// create the actor and get a handle to it
	auto actor_handler = ray::Actor(create_actor).Remote();
	
	// Call the actor's remote function
	auto res = actor_handler.Task(&RayActor::ray_actor_do_sth).Remote();
	
	// The result can be retrieved with ``ray::ObjectRef::Get``.
	auto result = *res.Get();
	
	std::cout<<"Result is: "<<result<<std::endl;
}
	
int main(int argc, char **argv) {
		
	// We need to initialize Ray before using it
	ray::Init();
	
	// run the taks remotely
	run_task();
	run_actor();
	
	ray::Shutdown();
	
	std::cout<<"Running normal C++ stuff here..."<<std::endl;
	auto result = do_sth();
	std::cout<<"Result is: "<<result<<std::endl;
	
	return 0;
}
