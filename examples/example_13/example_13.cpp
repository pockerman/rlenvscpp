/**
 * This example utilises the ```TensorboardServer``` class to log values of interest when running
 * an experiment. We can monitor the experimet  using <a href="https://www.tensorflow.org/tensorboard">tensorboard</a>.
 * The   ```TensorboardServer``` class is a simple wrapper that exposes three functions
 *
 *	- ```add_scalar```
 *	- ```add_scalars```
 *	- ```add_text```
 *
 *	We will use ```add_scalar``` and ```add_text```. In order to run this example, fire up the server using the ```torchboard_server/start_uvicorn.sh```.
 *	The server listens at port 8002. You can change this however you want just make sure that the port is not used and also update the
 *	variable ```TORCH_SERVER_HOST``` in the code below accordingly. Note that the implementation uses
 *	<a href="https://pytorch.org/docs/stable/_modules/torch/utils/tensorboard/writer.html#SummaryWriter">SummaryWriter</a> class.
 *	Thus you will need to have PyTorch installed on the machine that you run the server.
 */ 


#include "rlenvs/rlenvs_types_v2.h"
#include "rlenvs/utils/geometry/geom_point.h"
#include "rlenvs/utils/geometry/mesh/mesh.h"
#include "rlenvs/utils/geometry/mesh/quad_mesh_generation.h"

#include <random>
#include <filesystem>
#include <string>
#include <iostream>

namespace example_13
{
using namespace rlenvscpp;
using utils::geom::Mesh;
using utils::geom::GeomPoint;

}

int main() {

    using namespace example_13;

    try{

		// build a square grid
		Mesh<2> mesh;
		utils::geom::build_quad_mesh(mesh, 
		                             10, 10,
		                             GeomPoint<2>({0.0, 0.0}),
									 GeomPoint<2>({1.0, 1.0}));
									 
		std::cout<<"Number of elements: "<<mesh.n_elements()<<std::endl;
		std::cout<<"Number of nodes:    "<<mesh.n_nodes()<<std::endl;
     

    }
    catch(std::exception& e){
        std::cout<<e.what()<<std::endl;
    }
    catch(...){

        std::cout<<"Unknown exception occured"<<std::endl;
    }

   return 0;
}



