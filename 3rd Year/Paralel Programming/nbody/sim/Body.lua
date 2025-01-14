local Body = Object:extend()
function Body:constructor(mass, drawnSize, x, y, vx, vy)
    self.x = x or 0
    self.y = y or 0
    self.vx = vx or 0
    self.vy = vy or 0
    self.mass = mass
    self.drawnSize = drawnSize
end

return Body