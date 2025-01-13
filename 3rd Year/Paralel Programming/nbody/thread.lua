local environment = ...

function love.threaderror(thread, errorstr)
    print("Thread error: " .. errorstr)
end

local function calculatePhysics(index, object, objects, dt)
    local ax, ay = 0, 0
    for otherIndex, otherBody in pairs(objects) do
        if index ~= otherIndex then
            local dx = object.x - otherBody.x
            local dy = object.y - otherBody.y
            local d = math.sqrt(dx * dx + dy * dy)
            local a = -1.0 * environment.G * otherBody.mass / (d * d)
            local unitVector = {x = dx / d, y = dy / d}
            ax = ax + a * unitVector.x
            ay = ay + a * unitVector.y
        end
    end
    object.vx = object.vx + ax * dt
    object.vy = object.vy + ay * dt

    object.x = object.x + object.vx * dt
    object.y = object.y + object.vy * dt
    
    return object
end

while true do
    local objectChannel = environment.objectChannel
    local data = objectChannel:demand()
    local dt, index, object = data[1], data[2], data[3]
    object = calculatePhysics(index, object, environment.Objects, dt * environment.SECONDS_PER_FRAME)
    objectChannel:supply(object)
end
