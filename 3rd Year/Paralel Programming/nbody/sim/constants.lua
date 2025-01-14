-- Starting objects.
Objects = {
    Body(1.989e30, 20, 0, 0, 0, 0),                 -- The sun.
    Body(0.33011e24, 5, 57.9e9, 0, 0, 47.4e3),      -- Mercury
    Body(4.8675e24, 6, 108.2e9, 0, 0, 35.0e3),      -- Venus
    Body(5.97237e24, 8, 149.6e9, 0, 0, 29.8e3),     -- Earth
    Body(0.64171e24, 6, 227.9e9, 0, 0, 24.1e3),     -- Mars
}

-- Constants
G = 6.67408e-11
SECONDS_PER_DAY = 60 * 60 * 24
DRAWING_MEASURING_UNIT = 4e8                        -- Only distances are scaled using this.
SECONDS_PER_FRAME = SECONDS_PER_DAY * 14

THREAD_COUNT = 24                                   -- Constraint: THREAD_COUNT <= #Objects / 2 otherwise everything goes boom.

MAX_ZOOM = 2
MIN_ZOOM = 0.5

ASTEROID_COUNT = 606
ASTEROID_MAX_SIZE = 2
ASTEROID_MIN_SIZE = 0.66
ASTEROID_MAX_MASS = 5e22
ASTEROID_MIN_MASS = 1e22
ASTEROID_MIN_X = -5e11
ASTEROID_MAX_X = 5e11
ASTEROID_MIN_Y = -5e11
ASTEROID_MAX_Y = 5e11
ASTEROID_MIN_DISTANCE_FROM_SUN = 2e10

-- For performance checking.
DRAWING_ENABLED = true                              -- Set to false to disable drawing. In testing, this did not affect FPS in any way.

-- Set up the random seed.
math.randomseed(os.time())