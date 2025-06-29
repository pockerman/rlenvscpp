"""The Acrobot environment from gymnasium:
for more information check: https://gymnasium.farama.org/environments/classic_control/acrobot/

"""
import gymnasium as gym
from typing import Any
from loguru import logger
from fastapi import APIRouter, Body, status
from fastapi.responses import JSONResponse
from fastapi import HTTPException
from time_step_response import TimeStep, TimeStepType

lunar_lander_discrete_router = APIRouter(prefix="/gymnasium/lunar-lander-discrete-env",
                                         tags=["Lunar Lander Discrete API"])

ENV_NAME = "LunarLander"

# the environments to create
envs = {
    0: None
}

# actions that the environment accepts
ACTIONS_SPACE = {0: "do nothing",
                 1: "fire left orientation engine",
                 2: "fire main engine",
                 3: "fire right orientation engine"
                 }


@lunar_lander_discrete_router.get("/action-space")
async def get_action_space() -> JSONResponse:
    return JSONResponse(status_code=status.HTTP_200_OK,
                        content={"action_space": ACTIONS_SPACE})


@lunar_lander_discrete_router.get("/is-alive")
async def get_is_alive(cidx: int) -> JSONResponse:
    global envs
    if cidx in envs:
        env = envs[cidx]

        if env is None:
            return JSONResponse(status_code=status.HTTP_200_OK,
                                content={"result": False})
        else:
            return JSONResponse(status_code=status.HTTP_200_OK,
                                content={"result": True})
    else:
        return JSONResponse(status_code=status.HTTP_400_BAD_REQUEST,
                            content={"message": f"Environment {ENV_NAME} and index {cidx} has not been created"})


@lunar_lander_discrete_router.post("/close")
async def close(cidx: int) -> JSONResponse:
    global envs
    if cidx in envs:
        env = envs[cidx]
        if env is not None:
            envs[cidx].close()
            envs[cidx] = None
            logger.info(f'Closed environment {ENV_NAME}  and index {cidx}')
            return JSONResponse(status_code=status.HTTP_202_ACCEPTED,
                                content={"message": f"Environment {ENV_NAME} and index {cidx} is closed"})

    return JSONResponse(status_code=status.HTTP_400_BAD_REQUEST,
                        content={"message": f"Environment {ENV_NAME} and index {cidx} has not been created"})


@lunar_lander_discrete_router.post("/make")
async def make(version: str = Body(default="v3"), cidx: int = Body(...),
               options: dict[str, Any] = Body(default={'gravity': -10.0, 'enable_wind': False,
                                                       'wind_power': 15.0, 'turbulence_power': 1.5})) -> JSONResponse:
    if version == 'v1' or version == 'v2':
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST,
                            detail='Environment version v1 for `LunarLander` '
                                   'is deprecated. Please use `LunarLander-v3` instead.')

    global envs
    env_type = f"{ENV_NAME}-{version}"
    if cidx in envs:
        env = envs[cidx]

        if env is not None:
            envs[cidx].close()

        try:
            env = gym.make(env_type, continuous=False, **options)
            envs[cidx] = env
        except Exception as e:
            logger.error('An exception was raised')
            logger.opt(exception=e).info("Logging exception traceback")
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                                detail=str(e))
    else:
        try:
            env = gym.make(env_type)
            envs[cidx] = env
        except Exception as e:
            logger.error('An exception was raised')
            logger.opt(exception=e).info("Logging exception traceback")
            raise HTTPException(status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                                detail=str(e))

    logger.info(f'Created environment {ENV_NAME} and index {cidx}')
    return JSONResponse(status_code=status.HTTP_201_CREATED,
                        content={"result": True})


@lunar_lander_discrete_router.post("/reset")
async def reset(seed: int = Body(default=42), cidx: int = Body(...),
                options: dict[str, Any] = Body(default={})) -> JSONResponse:
    """Reset the environment

    :return:
    """

    global envs
    if cidx in envs:
        env = envs[cidx]

        if env is not None:

            if len(options) != 0:
                observation, info = env.reset(seed=seed, options=options)
            else:
                observation, info = env.reset(seed=seed)
            observation = [float(val) for val in observation]
            step = TimeStep(observation=observation,
                            reward=0.0,
                            step_type=TimeStepType.FIRST,
                            info=info,
                            discount=1.0)
            logger.info(f'Reset environment {ENV_NAME}  and index {cidx}')
            return JSONResponse(status_code=status.HTTP_202_ACCEPTED,
                                content={"time_step": step.model_dump()})

    raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST,
                        detail={"message": f"Environment {ENV_NAME} is not initialized."
                                           " Have you called make()?"})


@lunar_lander_discrete_router.post("/step")
async def step(action: int = Body(...), cidx: int = Body(...)) -> JSONResponse:
    if action not in ACTIONS_SPACE:
        raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST,
                            detail=f"Action {action} not in {list(ACTIONS_SPACE.keys())}")

    global envs
    if cidx in envs:
        env = envs[cidx]

        if env is not None:
            logger.info(f"Stepping in environment {ENV_NAME} with action={action}")
            observation, reward, terminated, truncated, info = env.step(action)
            observation = [float(val) for val in observation]

            step_type = TimeStepType.MID
            if terminated:
                step_type = TimeStepType.LAST

            if info is not None:
                info['truncated'] = truncated

            step = TimeStep(observation=observation,
                            reward=reward,
                            step_type=step_type,
                            info=info,
                            discount=1.0)

            logger.info(f'Step in environment {ENV_NAME} and index {cidx}')
            return JSONResponse(status_code=status.HTTP_202_ACCEPTED,
                                content={"time_step": step.model_dump()})

    raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST,
                        detail=f"Environment {ENV_NAME} is not initialized. Have you called make()?")


@lunar_lander_discrete_router.post("/sync")
async def sync(cidx: int = Body(...), options: dict[str, Any] = Body(default={})) -> JSONResponse:
    return JSONResponse(status_code=status.HTTP_202_ACCEPTED,
                        content={"message": "OK"})
