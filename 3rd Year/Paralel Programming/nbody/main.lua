require("lib.all")
require("sim.all")

-- Threading variables.
local threads = {}
local objectChannels = {}

-- Camera controls.
local scale = {x = 1, y = 1}
local offset = {x = 0, y = 0}
local diffMouse = {x = 0, y = 0}

function love.load()
    -- Set the colors.
    love.graphics.setBackgroundColor(0.1, 0.1, 0.1)
    love.graphics.setColor(0.9, 0.9, 0.9)

    -- Spawn a shitton of asteorids.
    for _ = 1, ASTEROID_COUNT do
        local x = math.random(ASTEROID_MIN_X, ASTEROID_MAX_X)
        local y = math.random(ASTEROID_MIN_Y, ASTEROID_MAX_Y)
        local distance_from_sun = math.sqrt(x * x + y * y)
        while distance_from_sun < ASTEROID_MIN_DISTANCE_FROM_SUN do
            x = math.random(ASTEROID_MIN_X, ASTEROID_MAX_X)
            y = math.random(ASTEROID_MIN_Y, ASTEROID_MAX_Y)
            distance_from_sun = math.sqrt(x * x + y * y)
        end
        local vx = 0
        local vy = 47.4e3 * (57.9e9 / distance_from_sun)
        local mass = math.random(ASTEROID_MIN_MASS, ASTEROID_MAX_MASS)
        local drawnSize = ((mass - ASTEROID_MIN_MASS) / (ASTEROID_MAX_MASS - ASTEROID_MIN_MASS)) * (ASTEROID_MAX_SIZE - ASTEROID_MIN_SIZE) + ASTEROID_MIN_SIZE
        table.insert(Objects, Body(mass, drawnSize, x, y, vx, vy))
    end

    -- Prepare the threads.
    for index = 1, THREAD_COUNT do
        local thread = love.thread.newThread("thread.lua")
        local objectChannel = love.thread.newChannel()
        table.insert(threads, thread)
        table.insert(objectChannels, objectChannel)
        thread:start({
            threadIndex = index,
            objectChannel = objectChannel, G = G,
            SECONDS_PER_FRAME = SECONDS_PER_FRAME,
            Objects = Objects
        })
    end
end

function love.update(dt)
    -- Quit on pressing escape.
    if love.keyboard.isDown("escape") then
        love.event.quit()
    end

    -- Drag controls.
    if love.mouse.isDown(1) then
        offset.x = offset.x + (love.mouse.getX() - diffMouse.x)
        offset.y = offset.y + (love.mouse.getY() - diffMouse.y)
        diffMouse.x = love.mouse.getX()
        diffMouse.y = love.mouse.getY()
    end
    
    -- Update all threads like so:
    -- Object 1, 2, ..., THREAD_COUNT are assigneg to threads 1, 2, ..., THREAD_COUNT and so on. Not ideal.
    local threadIndex = 1
    for index, body in pairs(Objects) do
        if threadIndex <= THREAD_COUNT then
            -- Supply the objects for which we need to calculate the physics.
            objectChannels[threadIndex]:supply({dt, index, body})
            threadIndex = threadIndex + 1
        else
            -- Collect the resulting objects.
            while threadIndex > 1 do
                threadIndex = threadIndex - 1
                local objectChannel = objectChannels[threadIndex]
                local object = objectChannel:demand()
                Objects[index - THREAD_COUNT + threadIndex - 1] = object
            end
            threadIndex = 1
            objectChannels[threadIndex]:supply({dt, index, body})
            threadIndex = threadIndex + 1
        end
    end

    -- Collect the remaining objects.
    local final = #Objects
    while threadIndex > 1 do
        threadIndex = threadIndex - 1
        local objectChannel = objectChannels[threadIndex]
        local object = objectChannel:demand()
        Objects[final - THREAD_COUNT + threadIndex] = object
    end
end

function love.wheelmoved(_, y)
    -- Zoom controls.
    scale.x = scale.x + y
    scale.y = scale.y + y
    if(scale.x > MAX_ZOOM) then
        scale.x = MAX_ZOOM
        scale.y = MAX_ZOOM
    end
    if(scale.x < MIN_ZOOM) then
        scale.x = MIN_ZOOM
        scale.y = MIN_ZOOM
    end
end

function love.mousepressed(mx, my, b)
    -- Drag controls.
    if b == 1 then
        diffMouse.x = mx
        diffMouse.y = my
    end
end

function love.draw()
    -- Draw the objects.
    local sun = Objects[1]
if DRAWING_ENABLED then
    for _, body in ipairs(Objects) do
        love.graphics.circle(
            "fill", (body.x - sun.x) / DRAWING_MEASURING_UNIT * scale.x + love.graphics.getWidth() / 2 + offset.x,
            (body.y - sun.y) / DRAWING_MEASURING_UNIT * scale.y + love.graphics.getHeight() / 2 + offset.y,
            body.drawnSize * scale.x
        )
    end
end
    love.graphics.print("FPS: " .. love.timer.getFPS(), 10, 10)
end