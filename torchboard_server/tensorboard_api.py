from loguru import logger
from typing import Optional
from fastapi import FastAPI, APIRouter, Body, status, HTTPException
from fastapi.responses import JSONResponse

from pydantic import BaseModel, Field
from torch.utils.tensorboard import SummaryWriter


tesnorboard_api_router = APIRouter(prefix="/tensorboard-api", tags=["tensorboard-api"])

class InitSchema(BaseModel):
    log_dir_path: str = Field(title='log_dir_path') 
    comment: Optional[str] = Field(title='comment', default='')
    filename_suffix: Optional[str] = Field(title='filename_suffix', 
                                           default='') 
    max_queue: Optional[int] = Field(title='max_queue', default=10)
    flush_secs: Optional[int] = Field(title='flush_secs', default=120)
    purge_step: Optional[int] = Field(title='purge_step', default=None)


# helper classes to communicate data
class AddScalarSchema(BaseModel):
    tag:str = Field(title="tag") 
    scalar_value: float = Field(title="scalar_value") 
    global_step: Optional[int] = Field(title="global_step", default=None)
    walltime: Optional[float] = Field(title="walltime", default=None)
    new_style: Optional[bool] = Field(title="new_style", default=False)
    double_precision: Optional[bool] =Field(title="double_precision", default=False)  

class AddScalarsSchema(BaseModel):
    main_tag: str = Field(title='main_tag')  
    tag_scalar_dict: dict = Field(title='tag_scalar_dict')  
    global_step: Optional[int] = Field(title='global_step', default=None)  
    walltime: Optional[float] = Field(title='walltime', default=None)  

class AddTextSchema(BaseModel):
    tag: str = Field(title='tag')  
    text_string: str = Field(title='text_string')  
    global_step: Optional[int] = Field(title='global_step', default=None)  
    walltime: Optional[float] = Field(title='walltime', default=None)  


# the object that handles the writes to the
# designated log location

summary_writer: SummaryWriter = None



@tesnorboard_api_router.post("/init")
def init(log_dir_path: InitSchema = Body(...)) -> JSONResponse:

    global summary_writer
    summary_writer = SummaryWriter(log_dir=log_dir_path.log_dir_path)

    return JSONResponse(status_code=status.HTTP_201_CREATED,
                        content={"result": True}) 


@tesnorboard_api_router.post("/close")
def close() -> JSONResponse:

    global summary_writer
    if summary_writer is None:
        return JSONResponse(status_code=status.HTTP_202_ACCEPTED,
                            content={"message": True})
       
    summary_writer.close()
    return JSONResponse(status_code=status.HTTP_202_ACCEPTED,
                            content={"message": True})

@tesnorboard_api_router.post("/add-scalar")
def add_scalar(data: AddScalarSchema) -> JSONResponse:

    global summary_writer
    
    if summary_writer is None:
        raise HTTException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                            detail="summary_writer is None. Have you called init?") 

    try:
        summary_writer.add_scalar(tag=data.tag, 
                                  scalar_value=data.scalar_value,
                                  global_step=data.global_step, walltime=data.walltime, 
                                  new_style=data.new_style, double_precision=data.double_precision)

        return JSONResponse(status_code=status.HTTP_201_CREATED,
                        content={"result": True})
    except Exception as e:
        print("An error was raised when  trying to add_scalar")
        raise HTTException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                            detail=str(e)) 
    
@tesnorboard_api_router.post("/add-scalars")
def add_scalars(data: AddScalarsSchema) -> JSONResponse:

    global summary_writer
    
    if summary_writer is None:
        raise HTTException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                            detail="summary_writer is None. Have you called init?") 

    try:
        summary_writer.add_scalars(main_tag=data.main_tag, 
                                   tag_scalar_dict=data.tag_scalar_dict,
                                   global_step=data.global_step, walltime=data.walltime)

        return JSONResponse(status_code=status.HTTP_201_CREATED,
                        content={"result": True})
    except Exception as e:
        print("An error was raised when  trying to add_scalar")
        raise HTTException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                            detail=str(e)) 
    
@tesnorboard_api_router.post("/add-text")
def add_text(data: AddTextSchema) -> JSONResponse:

    global summary_writer
    
    if summary_writer is None:
        raise HTTException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                            detail="summary_writer is None. Have you called init?") 

    try:
        summary_writer.add_text(tag=data.tag, 
                                text_string=data.text_string,
                                global_step=data.global_step, walltime=data.walltime)

        return JSONResponse(status_code=status.HTTP_201_CREATED,
                        content={"result": True})
    except Exception as e:
        print("An error was raised when  trying to add_scalar")
        raise HTTException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                            detail=str(e)) 




