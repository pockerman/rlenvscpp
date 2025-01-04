from loguru import logger
from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

from api_config import get_api_config
from tensorboard_api import tesnorboard_api_router


BASE_URL = "/api"

CONFIG = get_api_config()

app = FastAPI(title=CONFIG.API_TITLE,
              debug=CONFIG.DEBUG)

# CORS handling: https://fastapi.tiangolo.com/tutorial/cors/
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(tesnorboard_api_router)

 
@app.on_event("startup")
def on_startup():
    """Loads the trained model

    Returns
    -------

    """

    # make checks

    logger.info("Starting API...")
