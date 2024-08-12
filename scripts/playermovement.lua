local WINDOW_WIDTH = 800
local WINDOW_HEIGHT = 600

local x = 400
local y = 300
local dx = 400
local dy = 400

function update(delta_time)
    x = x + dx * delta_time
    y = y + dy * delta_time
    
    if x > WINDOW_WIDTH or x <= 0 then dx = -dx end
    if y > WINDOW_HEIGHT or y <= 0 then dy = -dy end
    
    set_player_pos(x, y)
end

function render()
    
end