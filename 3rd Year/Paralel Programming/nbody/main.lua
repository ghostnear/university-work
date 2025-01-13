require("love-debug")
require("lib.all")

local Body = Object:extend()
function Body:constructor(mass, drawnSize, x, y, vx, vy)
    self.x = x or 0
    self.y = y or 0
    self.vx = vx or 0
    self.vy = vy or 0
    self.mass = mass
    self.drawnSize = drawnSize
end

local scale = {x = 1, y = 1}

local Objects = {
    Body(1.989e30, 10, 0, 0, 0, 0),                -- The sun.
    Body(0.33011e24, 3, 57.9e9, 0, 0, 47.4e3),     -- Mercury
    Body(4.8675e24, 4, 108.2e9, 0, 0, 35.0e3),     -- Venus
    Body(5.97237e24, 5, 149.6e9, 0, 0, 29.8e3),    -- Earth
    Body(0.64171e24, 4, 227.9e9, 0, 0, 24.1e3),    -- Mars
}

local SECONDS_PER_FRAME = 60 * 60 * 24
local offset = {x = 0, y = 0}
local G = 6.67408e-11
local threads = {}
local objectChannels = {}
local THREAD_COUNT = 10

function love.load()
    -- Spawn a shitton of asteorids.
    for _ = 1, 2001 do
        local x = math.random(-1e12, 1e12)
        local y = math.random(-1e12, 1e12)
        local vx = 0
        local distance_from_sun = math.sqrt(x * x + y * y)
        local vy = 47.4e3 / (distance_from_sun / 57.9e9)
        local mass = math.random(3e23, 1e24)
        local drawnSize = ((mass - 3e23) / (1e24 - 3e23)) * (1 - 0.4) + 0.4
        table.insert(Objects, Body(mass, drawnSize, x, y, vx, vy))
    end

    for index = 1, THREAD_COUNT do
        local thread = love.thread.newThread("thread.lua")
        local objectChannel = love.thread.newChannel()
        table.insert(threads, thread)
        table.insert(objectChannels, objectChannel)
        thread:start({
            threadIndex = index,
            objectChannel = objectChannel,
            G = G,
            SECONDS_PER_FRAME = SECONDS_PER_FRAME,
            Objects = Objects
        })
    end
end

local diffMouse = {x = 0, y = 0}
function love.update(dt)
    if love.keyboard.isDown("escape") then
        love.event.quit()
    end

    if love.mouse.isDown(1) then
        offset.x = offset.x + (love.mouse.getX() - diffMouse.x)
        offset.y = offset.y + (love.mouse.getY() - diffMouse.y)
        diffMouse.x = love.mouse.getX()
        diffMouse.y = love.mouse.getY()
    end

    local threadIndex = 1
    for index, body in pairs(Objects) do
        if threadIndex <= THREAD_COUNT then
            objectChannels[threadIndex]:supply({dt * 100, index, body})
            threadIndex = threadIndex + 1
        else
            while threadIndex > 1 do
                threadIndex = threadIndex - 1
                local objectChannel = objectChannels[threadIndex]
                local object = objectChannel:demand()
                Objects[index - THREAD_COUNT + threadIndex - 1] = object
            end
            threadIndex = 1
            objectChannels[threadIndex]:supply({dt * 100, index, body})
            threadIndex = threadIndex + 1
        end
    end

    local final = #Objects
    while threadIndex > 1 do
        threadIndex = threadIndex - 1
        local objectChannel = objectChannels[threadIndex]
        local object = objectChannel:demand()
        Objects[final - THREAD_COUNT + threadIndex - 1] = object
    end
end

function love.wheelmoved(_, y)
    scale.x = scale.x + y
    scale.y = scale.y + y
    if(scale.x < 0.5) then
        scale.x = 0.5
    end
    if(scale.y < 0.5) then
        scale.y = 0.5
    end
    if(scale.x > 5) then
        scale.x = 5
    end
    if(scale.y > 5) then
        scale.y = 5
    end
end

function love.mousepressed(mx, my, b)
    if b == 1 then
        diffMouse.x = mx
        diffMouse.y = my
    end
end

function love.draw()
    local sun = Objects[1]
    for _, body in ipairs(Objects) do
        love.graphics.circle(
            "fill", (body.x - sun.x) / 1e9 * scale.x + love.graphics.getWidth() / 2 + offset.x,
            (body.y - sun.y) / 1e9 * scale.y + love.graphics.getHeight() / 2 + offset.y, 
            body.drawnSize * scale.x
        )
    end
    love.graphics.print("FPS: " .. love.timer.getFPS(), 10, 10)
end