import uvicorn
from tensorboard_main_api import app

app = app

if __name__ == "__main__":
    print("Starting uvicorn...")
    uvicorn.run(
        "main:app",
        host="localhost",
        port=8002,
        log_level="Debug",
    )



